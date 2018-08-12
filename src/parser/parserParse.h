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
#include <sstream>

#include "parserCode.h"
#include "orca_opcode.h"


extern map<string, string> g_term_map;
extern vector<string> g_term_list;
extern vector<string> g_expr_list;

string get_term_name();


struct expr_t
{
	string escape(const char* cp);

	void set_terminal(const char* cp);
	void set_terminal_re(const char* cp);
	void set_non_terminal(const char* cp);
	void set_action_code(const char* cp);
	string make_action_code();

	void pass1(int idx);
	void pass2(stringstream& flex, stringstream& bison);

	void dump();
	string to_str();

	char type;
	string expr;
	int idx;
};

struct bnf_t
{
	~bnf_t();
	void push_expr(expr_t* ep);
	void pass1();
	void pass2(stringstream& flex, stringstream& bison);

	void dump();
	string to_str();
	string get_terminal();

	vector<expr_t*> expr_list;
};

struct rule_t
{
	~rule_t();

	void set_name(const char* cp);
	void push_bnf(bnf_t* bnf);
	void pass1();
	void pass2(stringstream& flex, stringstream& bison);

	void dump();
	string to_str();

	string name;
	vector<bnf_t*> bnf_list;
};

struct parse_t
{
	~parse_t();

	void push_rule(rule_t* r);
	void make_lexer(const string& name, stringstream& flex, stringstream& bison);

	bool process(const string& name);
	void make_meta(const string& name);
	bool build_so(const string& name);

	void dump();
	string to_str();

	vector<rule_t*> rule_list;
};




//
// for outer so build
//
class orcaObject;

struct orcaParseContext // to ensure cleanup in case of exception
{
	orcaParseContext(orcaVM*, orcaObject*);
	~orcaParseContext();
};

void parse_set_error(const char* msg, const char* token);
int parse_make_string(const char* cp);
int parse_call(const string& name, int num, ...);

void parse_set_source(const string& src);
int parse_yyinput(char* buff, int max_size);
#endif



