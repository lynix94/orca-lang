/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMapVIter.cpp - map iterator

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#include "orcaMapVIter.h"
#include "orcaMap.h"
#include "orcaTuple.h"
#include "orcaException.h"

orcaMapVIter::orcaMapVIter(orcamap_iterator it, orcaMap* mp, bool flag_ready) : orcaMapIter(NULL)
{ 
	set_name("iter"); 
	insert_native_function("key", (object_fp)&orcaMapIter::ex_key);
	insert_native_function("value", (object_fp)&orcaMapIter::ex_value);
	insert_native_function("next", (object_fp)&orcaMapVIter::ex_next);
	insert_native_function("prev", (object_fp)&orcaMapVIter::ex_prev);
	insert_native_function("==", (object_fp)&orcaMapVIter::ex_eq);
	insert_native_function("<", (object_fp)&orcaMapVIter::ex_lt);
	insert_native_function("erase", (object_fp)&orcaMapIter::ex_erase);

	m_iter = it;

	m_mp = mp;
	m_timestamp = mp->get_timestamp();
	this->flag_ready = flag_ready;
}

orcaObject* orcaMapVIter::v_clone() 
{
	return new orcaMapVIter(m_iter, m_mp, flag_ready);
}

orcaMapVIter::~orcaMapVIter() { }

orcaData orcaMapVIter::ex_next(orcaVM* vm, int n) 
{
	orcaMapIter::ex_next(vm, n);
	return m_iter->first;
}

orcaData orcaMapVIter::ex_prev(orcaVM* vm, int n) 
{
	orcaMapIter::ex_prev(vm, n);
	return m_iter->first;
}

orcaData orcaMapVIter::ex_eq(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	orcaMapVIter* ip = dynamic_cast<orcaMapVIter*>(vm->get_param(0).Object());
	if (ip != NULL) {
		if (flag_ready == false || ip->flag_ready == false) {
			throw orcaException(vm, "orca.iter.ready", "not ready");
		}

		return m_iter == ip->m_iter;
	}

	return NIL;
}

orcaData orcaMapVIter::ex_lt(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	orcaMapVIter* ip = dynamic_cast<orcaMapVIter*>(vm->get_param(0).Object());
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

