/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserParser.cpp - common routine & utils

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // tolower

#include "parserParser.h"
#include "parserCode.h"
#include "orcaException.h"
#include "orcaVM.h"

parserParser s_parser;
parserParser* g_parser = &s_parser;

FILE* parser_curr_fp;
int parser_lineno = 1;
string parser_filename = "";
string g_parse_module_name; // for context

yyFlexLexer *lexer = NULL;


int yyFlexLexer::yywrap()/*{{{*/
{
#ifdef _VM_DEBUG
	print("Parsing end.\n");
#endif
	return 1;
}
/*}}}*/

void yyerror(const char* s)/*{{{*/
{
	print("[%s - %d]%s, nearby('%s')\n", parser_filename.c_str(), parser_lineno, s, yytext);
	if (!g_parser->is_interactive() and !g_parser->is_eval()) {
		exit(0);
	}
}/*}}}*/

void print(const char *fmt, ...)/*{{{*/
{
	char tmp[1024];

	va_list ap;
	va_start(ap, fmt);

	vsprintf(tmp, fmt, ap);
	printf("%s", tmp);
		
	va_end(ap);
}
/*}}}*/

void hex_dump(unsigned char* data, int len)/*{{{*/
{
	int j;
	
	print("(%x)", len);
	for(j=0; j<len; j++)
		print("%02x", data[j]);

	print("\n");
}
/*}}}*/

void parserParser::init()/*{{{*/
{
	if (lexer != NULL) delete lexer;
	lexer = new yyFlexLexer;
	free_all();

	curr_fp = NULL;
	lineno = 1;
	filename = "";
	module_name = "";
	//flag_interactive = false;
	flag_eval = false;
}
/*}}}*/

void parserParser::cleanup()/*{{{*/
{
	if (lexer != NULL) delete lexer;
	lexer = NULL;
	free_all();
}
/*}}}*/



bool parserParser::parse(const string& filename)/*{{{*/
{
	// open
	parser_curr_fp = fopen(filename.c_str(), "r");
	parser_lineno = 1;
	parser_filename = filename;

	// init
	parserCode::init();

	string module_name;
	if (filename.rfind("/") > 0) 
		module_name = filename.substr( filename.rfind("/")+1 );

	if (filename.rfind(".") > 0) 
		module_name = module_name.substr( 0, module_name.rfind(".") );

	g_parse_module_name = module_name;

	parserCode::push_code_stack((char*)module_name.c_str(), NULL, false);
	code_top->find_lvar((char*)"argv");
	code_top->set_argv_on();	// enable argv 

	// parse
	init();
	if (yyparse() != 0) {
		return false;
	}
	
	// make binary
	parserCode::pop_code_stack();
	parserCode::Final(filename.c_str());

#ifdef _VM_DEBUG
	parserCode::dump_final();
#endif

	// clean up
	fclose(parser_curr_fp);
	free_all();
	return true;
}

/*}}}*/



extern orcaData g_last_pop_stack;

orcaData parserParser::eval(orcaVM* vm, const string& src)/*{{{*/
{
	set_eval(true);

	printf(">>> eval: %s\n", src.c_str());
	parser_curr_fp = fmemopen((void*)src.c_str(), src.size(), "r");

	// init
	parserCode::init();
	parserCode::push_code_stack((char*)"eval", NULL, false);
	code_top->init_current();  

	// parse
	int rv;
	try {
		init();
		rv = yyparse();

		if (rv == 0) {
			code_top->push_char(OP_RETURN);

			code_top->eval(vm);
		}

		if (!is<TYPE_NIL>(g_last_pop_stack)) {
			parserCode::init();
			set_eval(false);
			return g_last_pop_stack;
		}
	}
	catch(orcaException& e) {
		printf("uncaugted exception: %s %s\n", e.who(), e.what());
		cout << e.m_stack_trace << endl;
	}

	parserCode::init();
	set_eval(false);
	return NIL;
}
/*}}}*/

bool parserParser::interpret(orcaVM* vm)/*{{{*/
{
	parser_curr_fp = stdin;

	// init
	parserCode::init();
	parserCode::push_code_stack((char*)"stdin.orca", NULL, false);
	code_top->init_current();  

	// parse
	int rv;
	do {
		try {
			init();

			rv = yyparse();

			if (rv == 0) {
				code_top->push_char(OP_RETURN);
				code_top->interpret(vm);
			}

			if (!is<TYPE_NIL>(g_last_pop_stack))
				cout << g_last_pop_stack.string_(vm) << endl;
			g_last_pop_stack = NIL;

			code_top->init_current();
		}
		catch(orcaException& e) {
			printf("uncaugted exception: %s %s\n", e.who(), e.what());
			cout << e.m_stack_trace << endl;

			parserCode::reinit_code_stack_for_interpreter();
			code_top->init_current();
			continue;
		}

	} while( true );

	// clean up
	parserCode::init();

	return true;
}
/*}}}*/

void parserParser::set_interactive(bool flag)/*{{{*/
{
	flag_interactive = flag;
}
/*}}}*/

bool parserParser::is_interactive()/*{{{*/
{
	return flag_interactive;
}
/*}}}*/

void parserParser::set_eval(bool flag)/*{{{*/
{
	flag_eval = flag;
}
/*}}}*/
bool parserParser::is_eval()/*{{{*/
{
	return flag_eval;
}
/*}}}*/

char* parserParser::alloc(size_t size)/*{{{*/
{
	char* cp = (char*)malloc(size);
	s_pool.push_back(cp);
	return cp;
}
/*}}}*/

const char* parserParser::strdup(const char* str)/*{{{*/
{
	const char* cp = (const char*)::strdup((char*)str);
	s_pool.push_back(cp);
	return cp;
}
/*}}}*/

name_list_t* parserParser::new_name_list()/*{{{*/
{
	name_list_t* np = new name_list_t;
	s_pool_nl.push_back(np);
	return np;
}
/*}}}*/

void parserParser::free_all()/*{{{*/
{
	vector<const char*>::iterator vi = s_pool.begin();
	for (; vi!=s_pool.end(); ++vi) {
		free ((char*)*vi);
	}
	s_pool.clear();

	vector<name_list_t*>::iterator it = s_pool_nl.begin();
	for (; it!=s_pool_nl.end(); ++it) {
		delete *it;
	}
	s_pool_nl.clear();
}
/*}}}*/




// common files
// defined at orca_common.h 
char* ll2l(long long i) /*{{{*/
{
	static char byte[8];

#ifdef _BIG_ENDIAN_
	int msw, lsw;

	msw = i >> 32;
	lsw = i & 0xffffffff;

	byte[0] = (msw&0xff000000) >> 24;
	byte[1] = (msw&0x00ff0000) >> 16;
	byte[2] = (msw&0x0000ff00) >> 8;
	byte[3] = (msw&0x000000ff);
	byte[4] = (lsw&0xff000000) >> 24;
	byte[5] = (lsw&0x00ff0000) >> 16;
	byte[6] = (lsw&0x0000ff00) >> 8;
	byte[7] = (lsw&0x000000ff);
#else
	memcpy(byte, &i, sizeof(long long));
#endif
	return byte;
}
/*}}}*/

char* i2l(int i) /*{{{*/
{
	static char byte[4];

#ifdef _BIG_ENDIAN_
	byte[0] = (i&0xff000000) >> 24;
	byte[1] = (i&0x00ff0000) >> 16;
	byte[2] = (i&0x0000ff00) >> 8;
	byte[3] = (i&0x000000ff);
#else
	memcpy(byte, &i, sizeof(int));
#endif
	return byte;
}
/*}}}*/

char* s2l(short s) /*{{{*/
{
	static char byte[2];

#ifdef _BIG_ENDIAN_
	byte[0] = (i&0x0000ff00) >> 8;
	byte[1] = (i&0x000000ff);
#else
	memcpy(byte, &s, 2);
#endif
	return byte;
}
/*}}}*/

short l2s(char* in)/*{{{*/
{
	short ret = in[0] + (in[1] * 0x100);
	return ret;
}
/*}}}*/

short l2s(const char* in)/*{{{*/
{
	short ret = in[0] + (in[1] * 0x100);
	return ret;
}
/*}}}*/

int l2i(char* in)/*{{{*/
{
	int ret = in[0] + (in[1] * 0x100) + (in[2] * 0x10000) + (in[3] * 0x1000000);
	return ret;
}
/*}}}*/

short htols(short in)/*{{{*/
{
#ifdef _BIG_ENDIAN_
	return l2s((char*)&in);
#else
	return in;
#endif
}
/*}}}*/

int htoli(int in)/*{{{*/
{
#ifdef _BIG_ENDIAN_
	return l2i((char*)&in);
#else
	return in;
#endif
}
/*}}}*/

short ltohs(short in)/*{{{*/
{
#ifdef _BIG_ENDIAN_
	return l2s((char*)&in);
#else
	return in;
#endif
}
/*}}}*/


