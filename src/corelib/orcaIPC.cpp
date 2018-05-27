/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaIPC.cpp -

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#include <sys/types.h>
#include <signal.h>


#include "porting.h"

#include "orcaObject.h"
#include "orcaVM.h"
#include "orcaException.h"
#include "orcaIPC.h"



orcaIPC* g_ipc;

orcaIPC::orcaIPC()
{
	set_name("ipc");

	insert_static("mutex", new orcaMutex());
	insert_static("cond", new orcaCond());
	insert_static("semaphore", new orcaSemaphore());
	insert_static_native_function("signal", (object_fp)&orcaIPC::ex_signal);
	insert_static_native_function("kill", (object_fp)&orcaIPC::ex_kill);

	insert_static("SIG_DFL", 0);
	insert_static("SIG_IGN", 1);

	insert_static("SIGHUP", 1);
	insert_static("SIGINT", 2);
	insert_static("SIGQUIT",3);
	insert_static("SIGILL", 4);
	insert_static("SIGTRAP", 5);
	insert_static("SIGABRT", 6);
	insert_static("SIGIOT", 6);
	insert_static("SIGBUS", 7);
	insert_static("SIGFPE", 8);
	insert_static("SIGKILL", 9);
	insert_static("SIGUSR1", 10);
	insert_static("SIGSEGV", 11);
	insert_static("SIGUSR2", 12);
	insert_static("SIGPIPE", 13);
	insert_static("SIGALRM", 14);
	insert_static("SIGTERM", 15);
	insert_static("SIGSTKFLT", 16);
	insert_static("SIGCHLD", 17);
	insert_static("SIGCONT", 18);
	insert_static("SIGSTOP", 19);
	insert_static("SIGTSTP", 20);
	insert_static("SIGTTIN", 21);
	insert_static("SIGTTOU", 22);
	insert_static("SIGURG", 23);
	insert_static("SIGXCPU", 24);
	insert_static("SIGXFSZ", 25);
	insert_static("SIGVTALRM", 26);
	insert_static("SIGPROF", 27);
	insert_static("SIGWINCH", 28);
	insert_static("SIGIO", 29);
	insert_static("SIGPOLL", 29);
	insert_static("SIGPWR", 30);
	insert_static("SIGSYS", 31);
	insert_static("SIGUNUSED", 31);

	g_ipc = this;
}

void signal_handler(int signum)
{
	orcaIPC* ipc = g_ipc;
	map<int, orcaData>::iterator it = ipc->handler.find(signum);
	if (it == ipc->handler.end()) {
		return;
	}
	
	orcaVM* vm = get_current_vm();
	vm->push_param(it->second);
	vm->push_param(signum);
	vm->call(1);
	vm->m_stack->pop();
}

orcaIPC::~orcaIPC()
{
	map<int, orcaData>::iterator it = handler.begin();
	for(; it != handler.end(); ++it) {
		it->second.rc_dec();
	}
}

orcaData orcaIPC::ex_signal(orcaVM* vm, int n) 
{
	if (n < 2) vm->need_param();
	int signum = vm->get_param(0).Integer();
	orcaData func = vm->get_param(1);

	handler[signum] = func;
	func.rc_inc();

	if (is<TYPE_INT>(func)) {
		signal(signum, (__sighandler_t)(long long)func.i()); // SIG_IGN, SIG_DFL
	}
	else {
		signal(signum, signal_handler);
	}
	return func; 
}

orcaData orcaIPC::ex_kill(orcaVM* vm, int n) 
{
	if (n < 2) vm->need_param();
	return kill(vm->get_param(0).Integer(), vm->get_param(1).Integer());
}

orcaObject* orcaIPC::v_clone()
{
	orcaIPC* ip = new orcaIPC(NULL);
	return ip;
}


orcaObject* orcaMutex::v_clone() 
{
	orcaMutex* mp = new orcaMutex(NULL);
	return mp;
}

orcaMutex::orcaMutex() 
{
	set_name("mutex");
	insert_native_function("lock", (object_fp)&orcaMutex::ex_lock);
	insert_native_function("unlock", (object_fp)&orcaMutex::ex_unlock);
	insert_native_function("{", (object_fp)&orcaMutex::ex_lock);
	insert_native_function("}", (object_fp)&orcaMutex::ex_unlock);
}

orcaData orcaMutex::ex_lock(orcaVM* vm, int n) 
{
	m_mutex.lock();
	return NIL;
}

orcaData orcaMutex::ex_unlock(orcaVM* vm, int n) 
{ 
	m_mutex.unlock();
	return NIL;
}

portMutex* orcaMutex::handle()
{
	return &m_mutex;
}


orcaCond::orcaCond() 
{
	set_name("cond");
	insert_native_function("wait", (object_fp)&orcaCond::ex_wait);
	insert_native_function("signal", (object_fp)&orcaCond::ex_signal);
}

orcaObject* orcaCond::v_clone() 
{
	orcaCond* cp = new orcaCond(NULL);
	return cp;
}

// true : signaled, false : timeout
orcaData orcaCond::ex_wait(orcaVM* vm, int n) 
{
	double tmout = -1;
	orcaMutex* mp = NULL;

	orcaData d = vm->get_param(0);
	if (n >= 2) {
		mp = castobj<orcaMutex>(vm->get_param(1));
		if (mp == NULL) {
			throw orcaException(vm, "orca.param", "mutex type is required");
		}
	}

	switch(d.get_type())
	{
	case TYPE_INT:
	case TYPE_REAL:
	case TYPE_BIGNUM:
		tmout = d.Double();
		break;

	default:
		if (mp != NULL) { // 2 param case(wait(&mutex, tmout)) : should be number
			throw orcaException(NULL, "orca.type", "number type needed");
		}

		// wait(&mutex)
		mp = castobj<orcaMutex>(d);
		if (mp == NULL) {
			throw orcaException(vm, "orca.param", "mutex type is required");
		}

		return m_cond.wait(mp->handle());
	}

	return m_cond.wait(tmout * (1000*1000*1000));
}

orcaData orcaCond::ex_signal(orcaVM* vm, int n) 
{
	m_cond.signal();
	return NIL;
}


orcaSemaphore::orcaSemaphore() : m_inited(false) 
{
	set_name("semaphore");
	insert_native_function("set", (object_fp)&orcaSemaphore::ex_set);
	insert_native_function("inc", (object_fp)&orcaSemaphore::ex_inc);
	insert_native_function("dec", (object_fp)&orcaSemaphore::ex_dec);
	insert_native_function("del", (object_fp)&orcaSemaphore::ex_del);
}


orcaObject* orcaSemaphore::v_clone() 
{
	orcaSemaphore* sp = new orcaSemaphore(NULL);
	return sp;
}

orcaData orcaSemaphore::ex_set(orcaVM* vm, int n) 
{
	int max;
	if (n < 1) vm->need_param();

	if (n < 2) {
		max = 1;
	}
	else {
		max = vm->get_param(1).Integer();
	}

	int key = vm->get_param(0).Integer();
	
	if (m_inited) {
		semctl(m_sem, 0, IPC_RMID, 0);
	}

	m_sem = semget(key, max, IPC_CREAT | 0660);
	m_inited = true;
	return NIL;
}

orcaData orcaSemaphore::ex_inc(orcaVM* vm, int n) 
{
	if (m_inited) {
		sem_inc(m_sem);
	}

	return NIL;
}

orcaData orcaSemaphore::ex_dec(orcaVM* vm, int n) 
{
	if (m_inited) {
		sem_dec(m_sem);
	}

	return NIL;
}

orcaData orcaSemaphore::ex_del(orcaVM* vm, int n) 
{
	if (m_inited) {
		semctl(m_sem, 0, IPC_RMID, 0);
	}

	return NIL;
}

