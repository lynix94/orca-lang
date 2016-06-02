/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2013 Free Software Foundation, Inc.

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0






/* First part of user declarations.  */
#line 11 "../src/parser/parser.y" /* glr.c:207  */

#define __YACC__


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // tolower
#include <limits.h>
#include <vector>

#include "parser_common.h"

#include "parserCode.h"
#include "parserControl.h"
#include "parserOP.h"
#include "parserException.h"
#include "orca_opcode.h"
#include "parserParse.h"

parserException s_ex;
parserException* g_ex = &s_ex;

// For parser
bool unary_minus = false;

int g_lvar_nil_check = 0;
int g_bnf_right_num = 0;

using namespace std;


const char* get_context();


#line 91 "../src/parser/parser.cpp" /* glr.c:207  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;

/* Copy the second part of user declarations.  */

#line 119 "../src/parser/parser.cpp" /* glr.c:230  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify clang.  */
# define YYLONGJMP(Env, Val) (longjmp (Env, Val), YYASSERT (0))
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#ifndef YYASSERT
# define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  163
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2167

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  160
/* YYNRULES -- Number of rules.  */
#define YYNRULES  322
/* YYNRULES -- Number of states.  */
#define YYNSTATES  521
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 9
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,     2,     2,    92,    82,     2,     2,
      83,    84,    90,    88,    77,    89,    78,    91,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    76,    75,
       2,    81,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    85,     2,    86,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,    80,    74,    79,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   184,   184,   185,   186,   191,   192,   197,   198,   203,
     204,   209,   219,   220,   221,   222,   223,   224,   225,   229,
     233,   234,   235,   236,   237,   243,   242,   255,   254,   263,
     262,   274,   278,   292,   306,   314,   314,   327,   328,   336,
     340,   346,   345,   358,   357,   365,   370,   375,   376,   382,
     381,   390,   389,   399,   398,   410,   414,   422,   426,   434,
     440,   448,   452,   460,   464,   468,   477,   480,   488,   489,
     495,   494,   507,   506,   537,   538,   544,   543,   551,   561,
     562,   567,   572,   572,   581,   586,   591,   599,   600,   601,
     606,   610,   618,   628,   636,   637,   642,   646,   642,   657,
     658,   663,   671,   675,   683,   687,   691,   699,   707,   708,
     709,   710,   715,   719,   727,   731,   739,   743,   751,   755,
     763,   768,   767,   781,   780,   791,   790,   800,   812,   811,
     823,   829,   834,   853,   878,   911,   914,   923,   926,   930,
     936,   940,   950,   956,   966,   970,   974,   980,   990,   994,
    1003,  1007,  1002,  1016,  1015,  1025,  1024,  1034,  1033,  1046,
    1045,  1058,  1062,  1057,  1074,  1073,  1085,  1093,  1097,  1105,
    1109,  1113,  1121,  1122,  1128,  1127,  1146,  1145,  1166,  1165,
    1185,  1184,  1209,  1208,  1233,  1232,  1254,  1253,  1275,  1274,
    1296,  1295,  1316,  1321,  1325,  1329,  1333,  1337,  1345,  1351,
    1350,  1360,  1366,  1365,  1375,  1380,  1384,  1389,  1393,  1397,
    1401,  1405,  1409,  1413,  1418,  1423,  1427,  1431,  1436,  1441,
    1446,  1451,  1455,  1459,  1463,  1469,  1468,  1479,  1480,  1485,
    1489,  1493,  1497,  1501,  1506,  1510,  1514,  1518,  1526,  1530,
    1539,  1544,  1538,  1556,  1561,  1562,  1567,  1571,  1579,  1583,
    1591,  1592,  1600,  1601,  1606,  1605,  1614,  1618,  1626,  1631,
    1632,  1633,  1634,  1635,  1646,  1650,  1654,  1658,  1662,  1666,
    1670,  1674,  1678,  1682,  1686,  1690,  1694,  1699,  1704,  1709,
    1708,  1716,  1720,  1724,  1729,  1734,  1739,  1745,  1744,  1754,
    1762,  1767,  1772,  1771,  1779,  1784,  1790,  1795,  1799,  1807,
    1815,  1819,  1823,  1827,  1831,  1839,  1847,  1848,  1856,  1857,
    1865,  1877,  1881,  1886,  1890,  1891,  1899,  1907,  1915,  1923,
    1931,  1939,  1947
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NEW_LINE", "STATIC", "DEF", "CLONE",
  "MY", "OWNER", "CALLER", "ROOT", "MODULE", "PARENT", "IF", "ELIF",
  "ELSE", "DO", "WHILE", "TIMES", "SWITCH", "DECODE", "PARSE", "FOR", "IN",
  "RETURN_", "CONTINUE", "BREAK", "EQ", "NEQ", "AND", "OR", "GT", "GE",
  "LT", "LE", "TRY", "CATCH", "FINALLY", "THROW", "DUMP", "STACK", "LOCAL",
  "USING", "TRUE", "FALSE", "DOUBLE_DOT", "TRIPLE_DOT", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "PURE", "NIL_", "RIGHT_ARROW",
  "LEFT_ARROW", "PARALLEL", "ASSIGNMENT", "ONCE", "NAME", "STRING",
  "FORMAT_STRING_HEAD", "FORMAT_STRING_TAIL", "RE_STRING",
  "RE_FORMAT_STRING_HEAD", "HEX_STRING", "SHELL_STRING_HEAD", "CONTEXT",
  "NUMBER", "MINUS_NUMBER", "BIG_NUMBER", "MINUS_BIG_NUMBER", "REAL",
  "MINUS_REAL", "'{'", "'}'", "';'", "':'", "','", "'.'", "'~'", "'|'",
  "'='", "'%'", "'('", "')'", "'['", "']'", "'!'", "'+'", "'-'", "'*'",
  "'/'", "'$'", "$accept", "statement_list", "statement_or_block",
  "statement_block", "open_statement_block", "statement", "scope_stmt",
  "$@1", "parallel_stmt", "$@2", "$@3", "parallel_option",
  "simple_call_stmt", "shell_stmt", "$@4", "shell_string",
  "exception_stmt", "try_stmt", "$@5", "catch_stmt_list_with_finally",
  "$@6", "finally_stmt", "catch_stmt_list", "catch_stmt", "$@7", "$@8",
  "$@9", "throw_stmt", "using_stmt", "object_path", "debug_stmt",
  "control_stmt", "opt_expr_list", "selection_stmt", "decode_stmt", "$@10",
  "parse_stmt", "$@11", "bnf_stmt_list", "bnf_stmt", "$@12",
  "bnf_right_list", "bnf_left", "bnf_right", "$@13", "bnf_right_",
  "bnf_node_list", "bnf_node", "terminal", "non_terminal", "action_code",
  "decode_pattern_stmt_list", "decode_pattern_stmt", "$@14", "$@15",
  "decode_pattern", "list_pattern", "pattern_list", "pattern", "p_var",
  "loop_stmt", "define_option_list", "define_option", "define_prefix",
  "name_or_string", "define_stmt", "$@16", "$@17", "$@18", "once_expr",
  "$@19", "lambda_object", "context_lambda_obj", "define_start",
  "lambda_define_start", "opt_superclass", "opt_argument_list",
  "name_list", "if_elif_else_stmt", "elif_stmt_list", "elif_stmt", "$@20",
  "$@21", "else_stmt", "$@22", "if_stmt", "$@23", "do_stmt", "$@24",
  "times_stmt", "$@25", "while_stmt", "$@26", "$@27", "for_stmt", "$@28",
  "expression_stmt", "expression_list", "tuple_expression_list",
  "expression", "assign_expr", "$@29", "$@30", "$@31", "$@32", "$@33",
  "$@34", "$@35", "$@36", "$@37", "assign_type", "bool_expr", "or_expr",
  "$@38", "and_expr", "$@39", "not_expr", "logical_expr", "numeric_expr",
  "add_expr", "mul_expr", "unary_expr", "$@40", "list", "tuple", "map",
  "sbf", "$@41", "$@42", "sbf_result", "sbf_rule_list", "sbf_rule",
  "in_expr", "range_expr", "range_expr_sub", "$@43", "pair_list",
  "pair_expression", "primary_object", "postfix_object", "$@44", "$@45",
  "slice_expression", "$@46", "calling_body", "object", "reserved_object",
  "lvar", "format_string", "re_format_string", "format_object", "regex",
  "string", "name", "minus_number", "number", "minus_big_number",
  "big_number", "real", "minus_real", YY_NULLPTR
};
#endif

#define YYPACT_NINF -358
#define YYTABLE_NINF -296

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short int yypact[] =
{
    1136,  -358,   -57,  -358,  -358,  -358,  -358,  -358,  1996,  -358,
    -358,  1824,    29,    -7,  1824,   -11,    32,  -358,    91,  -358,
    -358,    91,  -358,  -358,    77,  -358,  -358,   157,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  1824,  -358,    77,     6,  1824,  1824,   595,  2082,  -358,
     696,  -358,  -358,  -358,  -358,  -358,    59,  -358,   125,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,    14,  -358,    -1,
    -358,  -358,  -358,  -358,    58,    92,  -358,   240,  -358,  -358,
    -358,  -358,  -358,   143,    -4,  -358,  -358,   139,   155,  -358,
    -358,   282,   206,    40,  -358,  -358,  -358,  -358,  -358,  -358,
      89,   115,  -358,    90,   113,   113,  -358,  -358,     2,  -358,
    -358,  -358,  -358,  -358,  -358,    -7,   123,    77,    77,   129,
     140,    98,  -358,  -358,  1222,  1996,    -1,  -358,  -358,    91,
     200,  -358,   153,   159,  -358,  -358,  -358,    92,  -358,    70,
    -358,  -358,    39,    90,    90,  -358,    -7,   792,   165,    49,
    -358,    90,    90,  -358,   198,    16,   -25,   193,   205,   232,
    -358,  -358,  2082,  -358,   878,  -358,  -358,  -358,   113,    91,
    -358,   224,  -358,  -358,  -358,    57,   -15,  -358,  1824,  -358,
     878,  -358,  -358,   213,   258,  -358,  -358,  -358,  1824,   275,
      92,  -358,  -358,   595,   595,   595,   595,   595,   595,   595,
     595,  -358,  -358,  -358,  2082,  2082,  2082,    69,  1308,   209,
    1824,  -358,  -358,  -358,  -358,  -358,  -358,   223,  -358,  -358,
     128,   -30,    -7,  -358,  -358,  -358,  -358,  -358,    69,  1308,
     283,  -358,  -358,   225,   129,   226,   234,   129,  2082,  -358,
    -358,  -358,  1824,    91,   233,  -358,  -358,  -358,  1222,   288,
    -358,   964,  -358,  1824,  -358,  1394,  -358,  -358,  1824,  1480,
    1824,  -358,  1824,  1824,  -358,  -358,  1566,  1824,  -358,  -358,
    1050,    -2,  -358,    92,   148,   280,  -358,   236,  -358,    41,
    -358,  -358,  -358,  -358,   159,    92,  1996,  -358,  -358,  -358,
    -358,  -358,  -358,  1996,  1996,  -358,  -358,  -358,  -358,  -358,
    -358,    40,    40,  -358,  -358,  -358,   209,    90,    90,   149,
     242,   156,  1652,  -358,   152,  1824,  1824,  -358,  -358,   248,
     249,  1222,  -358,  -358,   181,  1996,  -358,  -358,  -358,  -358,
     247,   191,  -358,  -358,  1824,  1824,  -358,  2082,  -358,  -358,
    -358,  -358,  1824,  1824,  -358,   246,  -358,  -358,    68,  -358,
    -358,   -61,  -358,  -358,    -7,    92,    92,  -358,  -358,    48,
    -358,  1824,  -358,   251,  1222,  1222,   155,  -358,  -358,  -358,
    -358,  1824,  1824,    90,    90,  -358,    74,  -358,  -358,   267,
    -358,  -358,  -358,  -358,   256,  1222,   266,  -358,  1910,   268,
     270,  -358,  -358,  -358,  -358,   286,  -358,  -358,  -358,  1824,
    -358,  1824,  -358,   271,  -358,  -358,   261,  -358,   272,  -358,
    -358,  -358,  1824,  1824,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,   -41,   296,  -358,   273,  -358,   109,
    -358,  -358,    31,  1222,  1824,   276,  1996,   269,   274,    -7,
      92,  -358,  -358,  1222,  -358,  -358,  1824,  1824,  -358,  -358,
    1910,   277,  1824,   279,   -29,  -358,  -358,  -358,  -358,  -358,
     298,  -358,  -358,   -54,  -358,  -358,   303,  -358,  -358,  -358,
    -358,  -358,  -358,  1222,  -358,   285,    -7,  -358,  -358,   137,
    -358,  -358,   291,  1824,  1222,  1996,  -358,  1738,  -358,  -358,
    -358,   289,  -358,  -358,  -358,  -358,  -358,   290,  -358,   292,
    -358,    15,  -358,    50,  1824,  1824,  1824,  -358,  -358,  -358,
      50,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned short int yydefact[] =
{
      35,   114,   117,   304,   300,   301,   302,   303,     0,   157,
     161,     0,     0,     0,    66,     0,     0,    41,     0,    61,
      62,     0,   273,   274,     0,   115,   275,     0,   128,   316,
     313,   307,   311,   309,   315,   318,   317,   320,   319,   321,
     322,     0,    24,     0,     0,     0,    66,     0,     0,   225,
      35,     4,    20,    21,    18,    19,     0,    16,     0,    40,
      17,    23,    12,    13,    69,    22,    14,     0,   113,   137,
      15,   173,   262,   131,   135,     0,    68,   144,   109,   111,
     110,   108,    11,     0,   168,   172,   192,   198,   201,   204,
     206,   213,   214,   220,   224,   259,   260,   261,   233,   290,
     299,   228,   272,   263,   314,   312,   270,   271,   305,   265,
     264,   267,   266,   268,   269,     0,   117,     0,     0,   137,
       0,   299,   228,   263,    35,     0,   137,   125,    70,     0,
       0,   305,     0,    67,   168,    64,    65,     0,   119,     0,
      60,   118,     0,   283,   284,    27,     0,    35,     0,     0,
     257,   285,   286,   240,     0,     0,     0,     0,    67,   168,
     205,   227,     0,     1,    35,     3,     2,    38,    36,    53,
      39,    45,    48,   116,   112,     0,   137,   134,     0,   123,
      35,   130,   150,     0,   147,   149,   145,   166,     0,     0,
       0,   199,   202,     0,     0,     0,     0,     0,     0,     0,
       0,   217,   218,   219,     0,     0,     0,     0,     0,     0,
       0,   194,   195,   196,   197,   193,   174,     0,   306,   308,
       0,     0,     0,   283,   284,   285,   286,   155,     0,     0,
       0,     6,     5,     0,   137,     0,     0,   137,     0,    63,
      42,    55,     0,     0,     0,    57,   184,   186,    35,     0,
      10,    35,   129,     0,   238,     0,   188,   190,     0,     0,
       0,   234,     0,   171,   276,   229,     0,     0,   226,     8,
      35,   168,    37,     0,    49,     0,    47,     0,   138,     0,
     143,   121,   120,   133,   136,     0,     0,   153,   148,   146,
     167,   159,    26,     0,     0,   211,   212,   207,   208,   209,
     210,   215,   216,   223,   221,   222,     0,   277,   278,   292,
     296,     0,     0,   280,     0,     0,     0,   288,   132,     0,
       0,    35,   277,   278,     0,     0,   162,    96,    96,    72,
       0,     0,    59,    58,     0,     0,    28,     0,     9,   258,
     239,   256,     0,     0,   243,     0,   235,   169,     0,   170,
     230,     0,     7,    54,     0,     0,     0,    44,   139,     0,
     140,     0,   124,     0,    35,    35,   200,   203,   289,   176,
     178,     0,   294,   282,   281,   297,     0,    34,   175,     0,
     127,   156,   282,   281,     0,    35,    96,    95,     0,    96,
       0,   164,    56,   185,   187,    31,   189,   191,   241,     0,
     236,     0,   231,    51,    50,    46,     0,   142,     0,   151,
     154,   160,     0,     0,   293,   291,   182,   180,   298,   310,
     158,   163,   126,    94,     0,     0,   100,    99,   103,   105,
     104,    71,     0,    35,     0,     0,     0,     0,     0,     0,
       0,   141,   122,    35,   177,   179,     0,     0,   107,    97,
       0,     0,     0,     0,     0,    75,    76,    81,    92,   165,
      32,    29,   246,     0,   245,   247,   263,   237,   232,    52,
     152,   183,   181,    35,   102,   105,     0,   101,   106,     0,
      73,    74,     0,     0,    35,     0,   242,     0,    98,    90,
      91,     0,    82,    33,    30,   244,   254,   248,   249,   251,
      78,     0,    80,     0,     0,   253,     0,    77,    82,    83,
      84,    86,    87,    88,    89,    93,   255,   252,   250,    79,
      85
};

  /* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -358,    12,  -222,   -26,  -358,    13,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,   187,  -358,  -358,  -358,  -358,  -358,   -14,
    -358,  -358,   325,  -358,  -358,  -358,  -358,  -358,  -358,   -82,
    -358,  -358,  -358,  -135,  -358,  -358,  -358,  -136,  -103,  -357,
    -358,    51,  -172,  -358,  -358,  -358,  -358,  -358,   -73,  -165,
    -358,  -358,   313,    42,     3,  -358,  -358,  -358,  -358,  -358,
    -358,  -328,  -358,   370,  -358,  -358,  -167,    28,  -358,  -358,
     199,  -358,  -358,   201,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,    -8,  -358,   -10,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -104,    -6,  -358,  -358,    93,  -358,    94,   337,   141,  -358,
      88,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,   -98,  -358,  -358,  -358,  -358,  -358,   135,  -358,   357,
    -358,  -358,   163,  -358,    87,    33,   -21,   250,  -358,  -358,
     -95,  -358,   174,   -13,   307,  -358,   308,  -358,  -358,   309
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,   270,   230,   231,   252,   232,    52,   190,    53,   248,
     484,   435,    54,    55,    56,   168,    57,    58,   137,   170,
     275,   357,   171,   172,   355,   440,   273,    59,    60,   139,
      61,    62,   132,    63,    64,   236,    65,   390,   454,   455,
     482,   501,   456,   502,   503,   509,   510,   511,   512,   457,
     514,   386,   387,   388,   473,   425,   426,   427,   428,   429,
      66,    67,    68,   119,   140,    70,   361,   285,   235,    71,
     147,    72,    73,    74,    75,   179,   177,   279,    76,   184,
     185,   286,   443,   186,   364,    77,   321,    78,   124,    79,
     365,    80,   125,   385,    81,   433,    82,    83,   155,    84,
      85,   315,   412,   413,   447,   446,   334,   335,   342,   343,
     216,    86,    87,   293,    88,   294,    89,    90,    91,    92,
      93,    94,   162,    95,    96,    97,    98,   258,   436,   345,
     463,   464,   465,   498,   499,   504,   149,   150,    99,   100,
     209,   220,   311,   371,   313,   122,   102,   103,   104,   105,
     218,   106,   107,   108,   109,   110,   111,   112,   113,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short int yytable[] =
{
     131,   128,   120,   144,   134,   141,   133,   142,   141,   283,
     219,   141,    50,    51,   189,   401,   189,    29,     1,   173,
     262,   115,   152,   485,   165,   402,   336,   143,    29,    29,
     141,   148,   486,   101,   129,   156,   159,   154,   158,   246,
     247,   281,    69,   318,   153,   480,   151,   256,   257,   181,
     453,    29,   263,   126,     1,   116,   141,    29,   138,   264,
     282,  -287,  -287,   166,   135,    25,  -287,   283,   175,   -25,
     329,   -25,   176,   272,   253,   306,     3,     4,     5,     6,
       7,   161,   175,   101,     3,     4,     5,     6,     7,    29,
     507,   153,    69,   260,   406,   508,   224,   226,   244,   381,
     261,    25,   221,   277,   141,   141,    29,   136,    29,   489,
     453,   240,   490,   141,   245,    29,   141,   243,   359,   233,
     223,   225,   204,   254,   167,   360,   255,    29,   138,   234,
     205,   206,   237,   131,   178,    29,   138,   211,   212,   213,
     214,   278,   410,   411,   399,   241,   513,   242,   243,    29,
     138,   188,   400,   513,   271,   274,   141,   101,   418,   251,
      51,   169,   280,   421,   292,   180,    69,   207,   134,   191,
     284,   215,  -279,   145,   208,   515,   228,    51,   290,   146,
     101,  -279,   515,   229,   192,   451,   308,    30,    31,    69,
     452,   210,    34,    51,   141,   268,   489,   101,   310,   490,
     134,   222,   314,   369,   370,   217,    69,   323,   319,   320,
     307,   459,   175,   101,   423,   141,   227,   423,   187,   310,
     188,   470,    69,   238,   354,   165,   243,   377,   239,   188,
     141,   322,   134,  -295,   331,  -295,   188,   303,   304,   305,
     373,   253,   374,   339,   165,   148,   332,   353,   344,   290,
     347,   488,   348,   349,   182,   183,   290,   351,   123,   362,
     169,   -43,   494,   130,   166,   382,   392,   383,   188,   416,
     417,   330,   182,   183,    36,   259,    38,   267,    40,   265,
     363,   101,   266,   166,   101,   475,   477,   301,   302,   287,
      69,   291,   312,    69,   199,   200,   316,   123,   123,   327,
     325,   326,   134,   101,   376,   378,   379,   328,   333,   193,
     194,   337,    69,   195,   196,   197,   198,   356,   372,   384,
     358,   380,   318,   391,   393,   394,   398,   409,   419,   404,
     405,   420,   396,   397,   295,   296,   297,   298,   299,   300,
     422,   280,   431,   432,   434,   441,   407,   442,   439,   449,
     450,   408,   461,   467,   101,   479,   483,   487,   276,   476,
     468,   414,   415,    69,   500,   121,   452,   492,   506,   505,
     395,   157,   481,   519,   520,   123,   491,   474,   430,   389,
     174,   127,   403,   288,   160,   289,   366,   495,   367,   437,
     341,   438,   324,   368,   317,     0,   249,   101,   101,   201,
     202,   203,   444,   445,   121,   121,    69,    69,     0,     0,
       0,   131,   123,     0,   469,     0,     0,     0,   101,   458,
       0,     0,     0,     0,   460,     0,   407,    69,     0,     0,
     462,     0,     0,     0,     0,     0,   471,   472,     0,     0,
     430,   458,   478,   123,   123,   123,   123,   123,   123,   123,
     123,     0,     0,     0,   123,   123,   123,     0,     0,     0,
       0,     0,     0,   131,     0,     0,   101,     0,     0,     0,
       0,     0,     0,   493,     0,    69,   101,   497,     0,   462,
       0,     0,   121,     0,     0,    69,     0,     0,   123,     0,
     458,     0,     0,     0,   516,   517,   518,   458,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,     0,
       0,     0,     0,     0,     0,    69,     0,   101,     0,   121,
       0,     0,     0,     0,     0,     0,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,   123,   123,     0,     0,     0,     0,     0,
     121,   121,   121,   121,   121,   121,   121,   121,     0,     0,
       0,   121,   121,   121,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   123,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   123,     0,     0,
       0,     0,     0,     0,     0,   121,     0,     0,     0,     1,
     116,     0,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    22,    23,
     117,     0,     0,   121,     0,     0,    25,    26,     0,     0,
     121,   121,     0,    29,    30,    31,     0,    32,    33,    34,
       0,     0,    35,    36,    37,    38,    39,    40,    41,     0,
       0,     0,     0,   118,   448,     0,     0,    44,    45,     0,
      46,     0,   121,    48,    49,     0,   466,     0,     0,     0,
       0,     0,     0,     0,   121,     0,   163,     0,     0,     0,
       1,     2,     0,     3,     4,     5,     6,     7,     0,     8,
       0,     0,     9,    10,     0,     0,    11,    12,    13,     0,
      14,    15,    16,     0,     0,     0,   448,     0,     0,     0,
       0,    17,     0,     0,    18,   466,    19,    20,    21,    22,
      23,    24,     0,     0,     0,     0,     0,    25,    26,     0,
       0,    27,     0,    28,    29,    30,    31,     0,    32,    33,
      34,     0,     0,    35,    36,    37,    38,    39,    40,   164,
       0,    42,     0,     0,    43,     0,     0,     0,    44,    45,
       0,    46,     0,    47,    48,    49,     0,     0,     0,     0,
       0,     0,     0,   121,     0,     0,     1,     2,     0,     3,
       4,     5,     6,     7,     0,     8,     0,     0,     9,    10,
       0,     0,    11,    12,    13,     0,    14,    15,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
      18,     0,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,   121,    25,    26,     0,     0,    27,     0,    28,
      29,    30,    31,     0,    32,    33,    34,     0,     0,    35,
      36,    37,    38,    39,    40,    41,   250,    42,     0,     0,
      43,     0,     0,     0,    44,    45,     0,    46,     0,    47,
      48,    49,     1,     2,     0,     3,     4,     5,     6,     7,
       0,     8,     0,     0,     9,    10,     0,     0,    11,    12,
      13,     0,    14,    15,    16,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,    18,     0,    19,    20,
      21,    22,    23,    24,     0,     0,     0,     0,     0,    25,
      26,     0,     0,    27,     0,    28,    29,    30,    31,     0,
      32,    33,    34,     0,     0,    35,    36,    37,    38,    39,
      40,    41,   269,    42,     0,     0,    43,     0,     0,     0,
      44,    45,     0,    46,     0,    47,    48,    49,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     8,     0,     0,
       9,    10,     0,     0,    11,    12,    13,     0,    14,    15,
      16,     0,     0,     0,     0,     0,     0,     0,     0,    17,
       0,     0,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,     0,     0,     0,    25,    26,     0,     0,    27,
       0,    28,    29,    30,    31,     0,    32,    33,    34,     0,
       0,    35,    36,    37,    38,    39,    40,   164,   338,    42,
       0,     0,    43,     0,     0,     0,    44,    45,     0,    46,
       0,    47,    48,    49,     1,     2,     0,     3,     4,     5,
       6,     7,     0,     8,     0,     0,     9,    10,     0,     0,
      11,    12,    13,     0,    14,    15,    16,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,    18,     0,
      19,    20,    21,    22,    23,    24,     0,     0,     0,     0,
       0,    25,    26,     0,     0,    27,     0,    28,    29,    30,
      31,     0,    32,    33,    34,     0,     0,    35,    36,    37,
      38,    39,    40,   164,   352,    42,     0,     0,    43,     0,
       0,     0,    44,    45,     0,    46,     0,    47,    48,    49,
       1,     2,     0,     3,     4,     5,     6,     7,     0,     8,
       0,     0,     9,    10,     0,     0,    11,    12,    13,     0,
      14,    15,    16,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,     0,    18,     0,    19,    20,    21,    22,
      23,    24,     0,     0,     0,     0,     0,    25,    26,     0,
       0,    27,     0,    28,    29,    30,    31,     0,    32,    33,
      34,     0,     0,    35,    36,    37,    38,    39,    40,    41,
       0,    42,     0,     0,    43,     0,     0,     0,    44,    45,
       0,    46,     0,    47,    48,    49,     1,     2,     0,     3,
       4,     5,     6,     7,     0,     8,     0,     0,     9,    10,
       0,     0,    11,    12,    13,     0,    14,    15,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
      18,     0,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,     0,    25,    26,     0,     0,    27,     0,    28,
      29,    30,    31,     0,    32,    33,    34,     0,     0,    35,
      36,    37,    38,    39,    40,   164,     0,    42,     0,     0,
      43,     0,     0,     0,    44,    45,     0,    46,     0,    47,
      48,    49,     1,   116,     0,     3,     4,     5,     6,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,    23,    24,     0,     0,     0,     0,     0,    25,
      26,     0,     0,     0,     0,    28,    29,    30,    31,     0,
      32,    33,    34,     0,     0,    35,    36,    37,    38,    39,
      40,    41,     0,     0,   309,     0,    43,     0,     0,     0,
      44,    45,     0,    46,     0,    47,    48,    49,     1,   116,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,    24,
       0,     0,     0,     0,     0,    25,    26,     0,     0,     0,
       0,    28,    29,    30,    31,     0,    32,    33,    34,     0,
       0,    35,    36,    37,    38,    39,    40,    41,   340,     0,
       0,     0,    43,     0,     0,     0,    44,    45,     0,    46,
       0,    47,    48,    49,     1,   116,     0,     3,     4,     5,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    23,    24,     0,     0,     0,     0,
       0,    25,    26,     0,     0,     0,     0,    28,    29,    30,
      31,     0,    32,    33,    34,     0,     0,    35,    36,    37,
      38,    39,    40,    41,     0,     0,     0,     0,    43,     0,
       0,     0,    44,    45,   346,    46,     0,    47,    48,    49,
       1,   116,     0,     3,     4,     5,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
      23,    24,     0,     0,     0,     0,     0,    25,    26,     0,
       0,     0,     0,    28,    29,    30,    31,     0,    32,    33,
      34,     0,     0,    35,    36,    37,    38,    39,    40,    41,
       0,     0,     0,     0,    43,     0,     0,     0,    44,    45,
       0,    46,   350,    47,    48,    49,     1,   116,     0,     3,
       4,     5,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,    23,    24,     0,     0,
       0,     0,     0,    25,    26,     0,     0,     0,     0,    28,
      29,    30,    31,     0,    32,    33,    34,     0,     0,    35,
      36,    37,    38,    39,    40,    41,     0,     0,     0,     0,
      43,     0,     0,     0,    44,    45,   375,    46,     0,    47,
      48,    49,     1,   116,     0,     3,     4,     5,     6,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,    23,    24,     0,     0,     0,     0,     0,    25,
      26,     0,     0,     0,     0,    28,    29,    30,    31,     0,
      32,    33,    34,     0,     0,    35,    36,    37,    38,    39,
      40,    41,     0,     0,     0,     0,    43,   496,     0,     0,
      44,    45,     0,    46,     0,    47,    48,    49,     1,   116,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,    24,
       0,     0,     0,     0,     0,    25,    26,     0,     0,     0,
       0,    28,    29,    30,    31,     0,    32,    33,    34,     0,
       0,    35,    36,    37,    38,    39,    40,    41,     0,     0,
       0,     0,    43,     0,     0,     0,    44,    45,     0,    46,
       0,    47,    48,    49,     1,   116,     0,     3,     4,     5,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    23,    24,     0,     0,     0,     0,
       0,    25,    26,     0,     0,     0,     0,    28,    29,    30,
      31,     0,    32,    33,    34,     0,     0,    35,    36,    37,
      38,    39,    40,    41,     0,     0,     0,     0,    43,     0,
       0,     0,   424,    45,     0,    46,     0,    47,    48,    49,
       1,   116,     0,     3,     4,     5,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
      23,   117,     0,     0,     0,     0,     0,    25,    26,     0,
       0,     0,     0,     0,    29,    30,    31,     0,    32,    33,
      34,     0,     0,    35,    36,    37,    38,    39,    40,    41,
       0,     0,     0,     0,   118,     0,     0,     0,    44,    45,
       0,    46,     0,    47,    48,    49,     1,   116,     0,     3,
       4,     5,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,    23,   117,     0,     0,
       0,     0,     0,    25,    26,     0,     0,     0,     0,     0,
      29,    30,    31,     0,    32,    33,    34,     0,     0,    35,
      36,    37,    38,    39,    40,    41,     0,     0,     0,     0,
     118,     0,     0,     0,    44,    45,     0,    46
};

static const short int yycheck[] =
{
      13,    11,     8,    24,    14,    18,    14,    21,    21,   176,
     105,    24,     0,     0,    18,    76,    18,    58,     4,     5,
      45,    78,    43,    77,    50,    86,   248,    24,    58,    58,
      43,    41,    86,     0,     5,    45,    46,    45,    46,   143,
     144,    56,     0,    73,    85,    74,    43,   151,   152,    75,
      79,    58,    77,    11,     4,     5,    69,    58,    59,    84,
      75,    59,    60,    50,    75,    51,    64,   234,    83,    73,
     237,    73,    69,   168,    76,     6,     7,     8,     9,    10,
      11,    48,    83,    50,     7,     8,     9,    10,    11,    58,
      75,    85,    50,    77,    46,    80,   117,   118,    59,   321,
      84,    51,   115,    46,   117,   118,    58,    75,    58,    59,
      79,   137,    62,   126,    75,    58,   129,    78,    77,   125,
     117,   118,    82,    74,    65,    84,    77,    58,    59,   126,
      90,    91,   129,   146,    76,    58,    59,    47,    48,    49,
      50,    84,   364,   365,    76,    75,   503,    77,    78,    58,
      59,    77,    84,   510,   164,   169,   169,   124,    84,   147,
     147,    36,   175,   385,   190,    73,   124,    78,   178,    30,
     178,    81,    83,    16,    85,   503,    78,   164,   188,    22,
     147,    83,   510,    85,    29,    76,   207,    59,    60,   147,
      81,    76,    64,   180,   207,   162,    59,   164,   208,    62,
     210,    78,   210,   307,   308,    92,   164,   228,   221,   222,
     207,   433,    83,   180,   386,   228,    76,   389,    75,   229,
      77,   443,   180,    23,    76,   251,    78,    75,    75,    77,
     243,   228,   242,    84,   242,    86,    77,   204,   205,   206,
      84,    76,    86,   253,   270,   255,   243,   273,   258,   259,
     260,   473,   262,   263,    14,    15,   266,   267,     8,   285,
      36,    37,   484,    13,   251,    84,    75,    86,    77,   373,
     374,   238,    14,    15,    68,    77,    70,    45,    72,    86,
     286,   248,    77,   270,   251,   450,   451,   199,   200,    76,
     248,    16,    83,   251,    88,    89,    73,    47,    48,    73,
      17,    76,   312,   270,   312,   315,   316,    73,    75,    27,
      28,    23,   270,    31,    32,    33,    34,    37,    76,   325,
      84,    73,    73,    76,   334,   335,    80,    76,    61,   355,
     356,    75,   342,   343,   193,   194,   195,   196,   197,   198,
      74,   354,    74,    73,    58,    84,   359,    75,    77,    53,
      77,   361,    76,    84,   321,    76,    58,    54,   171,    82,
      86,   371,   372,   321,    75,     8,    81,    76,    76,    79,
     337,    46,   454,   508,   510,   125,   479,   450,   388,   328,
      67,    11,   354,   184,    47,   184,   293,   485,   294,   399,
     255,   401,   229,   306,   220,    -1,   146,   364,   365,    92,
      92,    92,   412,   413,    47,    48,   364,   365,    -1,    -1,
      -1,   424,   162,    -1,   440,    -1,    -1,    -1,   385,   432,
      -1,    -1,    -1,    -1,   434,    -1,   439,   385,    -1,    -1,
     436,    -1,    -1,    -1,    -1,    -1,   446,   447,    -1,    -1,
     450,   454,   452,   193,   194,   195,   196,   197,   198,   199,
     200,    -1,    -1,    -1,   204,   205,   206,    -1,    -1,    -1,
      -1,    -1,    -1,   476,    -1,    -1,   433,    -1,    -1,    -1,
      -1,    -1,    -1,   483,    -1,   433,   443,   487,    -1,   485,
      -1,    -1,   125,    -1,    -1,   443,    -1,    -1,   238,    -1,
     503,    -1,    -1,    -1,   504,   505,   506,   510,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   473,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   473,    -1,   484,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,   484,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   286,    -1,    -1,    -1,
      -1,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,
     193,   194,   195,   196,   197,   198,   199,   200,    -1,    -1,
      -1,   204,   205,   206,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   325,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   238,    -1,    -1,    -1,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,   286,    -1,    -1,    51,    52,    -1,    -1,
     293,   294,    -1,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    78,   424,    -1,    -1,    82,    83,    -1,
      85,    -1,   325,    88,    89,    -1,   436,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   337,    -1,     0,    -1,    -1,    -1,
       4,     5,    -1,     7,     8,     9,    10,    11,    -1,    13,
      -1,    -1,    16,    17,    -1,    -1,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,   476,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    38,   485,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    55,    -1,    57,    58,    59,    60,    -1,    62,    63,
      64,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,
      -1,    85,    -1,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   436,    -1,    -1,     4,     5,    -1,     7,
       8,     9,    10,    11,    -1,    13,    -1,    -1,    16,    17,
      -1,    -1,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      38,    -1,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,   485,    51,    52,    -1,    -1,    55,    -1,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,
      88,    89,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    55,    -1,    57,    58,    59,    60,    -1,
      62,    63,    64,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    78,    -1,    -1,    -1,
      82,    83,    -1,    85,    -1,    87,    88,    89,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    13,    -1,    -1,
      16,    17,    -1,    -1,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    -1,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,
      -1,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      -1,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,
      -1,    87,    88,    89,     4,     5,    -1,     7,     8,     9,
      10,    11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    55,    -1,    57,    58,    59,
      60,    -1,    62,    63,    64,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    78,    -1,
      -1,    -1,    82,    83,    -1,    85,    -1,    87,    88,    89,
       4,     5,    -1,     7,     8,     9,    10,    11,    -1,    13,
      -1,    -1,    16,    17,    -1,    -1,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    38,    -1,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    55,    -1,    57,    58,    59,    60,    -1,    62,    63,
      64,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,
      -1,    85,    -1,    87,    88,    89,     4,     5,    -1,     7,
       8,     9,    10,    11,    -1,    13,    -1,    -1,    16,    17,
      -1,    -1,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      38,    -1,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    55,    -1,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    -1,    75,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,
      88,    89,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    -1,
      62,    63,    64,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    76,    -1,    78,    -1,    -1,    -1,
      82,    83,    -1,    85,    -1,    87,    88,    89,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      -1,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,
      -1,    87,    88,    89,     4,     5,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    -1,    62,    63,    64,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    82,    83,    84,    85,    -1,    87,    88,    89,
       4,     5,    -1,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    -1,    62,    63,
      64,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,
      -1,    85,    86,    87,    88,    89,     4,     5,    -1,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    84,    85,    -1,    87,
      88,    89,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    -1,
      62,    63,    64,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    78,    79,    -1,    -1,
      82,    83,    -1,    85,    -1,    87,    88,    89,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      -1,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,
      -1,    87,    88,    89,     4,     5,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    -1,    62,    63,    64,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    82,    83,    -1,    85,    -1,    87,    88,    89,
       4,     5,    -1,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    -1,    62,    63,
      64,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,
      -1,    85,    -1,    87,    88,    89,     4,     5,    -1,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    59,    60,    -1,    62,    63,    64,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    85
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     4,     5,     7,     8,     9,    10,    11,    13,    16,
      17,    20,    21,    22,    24,    25,    26,    35,    38,    40,
      41,    42,    43,    44,    45,    51,    52,    55,    57,    58,
      59,    60,    62,    63,    64,    67,    68,    69,    70,    71,
      72,    73,    75,    78,    82,    83,    85,    87,    88,    89,
      94,    98,    99,   101,   105,   106,   107,   109,   110,   120,
     121,   123,   124,   126,   127,   129,   153,   154,   155,   156,
     158,   162,   164,   165,   166,   167,   171,   178,   180,   182,
     184,   187,   189,   190,   192,   193,   204,   205,   207,   209,
     210,   211,   212,   213,   214,   216,   217,   218,   219,   231,
     232,   238,   239,   240,   241,   242,   244,   245,   246,   247,
     248,   249,   250,   251,   252,    78,     5,    45,    78,   156,
     204,   232,   238,   240,   181,   185,   156,   166,   192,     5,
     240,   246,   125,   190,   192,    75,    75,   111,    59,   122,
     157,   246,   122,   157,   239,    16,    22,   163,   192,   229,
     230,   157,   239,    85,   190,   191,   192,   125,   190,   192,
     210,   238,   215,     0,    73,    96,    98,    65,   108,    36,
     112,   115,   116,     5,   155,    83,   157,   169,    76,   168,
      73,    96,    14,    15,   172,   173,   176,    75,    77,    18,
     100,    30,    29,    27,    28,    31,    32,    33,    34,    88,
      89,   247,   249,   252,    82,    90,    91,    78,    85,   233,
      76,    47,    48,    49,    50,    81,   203,    92,   243,   243,
     234,   246,    78,   157,   239,   157,   239,    76,    78,    85,
      95,    96,    98,   204,   157,   161,   128,   157,    23,    75,
      96,    75,    77,    78,    59,    75,   203,   203,   102,   240,
      74,    94,    97,    76,    74,    77,   203,   203,   220,    77,
      77,    84,    45,    77,    84,    86,    77,    45,   238,    74,
      94,   192,   243,   119,   122,   113,   116,    46,    84,   170,
     246,    56,    75,   169,   190,   160,   174,    76,   173,   176,
     192,    16,    96,   206,   208,   211,   211,   211,   211,   211,
     211,   213,   213,   238,   238,   238,     6,   157,   239,    76,
     192,   235,    83,   237,   190,   194,    73,   245,    73,   246,
     246,   179,   157,   239,   235,    17,    76,    73,    73,   169,
     238,   190,   157,    75,   199,   200,    95,    23,    74,   192,
      74,   230,   201,   202,   192,   222,    84,   192,   192,   192,
      86,   192,    74,    96,    76,   117,    37,   114,    84,    77,
      84,   159,    96,   204,   177,   183,   207,   209,   237,   203,
     203,   236,    76,    84,    86,    84,   190,    75,   192,   192,
      73,    95,    84,    86,   204,   186,   144,   145,   146,   144,
     130,    76,    75,   192,   192,   238,   192,   192,    80,    76,
      84,    76,    86,   170,    96,    96,    46,   246,   192,    76,
      95,    95,   195,   196,   192,   192,   203,   203,    84,    61,
      75,    95,    74,   145,    82,   148,   149,   150,   151,   152,
     192,    74,    73,   188,    58,   104,   221,   192,   192,    77,
     118,    84,    75,   175,   192,   192,   198,   197,   240,    53,
      77,    76,    81,    79,   131,   132,   135,   142,   246,    95,
     192,    76,   204,   223,   224,   225,   240,    84,    86,    96,
      95,   192,   192,   147,   151,   152,    82,   152,   192,    76,
      74,   132,   133,    58,   103,    77,    86,    54,    95,    59,
      62,   141,    76,   192,    95,   224,    79,   192,   226,   227,
      75,   134,   136,   137,   228,    79,    76,    75,    80,   138,
     139,   140,   141,   142,   143,   164,   192,   192,   192,   136,
     140
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    93,    94,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,   100,    99,   102,   101,   103,
     101,   104,   104,   104,   105,   107,   106,   108,   108,   109,
     109,   111,   110,   113,   112,   112,   114,   115,   115,   117,
     116,   118,   116,   119,   116,   120,   120,   121,   121,   122,
     122,   123,   123,   124,   124,   124,   125,   125,   126,   126,
     128,   127,   130,   129,   131,   131,   133,   132,   132,   134,
     134,   135,   137,   136,   138,   139,   139,   140,   140,   140,
     141,   141,   142,   143,   144,   144,   146,   147,   145,   148,
     148,   149,   150,   150,   151,   151,   151,   152,   153,   153,
     153,   153,   154,   154,   155,   155,   156,   156,   157,   157,
     158,   159,   158,   160,   158,   161,   158,   158,   163,   162,
     164,   164,   165,   166,   167,   168,   168,   169,   169,   169,
     169,   169,   170,   170,   171,   171,   171,   171,   172,   172,
     174,   175,   173,   177,   176,   179,   178,   181,   180,   183,
     182,   185,   186,   184,   188,   187,   189,   190,   190,   191,
     191,   191,   192,   192,   194,   193,   195,   193,   196,   193,
     197,   193,   198,   193,   199,   193,   200,   193,   201,   193,
     202,   193,   193,   203,   203,   203,   203,   203,   204,   206,
     205,   205,   208,   207,   207,   209,   209,   210,   210,   210,
     210,   210,   210,   210,   211,   212,   212,   212,   212,   212,
     212,   213,   213,   213,   213,   215,   214,   214,   214,   216,
     216,   216,   216,   216,   217,   217,   217,   217,   218,   218,
     220,   221,   219,   222,   223,   223,   224,   224,   225,   225,
     226,   226,   227,   227,   228,   227,   229,   229,   230,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   232,   232,   233,
     232,   232,   232,   232,   232,   232,   232,   234,   232,   232,
     232,   235,   236,   235,   235,   235,   235,   237,   237,   238,
     239,   239,   239,   239,   239,   240,   241,   241,   242,   242,
     243,   244,   244,   245,   245,   245,   246,   247,   248,   249,
     250,   251,   252
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     3,     0,     4,     0,
       9,     0,     2,     4,     4,     0,     2,     2,     1,     2,
       1,     0,     3,     0,     3,     1,     2,     2,     1,     0,
       4,     0,     6,     0,     3,     3,     5,     3,     4,     3,
       1,     1,     1,     3,     2,     2,     0,     1,     1,     1,
       0,     6,     0,     8,     2,     1,     0,     5,     4,     3,
       1,     1,     0,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     0,     0,     5,     1,
       1,     3,     3,     1,     1,     1,     3,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     2,     1,     1,     1,
       3,     0,     6,     0,     4,     0,     6,     5,     0,     3,
       2,     1,     4,     3,     2,     0,     2,     0,     2,     3,
       3,     5,     3,     1,     1,     2,     3,     2,     2,     1,
       0,     0,     6,     0,     4,     0,     5,     0,     6,     0,
       5,     0,     0,     6,     0,     7,     2,     3,     1,     3,
       3,     2,     1,     1,     0,     4,     0,     6,     0,     6,
       0,     7,     0,     7,     0,     5,     0,     5,     0,     5,
       0,     5,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     0,     4,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     1,     1,     3,     3,     2,     2,     2,
       1,     3,     3,     3,     1,     0,     3,     2,     1,     3,
       4,     5,     7,     1,     3,     4,     5,     7,     3,     4,
       0,     0,     8,     1,     3,     1,     1,     1,     3,     3,
       3,     1,     3,     2,     0,     3,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     0,
       3,     4,     4,     2,     2,     2,     2,     0,     3,     4,
       1,     3,     0,     3,     2,     1,     1,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     3,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     9,    11,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,   144,     0,   144,     0,   228,     0,   168,     0,   147,
       0,   147,     0
};

/* Error token number */
#define YYTERROR 1



YYSTYPE yylval;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yyGLRStack;
static void yypstack (struct yyGLRStack* yystackp, size_t yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (struct yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif


#if YYERROR_VERBOSE

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;


  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

static _Noreturn void
yyFail (yyGLRStack* yystackp, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static _Noreturn void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, size_t yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = (yystackp->yysplitPoint == YY_NULLPTR);
  int yylow;
  YYUSE (yyvalp);
  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  switch (yyn)
    {
        case 11:
#line 210 "../src/parser/parser.y" /* glr.c:783  */
    {
			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) > 1) {
				for(int i=0; i<(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer); i++)
					g_op->pop_stack();
			}
			else {
				g_op->fast_pop_stack();
			}
		}
#line 1891 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 18:
#line 226 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->fast_pop_stack();
		}
#line 1899 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 19:
#line 230 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->fast_pop_stack();
		}
#line 1907 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 25:
#line 243 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->do_scope_start();
		}
#line 1915 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 26:
#line 247 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->do_scope_end();
		}
#line 1923 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 27:
#line 255 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->parallel_start();
		}
#line 1931 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 28:
#line 259 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->parallel_end();
		}
#line 1939 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 29:
#line 263 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->parallel_for_start((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.cp));
		}
#line 1947 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 30:
#line 267 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->parallel_for_end();
		}
#line 1955 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 31:
#line 274 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_integer(0);	// by
			g_op->push_integer(1);	// per
		}
#line 1964 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 32:
#line 279 "../src/parser/parser.y" /* glr.c:783  */
    {
			int opt = 0;
			if (strncmp((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), "by", 2) == 0) {
				g_op->push_integer(1);
			}
			else if (strncmp((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), "per", 3) == 0) {
				g_op->push_integer(0);
				g_op->rotate();
			}
			else {
				yyerror("parallel option 'by' or 'per' expected");
			}
		}
#line 1982 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 33:
#line 293 "../src/parser/parser.y" /* glr.c:783  */
    {
			if (strncmp((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.cp), "by", 2) != 0) {
				yyerror("parallel option 'by' expected");
			}

			if (strncmp((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), "per", 3) != 0) {
				yyerror("parallel option 'per' expected");
			}
		}
#line 1996 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 34:
#line 307 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->call((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));
		}
#line 2004 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 35:
#line 314 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved(OP_PUSH_ROOT);
			g_op->find_member("os");
			g_op->find_member("run");
		}
#line 2014 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 36:
#line 320 "../src/parser/parser.y" /* glr.c:783  */
    {	
			g_op->call(1);
		}
#line 2022 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 38:
#line 329 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_string((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 2030 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 39:
#line 337 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->pop();
		}
#line 2038 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 41:
#line 346 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->push();
		}
#line 2046 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 42:
#line 350 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->goto_end();
		}
#line 2054 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 43:
#line 358 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->do_finally();
		}
#line 2062 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 44:
#line 362 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->goto_end();
		}
#line 2070 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 49:
#line 382 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->catch_start((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 2078 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 50:
#line 386 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->goto_finally();
		}
#line 2086 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 51:
#line 390 "../src/parser/parser.y" /* glr.c:783  */
    {
			name_list_t* vp = (name_list_t*)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.vector_cp);
			g_ex->catch_start((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.cp), vp);
		}
#line 2095 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 52:
#line 395 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->goto_finally();
		}
#line 2103 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 53:
#line 399 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->catch_start(NULL);
		}
#line 2111 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 54:
#line 403 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->goto_finally();
		}
#line 2119 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 55:
#line 411 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->do_throw((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), 0);
		}
#line 2127 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 56:
#line 415 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ex->do_throw((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.cp), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));
		}
#line 2135 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 57:
#line 423 "../src/parser/parser.y" /* glr.c:783  */
    {
			code_top->using_object((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), NULL);
		}
#line 2143 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 58:
#line 427 "../src/parser/parser.y" /* glr.c:783  */
    {
			code_top->using_object((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.cp), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp));
		}
#line 2151 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 59:
#line 435 "../src/parser/parser.y" /* glr.c:783  */
    {
			char buff[1024];
			sprintf(buff, "%s.%s", (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.cp), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
			((*yyvalp).cp) = parser_strdup(buff);
		}
#line 2161 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 60:
#line 441 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).cp) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
		}
#line 2169 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 61:
#line 449 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->dump_stack();
		}
#line 2177 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 62:
#line 453 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->dump_local();
		}
#line 2185 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 63:
#line 461 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->do_return((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));
		}
#line 2193 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 64:
#line 465 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->do_continue();
		}
#line 2201 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 65:
#line 469 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->do_break();
		}
#line 2209 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 66:
#line 477 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 0;
		}
#line 2217 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 67:
#line 481 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer);
		}
#line 2225 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 70:
#line 495 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_start();
		}
#line 2233 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 71:
#line 499 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_end();
		}
#line 2241 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 72:
#line 507 "../src/parser/parser.y" /* glr.c:783  */
    {
			name_list_t* vp = (name_list_t*)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.vector_cp);

			// check argv
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				yyerror("argv not allowed in parse object");
			}

			if (vp == NULL) {
				yyerror("at least 1 argument needed in parse object");
			}

			parserCode::push_code_stack((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), vp);
			g_parse->do_parse_init();
		}
#line 2261 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 73:
#line 523 "../src/parser/parser.y" /* glr.c:783  */
    {
			vector<char>& def = parserCode::get_def();

			g_parse->make_table();
			//g_parse->dump();
			g_parse->do_parse(def);
			g_parse->cleanup();

			parserCode::pop_code_stack();
		}
#line 2276 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 76:
#line 544 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_parse->set_current_bnf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.bp));
		}
#line 2284 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 77:
#line 548 "../src/parser/parser.y" /* glr.c:783  */
    {

		}
#line 2292 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 78:
#line 552 "../src/parser/parser.y" /* glr.c:783  */
    {
			bnf* b = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.bp);
			b->type = BNF_WS;
		}
#line 2301 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 82:
#line 572 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_bnf_right_num = 1;
			g_parse->current_bnf()->add_rule();
		}
#line 2310 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 85:
#line 587 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_bnf_right_num++;
			g_parse->current_bnf()->current_rule()->push_bnf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.bp));
		}
#line 2319 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 86:
#line 592 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_parse->current_bnf()->current_rule()->push_bnf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.bp));
		}
#line 2327 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 90:
#line 607 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).bp) = g_parse->get_term_bnf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 2335 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 91:
#line 611 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).bp) = g_parse->get_term_bnf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp), true);
		}
#line 2343 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 92:
#line 619 "../src/parser/parser.y" /* glr.c:783  */
    {
			string name = "`\a";
			name += (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
			((*yyvalp).bp) = g_parse->get_nonterm_bnf(name);
		}
#line 2353 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 93:
#line 629 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).bp) = g_parse->get_action_bnf(g_bnf_right_num);
		}
#line 2361 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 96:
#line 642 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_pattern_start();
		}
#line 2369 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 97:
#line 646 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_pattern_shift();
		}
#line 2377 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 98:
#line 650 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_pattern_end();
		}
#line 2385 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 101:
#line 664 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_cut_list((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.cp), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 2393 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 102:
#line 672 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer) + 1;
		}
#line 2401 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 103:
#line 676 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 1;
		}
#line 2409 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 104:
#line 684 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_match_expr();
		}
#line 2417 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 105:
#line 688 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_shift((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 2425 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 106:
#line 692 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_match_and_assign((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.cp));
		}
#line 2433 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 107:
#line 700 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).cp) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
		}
#line 2441 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 112:
#line 716 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer) | (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer);
		}
#line 2449 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 113:
#line 720 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer);
		}
#line 2457 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 114:
#line 728 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = BIT_DEFINE_STATIC;
		}
#line 2465 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 115:
#line 732 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = BIT_DEFINE_PURE;
		}
#line 2473 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 116:
#line 740 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer);
		}
#line 2481 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 117:
#line 744 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 0;
		}
#line 2489 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 118:
#line 752 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).cp) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
		}
#line 2497 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 119:
#line 756 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).cp) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
		}
#line 2505 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 120:
#line 764 "../src/parser/parser.y" /* glr.c:783  */
    {
			code_top->reg_object((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer));
		}
#line 2513 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 121:
#line 768 "../src/parser/parser.y" /* glr.c:783  */
    {
			code_top->reg_object((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer));
			code_top->init_object_start((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp));

			g_op->push_reserved(OP_PUSH_MY);
		}
#line 2524 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 122:
#line 775 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->assign_member((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.cp));
			g_op->pop_stack();
			code_top->init_object_done();
		}
#line 2534 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 123:
#line 781 "../src/parser/parser.y" /* glr.c:783  */
    {
			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer)) {
				code_top->make_super((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));
			}
		}
#line 2544 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 124:
#line 787 "../src/parser/parser.y" /* glr.c:783  */
    {
			parserCode::pop_code_stack();
		}
#line 2552 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 125:
#line 791 "../src/parser/parser.y" /* glr.c:783  */
    {
			
			g_ctl->decode_func_start();
		}
#line 2561 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 126:
#line 796 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();
		}
#line 2570 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 127:
#line 801 "../src/parser/parser.y" /* glr.c:783  */
    {
			const char* cp = get_context();
			print("get_context(): '%s'\n", cp);
			code_top->do_context((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.cp), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), cp);
			//TODO: fail check
		}
#line 2581 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 128:
#line 812 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->once_start();
		}
#line 2589 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 129:
#line 816 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->once_end();
		}
#line 2597 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 130:
#line 824 "../src/parser/parser.y" /* glr.c:783  */
    {
			parserCode::pop_code_stack();
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp));
		}
#line 2607 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 132:
#line 835 "../src/parser/parser.y" /* glr.c:783  */
    {
			// for serial tagging
			static int count = 1;
			char name[256];
			sprintf(name, "__%s_%d_context", g_parse_module_name.c_str(), count++);

			const char* cp = get_context();
			//print("get_context(): '%s'\n", cp);
			code_top->do_context((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), name, cp);
			//TODO: fail check

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member(name);
		}
#line 2626 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 133:
#line 854 "../src/parser/parser.y" /* glr.c:783  */
    {
			name_list_t* vp = (name_list_t*)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.vector_cp);

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			parserCode::push_code_stack((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp), vp, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer));

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}
		}
#line 2652 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 134:
#line 879 "../src/parser/parser.y" /* glr.c:783  */
    {
			name_list_t* vp = (name_list_t*)(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.vector_cp);

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			static int count = 1;
			char buff[256];
			sprintf(buff, "#%d_lambda", count++);
			const char* name = parser_strdup(buff);
			parserCode::push_code_stack(name, vp, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}

			((*yyvalp).cp) = name;
		}
#line 2684 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 135:
#line 911 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 0;
		}
#line 2692 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 136:
#line 915 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer);
		}
#line 2700 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 137:
#line 923 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).vector_cp) = 0;
		}
#line 2708 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 138:
#line 927 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).vector_cp) = 0;
		}
#line 2716 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 139:
#line 931 "../src/parser/parser.y" /* glr.c:783  */
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back("...");
			((*yyvalp).vector_cp) = vs;
		}
#line 2726 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 140:
#line 937 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).vector_cp) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.vector_cp);
		}
#line 2734 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 141:
#line 941 "../src/parser/parser.y" /* glr.c:783  */
    {
			name_list_t* vs = (name_list_t*)(((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.vector_cp);
			vs->push_back("...");
			((*yyvalp).vector_cp) = vs;
		}
#line 2744 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 142:
#line 951 "../src/parser/parser.y" /* glr.c:783  */
    {
			name_list_t* vs = (name_list_t*)(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.vector_cp);
			vs->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
			((*yyvalp).vector_cp) = vs;
		}
#line 2754 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 143:
#line 957 "../src/parser/parser.y" /* glr.c:783  */
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
			((*yyvalp).vector_cp) = vs;
		}
#line 2764 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 144:
#line 967 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->if_end();
		}
#line 2772 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 145:
#line 971 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->else_end();
		}
#line 2780 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 146:
#line 975 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->else_end();
			for(int i=0; i<(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer); i++)
				g_ctl->else_end();
		}
#line 2790 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 147:
#line 981 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->if_end();
			for(int i=0; i<(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer); i++)
				g_ctl->else_end();
		}
#line 2800 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 148:
#line 991 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer) + 1;
		}
#line 2808 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 149:
#line 995 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 1;
		}
#line 2816 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 150:
#line 1003 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->else_start();
		}
#line 2824 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 151:
#line 1007 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->if_start();
		}
#line 2832 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 153:
#line 1016 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->else_start();
		}
#line 2840 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 155:
#line 1025 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->if_start();
		}
#line 2848 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 157:
#line 1034 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->do_start();
		}
#line 2856 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 158:
#line 1038 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->do_end();
		}
#line 2864 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 159:
#line 1046 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->times_start();
		}
#line 2872 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 160:
#line 1050 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->times_end();
		}
#line 2880 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 161:
#line 1058 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->while_start_1();
		}
#line 2888 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 162:
#line 1062 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->while_start_2();
		}
#line 2896 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 163:
#line 1066 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->while_end();
		}
#line 2904 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 164:
#line 1074 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->for_start((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.cp));
		}
#line 2912 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 165:
#line 1078 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->for_end();
		}
#line 2920 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 166:
#line 1086 "../src/parser/parser.y" /* glr.c:783  */
    { 
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer); 
		}
#line 2928 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 167:
#line 1094 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer) + 1;
		}
#line 2936 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 168:
#line 1098 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 1;
		}
#line 2944 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 169:
#line 1106 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer) + 1;
		}
#line 2952 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 170:
#line 1110 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 2;
		}
#line 2960 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 171:
#line 1114 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 1;
		}
#line 2968 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 174:
#line 1128 "../src/parser/parser.y" /* glr.c:783  */
    {
			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->push_lvar((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp));
			}
		}
#line 2978 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 175:
#line 1134 "../src/parser/parser.y" /* glr.c:783  */
    {
			switch ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_local((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.cp));
		}
#line 2994 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 176:
#line 1146 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->clear_last_find_position();
			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->dup();
				g_op->find_member((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp));
			}
		}
#line 3006 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 177:
#line 1154 "../src/parser/parser.y" /* glr.c:783  */
    {
			switch ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.cp));
		}
#line 3022 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 178:
#line 1166 "../src/parser/parser.y" /* glr.c:783  */
    {
			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->dup();
				g_op->find_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));
			}
		}
#line 3033 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 179:
#line 1173 "../src/parser/parser.y" /* glr.c:783  */
    {
			switch ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.integer));
		}
#line 3049 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 180:
#line 1185 "../src/parser/parser.y" /* glr.c:783  */
    {
			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(false);
			}
		}
#line 3061 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 181:
#line 1193 "../src/parser/parser.y" /* glr.c:783  */
    {
			switch ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->do_rc_dec();
			}

			g_op->assign_list(false);
		}
#line 3081 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 182:
#line 1209 "../src/parser/parser.y" /* glr.c:783  */
    {
			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(true);
			}
		}
#line 3093 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 183:
#line 1217 "../src/parser/parser.y" /* glr.c:783  */
    {
			switch ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->do_rc_dec();
			}

			g_op->assign_list(true);
		}
#line 3113 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 184:
#line 1233 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->dup(); 
				g_op->find_member((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp));
			}
		}
#line 3126 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 185:
#line 1242 "../src/parser/parser.y" /* glr.c:783  */
    {
			switch ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.cp));
		}
#line 3142 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 186:
#line 1254 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));
			}
		}
#line 3155 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 187:
#line 1263 "../src/parser/parser.y" /* glr.c:783  */
    {
			switch ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.integer));
		}
#line 3171 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 188:
#line 1275 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->dup(); 
				g_op->find_member((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cp));
			}
		}
#line 3184 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 189:
#line 1284 "../src/parser/parser.y" /* glr.c:783  */
    {
			switch ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.cp));
		}
#line 3200 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 190:
#line 1296 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));
			}
		}
#line 3213 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 191:
#line 1305 "../src/parser/parser.y" /* glr.c:783  */
    {
			switch ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.integer));
		}
#line 3229 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 193:
#line 1322 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = '='; 
		}
#line 3237 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 194:
#line 1326 "../src/parser/parser.y" /* glr.c:783  */
    { 
			((*yyvalp).integer) = '+'; 
		}
#line 3245 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 195:
#line 1330 "../src/parser/parser.y" /* glr.c:783  */
    { 
			((*yyvalp).integer) = '-'; 
		}
#line 3253 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 196:
#line 1334 "../src/parser/parser.y" /* glr.c:783  */
    { 
			((*yyvalp).integer) = '*'; 
		}
#line 3261 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 197:
#line 1338 "../src/parser/parser.y" /* glr.c:783  */
    { 
			((*yyvalp).integer) = '/'; 
		}
#line 3269 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 199:
#line 1351 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->dup();
			g_ctl->if_start(false);
		}
#line 3278 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 200:
#line 1356 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->do_or();
			g_ctl->if_end();
		}
#line 3287 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 202:
#line 1366 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->dup();
			g_ctl->if_start();
		}
#line 3296 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 203:
#line 1371 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->do_and();
			g_ctl->if_end();
		}
#line 3305 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 205:
#line 1381 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->do_not();
		}
#line 3313 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 207:
#line 1390 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->gt();
		}
#line 3321 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 208:
#line 1394 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->ge();
		}
#line 3329 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 209:
#line 1398 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->lt();
		}
#line 3337 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 210:
#line 1402 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->le();
		}
#line 3345 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 211:
#line 1406 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->eq();
		}
#line 3353 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 212:
#line 1410 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->neq();
		}
#line 3361 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 215:
#line 1424 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->add();
		}
#line 3369 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 216:
#line 1428 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->sub();
		}
#line 3377 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 217:
#line 1432 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_integer((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));
			g_op->add();
		}
#line 3386 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 218:
#line 1437 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_bignum('-', (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
			g_op->add();
		}
#line 3395 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 219:
#line 1442 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_real((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.real));
			g_op->add();
		}
#line 3404 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 221:
#line 1452 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->mul();
		}
#line 3412 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 222:
#line 1456 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->div();
		}
#line 3420 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 223:
#line 1460 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->mod();
		}
#line 3428 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 225:
#line 1469 "../src/parser/parser.y" /* glr.c:783  */
    {
			unary_minus = true;
		}
#line 3436 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 226:
#line 1473 "../src/parser/parser.y" /* glr.c:783  */
    {
			if (unary_minus)
				g_op->minus();

			unary_minus = false;
		}
#line 3447 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 229:
#line 1486 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_list((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));
		}
#line 3455 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 230:
#line 1490 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_list((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer));
		}
#line 3463 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 231:
#line 1494 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_list(-2);
		}
#line 3471 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 232:
#line 1498 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_list(-3);
		}
#line 3479 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 234:
#line 1507 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_tuple((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));
		}
#line 3487 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 235:
#line 1511 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_tuple((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer));
		}
#line 3495 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 236:
#line 1515 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_tuple(-2);
		}
#line 3503 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 237:
#line 1519 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_tuple(-3);
		}
#line 3511 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 238:
#line 1527 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_map((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer));
		}
#line 3519 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 239:
#line 1531 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_map((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer));
		}
#line 3527 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 240:
#line 1539 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		}
#line 3536 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 241:
#line 1544 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->sbf_rule_start();
		}
#line 3544 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 242:
#line 1548 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->sbf_end();
			g_lvar_nil_check++;
		}
#line 3553 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 246:
#line 1568 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->sbf_rule();
		}
#line 3561 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 247:
#line 1572 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->sbf_in();
		}
#line 3569 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 248:
#line 1580 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->sbf_list_gen((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.cp));
		}
#line 3577 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 249:
#line 1584 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_ctl->sbf_range_gen((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.cp));
		}
#line 3585 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 251:
#line 1593 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_integer(1);
		}
#line 3593 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 253:
#line 1602 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_nil();
		}
#line 3601 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 254:
#line 1606 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_nil();
		}
#line 3609 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 256:
#line 1615 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.integer) + 1;
		}
#line 3617 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 257:
#line 1619 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 1;
		}
#line 3625 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 263:
#line 1636 "../src/parser/parser.y" /* glr.c:783  */
    {
			if (g_op->check_lvar((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp)) == false) {
				string msg = "variable ";
				msg += (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
				msg += " is not defined";
				yyerror(msg.c_str());
			}

			g_op->push_lvar((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 3640 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 264:
#line 1647 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_integer((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));
		}
#line 3648 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 265:
#line 1651 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_integer((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));
		}
#line 3656 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 266:
#line 1655 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_bignum('+', (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 3664 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 267:
#line 1659 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_bignum('-', (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 3672 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 268:
#line 1663 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_real((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.real));
		}
#line 3680 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 269:
#line 1667 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_real((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.real));
		}
#line 3688 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 270:
#line 1671 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_regex();
		}
#line 3696 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 271:
#line 1675 "../src/parser/parser.y" /* glr.c:783  */
    {
			// already in stack
		}
#line 3704 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 272:
#line 1679 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));
		}
#line 3712 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 273:
#line 1683 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_boolean(true);
		}
#line 3720 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 274:
#line 1687 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_boolean(false);
		}
#line 3728 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 275:
#line 1691 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_nil();
		}
#line 3736 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 277:
#line 1700 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->set_last_find_position();
			g_op->find_member((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 3745 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 278:
#line 1705 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->find_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));
		}
#line 3753 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 279:
#line 1709 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->clear_last_find_position();
		}
#line 3761 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 280:
#line 1713 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->call((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));
		}
#line 3769 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 281:
#line 1717 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->listat(false);
		}
#line 3777 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 282:
#line 1721 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->listat(true);
		}
#line 3785 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 283:
#line 1725 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_member((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 3794 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 284:
#line 1730 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));
		}
#line 3803 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 285:
#line 1735 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 3812 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 286:
#line 1740 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_reserved((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));
		}
#line 3821 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 287:
#line 1745 "../src/parser/parser.y" /* glr.c:783  */
    {
			if (g_op->push_mvar_using_space((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp)) == false) {
				yyerror("invalid object name in name'string' format");
			}
		}
#line 3831 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 288:
#line 1751 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->clone(1);
		}
#line 3839 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 289:
#line 1755 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->clone((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer));

			// this is not normal function call (virtual function call)
			// so it should mark that don't fast popping
			g_op->disable_fast_pop();
		}
#line 3851 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 291:
#line 1768 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_pair();
		}
#line 3859 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 292:
#line 1772 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_integer(0);
		}
#line 3867 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 293:
#line 1776 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->make_pair();
		}
#line 3875 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 294:
#line 1780 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
#line 3884 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 295:
#line 1785 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_integer(0);
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
#line 3894 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 297:
#line 1796 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = 0;
		}
#line 3902 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 298:
#line 1800 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.integer);
		}
#line 3910 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 299:
#line 1808 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->fix_last_find_position();
		}
#line 3918 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 300:
#line 1816 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = OP_PUSH_OWNER;
		}
#line 3926 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 301:
#line 1820 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = OP_PUSH_CALLER;
		}
#line 3934 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 302:
#line 1824 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = OP_PUSH_ROOT;
		}
#line 3942 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 303:
#line 1828 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = OP_PUSH_MODULE;
		}
#line 3950 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 304:
#line 1832 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = OP_PUSH_MY;
		}
#line 3958 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 305:
#line 1840 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).cp) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
		}
#line 3966 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 307:
#line 1849 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_string((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 3974 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 309:
#line 1858 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_string((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 3982 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 310:
#line 1866 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->add();

			g_op->push_string((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));

			g_op->add();
		}
#line 3994 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 311:
#line 1878 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_string((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 4002 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 313:
#line 1887 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_string((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 4010 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 315:
#line 1892 "../src/parser/parser.y" /* glr.c:783  */
    {
			g_op->push_string((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp));
		}
#line 4018 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 316:
#line 1900 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).cp) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
		}
#line 4026 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 317:
#line 1908 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer);
		}
#line 4034 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 318:
#line 1916 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).integer) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.integer);
		}
#line 4042 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 319:
#line 1924 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).cp) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
		}
#line 4050 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 320:
#line 1932 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).cp) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.cp);
		}
#line 4058 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 321:
#line 1940 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).real) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.real);
		}
#line 4066 "../src/parser/parser.cpp" /* glr.c:783  */
    break;

  case 322:
#line 1948 "../src/parser/parser.y" /* glr.c:783  */
    {
			((*yyvalp).real) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.real);
		}
#line 4074 "../src/parser/parser.cpp" /* glr.c:783  */
    break;


#line 4078 "../src/parser/parser.cpp" /* glr.c:783  */
      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
                &yys->yysemantics.yysval);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YYFPRINTF (stderr, "%s unresolved", yymsg);
          else
            YYFPRINTF (stderr, "%s incomplete", yymsg);
          YY_SYMBOL_PRINT ("", yystos[yys->yylrState], YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-358)))

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  0

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yypact_value_is_default (yypact[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, size_t yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YYASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds =
    (yybool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, size_t yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yynewSize;
  size_t yyn;
  size_t yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            {
              YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
                          (unsigned long int) yyi, (unsigned long int) yyj));
            }
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
            size_t yyposn,
            YYSTYPE* yyvalp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
                 size_t yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YYASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print Args;               \
} while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (int yynormal, yyGLRStackItem* yyvsp, size_t yyk,
                 yyRuleNum yyrule)
{
  int yynrhs = yyrhsLength (yyrule);
  int yyi;
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long int) yyk, yyrule - 1,
             (unsigned long int) yyrline[yyrule]);
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyvsp[yyi - yynrhs + 1].yystate.yylrState],
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval
                                              );
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YYFPRINTF (stderr, " (unresolved)");
      YYFPRINTF (stderr, "\n");
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((1, yyrhs, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp);
    }
  else
    {
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((0, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
             yybool yyforceEval)
{
  size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yysval);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        {
          YYDPRINTF ((stderr, "Parse on stack %lu rejected by rule #%d.\n",
                     (unsigned long int) yyk, yyrule - 1));
        }
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
                  "Reduced stack %lu by rule #%d; action deferred.  "
                  "Now in state %d.\n",
                  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
                                (unsigned long int) yyk,
                                (unsigned long int) yyi));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      yybool* yynewLookaheadNeeds;

      yynewStates = YY_NULLPTR;

      if (yystackp->yytops.yycapacity
          > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      yynewStates =
        (yyGLRState**) YYREALLOC (yystackp->yytops.yystates,
                                  (yystackp->yytops.yycapacity
                                   * sizeof yynewStates[0]));
      if (yynewStates == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yystates = yynewStates;

      yynewLookaheadNeeds =
        (yybool*) YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                             (yystackp->yytops.yycapacity
                              * sizeof yynewLookaheadNeeds[0]));
      if (yynewLookaheadNeeds == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize-1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp);
    yychar = yychar_current;
    yylval = yylval_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1, (unsigned long int) (yys->yyposn + 1),
               (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]));
          else
            YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]),
                       (unsigned long int) (yystates[yyi-1]->yyposn + 1),
                       (unsigned long int) yystates[yyi]->yyposn);
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              return yyreportAmbiguity (yybest, yyp);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YYASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yystos[yys->yylrState],
                                &yysval);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             ));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, size_t yyk,
                   size_t yyposn)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
                  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule]);
          if (yyflag == yyerr)
            {
              YYDPRINTF ((stderr,
                          "Stack %lu dies "
                          "(predicate failure or explicit user error).\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yySymbol yytoken;
          int yyaction;
          const short int* yyconflicts;

          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
          if (yychar == YYEMPTY)
            {
              YYDPRINTF ((stderr, "Reading a token: "));
              yychar = yylex ();
            }

          if (yychar <= YYEOF)
            {
              yychar = yytoken = YYEOF;
              YYDPRINTF ((stderr, "Now at end of input.\n"));
            }
          else
            {
              yytoken = YYTRANSLATE (yychar);
              YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
            }

          yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);

          while (*yyconflicts != 0)
            {
              YYRESULTTAG yyflag;
              size_t yynewStack = yysplitStack (yystackp, yyk);
              YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
                          (unsigned long int) yynewStack,
                          (unsigned long int) yyk));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts]);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn));
              else if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr, "Stack %lu dies.\n",
                              (unsigned long int) yynewStack));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
              yyconflicts += 1;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction]);
              if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr,
                              "Stack %lu dies "
                              "(predicate failure or explicit user error).\n",
                              (unsigned long int) yyk));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

static void
yyreportSyntaxError (yyGLRStack* yystackp)
{
  if (yystackp->yyerrState != 0)
    return;
#if ! YYERROR_VERBOSE
  yyerror (YY_("syntax error"));
#else
  {
  yySymbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);
  size_t yysize0 = yytnamerr (YY_NULLPTR, yytokenName (yytoken));
  size_t yysize = yysize0;
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULLPTR;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected").  */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
      yyarg[yycount++] = yytokenName (yytoken);
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for this
             state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;
          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytokenName (yyx);
                {
                  size_t yysz = yysize + yytnamerr (YY_NULLPTR, yytokenName (yyx));
                  yysize_overflow |= yysz < yysize;
                  yysize = yysz;
                }
              }
        }
    }

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  {
    size_t yysz = yysize + strlen (yyformat);
    yysize_overflow |= yysz < yysize;
    yysize = yysz;
  }

  if (!yysize_overflow)
    yymsg = (char *) YYMALLOC (yysize);

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
          if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
              yyp += yytnamerr (yyp, yyarg[yyi++]);
              yyformat += 2;
            }
          else
            {
              yyp++;
              yyformat++;
            }
        }
      yyerror (yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
#endif /* YYERROR_VERBOSE */
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp)
{
  size_t yyk;
  int yyj;

  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yySymbol yytoken;
        if (yychar == YYEOF)
          yyFail (yystackp, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval);
          }
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex ();
        if (yychar <= YYEOF)
          {
            yychar = yytoken = YYEOF;
            YYDPRINTF ((stderr, "Now at end of input.\n"));
          }
        else
          {
            yytoken = YYTRANSLATE (yychar);
            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
          }
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
    if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
      break;
  if (yyk >= yystackp->yytops.yysize)
    yyFail (yystackp, YY_NULLPTR);
  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystackp, yyk);
  yyremoveDeletes (yystackp);
  yycompressStack (yystackp);

  /* Now pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYTERROR;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yytable[yyj],
                          yys->yyposn, &yylval);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
        {
          yyRuleNum yyrule;
          int yyaction;
          const short int* yyconflicts;

          yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {

                  yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue));
            }
          else
            {
              yySymbol yytoken;
              if (yychar == YYEMPTY)
                {
                  YYDPRINTF ((stderr, "Reading a token: "));
                  yychar = yylex ();
                }

              if (yychar <= YYEOF)
                {
                  yychar = yytoken = YYEOF;
                  YYDPRINTF ((stderr, "Now at end of input.\n"));
                }
              else
                {
                  yytoken = YYTRANSLATE (yychar);
                  YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
                }

              yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
              if (*yyconflicts != 0)
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {

                  yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue));
            }
        }

      while (yytrue)
        {
          yySymbol yytoken_to_shift;
          size_t yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));

              yyreportSyntaxError (&yystack);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              int yyaction;
              const short int* yyconflicts;
              yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
              yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval);
              YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                          (unsigned long int) yys,
                          yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          size_t yysize = yystack.yytops.yysize;
          size_t yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                  if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif

#undef yylval
#undef yychar
#undef yynerrs



#line 1954 "../src/parser/parser.y" /* glr.c:2551  */



