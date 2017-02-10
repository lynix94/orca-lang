/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSbf.cpp - set builder form

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaSbf.h"
#include "orcaException.h"

range_gen::range_gen(int var, orcaLocal* loc, orcaList* lp) 
	: lvar(var), local(loc), list_p(lp), start(0), end(0), reverse(false), curr(0), step(0)
{ 
	list_p->rc_inc();
}

range_gen::range_gen(int var, orcaLocal* loc, orcaData s, orcaData e, orcaData st)
	: lvar(var), local(loc), list_p(NULL), start(s), end(e), reverse(false), curr(0), step(st) 
{ 
	if (is<TYPE_NIL>(start)) {
		reverse = true;
		start = e;
		end = NIL;
	}
	else if (is<TYPE_NIL>(end)) {
		// do nothing
	}
	else if (start > end) {
		reverse = true;
	}
}

range_gen::~range_gen() { }

bool range_gen::first()
{
	if (list_p) {
		it = list_p->begin();
		if (it == list_p->end()) {
			return false;
		}

		local->set(lvar, *it);
		return true;
	}
	else {
		curr = start;
		if (is<TYPE_NIL>(curr))		// nil~nil case
			return false;

		local->set(lvar, curr);
		return true;
	}
}

bool range_gen::next()
{
	if (list_p) {
		++it;

		if (it == list_p->end())
			return false;

		local->set(lvar, *it);
		return true;
	}
	else {
		if (reverse) {
			curr = curr - step;
			if (!is<TYPE_NIL>(end) && curr < end)
				return false;
		}
		else {
			curr = curr + step;
			if (!is<TYPE_NIL>(end) && curr > end)
				return false;
		}

		local->set(lvar, curr);
		return true;
	}
}




orcaSbf::orcaSbf() : m_eval(-1), m_done(false) 
{
	m_timestamp = 0;
}

orcaSbf::orcaSbf(void* vp) : m_eval(-1), m_done(false), orcaList(vp) 
{
	m_timestamp = 0;
}

orcaSbf::~orcaSbf()
{ 
	vector<range_gen>::iterator vi = m_range.begin();
	for (;vi!=m_range.end();++vi) {
		if ((*vi).list_p) 
			(*vi).list_p->rc_dec();
	}

	m_local->decrease(false);
	delete m_local;
	if (is_interactive() || is_eval()) {
		free(m_code);
	}
}

orcaObject* orcaSbf::v_clone() 
{
	orcaList* lp = new orcaList();
	
	for(int i=0; i<=m_eval; i++) {
		lp->push_back(at(i));
	}

	return lp;
}


void orcaSbf::set_result(char* code)
{
	m_result = code;
}

void orcaSbf::set_code(char* code)
{
	m_code = code;
}

void orcaSbf::set_vm(orcaVM* vm)
{
	m_vm = vm;
	orcaData* lp = vm->m_local->lp;
	int size = lp[IDX_CURSIZE].i();

	m_local = new orcaLocal(size + 256);

	m_local->increase(size);
	for(int i=0; i<size; i++) {
		if (i==IDX_GC) 
			m_local->set(i, 0);
		else
			m_local->set(i, lp[i]);
	}
}


// internal
orcaData& orcaSbf::at(int idx)
{
	if (evaluate(idx) == false) {
		if (!m_done) {
			throw orcaException(NULL, "orca.index", "out of range");
		}
	}

	return orcaList::at(idx);
}

orcaListIter orcaSbf::begin() 
{
	orcaListIter it(this);
	evaluate(0);

	if (m_value.empty()) {
		it.set_idx(-1);
	}
	else {
		it.set_idx(0);
	}

	return it;
}

orcaListIter orcaSbf::end() 
{
	orcaListIter it(this);
	it.set_idx(-1);
	return it;
}

int orcaSbf::size()
{
	for (int i=0; i<m_range.size(); i++) {
		if (is<TYPE_NIL>(m_range[i].start) || 
			is<TYPE_NIL>(m_range[i].end)) 
		{
			return -1;
		} 
	}

	while(evaluate(m_eval+1));
	return m_value.size();
}

bool orcaSbf::eof(int at)
{
	if (m_done) {
		if (at > m_eval) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return !evaluate(at);
	}
}


bool orcaSbf::evaluate(int at)
{
	if (at < 0) {
		if (size() < 0) {
			return false;
		}
	}

	if (at < m_eval) {
		return true;
	}

	if (m_done) {
		return false;
	}

	if (m_eval < 0) {
		if (!first()) {
			m_done = true;
			return false;
		}

		orcaData d = result();
		m_eval = 0;
		m_value.push_back(d);
		d.rc_inc();
	}

	while(m_eval < at) {
		if (!next()) {
			m_done = true;
			return false;
		}

		orcaData d = result();
		m_eval++;
		m_value.push_back(d);
		d.rc_inc();
	}

	return true;
}

orcaData orcaSbf::result()
{
	orcaLocal* local_org = m_vm->m_local;

	m_vm->m_local = m_local;
	m_vm->exec_code(m_code, m_result);
	m_vm->m_local = local_org;

	orcaData r = m_vm->m_stack->pop();
	return r;
}

int orcaSbf::get_eval()
{
	return m_eval;
}

void orcaSbf::push_gen(int var, orcaData start, orcaData end, orcaData step)
{
	orcaData d = 0;
	if (step <= d) {
		throw orcaException(NULL, "orca.list", "plus step is required in SBF");
	}
 
	range_gen rg(var, m_local, start, end, step);
	m_range.push_back(rg);
}

void orcaSbf::push_gen(int var, orcaList* op)
{
	range_gen rg(var, m_local, op);
	m_range.push_back(rg);
}

void orcaSbf::push_rule(char* addr)
{
	m_rule.push_back(addr);
}


bool orcaSbf::check()
{
	for(int i=0; i<m_rule.size(); i++) {

		orcaLocal* local_org = m_vm->m_local;
		m_vm->m_local = m_local;
		m_vm->exec_code(m_code, m_rule[i]);
		m_vm->m_local = local_org;

		orcaData r = m_vm->m_stack->pop();

		if (is<TYPE_BOOL>(r)) {
			if (!r.i()) {
				return false;
			}

			continue;
		}
		else if (is<TYPE_INT>(r)) {
			if (!r.i()) {
				return false;
			}

			continue;
		}

		continue;
	}

	return true;
}

bool orcaSbf::first()
{
	for(int i=0; i<m_range.size(); i++) {
		if (!m_range[i].first()) {
			return false;
		}
	}

	if(!check()) {
		return next();
	}

	return true;
}

bool orcaSbf::inc(int i)
{
	if (i<0) {
		return false;
	}

	do {
		if (!m_range[i].next()) {
			m_range[i].first();

			if (!inc(i-1)) {
				return false;
			}
		}
		
		return true;

	} while (true);
}

bool orcaSbf::next()
{
	do {
		if (!inc(m_range.size()-1)) {
			return false;
		}
	} while(!check());

	return true;
}


void orcaSbf::string_(orcaVM* vm, string& str) 
{
	for (int i=0; i<m_range.size(); i++) {
		if (is<TYPE_NIL>(m_range[i].start) || 
			is<TYPE_NIL>(m_range[i].end)) 
		{
			evaluate(10);
			orcaListIter li = begin();
			str += "[ ";

			for (int j=0; j<m_eval; j++) {
				if (is<TYPE_STR>(*li)) str += "'";
				(*li).string_(vm, str);
				if (is<TYPE_STR>(*li)) str += "'";

				++li;
				if (li!=end()) str+= ",";
			}

			str += " ... ]";
			return;
		} 
	}

	size();
	orcaList::string_(vm, str);
}


orcaData orcaSbf::slice(int start, int end, bool include_right) 
{
	if (start < 0 || end < 0) {
		if (size() < 0) {
			throw orcaException(NULL, "orca.index", "out of range");
		}
	}

	evaluate(end);
	return orcaList::slice(start, end, include_right);
}


