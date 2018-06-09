/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTupleIter.h - tuple iterator

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_TUPLEITER
#define _DEF_ORCA_TUPLEITER

#include "orcaTuple.h"


class LIBORCA_API orcaTupleIter : public orcaObject
{
public:
	orcaTupleIter(orcatuple_iterator begin, orcaTuple* tp, bool flag_ready = true);
	orcaTupleIter(void*) {};
	orcaObject* v_clone();
	virtual ~orcaTupleIter();

	virtual orcaData operator()(orcaVM* vm, int n);
	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_prev(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);
	orcatuple_iterator& get_iter()
	{
		return m_iter;
	}

protected:
	bool valid();

	bool flag_ready;
	orcatuple_iterator m_iter;
	orcaTuple* m_tp;

	int m_timestamp;
};

#endif

