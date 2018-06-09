/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMapIter.cpp - map iterator

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#include "orcaMapIter.h"
#include "orcaMap.h"
#include "orcaTuple.h"
#include "orcaException.h"

orcaMapIter::orcaMapIter(orcamap_iterator it, orcaMap* mp, bool flag_ready)
{ 
	set_name("mapiter"); 
	insert_native_function("key", (object_fp)&orcaMapIter::ex_key);
	insert_native_function("value", (object_fp)&orcaMapIter::ex_value);
	insert_native_function("next", (object_fp)&orcaMapIter::ex_next);
	insert_native_function("prev", (object_fp)&orcaMapIter::ex_prev);
	insert_native_function("==", (object_fp)&orcaMapIter::ex_eq);
	insert_native_function("<", (object_fp)&orcaMapIter::ex_lt);
	insert_native_function("erase", (object_fp)&orcaMapIter::ex_erase);

	m_iter = it;

	m_mp = mp;
	m_timestamp = mp->get_timestamp();
	this->flag_ready = flag_ready;
}

bool orcaMapIter::valid()
{
	if (m_timestamp < m_mp->get_timestamp()) {
		return false;
	}

	return true;
}

orcaObject* orcaMapIter::v_clone() 
{
	return new orcaMapIter(m_iter, m_mp, flag_ready);
}

orcaMapIter::~orcaMapIter() { }

orcaData orcaMapIter::ex_key(orcaVM* vm, int n) 
{
	if (flag_ready == false) {
		throw orcaException(vm, "orca.iter.ready", "not ready");
	}

	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	if (m_iter == m_mp->end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return m_iter->first;
}

orcaData orcaMapIter::ex_value(orcaVM* vm, int n) 
{
	if (flag_ready == false) {
		throw orcaException(vm, "orca.iter.ready", "not ready");
	}

	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	if (m_iter == m_mp->end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return m_iter->second;
}

orcaData orcaMapIter::operator()(orcaVM* vm, int n) 
{
	if (flag_ready == false) {
		throw orcaException(vm, "orca.iter.ready", "not ready");
	}

	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	if (m_iter == m_mp->end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (n>0) {
		m_iter->second.rc_dec();
		m_iter->second = vm->get_param(0);
		m_iter->second.rc_inc();
	}

	orcaTuple* tp = new orcaTuple(2);
	tp->update(0, m_iter->first);
	tp->update(1, m_iter->second);

	return tp;
}

orcaData orcaMapIter::ex_next(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	if (m_iter == m_mp->end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (flag_ready == false) {
		flag_ready = true;
		return this;
	}

	++m_iter;

	if (m_iter == m_mp->end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return this;
}

orcaData orcaMapIter::ex_prev(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	if (m_iter == m_mp->begin()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	--m_iter;

	return this;
}

orcaData orcaMapIter::ex_eq(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	orcaMapIter* ip = dynamic_cast<orcaMapIter*>(vm->get_param(0).Object());
	if (ip != NULL) {
		if (flag_ready == false || ip->flag_ready == false) {
			throw orcaException(vm, "orca.iter.ready", "not ready");
		}

		return m_iter == ip->m_iter;
	}

	return NIL;
}

orcaData orcaMapIter::ex_lt(orcaVM* vm, int n) 
{
	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	orcaMapIter* ip = dynamic_cast<orcaMapIter*>(vm->get_param(0).Object());
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

orcaData orcaMapIter::ex_erase(orcaVM* vm, int n) 
{
	if (flag_ready == false) {
		throw orcaException(vm, "orca.iter.ready", "not ready");
	}

	if (valid() == false) {
		throw orcaException(vm, "orca.map", "invalid iterator - timestamp");
	}

	if (m_iter == m_mp->end()) {
		throw orcaException(vm, "orca.map", "invalid iterator");
	}
		
	orcamap_iterator old = m_iter++;
	orcaData key = old->first;
	key.rc_dec();
	old->second.rc_dec();
	m_mp->m_value.erase(old);
	m_mp->inc_timestamp();
	m_timestamp++;

	return this;
}

