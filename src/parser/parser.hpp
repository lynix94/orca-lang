/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_PARSER_PARSER_HPP_INCLUDED
# define YY_YY_SRC_PARSER_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NEW_LINE = 258,
    STATIC = 259,
    DEF = 260,
    CLONE = 261,
    MY = 262,
    OWNER = 263,
    CALLER = 264,
    ROOT = 265,
    MODULE = 266,
    PARENT = 267,
    IF = 268,
    ELIF = 269,
    ELSE = 270,
    DO = 271,
    WHILE = 272,
    TIMES = 273,
    SWITCH = 274,
    DECODE = 275,
    PARSE = 276,
    FOR = 277,
    IN = 278,
    RETURN_ = 279,
    CONTINUE = 280,
    BREAK = 281,
    EQ = 282,
    NEQ = 283,
    AND = 284,
    OR = 285,
    GT = 286,
    GE = 287,
    LT = 288,
    LE = 289,
    TRY = 290,
    CATCH = 291,
    FINALLY = 292,
    THROW = 293,
    DUMP = 294,
    STACK = 295,
    LOCAL = 296,
    USING = 297,
    TRUE = 298,
    FALSE = 299,
    DOUBLE_DOT = 300,
    TRIPLE_DOT = 301,
    ADD_ASSIGN = 302,
    SUB_ASSIGN = 303,
    MUL_ASSIGN = 304,
    DIV_ASSIGN = 305,
    NIL_ = 306,
    RIGHT_ARROW = 307,
    LEFT_ARROW = 308,
    PARALLEL = 309,
    ASSIGNMENT = 310,
    ONCE = 311,
    EVAL = 312,
    LAMBDA = 313,
    UNDER = 314,
    NAME = 315,
    STRING = 316,
    FORMAT_STRING_HEAD = 317,
    FORMAT_STRING_TAIL = 318,
    RE_STRING = 319,
    RE_FORMAT_STRING_HEAD = 320,
    HEX_STRING = 321,
    SHELL_STRING_HEAD = 322,
    CONTEXT = 323,
    NUMBER = 324,
    MINUS_NUMBER = 325,
    BIG_NUMBER = 326,
    MINUS_BIG_NUMBER = 327,
    REAL = 328,
    MINUS_REAL = 329
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 53 "../src/parser/parser.y" /* yacc.c:1909  */

	const char* cp;
	int integer;
	double real;
	void* vector_cp;	
	struct bnf* bp;	
	struct cp2_t cp2; 
	struct int2_t int2;

#line 139 "../src/parser/parser.hpp" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_PARSER_HPP_INCLUDED  */
