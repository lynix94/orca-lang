/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserParse.cpp - manage parse statement

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <stdio.h>

#include "parserParse.h"
#include "orca_opcode.h"
#include "parserOP.h"

//#define _PARSE_DEBUG_

static bnf* g_term_eof = NULL;
static set<bnf*> g_ahead_eof;

parserParse s_parse;
parserParse* g_parse = &s_parse;

int rule::m_ruleid;
vector<rule*> rule::m_rules;

static void ahead_dump(set<bnf*> ahead)
{
	set<bnf*>::iterator it = ahead.begin();
	for (; it != ahead.end(); ++it) {
		printf("%s, ", (*it)->name.c_str());
	}
}


rule::rule(bnf* left)/*{{{*/
{
	this->left = left;
	ruleid = m_ruleid++;
	m_rules.push_back(this);
}
/*}}}*/

void rule::push_bnf(bnf* b)/*{{{*/
{
	right.push_back(b);
}
/*}}}*/

void rule::dump(int idx)/*{{{*/
{
	vector<bnf*>::iterator vi = right.begin();
	printf("r:%d %s :", ruleid, left->name.c_str());

	int i;
	for(i=0; vi != right.end(); ++vi, i++) {
		if (i==idx) printf(" . ");
		printf("%s ", (*vi)->name.c_str());
	}
	if (i==idx) printf(" . ");
	printf("\n");
}
/*}}}*/

set<bnf*> rule::ahead_terminals(int i)/*{{{*/
{
	if (right.size() > i) {
		return right[i]->first_terminals();
	}
	else {
		set<bnf*> sb;
		return sb;
	}
}
/*}}}*/




void state::dump_ahead()/*{{{*/
{
	printf(" [ ");
	set<bnf*>::iterator it = ahead.begin();
	for (; it != ahead.end(); ++it) {
		printf("%s, ", (*it)->name.c_str());
	}
	printf(" ] ");
}
/*}}}*/

void state::push_ahead(bnf* b)/*{{{*/
{
	ahead.insert(b);
}
/*}}}*/

void state::merge_ahead(state* s)/*{{{*/
{
	set<bnf*>& bp = s->ahead;
	ahead.insert(bp.begin(), bp.end());
}
/*}}}*/

bnf* state::next()/*{{{*/
{
	if (idx >= r->right.size()) return NULL;
	return r->right[idx];
}
/*}}}*/

bnf* state::next(int i)/*{{{*/
{
	if (idx + i >= r->right.size()) return NULL;
	return r->right[idx + i];
}
/*}}}*/

bnf* state::before(int i)/*{{{*/
{
	if ((idx-i) < 0) return NULL;
	return r->right[idx-i];
}
/*}}}*/

void state::dump()/*{{{*/
{
	if (kernel) printf("[*]");
	printf("state %d, idx: %d, (from: %d)", s, idx, from);
	dump_ahead();
	r->dump(idx);

	if (transit)
		printf("		transit: s(%d), r(%d)\n", transit->s, transit->r->ruleid);
}
/*}}}*/

set<bnf*> state::ahead_terminals()/*{{{*/
{
	return r->ahead_terminals(idx + 1);
}
/*}}}*/



bnf::bnf(int type, const string& name, int nth)/*{{{*/
{
	this->type = type;
	this->name = name;
	this->nth = nth;
}
/*}}}*/

bnf::~bnf()/*{{{*/
{
	vector<rule*>::iterator it = rules.begin();
	for (; it != rules.end(); ++it) {
		delete (*it);
	}
}
/*}}}*/

rule* bnf::current_rule()/*{{{*/
{
	return rules[rules.size()-1];
}
/*}}}*/

void bnf::add_rule()/*{{{*/
{
	rules.push_back(new rule(this));
}
/*}}}*/

void bnf::dump() /*{{{*/
{
	vector<rule*>::iterator vi = rules.begin();
	for(; vi != rules.end(); ++vi) {
		(*vi)->dump();
	}
}
	/*}}}*/

set<bnf*> bnf::first_terminals() /*{{{*/
{
	if (firsts.size() > 0) {
		return firsts;
	}

	if (type == BNF_TERMINAL) {
		firsts.insert(this);
	}
	else if (type == BNF_NONTERMINAL) {
		for (int i=0; i<rules.size(); i++) {
			rule* rp = rules[i];
			if (rp->right[0] == this) continue;
			set<bnf*> fp = rp->right[0]->first_terminals();
			if (fp.size() > 0) {
				firsts.insert(fp.begin(), fp.end());
			}
		}

		return firsts;
	}

	// action, return empty set
	return firsts;
}
/*}}}*/


parserParse::parserParse() { }

void parserParse::cleanup()/*{{{*/
{
	m_items.clear();

	state_t::iterator si = m_state.begin();
	for (; si != m_state.end(); ++si) {
		delete (*si);
	}
	m_state.clear();
	m_state_group.clear();

	m_max_state = 0;

	map<string, bnf*>::iterator it = m_sb.begin();
	for (; it != m_sb.end(); ++it) {
		delete (*it).second;
	}
	m_sb.clear();

	vector<bnf*>::iterator vi = m_ib.begin();
	for (; vi != m_ib.end(); ++vi) {
		delete (*vi);
	}
	m_ib.clear();
}
/*}}}*/

bnf* parserParse::get_term_bnf(const string& name, bool is_re) /*{{{*/
{
	if (m_sb.find(name) == m_sb.end()) {
		int nth = m_sb.size();
		m_sb[name] = new bnf(BNF_TERMINAL, name, nth);
		m_sb[name]->is_re = is_re;
	}

	return m_sb[name];
}
/*}}}*/

bnf* parserParse::get_nonterm_bnf(const string& name) /*{{{*/
{
	if (m_sb.find(name) == m_sb.end()) {
		bool first = false;
		if (m_sb.size() == 0) { // first case
			first = true;

			// add dummy rule
			bnf* bp = new bnf(BNF_NONTERMINAL, "@stmt_done", 0);
			m_sb["@stmt_done"] = bp;
			m_start = bp;

			g_term_eof = get_term_bnf("@EOF");
			if (g_ahead_eof.size() == 0) {
				g_ahead_eof.insert(g_term_eof);
			}
		}

		int nth = m_sb.size();
		bnf* bp = new bnf(BNF_NONTERMINAL, name, nth);
		m_sb[name] = bp;

		if (first) {
			m_start->add_rule();
			m_start->current_rule()->push_bnf(bp);
		}
	}

	return m_sb[name];
}
/*}}}*/

bnf* parserParse::get_action_bnf(int rights)/*{{{*/
{
	int nth = m_ib.size();
	bnf* bp = new bnf(BNF_ACTION, "@ACTION", nth);
	bp->node_num = rights;
	m_ib.push_back(bp);
	
	return bp;
}
/*}}}*/

bnf* parserParse::current_bnf()/*{{{*/
{
	return m_current;
}
/*}}}*/

void parserParse::set_current_bnf(bnf* b)/*{{{*/
{
	m_current = b;
}
/*}}}*/

int parserParse::find_same_shift_goto(rule* r, int idx)/*{{{*/
{
	for (int i=0; i<m_state.size(); i++) {
		if ((m_state[i]->r == r) &&
			(m_state[i]->idx == idx)) 
		{
			return i;
		}
	}

	return -1;
}
/*}}}*/

int parserParse::find_dup_shift_goto(int sn, bnf* b)/*{{{*/
{
	for (int i=0; i<m_items.size(); i++) {
		if ((m_items[i].from == sn) &&
			(m_items[i].b == b))
		{
			return m_items[i].to;
		}
	}

	return -1;
}
/*}}}*/

int parserParse::find_dup_action(int sn, bnf* b)/*{{{*/
{
	for (int i=0; i<m_items.size(); i++) {
		if ((m_items[i].from == sn) &&
			(m_items[i].b->type == BNF_ACTION))
		{
			return m_items[i].to;
		}
	}

	return -1;
}
/*}}}*/

int parserParse::find_same_state(int sn, rule* r, int idx)/*{{{*/
{
// fix more efficient
	for (int i=0; i<m_state.size(); i++) {
		if ((m_state[i]->s == sn) &&
			(m_state[i]->r == r) &&
			(m_state[i]->idx == idx)) 
		{
			return i;
		}
	}

	return -1;
}
/*}}}*/

void parserParse::dump()/*{{{*/
{
	map<string, bnf*>::iterator it = m_sb.begin();
	for(; it != m_sb.end(); ++it) {
		(*it).second->dump();
	}

	for (int i=0; i<m_state.size(); i++) {
		m_state[i]->dump();
	}
}
/*}}}*/

void parserParse::make_parsing_table(map<string, bnf*>& cols)/*{{{*/
{
	int depth = m_max_state + 1;
	int width = cols.size() + 1;

	m_table.resize(depth);
	for (int i=0; i<depth; i++) {
		m_table[i].resize(width);
		for (int j=0; j<width-1; j++) {
			m_table[i][j].first = 'x';
			m_table[i][j].second = 0;
		}	
	}

	for (int i=0; i<m_items.size(); i++) {
		int row = m_items[i].from;
		int col = m_items[i].b->nth;
		char type = m_items[i].type;
		int to = m_items[i].to;

		if (type == 'a') { // nth of action means executable object order
			col = 0;
		}

		if (m_table[row][col].first != 'x') {
		//	printf("conflict at: %d, %d\n", row, col);
		}

		if (type == 's') {
			m_table[row][col].first = type;
			m_table[row][col].second = to;
		}
		else if (type == 'g') {
			m_table[row][col].first = type;
			m_table[row][col].second = to;
		}
		else if (type == 'a') {
			m_table[row][col].first = type;
			m_table[row][col].second = to;
		}
		else { // 'r'
			set<bnf*>::iterator it = m_items[i].sp->ahead.begin();
			for (; it!=m_items[i].sp->ahead.end(); ++it) {
				bnf* b = (*it);
				int ahead = b->nth;
				m_table[row][ahead].first = type;
				m_table[row][ahead].second = to;
			}
		}

		if (type == 'a') {
			for (int j=0; j<width-1; j++) {
				if (m_table[row][j].first == 'x') {
					m_table[row][j].first = type;
					m_table[row][j].second = to;
				}

				if (type == 'a') {
					m_table[row][width-1].first = m_items[i].b->node_num;
					m_table[row][width-1].second = m_items[i].b->nth;
				}
			}
		}
	}

	if (m_table[0][0].first == 'x')
			m_table[0][0].first = 'q';	// END condition

#ifdef _PARSE_DEBUG_/*{{{*/
	vector<string> columns;
	columns.resize(cols.size());
	map<string, bnf*>::iterator it = cols.begin();
	for(; it != cols.end(); ++it) {
		columns[(*it).second->nth] = (*it).first.c_str();
	}

	printf("\t");
	for (int j=0; j<width-1; j++) {
		printf("%s,\t", columns[j].c_str());
	}
	printf("\n");

	for (int i=0; i<depth; i++) {
		printf("%d:\t", i);
		for (int j=0; j<width; j++) {
			if (j == width-1) {
				printf("%d:%d\t", m_table[i][j].first, m_table[i][j].second);
			}
			else {
				printf("%c%d\t", m_table[i][j].first, m_table[i][j].second);
			}
		}
		printf("\n");
	}
#endif
/*}}}*/
}
/*}}}*/

#include <stdlib.h>

void parserParse::make_transit(state* sp)/*{{{*/
{
#ifdef _PARSE_DEBUG_
	printf("Make transit: %d\n", sp->s);
	sp->dump_ahead();
#endif
	int from = sp->s;

	if (sp->next() == NULL) {
#ifdef _PARSE_DEBUG_
		printf("REDUCE(%s): %d-%d\n", sp->before()->name.c_str(), sp->s, sp->r->ruleid);
		sp->dump();
#endif
		int idx = 1;
		if (sp->before(1)==NULL) {
			return;
		}
		if (sp->before(1)->type == BNF_ACTION) {
			idx = 2;
		}

		table_item ti(sp->s, sp->before(idx), 'r', sp->r->ruleid);
		ti.sp = sp;
		m_items.push_back(ti);
		return;
	}

	state* s = new state();
	*s = *sp;
	bool find = false;
	bool dup_find = false;
	int to = m_max_state + 1;
	int type = s->next()->type;
	int ret;

	if (type == BNF_TERMINAL) {
		if ((ret = find_dup_shift_goto(s->s, s->next())) >= 0) {
			to = ret;
			dup_find = true;
		}
		else if ((ret = find_same_shift_goto(s->r, s->idx+1)) >= 0) {
			to = m_state[ret]->s;
			find = true;
			sp->transit = m_state[ret];
		}


#ifdef _PARSE_DEBUG_
		printf("SHIFT(%s): %d-%d\n", s->next()->name.c_str(), from, to);
		s->dump();
#endif
		table_item ti(from, s->next(), 's', to);
		ti.sp = s;
		m_items.push_back(ti);

		if (to >= m_max_state) m_max_state = to;

	}
	else if (type == BNF_NONTERMINAL) {
		if ((ret = find_dup_shift_goto(s->s, s->next())) >= 0) {
			to = ret;
			dup_find = true;
		}
		else if ((ret = find_same_shift_goto(s->r, s->idx+1)) >= 0) {
			to = m_state[ret]->s;
			find = true;
			sp->transit = m_state[ret];
		}

#ifdef _PARSE_DEBUG_
		printf("GOTO(%s): %d-%d\n", s->next()->name.c_str(), from, to);
		s->dump();
#endif
		table_item ti(from, s->next(), 'g', to);
		ti.sp = s;
		m_items.push_back(ti);
		if (to >= m_max_state) m_max_state = to;
	}
	else {
#ifdef _PARSE_DEBUG_
		printf("ACTION(%s): %d-%d\n", s->next()->name.c_str(), from, to);
		s->dump();
#endif
		if ((ret = find_dup_action(s->s, s->next())) >= 0) {
			to = ret;
		}

		table_item ti(from, s->next(), 'a', to);
		ti.sp = s;
		m_items.push_back(ti);
		if (to >= m_max_state) m_max_state = to;
	}

	if (find) return;

	if (dup_find) {
		if (find_same_state(to, s->r, s->idx + 1) >= 0) {
			return;
		}
	}

	sp->transit = s;
	s->from = from;
	s->s = to;
	s->idx++;
//	s->merge_ahead(sp);
	make_one_state(s);
}
/*}}}*/

void parserParse::make_one_state(state* s)/*{{{*/
{
#ifdef _PARSE_DEBUG_
	printf("####  make one state : %d####\n", s->s);
	s->dump();
#endif

	int start = m_state.size();
	s->kernel = true;
	make_closure(s);

#ifdef _PARSE_DEBUG_
	printf("####  make one state done: %d####\n", s->s);
	s->dump();
#endif
	
	// todo : fix more efficienty
	for (int i=0; i<m_state.size(); i++) {
		if (m_state[i]->s == s->s && m_state[i]->transited == false) {
			make_transit(m_state[i]);
			m_state[i]->transited = true;
		}
	}

#ifdef _PARSE_DEBUG_
	printf("####  make one state complete done: %d####\n", s->s);
	s->dump();
#endif
}
/*}}}*/

void parserParse::make_ahead()/*{{{*/
{
	state_group_t::iterator it = m_state_group.begin();
	for (; it != m_state_group.end(); ++it) {
		state* sp = it->second;

		if (sp->kernel && sp->next()) {
#ifdef _PARSE_DEBUG_
	printf("####  make ahead of ####\n");
	sp->dump();
#endif
			state_group_t::iterator si = m_state_group.find(sp->s);
			while (si != m_state_group.end() && si->first == sp->s) {
				state* cp = si->second;
				set<bnf*> aheads = cp->ahead_terminals();
				cp->next()->new_ahead.insert(aheads.begin(), aheads.end());
				
				state_group_t::iterator sub_si = m_state_group.find(sp->s);
				while (sub_si != m_state_group.end() && sub_si->first == sp->s) {
					state* sub_cp = sub_si->second;
					if (sub_cp->r->left->new_ahead.size()) {
						sub_cp->ahead.insert(sub_cp->r->left->new_ahead.begin(), sub_cp->r->left->new_ahead.end());
					}

					++sub_si;
				}
					
				++si;
			} // while (si ...

		} // if (sp...

	} // for (; ..


	for (int i=0; i<m_state.size(); i++) {
		state* sp = m_state[i];
		if (sp->kernel && sp->next()) {
			
#ifdef _PARSE_DEBUG_
	printf("####  make ahead done ####\n");
	sp->dump();
#endif
		}
	}


	bool cont = false;
	do {
		cont = false;
		state_group_t::iterator it = m_state_group.begin();
		for (; it != m_state_group.end(); ++it) {
			state* sp = it->second;
			state_group_t::iterator si = m_state_group.find(sp->s);
			while (si != m_state_group.end() && si->first == sp->s) {
				state* cp = si->second;
				state* tp = cp->transit;
				if (tp) {
					int old = tp->ahead.size();
					tp->merge_ahead(sp);
					if (old < tp->ahead.size()) {
						cont = true;
					}
				}
				++si;
			}
		}
	} while (cont);
}
/*}}}*/

void parserParse::make_closure_bnf(state* sp)/*{{{*/
{
	int ret;
	bnf* b = sp->r->right[sp->idx];

	for(int i=0; i<b->rules.size(); i++) {
		state* s = new state(sp->s, b->rules[i], 0, sp->from);

		if ((ret = find_same_state(s->s, b->rules[i], 0)) < 0) {
#ifdef _PARSE_DEBUG_
			printf("      push_rule_bnf: state: %d, idx: %d, (from: %d)\t", s->s, 0, s->from);
			b->rules[i]->dump();
			s->dump_ahead();
#endif
			m_state.push_back(s);
			m_state_group.insert(pair<int, state*>(s->s, s));

			if (b->rules[i]->right[0]->type == BNF_NONTERMINAL) {
				make_closure_bnf(s);
			}
		}
	}
}
/*}}}*/

void parserParse::make_closure(state* s)/*{{{*/
{
	int ret;
	if ((ret = find_same_state(s->s, s->r, s->idx)) < 0) {
		m_state.push_back(s);
		m_state_group.insert(pair<int, state*>(s->s, s));
#ifdef _PARSE_DEBUG_
		printf("      push_rule: state: %d, idx: %d, (from: %d)\t", s->s, s->idx, s->from);
		s->r->dump();
		//s->dump_ahead();
#endif

		if (s->s >= m_max_state) m_max_state = s->s;

		if (s->r->right.size() > s->idx && 
			s->r->right[s->idx]->type == BNF_NONTERMINAL) 
		{
			make_closure_bnf(s);
		}
	}
}
/*}}}*/

void parserParse::make_table()/*{{{*/
{
#ifdef _PARSE_DEBUG_
	map<string, bnf*>::iterator mi = m_sb.begin();
	for (; mi != m_sb.end(); ++mi) {
		printf("## %s\n", mi->first.c_str()); 
		mi->second->dump();
		set<bnf*> sp = mi->second->first_terminals();
		if (sp.size() > 0) {
			set<bnf*>::iterator si = sp.begin();
			for (; si != sp.end(); ++si) {
				printf(">%s\n", (*si)->name.c_str());
			}
		}
		printf("\n");
	}
#endif

	state* st = new state(0, m_start->rules[0], 0, -1);

	make_one_state(st);
	st->push_ahead(get_term_bnf("@EOF"));

	make_ahead();
	
	

#ifdef _PARSE_DEBUG_
	item_dump();
	dump();
#endif
	make_parsing_table(m_sb);
}
/*}}}*/

void parserParse::do_parse_init()/*{{{*/
{
	cleanup();
	rule::m_ruleid = 0;
	rule::m_rules.clear();

	code_top->push_char(OP_PUSH_LVAR);
	code_top->push_short(0);

	code_top->push_char(OP_PARSE_INIT);
	m_idx_2pass = code_top->size();
	code_top->increase(sizeof(int));
}
/*}}}*/

void parserParse::do_parse(vector<char>& def)/*{{{*/
{
	code_top->set_int(code_top->size(), m_idx_2pass);
	int depth = m_max_state+1;
	int width = m_sb.size();
	int rules = rule::m_rules.size();

	def.push_back(OP_PARSE);
	copy((char*)&width, (char*)(&width+1), back_inserter(def));
	copy((char*)&depth, (char*)(&depth+1), back_inserter(def));
	copy((char*)&rules, (char*)(&rules+1), back_inserter(def));

	vector<bnf*> vec;
	vec.resize(width);
	map<string, bnf*>::iterator it = m_sb.begin();
	for (; it != m_sb.end(); ++it) 
		vec[it->second->nth] = it->second;

	// terms
	for (int i=0; i<vec.size(); i++) {
		def.push_back(vec[i]->type); 
		if (vec[i]->type == BNF_TERMINAL || vec[i]->type == BNF_WS) {
			def.push_back(vec[i]->is_re); // str or regex
		}

		const char* cp = vec[i]->name.c_str();
		def.push_back(strlen(cp));
		copy(cp, cp + strlen(cp)+1, back_inserter(def));
	}

	// table
	for (int i=0; i<depth; i++) {
		for (int j=0; j<width + 1; j++) {	// 1 for action
			def.push_back(m_table[i][j].first);
			short idx = m_table[i][j].second;
			copy((char*)&idx, (char*)(&idx+1), back_inserter(def));
		}
	}

	// rules
	for (int i=0; i<rules; i++) {
		rule* rp = rule::m_rules[i];
		short rn = rp->left->nth;
		copy((char*)&rn, (char*)(&rn+1), back_inserter(def));
		rn = rp->right.size();
		copy((char*)&rn, (char*)(&rn+1), back_inserter(def));
	}

	// actions
	code_top->push_char(OP_PARSE);
	code_top->push_short(m_ib.size());
	code_top->push_char(OP_RETURN);
}
/*}}}*/

