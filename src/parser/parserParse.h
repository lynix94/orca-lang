/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserParse.h - manage parse statement

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

//#define _PARSE_DEBUG_

#ifndef _DEF_PARSER_PARSE
#define _DEF_PARSER_PARSE

#include <string>
#include <map>
#include <set>
#include <stdio.h>

#include "parserCode.h"
#include "orca_opcode.h"

#define BNF_TERMINAL	0	
#define BNF_NONTERMINAL 1	
#define BNF_ACTION		2
#define BNF_WS			3

struct bnf;



// bnf* left : vector<bnf*> right
struct rule
{
	rule(bnf* left);
	void push_bnf(bnf* b);
	void dump(int idx=-1);

	int ruleid;
	bnf* left;
	vector<bnf*> right;

	static int m_ruleid;
	static vector<rule*> m_rules;

	set<bnf*> ahead_terminals(int i);
};

// name : vector<rule*>vules
struct bnf
{
	bnf(int type, const string& name, int nth);
	~bnf();

	rule* current_rule();
	void add_rule();
	void dump();
	
	string name;
	int type;
	int nth;
	bool is_re;
	int node_num;
	
	set<bnf*> first_terminals();
	vector<rule*> rules;
	set<bnf*> firsts;

	set<bnf*> new_ahead;
};

struct state
{
	state() : transited(false) {}
	state(int st, rule* rp, int i, int f) 
		  : s(st), r(rp), idx(i), from(f), by(NULL), 
			transited(false),
			kernel(false), 
			transit(NULL) 
			{}

	int s;
	int from;
	rule* r;
	int idx;
	bnf* by;

	bnf* next();
	bnf* next(int i);
	bnf* before(int i=1);

	// for ahead
	void push_ahead(bnf* b);
	void merge_ahead(state* s);
	set<bnf*> ahead_terminals();
	set<bnf*> ahead;
	state* transit;
	bool transited;
	bool kernel;

	// for debug
	void dump();
	void dump_ahead();

}; 

// result parsing tables
struct table_item
{
	table_item(int pfrom, bnf* pb, char ptype, int pto) 
		: from(pfrom), b(pb), type(ptype), to(pto) {}

	int from; // from state
	bnf* b;		// next bnf
	char type;	// action type, s, g, a, r
	int to;	// to state

	state* sp;

	void dump()
	{
		printf("(%c:%s) %d -> %d\n", type, b->name.c_str(), from, to);
	}
}; 

class parserParse
{
public:
	typedef vector<state*> state_t;
	typedef multimap<int, state*> state_group_t;

	parserParse();

	// make table by parser.y
	// it makes table items
	// and invokes make_parsing_table
	void make_table();

	// by parser.y	to setup bnfs
	void do_parse_init();
	void do_parse(vector<char>& def);
	void cleanup();

	bnf* get_term_bnf(const string& name, bool is_re = false);
	bnf* get_nonterm_bnf(const string& name);
	bnf* get_action_bnf(int rights);

	bnf* current_bnf();
	void set_current_bnf(bnf* b);

	void dump();

private:
	// same in states
	int find_same_state(int sn, rule* r, int idx);
	int find_same_shift_goto(rule* r, int idx);

	// dup in m_items
	int find_dup_shift_goto(int sn, bnf* b);
	int find_dup_action(int sn, bnf* b);

	void make_transit(state* s);
	void make_one_state(state* s);
	void make_ahead();
	void make_closure(state* s);
	void make_closure_bnf(state* s);
	void make_parsing_table(map<string, bnf*>& cols);

void item_dump()
{
	for (int i=0; i<m_items.size(); i++) {
printf("%d: ", i);
		m_items[i].dump();
	}
}

private:
	bnf* m_current;
	bnf* m_start;
	int m_idx_2pass;

	// after parser.y
	map<string, bnf*> m_sb;
	vector<bnf*> m_ib; // for action

	// after make_table
	int m_max_state;
	state_t m_state;
	state_group_t m_state_group;

	vector<table_item> m_items;

	// after make_table -> make_parsing_table
	vector<vector<pair<char, short> > > m_table;
};

extern parserParse* g_parse;

#endif



