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
%%%%\n\n";


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
int %sparse (void);\n\
class orcaParseObject : public orcaObject\n\
{\n\
public:\n\
	orcaData operator()(orcaVM* vm, int param_n)\n\
	{\n\
		orcaParseContext ctx(vm, this);\n\
		vector<orcaData> argv;\n\
		if (param_n < 1) return NIL;\n\
		\n\
		parse_set_source(vm->get_param(0).String());\n\
		int ret = %sparse();\n\
		return ret;\n\
	}\n\
};\n\
\n\
extern \"C\" EXPORT void* get_parse()\n\
{\n\
	orcaParseObject* pp = new orcaParseObject();\n\
	return pp;\n\
}\n\
\n\
extern char *%stext;\n\
void %serror(const char* s)\n\
{\n\
	parse_set_error(s, %stext);\n\
}\n\
\n\
extern \"C\" int %swrap()\n\
{\n\
	return 1;\n\
}\n\n";






