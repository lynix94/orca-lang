/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTupleIter.cpp - tuple iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaTupleIter.h"
#include "orcaMap.h"
#include "orcaTuple.h"
#include "orcaException.h"

orcaTupleIter::orcaTupleIter(orcatuple_iterator it, orcaTuple* tp, bool flag_ready)
{ 
	set_name("tupleiter"); 
	insert_native_function("next", (object_fp)&orcaTupleIter::ex_next);
	insert_native_function("prev", (object_fp)&orcaTupleIter::ex_prev);
	insert_native_function("==", (object_fp)&orcaTupleIter::ex_eq);

	m_iter = it;
	m_tp = tp;
	m_timestamp = tp->get_timestamp();

	this->flag_ready = flag_ready;
}

bool orcaTupleIter::valid()
{
	if (m_timestamp < m_tp->get_timestamp()) {
		return false;
	}

	return true;
}

orcaObject* orcaTupleIter::v_clone() 
{
	return new orcaTupleIter(m_iter, m_tp);
}

orcaTupleIter::~orcaTupleIter() { }

orcaData orcaTupleIter::operator()(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.tuple", "invalid iterator - timestamp");
	}

	if (m_iter == m_tp->end()) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	if (n>0) {
		(*m_iter).rc_dec();
		*m_iter = vm->get_param(0);
		(*m_iter).rc_inc();
	}

	return *m_iter;
}

orcaData orcaTupleIter::ex_next(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.tuple", "invalid iterator - timestamp");
	}

	if (m_iter == m_tp->end()) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	if (flag_ready == false) {
		flag_ready = true;
		return this;
	}

	++m_iter;

	if (m_iter == m_tp->end()) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	return this;
}

orcaData orcaTupleIter::ex_prev(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.tuple", "invalid iterator - timestamp");
	}

	if (m_iter == m_tp->begin()) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	--m_iter;

	return this;
}

orcaData orcaTupleIter::ex_eq(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.tuple", "invalid iterator - timestamp");
	}

	orcaTupleIter* ip = dynamic_cast<orcaTupleIter*>(vm->get_param(0).Object());
	if (ip != NULL) {
		return m_iter == ip->m_iter;
	}

	return NIL;
}


