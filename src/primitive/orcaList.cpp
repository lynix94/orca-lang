/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaList.cpp - list type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaList.h"
#include "orcaSbf.h"
#include "orcaVirtList.h"
#include "orcaListIterator.h"

#include "orcaStack.h"
#include "orcaException.h"
#include <boost/lexical_cast.hpp>
#include "orcaSort.h"


bool islist(orcaData p)
{
	if (isobj<orcaList>(p)) {
		orcaObject* o = p.o();

		if (dynamic_cast<orcaList*>(o) ||
			dynamic_cast<orcaSbf*>(o) ||
			dynamic_cast<orcaVirtList*>(o))
		{
			return true;
		}
	}

	return false;
}

cp_map<orcaData>::Type orcaList::m_static_list;

orcaList::orcaList()
{ 
	m_timestamp = 0;

	set_name("list"); 
	insert_native_function("size", (object_fp)&orcaList::ex_size);
	insert_native_function("tuple", (object_fp)&orcaList::ex_tuple);
	insert_native_function("push_back", (object_fp)&orcaList::ex_push_back);
	insert_native_function("push_front", (object_fp)&orcaList::ex_push_front);
	insert_native_function("pop_back", (object_fp)&orcaList::ex_pop_back);
	insert_native_function("pop_front", (object_fp)&orcaList::ex_pop_front);
	insert_native_function("find", (object_fp)&orcaList::ex_find);
	insert_native_function("begin", (object_fp)&orcaList::ex_begin);
	insert_native_function("last", (object_fp)&orcaList::ex_last);
	insert_native_function("end", (object_fp)&orcaList::ex_end);
	insert_native_function("sort", (object_fp)&orcaList::ex_sort);
	insert_native_function("empty", (object_fp)&orcaList::ex_empty);
	insert_native_function("clear", (object_fp)&orcaList::ex_clear);
	insert_native_function("->", (object_fp)&orcaList::ex_channel_out);
	insert_native_function("<-", (object_fp)&orcaList::ex_channel_in);
}

orcaList::orcaList(void* vp) 
{ 
	m_timestamp = 0;
}

orcaObject* orcaList::v_clone() {
	return slice(0, m_value.size(), false).o();
}

orcaList::~orcaList()
{
	list<orcaData>::iterator it;
	for (it=m_value.begin(); it!=m_value.end(); ++it) {
		(*it).rc_dec();
	}
}

orcaData& orcaList::at(int idx) 
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
					boost::lexical_cast<string>(idx + len));
		}
	}

	list<orcaData>::iterator li = m_value.begin();
	for(int i=0; i<idx; i++) ++li;

	return *li;
}

orcaData orcaList::slice(int start, int end, bool include_right) 
{
	int len = m_value.size();
	bool reverse;

	if (start < 0) start += len;
	if (end < 0) end += len;

	if (start <= end) {
		reverse = false;
	}
	else {
		reverse = true;
		int tmp = start;
		start = end;
		end = tmp;
	}

	if (start < 0) start =0;
	if (end < 0) end = 0;
	if (start > len) start = len;
	if (end > len) end = len;

	orcaList* lst = new orcaList();

	list<orcaData>::iterator li = m_value.begin();
	int i;
	for(i=0; i<start; i++) li++;

	if (!reverse) {
		for(; i<end; i++) {
			lst->push_back(*li++);
		}

		if (include_right && li != m_value.end()) {
			lst->push_back(*li);
		}
	}
	else {
		for(; i<end; i++) {
			lst->push_front(*li++);
		}

		if (include_right && li != m_value.end()) {
			lst->push_front(*li);
		}
	}

	return lst;
}

orcaData orcaList::slice(orcaListIter start, orcaListIter to)
{
	orcaList* lst = new orcaList();
	while (start != to && start != end()) {
		lst->push_back(*start++);
	}

	return lst;
}

void orcaList::update(int idx, orcaData& d)
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

	list<orcaData>::iterator li = m_value.begin();
	for(int i=0; i<idx; i++) ++li;

	(*li).rc_dec();
	*li = d;
	(*li).rc_inc();
}


struct RC_INC : public unary_function<orcaData, void>
{
	void operator()(orcaData d) {
		d.rc_inc();
	}
};

void orcaList::update_range(int start, int end, bool include_right, orcaData& d)
{

	int len = m_value.size();
	bool reverse;

	orcaList* lo = NULL;
	if (is<TYPE_OBJ>(d)) lo =  dynamic_cast<orcaList*>(d.o());

	if (start < 0) start += len;
	if (end < 0) end += len;

	if ( start <= end) {
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

	orcaList* lst = new orcaList();

	int i;
	list<orcaData>::iterator li = m_value.begin();
	if (!reverse) {
		for(i=0; i<start; i++) 
			lst->m_value.push_back(*li++);

		for(; i<end; i++) {
			(*li).rc_dec();
			++li;
		}

		if (lo != NULL) {
			copy(lo->m_value.begin(), lo->m_value.end(), back_inserter(lst->m_value));
			for_each(lo->m_value.begin(), lo->m_value.end(), RC_INC());
		}
		else {
			lst->m_value.push_back(d);
			d.rc_inc();
		}

		copy(li, m_value.end(), back_inserter(lst->m_value));

	}
	else {
		for(i=0; i<start; i++) 
			lst->m_value.push_front(*li++);

		for(; i<end; i++) li++;
		if (include_right) li++;

		if (lo != NULL) {
			copy(lo->m_value.begin(), lo->m_value.end(), front_inserter(lst->m_value));
			for_each(lo->m_value.begin(), lo->m_value.end(), RC_INC());
		}
		else {
			lst->m_value.push_front(d);
			d.rc_inc();
		}

		copy(li, m_value.end(), front_inserter(lst->m_value));
	}

	m_value.swap(lst->m_value);
	delete lst;
}

void orcaList::string_(orcaVM* vm, string& str) 
{
	orcaListIter li = begin();

	str += "[ ";
	while(li!=end()) {
		if (is<TYPE_STR>(*li)) str += "'";
		(*li).string_(vm, str);
		if (is<TYPE_STR>(*li)) str += "'";

		++li;
		if (li!=end()) str+= ",";
	}

	str += " ]";
}

orcaData orcaList::ex_size(orcaVM* vm, int n) 
{
	return size();
}

orcaData orcaList::ex_tuple(orcaVM* vm, int n) 
{
	orcaTuple* tp = new orcaTuple();

	orcaListIter li = begin();
	for(; li != end(); ++li) {
		tp->push_back(*li);
	}

	return tp;
}

orcaData orcaList::ex_push_back(orcaVM* vm, int n) 
{
	if (n < 1) vm->need_param();

	push_back(vm->get_param(0));
	return this;
}

orcaData orcaList::ex_pop_back(orcaVM* vm, int n) 
{
	pop_back();
	return this;
}

orcaData orcaList::ex_push_front(orcaVM* vm, int n) 
{
	if (n < 1) vm->need_param();

	push_front(vm->get_param(0));
	return this;
}

orcaData orcaList::ex_pop_front(orcaVM* vm, int n) 
{
	pop_front();
	return this;
}

orcaData orcaList::ex_find(orcaVM* vm, int n) 
{
	if (n < 1) vm->need_param();

	orcaData val = vm->get_param(0);

	orcaListIter it = begin();
	orcaListIter it_end = end();
	for (; it!=it_end; ++it) {
		if ((*it).operator_eq(vm, val)) {
			return new orcaListIterator(it, begin(), it_end);
		}
	}

	return new orcaListIterator(it_end, begin(), it_end);
}

orcaData orcaList::ex_begin(orcaVM* vm, int n) 
{
	return new orcaListIterator(begin(), begin(), end());
}

orcaData orcaList::ex_last(orcaVM* vm, int n) 
{
	orcaListIter li = end();
	--li;
	return new orcaListIterator(li, begin(), end());
}

orcaData orcaList::ex_end(orcaVM* vm, int n) 
{
	return new orcaListIterator(end(), begin(), end());
}

void orcaList::sort(orcaVM* vm, orcaData fun)
{
	if (is<TYPE_NIL>(fun)) {
		m_value.sort();
	}
	else {
		sort_compare cmp;
		cmp.vm = vm;
		cmp.fun = fun;

		m_value.sort(cmp);
	}
}

orcaData orcaList::ex_sort(orcaVM* vm, int n) 
{
	if (n < 1) {
		sort(vm, NIL);
	}
	else {
		sort(vm, vm->get_param(0));
	}

	return this;
}

orcaData orcaList::ex_empty(orcaVM* vm, int n) 
{
	return m_value.empty();
}

orcaData orcaList::ex_clear(orcaVM* vm, int n) 
{
	list<orcaData>::iterator it;
	for (it=m_value.begin(); it!=m_value.end(); ++it) {
		(*it).rc_dec();
	}

	m_value.clear();
	return this;
}

void orcaList::dump() 
{ 
	orcaListIter li = begin();
	printf("[ ");

	for(; li != end(); ++li) 
		(*li).dump();

	printf(" ]\n");
}

orcaData orcaList::operator_add(orcaVM* vm, orcaData& p)
{
	if (!islist(p)) {
		return NIL;
	}

	orcaList* lst = new orcaList();
	orcaList* lo = static_cast<orcaList*>(p.o());

	orcaListIter lhs = begin();
	orcaListIter rhs = lo->begin();

	while(lhs != end()) {
		lst->push_back(*lhs);
		++lhs;
	}

	while(rhs != lo->end()) {
		lst->push_back(*rhs);
		++rhs;
	}

	return lst;
}

orcaData orcaList::operator_eq(orcaVM* vm, orcaData& p)
{
	orcaList* lo = NULL;
	if (is<TYPE_OBJ>(p)) {
		lo = dynamic_cast<orcaList*>(p.o());
	}

	if (lo == NULL) {
		return NIL;
	}

	orcaListIter lhs = begin();
	orcaListIter rhs = lo->begin();

	for(; lhs != end() && rhs != lo->end(); ++lhs, ++rhs) {
		if ((*lhs).operator_neq(vm, *rhs)) return false;
	}

	if (lhs == end() && rhs == lo->end()) 
		return true;

	return false;
}


bool orcaList::compare(orcaVM* vm, orcaList* lo, int len, orcaListIter lhs)
{
	orcaListIter rhs = lo->begin();
	for(int i=0; lhs != end() && i<len; ++lhs, ++rhs, i++) {
		if ((*lhs).operator_neq(vm, *rhs)) return false;
	}

	return true;
}


orcaListIter orcaList::search(orcaVM* vm, orcaList* lo, orcaListIter lhs)
{
	int len = lo->size();
	orcaListIter start = lhs;
	
	for(; start != end(); ++start) {
		lhs = start;
		orcaListIter rhs = lo->begin();
		for(; rhs != lo->end(); ++rhs, ++lhs) {
			if ((*lhs).operator_neq(vm, *rhs)) break;
		}

		if (rhs == lo->end()) {
			return start;
		}
		else {
			continue;
		}
	}

	return end();
}


int orcaList::size() 
{ 
	return m_value.size(); 
}

void orcaList::push_front(orcaData p) 
{
	m_value.push_front(p);
	inc_timestamp();
	p.rc_inc();
}

void orcaList::push_back(orcaData p) 
{
	m_value.push_back(p);
	inc_timestamp();
	p.rc_inc();
}


orcaData orcaList::pop_front() 
{
	if (m_value.size() == 0) {
		return NIL;
	}

	orcaData ret = *(m_value.begin());
	m_value.pop_front();
	inc_timestamp();

	ret.rc_dec();
	return NIL;
}

orcaData orcaList::pop_back() 
{
	if (m_value.size() == 0) {
		return NIL;
	}

	orcaData ret = *(--m_value.end());
	inc_timestamp();
	m_value.pop_back();

	ret.rc_dec();
	return NIL;
}

orcaListIter orcaList::begin() 
{
	orcaListIter it(this, m_value.begin());
	return it;
}

orcaListIter orcaList::end() 
{
	orcaListIter it(this, m_value.end());
	return it;
}

orcaData orcaList::ex_channel_out(orcaVM* vm, int n) 
{
	if (n<1) vm->need_param();

	int count = vm->get_param(0).Integer();
	if (count == 0) { // argv
		count = m_value.size();
	}

	orcaTuple* tup = new orcaTuple();
	int i=0;
	list<orcaData>::iterator it;
	for (it=m_value.begin(); it!=m_value.end() && i<count; ++it, i++) {
		tup->push_back(*it);
	}

	return tup;
}

orcaData orcaList::ex_channel_in(orcaVM* vm, int n) 
{
	for (int i=0; i<n; i++) {
		orcaData val = vm->get_param(i);
		push_back(val);
	}

	return this;
}





