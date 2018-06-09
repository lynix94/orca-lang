/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectMembersIter.cpp - orca object member iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaObjectMembersIter.h"
#include "orcaException.h"
#include "orcaTuple.h"


orcaObjectMembersIter::orcaObjectMembersIter(orcaObject* src, int pos)
{
	set_name("MEMBERS_ITERATOR");
	insert_native_function("first", (object_fp)&orcaObjectMembersIter::ex_first);
	insert_native_function("second", (object_fp)&orcaObjectMembersIter::ex_second);
	insert_native_function("next", (object_fp)&orcaObjectMembersIter::ex_next);
	insert_native_function("prev", (object_fp)&orcaObjectMembersIter::ex_prev);
	insert_native_function("==", (object_fp)&orcaObjectMembersIter::ex_eq);
	insert_native_function("<", (object_fp)&orcaObjectMembersIter::ex_lt);
	insert_native_function("erase", (object_fp)&orcaObjectMembersIter::ex_erase);

	m_op = src;
	if (m_op == NULL) return;

	if (pos == 0) {
		m_mit = m_op->m_member.begin();
		in_static = false;
		
		if (m_op->m_static) {
			m_sit = m_op->m_static->begin();
			in_static = true;
		}
	}
	else if (pos == -1) {
		if (m_op->m_member.empty()) {
			in_static = true;
			if (m_op->m_static) {
				m_sit = m_op->m_static->end();
				--m_sit;
			}
		}
		else {
			in_static = false;
			m_mit = m_op->m_member.end();
			--m_mit;
		}
	}
	else if (pos == INT_MIN) {
		m_mit = m_op->m_member.end();
		in_static = false;
	}
	else {
		assert(0);
	}
}


orcaObjectMembersIter::orcaObjectMembersIter(orcaObject* src, string& name)
{
	set_name("members_iterator");
	insert_native_function("first", (object_fp)&orcaObjectMembersIter::ex_first);
	insert_native_function("second", (object_fp)&orcaObjectMembersIter::ex_second);
	insert_native_function("next", (object_fp)&orcaObjectMembersIter::ex_next);
	insert_native_function("prev", (object_fp)&orcaObjectMembersIter::ex_prev);
	insert_native_function("==", (object_fp)&orcaObjectMembersIter::ex_eq);
	insert_native_function("<", (object_fp)&orcaObjectMembersIter::ex_lt);
	insert_native_function("erase", (object_fp)&orcaObjectMembersIter::ex_erase);

	m_op = src;
	if (m_op == NULL) return;

	if (m_op->m_static) {
		m_sit = m_op->m_static->find(name.c_str());
		if (m_sit != m_op->m_static->end()) {
			in_static = true;
			return;
		}
	}

	in_static = false;
	m_mit = m_op->m_member.find(name.c_str());
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
		throw orcaException(vm, "orca.iter", "out of range");
	}

	if (in_static) {
		orcaTuple* tp = new orcaTuple(2);
		tp->update(0, m_sit->first);
		tp->update(1, m_sit->second);
		return tp;
	}

	if (m_mit == m_op->m_member.end()) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	orcaTuple* tp = new orcaTuple(2);
	tp->update(0, m_mit->first);
	tp->update(1, m_mit->second);

	return tp;
}

orcaData orcaObjectMembersIter::ex_first(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	cp_map<orcaData>::Type::iterator it;
	cp_map<orcaData>::Type::iterator end;
	if (in_static) {
		it = m_sit;
		end = m_op->m_static->end();
	}
	else {
		it = m_mit;
		end = m_op->m_member.end();
	}

	if (it == end) {
		throw orcaException(vm, "orca.iter", "out of range");
	}
	
	return it->first;
}

orcaData orcaObjectMembersIter::ex_second(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	cp_map<orcaData>::Type::iterator it;
	cp_map<orcaData>::Type::iterator end;
	if (in_static) {
		it = m_sit;
		end = m_op->m_static->end();
	}
	else {
		it = m_mit;
		end = m_op->m_member.end();
	}

	if (it == end) {
		throw orcaException(vm, "orca.iter", "out of range");
	}
	
	return it->second;
}

orcaData orcaObjectMembersIter::ex_next(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	if (in_static) {
		assert(m_op->m_static != NULL);

		if (m_sit != m_op->m_static->end())  {
			++m_sit;
			if (m_sit != m_op->m_static->end()) {
				return this;
			}
		}
	
		in_static = false;
		m_mit = m_op->m_member.begin();
		if (m_mit == m_op->m_member.end()) {
			throw orcaException(vm, "orca.iter", "out of range");
		}

		return this;
	}

	if (m_mit == m_op->m_member.end()) {
		throw orcaException(vm, "orca.iter", "out of range");
	}
	++m_mit;
	if (m_mit == m_op->m_member.end()) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	return this;
}

orcaData orcaObjectMembersIter::ex_prev(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	if (!in_static) {
		if (m_mit != m_op->m_member.begin()) {
			--m_mit;
			return this;
		}

		if (!m_op->m_static) {
			throw orcaException(vm, "orca.iter", "out of range");
		}

		in_static = true;
		m_sit = m_op->m_static->end();
	}

	if (!m_op->m_static) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	if (m_sit == m_op->m_static->begin()) {
		throw orcaException(vm, "orca.iter", "out of range");
	}
	--m_sit;
	
	return this;
}

orcaData orcaObjectMembersIter::ex_eq(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	if (n<1) vm->need_param();
	orcaObjectMembersIter* ip = dynamic_cast<orcaObjectMembersIter*>(vm->get_param(0).Object());
	if (ip == NULL) {
		throw orcaException(vm, "orca.param", "object member iterator required");
	}

	if (ip->m_op != m_op) { // different object (not type but instance)
		return false;
	}

	if (in_static) {
		assert(m_op->m_static != NULL);
		return m_sit == ip->m_sit;
	}

	return m_mit == ip->m_mit;
}


orcaData orcaObjectMembersIter::ex_lt(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	if (n<1) vm->need_param();
	orcaObjectMembersIter* ip = dynamic_cast<orcaObjectMembersIter*>(vm->get_param(0).Object());
	if (ip == NULL) {
		throw orcaException(vm, "orca.param", "object member iterator required");
	}

	if (ip->m_op != m_op) { // different object (not type but instance)
		return false;
	}

	if (in_static) {
		assert(m_op->m_static != NULL);
		return string(m_sit->first) < string(ip->m_sit->first);
	}

	return string(m_mit->first) < string(ip->m_mit->first);
}

orcaData orcaObjectMembersIter::ex_erase(orcaVM* vm, int n)
{
	if (m_op == NULL) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	string name;
	if (in_static) {
		assert(m_op->m_static != NULL);
		if (m_sit == m_op->m_static->end()) {
			throw orcaException(vm, "orca.iter", "out of range");
		}
	
		name = m_sit->first;
	}
	else {
		if (m_mit == m_op->m_member.end()) {
			throw orcaException(vm, "orca.iter", "out of range");
		}

		name = m_mit->first;
	}

	m_op->remove_member(name.c_str());
	return this;
}

