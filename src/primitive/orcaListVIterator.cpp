/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaListVIterator.h - list type iterator

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#include "orcaListVIterator.h"
#include "orcaException.h"


orcaListVIterator::orcaListVIterator(orcaListIter it, orcaListIter begin, orcaListIter end, bool flag_ready) : orcaListIterator(NULL)
{
	set_name("iter"); 
	insert_native_function("next", (object_fp)&orcaListVIterator::ex_next);
	insert_native_function("prev", (object_fp)&orcaListVIterator::ex_prev);
	insert_native_function("==", (object_fp)&orcaListVIterator::ex_eq);
	insert_native_function("erase", (object_fp)&orcaListIterator::ex_erase);
	insert_native_function("insert", (object_fp)&orcaListIterator::ex_insert);

	m_iter = it;
	m_begin = begin;
	m_end = end;
	this->flag_ready = flag_ready;
}

orcaObject* orcaListVIterator::v_clone()
{
	orcaListVIterator* lp = new orcaListVIterator(m_iter, m_begin, m_end, flag_ready);
	return lp;
}

orcaListVIterator::~orcaListVIterator() { }

orcaData orcaListVIterator::ex_next(orcaVM* vm, int n)
{
	orcaListIterator::ex_next(vm, n);
	return *m_iter;
}

orcaData orcaListVIterator::ex_prev(orcaVM* vm, int n)
{
	orcaListIterator::ex_prev(vm, n);
	return *m_iter;
}

orcaData orcaListVIterator::ex_eq(orcaVM* vm, int n)
{
	if (is<TYPE_OBJ>(vm->get_param(0))) {
		orcaListVIterator* ip = dynamic_cast<orcaListVIterator*>(vm->get_param(0).Object());
		if (ip != NULL) {
			if (flag_ready == false || ip->flag_ready == false) {
				throw orcaException(vm, "orca.iter.ready", "not ready");
			}

			return m_iter == ip->m_iter;
		}
	}

	return NIL;
}

