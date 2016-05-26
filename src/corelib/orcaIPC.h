/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaIPC.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_IPC
#define _DEF_ORCA_IPC

#include "porting.h"

#include "orcaObject.h"
#include "orcaVM.h"
#include "orcaException.h"

class orcaIPC : public orcaObject 
{
public:
	orcaIPC()
	{
		set_name("ipc");

		insert_static("mutex", new orcaMutex());
		insert_static("cond", new orcaCond());
		insert_static("semaphore", new orcaSemaphore());
	}

	class orcaMutex : public orcaObject 
	{
	public:
		orcaMutex(void* vp) {}
		virtual ~orcaMutex() { }

		orcaObject* v_clone() 
		{
			orcaMutex* mp = new orcaMutex(NULL);
			return mp;
		}

		orcaMutex() 
		{
			set_name("mutex");
			insert_native_function("lock", (object_fp)&orcaMutex::ex_lock);
			insert_native_function("unlock", (object_fp)&orcaMutex::ex_unlock);
			insert_native_function("scope_start", (object_fp)&orcaMutex::ex_lock);
			insert_native_function("scope_end", (object_fp)&orcaMutex::ex_unlock);
		}

		orcaData ex_lock(orcaVM* vm, int n) 
		{
			m_mutex.lock();
			return NIL;
		}

		orcaData ex_unlock(orcaVM* vm, int n) 
		{ 
			m_mutex.unlock();
			return NIL;
		}

		portMutex* handle()
		{
			return &m_mutex;
		}

	private:
		portMutex m_mutex;
	};

	class orcaCond : public orcaObject 
	{
	public:
		orcaCond(void* vp) {}
		virtual ~orcaCond() {}

		orcaCond() 
		{
			set_name("cond");
			insert_native_function("wait", (object_fp)&orcaCond::ex_wait);
			insert_native_function("signal", (object_fp)&orcaCond::ex_signal);
		}

		orcaObject* v_clone() 
		{
			orcaCond* cp = new orcaCond(NULL);
			return cp;
		}

		// true : signaled, false : timeout
		orcaData ex_wait(orcaVM* vm, int n) 
		{
			int msec = -1;

			if (n >= 2) {
				orcaMutex* mp = castobj<orcaMutex>(vm->get_param(1));
				if (mp == NULL) {
					throw orcaException(vm, "orca.param", "mutex type is required");
				}

				msec = vm->get_param(0).Integer();
				return m_cond.wait(mp->handle(), msec);
			}
			else if (n >= 1) {
				orcaData p = vm->get_param(0);
				if (is<TYPE_INT>(p)) {
					msec = p.Integer();
				}
				else {
					orcaMutex* mp = castobj<orcaMutex>(vm->get_param(1));
					if (mp == NULL) {
						throw orcaException(vm, "orca.param", "mutex type is required");
					}
		
					return m_cond.wait(mp->handle());
				}
			}

			return m_cond.wait(msec);
		}

		orcaData ex_signal(orcaVM* vm, int n) 
		{
			m_cond.signal();
			return NIL;
		}


	private:
		portCond m_cond;
	};

	class orcaSemaphore : public orcaObject 
	{
	public:
		orcaSemaphore(void* vp) : m_inited(false) {}
		virtual ~orcaSemaphore() {}

		orcaSemaphore() : m_inited(false) 
		{
			set_name("semaphore");
			insert_native_function("set", (object_fp)&orcaSemaphore::ex_set);
			insert_native_function("inc", (object_fp)&orcaSemaphore::ex_inc);
			insert_native_function("dec", (object_fp)&orcaSemaphore::ex_dec);
			insert_native_function("del", (object_fp)&orcaSemaphore::ex_del);
		}


		orcaObject* v_clone() 
		{
			orcaSemaphore* sp = new orcaSemaphore(NULL);
			return sp;
		}

		orcaData ex_set(orcaVM* vm, int n) 
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

		orcaData ex_inc(orcaVM* vm, int n) 
		{
			if (m_inited) {
				sem_inc(m_sem);
			}

			return NIL;
		}

		orcaData ex_dec(orcaVM* vm, int n) 
		{
			if (m_inited) {
				sem_dec(m_sem);
			}

			return NIL;
		}

		orcaData ex_del(orcaVM* vm, int n) 
		{
			if (m_inited) {
				semctl(m_sem, 0, IPC_RMID, 0);
			}

			return NIL;
		}

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
};

#endif




