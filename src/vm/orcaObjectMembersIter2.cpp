/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectMembersIter2.cpp - orca object member iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaObjectMembersIter2.h"
#include "orcaException.h"
#include "orcaTuple.h"


orcaObjectMembersIter2::orcaObjectMembersIter2(orcaObject* src, bool flag_ready)
{
	set_name("iter2");
	insert_native_function("next", (object_fp)&orcaObjectMembersIter2::ex_next);

	m_op = src;
	if (m_op == NULL) return;

	m_mit = m_op->m_member.begin();
	in_static = false;
	
	if (m_op->m_static && !m_op->m_static->empty()) {
		m_sit = m_op->m_static->begin();
		in_static = true;
	}

	this->flag_ready = flag_ready;
}


orcaObjectMembersIter2::orcaObjectMembersIter2(void* vp) { }

orcaObject* orcaObjectMembersIter2::v_clone()
{
	orcaObjectMembersIter2* ip = new orcaObjectMembersIter2(m_op, 0);
	ip->m_sit = m_sit;
	ip->m_mit = m_mit;
	ip->in_static = in_static;
	return ip;
}

orcaObjectMembersIter2::~orcaObjectMembersIter2() { }

orcaTuple* orcaObjectMembersIter2::value(orcaVM *vm)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (in_static) {
		orcaTuple* tp = new orcaTuple(2);
		tp->update(0, m_sit->first);
		tp->update(1, m_sit->second);
		return tp;
	}

	if (m_mit == m_op->m_member.end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	orcaTuple* tp = new orcaTuple(2);
	tp->update(0, m_mit->first);
	tp->update(1, m_mit->second);

	return tp;
}

orcaData orcaObjectMembersIter2::ex_next(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (flag_ready == false) {
		flag_ready = true;
		return value(vm);
	}

	if (in_static) {
		assert(m_op->m_static != NULL);

		if (m_sit != m_op->m_static->end())  {
			++m_sit;
			if (m_sit != m_op->m_static->end()) {
				return value(vm);
			}
		}
	
		in_static = false;
		m_mit = m_op->m_member.begin();
		if (m_mit == m_op->m_member.end()) {
			throw orcaException(vm, "orca.iter.end", "out of range");
		}

		return value(vm);
	}

	if (m_mit == m_op->m_member.end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}
	++m_mit;
	if (m_mit == m_op->m_member.end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return value(vm);
}



