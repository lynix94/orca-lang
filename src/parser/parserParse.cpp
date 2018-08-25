/* vim: et fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserParse.cpp - manage parse statement

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <stdio.h>
#include <stdarg.h>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "parserParser.h"
#include "parserParse.h"
#include "orcaObject.h"
#include "kyString.h"

namespace fs = boost::filesystem;

//#define _PARSE_DEBUG_

map<string, string> g_term_map;
vector<string> g_term_list;
set<string> g_expr_set;


extern const char* flex_head;
extern const char* flex_tail;
extern const char* bison_head;
extern const char* bison_tail;


string get_term_name()
{           
  char buff[1024];
  sprintf(buff, "TERM_%d", (int)g_term_map.size());
		  
  return buff;
}  


string expr_t::escape(const char* cp)
{
	stringstream ss;
	for (const char* c = cp; *c != 0; c++) {
		switch (*c)
		{
		case '\a': ss << "\\a"; break;
		case '\b': ss << "\\b"; break;
		case '\f': ss << "\\f"; break;
		case '\n': ss << "\\n"; break;
		case '\r': ss << "\\r"; break;
		case '\t': ss << "\\t"; break;
		case '\v': ss << "\\v"; break;
		case '\"': ss << "\\\""; break;
		case '\'': ss << "\\'"; break;
		default: ss << *c; break;
		}
	}

	return ss.str();
}

void expr_t::set_terminal(const char* cp)
{
	type = 'T';
	expr = escape(cp);
}

void expr_t::set_terminal_re(const char* cp)
{
	type = 'R';
	expr = escape(cp);
}

void expr_t::set_non_terminal(const char* cp)
{
	type = 'N';
	expr = cp;
}

void expr_t::set_action_code(const char* cp)
{
	type = 'A';
	expr = cp;
}

void expr_t::pass1(int idx)
{
	this->idx = idx;

	string key;
	if (type == 'T') {
		key = string("\"") + expr + "\"";
	}
	else if (type == 'R') {
		key = expr;
	}
	else if (type == 'A') {
		return;
	}
	else { // 'N'
		return;
	}

	map<string, string>::iterator it = g_term_map.find(key);
	
	if (it == g_term_map.end()) {
		g_term_map[key] = get_term_name();
		g_term_list.push_back(key);
		it = g_term_map.find(key);
	}

	type = 'N';
	expr = it->second;
}



string expr_t::make_action_code()
{
	char buff[1024];
	if (idx != bp->expr_list.size()-1) { // not end
		sprintf(buff, "{ parse_call(\"%s\", %d, ", expr.c_str(), idx);
	}
	else {
		if (idx == 0) { // action only
			sprintf(buff, "{ $$ = parse_call(\"%s\", 0); }", expr.c_str());
			return buff;
		}

		sprintf(buff, "{ $$ = parse_call(\"%s\", %d, ", expr.c_str(), idx);
	}

	string ret = buff;
	for (int i=1; i<=idx; i++) {
		if (bp->expr_list[i-1]->type == 'A') {
			if (i < idx) sprintf(buff, "-1, ");
			else		 sprintf(buff, "-1); }");
		}
		else {
			if (i < idx) sprintf(buff, "$%d, ", i);
			else		 sprintf(buff, "$%d); }", i);
		}


		ret += buff;
	}

	return ret;
}

void expr_t::pass2(stringstream& flex, stringstream& bison)
{
	if (type == 'N') {
		bison << expr + " ";
	}
	else if (type == 'A') {
#ifndef _PARSE_DEBUG_
		bison << make_action_code();
#endif
	}
	else {
		printf("Something wrong\n");
	}
}

void expr_t::dump()
{
	printf("%s", to_str().c_str());
}

string expr_t::to_str()
{
	switch(type)
	{
	case 'T':
		return string("'") + expr + "'";

	case 'R':
		return string("r'") + expr + "'";

	case 'N':
		return expr;

	case 'A':
		return expr;
	}

	return "N/A";
}



bnf_t::~bnf_t()
{
	for (int i=0; i<expr_list.size(); i++) {
		delete expr_list[i];
	}
}

void bnf_t::push_expr(expr_t* ep)
{
	ep->bp = this;
	expr_list.push_back(ep);
}

void bnf_t::pass1()
{
	for (int i=0; i<expr_list.size(); i++) {
		expr_list[i]->pass1(i);
	}
}

void bnf_t::pass2(stringstream& flex, stringstream& bison)
{
	for (int i=0; i<expr_list.size(); i++) {
		expr_list[i]->pass2(flex, bison);
	}

	bison << "\n";
}

void bnf_t::dump()
{
	printf("%s", to_str().c_str());
}

string bnf_t::to_str()
{
	stringstream str;
	for (int i=0; i<expr_list.size(); i++) {
		str << expr_list[i]->to_str() << " ";
	}

	return str.str();
}

string bnf_t::get_terminal()
{
	if (expr_list.size() != 1) {
		throw "escaping terminal should be one";
	}

	return expr_list[0]->expr;
}





rule_t::~rule_t()
{
	for (int i=0; i<bnf_list.size(); i++) {
		if (bnf_list[i] == NULL) continue;
		delete bnf_list[i];
	}
}

void rule_t::set_name(const char* cp)
{
	name = cp;
}

void rule_t::push_bnf(bnf_t* bnf)
{
	bnf_list.push_back(bnf);
}

void rule_t::pass1()
{
	for (int i=0; i<bnf_list.size(); i++) {
		if (name == "nil") continue;
		if (bnf_list[i] == NULL) continue;
		bnf_list[i]->pass1();
	}

	g_expr_set.insert(name);
}

void rule_t::pass2(stringstream& flex, stringstream& bison)
{
	if (name == "nil") {
		for (int i=0; i<bnf_list.size(); i++) {
			flex << bnf_list[i]->get_terminal() << "\t;\n";
		}
		return;
	}

	bison << name + ":\n\t";
	for (int i=0; i<bnf_list.size(); i++) {
		if (bnf_list[i] == NULL) {
			bison << "/* empty */\n";
		}
		else {
			bnf_list[i]->pass2(flex, bison);
		}

#ifdef _PARSE_DEBUG_
		string debug;
		bnf_t* bp = bnf_list[i];
		for (int j=0; j<bp->expr_list.size(); j++) {
			debug += bp->expr_list[j]->to_str();
			debug += " ";
		}
		bison << kyString::sprintf("\t\t{ printf(\"rule match: %s <- %s\\n\"); }\n", name.c_str(), debug.c_str());
#endif

		if (i < bnf_list.size()-1) {
			bison << "\t| ";
		}
		else {
			bison << "\t;\n\n";
		}
	}
}

void rule_t::dump()
{
	printf("%s", to_str().c_str());
}

string rule_t::to_str()
{
	stringstream str;
	str << name << " : ";
	for (int i=0; i<bnf_list.size(); i++) {
		str << bnf_list[i]->to_str();
		if (i != bnf_list.size()-1) {
			str << "\n\t|";
		}
	}
	str << "\n\t;";

	return str.str();
}

parse_t::~parse_t()
{
	for (int i=0; i<rule_list.size(); i++) {
		delete rule_list[i];
	}
}

void parse_t::push_rule(rule_t* r)
{
	rule_list.push_back(r);
}

void parse_t::make_lexer(const string& prefix, stringstream& flex, stringstream& bison)
{
	for (int i=0; i<g_term_list.size(); i++) {
		string key = g_term_list[i];
		string value = g_term_map[key];

		flex<< kyString::sprintf("%s\t{ %slval.i = parse_make_string(%stext); return %s; }\n",
								key.c_str(), prefix.c_str(), prefix.c_str(), value.c_str());

		bison << kyString::sprintf("%%token<i> %s\n", value.c_str());
	}

	bison << "\n\n";
	set<string>::iterator it = g_expr_set.begin();
	for (; it != g_expr_set.end(); ++it) {
		if ((*it) == "nil") continue;
		bison << kyString::sprintf("%%type<i> %s\n", (*it).c_str());
	}

	bison << "%%\n\n";
}

bool parse_t::process(const string& name)
{
	make_meta(name);
	return build_so(name);
}

bool parse_t::build_so(const string& name)
{
	int ret;
	char buff[4096];
	const char* cp = name.c_str();

	// calc path
	boost::filesystem::path src_path(g_parser->filename);
	string dir = src_path.parent_path().string();
	const char* dp = dir.c_str();
	if (dp[0] == 0) {
		dp = ".";
	}

	fs::remove(kyString::sprintf("%s/%s_lexer.cpp", dp, name.c_str()));
	sprintf(buff, "flex -P %s -o %s/%s_lexer.cpp %s/%s_lexer.l", cp, dp, cp, dp, cp);
	printf("flex compile: %s\n", buff);
	ret = ::system(buff);

	fs::remove(kyString::sprintf("%s/%s_parser.cpp", dp, name.c_str()));
	fs::remove(kyString::sprintf("%s/%s_parser.hpp", dp, name.c_str()));
	sprintf(buff, "bison -p %s -d -r all -o %s/%s_parser.cpp %s/%s_parser.y", cp, dp, cp, dp, cp);
	printf("bison compile: %s\n", buff);
	ret = ::system(buff);

	string target = kyString::sprintf("%s/libparse_%s.so", dp, name.c_str());
	fs::remove(target);
	sprintf(buff, "g++ -g -fPIC -shared -o %s %s/%s_lexer.cpp %s/%s_parser.cpp -I${ORCA_HOME}/include/orca -L${ORCA_HOME}/lib -lorca", target.c_str(), dp, cp, dp, cp);
	printf("external module compile: %s\n", buff);
	ret = ::system(buff);

	if (!fs::exists(target)) {
		return false;
	}

	return true;
}

void parse_t::make_meta(const string& name)
{
	// calc path
	boost::filesystem::path src_path(g_parser->filename);
	string dir = src_path.parent_path().string();
	const char* dp = dir.c_str();
	if (dp[0] == 0) {
		dp = ".";
	}

	stringstream flex;
	stringstream bison;

	for (int i=0; i<rule_list.size(); i++) {
		rule_list[i]->pass1();
	}

	const char* cp = name.c_str();
	flex << kyString::sprintf(flex_head, cp);
	bison << kyString::sprintf(bison_head, cp, cp, cp, cp);

	// make flex
	make_lexer(name, flex, bison);
	// make bison
	for (int i=0; i<rule_list.size(); i++) {
		rule_list[i]->pass2(flex, bison);
	}

	flex << kyString::sprintf(flex_tail);
	bison << kyString::sprintf(bison_tail, cp, cp, cp, cp, cp, cp, cp, cp);

	//dump();
	//printf("flex>> '%s'\n", flex.str().c_str());
	//printf("bison>> '%s'\n", bison.str().c_str());

	FILE* fp;
	fp = fopen(kyString::sprintf("%s/%s_lexer.l", dp, name.c_str()).c_str(), "w");
	string flex_string = flex.str();
	cp = flex_string.c_str();
	fwrite(cp, strlen(cp), 1, fp);
	fclose(fp);

	fp = fopen(kyString::sprintf("%s/%s_parser.y", dp, name.c_str()).c_str(), "w");
	string bison_string = bison.str();
	cp = bison_string.c_str();
	fwrite(cp, strlen(cp), 1, fp);
	fclose(fp);
}

void parse_t::dump()
{
	if (!g_term_map.empty()) {
		printf("========= term table =========\n");
		map<string, string>::iterator it = g_term_map.begin();
		for(; it != g_term_map.end(); ++it) {
			printf("\t%s : %s\n", it->first.c_str(), it->second.c_str());
		}

		printf("\n");
	}

	printf("========= rule table =========\n");
	printf("%s", to_str().c_str());
}

string parse_t::to_str()
{
	stringstream str;
	for (int i=0; i<rule_list.size(); i++) {
		str << rule_list[i]->to_str();
		str << "\n";
	}

	return str.str();
}





// parse runtime
static orcaVM* parseVM;
static orcaObject* parseObject;
static string parse_error;
static portMutex parseMutex;
static vector<orcaData> gc_pool;


orcaParseContext::orcaParseContext(orcaVM* vm, orcaObject* op)
{
	parseMutex.lock();

	// cleanup
	for (int i=0; i<gc_pool.size(); i++) {
		gc_pool[i].rc_dec();
	}
	gc_pool.clear();

	// init
	parseVM = vm;
	parseObject = op;

	op->update_member("RESULT", NIL);
	op->update_member("ERROR", "");
	parse_error = "";
}


orcaParseContext::~orcaParseContext()
{
	parseObject->update_member("ERROR", parse_error);

	for (int i=0; i<gc_pool.size(); i++) {
		gc_pool[i].rc_dec();
	}
	gc_pool.clear();

	parseMutex.unlock();
}


void parse_set_error(const char* msg, const char* token)
{
	parse_error = kyString::sprintf("%s near by '%s'", msg, token);
}

int parse_make_string(const char* cp)
{
	orcaData d = cp;
	gc_pool.push_back(d);
	d.rc_inc();

	return gc_pool.size()-1;
}


int parse_call(const string& name, int num, ...)
{
	orcaData d = parseObject->get_member(name.c_str());
	parseVM->push_stack(d);

	va_list ap;
	va_start(ap, num);
	for (int i=0; i<num; i++) {
		int idx = va_arg(ap, int);
		if (idx == -1) {
			parseVM->push_param(NIL);
		}
		else {
			parseVM->push_param(gc_pool[idx]);
		}
	}
	va_end(ap);

	parseVM->call(num);
	orcaData ret = parseVM->pop_stack(); 
	gc_pool.push_back(ret);
	ret.rc_inc();

	return gc_pool.size() - 1;
}


// parse source
struct parseSource
{
	string source;
	int len;
	int idx;
};

static parseSource parse_source;

void parse_set_source(const string& src)
{
	parse_source.source = src;
	parse_source.len = src.length();
	parse_source.idx = 0;
}

int parse_yyinput(char* buff, int max_size)
{
	int remain = parse_source.len - parse_source.idx;
	int n = max_size;

	if (remain < n) {
		n = remain;
	}

	if (n > 0) {
		memcpy(buff, parse_source.source.c_str() + parse_source.idx, n);
		parse_source.idx += n;
	}
	
	return n;
}





