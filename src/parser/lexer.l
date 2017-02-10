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

using namespace std;

int my_yyinput(char* buff, int max_size);

#include "parser_common.h"
#include "parser.hpp"
#include "orca_common.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifndef WIN32
#include <readline/readline.h>
#include <readline/history.h>
#endif

#undef YY_INPUT
#define YY_INPUT(buffer, result, max_size) ( result = my_yyinput(buffer, max_size))

static bool g_shell_start = true;
static int g_format_string = 0;
static bool g_comment = false;
static const char* get_string(char end);
static const char* get_comment(char end);
//static const char* get_context();
const char* get_context();
static const char* get_hex_string(char end);
static const char* get_bin_string(char end);
%}

ws			        [ \t\r]+
cpp_comment			\/\/.*
sharp_comment		\#.*
crlf				\r\n
lf					\n

%%

{ws}				;
{cpp_comment} 		; 
{sharp_comment}		; 
{crlf}				{ parser_lineno++; }
{lf}				{ parser_lineno++; }

static				{ return STATIC; }
def					{ return DEF; }
clone				{ return CLONE; }

my					{ return MY; }
owner				{ return OWNER; }
caller				{ return CALLER; }
root				{ return ROOT; }
module				{ return MODULE; }

if					{ return IF; }
elif				{ return ELIF; }
else				{ return ELSE; }

for					{ return FOR; }
in					{ return IN; }
switch				{ return SWITCH; }
decode				{ return DECODE; }
do					{ return DO; }
while				{ return WHILE; }
times				{ return TIMES; }
parse				{ return PARSE; }

continue			{ return CONTINUE; }
break				{ return BREAK; }
return 				{ return RETURN_; }

"?stack"			{ return STACK; }
"?local"			{ return LOCAL; }

using				{ return USING; }

true				{ return TRUE; }
false				{ return FALSE; }

try					{ return TRY; }
catch				{ return CATCH; }
finally				{ return FINALLY; }
throw				{ return THROW; }

nil					{ return NIL_; }
parallel			{ return PARALLEL; }

eval				{ return EVAL; }



"||"				{ return OR; }
"&&"				{ return AND; }
">="				{ return GE; }
"<="				{ return LE; }
">"					{ return GT; }
"<"					{ return LT; }
"=="				{ return EQ; }
"!="				{ return NEQ; }
".."				{ return DOUBLE_DOT; }
"..."				{ return TRIPLE_DOT; }

"+="				{ return ADD_ASSIGN; }
"-="				{ return SUB_ASSIGN; }
"*="				{ return MUL_ASSIGN; }
"/="				{ return DIV_ASSIGN; }
":="				{ return ASSIGNMENT; }

"->"				{ return RIGHT_ARROW; }
"<-"				{ return LEFT_ARROW; }



[a-zA-Z_][a-zA-Z0-9_]*	{
						yylval.cp = parser_strdup(yytext);
						return NAME; 
					}

-?[0-9]+			{
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
							yylval.cp = parser_strdup(yytext);

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
								yylval.cp = parser_strdup(yytext);
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
								yylval.cp = parser_strdup(yytext);
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
						yylval.cp = get_comment('\"');
						return STRING;
					}

\'\'\'				{ 
						yylval.cp = get_comment('\'');

						if (g_format_string) {
							return FORMAT_STRING_HEAD;
						}

						return STRING;
					}


'					{ 
						yylval.cp = get_string('\'');

						if (g_format_string) {
							return FORMAT_STRING_HEAD;
						}

						return STRING; 
					}

\"					{ 
						yylval.cp = get_string('\"');

						if (g_format_string) {
							return FORMAT_STRING_HEAD;
						}

						return STRING; 
					}

r'					{ 
						yylval.cp = get_string('\'');

						if (g_format_string) {
							return RE_FORMAT_STRING_HEAD;
						}

						return RE_STRING; 
					}

r\"					{ 
						yylval.cp = get_string('\"');

						if (g_format_string) {
							return RE_FORMAT_STRING_HEAD;
						}

						return RE_STRING; 
					}

h'					{ 
						yylval.cp = get_hex_string('\'');
						if (yylval.cp == NULL) {
							yyerror("invalid hex string format");
							return NIL_;
						}
						return HEX_STRING; 
					}

h\"					{ 
						yylval.cp = get_hex_string('\"');
						if (yylval.cp == NULL) {
							yyerror("invalid hex string format");
							return NIL_;
						}
						return HEX_STRING; 
					}

b'					{ 
						yylval.cp = get_bin_string('\'');
						if (yylval.cp == NULL) {
							yyerror("invalid hex string format");
							return NIL_;
						}
						return HEX_STRING; 
					}

b\"					{ 
						yylval.cp = get_bin_string('\"');
						if (yylval.cp == NULL) {
							yyerror("invalid hex string format");
							return NIL_;
						}
						return HEX_STRING; 
					}

;					{ 
						if (g_shell_start) {
							yylval.cp = get_string('\n');
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
						if (g_format_string) {
							if (g_comment) 
								yylval.cp = get_comment(g_format_string);
							else 
								yylval.cp = get_string(g_format_string);

							return FORMAT_STRING_TAIL;
						}
						
						return '}';
					}

"%1{"				{ return ONCE; }

.					{ g_shell_start = false; return yytext[0]; }

%%


int my_yyinput(char* buff, int max_size)/*{{{*/
{
	int i, n;

retry:

#ifdef WIN32
	if (is_interactive()) {
	    parser_curr_fp = stdin;
		printf("$ ");
	}

	if (fgets(buff, max_size, parser_curr_fp) == NULL) {
		n = 0;
	}
	else {	
		n = strlen(buff);
	}
#else
	if (is_interactive()) {
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
		if (fgets(buff, max_size, parser_curr_fp) == NULL) {
			n = 0;
		}
		else {
			n = strlen(buff);
		}
	}
#endif

	g_shell_start = false;
	for(i=0; i<strlen(buff); i++) {
		char c = buff[i];

		// if first character is ';', this is shell stmt
		if (c == ';') {	
			g_shell_start = true;
			break;
		}

		if (c != ' ' && c != '\t' && 
		    c != '\n' && c != '\r') 
		{
			break;
		}
	}


	if (is_interactive()) {
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
				if (fgets(add, sizeof(add), parser_curr_fp) == NULL) {
					break;
				}

				if (add[0] == '\r' || add[0] == '\n') {
					parser_lineno++;
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

static const char* get_string(char end)/*{{{*/
{
	char c;
	string str;
	int i = 0;

	while ((c = lexer->yyinput()) != end && c != 0 && c!= -1) {
		if (c == '\r' || c == '\n') { 
			parser_lineno++;
			break;
		}

		if (c == '\\') {
			c = lexer->yyinput();
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
			if (c != '{') {
				str += '$';
				str += c;
				continue;
			}
			else {
				lexer->yyunput('{', (char*)lexer->YYText());
				lexer->yyunput('$', (char*)lexer->YYText());
				if (g_format_string && g_format_string != end) yyerror("nested format string is not allowed");
				g_format_string = end;
				break;
			}
		}

		str += c;
	}

	if (c == end && g_format_string == c) {
		g_format_string = 0;
	}

	return parser_strdup(str.c_str());
}
/*}}}*/

static const char* get_comment(char end)/*{{{*/
{
	char c;
	string str;
	int i = 0;
	g_comment = true;

	while ((c = lexer->yyinput()) != 0 && c != -1) {
		if (c == end) {
			char c2 = lexer->yyinput();
			if (c2 == end) {
				char c3 = lexer->yyinput();
				if (c3 == end) {
					g_format_string = 0;
					g_comment = false;
					break;
				}	
				lexer->yyunput(c3, (char*)lexer->YYText());
			}
			lexer->yyunput(c2, (char*)lexer->YYText());
		}

		if (c == '\r' || c == '\n') { 
			parser_lineno++;
		}

		if (end == '\'' && c == '$') {
			c = lexer->yyinput();
			if (c != '{') {
				str += '$';
				str += c;
				continue;
			}
			else {
				lexer->yyunput('{', (char*)lexer->YYText());
				lexer->yyunput('$', (char*)lexer->YYText());
				g_format_string = end;
				break;
			}
		}

		str += c;
	}

	return parser_strdup(str.c_str());
}
/*}}}*/

const char* get_context()/*{{{*/
{
	char c;
	char open = '{';
	char close = '}';
	int depth = 0;

	string str;
	depth++;

	
	c = lexer->yyinput();

	while ((c = lexer->yyinput()) != 0 && c != -1) {
		if (c == open) depth++;
		if (c == close) depth--;

		if (depth == 0 && c == close) {
			break;
		}


		if (c == '\r' || c == '\n') { 
			parser_lineno++;
		}

		str += c;
	}

	return parser_strdup(str.c_str());
}
/*}}}*/
static const char* get_hex_string(char end)/*{{{*/
{
	char c;
	string str;
	int i = 0;

	while ((c = lexer->yyinput()) != end && c != 0 && c!= -1) {
		if (c == '\r' || c == '\n') { 
			parser_lineno++;
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

	return parser_strdup(out.c_str());
}
/*}}}*/

static const char* get_bin_string(char end)/*{{{*/
{
	char c;
	string str;
	int i = 0;

	while ((c = lexer->yyinput()) != end && c != 0 && c!= -1) {
		if (c == '\r' || c == '\n') { 
			parser_lineno++;
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

	return parser_strdup(out.c_str());
}
/*}}}*/




