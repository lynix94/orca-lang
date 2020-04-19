/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaListIter.h - list type iterator

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#include "orcaListIterator.h"
#include "orcaException.h"



orcaListIterator::orcaListIterator(orcaListIter it, orcaListIter begin, orcaListIter end, bool flag_ready, orcaObject* source)
{
	set_name("iter"); 
	insert_native_function("next", (object_fp)&orcaListIterator::ex_next);
	insert_native_function("prev", (object_fp)&orcaListIterator::ex_prev);
	insert_native_function("==", (object_fp)&orcaListIterator::ex_eq);
	insert_native_function("erase", (object_fp)&orcaListIterator::ex_erase);
	insert_native_function("insert", (object_fp)&orcaListIterator::ex_insert);

	m_iter = it;
	m_begin = begin;
	m_end = end;
	this->flag_ready = flag_ready;
	this->source = source;
	this->source->rc_inc();
}

orcaObject* orcaListIterator::v_clone()
{
	orcaListIterator* lp = new orcaListIterator(m_iter, m_begin, m_end, flag_ready, source);

	return lp;
}

orcaListIterator::~orcaListIterator()
{
	source->rc_dec();
}

orcaData orcaListIterator::operator()(orcaVM* vm, int n)
{
	if (flag_ready == false) {
		throw orcaException(vm, "orca.iter.ready", "not ready");
	}

	if (m_iter == m_end) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (n>0) {
		(*m_iter).rc_dec();
		*m_iter = vm->get_param(0);
		(*m_iter).rc_inc();
	}

	return *m_iter;
}

orcaData orcaListIterator::ex_next(orcaVM* vm, int n)
{
	if (m_iter == m_end) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	// in case of iter()
	if (flag_ready == false) {
		flag_ready = true;
		return *m_iter;
	}

	++m_iter;

	if (m_iter == m_end) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return *m_iter;
}

orcaData orcaListIterator::ex_prev(orcaVM* vm, int n)
{
	if (m_iter == m_begin) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	--m_iter;

	return *m_iter;
}

orcaData orcaListIterator::ex_eq(orcaVM* vm, int n)
{
	if (is<TYPE_OBJ>(vm->get_param(0))) {
		orcaListIterator* ip = dynamic_cast<orcaListIterator*>(vm->get_param(0).Object());

		if (ip != NULL) {
			if (flag_ready == false || ip->flag_ready == false) {
				throw orcaException(vm, "orca.iter.ready", "not ready");
			}

			return m_iter == ip->m_iter;
		}
	}

	return NIL;
}

orcaData orcaListIterator::ex_erase(orcaVM* vm, int n)
{
	if (flag_ready == false) {
		throw orcaException(vm, "orca.iter.ready", "not ready");
	}

	m_iter.raw_erase();
	return this;
}

orcaData orcaListIterator::ex_insert(orcaVM* vm, int n)
{
	if (flag_ready == false) {
		throw orcaException(vm, "orca.iter.ready", "not ready");
	}

	if (n < 1) vm->need_param();
	
	for (int i=0; i<n; i++) {
		m_iter.raw_insert(vm->get_param(i));
	}

	return this;
}

