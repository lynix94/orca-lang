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
#include <fstream>
#include <streambuf>



#include "parserParser.h"
#include "parserCode.h"
#include "orcaException.h"
#include "orcaVM.h"
#include "kyString.h"

parserParser s_parser;
parserParser* g_parser = &s_parser;


orcaFlexLexer *lexer = NULL;


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
	if (g_parser->n_tok == 0) { // empty file
		return;
	}

	print("[%s - %d]%s, nearby('%s')\n", g_parser->filename.c_str(), g_parser->lineno, s, lexer->YYText());
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

int parser_starts_with(const char* line, const char* word)/*{{{*/
{
	int ret = -1;
	for(int i=0; i<strlen(line); i++) {
		char c = line[i];

		if (strncmp(&line[i], word, strlen(word)) == 0) {
			ret = i;
			break;
		}

		if (!isspace(c)) {
			break;
		}
	}

	return ret;
}
/*}}}*/

static int count_in(const char* line, const char* word)/*{{{*/
{
	int ret = 0;
	int len = strlen(line);
	for (int i=0; i<len; i++) {
		if (strncmp(line + i, word, strlen(word)) == 0) {
			if (i > 1 && line[i-1] == '\\') {
				continue;
			}

			ret++;
			i += strlen(word) - 1;
			continue;
		}
	}

	return ret;
}
/*}}}*/

void parser_split_ctx_def(const string& src, string& ctx, string& def, map<string, int>& pos_map)/*{{{*/
{
	istringstream f(src);
	string line;	
	stringstream ctx_ss, def_ss;

	int open = 0;
	int close = 0;
	int line_no = -1;
	while (getline(f, line)) {
		line_no++;
		int start = parser_starts_with(line.c_str(), "def");
		if (start >= 0) {
			open = close = 0;

			// get name
			int name_start = -1;
			int name_end = -1;
			bool is_start = false;
			int i=start;
			for (; i<line.length(); i++) {
				if (is_start == false && isspace(line[i])) {
					is_start = true;
					continue;
				}

				if (is_start == true && name_start < 0 && !isspace(line[i])) {
					name_start = i;
				}

				if (name_start >= 0 && 
					(isspace(line[i]) || line[i] == '(' || line[i] == '{'))
				{
					name_end = i;
					break;
				}
			}
			if (i == line.length() && name_start > 0) {
				name_end = line.length();
			}

			if (name_start > 0 && name_end > 0) {
				string name = line.substr(name_start, name_end - name_start);
				pos_map[name] = line_no;
			}

			while (true) {
				def_ss << line << "\n";
				ctx_ss << "\n";

				open += count_in(line.c_str(), "{");
				close += count_in(line.c_str(), "}");

				if (open > 0 && open == close) {
					break;
				}

				if (!getline(f, line)) {
					printf("context extension compile failed. check {, } pair");
					break;
				}

				line_no++;
			}
		}
		else if (parser_starts_with(line.c_str(), "using") >=  0) {
			def_ss << line << "\n";
			ctx_ss << "\n";
		}
		else {
			ctx_ss << line << "\n";
			def_ss << "\n";
		}
	}

	ctx = ctx_ss.str();
	def = def_ss.str();
}
/*}}}*/




parserParser::parserParser()/*{{{*/
{
	curr_fp = NULL;
	lineno = 1;
	filename = "";
	module_name = "";
	flag_interactive = false;
	flag_eval = false;
	n_tok = 0;
}

/*}}}*/

void parserParser::init()/*{{{*/
{
	if (lexer != NULL) delete lexer;
	lexer = new orcaFlexLexer;
	free_all();

	n_tok = 0;
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
	curr_fp = fopen(filename.c_str(), "r");
	lineno = 1;
	this->filename = filename;

	// read for error recovery
	fseek(curr_fp, 0, SEEK_END);
	int f_size = ftell(curr_fp);
	fseek(curr_fp, 0, SEEK_SET);

	string compile_string;
	compile_string.resize(f_size);
	size_t ret = fread(&compile_string[0], 1, f_size, curr_fp);
	fseek(curr_fp, 0, SEEK_SET);


	// init
	parserCode::init();

	string module_name; 
	if (filename.rfind("/") > 0) {
		module_name = filename.substr( filename.rfind("/")+1 );
	}

	if (filename.rfind(".") > 0) {
		module_name = module_name.substr( 0, module_name.rfind(".") );
	}

	this->module_name = module_name;

	name_list_t* vs = g_parser->new_name_list();
	vs->push_back("...argv");
	parserCode::push_code_stack((char*)module_name.c_str(), vs);
	code_top->set_argv_on();	// enable argv 

	// parse
	init();
	try {
		int ret = yyparse();
		if (ret != 0) {
			try_parse(compile_string);
			if (!g_parser->is_interactive() && !g_parser->is_eval()) {
				exit(0);
			}

			if (g_parser->n_tok > 0) {
				return false;
			}
			else {
				code_top->clear();
			}
		}
	}
	catch(const char* cp) {
		print("[%s - %d]%s\n", filename.c_str(), lineno, cp);
		try_parse(compile_string);
		if (!g_parser->is_interactive() && !g_parser->is_eval()) {
			exit(0);
		}
		return false;
	}
	
	// make binary
	parserCode::pop_code_stack();
	parserCode::Final(filename.c_str());

#ifdef _VM_DEBUG
	parserCode::dump_final();
#endif

	// clean up
	fclose(curr_fp);
	free_all();
	return true;
}

/*}}}*/

bool parserParser::parse_context_file(const string& filename, const string& mod_name, const string& sub_postfix)/*{{{*/
{
	this->filename = filename;

	// open
	ifstream fs(filename.c_str());
	string source((istreambuf_iterator<char>(fs)), istreambuf_iterator<char>());

	string code;
	string def;
	map<string, int> pos_map;
	parser_split_ctx_def(source, code, def, pos_map);

	// init
	parserCode::init();
	this->module_name = mod_name;

	parserCode::push_context_stack((char*)sub_postfix.c_str(), (char*)code.c_str(), (char*)mod_name.c_str(), NULL, 0, NULL, NULL, pos_map);

	// parse
	init();
	curr_fp = fmemopen((void*)def.c_str(), def.size(), "r");
	lineno = 1;
	try {
		int ret = yyparse();
		if (ret != 0) {
			if (g_parser->n_tok > 0) {
				return false;
			}
			else {
				code_top->clear();
			}
		}
	}
	catch(const char* cp) {
		printf("%s\n", cp);
		return false;
	}

	// make binary
	parserCode::pop_code_stack();

	string parent_path = fs::path(filename).parent_path().string();
	string target_path = mod_name;
	if (parent_path.length() > 0) {
		target_path = parent_path + "/" + mod_name;
	}

	parserCode::Final(target_path.c_str());


#ifdef _VM_DEBUG
	parserCode::dump_final();
#endif

	// clean up
	fclose(curr_fp);
	free_all();

	return true;
}

/*}}}*/



extern orcaData g_last_pop_stack;

static string line_replace(const string& src)
{
	stringstream buff;
	for(int i=0; i<src.length(); i++) {
		if (src[i] == '{') {
			buff << "{";
		}

		if (src[i] == '}') {
			buff << "}";
		}
	}

	return buff.str();
}

void parserParser::try_parse(const string& src)/*{{{*/
{
	vector<string> lines = kyString::split(src, "\n", INT_MAX, true);
	//printf("compile string: '%s'\n", src.c_str());

	for (int i=0; i<10; i++) {
		// replace with
		if (lineno < 0 || lineno > lines.size()) {
			return;
		}
		lines[lineno-1] = line_replace(lines[lineno-1]);
		string new_src = kyString::join(lines, "\n");
	
		//printf(">>> try %d: '%s'\n", i, new_src.c_str());
		curr_fp = fmemopen((void*)new_src.c_str(), new_src.size(), "r");

		// init
		lineno = 1;
		parserCode::init();
		parserCode::push_code_stack((char*)"try", NULL);
		code_top->init_current();  

		// parse
		init();
		try {
			int rv = yyparse();
			if (rv != 0) {
				//printf("fail again at %d\n", lineno);
			}
			else {
				break;
			}
		}
		catch (const char* cp) {
			print("[%s - %d]%s\n", filename.c_str(), lineno, cp);
		}
	}
}
/*}}}*/

orcaData parserParser::eval(orcaVM* vm, const string& src)/*{{{*/
{
	set_eval(true);

	//printf(">>> eval: %s\n", src.c_str());
	curr_fp = fmemopen((void*)src.c_str(), src.size(), "r");

	// init
	parserCode::init();
	parserCode::push_code_stack((char*)"eval", NULL);
	code_top->init_current();  

	// parse
	int rv;
	try {
		init();
		try {
			rv = yyparse();
		}
		catch(const char* cp) {
			printf("%s\n", cp);
			rv = -1;
		}

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
	curr_fp = stdin;

	// init
	parserCode::init();
	parserCode::push_code_stack((char*)"stdin.orca", NULL);
	code_top->init_current();  

	// parse
	int rv;
	do {
		try {
			init();

			try {
				rv = yyparse();
			}
			catch(const char* cp) {
				printf("%s\n", cp);
				rv = -1;
			}

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


