/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectMembersIter.cpp - orca object member iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaObjectMembersIter.h"
#include "orcaException.h"
#include "orcaTuple.h"


orcaObjectMembersIter::orcaObjectMembersIter(orcaObject* src, bool flag_ready)
{
	set_name("iter");
	insert_native_function("next", (object_fp)&orcaObjectMembersIter::ex_next);

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


orcaObjectMembersIter::orcaObjectMembersIter(void* vp) { }

orcaObject* orcaObjectMembersIter::v_clone()
{
	orcaObjectMembersIter* ip = new orcaObjectMembersIter(m_op, 0);
	ip->m_sit = m_sit;
	ip->m_mit = m_mit;
	ip->in_static = in_static;
	return ip;
}

orcaObjectMembersIter::~orcaObjectMembersIter() { }

orcaData orcaObjectMembersIter::operator()(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (flag_ready == false) {
		throw orcaException(vm, "orca.iter.ready", "not ready");
	}

	if (in_static) {
		return m_mit->first;
	}

	if (m_mit == m_op->m_member.end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return m_mit->first;
}

orcaData orcaObjectMembersIter::ex_next(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (flag_ready == false) {
		flag_ready = true;

		if (in_static) {
			return m_sit->first; // at least 1
		}
		else {
			if (m_mit == m_op->m_member.end()) {
				throw orcaException(vm, "orca.iter.end", "out of range");
			}

			return m_mit->first;
		}
	}

	if (in_static) {
		assert(m_op->m_static != NULL);

		if (m_sit != m_op->m_static->end())  {
			++m_sit;
			if (m_sit != m_op->m_static->end()) {
				return m_sit->first;
			}
		}
	
		in_static = false;
		m_mit = m_op->m_member.begin();
		if (m_mit == m_op->m_member.end()) {
			throw orcaException(vm, "orca.iter.end", "out of range");
		}

		return m_mit->first;
	}

	if (m_mit == m_op->m_member.end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}
	++m_mit;
	if (m_mit == m_op->m_member.end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return m_mit->first;
}



