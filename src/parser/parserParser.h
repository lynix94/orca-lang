/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserParser.h - common routine & utils

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/
#ifndef _DEF_PARSER_PARSER
#define _DEF_PARSER_PARSER

// lex, yacc function
#include <FlexLexer.h>
#include <string>
#include <vector>

#include "orcaData.h"

using namespace std;

// for flex
///////////////
class orcaFlexLexer : public yyFlexLexer
{
public:
	int yylex(); // made in lexer.cpp

	// made in lexer.l
	const char* get_string(char end);
	const char* get_comment(char end);

	string get_raw_context();
	const char* get_context();
	const char* get_hex_string(char end);
	const char* get_bin_string(char end);

	void yyunput_string(const char* str);
};

extern orcaFlexLexer *lexer;
int yylex();


// for bison
///////////////
int yyparse();
void yyerror(const char* s);
#ifndef  __LEX__	// only yacc, not lex
#define yylex() lexer->yylex()
#endif


typedef vector<const char*> name_list_t;

struct cp2_t
{
	const char* c1;
	const char* c2;
};

struct int2_t
{
	int i1;
	int i2;
};



class orcaVM;

void print(const char* fmt, ...);
void hex_dump(unsigned char* data, int len);

void parser_split_ctx_def(const string& src, string& ctx, string& def);
bool parser_starts_with(const char* line, const char* word);


class parserParser
{
public:
	parserParser();

	void init();
	void cleanup();

	bool parse(const string& filename);
	bool parse_context_file(const string& filename, const string& mod_name, const string& sub_postfix);
	bool interpret(orcaVM* vm);
	orcaData eval(orcaVM* vm, const string& src);

	void set_interactive(bool flag);
	bool is_interactive();
	void set_eval(bool flag);
	bool is_eval();


	char* alloc(size_t size);
	const char* strdup(const char* str);
	name_list_t* new_name_list();
	void free_all();

public:
	FILE* curr_fp;
	int lineno;
	string filename;
	string module_name;


	bool flag_interactive;
	bool flag_eval;

	int n_tok;

private:
	vector<const char*> s_pool;
	vector<name_list_t*> s_pool_nl;
};

extern parserParser* g_parser;




#endif

