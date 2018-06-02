/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaIPC.h -

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_IPC
#define _DEF_ORCA_IPC

#include "orcaObject.h"
#include "orcaMap.h"

class orcaIPC : public orcaObject 
{
public:
	orcaIPC();
	orcaIPC(void* vp) {}
	virtual ~orcaIPC();
	orcaObject* v_clone();

	orcaData ex_signal(orcaVM* vm, int n);
	orcaData ex_kill(orcaVM* vm, int n);

	map<int, orcaData> handler;
};

class orcaMutex : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaMutex);
	orcaMutex();

	orcaData ex_lock(orcaVM* vm, int n);
	orcaData ex_unlock(orcaVM* vm, int n);
	portMutex* handle();

private:
	portMutex m_mutex;
};

class orcaCond : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaCond);
	orcaCond();

	// true : signaled, false : timeout
	orcaData ex_wait(orcaVM* vm, int n);
	orcaData ex_signal(orcaVM* vm, int n);

private:
	portCond m_cond;
};

class orcaSemaphore : public orcaObject 
{
public:
	orcaSemaphore(void* vp) : m_inited(false) {}
	virtual ~orcaSemaphore() {}
	orcaObject* v_clone() 
	{
		return new orcaSemaphore(NULL);
	}

	orcaSemaphore();

	orcaData ex_set(orcaVM* vm, int n);
	orcaData ex_inc(orcaVM* vm, int n);
	orcaData ex_dec(orcaVM* vm, int n);
	orcaData ex_del(orcaVM* vm, int n);

private:
	sem_t m_sem;
	bool m_inited;
};

#if 0
class orcaShareMemory : public orcaObject 
{
public:
	orcaShareMemory(int key, int size) : m_size(size) {
		m_id = shmget((key_t)key, size, 0666 | IPC_CREAT);
		m_ptr = (char*)shmat(m_id, (void*)0, 0);
	}

	~orcaShareMemory() {
		shm_rm(m_handle, m_ptr)
	}

	char* data() { 
		return (char*)m_ptr; 
	}

	size_t size() { 
		return m_size; 
	}

private:
	shm_t m_handle;
	char* m_ptr;
	size_t m_size;
};
#endif

#endif




