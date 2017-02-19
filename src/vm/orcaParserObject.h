/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaParserObject.h - parse object

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_PARSER_OBJ
#define _DEF_ORCA_PARSER_OBJ

#include "orcaObject.h"
#include "orcaVM.h"
#include "orcaLocal.h"


class orcaParserObject : public orcaObject
{
public:
	orcaParserObject(orcaVM* vm) : m_vm(vm) { }

	void push_str(const char* str, int i);
	void push_re(const char* str, int i);
	void push_str_ws(const char* str, int i);
	void push_re_ws(const char* str, int i);
	void push_nonterminal(const char* str, int i);
	void new_rule(short left, short right);
	void resize_table(int width, int depth);
	void set_table(int i, int j, char c, short to);
	void resize_action(int size);
	void set_action(int idx, orcaObject* op);
	int get_action_size();
	int reduce(int n, orcaData& d);

	// parse
	orcaData parse(string& input);
	orcaData operator()(orcaVM* vm, int n);
	string lexer(int* tok);

	// debug
	void dump();

private:
	struct term_re
	{
		boost::regex re;
		int nth;
		int type;
	};

	struct term_str
	{
		string str;
		int nth;
		int type;
	};

	// parsing table & rules
	vector<term_re> m_term_re;
	multimap<int, term_str> m_term_str;
	vector<term_str> m_term_nt;

	map<int, string> m_term_i_name;

	vector<vector<pair<char, short> > > m_table;
	vector<pair<short, short> > m_rules;
	vector<orcaObject*> m_actions;
	int m_state;

	// stack
	struct pstate
	{
		int bnf;
		int state;
		orcaData d;
	};

	vector<pstate> m_pstack;

	// input
	string m_input;
	int m_idx;

	orcaVM* m_vm;
};

#endif

