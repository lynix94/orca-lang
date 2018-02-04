/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaGlobal.h - global settings

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef __DEF_ORCA_GLOBAL
#define __DEF_ORCA_GLOBAL

#include <map>
#include <vector>
#include <set>

#include "porting.h"
#include "orca_common.h"
#include "orcaObject.h"

using namespace std;

extern pthread_mutex_t g_rc_mutex;
extern pthread_key_t g_thread_context;

class orcaVM;

struct thread_arg_t
{
	orcaVM* vm_main;
	const char* code;
	const char* offset;
	pthread_t tid;
	int* run_count;
	int per;
	orcaObject* iter;
	bool is_iterator;
};

struct thread_pool_t 
{
	portCond cond;
	portMutex mutex;

	bool running;
	thread_arg_t arg;

	thread_pool_t() {
		running = false;
	}
};

class LIBORCA_API thread_pool
{
public:
	thread_pool();
	~thread_pool();

	bool signal_restart(thread_arg_t arg);
	void work(thread_arg_t arg);

	void join_all();

	portCond m_cond_start;
	portMutex m_mutex_pool;
	portCond m_cond_done;
	
private:
	void set_start(pthread_t tid);
	void set_stop(pthread_t tid);
	thread_arg_t get_arg(pthread_t tid);

	bool is_exit();
	void inc_run(pthread_t tid);
	void dec_run(pthread_t tid);

private:
	bool m_quit;
	map<pthread_t, thread_pool_t*> m_map;

	portMutex m_mutex_run;
};


#ifdef WINDOWS
__declspec(dllimport) thread_pool *g_thread_pool;
#else
extern thread_pool *g_thread_pool;
#endif



class orcaCodeContainer
{
public:
	orcaCodeContainer();
	~orcaCodeContainer();

	char* new_define(int size);
	char* new_define(int size, const string& name);
	char* new_code(int size);
	char* new_code(int size, const string& name);
	void remove_code(const string& name);
	void remove_define(const string& name);
	const char* get_base(const char* code, int* size = NULL);
	string get_name(const char* code);
	const char* get_addr(string name, int* size = NULL);
	int get_size(const char* code);

private:
	typedef map<const char*, string> code_name_t;
	typedef map<string, const char*> name_code_t;

	code_name_t m_code_name;
	name_code_t m_code;
	name_code_t m_define;
};

#ifdef WINDOWS
__declspec(dllimport) orcaCodeContainer *g_codes;
#else
extern orcaCodeContainer *g_codes;
#endif


const char* const_strdup(const char* str);

#endif

