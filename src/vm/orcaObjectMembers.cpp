/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObjectMembers.cpp - base class of all orca object members

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/
#include "porting.h"

#include "orcaObjectMembers.h"
#include "orcaObjectMembersIter.h"
#include "orcaException.h"
#include "orcaGlobal.h"
#include "orcaBoolean.h"
#include "orcaInteger.h"
#include "orcaFloat.h"
#include "orcaString.h"
#include "orcaList.h"

orcaObjectMembers::orcaObjectMembers(orcaData src) : m_src(src) 
{ 
	set_name("members");
	insert_native_function("[]", (object_fp)&orcaObjectMembers::ex_get_at);
	insert_native_function("[]=", (object_fp)&orcaObjectMembers::ex_set_at);
	insert_native_function("string", (object_fp)&orcaObjectMembers::ex_string);
	insert_native_function("has_key", (object_fp)&orcaObjectMembers::ex_has_key);
	insert_native_function("erase_key", (object_fp)&orcaObjectMembers::ex_erase_key);
	insert_native_function("keys", (object_fp)&orcaObjectMembers::ex_keys);
	insert_native_function("values", (object_fp)&orcaObjectMembers::ex_values);
	insert_native_function("begin", (object_fp)&orcaObjectMembers::ex_begin);
	insert_native_function("end", (object_fp)&orcaObjectMembers::ex_end);
	insert_native_function("last", (object_fp)&orcaObjectMembers::ex_last);
	insert_native_function("find", (object_fp)&orcaObjectMembers::ex_find);

	is_static = false;

	m_src.rc_inc();

	switch(m_src.get_type())
	{
	case TYPE_INT:
		m_internal = &g_integer;
		break;
	case TYPE_BIGNUM:
		m_internal = &g_big_integer;
		break;
	case TYPE_REAL:
		m_internal = &g_float;
		break;
	case TYPE_BOOL:
		m_internal = &g_boolean;
		break;
	case TYPE_STR:
		m_internal = &g_string;
		break;
	default:
		m_internal = NULL;
		break;
	}
}

orcaObjectMembers::orcaObjectMembers(void* vp)
{
	is_static = false;
}

orcaObject* orcaObjectMembers::v_clone()
{
	orcaObjectMembers* op = new orcaObjectMembers((void*)NULL);
	op->is_static = is_static;
	op->m_src = m_src;

	m_src.rc_inc();
	return op;
}

orcaObjectMembers::~orcaObjectMembers()
{
	m_src.rc_dec();
}

orcaData orcaObjectMembers::ex_get_at(orcaVM* vm, int n)
{
	const char* name = vm->get_param(0).String().c_str();	
	orcaData out;

	orcaObject* op = NULL;
	if (isinternal(m_src)) 
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();
	
	if (op == NULL) return NIL;

	if (is_static && !op->has_static_member(name, out)) 
		return NIL;

	if (op->has_member(name, out)) {
		if (is<TYPE_INTERNAL>(out)) {
			switch(m_src.get_type())
			{
			case TYPE_INT:
				out.internal().owner.i = m_src.i();
				break;
			case TYPE_BIGNUM:
				out.internal().owner.bo = m_src.bo();
				break;
			case TYPE_REAL:
				out.internal().owner.r = m_src.r();
				break;
			case TYPE_BOOL:
				out.internal().owner.i = m_src.i();
				break;
			case TYPE_STR:
				out.internal().owner.so = m_src.so();
				break;
			default:
				break;
			}
		}

		return out;
	}

	return NIL;
}

orcaData orcaObjectMembers::ex_set_at(orcaVM* vm, int n)
{
	const char* name = vm->get_param(0).String().c_str();	
	orcaData data = vm->get_param(1);
	orcaData out;

	if (!is<TYPE_OBJ>(m_src))
		throw orcaException(vm, "orca.type", "cannot set internal function");

	orcaObject* op = m_src.o();
	if (is_static && !op->has_static_member(name, out)) {
		if (op->has_member(name)) { // has normal member
			op->remove_member(name);
		}

		op->insert_static(const_strdup(name), data);
		return this;
	}

	if (op->has_member(name)) {
		op->update_member(name, data);
	}
	else {
		op->insert_member(const_strdup(name), data);
	}

	return this;
}

orcaData orcaObjectMembers::ex_string(orcaVM* vm, int n)
{
	cp_map<orcaData>::Type::iterator mi;

	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();

    string str = "{ ";
	if (op == NULL) {
		str += " }";
		return str;
	}

	if (op->m_static) {
		mi = op->m_static->begin();
		while(mi!=op->m_static->end()) {
			str += "'";
			str += mi->first;
			str += "'";

			str += ":";

			if (is<TYPE_STR>(mi->second)) str += "'";
			(mi->second).string_(vm, str);
			if (is<TYPE_STR>(mi->second)) str += "'";

			++mi;
			if (mi!=op->m_static->end()) str+= ",";
		}
	}
	if (is_static) {
		str += " }";
		return str;
	}

	if (op->m_static && 
		op->m_static->size() > 0 &&  
		m_member.size() > 0) 
	{
		str += ",";
	}
  
	mi = op->m_member.begin();
	while(mi!=op->m_member.end()) {
		str += "'";
		str += mi->first;
		str += "'";

		str += ":";

		if (is<TYPE_STR>(mi->second)) str += "'";
		(mi->second).string_(vm, str);
		if (is<TYPE_STR>(mi->second)) str += "'";

		++mi;
		if (mi!=op->m_member.end()) str+= ",";
	}

    str += " }";

	return str;
}

orcaData orcaObjectMembers::ex_has_key(orcaVM* vm, int n)
{
	const char* name = vm->get_param(0).String().c_str();	

	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();

	if (op == NULL) return false;

	if (is_static) {
		orcaData out;
		return op->has_static_member(name, out);
	}

	return op->has_member(name);
}

orcaData orcaObjectMembers::ex_erase_key(orcaVM* vm, int n)
{
	const char* name = vm->get_param(0).String().c_str();	

	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();
		
	if (op == NULL)
		throw orcaException(vm, "orca.param", string("Object has no member ") + name);

	if (is_static) {
		orcaData out;
		if (op->has_static_member(name, out) == false) {
			return this;
		}
	}

	op->remove_member(name);
	return this;
}

orcaData orcaObjectMembers::ex_keys(orcaVM* vm, int n)
{
	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();

	orcaList* lp = new orcaList();
	if (op == NULL) return lp;

	cp_map<orcaData>::Type::iterator it;
	if (op->m_static) {
		it = op->m_static->begin();
		for (; it != op->m_static->end(); ++it) {
			lp->push_back(it->first);
		}
	}

	it = op->m_member.begin();
	for (; it != op->m_member.end(); ++it) {
		lp->push_back(it->first);
	}
	
	return lp;
}

orcaData orcaObjectMembers::ex_values(orcaVM* vm, int n)
{
	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();
		
	orcaList* lp = new orcaList();
	if (op == NULL) return lp;

	cp_map<orcaData>::Type::iterator it;
	if (op->m_static) {
		it = op->m_static->begin();
		for (; it != op->m_static->end(); ++it) {
			lp->push_back(it->second);
		}
	}

	it = op->m_member.begin();
	for (; it != op->m_member.end(); ++it) {
		lp->push_back(it->second);
	}
	
	return lp;
}


orcaData orcaObjectMembers::ex_begin(orcaVM* vm, int n)
{
	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();
		
	orcaObjectMembersIter* ip = new orcaObjectMembersIter(op, 0);
	return ip;
}


orcaData orcaObjectMembers::ex_end(orcaVM* vm, int n)
{
	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();
		
	orcaObjectMembersIter* ip = new orcaObjectMembersIter(op, INT_MIN);
	return ip;
}


orcaData orcaObjectMembers::ex_last(orcaVM* vm, int n)
{
	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();
		
	orcaObjectMembersIter* ip = new orcaObjectMembersIter(op, -1);
	return ip;
}

orcaData orcaObjectMembers::ex_find(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param();

	string name = vm->get_param(0).String();

	orcaObject* op = NULL;
	if (isinternal(m_src))
		op = m_internal;
	else if (is<TYPE_OBJ>(m_src))
		op = m_src.o();
		
	orcaObjectMembersIter* ip = new orcaObjectMembersIter(op, name);
	return ip;
}


