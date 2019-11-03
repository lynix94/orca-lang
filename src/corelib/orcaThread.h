/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaThread.h - 

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_THREAD
#define _DEF_ORCA_THREAD

#include <iostream>
#include <set>

#include "porting.h"

#ifdef WINDOWS

#else
#include <unistd.h>
#include <pthread.h>
#endif


#include "orcaObject.h"
#include "orcaLocal.h"
#include "orcaRoot.h"
#include "orcaException.h"

using namespace std;

class LIBORCA_API orcaThread : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaThread);

	orcaThread();
	orcaData ex_run(orcaVM* vm, int n);
	orcaData ex_join(orcaVM* vm, int n);
	orcaData ex_stop(orcaVM* vm, int n);

public:
	orcaObject* m_arg;
	pthread_t m_tid;

	static THREAD_RET entryPoint(void* pthis) {
		((orcaThread*)pthis)->execute( ((orcaThread*)pthis)->m_arg );
		return 0;
	}

	virtual void execute(orcaObject* arg);

private:
	orcaVM m_vm;
	vector<orcaData> m_param;

	static set<pthread_t> m_remains;

public:
	static void join_remains();
};


#endif

