/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

#include "orcaThread.h"

orcaThread::orcaThread() 
{
	set_name("thread");

	insert_native_function("run", (object_fp)&orcaThread::ex_run);
	insert_native_function("join", (object_fp)&orcaThread::ex_join);
}

orcaData orcaThread::ex_run(orcaVM* vm, int n) 
{
	if (n<1) {
		return NIL;
	}

	orcaThread* tp = new orcaThread();

	tp->m_arg = vm->get_param(0).Object();
	tp->m_tid = 0;

	for(int i=1; i<n; i++) {
		tp->m_param.push_back(vm->get_param(i));
	}

	if(pthread_create(&tp->m_tid, NULL, orcaThread::entryPoint, tp) < 0) {
		printf("Thread Start Error, ThreadID: %d\n", (int)tp->m_tid);
		return NIL;
	}

	m_remains.insert(tp->m_tid);
	return tp;
}

orcaData orcaThread::ex_join(orcaVM* vm, int n) 
{
	long long status = 0;
	pthread_join(m_tid, (void**)&status);
	m_remains.erase(m_remains.find(m_tid));

	return (int)status;
}

void orcaThread::execute(orcaObject* arg) {
	m_vm.init();
	set_current_vm(&m_vm);

	m_vm.m_module = g_root;
	m_vm.m_curr = g_root;

	m_vm.m_local->increase(1024);
	m_vm.push_stack(arg);
	arg->rc_inc();

	for (int i=0; i<m_param.size(); i++) {
		m_vm.push_stack(m_param[i]);
	}

	try {
		m_vm.call(m_param.size());
	}
	catch(orcaException& e) {
		printf("uncaugted exception in thread: %s %s\n", e.who(), e.what());
		cout << e.m_stack_trace << endl;

		arg->rc_dec();
		m_vm.cleanup();
		return;
	}

	arg->rc_dec();
	m_vm.cleanup();
}

void orcaThread::join_remains()
{
	long long status = 0;
	set<pthread_t>::iterator it = m_remains.begin();
	for (; it != m_remains.end(); ++it) {
		pthread_join((*it), (void**)&status);
	}
}

