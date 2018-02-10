/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaQueue.h - queue

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_QUEUE
#define _DEF_ORCA_QUEUE

#include "orcaObject.h"

class LIBORCA_API orcaQueue : public orcaObject
{
public:
	orcaQueue();
	orcaQueue(void* vp) {}
	orcaObject* v_clone()
	{
		return new orcaQueue();
	}

	virtual ~orcaQueue();

	// member function
	orcaData ex_init(orcaVM* vm, int n);
	orcaData ex_size(orcaVM* vm, int n);
	orcaData ex_cap(orcaVM* vm, int n);
	orcaData ex_channel_out(orcaVM* vm, int n);
	orcaData ex_channel_in(orcaVM* vm, int n);
	orcaData ex_push(orcaVM* vm, int n);
	orcaData ex_pop(orcaVM* vm, int n);

	virtual void string_(orcaVM* vm, string& str);
	void dump(); 

protected:
	list<orcaData> m_value;
	int m_cap;

	portMutex mutex;
	portCond putable_cond;
	portCond getable_cond;
};

#endif

