/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaGlobal.cpp - global settings

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "porting.h"

#include <iostream>

#include "orcaData.h"
#include "orcaGlobal.h"

#include "orcaVM.h"
#include "orcaLocal.h"
#include "orcaException.h"
#include "orcaTime.h"

#include "kyString.h"

using namespace std;

pthread_mutex_t g_rc_mutex;
pthread_key_t g_thread_context;

thread_pool *g_thread_pool;
orcaCodeContainer *g_codes;

struct init_once
{
	init_once()
	{
		pthread_mutex_init(&g_rc_mutex, NULL);
		pthread_key_create(&g_thread_context, NULL);

		g_thread_pool = new thread_pool();
		g_codes = new orcaCodeContainer();

		g_timer = new orcaGlobalTimer();
		g_timer->start();
	}

	~init_once()
	{
		pthread_mutex_destroy(&g_rc_mutex);
		pthread_key_delete(g_thread_context);

		delete g_thread_pool;
		delete g_codes;

		g_timer->quit();
		delete g_timer;
	}
};

init_once g_init_once;




thread_pool::thread_pool() : m_quit(false) {}

thread_pool::~thread_pool()
{
	map<pthread_t, thread_pool_t*>::iterator it;
	for (it = m_map.begin(); it != m_map.end(); ++it) {
		delete it->second;
	}
}


bool thread_pool::signal_restart(thread_arg_u *arg)
{
	map<pthread_t, thread_pool_t*>::iterator it;
	for (it = m_map.begin(); it != m_map.end(); ++it) {
		it->second->mutex.lock();
		if (it->second->running == false) {
			it->second->arg = arg;
			it->second->cond.signal();
			it->second->mutex.unlock();
			return true;
		}
		it->second->mutex.unlock();
	}

	return false;
}

void thread_pool::work(thread_arg_u *arg)
{
	PRINT1("thread added, tid:%d\n", (int)arg->p_do.tid);
	pthread_t tid = arg->p_do.tid; // p_do.tid == p_for.tid == p_call.tid (same addr)
	thread_pool_t* pool = new thread_pool_t;
	m_map[tid] = pool;
	m_map[tid]->running = true;
	m_map[tid]->arg = arg;

	do {
		arg = get_arg(tid);

		orcaVM* vm = arg->p_do.vm_main; // p_do.vm_main == p_for.vm_main
		set_current_vm(vm);

		switch (arg->p_do.type)
		{
		case 'f':
			if (arg->p_for.iter != NULL) {
				vm->m_stack->push(arg->p_for.iter);
				vm->m_stack->push(arg->p_for.per);
			}
			// fallthrough
		case 'd':
			set_start(tid);

			try {
				vm->exec_code(arg->p_do.code, arg->p_do.offset);
				vm->m_local->decrease();
			}
			catch (orcaException& e) {
				printf("uncaught exception: %s - %s\n", e.who(), e.what());
				cout << e.m_stack_trace << endl;
				vm->m_stack->dump();
				vm->m_local->dump();
				exit(-1);
			}
			break;

		case 'c':
			orcaData func = *arg->p_call.func;
			vector<orcaData>* params = arg->p_call.params;
			int param_n = params->size();

			vm->m_local->reset(); // resued thread lp is to 0 so set it FRAME SIZE

			vm->push_stack(func);
			func.rc_inc();
			for (int i=params->size()-1; i>=0; i--) {
				vm->push_stack(params->at(i));
			}

			set_start(tid);

			try {
				vm->call(param_n);
			}
			catch(orcaException& e) {
				printf("uncaugted exception in thread: %s %s\n", e.who(), e.what());
				cout << e.m_stack_trace << endl;
				func.rc_dec();
				vm->m_stack->dump();
				vm->m_local->dump();
				exit(-1);
			}
		}



		// wait next job
		if (is_exit()) {
			set_stop(tid);
			// clean & free arg
			arg->p_do.vm_main->cleanup();
			delete arg->p_do.vm_main;
			delete arg;

			return;
		}

		set_stop(tid);
		// clean & free arg
		arg->p_do.vm_main->cleanup();
		delete arg->p_do.vm_main;
		delete arg;

		if (is_exit()) {
			return;
		}

	} while (true);

	return;
}

void thread_pool::join_all()
{
	// wait until all done
	while (true) {
		int running  = 0;
		port_msleep(10);

		m_mutex_pool.lock();
		map<pthread_t, thread_pool_t*>::iterator it;
		for (it = m_map.begin(); it != m_map.end(); ++it) {
			if (it->second->running) {
				running++;
			}
		}
		m_mutex_pool.unlock();

		if (running == 0) {
			break;
		}
	}

	m_quit = true;
	map<pthread_t, thread_pool_t*>::iterator it;
	for (it = m_map.begin(); it != m_map.end(); ++it) {
retry:
		while (it->second->running) { 
			port_msleep(1);
		}

		it->second->mutex.lock();
		if (it->second->running) {
			it->second->mutex.unlock();
			goto retry;
		}
		
		it->second->cond.signal();
		it->second->mutex.unlock();
	}

	for (it = m_map.begin(); it != m_map.end(); ++it) {
		PRINT1("thread join, tid:%d\n", (int)it->first);
		pthread_join(it->first, NULL);
	}
}


void thread_pool::set_start(pthread_t tid)
{
	PRINT1("thread start, tid:%d\n", (int)tid);
	m_cond_mutex.lock();
	m_map[tid]->running = true;
	m_cond_start.signal();
	inc_run(tid);
	m_cond_mutex.unlock();

}

void thread_pool::set_stop(pthread_t tid)
{
	PRINT1("thread stop, tid:%d\n", (int)tid);
	m_cond_mutex.lock();
	dec_run(tid);
	m_cond_done.signal();
	m_cond_mutex.unlock();

	m_map[tid]->mutex.lock();
	m_map[tid]->running = false;
	m_map[tid]->cond.wait(&m_map[tid]->mutex);
	m_map[tid]->mutex.unlock();
}

thread_arg_u* thread_pool::get_arg(pthread_t tid)
{
	return m_map[tid]->arg;
}

bool thread_pool::is_exit() 
{
	return m_quit;
}

void thread_pool::inc_run(pthread_t tid)
{
	if (m_map[tid]->arg->p_for.run_count) {
		(*m_map[tid]->arg->p_for.run_count)++;
	}
}

void thread_pool::dec_run(pthread_t tid)
{
	if (m_map[tid]->arg->p_for.run_count) {
		(*m_map[tid]->arg->p_for.run_count)--;
	}
}




orcaCodeContainer::orcaCodeContainer() {}
orcaCodeContainer::~orcaCodeContainer()
{
	map<string, const char*>::iterator mi = m_codes.begin();
	for(; mi!=m_codes.end(); ++mi) {
		delete[] mi->second;
	}

	mi = m_defines.begin();
	for(; mi!=m_defines.end(); ++mi) {
		delete[] mi->second;
	}
}

char* orcaCodeContainer::new_define(int size)
{
	char* define = new char[size];
	return define;
}

void orcaCodeContainer::regist_define(const string& name, char* code)
{
	if (m_defines.find(name) != m_defines.end()) {
		throw orcaException(NULL, "orca.lang", string("duplicated define - ") + name.c_str());
	}

	m_defines[name] = code;
}


char* orcaCodeContainer::new_code(int size)
{
	char* code = new char[size];
	return code;
}

void orcaCodeContainer::regist_code(const string& name, char* code, int size)
{
	if (m_codes.find(name) != m_codes.end()) {
		throw orcaException(NULL, "orca.lang", string("duplicated code - ") + name.c_str());
	}

	m_code_name[code] = name;
	m_code_name[code + size] = name;
	m_codes[name] = code;
}



void orcaCodeContainer::remove_code(const string& name)
{
	map<string, const char*>::iterator mi = m_codes.find(name);
	if (mi == m_codes.end()) {
		return;
	}

	const char* code = mi->second;
	map<const char*, string>::iterator mi1 = m_code_name.lower_bound(code);
	map<const char*, string>::iterator mi2 = m_code_name.upper_bound(code);

	delete[] code;
	m_codes.erase(mi);
	m_code_name.erase(mi1);
	m_code_name.erase(mi2);
}

void orcaCodeContainer::remove_code_tree(const string& name)
{
	map<string, const char*>::iterator mi = m_codes.lower_bound(name);
	for (; mi != m_codes.end(); ++mi) {
		if (!kyString::starts_with(mi->first, name)) {
			break;
		}
		remove_code(mi->first);
	}
}


void orcaCodeContainer::remove_define(const string& name)
{
	map<string, const char*>::iterator mi = m_defines.find(name);
	if (mi == m_defines.end()) {
		return; 
	}

	const char* define = mi->second;
	delete[] define;
	m_defines.erase(mi);
}

void orcaCodeContainer::remove_define_tree(const string& name)
{
	map<string, const char*>::iterator mi = m_defines.lower_bound(name);
	for (; mi != m_defines.end(); ++mi) {
		if (!kyString::starts_with(mi->first, name)) {
			break;
		}
		remove_define(mi->first);
	}
}

const char* orcaCodeContainer::get_base(const char* code, int* size)
{
	const char* ll = code;
	map<const char*, string>::iterator mi = m_code_name.lower_bound(ll);
	string name = mi->second;
	
	if (size) {
		const char *base, *end;
		if (mi->first == ll) {
			base = mi->first;
			++mi;
			end = mi->first;
		}
		else {
			end = mi->first;
			--mi;
			base = mi->first;
		}

		*size = end - base;
	}

	return m_codes[name];
}

string orcaCodeContainer::get_name(const char* code)
{
	const char* ll = code;
	map<const char*, string>::iterator mi = m_code_name.lower_bound(ll);
	return mi->second;
}

const char* orcaCodeContainer::get_addr(const string& name, int* size)
{
	map<string, const char*>::iterator mi = m_codes.find(name);
	if (mi == m_codes.end()) {
		return NULL;
	}

	if (size) {
		*size = get_size(mi->second);
	}
	
	return mi->second;
}

int orcaCodeContainer::get_size(const char* code)
{
	map<const char*, string>::iterator mi1 = m_code_name.lower_bound(code);
	map<const char*, string>::iterator mi2 = m_code_name.upper_bound(code);

	const char* end = mi2->first;
	const char* base = mi1->first;

	return end - base;
}

static set<string> g_consts;

const char* const_strdup(const char* str)
{
	set<string>::iterator it = g_consts.find(str);
	if (it == g_consts.end()) {
		g_consts.insert(str);
		it = g_consts.find(str);
	}

	return (*it).c_str();
}


