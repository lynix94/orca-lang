/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTuple.cpp - tuple type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <sstream>
#include <boost/lexical_cast.hpp>

#include "orcaTuple.h"
#include "orcaTupleIter.h"
#include "orcaTupleVIter.h"
#include "orcaList.h"
#include "orcaException.h"

cp_map<orcaData>::Type orcaTuple::m_static_tuple;

orcaTuple::orcaTuple()
{ 
	set_name("tuple"); 
	insert_native_function("size", (object_fp)&orcaTuple::ex_size);
	insert_native_function("list", (object_fp)&orcaTuple::ex_list);
	insert_native_function("push_back", (object_fp)&orcaTuple::ex_push_back);
	insert_native_function("pop_back", (object_fp)&orcaTuple::ex_pop_back);
	insert_native_function("iter", (object_fp)&orcaTuple::ex_iter);
	insert_native_function("piter", (object_fp)&orcaTuple::ex_piter);
	insert_native_function("first", (object_fp)&orcaTuple::ex_first);
	insert_native_function("last", (object_fp)&orcaTuple::ex_last);
	insert_native_function("end", (object_fp)&orcaTuple::ex_end);
	insert_native_function("find", (object_fp)&orcaTuple::ex_find);
	insert_native_function("empty", (object_fp)&orcaTuple::ex_empty);
	insert_native_function("clear", (object_fp)&orcaTuple::ex_clear);
	insert_native_function("->", (object_fp)&orcaTuple::ex_channel_out);
	insert_native_function("<-", (object_fp)&orcaTuple::ex_channel_in);

	m_timestamp = 0;
}

orcaTuple::orcaTuple(void* vp) 
{ 
	m_timestamp = 0;
}

orcaTuple::orcaTuple(int n)
{ 
	set_name("tuple"); 
	insert_native_function("size", (object_fp)&orcaTuple::ex_size);
	insert_native_function("list", (object_fp)&orcaTuple::ex_list);
	insert_native_function("push_back", (object_fp)&orcaTuple::ex_push_back);
	insert_native_function("pop_back", (object_fp)&orcaTuple::ex_pop_back);
	insert_native_function("iter", (object_fp)&orcaTuple::ex_iter);
	insert_native_function("piter", (object_fp)&orcaTuple::ex_piter);
	insert_native_function("first", (object_fp)&orcaTuple::ex_first);
	insert_native_function("last", (object_fp)&orcaTuple::ex_last);
	insert_native_function("end", (object_fp)&orcaTuple::ex_end);
	insert_native_function("find", (object_fp)&orcaTuple::ex_find);
	insert_native_function("empty", (object_fp)&orcaTuple::ex_empty);
	insert_native_function("clear", (object_fp)&orcaTuple::ex_clear);
	insert_native_function("->", (object_fp)&orcaTuple::ex_channel_out);
	insert_native_function("<-", (object_fp)&orcaTuple::ex_channel_in);

	m_value.resize(n);
	m_timestamp = 0;
}

orcaObject* orcaTuple::v_clone() {
	return slice(0, m_value.size(), false).o();
}

orcaTuple::~orcaTuple()
{
	vector<orcaData>::iterator it;
	for (it=m_value.begin(); it!=m_value.end(); ++it) {
		(*it).rc_dec();
	}
}


orcaData& orcaTuple::at(int idx) 
{
	int len = m_value.size();

	if (idx >= len) {
		throw orcaException(NULL, "orca.index", string("out of index. size: ") + 
				boost::lexical_cast<string>(len) + " index: " + 
				boost::lexical_cast<string>(idx));
	}

	if (idx < 0) {
		idx = len + idx;

		if (idx < 0) {
			throw orcaException(NULL, "orca.index", string("out of index. size: ") + 
					boost::lexical_cast<string>(len) + " index: " + 
					boost::lexical_cast<string>(idx));
		}
	}

	return m_value[idx];
}

struct RC_INC : public unary_function<orcaData, void>
{
	void operator()(orcaData d) {
		d.rc_inc();
	}
};


orcaData orcaTuple::slice(int start, int end, bool include_right) 
{
	int len = m_value.size();
	bool reverse;

	if (start < 0) start += len;
	if (end < 0) end += len;

	if ( start <= end) {
		reverse = false;
	}
	else {
		reverse = true;
		int tmp = start;
		start = end + 1;
		end = tmp + 1;
	}

	if (start < 0) start =0;
	if (end < 0) end = 0;
	if (start > len) start = len;
	if (end > len) end = len;

	orcaTuple* tup = new orcaTuple();
	if (!reverse) {
		vector<orcaData>::iterator vis = m_value.begin() + start;
		vector<orcaData>::iterator vie = m_value.begin() + end;
		if (include_right) vie++;

		copy(vis, vie, back_inserter(tup->m_value));
		for_each(tup->m_value.begin(), tup->m_value.end(), RC_INC());
	}
	else {
		vector<orcaData>::reverse_iterator vis = 
			m_value.rbegin() + m_value.size() - end;
		vector<orcaData>::reverse_iterator vie = 
			m_value.rbegin() + m_value.size() - start;

		if (include_right) vie++;

		copy(vis, vie, back_inserter(tup->m_value));
		for_each(tup->m_value.begin(), tup->m_value.end(), RC_INC());
	}

	return tup;
}

void orcaTuple::update(int idx, orcaData d) 
{
	int len = m_value.size();
	if (idx < 0) idx += len;

	m_value[idx].rc_dec();
	m_value[idx] = d;
	m_value[idx].rc_inc();
}

void orcaTuple::update_range(int start, int end, bool include_right, orcaData& d)
{
	int len = m_value.size();
	bool reverse;

	orcaTuple* to = NULL;
	if (is<TYPE_OBJ>(d)) to =  dynamic_cast<orcaTuple*>(d.o());

	if (start < 0) start += len;
	if (end < 0) end += len;

	if (start <= end) {
		reverse = false;

		if (include_right) 
			end++;
	}
	else {
		reverse = true;
		int tmp = start;
		start = end + 1;
		end = tmp + 1;

		if (include_right) 
			start--;
	}


	if (start < 0) start =0;
	if (end < 0) end = 0;
	if (start > len) start = len;
	if (end > len) end = len;


	orcaTuple* tup = new orcaTuple();

	vector<orcaData>::iterator vis = m_value.begin() + start;
	vector<orcaData>::iterator vie = m_value.begin() + end;

	// copy head
	copy(m_value.begin(), vis, back_inserter(tup->m_value));

	// rc_dec to removed region
	for(; vis != vie; ++vis) {
		(*vis).rc_dec();
	}

	// copy body
	if (!reverse) {
		if (to != NULL) {
			copy(to->m_value.begin(), to->m_value.end(), back_inserter(tup->m_value));
			for_each(to->m_value.begin(), to->m_value.end(), RC_INC());
		}
		else {
			tup->m_value.push_back(d); 
			d.rc_inc();
		}
	}
	else {
		if (to != NULL) {
			copy(to->m_value.rbegin(), to->m_value.rend(), back_inserter(tup->m_value));
			for_each(to->m_value.begin(), to->m_value.end(), RC_INC());
		}
		else {
			tup->m_value.push_back(d); 
			d.rc_inc();
		}
	}

	// copy tail
	copy(vie, m_value.end(), back_inserter(tup->m_value));

	m_value.swap(tup->m_value);
	delete tup;
}


void orcaTuple::string_(orcaVM* vm, string& str) 
{
	vector<orcaData>::iterator vi = m_value.begin();

	stringstream ss;
	ss << str;
	ss << "( ";
	while(vi!=m_value.end()) {
		if (is<TYPE_STR>(*vi)) ss << "'";
		ss << (*vi).string_(vm);
		if (is<TYPE_STR>(*vi)) ss << "'";

		++vi;
		if (vi!=m_value.end()) ss << ",";
	}

	ss << " )";
	str = ss.str();
}

void orcaTuple::repr(orcaVM* vm, string& str) 
{
	vector<orcaData>::iterator vi = m_value.begin();

	stringstream ss;
	ss << str;
	ss << "( ";
	while(vi!=m_value.end()) {
		ss << (*vi).repr(vm);
		++vi;
		if (vi!=m_value.end()) ss << ",";
	}

	ss << " )";
	str = ss.str();
}

orcaData orcaTuple::ex_size(orcaVM* vm, int n) 
{
	return m_value.size();
}

orcaData orcaTuple::ex_list(orcaVM* vm, int n) 
{
	orcaList* lp = new orcaList();

	for(int i=0; i < m_value.size(); i++) {
		lp->push_back(m_value[i]);
	}

	return lp;
}

orcaData orcaTuple::ex_push_back(orcaVM* vm, int n) 
{
	if (n<1) vm->need_param();

	push_back(vm->get_param(0));
	return this;
}

orcaData orcaTuple::ex_pop_back(orcaVM* vm, int n) 
{
	if (!pop_back()) {
		throw orcaException(vm, "orca.tuple", "out of bound");
	}

	inc_timestamp();
	return this;
}

orcaData orcaTuple::ex_iter(orcaVM* vm, int n) 
{
	return new orcaTupleVIter(begin(), this, false);
}

orcaData orcaTuple::ex_piter(orcaVM* vm, int n) 
{
	return new orcaTupleIter(begin(), this, false);
}

orcaData orcaTuple::ex_first(orcaVM* vm, int n) 
{
	return new orcaTupleIter(begin(), this);
}

orcaData orcaTuple::ex_last(orcaVM* vm, int n) 
{
	orcatuple_iterator it = end();
	--it;
	return new orcaTupleIter(it, this);
}

orcaData orcaTuple::ex_end(orcaVM* vm, int n) 
{
	return new orcaTupleIter(end(), this);
}

void orcaTuple::dump() 
{ 
	vector<orcaData>::iterator vi = m_value.begin();

	printf("( ");

	for(; vi!=m_value.end(); ++vi) 
		(*vi).dump();

	printf(" )\n");
}

orcaData orcaTuple::operator_add(orcaVM* vm, orcaData& p)
{
	orcaTuple* to = NULL;
	if (is<TYPE_OBJ>(p))
		to = dynamic_cast<orcaTuple*>(p.o());

	if (to == NULL) 
		return NIL;
	
	orcaTuple* tpl = new orcaTuple();

	vector<orcaData>::iterator lhs = m_value.begin();
	for(; lhs != m_value.end(); ++lhs) {
		tpl->push_back(*lhs);
	}

	vector<orcaData>::iterator rhs = to->m_value.begin();
	for(; rhs != to->m_value.end(); ++rhs) {
		tpl->push_back(*rhs);
	}

	return tpl;
}

orcaData orcaTuple::operator_eq(orcaVM* vm, orcaData& p)
{
	orcaTuple* lo = NULL;
	if (is<TYPE_OBJ>(p))
		lo = dynamic_cast<orcaTuple*>(p.o());

	if (lo == NULL) 
		return NIL;

	vector<orcaData>::iterator lhs = m_value.begin();
	vector<orcaData>::iterator rhs = lo->m_value.begin();
	for(; lhs != m_value.end(); ++lhs, ++rhs) {
		if (lhs->operator_neq(vm, *rhs).Boolean()) return false;
	}

	if (rhs == lo->m_value.end()) 
		return true;

	return false;
}

orcaData orcaTuple::ex_find(orcaVM* vm, int n) 
{
	if (n<1) vm->need_param();

	orcaData val = vm->get_param(0);

	orcatuple_iterator it = begin();
	for(; it != end(); ++it) {
		if (it->operator_eq(vm, val).Boolean()) break;
	}

	return new orcaTupleIter(it, this);
}

orcaData orcaTuple::ex_empty(orcaVM* vm, int n) 
{
	return m_value.empty();
}

orcaData orcaTuple::ex_clear(orcaVM* vm, int n) 
{
	vector<orcaData>::iterator it;
	for (it=m_value.begin(); it!=m_value.end(); ++it) {
		(*it).rc_dec();
	}

	m_value.clear();
	return this;
}


orcaData orcaTuple::ex_channel_out(orcaVM* vm, int n) 
{
	if (n<1) vm->need_param();

	int count = vm->get_param(0).Integer();
	if (count == 0) { // argv
		count = m_value.size();
	}

	orcaTuple* tup = new orcaTuple();
	for (int i=0; i<count && !m_value.empty(); i++) {
		tup->push_back(at(-1));
		pop_back();
	}

	return tup;
}

orcaData orcaTuple::ex_channel_in(orcaVM* vm, int n) 
{
	for (int i=0; i<n; i++) {
		orcaData val = vm->get_param(i);
		push_back(val);
	}

	return this;
}



