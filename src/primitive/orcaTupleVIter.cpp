/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTupleVIter.cpp - tuple iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaTupleVIter.h"
#include "orcaMap.h"
#include "orcaTuple.h"
#include "orcaException.h"

orcaTupleVIter::orcaTupleVIter(orcatuple_iterator it, orcaTuple* tp, bool flag_ready) : orcaTupleIter(NULL)
{ 
	set_name("tupleiter"); 
	insert_native_function("next", (object_fp)&orcaTupleVIter::ex_next);
	insert_native_function("prev", (object_fp)&orcaTupleVIter::ex_prev);
	insert_native_function("==", (object_fp)&orcaTupleVIter::ex_eq);

	m_iter = it;
	m_tp = tp;
	m_timestamp = tp->get_timestamp();

	this->flag_ready = flag_ready;
}


orcaObject* orcaTupleVIter::v_clone() 
{
	return new orcaTupleVIter(m_iter, m_tp);
}

orcaTupleVIter::~orcaTupleVIter() { }

orcaData orcaTupleVIter::ex_next(orcaVM* vm, int n) 
{
	orcaTupleIter::ex_next(vm, n);
	return *m_iter;
}

orcaData orcaTupleVIter::ex_prev(orcaVM* vm, int n) 
{
	orcaTupleIter::ex_prev(vm, n);
	return *m_iter;
}

orcaData orcaTupleVIter::ex_eq(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.tuple", "invalid iterator - timestamp");
	}

	orcaTupleVIter* ip = dynamic_cast<orcaTupleVIter*>(vm->get_param(0).Object());
	if (ip != NULL) {
		return m_iter == ip->m_iter;
	}

	return NIL;
}


