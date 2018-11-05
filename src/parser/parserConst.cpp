/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parserConst.cpp - 

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/


const char* flex_head = "\n\
%%{\n\
#include <unistd.h>\n\
#include <string.h>\n\
#include <stdlib.h>\n\
#include <stdio.h>\n\
#include <limits.h>\n\
#include \"parserParse.h\"\n\
#include \"%s_parser.hpp\"\n\
\n\
#undef YY_INPUT\n\
#define YY_INPUT(buffer, result, max_size) ( result = parse_yyinput(buffer, max_size))\n\
\n\
%%}\n\
\n\
%%%%\n\n\n";


const char* flex_tail = "\n\
%%%%\n\
int parse_input() { return yyinput(); }\n\
int parse_unput(const char* str) {\n\
	const char *cp = str + strlen(str) - 1;\n\
	while (cp >= str) {\n\
		yyunput(*cp, yytext);\n\
		cp--;\n\
	}\n\
}\n\
\n\n";


const char* bison_head = "\n\
%%{\n\
#define __YACC__\n\
#include <stdio.h>\n\
#include <stdarg.h>\n\
#include <stdlib.h>\n\
#include <string.h>\n\
#include <limits.h>\n\
#include <vector>\n\
#include \"parserParse.h\"\n\
#include \"%s_parser.hpp\"\n\
using namespace std;\n\
int %slex();\n\
void %serror(const char* s);\n\
extern \"C\" int %swrap();\n\
%%}\n\
%%union \n\
{\n\
	int i;\n\
};\n\
%%error-verbose\n\n\n";


const char* bison_tail = "\n\
%%%%\n\
#include \"orcaObject.h\"\n\
\n\
#ifdef WINDOWS\n\
#define EXPORT __declspec(dllexport)\n\
#else\n\
#define EXPORT\n\
#endif\n\
\n\
int parse_input(void);\n\
int parse_unput(const char* cp);\n\
int %sparse (void);\n\
extern char *%stext;\n\
void %serror(const char* s)\n\
{\n\
	parse_set_error(s, %stext);\n\
}\n\
\n\
extern \"C\" int %swrap()\n\
{\n\
	return 1;\n\
}\n\n\
class orcaParseObject : public orcaObject\n\
{\n\
public:\n\
	DEFAULT_NATIVE_DEFINE(orcaParseObject);\n\
	int error;\n\
	orcaParseObject()\n\
	{\n\
		set_name(\"%s\");\n\
		insert_native_function(\"yyinput\", (object_fp)&orcaParseObject::ex_yyinput);\n\
		insert_native_function(\"yyunput\", (object_fp)&orcaParseObject::ex_yyunput);\n\
		insert_native_function(\"yyerror\", (object_fp)&orcaParseObject::ex_yyerror);\n\
	}\n\
	\n\
	orcaData operator()(orcaVM* vm, int param_n)\n\
	{\n\
		error = 0;\n\
		orcaParseContext ctx(vm, this);\n\
		vector<orcaData> argv;\n\
		if (param_n < 1) return NIL;\n\
		\n\
		parse_set_source(vm->get_param(0).String());\n\
		int ret = %sparse();\n\
		if (error != 0) return error;\n\
		return ret;\n\
	}\n\
	\n\
	orcaData ex_yyinput(orcaVM* vm, int n)\n\
	{\n\
		char buff[2];\n\
		buff[0] = parse_input();\n\
		buff[1] = 0;\n\
		if (buff[0] == 0 || buff[0]  == -1) return \"\";\n\
		return buff;\n\
	}\n\
	orcaData ex_yyunput(orcaVM* vm, int n)\n\
	{\n\
		if (n<1) vm->need_param();\n\
		parse_unput(vm->get_param(0).String().c_str());\n\
	}\n\
	\n\
	orcaData ex_yyerror(orcaVM* vm, int n)\n\
	{\n\
		if (n<1) vm->need_param();\n\
		%serror(vm->get_param(0).String().c_str());\n\
		error = -1;\n\
	}\n\
	\n\
};\n\
\n\
extern \"C\" EXPORT void* get_parse()\n\
{\n\
	orcaParseObject* pp = new orcaParseObject();\n\
	return pp;\n\
}\n\
\n\n";






