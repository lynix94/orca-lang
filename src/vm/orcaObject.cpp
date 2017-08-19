/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObject.cpp - base class of all orca object

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaObject.h"
#include "orcaData.h"
#include "orcaStack.h"
#include "orcaException.h"
#include "orca_opcode.h"
#include "orcaTuple.h"
#include "parserParser.h"
#include "orcaMap.h"
#include "orcaGlobal.h"
#include "orcaList.h"
#include "orcaMap.h"
#include "orcaTuple.h"

#include "orcaVM.h"
#include "orcaRoot.h"

// for members
#include "orcaInteger.h"
#include "orcaFloat.h"
#include "orcaString.h"
#include "orcaBoolean.h"
#include "orcaObjectMembers.h"
#include "orcaObjectParents.h"

using namespace std;

char buff[1024];

orcaObject::orcaObject() 
{ 
	m_static = NULL;
	m_name = (char*)"None";
	m_code = NULL;
	m_owner = NULL;
	m_base = NULL;
	m_parent = NULL;
	m_original = NULL;
	m_flag = 0;
}

orcaObject::orcaObject(orcaObject* o)
{
	m_name = o->m_name;
	m_static = o->m_static;
	m_code = o->m_code;
	m_owner = NULL;
	m_base = NULL;
	m_parent = NULL;
	m_original = this;
	m_flag = 0;
}

orcaObject::~orcaObject()
{
	cp_map<orcaData>::Type::iterator mi = m_member.begin();
	for(; mi!=m_member.end(); ++mi) {
		mi->second.rc_dec();
	}

	if (m_parent) {
		list<orcaObject*>::iterator vi = m_parent->begin();
		for(; vi != m_parent->end(); ++vi) {
			(*vi)->rc_dec();
		}

		delete m_parent;
	}

	if (m_original == this && m_static != NULL) {
		cp_map<orcaData>::Type::iterator mi = m_static->begin();
		for (; mi!=m_static->end(); ++mi) {
			mi->second.rc_dec();
		}
		delete m_static;
		m_static = NULL;
	}

	if (m_flag & BIT_DEFINE_NAME_CHANGED) {
		free((void*)m_name);
	}
}

void orcaObject::make_original()
{
	m_original = this;
}

orcaObject* orcaObject::v_clone()
{
	return new orcaObject();
}


orcaObject* orcaObject::clone(orcaObject* owner) 
{
	orcaObject* no = v_clone();

	no->m_name = this->m_name;
	no->m_static = this->m_static;
	no->m_code = this->m_code;
	no->m_parent = NULL;
	no->m_owner = owner;
	no->m_base = NULL;
	no->m_original = this->m_original;

	cp_map<orcaData>::Type::iterator it = m_member.begin();
	for(; it!=m_member.end(); ++it) {
		no->m_member[it->first] = it->second.clone(no);
		no->m_member[it->first].rc_inc();
	}

	if (m_parent) {
		list<orcaObject*>::iterator it = m_parent->begin();
		for(; it!=m_parent->end(); ++it) {
			no->make_super(*it);
		}
	}

	return no;
}

orcaObject* orcaObject::make_super(orcaObject* o) 
{
	if (m_parent == NULL) {
		m_parent = new list<orcaObject*>;
	}

	orcaObject *pp = o->clone();
	pp->m_base = this;
	pp->rc_inc();
	m_parent->push_back(pp);

	return pp;
}

orcaData orcaObject::operator()(orcaVM* vm, int param_n) 
{
	if (m_code == NULL) {
		return this;
	}
	
	int as = get_argument_size();
	if (param_n > as) {
		if (get_flag_argv()) {	// if object use argv
			orcaTuple* tp = new orcaTuple(param_n-as);

			for (int i=0; i<param_n-as; i++) {
				tp->update(i, vm->get_param(as + i));
				vm->set_param(as + i, NIL);
			}

			vm->set_param(as, tp);
		}
		else {					// if not, remove them
			for (int i=0; i<param_n-as; i++) {
				vm->set_param(as + i, NIL);
			}
		}
	}

	orcaObject* curr_back = vm->m_curr;

	vm->m_curr = this;
	vm->exec_code(m_code);
	vm->m_curr = curr_back;
	return vm->m_stack->pop();
}

bool orcaObject::insert_member(const char* name, orcaData d) 
{ 
	PRINT3("\t\t  insert %s(%s) in %s\n", name, d.dump(buff), m_name);

	m_member[name] = d;
	d.rc_inc();

	if (is<TYPE_OBJ>(d)) {
		m_member[name].o()->m_owner = this;
	}

	return true;
}

bool orcaObject::remove_member(const char* name)
{ 
	PRINT2("\t\t  remove %s from %s\n", name, m_name);

	cp_map<orcaData>::Type::iterator mi;
	if (m_static) {
		mi = m_static->find(name);
		if (mi != m_static->end()) {
			mi->second.rc_dec();
			m_static->erase(mi);
			return true;
		}
	}
	
	mi = m_member.find(name);
	if (mi != m_member.end()) {
		mi->second.rc_dec();
		m_member.erase(mi);
		return true;
	}

	return false;
}

bool orcaObject::insert_static(const char* name, orcaData d) 
{ 
	PRINT3("\t\t  insert static %s(%s) in %s\n", name, d.dump(buff), m_name);

	if (m_static == NULL) {
		m_static = new cp_map<orcaData>::Type;
	}

	(*m_static)[name] = d;
	d.rc_inc();

	if (is<TYPE_OBJ>(d)) {
		(*m_static)[name].o()->m_owner = this;
	}

	return true;
}

bool orcaObject::insert_native_function(const char* name, object_fp func) 
{
	return insert_member(name, orcaData(this, func, name));
}

bool orcaObject::insert_static_native_function(const char* name, object_fp func) 
{
	return insert_static(name, orcaData(this, func, name));
}

bool orcaObject::insert_parent(orcaObject* o)
{ 
	PRINT2("\t\t  insert (%s) in %s as parent\n", o->dump(buff), m_name);

	orcaObject* op = o->clone(m_owner);
	if (m_parent == NULL) {
		m_parent = new list<orcaObject*>;
	}

	m_parent->push_back(op);
	op->rc_inc();
	return true;
}

bool orcaObject::insert_parent_runtime(orcaObject* o)
{ 
	PRINT2("\t\t  insert (%s) in %s as parent\n", o->dump(buff), m_name);

	if (m_parent == NULL) {
		m_parent = new list<orcaObject*>;
	}

	m_parent->push_back(o);
	o->rc_inc();
	return true;
}

bool orcaObject::remove_parent(orcaObject* o)
{ 
	PRINT3("\t\t  remove parent %p (%s) from %s\n", o, o->dump(buff), m_name);

	if (m_parent == NULL) {
		return false;
	}

	list<orcaObject*>::iterator vi;
	vi = m_parent->begin();

	for (;vi != m_parent->end(); ++vi) {
		if ((*vi) == o) {
			(*vi)->rc_dec();
			m_parent->erase(vi);
			return true;
		}
	}

	return false;
}

orcaData orcaObject::get_member_last(const char* name) 
{ 
	return get_member_sub(name, true);
}

orcaData orcaObject::get_member(const char* name) 
{ 
	return get_member_sub(name, false);
}

orcaData orcaObject::operator_string(orcaVM* vm, orcaData& p)
{
	string str;
	string_(vm, str);
	return str;
}

orcaData orcaObject::get_member_sub(const char* name, bool last) 
{ 
	PRINT3("\t\t  get %s from %s, (parent: %p)\n", name, dump(buff), m_parent);
	cp_map<orcaData>::Type::iterator mi;

	// first, find at static
	if (m_static) {
		mi = m_static->find(name);
		if (mi != m_static->end())
			return mi->second;
	}

	// second, find at member
	mi = m_member.find(name);
	if (mi != m_member.end())
		return mi->second;

	// try virtual member
	if (strcmp(name, "string") == 0) {
		orcaData d(this, (object_fp)&orcaObject::operator_string, "string");
		return d;
	}
	else if (strcmp(name, "TYPE") == 0) {
		orcaData d;
		d.type_set(this);
		return d;
	}
	else if (strcmp(name, "TYPENAME") == 0) {
		string str;
		if (isobj<orcaList>(this)) str = "list";
		else if (isobj<orcaMap>(this)) str = "map";
		else if (isobj<orcaTuple>(this)) str = "tuple";
		else {
			str = "object "; 
			str += get_name();
		}

		return str;
	}
	else if (strcmp(name, "ID") == 0) {
		return (long long)this;
	}
	else if (strcmp(name, "RC") == 0) {
		return get_rc();
	}
	else if (strcmp(name, "NAME") == 0) {
		return get_name();
	}
	else if (strcmp(name, "MEMBERS") == 0) {
		return new orcaObjectMembers(orcaData(this));
	}
	else if (strcmp(name, "STATIC_MEMBERS") == 0) {
		orcaObjectMembers* mp = new orcaObjectMembers(orcaData(this));
		mp->set_static();
		return mp;
	}
	else if (strcmp(name, "PARENTS") == 0) {
		return new orcaObjectParents(orcaData(this));
	}
	else if (strcmp(name, "ORIGINAL") == 0) {
		return get_original();
	}


	// finally... find at parent
	if (m_parent) {
		list<orcaObject*>::iterator it = m_parent->begin();
		for(; it!=m_parent->end(); ++it) {
			try {
				return (*it)->get_member(name);
			}
			catch(...) {
				continue;
			}
		}
	}

	// last, try operator_get
	// TODO : study this reference
	string str_name = name;
	orcaData d(str_name);
	d.rc_inc();

	orcaVM* vm = get_current_vm();

	orcaData ret = NIL;
	if (last == true) {
		ret = operator_get_last(vm, d);
	}
	else {
		ret = operator_get(vm, d);
	}

	d.rc_dec();

	if (!is<TYPE_NIL>(ret)) {
		return ret;
	}

	throw orcaException(vm, "orca.name", string("member ")
						+ name + " not found");

	return NIL;
}

bool orcaObject::has_static_member(const char* name, orcaData& out) 
{ 
	PRINT2("\t\t  get %s from %s\n", name, dump(buff));
	cp_map<orcaData>::Type::iterator mi;
	if (!m_static) {
		return false;
	}

	mi = m_static->find(name);

	// first, find at static
	if (mi == m_static->end()) {
		return false;
	}

    out = mi->second;
	return true;
}

bool orcaObject::has_parent(orcaObject* op)
{ 
	if (m_parent == NULL) {
		return false;
	}

	list<orcaObject*>::iterator vi;
	vi = m_parent->begin();

	for (;vi != m_parent->end(); ++vi) {
		if ((*vi) == op)
			return true;
	}

	return false;
}

bool orcaObject::has_member(const char* name) 
{ 
	PRINT2("\t\t  get %s from %s\n", name, dump(buff));
	orcaData out;
	return has_member(name, out);
}


bool orcaObject::has_member(const char* name, orcaData& out) 
{ 
	PRINT2("\t\t  get %s from %s\n", name, dump(buff));

	// first, find at static
	if (has_static_member(name, out) == true) {
		return true;
	}
	
	// second, find at member
	cp_map<orcaData>::Type::iterator mi;
	mi = m_member.find(name);
	if (mi != m_member.end()) {
		out = mi->second;
		return true;
	}

	// last, find at parents
	if (m_parent) {
		list<orcaObject*>::iterator it = m_parent->begin();
		for(; it!=m_parent->end(); ++it) {
			if ((*it)->has_member(name, out)) {
				return true;
			}
		}
	}

	return false;
}

orcaData orcaObject::update_member(const char* name, orcaData d) 
{
	cp_map<orcaData>::Type::iterator mi;
	if (m_static) {
		mi = m_static->find(name);
	}

	// first, find at static
	if (m_static == NULL || mi == m_static->end()) {

		// second, find at member
		mi = m_member.find(name);
		if (mi == m_member.end()) {
			// try virtual member
			if (strcmp(name, "string") == 0 
				|| (strcmp(name, "TYPE") == 0) 
				|| (strcmp(name, "TYPENAME") == 0)
				|| (strcmp(name, "ID") == 0)
				|| (strcmp(name, "RC") == 0)
				|| (strcmp(name, "MEMBERS") == 0)
				|| (strcmp(name, "STATIC_MEMBERS") == 0)
				|| (strcmp(name, "PARENTS") == 0)
				|| (strcmp(name, "ORIGINAL") == 0))
			{
				throw orcaException(get_current_vm(), "orca.name",
					string("member ") + name + " is read only");
			}
			else if (strcmp(name, "NAME") == 0) {
				m_name = strdup(d.String().c_str());
				m_flag |= BIT_DEFINE_NAME_CHANGED;
				return d;
			}

			// finally... find at parent
			if (m_parent) {
				list<orcaObject*>::iterator it = m_parent->begin();
				for(; it!=m_parent->end(); ++it) {
					try {
						return (*it)->update_member(name, d);
					}
					catch(...) {
						continue;
					}
				}
			}

			// last, try operator_set
			orcaVM* vm = get_current_vm();
			orcaData ret = operator_set(vm, name, d);
			if (!is<TYPE_NIL>(ret)) {
				return ret;
			}

			throw orcaException(vm, "orca.name", string("member ") +
								name + " not found");
		}
	}

	mi->second.rc_dec();
	mi->second = d;
	mi->second.rc_inc();

	return mi->second;
}

void orcaObject::string_(orcaVM* vm, string& str) 
{ 
	orcaData d;
	if (has_member("string", d)) {
		vm->push_stack(d);
		vm->call(0);
		str += vm->m_stack->pop().String();
	}
	else {
		char buff[32];
		sprintf(buff, "<%p>", this);
		str += m_name;
		str += " ";
		str += buff;
	}
}

void orcaObject::dump() 
{ 
	printf("%s\n", dump(buff));
}

string orcaObject::dump_str()
{
	return dump(buff);
}

char* orcaObject::dump(char* buff) 
{ 
	sprintf(buff, "object (%s)", m_name?m_name:"(null)");
	return buff;
}

void orcaObject::member_dump()
{
	printf("# %s Member Variables dump\n", dump(buff));

	cp_map<orcaData>::Type::iterator it = m_member.begin();
	for(; it!=m_member.end(); ++it) {
		printf("  [%s] ", it->first);
		it->second.dump();
	}

	printf("  parent: %p\n", m_parent);
}

void orcaObject::set_name(const char* name)
{
	m_name = name;
	make_original();
}

const char* orcaObject::get_name()
{
	return m_name;
}

string orcaObject::get_path_name()
{
	string name = m_name;
	orcaObject* curr = m_owner;

	while (curr) {
		if (curr == g_root) break;
		name = string(curr->get_name()) + "." + name; 
		curr = curr->m_owner;
	}

	return name;
}

const char* orcaObject::get_code()
{
	return m_code;
}

void orcaObject::set_code(const char* cp)
{
	m_code = cp;
}

orcaData orcaObject::operator_mul(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("*", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}

	return NIL;
}

orcaData orcaObject::operator_add(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("+", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);

		return vm->m_stack->pop();
	}

	return NIL;
}

orcaData orcaObject::operator_sub(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("-", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}

	return NIL;
}

orcaData orcaObject::operator_sub_rev(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("-rev", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}

	return NIL;
}

orcaData orcaObject::operator_div(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("/", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}

	return NIL;
}

orcaData orcaObject::operator_div_rev(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("/rev", d)) { 
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}

	return NIL;
}

orcaData orcaObject::operator_lt(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("<", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}
	else {
		return NIL;
	}
}

orcaData orcaObject::operator_eq(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("==", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}
	else {
		return NIL;
	}
}

orcaData orcaObject::operator_and(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("&&", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}
	else {
		return NIL;
	}
}

orcaData orcaObject::operator_or(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("||", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}
	else {
		return NIL;
	}
}

orcaData orcaObject::operator_get(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member(".attr", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}

	return NIL;
}

orcaData orcaObject::operator_get_last(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member(".attr_last", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}

	return operator_get(vm, p);
}

orcaData orcaObject::operator_set(orcaVM* vm, const char* name, orcaData& p)
{
	orcaData d;
	if (has_member(".attr=", d)) {
		vm->push_param(d);
		vm->push_param(name);
		vm->push_param(p);
		vm->call(2);
		return vm->m_stack->pop();
	}

	return NIL;
}

orcaData orcaObject::operator_get_at(orcaVM* vm, orcaData& p)
{
	orcaData d;
	if (has_member("[]", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->call(1);
		return vm->m_stack->pop();
	}
	else {
		throw orcaException(vm, "orca.type",
							string("object is not indexible: ") +
							dump_str());
	}

	return NIL;
}

orcaData orcaObject::operator_set_at(orcaVM* vm, orcaData& p, orcaData& v)
{
	orcaData d;
	if (has_member("[]=", d)) {
		vm->push_param(d);
		vm->push_param(p);
		vm->push_param(v);
		vm->call(2);
		return vm->m_stack->pop();
	}
	else {
		throw orcaException(vm, "orca.type",
							string("object is not indexible: ") +
							dump_str());
	}

	return NIL;
}


bool orcaObject::issubclassof(orcaObject* o)
{
	if (m_parent == NULL) {
		return false;
	}
	
	list<orcaObject*>::iterator vi;
	vi = m_parent->begin();
	for(; vi != m_parent->end(); ++vi) {
		if ((*vi)->m_original == o) {
			return true;
		}
	}

	vi = m_parent->begin();
	for(; vi != m_parent->end(); ++vi) {
		if ((*vi)->issubclassof(o)) {
			return true;
		}
	}

	return false;
}

bool orcaObject::isinstanceof(orcaObject* o)
{
	return m_original == o;
}

int orcaObject::get_frame_size()
{
	if (m_code == NULL)
		return 0;

	CodeHeader* cp = (CodeHeader*)m_code;
	return ltohs(cp->frame_size);
}

int orcaObject::get_argument_size()
{
	if (m_code == NULL)
		return 0;

	CodeHeader* cp = (CodeHeader*)m_code;
	return ltohs(cp->argument_size);
}

char orcaObject::get_flag_argv()
{
	if (m_code == NULL)
		return 0;

	CodeHeader* cp = (CodeHeader*)m_code;
	return (char)ltohs(cp->flag_argv);
}


void orcaObject::set_flag(char flag)
{
	m_flag = flag;
}

char orcaObject::get_flag()
{
	return m_flag;
}

bool orcaObject::is_pure()
{
	return m_flag & BIT_DEFINE_PURE;
}

bool orcaObject::is_init()
{
	return m_flag & BIT_DEFINE_INIT;
}


string orcaObject::pack_save()
{
	return "";
}

void orcaObject::pack_load(string& str)
{
	return;
}


orcaObject* orcaObject::get_owner()
{
	orcaObject* op = m_owner;
	if (op == NULL) return op;

	while (op->m_base != NULL) {
		op = op->m_base;
	}

	return op;
}

