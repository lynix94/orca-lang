/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaCPP.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_CPP
#define _DEF_ORCA_CPP

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <stdlib.h>

#ifdef WINDOWS
#include <direct.h>
#endif

#include "porting.h"
#include "orcaObject.h"

#include "kyString.h"


namespace fs = boost::filesystem;

using namespace std;
using namespace boost;


class orcaCPP : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaCPP);

	orcaCPP()
	{
		set_name("cpp");

		char* cp = getenv("ORCA_HOME");
		if (cp != NULL) {
			m_path = cp;
			m_path += "/tmp/";
		}

		if (fs::exists(m_path) == false || fs::is_directory(m_path) == false) {
#ifdef WINDOWS
			m_path = "C:\\windows\\temp\\";  // change to process path
#else
			m_path = "/tmp/";
#endif
		}
	}

	virtual orcaData operator()(orcaVM* vm, int n) 
	{
		if (n < 3) vm->need_param();

		string name = vm->get_param(0).String();
		orcaData dt = vm->get_param(1);

		string mod = m_path + dl_get_filename(name);
		if (need_recompile(vm, mod, dt)) {
			string code = vm->get_param(2).String();
			if (compile(name.c_str(), mod.c_str(), code)==false) {
				throw orcaException(vm, "orca.context", 
										"context module compile failed");
			}
		}

		orcaData ret = load(name);
		return ret;
	}


	bool need_recompile(orcaVM* vm, string& mod, orcaData dt)
	{
		if (fs::exists(mod) == false || fs::is_directory(mod) == true) {
			return true;
		}

		orcaDatetime* dtp = dynamic_cast<orcaDatetime*>(dt.Object());
		if (dtp == NULL) {
			return true;
		}

		ptime mod_ptime = from_time_t(fs::last_write_time(mod));
		ptime& src_ptime = dtp->get_ptime();
		if (mod_ptime < src_ptime) {
			return true;
		}

		return false;
	}

	bool compile(const char* name, const char* mod, string& src_code)
	{
		string file_name = m_path + name + ".cpp";

		string code;
		string header;
		string line;
		string cflags;
		string ldflags;

		vector<string> lines = kyString::chomp(src_code, "\n");
		for (int i=0; i<lines.size(); i++) {
			string line = kyString::strip(lines[i]);
			if (kyString::starts_with(line, "#include")) {
				header += line + "\n";
			}
			else if (kyString::starts_with(line, "#cflags")) {
				line = line.substr(strlen("#cflags"));
				cflags += line;
			}
			else if (kyString::starts_with(line, "#ldflags")) {
				line = line.substr(strlen("#ldflags"));
				ldflags += line;
			}
			else {
				code += line + "\n";
			}
		}

		const char* format = "%s\n#include \"orcaObject.h\"\n\n\
	class %s : public orcaObject\n\
	{\n\
	public:\n\
		orcaData udf(orcaVM* vm, vector<orcaData>& argv)\n\
		{\n\
			%s\n\n\
		}\n\n\
		orcaData operator()(orcaVM* vm, int param_n)\n\
		{\n\
			vector<orcaData> argv;\n\
			for (int i=0; i<param_n; i++)\n\
				argv.push_back(vm->get_param(i));\n\n\
			return udf(vm, argv);\n\
		}\n\
	};\n\n\
	#ifdef WINDOWS\n\
	#define EXPORT __declspec(dllexport)\n\
	#else\n\
	#define EXPORT\n\
	#endif\n\n\
	extern \"C\" EXPORT void* get_%s()\n\
	{\n\
		%s* sp = new %s();\n\
		return sp;\n\
	}\n\n";

		int len = strlen(format) + strlen(name)*4 + header.length() + code.length() + 256;
		char* buff = (char*)malloc(len);

		sprintf(buff, format, header.c_str(), name, code.c_str(), name, name, name);

		fs::remove(mod);
		FILE* fp = fopen(file_name.c_str(), "w");
		if (fp == NULL) {
			return false;
		}

		int ret = fwrite(buff, 1, strlen(buff), fp);
		fclose(fp);

#ifdef LINUX
		string cmd = string("g++ -shared -o ") + mod + " " + file_name + 
							" -I${ORCA_HOME}/include/orca -L${ORCA_HOME}/lib -lorca" + cflags + ldflags;
		printf("cpp external module compile: %s\n", cmd.c_str());
		::system(cmd.c_str());
#else
		string cmd = string("vscompile.bat ") + m_path + " " + name + " " + dl_get_filename(name) + " " + cflags + " " + ldflags;
		printf("cpp external module compile: %s\n", cmd.c_str());
		::system(cmd.c_str());
#endif

		if (!fs::exists(mod))
			return false;

		return true;
	}

	orcaData load(string& name)
	{
		string mod = dl_get_filename(name);
		DLHANDLE handle = dlopen(mod.c_str(), RTLD_NOW);

		if (handle == NULL) {
			string mod = m_path + dl_get_filename(name);
			handle = dlopen(mod.c_str(), RTLD_NOW);
		}

		if (handle == NULL) {
			printf("file %s: %s\n", mod.c_str(), dlerror());
			printf("module file not exists\n");
			return NIL;
		}

		typedef void* (*fp_t)(void);

		fp_t pfunc = (fp_t)dlsym(handle, (string("get_")+name).c_str());
		if (pfunc == NULL) {
			printf("### invalid module file: %p, %s\n", handle, name.c_str());
			return NIL;
		}

		orcaObject* obj = (orcaObject*)(*pfunc)();
		return obj;
	}

	string m_path;
	string m_path2;
};


#endif

