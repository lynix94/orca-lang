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

typedef vector<const char*> name_list_t;

extern yyFlexLexer *lexer;

void yyerror(const char* s);
extern "C" int yywrap();

int yyparse();
int yylex();

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



#ifndef  __LEX__	// only yacc, not lex
#define yytext lexer->YYText()
#define yylex() lexer->yylex()
#endif

class orcaVM;

void print(const char* fmt, ...);
void hex_dump(unsigned char* data, int len);


class parserParser
{
public:
	parserParser();

	void init();
	void cleanup();

	bool parse(const string& filename);
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

private:
	vector<const char*> s_pool;
	vector<name_list_t*> s_pool_nl;
};

extern parserParser* g_parser;




#endif

