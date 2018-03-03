/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMap.cpp - map type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <sstream>

#include "orcaMap.h"
#include "orcaMapIter.h"
#include "orcaList.h"
#include "orcaException.h"

bool data_cmp::operator()(orcaData l, orcaData r) const
{
	if (is<TYPE_OBJ>(l) || is<TYPE_OBJ>(r)) {
		return l.operator_lt(get_current_vm(), r).Boolean(); // for user made operator..
	}

	return l.operator_lt(NULL, r).Boolean();
}


cp_map<orcaData>::Type orcaMap::m_static_map;

orcaMap::orcaMap()
{ 
	set_name("map"); 
	insert_native_function("size", (object_fp)&orcaMap::ex_size);
	insert_native_function("keys", (object_fp)&orcaMap::ex_keys);
	insert_native_function("values", (object_fp)&orcaMap::ex_values);
	insert_native_function("has_key", (object_fp)&orcaMap::ex_has_key);
	insert_native_function("erase_key", (object_fp)&orcaMap::ex_erase_key);
	insert_native_function("find", (object_fp)&orcaMap::ex_find);
	insert_native_function("begin", (object_fp)&orcaMap::ex_begin);
	insert_native_function("last", (object_fp)&orcaMap::ex_last);
	insert_native_function("end", (object_fp)&orcaMap::ex_end);
	insert_native_function("lower_bound", (object_fp)&orcaMap::ex_lower_bound);
	insert_native_function("upper_bound", (object_fp)&orcaMap::ex_upper_bound);
	insert_native_function("empty", (object_fp)&orcaMap::ex_empty);
	insert_native_function("clear", (object_fp)&orcaMap::ex_clear);

	m_timestamp = 0;
}

orcaMap::orcaMap(void* vp) 
{ 
	m_timestamp = 0;
}

orcaObject* orcaMap::v_clone() 
{
	orcaMap* mp = new orcaMap(NULL);

	orcamap_iterator mi = m_value.begin();
	for(; mi != m_value.end(); ++mi) {
		orcaData key = mi->first;
		orcaData value = mi->second;
		mp->update(key, value);
	}

	return mp;
}

orcaMap::~orcaMap()
{
	orcamap_iterator it;
	for (it=m_value.begin(); it!=m_value.end(); ++it) {
		orcaData key = it->first;
		orcaData value = it->second;
		key.rc_dec();
		value.rc_dec();
	}
}

orcaData& orcaMap::at(orcaData& key) 
{
	orcamap_iterator mi;
	mi = m_value.find(key);

	if (mi == m_value.end()) {
		return NIL;
	}

	return mi->second;
}

bool orcaMap::has_key(orcaData& key)
{
	orcamap_iterator mi = m_value.find(key);
	if (mi == m_value.end()) {
		return false;
	}

	return true;
}

struct RC_INC : public unary_function<orcaData, void>
{
	void operator()(orcaData d) {
		d.rc_inc();
	}
};


orcaData orcaMap::slice(orcaData& start, orcaData& end, bool include_right) 
{
	if (start.operator_gt(NULL, end).Boolean()) {
		std::swap(start, end);
	}

	orcaList* lp = new orcaList();
	orcamap_iterator mi = m_value.find(start);;
	for( ; mi != m_value.end(); ++mi) {
		lp->push_back(mi->second);
	}

	return lp;
}

void orcaMap::update(orcaData& key, orcaData& val)
{
	orcamap_iterator mi = m_value.find(key);;
	if (mi == m_value.end()) {
		m_timestamp++; // in this case, key order will be changed.
		key.rc_inc();
	}

	m_value[key].rc_dec();
	m_value[key] = val;
	m_value[key].rc_inc();
}


void orcaMap::string_(orcaVM* vm, string& str) 
{
	orcamap_iterator mi = m_value.begin();

	stringstream ss;
	ss << str;
	ss << "{ ";
	while(mi!=m_value.end()) {
		if (is<TYPE_STR>(mi->first)) ss << "'";
		ss << (mi->first).string_(vm);
		if (is<TYPE_STR>(mi->first)) ss << "'";

		ss << ":";

		if (is<TYPE_STR>(mi->second)) ss << "'";
		ss << (mi->second).string_(vm);
		if (is<TYPE_STR>(mi->second)) ss << "'";

		++mi;
		if (mi!=m_value.end()) ss << ",";
	}

	ss << " }";
	str = ss.str();
}

void orcaMap::repr(orcaVM* vm, string& str) 
{
	orcamap_iterator mi = m_value.begin();

	stringstream ss;
	ss << str;
	ss << "{ ";
	while(mi!=m_value.end()) {
		ss << (mi->first).repr(vm);
		ss << ":";
		ss << (mi->second).repr(vm);

		++mi;
		if (mi!=m_value.end()) ss << ",";
	}

	ss << " }";
	str = ss.str();
}


orcaData orcaMap::ex_size(orcaVM* vm, int n) 
{
	return m_value.size();
}

orcaData orcaMap::ex_keys(orcaVM* vm, int n) 
{
	orcaList* lp = new orcaList();

	orcamap_iterator mi = m_value.begin();

	for(; mi!=m_value.end(); ++mi) {
		orcaData d = mi->first;
		lp->push_back(d);
	}

	return lp;
}

orcaData orcaMap::ex_values(orcaVM* vm, int n) 
{
	orcaList* lp = new orcaList();

	orcamap_iterator mi = m_value.begin();

	for(; mi!=m_value.end(); ++mi) {
		lp->push_back(mi->second);
	}

	return lp;
}

orcaData orcaMap::ex_has_key(orcaVM* vm, int n) 
{
	if (n<1) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	orcamap_iterator mi = m_value.find(vm->get_param(0));

	if (mi == m_value.end()) {
		return false;
	}

	return true;
}

orcaData orcaMap::ex_find(orcaVM* vm, int n) 
{
	if (n<1) {
		throw orcaException(vm, "orca.param", "insuffiecient parameter");
	}

	orcamap_iterator mi = m_value.find(vm->get_param(0));

	return new orcaMapIter(mi, this);
}

orcaData orcaMap::ex_lower_bound(orcaVM* vm, int n) 
{
	if (n<1) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	orcamap_iterator mi = m_value.lower_bound(vm->get_param(0));

	return new orcaMapIter(mi, this);
}

orcaData orcaMap::ex_upper_bound(orcaVM* vm, int n) 
{
	if (n<1) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	orcamap_iterator mi = m_value.upper_bound(vm->get_param(0));

	return new orcaMapIter(mi, this);
}

orcaData orcaMap::ex_begin(orcaVM* vm, int n) 
{
	return new orcaMapIter(m_value.begin(), this);
}

orcaData orcaMap::ex_last(orcaVM* vm, int n) 
{
	orcamap_iterator it = m_value.end();
	--it;
	return new orcaMapIter(it, this);
}

orcaData orcaMap::ex_end(orcaVM* vm, int n) 
{
	return new orcaMapIter(m_value.end(), this);
}

orcaData orcaMap::ex_erase_key(orcaVM* vm, int n) 
{
	if (n<1) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	bool changed = false;
	for (int i=0; i<n; i++) {
		orcamap_iterator mi = m_value.find(vm->get_param(i));
		if (mi == m_value.end()) {
			continue;
		}

		changed = true;
		orcaData key = mi->first;
		key.rc_dec();
		mi->second.rc_dec();
		m_value.erase(mi);
	}

	m_timestamp++;
	return NIL;
}

orcaData orcaMap::operator_eq(orcaVM* vm, orcaData& p)
{
	orcaMap* mo = NULL;
	if (is<TYPE_OBJ>(p)) {
		mo = dynamic_cast<orcaMap*>(p.o());
	}

	if (mo == NULL) {
		return NIL;
	}

	if (m_value.size() != mo->m_value.size()) 
		return false;

	orcamap_iterator it1 = begin();
	orcamap_iterator it2 = mo->begin();
	for(; it1!=end(); ++it1, ++it2) {
		orcaData t1, t2;
		t1 = it1->first;
		t2 = it2->first;
		if (!t1.operator_eq(vm, t2).Boolean())
			return false;

		t1 = it1->second;
		t2 = it2->second;
		if (!t1.operator_eq(vm, t2).Boolean())
			return false;
	}

	return true;
}

orcaData orcaMap::ex_empty(orcaVM* vm, int n) 
{
	return m_value.empty();
}

orcaData orcaMap::ex_clear(orcaVM* vm, int n) 
{
	orcamap_iterator it;
	for (it=m_value.begin(); it!=m_value.end(); ++it) {
		orcaData key = it->first;
		orcaData value = it->second;
		key.rc_dec();
		value.rc_dec();
	}

	m_value.clear();
	return this;
}

void orcaMap::dump() 
{ 
	orcamap_iterator mi = begin();

	printf("{ ");

	for(; mi!=end(); ++mi) {
		printf("key: ");
		(mi->first).dump();
		printf("value: ");
		(mi->second).dump();
	}

	printf(" }\n");
}



