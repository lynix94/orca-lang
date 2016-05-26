/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaOS.h - system utils

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_OS
#define _DEF_ORCA_OS

#include <iostream>
#include <stdlib.h>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "porting.h"
#include "orcaObject.h"
#include "orcaList.h"
#include "orcaDatetime.h"

#ifdef WINDOWS
#include <direct.h>
#endif


namespace fs = boost::filesystem;

using namespace std;
using namespace boost;

class orcaDirIter : public orcaObject
{
public:
	orcaDirIter(void* vp) { } 
	virtual ~orcaDirIter()
	{
		delete m_iter;
	}

	orcaObject* v_clone() 
	{
		orcaDirIter* ip = new orcaDirIter(NULL);
		ip->m_iter = m_iter;
		return ip;
	}

	orcaDirIter(string& path)
	{
		m_iter = new fs::directory_iterator(path);

		set_name("iterator");
		insert_native_function("next", (object_fp)&orcaDirIter::ex_next);
	}


	orcaData ex_next(orcaVM* vm, int n)
	{
		if (*m_iter == m_end) {
			throw orcaException(vm, "done", "done");
		}

		string str = (*m_iter)->path().string();
		++(*m_iter);

		return str;
	}

private:
	fs::directory_iterator* m_iter;
	fs::directory_iterator m_end;
};


class orcaDirTraverse : public orcaObject
{
public:
	orcaDirTraverse(void* vp) { } 

	virtual ~orcaDirTraverse()
	{
		while (!m_iter.empty()) {
			delete m_iter[m_iter.size()-1];
			m_iter.pop_back();
		}
	}

	orcaObject* v_clone() 
	{
		orcaDirTraverse* ip = new orcaDirTraverse(NULL);
		ip->m_iter = m_iter;
		return ip;
	}


	orcaDirTraverse(string& path)
	{
		m_iter.push_back(new fs::directory_iterator(path));

		set_name("traverse");
		insert_native_function("next", (object_fp)&orcaDirTraverse::ex_next);
	}

	orcaData ex_next(orcaVM* vm, int n)
	{
retry:
		if (m_iter.empty()) {
			throw orcaException(vm, "done", "done");
		}

		fs::directory_iterator* iter = m_iter[m_iter.size()-1];
		
		if (*iter == m_end) {
			m_iter.pop_back();
			delete iter;
			goto retry;
		}

		string str = (*iter)->path().string();
		++(*iter);

		if (fs::is_directory(str)) {
			m_iter.push_back(new fs::directory_iterator(str));
		}

		return str;
	}

private:
	vector<fs::directory_iterator*> m_iter;
	fs::directory_iterator m_end;
};

class orcaOS : public orcaObject 
{
public:
	orcaOS() 
	{
		set_name("os");

		insert_static_native_function("run", (object_fp)&orcaOS::ex_run);
		insert_static_native_function("getenv", (object_fp)&orcaOS::ex_getenv);

		// file work
		insert_static_native_function("cwd", (object_fp)&orcaOS::ex_cwd);
		insert_static_native_function("mkdir", (object_fp)&orcaOS::ex_mkdir);
		insert_static_native_function("rename", (object_fp)&orcaOS::ex_rename);
		insert_static_native_function("copy", (object_fp)&orcaOS::ex_copy);
		insert_static_native_function("remove", (object_fp)&orcaOS::ex_remove);
		insert_static_native_function("ls", (object_fp)&orcaOS::ex_ls);
		insert_static_native_function("cd", (object_fp)&orcaOS::ex_cd);

		insert_static_native_function("isexists", (object_fp)&orcaOS::ex_isexists);
		insert_static_native_function("isfile", (object_fp)&orcaOS::ex_isfile);
		insert_static_native_function("isdir", (object_fp)&orcaOS::ex_isdir);

		insert_static_native_function("dir_iterator", (object_fp)&orcaOS::ex_dir_iterator);
		insert_static_native_function("dir_traverser", (object_fp)&orcaOS::ex_dir_traverser);

		insert_static_native_function("read", (object_fp)&orcaOS::ex_read);
		insert_static_native_function("write", (object_fp)&orcaOS::ex_write);
		insert_static_native_function("file_size", (object_fp)&orcaOS::ex_file_size);
		insert_static_native_function("last_write_time", (object_fp)&orcaOS::ex_last_write_time);
	}

	orcaData ex_run(orcaVM* vm, int n) 
	{
		string& cmd = vm->get_param(0).String();
		FILE* fp = popen(cmd.c_str(), "r");
		if (fp == NULL) {
			return NIL;
		}

		// check __cout__
		bool update = false;
		orcaData ret;
		if (vm->get_caller().o()->has_member("__cout__", ret)) {
			if (is<TYPE_NIL>(ret) || is<TYPE_STR>(ret)) {
				update = true;
			}
		}

		// read and print
		string str;
		char buff[1024];
		while(fgets(buff, 1024, fp)) {
			if (update)  str += buff;
			printf("%s", buff);
		}

		if (update) {
			vm->get_caller().o()->update_member("__cout__", str);
		}

		return NIL;
	}

	orcaData ex_getenv(orcaVM* vm, int n) 
	{
		string& env = vm->get_param(0).String();
		char* ep = getenv(env.c_str());
		if (ep == NULL) {
			throw orcaException(vm, "orca.name", string("env ") + env + " not exists");
		}

		return ep;
	}

	orcaData ex_cwd(orcaVM* vm, int n) 
	{
		return fs::current_path().string();
	}

	orcaData ex_cd(orcaVM* vm, int n) 
	{
		string& name = vm->get_param(0).String();
		chdir(name.c_str());
		return NIL;
	}

	orcaData ex_dir_iterator(orcaVM* vm, int n) 
	{
		string& name = vm->get_param(0).String();
		orcaDirIter* ip = new orcaDirIter(name);
		return ip;
	}

	orcaData ex_dir_traverser(orcaVM* vm, int n) 
	{
		string& name = vm->get_param(0).String();
		orcaDirTraverse* tp = new orcaDirTraverse(name);
		return tp;
	}

	orcaData ex_mkdir(orcaVM* vm, int n) 
	{
		string& name = vm->get_param(0).String();

		try {
			fs::create_directory(name);
		} catch(...) {
			throw orcaException(vm, "orca.file", string("directory ") 
								+ name + "creation failed");
		}

		return NIL;
	}

	orcaData ex_remove(orcaVM* vm, int n) 
	{
		string& name = vm->get_param(0).String();

		try {
			fs::remove(name);
		} catch(...) {
			throw orcaException(vm, "orca.file", string("remove ") 
								+ name + " failed");
		}

		return NIL;
	}

	orcaData ex_ls(orcaVM* vm, int n) 
	{
		string& name = vm->get_param(0).String();
		orcaList* lp = new orcaList();

		try {
			fs::directory_iterator end;
			fs::directory_iterator itr(name);

			for(; itr != end; ++itr) {
				lp->push_back(itr->path().string());
			}

		} catch(...) {
			delete lp;
			throw orcaException(vm, "orca.file", string("list dir ") 
								+ name + " failed");
		}

		return lp;
	}

	orcaData ex_rename(orcaVM* vm, int n) 
	{
		string& src = vm->get_param(0).String();
		string& dst = vm->get_param(1).String();

		try {
			if (!fs::exists(src)) {
				throw orcaException(vm, "orca.file", string("file ") 
									+ src + " not exists");
			}

			if (fs::exists(dst)) {
				throw orcaException(vm, "orca.file", string("destion file ") 
									+ dst + " exists");
			}

			fs::rename(src, dst);
		} catch(...) {
			throw orcaException(vm, "orca.file", string("rename ") 
								+ src + " failed");
		}

		return NIL;
	}

	orcaData ex_copy(orcaVM* vm, int n) 
	{
		string& src = vm->get_param(0).String();
		string& dst = vm->get_param(1).String();

		try {
			if (!fs::exists(src)) {
				throw orcaException(vm, "orca.file", string("file ") 
									+ src + " not exists");
			}

			if (fs::exists(dst)) {
				throw orcaException(vm, "orca.file", string("destion file ") 
									+ dst + " exists");
			}

			fs::copy_file(src, dst);
		} catch(...) {
			throw orcaException(vm, "orca.file", string("copy ") 
								+ src + " failed");
		}

		return NIL;
	}

	orcaData ex_isexists(orcaVM* vm, int n) 
	{
		try {
			string& name = vm->get_param(0).String();
			return fs::exists(name);
		}
		catch (...) {
			return false;
		}
	}

	orcaData ex_isdir(orcaVM* vm, int n) 
	{
		try {
			string& name = vm->get_param(0).String();
			return fs::is_directory(name);
		}
		catch (...) {
			return false;
		}
	}

	orcaData ex_isfile(orcaVM* vm, int n) 
	{
		try {
			string& name = vm->get_param(0).String();
			return (fs::exists(name) && !fs::is_directory(name));
		}
		catch (...) {
			return false;
		}
	}

	orcaData ex_read(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		int size = INT_MAX;
		int offset = 0;

		string& path = vm->get_param(0).String();
		if (!is<TYPE_NIL>(vm->get_param(2))) {
			offset = vm->get_param(2).Integer();
		}

		if (!is<TYPE_NIL>(vm->get_param(1))) {
			size = vm->get_param(1).Integer();
			if (size < 0) size = INT_MAX;
		}

		FILE* fp = fopen(path.c_str(), "r");
		if (fp == NULL) {
			throw orcaException(vm, "orca.file", string("file ") 
								+ path + " not exists");
		}

		fseek(fp, 0, SEEK_END);
		int fsize = ftell(fp);
		fseek(fp, offset, SEEK_SET);

		int rsize = size;
		if (fsize - offset < rsize) {
			rsize = fsize - offset;
		}

		string buff;
		buff.resize(rsize);
		fread(&buff[0], 1, rsize, fp);
		fclose(fp);
		
		return buff;
	}

	orcaData ex_write(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		int size = INT_MAX;
		int offset = 0;
		string buff;

		string& path = vm->get_param(0).String();
		if (!is<TYPE_NIL>(vm->get_param(2))) {
			offset = vm->get_param(2).Integer();
		}

		buff = vm->get_param(1).String();
		

		FILE* fp = fopen(path.c_str(), "r+");
		if (fp == NULL) {
			fp = fopen(path.c_str(), "w");
			if (fp == NULL) {
				throw orcaException(vm, "orca.file", string("file ") 
									+ path + " creation fail");
			}
		}

		fseek(fp, offset, SEEK_SET);
		int ret = fwrite(buff.c_str(), 1, buff.length(), fp);
		fclose(fp);
		
		return ret;
	}

	orcaData ex_file_size(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		string& path = vm->get_param(0).String();
		FILE* fp = fopen(path.c_str(), "r");
		if (fp == NULL) {
			throw orcaException(vm, "orca.file", string("file ") 
								+ path + " not exists");
		}

		fseek(fp, 0, SEEK_END);
		int fsize = ftell(fp);
		fclose(fp);
		return fsize;
	}

	orcaData ex_last_write_time(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		string& path = vm->get_param(0).String();
		try {
			time_t tt = fs::last_write_time(fs::path(path));

			return new orcaDatetime(from_time_t(tt));
		}
		catch (...) {
			throw orcaException(vm, "orca.param", string("file ") + path + " is invalid");
		}
	}

};

#endif

