/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parser_common.h - common routine & utils

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/
#ifndef _DEF_PARSER_COMMON
#define _DEF_PARSER_COMMON

// lex, yacc function
#include <FlexLexer.h>
#include <string>
#include <vector>

using namespace std;

typedef vector<const char*> name_list_t;

extern FILE* parser_curr_fp;
extern int parser_lineno;
extern string g_parse_module_name;


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

void parse_init();
void parse_cleanup();
bool parse(const string& filename);
bool interpret(orcaVM* vm);

void set_interactive(bool flag);
bool is_interactive();

char* parser_alloc(size_t size);
const char* parser_strdup(const char* str);
name_list_t* parser_new_name_list();
void parser_free_all();

#endif

