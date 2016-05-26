/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectParents.cpp - orca object orcaObjectParents

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaObjectParents.h"
#include "orcaObjectParentsIter.h"
#include "orcaException.h"

orcaObjectParents::orcaObjectParents(orcaData src) : m_src(src) 
{ 
	set_name("orcaObjectParents");
	insert_native_function("[]", (object_fp)&orcaObjectParents::ex_get_at);
	insert_native_function("[]=", (object_fp)&orcaObjectParents::ex_set_at);
	insert_native_function("string", (object_fp)&orcaObjectParents::ex_string);
	insert_native_function("push_back", (object_fp)&orcaObjectParents::ex_push_back);
	insert_native_function("pop_back", (object_fp)&orcaObjectParents::ex_pop_back);
	insert_native_function("push_front", (object_fp)&orcaObjectParents::ex_push_front);
	insert_native_function("pop_front", (object_fp)&orcaObjectParents::ex_pop_front);

	insert_native_function("begin", (object_fp)&orcaObjectParents::ex_begin);
	insert_native_function("end", (object_fp)&orcaObjectParents::ex_end);
	insert_native_function("last", (object_fp)&orcaObjectParents::ex_last);
	insert_native_function("find", (object_fp)&orcaObjectParents::ex_find);
	m_src.rc_inc();
}

orcaObjectParents::orcaObjectParents(void* vp) { }

orcaObject* orcaObjectParents::v_clone()
{
	orcaObjectParents* op = new orcaObjectParents((void*)NULL);
	op->m_src = m_src;

	m_src.rc_inc();
	return op;
}

orcaObjectParents::~orcaObjectParents()
{
	m_src.rc_dec();
}


orcaData orcaObjectParents::ex_get_at(orcaVM* vm, int n)
{
	int idx = vm->get_param(0).Integer();

	if (is<TYPE_OBJ>(m_src)) {
		orcaObject* op = m_src.o();
		
		if (op->m_parent) {
			int size = op->m_parent->size();
			if (idx > size)
				throw orcaException(vm, "orca.index", "out of range");

			if (idx < 0) idx += size;

			if (idx < 0)
				throw orcaException(vm, "orca.index", "out of range");

			list<orcaObject*>::iterator it = op->m_parent->begin();
			for (int i=0; i<idx; i++) it++;

			return *it;
		}
	}

	return NIL;
}

orcaData orcaObjectParents::ex_set_at(orcaVM* vm, int n)
{
	int idx = vm->get_param(0).Integer();
	orcaData data = vm->get_param(1);
	orcaData out;

	if (is<TYPE_OBJ>(m_src)) {
		orcaObject* op = m_src.o();
		
		if (op->m_parent) {
			int size = op->m_parent->size();
			if (idx > size)
				throw orcaException(vm, "orca.index", "out of range");

			if (idx < 0) idx += size;

			if (idx < 0)
				throw orcaException(vm, "orca.index", "out of range");

			list<orcaObject*>::iterator it = op->m_parent->begin();
			for (int i=0; i<idx; i++) it++;
			(*it)->rc_dec();
			(*it) = data.Object();
			(*it)->rc_inc();

			return this;
		}

		throw orcaException(vm, "orca.index", "out of range");
	}

	return NIL;
}

orcaData orcaObjectParents::ex_string(orcaVM* vm, int n)
{
	string str = "[ ";

	if (is<TYPE_OBJ>(m_src)) {
		orcaObject* op = m_src.o();
		
		if (op->m_parent) {
			list<orcaObject*>::iterator li = op->m_parent->begin();
			while(li!=op->m_parent->end()) {
				(*li)->string_(vm, str);
				++li;
				if (li!=op->m_parent->end()) str+= ",";
			}
		}
	}

	str += " ]";
	return str;
}

orcaData orcaObjectParents::ex_push_back(orcaVM* vm, int n)
{
	if (n<1) vm->need_param();

	if (is<TYPE_OBJ>(m_src)) {
		orcaObject* op = m_src.o();
		
		if (!op->m_parent)
			op->m_parent = new list<orcaObject*>;

		orcaObject* pp = vm->get_param(0).Object();
		pp->m_base = op;
		op->m_parent->push_back(pp);
	}

	return this;
}

orcaData orcaObjectParents::ex_pop_back(orcaVM* vm, int n)
{
	if (is<TYPE_OBJ>(m_src)) {
		orcaObject* op = m_src.o();
		
		if (op->m_parent && op->m_parent->size() > 0) {
			(*(--op->m_parent->end()))->m_base = NULL;
			op->m_parent->pop_back();
		}
	}

	return this;
}

orcaData orcaObjectParents::ex_push_front(orcaVM* vm, int n)
{
	if (n<1) vm->need_param();

	if (is<TYPE_OBJ>(m_src)) {
		orcaObject* op = m_src.o();
		
		if (!op->m_parent)
			op->m_parent = new list<orcaObject*>;

		op->m_parent->push_front(vm->get_param(0).Object());
	}

	return this;
}

orcaData orcaObjectParents::ex_pop_front(orcaVM* vm, int n)
{
	if (is<TYPE_OBJ>(m_src)) {
		orcaObject* op = m_src.o();
		
		if (op->m_parent && op->m_parent->size() > 0)
			op->m_parent->pop_front();
	}

	return this;
}

orcaData orcaObjectParents::ex_begin(orcaVM* vm, int n)
{
	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();

	orcaObjectParentsIter* ip = new orcaObjectParentsIter(op, 0);
	return ip;
}


orcaData orcaObjectParents::ex_end(orcaVM* vm, int n)
{
	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();

	orcaObjectParentsIter* ip = new orcaObjectParentsIter(op, INT_MIN);
	return ip;
}


orcaData orcaObjectParents::ex_last(orcaVM* vm, int n)
{
	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();

	orcaObjectParentsIter* ip = new orcaObjectParentsIter(op, -1);
	return ip;
}

orcaData orcaObjectParents::ex_find(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param();

	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();

	orcaObjectParentsIter* ip = new orcaObjectParentsIter(op, vm->get_param(0));
	return ip;
}


