/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMapVIter2.cpp - map iterator

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#include "orcaMapVIter2.h"
#include "orcaMap.h"
#include "orcaTuple.h"
#include "orcaException.h"

orcaMapVIter2::orcaMapVIter2(orcamap_iterator it, orcaMap* mp, bool flag_ready) : orcaMapIter(NULL)
{ 
	set_name("iter"); 
	insert_native_function("key", (object_fp)&orcaMapIter::ex_key);
	insert_native_function("value", (object_fp)&orcaMapIter::ex_value);
	insert_native_function("next", (object_fp)&orcaMapVIter2::ex_next);
	insert_native_function("prev", (object_fp)&orcaMapVIter2::ex_prev);
	insert_native_function("==", (object_fp)&orcaMapVIter2::ex_eq);
	insert_native_function("<", (object_fp)&orcaMapVIter2::ex_lt);
	insert_native_function("erase", (object_fp)&orcaMapIter::ex_erase);

	m_iter = it;

	m_mp = mp;
	m_timestamp = mp->get_timestamp();
	this->flag_ready = flag_ready;
}

orcaObject* orcaMapVIter2::v_clone() 
{
	return new orcaMapVIter2(m_iter, m_mp, flag_ready);
}

orcaMapVIter2::~orcaMapVIter2() { }

orcaData orcaMapVIter2::ex_next(orcaVM* vm, int n) 
{
	orcaMapIter::ex_next(vm, n);
	orcaTuple* tp = new orcaTuple(2);
	tp->update(0, m_iter->first);
	tp->update(1, m_iter->second);
	return tp;
}

orcaData orcaMapVIter2::ex_prev(orcaVM* vm, int n) 
{
	orcaMapIter::ex_prev(vm, n);
	orcaTuple* tp = new orcaTuple(2);
	tp->update(0, m_iter->first);
	tp->update(1, m_iter->second);
	return tp;
}

orcaData orcaMapVIter2::ex_eq(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	orcaMapVIter2* ip = dynamic_cast<orcaMapVIter2*>(vm->get_param(0).Object());
	if (ip != NULL) {
		if (flag_ready == false || ip->flag_ready == false) {
			throw orcaException(vm, "orca.iter.ready", "not ready");
		}

		return m_iter == ip->m_iter;
	}

	return NIL;
}

orcaData orcaMapVIter2::ex_lt(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	orcaMapVIter2* ip = dynamic_cast<orcaMapVIter2*>(vm->get_param(0).Object());
	if (ip != NULL) {
		if (flag_ready == false || ip->flag_ready == false) {
			throw orcaException(vm, "orca.iter.ready", "not ready");
		}

		orcaData k1 = m_iter->first;
		orcaData k2 = ip->m_iter->first;
		return k1.operator_lt(vm, k2);
	}

	return NIL;
}

