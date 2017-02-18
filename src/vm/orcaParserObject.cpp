/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaParserObject.cpp - parse object

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/
//#define _VM_DEBUG_
#include "orca_common.h"

#include "orcaParserObject.h"

#include <boost/regex.hpp>

using namespace boost;

#include "orcaStack.h"
#include "orcaException.h"

#include "parserParse.h"


void orcaParserObject::push_str(const char* str, int i)
{
	pair<int, term_str> p;
	p.first = strlen(str);
	p.second.str = str;
	p.second.nth = i;
	p.second.type = BNF_TERMINAL;
	
	m_term_str.insert(p);
	m_term_i_name[i] = string("'") + str + "'";
}

void orcaParserObject::push_str_ws(const char* str, int i)
{
	pair<int, term_str> p;
	p.first = strlen(str);
	p.second.str = str;
	p.second.nth = i;
	p.second.type = BNF_WS;
	
	m_term_str.insert(p);
}

void orcaParserObject::push_re(const char* str, int i)
{
	term_re t;
	t.re = str;
	t.nth = i;
	t.type = BNF_TERMINAL;

	m_term_re.push_back(t);
	m_term_i_name[i] = string("r'" )+ str + "'";
}

void orcaParserObject::push_re_ws(const char* str, int i)
{
	term_re t;
	t.re = str;
	t.nth = i;
	t.type = BNF_WS;

	m_term_re.push_back(t);
}

void orcaParserObject::push_nonterminal(const char* str, int i)
{
	term_str p;
	p.str = str;
	p.nth = i;
	p.type = BNF_NONTERMINAL;
	m_term_nt.push_back(p);
}

void orcaParserObject::new_rule(short left, short right)
{
	m_rules.push_back(pair<short, short>(left, right));
}

void orcaParserObject::resize_table(int width, int depth)
{
	m_table.resize(depth);
	for (int i=0; i<depth; i++) {
		m_table[i].resize(width);
		for (int j=0; j<width; j++) {
			m_table[i][j].first = 'x';
			m_table[i][j].second = 0;
		}
	}
}

void orcaParserObject::set_table(int i, int j, char c, short to)
{
	m_table[i][j].first = c;
	m_table[i][j].second = to;
}

void orcaParserObject::resize_action(int size)
{
	m_actions.resize(size);
}

void orcaParserObject::set_action(int idx, orcaObject* op)
{
	m_actions[idx] = op;
}

int orcaParserObject::get_action_size()
{
	return m_actions.size();
}

int orcaParserObject::reduce(int n, orcaData& d)
{
	pair<short, short> p = m_rules[n];
	short left = p.first;
	short right = p.second;

	d = m_pstack[m_pstack.size()-1].d;
	for (int i=0; i<right; i++) {
		m_pstack.pop_back();
	}

	m_state = m_pstack[m_pstack.size()-1].state;
#ifdef _VM_DEBUG_
	printf("reduce: "); dump();
#endif
	return left;
}

// parsing
orcaData orcaParserObject::parse(string& input)
{
	m_input = input;
	m_idx = 0;
	m_state = 0;
	m_pstack.clear();

	PRINT1("## parse start: %s\n", input.c_str());
	pstate ps;
	ps.bnf = -1;
	ps.state = m_state = 0;
	m_pstack.push_back(ps);

	int token;
	int ahead;
	string token_str;
	string ahead_str = lexer(&ahead);

	do {
		token_str = ahead_str;
		token = ahead;
		ahead_str = lexer(&ahead);
	
		if (token < 0) {
			printf("invalid token: %s\n", m_input.substr(m_idx).c_str());
			return NIL;
		}

		orcaData reduced_d = NIL;
retry:

		pair<char, short> p = m_table[m_state][token];
		char action = p.first;
		short to = p.second;
		char next_action;

		PRINT4("table: %d-%d, action: %c%d\n", m_state, token, action, to);

		switch (action)
		{
		case 's':
			ps.bnf = token;
			ps.state = to;
			ps.d = token_str;
			m_pstack.push_back(ps);
			m_state = to;
#ifdef _VM_DEBUG_
			printf("shift: "); dump();
#endif
			next_action = m_table[m_state][ahead].first;
			if (next_action == 'r' || next_action == 'a') {
				token = ahead;
				goto retry;
			}
			break;

		case 'g':
			ps.bnf = token;
			ps.state = to;
			ps.d = reduced_d;
			m_pstack.push_back(ps);
			m_state = to;

#ifdef _VM_DEBUG_
			printf("goto: "); dump();
#endif
			next_action = m_table[m_state][ahead].first;
			if (next_action == 'r' || next_action == 'a') {
				token = ahead;
				goto retry;
			}
			break;

		case 'r':
			token = reduce(to, reduced_d);
			goto retry;
			break;

		case 'a': {
			// do action
			int width = m_table[0].size();
			int action = m_table[m_state][width-1].second;
			int params = m_table[m_state][width-1].first;

			int start = m_pstack.size() - params;
			m_vm->m_stack->push(m_actions[action]);
			for (int i=0; i<params; i++) {
				m_vm->m_stack->push(m_pstack[start+i].d);
			}

			m_vm->call(params);
			orcaData ret = m_vm->m_stack->pop();

			// and, go
			ps.bnf = token;
			ps.state = to;
			ps.d = ret;
			m_pstack.push_back(ps);
#ifdef _VM_DEBUG_
			printf("action: "); dump();
#endif
			m_state = to;
			goto retry;
			break;
		  }
		case 'q':
			// fix later
			if (m_state == 0 && token == 0) {
				return reduced_d;
			}

			return m_pstack[m_pstack.size()-1].d;
			break;

		case 'x':
		  {
			string expected = "";
			for (int i=0; i<m_table[m_state].size(); i++) {
				pair<char, short> p = m_table[m_state][i];
				char action = p.first;

				if (action != 'x') {
					map<int, string>::iterator mi = m_term_i_name.find(i);
					if (mi != m_term_i_name.end()) {
						expected += mi->second + " ";
					}
				}
			}
			
	
			throw orcaException(get_current_vm(), "orca.parse", 
				string("unexpected '") + token_str + "' expected " + expected);
			break;
		  }

		default:
			break;
		}
	} while(true);

	return NIL;
}

orcaData orcaParserObject::operator()(orcaVM* vm, int n)
{
	if (n<1) vm->need_param();

	string str = vm->get_param(0).String();
	orcaData ret = parse(str);

	return ret;
}

string orcaParserObject::lexer(int* tok)
{
retry:
	int nth = -1;
	int len = 0;
	int type;

	// fine first longest match in string
	multimap<int, term_str>::reverse_iterator mi = m_term_str.rbegin();
	for (; mi != m_term_str.rend(); ++mi) {
		if (strncmp(m_input.c_str() + m_idx, mi->second.str.c_str(), 
			mi->second.str.length()) == 0) 
		{
			len = mi->second.str.length();
			nth = mi->second.nth;
			type = mi->second.type;
			break;
		}
	}

	// then find longest match in regex
	for (int i=0; i<m_term_re.size(); i++) {
		match_results<string::const_iterator> mr;
		string::const_iterator start, end; 
		start = m_input.begin() + m_idx;
		end = m_input.end();

		if ( regex_search(start, end, mr, m_term_re[i].re) ) {
			if (mr[0].first == m_input.begin() + m_idx) {
				int re_len = mr[0].second - mr[0].first;
				if (re_len > len) {
					len = re_len;
					nth = m_term_re[i].nth;
					type = m_term_re[i].type;
				}
			}
		}
	}

	if (nth == -1) {
		if (m_idx >= m_input.length()) {
			// set eof
			nth = 1;
		}

		*tok = nth;
		return "";
	}

	PRINT2(" lex found: %s, %d\n", m_input.substr(m_idx, len).c_str(), nth);
	string tok_str = m_input.substr(m_idx, len);
	m_idx += len;

	if (type == BNF_WS) {
		goto retry;
	}

	*tok = nth;
	return tok_str;
}

// debug
void orcaParserObject::dump()
{
	for (int i=0; i<m_pstack.size(); i++) {
		printf("(%d, %d)", m_pstack[i].bnf, m_pstack[i].state);
	}
	printf("\n");
}



