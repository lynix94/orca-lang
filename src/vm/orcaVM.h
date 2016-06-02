/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaVM.h - main orcaVM routine

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_VM
#define _DEF_ORCA_VM

#include <vector>
#include <map>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
namespace fs = boost::filesystem;

#include "orcaData.h"

class orcaTrace;
class orcaForStack;
class orcaDecodeStack;
class orcaPure;
class orcaStack;
class orcaLocal;
class orcaList;
class orcaOnce;


using namespace std;

void orca_error(const char* fmt, ...);

enum FUNCTION_INDEX
{
	FI_STR_LENGTH = 1,
	FI_STR_FIND,
	FI_STR_FIND_ALL,
	FI_STR_STRIP,
	FI_STR_LSTRIP,
	FI_STR_RSTRIP,
	FI_STR_TO_INT,
	FI_STR_TO_FLOAT,
	FI_STR_TO_STR,
	FI_STR_REPLACE,
	FI_STR_STARTSWITH,
	FI_STR_ENDSWITH,
	FI_STR_HASH,
	FI_STR_CHOMP,
	FI_STR_PUSH_BACK,
	FI_STR_CHAR,
	FI_STR_UPPER,
	FI_STR_LOWER,
	FI_INT_TO_INT,	
	FI_BN_TO_INT,	
	FI_INT_TO_FLOAT,	
	FI_BN_TO_FLOAT,	
	FI_INT_TO_STR,	
	FI_BN_TO_STR,	
	FI_FLOAT_TO_INT,	
	FI_FLOAT_TO_FLOAT,	
	FI_FLOAT_TO_STR,	
	FI_BOOL_TO_INT,	
	FI_BOOL_TO_FLOAT,	
	FI_BOOL_TO_STR,	
};

class LIBORCA_API orcaVM
{
friend class orcaLocal;
public:
	void init_once();
	void init();
	void cleanup();

	inline orcaData invoke_internal_func(InternalFunction& in);
	void call(int param_n, const char* addr = NULL);

	orcaObject* exec_define(const char* c, int size, const char* code, 
							orcaObject* parent, time_t last_write_time);

	void exec_code(const char* c, const char* offset=NULL);
	bool load(const string& module_name, orcaObject* parent = NULL);
	bool load_cpp(const string& mod_name);
	void reserve_local(); // for interactive
	void parallel_do(const char* code, const char* offset, 
					 int* run_count = NULL, orcaObject* op = NULL, int per = 0,
					 bool is_iterator = true);

	// for interface
	orcaData get_param(int i);
	void need_param();
	void set_param(int i, orcaData d);
	void push_param(orcaData d);
	void push_stack(orcaData d);
	orcaData pop_stack();
	orcaData get_caller();
	void set_caller(orcaObject* o);

	orcaData do_context(const char* mod, const char* name, 
						const char* cp, time_t last_write_time);

private:
	orcaData& handle_throw(const char* name);
	orcaForStack* m_for_stack;
	orcaDecodeStack* m_decode_stack;

public:
	orcaObject* m_module;
	orcaObject* m_curr;
	orcaStack* m_stack;
	orcaLocal* m_local;
	orcaPure* m_pure;
	orcaOnce* m_once;

	orcaTrace* m_trace;
	string m_last_trace_info;

	static map<const char*, int> m_debug;
	static map<const char*, string> m_debug_name;
	static map<const char*, string> m_debug_line;
	static vector<fs::path> m_module_path;
};

LIBORCA_API int orca_launch_module(orcaVM* vm, char* module, 
				int argc=0, char** argv = NULL);

LIBORCA_API int orca_launch_interpreter(orcaVM* vm);

LIBORCA_API void set_current_vm(orcaVM* vm);
LIBORCA_API orcaVM* get_current_vm();

#endif

