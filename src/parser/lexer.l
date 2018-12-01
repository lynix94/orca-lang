/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  lexer.l - 

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

%{
#define __LEX__


#if !defined(UNISTD_H)
#define YY_NO_UNISTD_H
#endif

#undef yyFlexLexer

using namespace std;

int my_yyinput(char* buff, int max_size);

#include "parserParser.h"
#include "parser.hpp"
#include "orca_common.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sstream>
#include <iostream>


#ifndef WIN32
#include <readline/readline.h>
#include <readline/history.h>
#endif

#undef YY_INPUT
#define YY_INPUT(buffer, result, max_size) ( result = my_yyinput(buffer, max_size))

static bool g_shell_start = true;
static int g_string_var = 0;
static bool g_comment = false;
//%option prefix="orca"

%}

%option yyclass="orcaFlexLexer"

ws			        [ \t\r]+
cpp_comment			\/\/.*
sharp_comment		\#.*
crlf				\r\n
lf					\n

%%

{ws}				;
{cpp_comment} 		; 
{sharp_comment}		; 
{crlf}				{ g_parser->lineno++; }
{lf}				{ g_parser->lineno++; }

static				{ g_parser->n_tok++; return STATIC; }
def					{ g_parser->n_tok++; return DEF; }
clone				{ g_parser->n_tok++; return CLONE; }

my					{ g_parser->n_tok++; return MY; }
owner				{ g_parser->n_tok++; return OWNER; }
caller				{ g_parser->n_tok++; return CALLER; }
root				{ g_parser->n_tok++; return ROOT; }
module				{ g_parser->n_tok++; return MODULE; }

if					{ g_parser->n_tok++; return IF; }
elif				{ g_parser->n_tok++; return ELIF; }
else				{ g_parser->n_tok++; return ELSE; }

for					{ g_parser->n_tok++; return FOR; }
in					{ g_parser->n_tok++; return IN; }
switch				{ g_parser->n_tok++; return SWITCH; }
select				{ g_parser->n_tok++; return SELECT; }
decode				{ g_parser->n_tok++; return DECODE; }
case				{ g_parser->n_tok++; return CASE; }
default				{ g_parser->n_tok++; return DEFAULT; }
fallthrough			{ g_parser->n_tok++; return FALLTHROUGH; }
do					{ g_parser->n_tok++; return DO; }
while				{ g_parser->n_tok++; return WHILE; }
times				{ g_parser->n_tok++; return TIMES; }
parse				{ g_parser->n_tok++; return PARSE; }

continue			{ g_parser->n_tok++; return CONTINUE; }
break				{ g_parser->n_tok++; return BREAK; }
return 				{ g_parser->n_tok++; return RETURN_; }

"?stack"			{ g_parser->n_tok++; return STACK; }
"?local"			{ g_parser->n_tok++; return LOCAL; }

using				{ g_parser->n_tok++; return USING; }

true				{ g_parser->n_tok++; return TRUE; }
false				{ g_parser->n_tok++; return FALSE; }

try					{ g_parser->n_tok++; return TRY; }
catch				{ g_parser->n_tok++; return CATCH; }
finally				{ g_parser->n_tok++; return FINALLY; }
throw				{ g_parser->n_tok++; return THROW; }

nil					{ g_parser->n_tok++; return NIL_; }
parallel			{ g_parser->n_tok++; return PARALLEL; }

eval				{ g_parser->n_tok++; return EVAL; }
lambda				{ g_parser->n_tok++; return LAMBDA; }
under				{ g_parser->n_tok++; return UNDER; }



"||"				{ g_parser->n_tok++; return OR; }
"&&"				{ g_parser->n_tok++; return AND; }
">="				{ g_parser->n_tok++; return GE; }
"<="				{ g_parser->n_tok++; return LE; }
">"					{ g_parser->n_tok++; return GT; }
"<"					{ g_parser->n_tok++; return LT; }
"=="				{ g_parser->n_tok++; return EQ; }
"!="				{ g_parser->n_tok++; return NEQ; }
".."				{ g_parser->n_tok++; return DOUBLE_DOT; }
"..."				{ g_parser->n_tok++; return TRIPLE_DOT; }

"+="				{ g_parser->n_tok++; return ADD_ASSIGN; }
"-="				{ g_parser->n_tok++; return SUB_ASSIGN; }
"*="				{ g_parser->n_tok++; return MUL_ASSIGN; }
"/="				{ g_parser->n_tok++; return DIV_ASSIGN; }
":="				{ g_parser->n_tok++; return ASSIGNMENT; }

"->"				{ g_parser->n_tok++; return RIGHT_ARROW; }
"<-"				{ g_parser->n_tok++; return LEFT_ARROW; }
"+]"				{ g_parser->n_tok++; return IR_BRACKET; }



[a-zA-Z_][a-zA-Z0-9_]*	{
						g_parser->n_tok++;
						yylval.cp = g_parser->strdup(yytext);
						return NAME; 
					}

-?[0-9]+			{
						g_parser->n_tok++;
						bool minus = false;
						if (yytext[0] == '-') {
							minus = true;
							yytext++;
						}
							
						bool f_overflow = false;
						
						if (strlen(yytext) > 10) {
							f_overflow = true;
						}
						else if (strlen(yytext) == 10) {
							if (strcmp(yytext, "2147483647") > 0) {
								f_overflow = true;
							}
						}

						if (f_overflow) {
							yylval.cp = g_parser->strdup(yytext);

							if (minus) {
								return MINUS_BIG_NUMBER; 
							}

							return BIG_NUMBER;
						}
						
						yylval.integer = atoi(yytext);
						if (minus) {
							yylval.integer *= -1;
							return MINUS_NUMBER; 
						}

						return NUMBER; 
					}

-?0x[0-9a-fA-F]+	{
						g_parser->n_tok++;
						bool minus = false;
						if (yytext[0] == '-') {
							minus = true;
							yytext++;
						}
							
						char* c = yytext+2;
						int i = 0;
						unsigned long long val = 0;
						while (c[i] != '\0') {
							if (val > UINT_MAX) {
								yylval.cp = g_parser->strdup(yytext);
								if (minus) {
									return MINUS_BIG_NUMBER; 
								}

								return BIG_NUMBER;
							}
							else if (c[i] >= '0' && c[i] <='9') 
								val = val * 16 + c[i] - '0';
							else if (c[i] >= 'a' && c[i] <='f') 
								val = val * 16 + c[i] - 'a' + 10;
							else if (c[i] >= 'A' && c[i] <='F') 
								val = val * 16 + c[i] - 'A' + 10;

							i++;
						}

						yylval.integer = val;
						if (minus) {
							yylval.integer *= -1;
							return MINUS_NUMBER; 
						}

						return NUMBER; 
					}

-?0b[01]+				{
						g_parser->n_tok++;
						bool minus = false;
						if (yytext[0] == '-') {
							minus = true;
							yytext++;
						}

						char* c = yytext+2;
						int i = 0;
						unsigned long long val = 0;
						while (c[i] != '\0') {
							if (val > UINT_MAX) {
								yylval.cp = g_parser->strdup(yytext);
								if (minus) {
									return MINUS_BIG_NUMBER; 
								}

								return BIG_NUMBER;
							}

							val = val * 2 + c[i] - '0';
							i++;
						}

						yylval.integer = val;
						if (minus) {
							yylval.integer *= -1;
							return MINUS_NUMBER; 
						}

						return NUMBER; 
					}

(-?[0-9]+[Ee][\+\-]?[0-9]+)|(-?[0-9]*\.[0-9]+([Ee][\+\-]?[0-9]+)?)  {
						g_parser->n_tok++;
						bool minus = false;
						if (yytext[0] == '-') {
							minus = true;
							yytext++;
						}
							
						yylval.real = atof(yytext);
						if (minus) {
							yylval.real *= -1;
							return MINUS_REAL;
						}
						return REAL;
					}

\"\"\"				{ 
						g_parser->n_tok++;
						yylval.cp = lexer->get_comment('\"');
						return STRING;
					}

\'\'\'				{ 
						g_parser->n_tok++;
						yylval.cp = lexer->get_comment('\'');

						if (g_string_var) {
							return STRING_VAR_HEAD;
						}

						return STRING;
					}


'					{ 
						yylval.cp = lexer->get_string('\'');

						if (g_string_var) {
							return STRING_VAR_HEAD;
						}

						return STRING; 
					}

\"					{ 
						g_parser->n_tok++;
						yylval.cp = lexer->get_string('\"');

						if (g_string_var) {
							return STRING_VAR_HEAD;
						}

						return STRING; 
					}

r'					{ 
						g_parser->n_tok++;
						yylval.cp = lexer->get_string('\'');

						if (g_string_var) {
							return RE_STRING_VAR_HEAD;
						}

						return RE_STRING; 
					}

r\"					{ 
						g_parser->n_tok++;
						yylval.cp = lexer->get_string('\"');

						if (g_string_var) {
							return RE_STRING_VAR_HEAD;
						}

						return RE_STRING; 
					}

h'					{ 
						g_parser->n_tok++;
						yylval.cp = lexer->get_hex_string('\'');
						if (yylval.cp == NULL) {
							yyerror("invalid hex string format");
							return NIL_;
						}
						return HEX_STRING; 
					}

h\"					{ 
						g_parser->n_tok++;
						yylval.cp = lexer->get_hex_string('\"');
						if (yylval.cp == NULL) {
							yyerror("invalid hex string format");
							return NIL_;
						}
						return HEX_STRING; 
					}

b'					{ 
						g_parser->n_tok++;
						yylval.cp = lexer->get_bin_string('\'');
						if (yylval.cp == NULL) {
							yyerror("invalid hex string format");
							return NIL_;
						}
						return HEX_STRING; 
					}

b\"					{ 
						g_parser->n_tok++;
						yylval.cp = lexer->get_bin_string('\"');
						if (yylval.cp == NULL) {
							yyerror("invalid hex string format");
							return NIL_;
						}
						return HEX_STRING; 
					}

;					{ 
						g_parser->n_tok++;
						if (g_shell_start) {
							yylval.cp = lexer->get_string('\n');
							bool null_flag = true;
							const char* cp = yylval.cp;
							for(int i=0; i<strlen(cp); i++) {
								if (cp[i] != ' ' && cp[i] != '\t') {
									null_flag = false;
									break;
								}
							}

							if (null_flag == false) {
								return SHELL_STRING_HEAD;
							}
						}

						return ';';
					}

\}					{
						g_parser->n_tok++;
						if (g_string_var) {
							if (g_comment) 
								yylval.cp = lexer->get_comment(g_string_var);
							else 
								yylval.cp = lexer->get_string(g_string_var);

							return STRING_VAR_TAIL;
						}
						
						return '}';
					}

.					{ g_parser->n_tok++; g_shell_start = false; return yytext[0]; }

%%



int my_yyinput(char* buff, int max_size)/*{{{*/
{
	int i, n;

retry:

#ifdef WIN32
	if (g_parser->is_interactive()) {
		printf("$ ");
	}

	if (fgets(buff, max_size, g_parser->curr_fp) == NULL) {
		n = 0;
	}
	else {	
		n = strlen(buff);
	}
#else
	if (g_parser->is_interactive()) {
		char *cp, *line = readline("$ ");
		if (line != NULL) {
			for(cp = line; isspace(*cp); cp++);

			if (*cp != '\0') {
				add_history(line);
			}

			strncpy(buff, line, max_size);
			free(line);
			n = strlen(buff);
			buff[n++]='\n';
		}
	}
	else {
		if (fgets(buff, max_size, g_parser->curr_fp) == NULL) {
			n = 0;
		}
		else {
			n = strlen(buff);
		}
	}
#endif

	g_shell_start = parser_starts_with(buff, ";");

	if (g_parser->is_interactive()) {
		if (g_shell_start) {
			buff[n++] = -1;
			buff[n] = 0;
			return n;
		}

		// only whitespaces exist.
		if (i == strlen(buff)) { 
			goto retry;
		}
		
		// delay mode
		if (n >= 2 && buff[n-2] != ';') {
			do {
				printf("* ");
				char add[1024*5];
				if (fgets(add, sizeof(add), g_parser->curr_fp) == NULL) {
					break;
				}

				if (add[0] == '\r' || add[0] == '\n') {
					g_parser->lineno++;
					break;
				}

				// fix. check max_size
				strcat(buff, add);

			} while((strlen(buff) + 100) < max_size);
		}

		n = strlen(buff);
		buff[n++] = -1;
		buff[n] = 0;
	}

	return n;
}
/*}}}*/

const char* orcaFlexLexer::get_string(char end)/*{{{*/
{
	char c;
	string str;
	int i = 0;

	while ((c = lexer->yyinput()) != end && c != 0 && c!= -1) {
		if (c == '\r' || c == '\n') { 
			g_parser->lineno++;
			break;
		}

		if (c == '\\') {
			c = lexer->yyinput();
			if (c == '\r' || c == '\n') { g_parser->lineno++; }

			if (c == 0 || c == -1) {
				yyerror("empty stream");
				return "";
			}

			switch(c)
			{
			case 'n': str += '\n'; break;
			case 'r': str += '\r'; break; 
			case 'a': str += '\a'; break; 
			case 'b': str += '\b'; break; 
			case 't': str += '\t'; break;
			default: str += c; break;
			}

			continue;
		}

		if (c == '$') {
			c = lexer->yyinput();
			if (c == '\r' || c == '\n') { g_parser->lineno++; }

			if (c == end) {
				str += '$';
				break;
			}
			else if (c != '{') {
				str += '$';
				str += c;
				continue;
			}
			else {
				lexer->yyunput('{', (char*)lexer->YYText());
				lexer->yyunput('$', (char*)lexer->YYText());
				if (g_string_var && g_string_var != end) yyerror("nested format string is not allowed");
				g_string_var = end;
				break;
			}
		}
		else {
			str += c;
		}
	}

	if (c == end) {
		if (c == '\n' || c == '\r') g_parser->lineno++;
		if (g_string_var == c) {
			g_string_var = 0;
		}
	}

	return g_parser->strdup(str.c_str());
}
/*}}}*/

const char* orcaFlexLexer::get_comment(char end)/*{{{*/
{
	char c;
	string str;
	int i = 0;
	g_comment = true;

	while ((c = lexer->yyinput()) != 0 && c != -1) {
		if (c == '\r' || c == '\n') { g_parser->lineno++; }

		if (c == end) {
			char c2 = lexer->yyinput();
			if (c2 == '\r' || c2 == '\n') { g_parser->lineno++; }

			if (c2 == end) {
				char c3 = lexer->yyinput();
				if (c3 == '\r' || c3 == '\n') { g_parser->lineno++; }

				if (c3 == end) {
					g_string_var = 0;
					g_comment = false;
					break;
				}	
				lexer->yyunput(c3, (char*)lexer->YYText());
			}
			lexer->yyunput(c2, (char*)lexer->YYText());
		}

		if (c == '\r' || c == '\n') { 
			g_parser->lineno++;
		}

		if (end == '\'' && c == '$') {
			c = lexer->yyinput();
			if (c == '\r' || c == '\n') { g_parser->lineno++; }

			if (c != '{') {
				str += '$';
				str += c;
				continue;
			}
			else {
				lexer->yyunput('{', (char*)lexer->YYText());
				lexer->yyunput('$', (char*)lexer->YYText());
				g_string_var = end;
				break;
			}
		}

		str += c;
	}

	return g_parser->strdup(str.c_str());
}
/*}}}*/

string orcaFlexLexer::get_raw_context()/*{{{*/
{
	char c;
	char open = '{';
	char close = '}';
	int depth = 1;

	string str;
	
	while ((c = lexer->yyinput()) != 0 && c != -1) {
		if (c == '\r' || c == '\n') { g_parser->lineno++; }

		if (c == open) depth++;
		else if (c == close) depth--;

		if (depth == 0 && c == close) {
			break;
		}

		str += c;
	}

	yyunput_string("}"); // recover last '}'

	return str;

}
/*}}}*/

const char* orcaFlexLexer::get_context()/*{{{*/
{
	string raw_str = get_raw_context();
	string ctx, def;
	parser_split_ctx_def(raw_str, ctx, def);

	yyunput_string(def.c_str());
	
	//printf("# lexer get_context> '%s'\n", ctx.c_str());
	return g_parser->strdup(ctx.c_str());
}
/*}}}*/

void orcaFlexLexer::yyunput_string(const char* str)/*{{{*/
{
	const char* cp = str + strlen(str) - 1;
	while (cp >= str) {
		lexer->yyunput((int)*cp, (char*)lexer->YYText());
		cp--;
	}
}
/*}}}*/

const char* orcaFlexLexer::get_hex_string(char end)/*{{{*/
{
	char c;
	string str;
	int i = 0;

	while ((c = lexer->yyinput()) != end && c != 0 && c!= -1) {
		if (c == '\r' || c == '\n') { 
			g_parser->lineno++;
			break;
		}

		str += c;
	}

	string out;
	for (int i=0; i<str.length(); i++) {
		int h = str[i];
		if (h == ' ' || h == '\t') continue;
		if (++i == str.length()) return NULL;
		int l = str[i];

		if (isdigit(h)) h -= '0';
		else if (isalpha(h)) h = tolower(h) - 'a' + 10;
		else return NULL;

		if (isdigit(l)) l -= '0';
		else if (isalpha(l)) l = tolower(l) - 'a' + 10;
		else return NULL;

		if (h > 15 || l > 15) return NULL;

		out += h<<4 | l;
	}

	return g_parser->strdup(out.c_str());
}
/*}}}*/

const char* orcaFlexLexer::get_bin_string(char end)/*{{{*/
{
	char c;
	string str;
	int i = 0;

	while ((c = lexer->yyinput()) != end && c != 0 && c!= -1) {
		if (c == '\r' || c == '\n') { 
			g_parser->lineno++;
			break;
		}

		str += c;
	}

	string out;
	int offset = 0;
	int val = 0;
	for (int i=0; i<str.length(); i++) {
		int b = str[i];
		if (b == ' ' || b == '\t') continue;
		if (b != '0' && b != '1') return NULL;
		b -= '0';

		offset++;	
		val <<= 1;
		val += b;
		if ((offset % 8) == 0) {
			out += val;
			val = 0;
		}
	}

	if (val != 0) {
		val <<= (8 - offset % 8);
		out += val;
	}

	return g_parser->strdup(out.c_str());
}
/*}}}*/




