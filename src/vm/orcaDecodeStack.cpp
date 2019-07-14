/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaDecodeStack.cpp - class for handling "decode statement"

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <boost/regex.hpp>

#include "orcaLocal.h"
#include "orcaList.h"
#include "orcaSbf.h"
#include "orcaVirtList.h"
#include "orcaException.h"
#include "orcaDecodeStack.h"
#include "orcaTuple.h"

using namespace boost;

orcaDecodeStack::orcaDecodeStack(orcaVM* vm)
{
	m_vm = vm;
	m_local = vm->m_local;
}

void orcaDecodeStack::push(orcaData d) 
{
	DECODE dec;
	dec.original = d;

	m_stack.push_back(dec);
}

void orcaDecodeStack::pop() 
{
	m_stack.pop_back();
}

void orcaDecodeStack::init_pattern() 
{
	last().pattern_idx = 0;
	if (isobj<orcaList>(get_pattern()))
		last().pattern_iter = TO_LIST(get_pattern().o())->begin();
}

orcaData orcaDecodeStack::get_tail() 
{
	orcaData p = get_pattern();
	if (is<TYPE_STR>(p)) {
		return p.s().substr(get_idx());
	}
	else if (isobj<orcaList>(p)) {
		orcaList* lo = TO_LIST(p.o());
		return lo->slice(get_iter(), lo->end());
	}

	return NIL;
}

orcaData& orcaDecodeStack::get_pattern() 
{
	return last().original;
}

void orcaDecodeStack::set_idx(int idx) 
{
	last().pattern_idx = idx;
}

int orcaDecodeStack::get_idx() 
{
	return last().pattern_idx;
}

void orcaDecodeStack::set_iter(orcaListIter it ) 
{
	last().pattern_iter = it;
}

orcaListIter orcaDecodeStack::get_iter() 
{
	return last().pattern_iter;
}

void orcaDecodeStack::set_next_pattern_addr(int addr) 
{
	last().next_pattern_addr = addr;
}

int orcaDecodeStack::get_next_pattern_addr() 
{
	return last().next_pattern_addr;
}

bool orcaDecodeStack::match_str(orcaData p2, short idx)
{
	string& p1 = get_pattern().s();

	if (is<TYPE_STR>(p2)) {
		if (p1.substr(get_idx(), p2.s().length()) == p2.s()) {

			if (idx >= 0)  {
				m_local->set(idx, p2);
			}

			set_idx(get_idx() + p2.s().length());
			return true;
		}
		else {
			return false;
		}
	}
	else if (is<TYPE_REGEX>(p2)) {
		match_results<string::const_iterator> mr;
		string::const_iterator start, end;
		start = p1.begin() + get_idx();
		end = p1.end();

		bool ret = regex_search(start, end, mr, p2.re());
		if (ret && mr[0].first == p1.begin() + get_idx()) {

			if (idx >= 0) {
				m_local->set(idx, p1.substr(get_idx(), mr[0].second-mr[0].first));
			}

			set_idx(mr[0].second - p1.begin());
			return true;
		}
		else {
			return false;
		}
	}
	else if (is<TYPE_OBJ>(p2)) {
		string remain = p1.substr(get_idx());
		orcaObject* op = p2.o();

		orcaVM* vm = get_current_vm();
		vm->push_param(op);
		vm->push_param(remain);
		vm->call(1);
		orcaData ret = vm->m_stack->pop();
		if (is<TYPE_STR>(ret)) {
			int size = ret.s().length();
			if (idx >= 0) {
				m_local->set(idx, ret);
			}

			set_idx(get_idx() + size);
			return true;
		}
		else {
			return false;
		}
	}

	return false;
}


bool orcaDecodeStack::match_str_shift(orcaData p2, short idx, short shift)
{
	string& p1 = get_pattern().s();

	if (is<TYPE_STR>(p2)) {
		int s = p1.find(p2.s(), get_idx());
		if (s >= 0) {

			if (idx >= 0)  {
				m_local->set(idx, p2);
			}

			m_local->set(shift, p1.substr(get_idx(), s-get_idx()));

			set_idx(s + p2.s().length());
			return true;
		}
		else {
			return false;
		}
	}
	else if (is<TYPE_REGEX>(p2)) {
		match_results<string::const_iterator> mr;
		string::const_iterator start, end;
		start = p1.begin() + get_idx();
		end = p1.end();

		bool ret = regex_search(start, end, mr, p2.re());
		if (ret) {
			if (idx >= 0) {
				m_local->set(idx, p1.substr(mr[0].first - p1.begin(), 
							 mr[0].second - mr[0].first));
			}

			m_local->set(shift, p1.substr(get_idx(), mr[0].first - p1.begin() - get_idx()));

			set_idx(mr[0].second - p1.begin());
			return true;
		}
		else {
			return false;
		}
	}

	return false;
}



bool orcaDecodeStack::match_list(orcaList* p2, short idx)
{
	int size = p2->size();
	orcaList* p1 = TO_LIST(get_pattern().o());
	orcaListIter p1_it = get_iter(); 

	if (size == 0 && p1->size() != 0) {
		return false;
	}

	bool ret = p1->compare(m_vm, p2, size, p1_it);

	if (ret == true) {
		if (idx >= 0)  {
			m_local->set(idx, p2);
		}

		for(int i=0; i<size; i++) p1_it++;
		set_iter(p1_it);
		return true;
	}

	return false;
}

bool orcaDecodeStack::match_list_shift(orcaList* p2, short idx, short shift)
{
	orcaListIter p1_it = get_iter();
	orcaList* p1 = TO_LIST(get_pattern().o());
	
	orcaListIter start = p1->search(m_vm, p2, p1_it);

	if (start != p1->end()) {
		if (idx >= 0)  {
			m_local->set(idx, p2);
		}

		m_local->set(shift, p1->slice(get_iter(), start));

		for(int i=0; i<p2->size(); i++) p1_it++;
		set_iter(p1_it);
		return true;
	}

	return false;
}



bool orcaDecodeStack::match_expr(orcaData p2, short idx)
{
	orcaData p1 = get_pattern();

	if (is<TYPE_STR>(p1)) {
		return match_str(p2, idx);
	}
	else if (islist(p1)) {
		if (!islist(p2)) {
			throw orcaException(m_vm, "orca.type", p2.dump_str() + 
								"should be list type for list matching");
		}
			
		return match_list(TO_LIST(p2.o()), idx);
	}
	else {
		throw orcaException(m_vm, "orca.type", p1.dump_str() + 
							"is not allowed in decode statement");
	}
	
	return false;
}

bool orcaDecodeStack::match_expr_shift(orcaData p2, short idx, short shift)
{
	orcaData p1 = get_pattern();

	if (is<TYPE_STR>(p1)) {
		return match_str_shift(p2, idx, shift);
	}
	else if (islist(p1)) {
		if (!islist(p2)) {
			throw orcaException(m_vm, "orca.type", p2.dump_str() + 
								"should be list type for list matching");
		}

		return match_list_shift(TO_LIST(p2.o()), idx, shift);
	}
	else {
		throw orcaException(m_vm, "orca.type", p1.dump_str() + 
							"is not allowed in decode statement");
	}
	
	return false;
}

orcaDecodeStack::DECODE& orcaDecodeStack::last()
{ 
	return m_stack[m_stack.size()-1]; 
}


bool orcaDecodeStack::check_remain()
{
	orcaData p1 = get_pattern();

	if (is<TYPE_STR>(p1)) {
		int idx = get_idx();
		if (idx < p1.s().length()) {
			return false;
		}
	}
	else if (islist(p1)) {
		orcaListIter p1_it = get_iter(); 
		orcaList* lo = TO_LIST(p1.o());
		if (p1_it != lo->end()) {
			return false;
		}
	}
	else {
		throw orcaException(m_vm, "orca.type", p1.dump_str() + 
							"is not allowed in decode statement");
	}
	
	return true;
}

