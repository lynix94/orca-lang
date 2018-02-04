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

using namespace std;

pthread_mutex_t g_rc_mutex;
pthread_key_t g_thread_context;
thread_pool g_thread_pool;
orcaCodeContainer g_codes;

struct init_once
{
	init_once()
	{
		pthread_mutex_init(&g_rc_mutex, NULL);
		pthread_key_create(&g_thread_context, NULL);
		g_timer.start();
	}

	~init_once()
	{
		pthread_mutex_destroy(&g_rc_mutex);
		pthread_key_delete(g_thread_context);
		g_timer.quit();
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


bool thread_pool::signal_restart(thread_arg_t arg)
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

void thread_pool::work(thread_arg_t arg)
{
	PRINT1("thread added, tid:%d\n", (int)arg.tid);
	pthread_t tid = arg.tid;
	thread_pool_t* pool = new thread_pool_t;
	m_map[tid] = pool;
	m_map[tid]->running = true;
	m_map[tid]->arg = arg;

	orcaVM* vm = new orcaVM;
	vm->init();

	do {
		arg = get_arg(tid);
		orcaVM* vm_main = arg.vm_main;
	
		vm->m_module = vm_main->m_module;
		vm->m_curr = vm_main->m_curr;
		vm_main->m_local->duplicate(vm->m_local);
		
		if (arg.iter != NULL) {
			vm->m_stack->push(arg.iter);
			vm->m_stack->push(arg.per);
			vm->m_stack->push(arg.is_iterator);
		}

		set_start(tid);
		try {
			vm->exec_code(arg.code, arg.offset);
			vm->m_local->decrease();
		}
		catch (orcaException& e) {
			printf("uncaugted exception: %s - %s\n", e.who(), e.what());
			cout << e.m_stack_trace << endl;
			vm->m_stack->dump();
			vm->m_local->dump();
			exit(-1);
		}

		if (is_exit()) {
			set_stop(tid);
			vm->cleanup();
			delete vm;
			return;
		}

		set_stop(tid);

		if (is_exit()) {
			vm->cleanup();
			delete vm;
			return;
		}
	} while (true);

	vm->cleanup();
	delete vm;
	return;
}

void thread_pool::join_all()
{
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
	m_mutex_pool.lock();
	m_map[tid]->running = true;
	m_cond_start.signal();
	inc_run(tid);
	m_mutex_pool.unlock();

}

void thread_pool::set_stop(pthread_t tid)
{
	PRINT1("thread stop, tid:%d\n", (int)tid);
	m_mutex_pool.lock();
	dec_run(tid);
	m_cond_done.signal();
	m_mutex_pool.unlock();

	m_map[tid]->mutex.lock();
	m_map[tid]->running = false;
	m_map[tid]->cond.wait(&m_map[tid]->mutex);
	m_map[tid]->mutex.unlock();
}

thread_arg_t thread_pool::get_arg(pthread_t tid)
{
	return m_map[tid]->arg;
}

bool thread_pool::is_exit() 
{
	return m_quit;
}

void thread_pool::inc_run(pthread_t tid)
{
	if (m_map[tid]->arg.run_count) {
		(*m_map[tid]->arg.run_count)++;
	}
}

void thread_pool::dec_run(pthread_t tid)
{
	if (m_map[tid]->arg.run_count) {
		(*m_map[tid]->arg.run_count)--;
	}
}




orcaCodeContainer::orcaCodeContainer() {}
orcaCodeContainer::~orcaCodeContainer()
{
	name_code_t::iterator mi = m_code.begin();
	for(; mi!=m_code.end(); ++mi) {
		delete[] mi->second;
	}

	mi = m_define.begin();
	for(; mi!=m_define.end(); ++mi) {
		delete[] mi->second;
	}
}

char* orcaCodeContainer::new_define(int size)
{
	string name = string("$__define__") + boost::lexical_cast<string>(m_define.size());
	return new_define(size, name);
}

char* orcaCodeContainer::new_define(int size, const string& name)
{
	if (m_define.find(name) != m_define.end()) {
		return NULL;
	}

	char* define = new char[size];
	m_define[name] = define;
	return define;
}

char* orcaCodeContainer::new_code(int size)
{
	string name = string("$__code__") + boost::lexical_cast<string>(m_code.size());
	return new_code(size, name);
}

char* orcaCodeContainer::new_code(int size, const string& name)
{
	if (m_code.find(name) != m_code.end()) {
		return NULL;
	}

	char* code = new char[size];
	m_code_name[code] = name;
	m_code_name[code + size] = name;
	m_code[name] = code;
	return code;
}

void orcaCodeContainer::remove_code(const string& name)
{
	name_code_t::iterator mi = m_code.find(name);
	if (mi == m_code.end()) {
		return;
	}

	const char* code = mi->second;
	code_name_t::iterator mi1 = m_code_name.lower_bound(code);
	code_name_t::iterator mi2 = m_code_name.upper_bound(code);

	delete[] code;
	m_code.erase(mi);
	m_code_name.erase(mi1);
	m_code_name.erase(mi2);
	return;
}

void orcaCodeContainer::remove_define(const string& name)
{
	name_code_t::iterator mi = m_define.find(name);
	if (mi == m_define.end()) {
		return;
	}

	const char* define = mi->second;
	delete[] define;
	m_define.erase(mi);
	return;
}

const char* orcaCodeContainer::get_base(const char* code, int* size)
{
	const char* ll = code;
	code_name_t::iterator mi = m_code_name.lower_bound(ll);
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

	return m_code[name];
}

string orcaCodeContainer::get_name(const char* code)
{
	const char* ll = code;
	code_name_t::iterator mi = m_code_name.lower_bound(ll);
	return mi->second;
}

const char* orcaCodeContainer::get_addr(string name, int* size)
{
	name_code_t::iterator mi = m_code.find(name);
	if (mi == m_code.end()) {
		return NULL;
	}

	if (size) {
		*size = get_size(mi->second);
	}
	
	return mi->second;
}

int orcaCodeContainer::get_size(const char* code)
{
	code_name_t::iterator mi1 = m_code_name.lower_bound(code);
	code_name_t::iterator mi2 = m_code_name.upper_bound(code);

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


