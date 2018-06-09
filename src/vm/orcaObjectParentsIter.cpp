/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectParentsIter.cpp - orca object parents iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaObjectParentsIter.h"
#include "orcaException.h"
#include "orcaTuple.h"
#include "orcaList.h"
#include "orcaMap.h"


orcaObjectParentsIter::orcaObjectParentsIter(orcaObject* src, bool flag_ready)
{
	set_name("iter");
	insert_native_function("next", (object_fp)&orcaObjectParentsIter::ex_next);
	insert_native_function("erase", (object_fp)&orcaObjectParentsIter::ex_erase);

	m_op = src;
	if (m_op == NULL || m_op->m_parent == NULL) return;

	m_it = m_op->m_parent->begin();
	this->flag_ready = flag_ready;
}


struct same_type : public binary_function<orcaObject*, orcaObject*, bool>
{
	bool operator()(orcaObject* o1, orcaObject* o2) const
	{
		if (dynamic_cast<orcaList*>(o1) && dynamic_cast<orcaList*>(o2)) {
			return true;
		}
		else if (dynamic_cast<orcaTuple*>(o1) && dynamic_cast<orcaTuple*>(o2)) {
			return true;
		}
		else if (dynamic_cast<orcaMap*>(o1) && dynamic_cast<orcaMap*>(o2)) {
			return true;
		}

		return o1->get_original() == o2->get_original();
	}
};

orcaObjectParentsIter::orcaObjectParentsIter(void* vp) { }

orcaObject* orcaObjectParentsIter::v_clone()
{
	orcaObjectParentsIter* ip = new orcaObjectParentsIter(m_op, 0);
	ip->m_it = m_it;
	return ip;
}

orcaObjectParentsIter::~orcaObjectParentsIter() { }

orcaData orcaObjectParentsIter::operator()(orcaVM* vm, int n)
{
	if (m_op == NULL || m_op->m_parent == NULL) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (m_it == m_op->m_parent->end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return *m_it;
}

orcaData orcaObjectParentsIter::ex_next(orcaVM* vm, int n)
{
	if (m_op == NULL || m_op->m_parent == NULL) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (flag_ready == false) {
		if (m_it == m_op->m_parent->end()) {
			throw orcaException(vm, "orca.iter.end", "out of range");
		}

		flag_ready = true;
		return *m_it;
	}

	if (m_it == m_op->m_parent->end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	++m_it;

	if (m_it == m_op->m_parent->end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return *m_it;
}

orcaData orcaObjectParentsIter::ex_erase(orcaVM* vm, int n)
{
	if (m_op == NULL || m_op->m_parent == NULL) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (m_it == m_op->m_parent->end()) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}
	
	m_op->remove_parent(*m_it);
	return this;
}

