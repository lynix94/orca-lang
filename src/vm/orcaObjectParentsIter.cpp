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


orcaObjectParentsIter::orcaObjectParentsIter(orcaObject* src, int pos)
{
	set_name("parents_iterator");
	insert_native_function("next", (object_fp)&orcaObjectParentsIter::ex_next);
//	insert_native_function("prev", (object_fp)&orcaObjectParentsIter::ex_prev);
//	insert_native_function("==", (object_fp)&orcaObjectParentsIter::ex_eq);
	insert_native_function("erase", (object_fp)&orcaObjectParentsIter::ex_erase);

	m_op = src;
	if (m_op == NULL || m_op->m_parent == NULL) return;

	if (pos == 0) {
		m_it = m_op->m_parent->begin();
	}
/*
	else if (pos == -1) {
		m_it = m_op->m_parent->end();
		--m_it;
	}
	else if (pos == INT_MIN) {
		m_it = m_op->m_parent->end();
	}
*/
	else {
		assert(0);
	}
}


struct same_type : public binary_function<orcaObject*, orcaObject*, bool>
{
	bool operator()(orcaObject* o1, orcaObject* o2) const
	{
		if (dynamic_cast<orcaList*>(o1) && 
			dynamic_cast<orcaList*>(o2))
		{
			return true;
		}
		else if (dynamic_cast<orcaTuple*>(o1) && 
			dynamic_cast<orcaTuple*>(o2))
		{
			return true;
		}
		else if (dynamic_cast<orcaMap*>(o1) && 
			dynamic_cast<orcaMap*>(o2))
		{
			return true;
		}

		return o1->get_original() == o2->get_original();
	}
};

/*
orcaObjectParentsIter::orcaObjectParentsIter(orcaObject* src, orcaData p)
{
	set_name("parents_iterator");
	insert_native_function("next", (object_fp)&orcaObjectParentsIter::ex_next);
	insert_native_function("prev", (object_fp)&orcaObjectParentsIter::ex_prev);
	insert_native_function("==", (object_fp)&orcaObjectParentsIter::ex_eq);
	insert_native_function("erase", (object_fp)&orcaObjectParentsIter::ex_erase);

	m_op = src;
	if (m_op == NULL || m_op->m_parent == NULL) return;

	if (!is<TYPE_OBJ>(p)) {
		m_it = m_op->m_parent->end();
		return;
	}

	orcaObject* op = p.o();

	m_it = find_if(m_op->m_parent->begin(), m_op->m_parent->end(), bind1st(same_type(), op));
}
*/

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
	if (m_op == NULL || m_op->m_parent == NULL)
		throw orcaException(vm, "orca.iter", "out of range");

	if (m_it == m_op->m_parent->end())
		throw orcaException(vm, "orca.iter", "out of range");

	return *m_it;
}

orcaData orcaObjectParentsIter::ex_next(orcaVM* vm, int n)
{
	if (m_op == NULL || m_op->m_parent == NULL)
		throw orcaException(vm, "orca.iter", "out of range");

	if (m_it == m_op->m_parent->end()) 
		throw orcaException(vm, "orca.iter", "out of range");
	++m_it;
	if (m_it == m_op->m_parent->end()) 
		throw orcaException(vm, "orca.iter", "out of range");

	return this;
}

/*
orcaData orcaObjectParentsIter::ex_prev(orcaVM* vm, int n)
{
	if (m_op == NULL || m_op->m_parent == NULL)
		throw orcaException(vm, "orca.iter", "out of range");

	if (m_it == m_op->m_parent->begin()) 
		throw orcaException(vm, "orca.iter", "out of range");
	--m_it;
	return this;
}

orcaData orcaObjectParentsIter::ex_eq(orcaVM* vm, int n)
{
	if (m_op == NULL || m_op->m_parent == NULL)
		throw orcaException(vm, "orca.iter", "out of range");

	if (n<1) vm->need_param();
	orcaObjectParentsIter* ip = 
		dynamic_cast<orcaObjectParentsIter*>(vm->get_param(0).Object());
	if (ip == NULL) {
		throw orcaException(vm, "orca.param", "object parents iterator required");
	}

	if (ip->m_op != m_op) { // different object (not type but instance)
		return false;
	}

	return m_it == ip->m_it;
}
*/


orcaData orcaObjectParentsIter::ex_erase(orcaVM* vm, int n)
{
	if (m_op == NULL || m_op->m_parent == NULL)
		throw orcaException(vm, "orca.iter", "out of range");

	if (m_it == m_op->m_parent->end()) 
		throw orcaException(vm, "orca.iter", "out of range");
	
	m_op->remove_parent(*m_it);
	return this;
}

