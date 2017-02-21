/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 11 "../src/parser/parser.y" /* yacc.c:339  */

#define __YACC__


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // tolower
#include <limits.h>
#include <vector>

#include "parserParser.h"

#include "parserCode.h"
#include "parserControl.h"
#include "parserOP.h"
#include "parserException.h"
#include "orca_opcode.h"
#include "parserParse.h"


//TEMP
#include "orcaRoot.h"

parserException s_ex;
parserException* g_ex = &s_ex;

// For parser
bool unary_minus = false;

int g_lvar_nil_check = 0;
int g_bnf_right_num = 0;

using namespace std;


const char* get_context();


#line 107 "../src/parser/parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
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
#line 53 "../src/parser/parser.y" /* yacc.c:355  */

	const char* cp;
	int integer;
	double real;
	void* vector_cp;	
	struct bnf* bp;	
	struct cp2_t cp2; 
	struct int2_t int2;

#line 232 "../src/parser/parser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 247 "../src/parser/parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  161
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2128

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  165
/* YYNRULES -- Number of rules.  */
#define YYNRULES  338
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  557

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,     2,     2,    94,    87,     2,     2,
      88,    82,    92,    90,    78,    91,    79,    93,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,    77,
       2,    86,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    80,     2,    81,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,    85,    76,    84,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   190,   190,   191,   192,   197,   198,   203,   204,   209,
     210,   215,   225,   226,   227,   228,   229,   230,   231,   235,
     239,   240,   241,   242,   243,   249,   248,   257,   256,   267,
     271,   278,   282,   286,   290,   294,   298,   303,   308,   313,
     322,   321,   334,   333,   342,   341,   353,   357,   371,   385,
     393,   393,   406,   407,   415,   419,   425,   424,   437,   436,
     444,   449,   454,   455,   461,   460,   469,   468,   478,   477,
     489,   493,   501,   505,   513,   519,   527,   531,   539,   543,
     547,   556,   559,   567,   568,   574,   573,   585,   586,   592,
     591,   599,   609,   610,   615,   620,   620,   629,   634,   639,
     647,   648,   649,   654,   658,   666,   676,   684,   685,   690,
     694,   690,   705,   706,   711,   719,   723,   731,   735,   739,
     747,   755,   756,   757,   758,   763,   767,   775,   779,   788,
     791,   798,   803,   802,   816,   815,   845,   853,   852,   880,
     879,   913,   912,   925,   924,   936,   951,   959,   977,  1009,
    1043,  1070,  1073,  1082,  1085,  1089,  1095,  1099,  1109,  1115,
    1125,  1129,  1133,  1139,  1149,  1153,  1162,  1166,  1161,  1175,
    1174,  1184,  1183,  1193,  1192,  1205,  1204,  1217,  1221,  1216,
    1233,  1232,  1244,  1252,  1256,  1264,  1265,  1272,  1271,  1290,
    1289,  1310,  1309,  1329,  1328,  1353,  1352,  1377,  1376,  1398,
    1397,  1419,  1418,  1440,  1439,  1460,  1465,  1469,  1473,  1477,
    1481,  1489,  1495,  1494,  1504,  1510,  1509,  1519,  1524,  1528,
    1533,  1537,  1541,  1545,  1549,  1553,  1557,  1562,  1568,  1572,
    1576,  1581,  1586,  1591,  1596,  1600,  1604,  1608,  1614,  1613,
    1624,  1625,  1630,  1634,  1638,  1642,  1646,  1651,  1655,  1659,
    1663,  1671,  1675,  1684,  1689,  1683,  1701,  1706,  1707,  1712,
    1716,  1724,  1728,  1736,  1737,  1745,  1746,  1751,  1750,  1759,
    1763,  1771,  1776,  1777,  1778,  1779,  1780,  1791,  1795,  1799,
    1803,  1807,  1811,  1815,  1819,  1823,  1827,  1831,  1835,  1839,
    1840,  1845,  1850,  1857,  1862,  1867,  1866,  1874,  1878,  1882,
    1887,  1892,  1897,  1903,  1902,  1912,  1920,  1925,  1930,  1929,
    1937,  1942,  1948,  1953,  1957,  1965,  1973,  1977,  1981,  1985,
    1989,  1997,  2005,  2006,  2014,  2015,  2023,  2035,  2039,  2044,
    2048,  2049,  2057,  2065,  2073,  2081,  2089,  2097,  2105
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
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "NIL_", "RIGHT_ARROW",
  "LEFT_ARROW", "PARALLEL", "ASSIGNMENT", "ONCE", "EVAL", "LAMBDA",
  "UNDER", "NAME", "STRING", "FORMAT_STRING_HEAD", "FORMAT_STRING_TAIL",
  "RE_STRING", "RE_FORMAT_STRING_HEAD", "HEX_STRING", "SHELL_STRING_HEAD",
  "CONTEXT", "NUMBER", "MINUS_NUMBER", "BIG_NUMBER", "MINUS_BIG_NUMBER",
  "REAL", "MINUS_REAL", "'{'", "'}'", "';'", "','", "'.'", "'['", "']'",
  "')'", "':'", "'~'", "'|'", "'='", "'%'", "'('", "'!'", "'+'", "'-'",
  "'*'", "'/'", "'$'", "$accept", "statement_list", "statement_or_block",
  "statement_block", "open_statement_block", "statement", "channel_stmt",
  "$@1", "$@2", "assign_target_list", "assign_target", "scope_stmt", "$@3",
  "parallel_stmt", "$@4", "$@5", "parallel_option", "simple_call_stmt",
  "shell_stmt", "$@6", "shell_string", "exception_stmt", "try_stmt", "$@7",
  "catch_stmt_list_with_finally", "$@8", "finally_stmt", "catch_stmt_list",
  "catch_stmt", "$@9", "$@10", "$@11", "throw_stmt", "using_stmt",
  "object_path", "debug_stmt", "control_stmt", "opt_expr_list",
  "selection_stmt", "decode_stmt", "$@12", "bnf_stmt_list", "bnf_stmt",
  "$@13", "bnf_right_list", "bnf_left", "bnf_right", "$@14", "bnf_right_",
  "bnf_node_list", "bnf_node", "terminal", "non_terminal", "action_code",
  "decode_pattern_stmt_list", "decode_pattern_stmt", "$@15", "$@16",
  "decode_pattern", "list_pattern", "pattern_list", "pattern", "p_var",
  "loop_stmt", "def", "name_or_string", "opt_under", "define_stmt", "$@17",
  "$@18", "$@19", "$@20", "once_expr", "$@21", "lambda_object", "$@22",
  "lambda_define_header", "lambda_decode_header", "lambda_parse_header",
  "opt_superclass", "opt_argument_list", "name_list", "if_elif_else_stmt",
  "elif_stmt_list", "elif_stmt", "$@23", "$@24", "else_stmt", "$@25",
  "if_stmt", "$@26", "do_stmt", "$@27", "times_stmt", "$@28", "while_stmt",
  "$@29", "$@30", "for_stmt", "$@31", "expression_stmt", "expression_list",
  "expression", "assign_expr", "$@32", "$@33", "$@34", "$@35", "$@36",
  "$@37", "$@38", "$@39", "$@40", "assign_type", "bool_expr", "or_expr",
  "$@41", "and_expr", "$@42", "not_expr", "logical_expr", "numeric_expr",
  "add_expr", "mul_expr", "unary_expr", "$@43", "list", "tuple", "map",
  "sbf", "$@44", "$@45", "sbf_result", "sbf_rule_list", "sbf_rule",
  "in_expr", "range_expr", "range_expr_sub", "$@46", "pair_list",
  "pair_expression", "primary_object", "reserved_functions",
  "eval_function", "postfix_object", "$@47", "$@48", "slice_expression",
  "$@49", "calling_body", "object", "reserved_object", "lvar",
  "format_string", "re_format_string", "format_object", "regex", "string",
  "name", "minus_number", "number", "minus_big_number", "big_number",
  "real", "minus_real", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   123,   125,    59,    44,    46,
      91,    93,    41,    58,   126,   124,    61,    37,    40,    33,
      43,    45,    42,    47,    36
};
# endif

#define YYPACT_NINF -447

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-447)))

#define YYTABLE_NINF -312

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1139,    31,  -447,  -447,  -447,  -447,  -447,  -447,  1853,  -447,
    -447,  1705,   -17,  1705,    -9,    13,  -447,   121,  -447,  -447,
     121,  -447,  -447,    78,  -447,    89,  -447,   -24,    62,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,  1705,  -447,    78,  1705,    28,  1705,  1927,  2001,  -447,
     696,  -447,  -447,  -447,  -447,  -447,  -447,    49,  -447,   101,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,    35,  -447,  -447,
    -447,    76,   116,   125,  -447,   201,  -447,  -447,  -447,  -447,
    -447,   152,    19,  -447,  -447,   114,   190,  -447,  -447,   206,
      73,    68,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
     109,  -447,  -447,    71,   132,   132,  -447,  -447,   137,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,    78,    78,  -447,    21,
    -447,   147,  1853,  -447,    43,   212,  -447,   169,   174,  -447,
    -447,  -447,   147,  -447,   -35,  -447,  -447,    69,    71,    71,
    -447,   -17,   787,  1705,     6,   -12,  -447,   171,   128,  -447,
      71,    71,   199,   193,   242,  -447,   228,   -21,  -447,  -447,
    2001,  -447,   875,  -447,  -447,  -447,   132,   121,  -447,   208,
    -447,    38,   -38,  1705,  -447,  -447,   -22,  -447,  -447,   201,
    -447,  -447,  -447,  1705,   293,  -447,  -447,   147,  -447,  -447,
    1927,  1927,  1927,  1927,  1927,  1927,  1927,  1927,  -447,  -447,
    -447,  2001,  2001,  2001,    46,   544,  1705,   226,  -447,  -447,
    -447,  -447,  -447,  -447,   247,  -447,  -447,   162,  -447,  -447,
    -447,  -447,   147,    46,   544,   875,   313,  -447,   279,  2001,
    -447,  -447,  1705,  -447,   121,   281,  -447,  -447,  -447,   147,
     320,  -447,   963,  -447,   274,   271,   271,   285,   280,  -447,
      51,  -447,  1705,  -447,  1301,  -447,  -447,  -447,  1375,  1705,
    1705,  1450,  1705,  -447,  -447,  -447,  1051,    -6,  -447,   147,
      -3,   326,  -447,   121,   121,   121,  -447,  -447,    76,   174,
     147,   291,  -447,  1779,   288,    50,  -447,  -447,  -447,  -447,
    1853,   147,  -447,  -447,  -447,  -447,  2040,  1705,  -447,  1853,
    1853,  -447,  -447,  -447,  -447,  -447,  -447,    68,    68,  -447,
    -447,  -447,   226,    71,    71,   182,   289,   194,   200,  1535,
    -447,  1705,  1705,  -447,  -447,  -447,  -447,   207,  1853,   147,
    -447,  -447,   214,  -447,  -447,  1705,  1705,  -447,  2001,  -447,
    -447,  -447,  -447,  -447,  -447,    37,  -447,  -447,  -447,  -447,
    1705,  1705,  -447,    84,  -447,   283,  -447,   294,   220,  -447,
    -447,   -17,   147,   147,  -447,   271,   271,   316,  1705,   316,
    -447,  -447,  -447,   -39,   325,  -447,   301,  -447,    88,  -447,
     112,  -447,  -447,   297,  -447,  -447,   147,    78,    78,   235,
    -447,   237,   241,   243,   190,  -447,  -447,  -447,  -447,  1705,
    1705,    71,    71,  -447,  -447,    58,  -447,   321,  -447,  -447,
     306,  -447,   309,   147,  -447,  -447,  -447,   327,   304,  -447,
    -447,  -447,  -447,  1705,  -447,  -447,  -447,  1705,   312,  -447,
    -447,   316,   316,   121,   317,   314,  -447,  -447,  -447,  1779,
     307,  1705,  -447,  -447,   323,  -447,   147,  -447,   249,   251,
     255,   260,  -447,  2040,    46,   544,  -447,  1705,  1705,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  1705,  -447,
    -447,   328,  1853,   315,   -17,   147,  -447,  -447,   322,  -447,
    -447,   147,  1227,  -447,   318,   -17,  -447,  -447,  -447,   -45,
    -447,   150,  -447,  -447,   264,   268,   266,  -447,  -447,  1705,
    1705,   342,   147,  -447,  -447,   102,  -447,  -447,   353,  -447,
    -447,   332,   333,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
     150,  -447,  -447,  -447,  -447,  -447,    71,    71,  -447,  -447,
    1705,  -447,  1853,  -447,  1620,  -447,   -22,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,   329,  -447,   331,   334,    82,  1705,
    1705,  1705,  -447,  -447,  -447,  -447,  -447
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      50,     0,   126,   320,   316,   317,   318,   319,     0,   173,
     177,     0,     0,    81,     0,     0,    56,     0,    76,    77,
       0,   286,   287,     0,   288,     0,   141,     0,   153,   332,
     329,   323,   327,   325,   331,   334,   333,   336,   335,   337,
     338,     0,    24,     0,    81,     0,     0,     0,     0,   238,
      50,     4,    23,    20,    21,    18,    19,     0,    16,     0,
      55,    17,    22,    12,    13,    84,    14,     0,    15,   186,
     275,   151,     0,     0,    83,   160,   122,   124,   123,   121,
      11,     0,   184,   185,   205,   211,   214,   217,   219,   226,
     227,   233,   237,   272,   273,   274,   246,   306,   290,   291,
     315,   241,   285,   276,   330,   328,   283,   284,   321,   278,
     277,   280,   279,   281,   282,   125,     0,     0,   171,   315,
     276,     0,     0,    85,   315,     0,   321,     0,    82,   184,
      79,    80,     0,   128,     0,    75,   127,     0,   299,   300,
      42,     0,    50,     0,     0,     0,   148,     0,     0,   270,
     301,   302,     0,    82,   184,   253,     0,   184,   218,   240,
       0,     1,    50,     3,     2,    53,    51,    68,    54,    60,
      63,     0,   153,     0,   143,   109,     0,   166,   169,   163,
     165,   161,   182,     0,     0,    27,    25,     0,   212,   215,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,     0,     0,     0,     0,     0,     0,     0,   207,   208,
     209,   210,   206,   187,     0,   322,   324,     0,   299,   300,
     301,   302,     0,     0,     0,    50,     0,   178,     0,     0,
      78,    57,     0,    70,     0,     0,    72,   197,   199,     0,
       0,    10,    50,   142,     0,   153,   153,     0,     0,   154,
       0,   159,     0,   251,     0,   201,   203,   242,     0,     0,
       0,     0,     0,   289,   239,     8,    50,   184,    52,     0,
      64,     0,    62,     0,     0,     0,   132,   131,   151,   152,
       0,   109,   108,     0,     0,     0,    88,    89,    94,   105,
       0,     0,   164,   162,   183,   175,     0,     0,    41,     0,
       0,   224,   225,   220,   221,   222,   223,   228,   229,   236,
     234,   235,     0,   293,   294,   308,   312,     0,     0,     0,
     296,     0,     0,   304,   172,   293,   294,     0,     0,     0,
     109,   180,     0,    74,    73,     0,     0,    43,     0,     9,
     292,   149,   150,   145,   155,     0,   156,   271,   252,   269,
       0,     0,   243,     0,   256,     0,   248,   183,     0,     7,
      69,     0,     0,     0,    59,   153,   153,   129,     0,   129,
     144,   146,   107,     0,     0,   113,   112,   116,   118,   117,
       0,   147,    87,     0,   167,   170,     0,     0,     0,     0,
      30,   295,   276,     0,   213,   216,   305,   189,   191,     0,
     310,   297,   298,    49,   313,     0,   188,     0,   297,   298,
       0,   179,   109,     0,    71,   198,   200,    46,     0,   158,
     202,   204,   244,     0,   254,   247,   249,     0,    66,    65,
      61,   129,   129,     0,     0,     0,   134,   120,   110,     0,
       0,     0,   103,   104,     0,    95,     0,   176,   299,   300,
     301,   302,    28,     0,     0,     0,    26,     0,     0,   309,
     307,   193,   195,   314,   326,   174,    86,   181,     0,    44,
     157,     0,     0,     0,     0,     0,   139,   137,   130,   136,
     133,     0,    50,   115,   118,     0,   114,   119,    91,     0,
      93,     0,   168,    29,   293,   294,     0,   190,   192,     0,
       0,    47,     0,   245,   259,     0,   258,   260,   276,   250,
      67,     0,     0,   135,   111,     6,     5,    90,    95,    96,
      97,    99,   100,   101,   102,   106,   297,   298,   194,   196,
       0,    45,     0,   255,     0,   109,     0,    92,    98,    34,
      35,    48,   257,   267,   261,   262,   264,   109,     0,     0,
     266,     0,   140,   138,   268,   265,   263
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -447,    14,  -447,   183,  -447,   -49,  -447,  -447,  -447,  -447,
     -42,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,   246,  -447,
    -447,  -447,  -447,  -447,   -13,  -447,  -447,   375,  -447,  -447,
    -447,  -115,  -279,  -447,  -447,  -447,   -95,  -447,  -447,  -447,
     -96,    45,  -446,  -447,  -317,  -277,  -447,  -447,  -447,  -447,
    -447,   -10,   -90,  -447,  -447,    61,  -353,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,  -428,  -447,  -447,  -447,  -447,   148,
    -164,    66,  -447,  -447,   252,  -447,  -447,   253,  -447,  -447,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,    47,   -11,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,  -447,  -447,  -128,    -5,  -447,  -447,   135,  -447,   136,
     388,   106,  -447,   155,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,  -447,  -447,  -447,   -94,  -447,  -447,  -447,  -447,  -447,
     185,  -447,  -447,  -447,    65,  -447,  -447,  -219,  -447,   130,
     -33,   -14,   370,  -447,  -447,   -86,  -447,   233,     8,   347,
    -447,   355,  -447,  -447,   361
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   266,   514,   163,   243,    51,    52,   297,   296,   389,
     390,    53,   187,    54,   239,   502,   469,    55,    56,    57,
     166,    58,    59,   132,   168,   271,   364,   169,   170,   362,
     475,   269,    60,    61,   134,    62,    63,   127,    64,    65,
     228,   285,   286,   383,   489,   287,   490,   491,   519,   520,
     521,   522,   288,   524,   281,   282,   283,   482,   374,   375,
     376,   377,   378,    66,    67,   135,   434,    68,   368,   481,
     512,   511,    69,   142,    70,   280,    71,    72,    73,   174,
     146,   250,    74,   179,   180,   290,   446,   181,   291,    75,
     222,    76,   121,    77,   386,    78,   122,   329,    79,   413,
      80,    81,    82,    83,   321,   457,   458,   499,   500,   335,
     336,   350,   351,   213,    84,    85,   299,    86,   300,    87,
      88,    89,    90,    91,    92,   160,    93,    94,    95,    96,
     260,   472,   355,   505,   506,   507,   545,   546,   549,   148,
     149,    97,    98,    99,   124,   207,   217,   317,   399,   320,
     101,   102,   103,   104,   105,   215,   106,   107,   108,   109,
     110,   111,   112,   113,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     123,   164,   129,   118,   372,   327,   382,   137,   278,   139,
     237,   238,   184,   412,    50,   159,   436,   276,   232,   216,
     126,    29,   255,   256,   262,   136,   245,   246,   136,   151,
     147,   136,   517,   154,   248,   157,   115,   184,    29,   277,
     518,   155,   233,    29,   234,   523,   185,   186,    29,   361,
     145,   136,   312,     3,     4,     5,     6,     7,   273,   274,
     128,   263,   284,   525,   143,   100,    29,   133,   130,   -40,
     249,   185,   186,   119,   523,   136,   234,   252,   476,   477,
     268,   341,   342,   418,   138,     3,     4,     5,     6,     7,
     131,   153,   525,   156,   -40,    29,   133,    29,    29,   133,
     223,   224,   219,   221,   150,   140,    29,   133,   155,  -295,
      29,   141,   119,   119,   171,   100,   165,   227,   208,   209,
     210,   211,   204,   205,   136,   136,   381,   264,   172,   345,
     235,  -295,   244,   346,   284,   372,   183,   167,    29,   133,
     463,   144,    29,    36,   188,    38,   236,    40,   234,   126,
     145,   267,   136,   251,   270,   201,   242,   212,   553,   173,
     202,   203,   129,   196,   197,   422,   284,   423,   309,   310,
     311,   440,   294,   442,   441,   136,   443,   218,   220,   136,
     532,    29,   133,   533,   289,   397,   398,   119,   204,   205,
     314,   175,   206,   164,   316,   129,   331,  -295,  -303,  -303,
     176,   431,   432,  -303,   253,   247,   254,   100,    28,   326,
      29,   442,   136,   316,   443,   177,   178,   164,   547,   189,
     279,   129,   225,    30,    31,   119,   214,   100,    34,   182,
     183,   136,   275,   190,   191,   229,   496,   192,   193,   194,
     195,   347,   136,   147,   167,   -58,   230,   294,   353,   354,
     357,   358,   183,   318,   252,   119,   119,   119,   119,   119,
     119,   119,   119,  -311,  -311,   313,   119,   119,   119,   382,
     372,   258,   379,   461,   462,   401,   402,   403,   183,   332,
     257,   136,   136,   136,   325,   384,   129,   259,   408,   409,
     100,   414,   183,   289,   119,   333,   301,   302,   303,   304,
     305,   306,   426,   427,   226,   417,   261,   100,   129,   295,
     406,   407,   452,   453,   319,   231,   454,   455,   -31,   -31,
     456,   183,   322,   410,   415,   416,   -36,   -36,   -37,   -37,
     328,   100,   -38,   -38,   365,   366,   367,   -39,   -39,   420,
     421,   -32,   -32,   338,   393,   -33,   -33,   526,   527,   484,
     486,   307,   308,   419,   330,   119,   340,   435,   334,   145,
     343,   391,   344,   363,   119,   119,   405,   371,   424,   251,
     298,   380,   400,   449,   451,   433,   425,   438,   120,   439,
     445,   126,   125,   465,   464,   466,   470,   468,   459,   460,
     474,   480,   479,   119,   485,   136,   136,   509,   539,   540,
     488,   234,   530,   119,   441,   324,   534,   535,   536,   503,
     552,   493,   471,   550,   551,   272,   473,   120,   120,   152,
     478,   548,   337,   537,   538,   444,   369,   428,   379,   483,
     487,   292,   293,   516,   394,   158,   395,   198,   542,   349,
     495,   136,   396,     0,   316,   199,   497,   498,   448,   450,
     323,   200,   360,     0,     0,     0,     0,   501,     0,     0,
       0,     0,   136,   370,     0,     0,     0,   504,     0,     0,
       0,     0,     0,     0,   385,     0,     0,     0,     0,     0,
       0,     0,   419,     0,     0,     0,     0,     0,   528,   529,
       0,     0,   120,   126,     0,     0,     0,     0,     0,   289,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   240,   411,     0,     0,   494,     0,     0,   391,   541,
       0,     0,     0,   544,     0,     0,     0,   504,   289,     0,
     120,     0,     0,     0,     0,     0,     0,   119,   554,   555,
     556,     0,     0,     0,   289,   429,   430,   100,     0,     0,
       0,     3,     4,     5,     6,     7,   289,     0,     0,     0,
     120,   120,   120,   120,   120,   120,   120,   120,     0,   447,
       0,   120,   120,   120,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
       0,     0,     0,     0,     0,    24,   467,   119,     0,   120,
      26,    27,    28,     0,    29,    30,    31,     0,    32,    33,
      34,     0,     0,    35,    36,    37,    38,    39,    40,    41,
       0,     0,     0,    43,    44,     0,     0,   315,     0,   492,
       0,    45,    46,    47,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   510,     0,
     120,     0,     0,     0,   513,   515,   392,     0,     0,   120,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   531,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   161,     0,   120,     0,
       1,     2,     0,     3,     4,     5,     6,     7,   120,     8,
       0,     0,     9,    10,     0,     0,    11,     0,    12,     0,
      13,    14,    15,     0,     0,     0,     0,     0,     0,     0,
       0,    16,     0,     0,    17,     0,    18,    19,    20,    21,
      22,    23,     0,   437,     0,     0,     0,    24,     0,     0,
      25,     0,    26,    27,    28,     0,    29,    30,    31,     0,
      32,    33,    34,     0,     0,    35,    36,    37,    38,    39,
      40,   162,     0,    42,     0,    43,    44,     0,     0,     0,
       0,     0,     0,    45,    46,    47,    48,    49,     0,     0,
       0,     1,     2,     0,     3,     4,     5,     6,     7,     0,
       8,     0,     0,     9,    10,     0,     0,    11,     0,    12,
       0,    13,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,    16,   392,     0,    17,     0,    18,    19,    20,
      21,    22,    23,     0,     0,     0,     0,     0,    24,     0,
       0,    25,   508,    26,    27,    28,     0,    29,    30,    31,
       0,    32,    33,    34,     0,   437,    35,    36,    37,    38,
      39,    40,    41,   241,    42,     0,    43,    44,     0,     0,
       0,     0,     0,     0,    45,    46,    47,    48,    49,     1,
       2,     0,     3,     4,     5,     6,     7,     0,     8,     0,
       0,     9,    10,     0,     0,    11,     0,    12,     0,    13,
      14,    15,   508,     0,     0,     0,     0,     0,     0,     0,
      16,     0,     0,    17,     0,    18,    19,    20,    21,    22,
      23,     0,     0,     0,     0,     0,    24,     0,     0,    25,
       0,    26,    27,    28,     0,    29,    30,    31,     0,    32,
      33,    34,     0,     0,    35,    36,    37,    38,    39,    40,
      41,   265,    42,     0,    43,    44,     0,     0,     0,     0,
       0,     0,    45,    46,    47,    48,    49,     1,     2,     0,
       3,     4,     5,     6,     7,     0,     8,     0,     0,     9,
      10,     0,     0,    11,     0,    12,     0,    13,    14,    15,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
       0,    17,     0,    18,    19,    20,    21,    22,    23,     0,
       0,     0,     0,     0,    24,     0,     0,    25,     0,    26,
      27,    28,     0,    29,    30,    31,     0,    32,    33,    34,
       0,     0,    35,    36,    37,    38,    39,    40,   162,   339,
      42,     0,    43,    44,     0,     0,     0,     0,     0,     0,
      45,    46,    47,    48,    49,     1,     2,     0,     3,     4,
       5,     6,     7,     0,     8,     0,     0,     9,    10,     0,
       0,    11,     0,    12,     0,    13,    14,    15,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,     0,    17,
       0,    18,    19,    20,    21,    22,    23,     0,     0,     0,
       0,     0,    24,     0,     0,    25,     0,    26,    27,    28,
       0,    29,    30,    31,     0,    32,    33,    34,     0,     0,
      35,    36,    37,    38,    39,    40,   162,   359,    42,     0,
      43,    44,     0,     0,     0,     0,     0,     0,    45,    46,
      47,    48,    49,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     8,     0,     0,     9,    10,     0,     0,    11,
       0,    12,     0,    13,    14,    15,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     0,     0,    17,     0,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,    25,     0,    26,    27,    28,     0,    29,
      30,    31,     0,    32,    33,    34,     0,     0,    35,    36,
      37,    38,    39,    40,    41,     0,    42,     0,    43,    44,
       0,     0,     0,     0,     0,     0,    45,    46,    47,    48,
      49,     1,     2,     0,     3,     4,     5,     6,     7,     0,
       8,     0,     0,     9,    10,     0,     0,    11,     0,    12,
       0,    13,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,     0,    17,     0,    18,    19,    20,
      21,    22,    23,     0,     0,     0,     0,     0,    24,     0,
       0,    25,     0,    26,    27,    28,     0,    29,    30,    31,
       0,    32,    33,    34,     0,     0,    35,    36,    37,    38,
      39,    40,   162,     0,    42,     0,    43,    44,     3,     4,
       5,     6,     7,     0,    45,    46,    47,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    22,    23,     0,     0,     0,
       0,     0,    24,     0,     0,     0,     0,    26,    27,    28,
       0,    29,    30,    31,     0,    32,    33,    34,     0,     0,
      35,    36,    37,    38,    39,    40,    41,   348,     0,     0,
      43,    44,     3,     4,     5,     6,     7,     0,    45,    46,
      47,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,     0,     0,     0,     0,     0,    24,     0,     0,     0,
       0,    26,    27,    28,     0,    29,    30,    31,     0,    32,
      33,    34,     0,     0,    35,    36,    37,    38,    39,    40,
      41,     0,     0,     0,    43,    44,   352,     3,     4,     5,
       6,     7,    45,    46,    47,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,     0,     0,     0,     0,
       0,    24,     0,     0,     0,     0,    26,    27,    28,     0,
      29,    30,    31,     0,    32,    33,    34,     0,     0,    35,
      36,    37,    38,    39,    40,    41,     0,     0,     0,    43,
      44,     0,   356,     0,     0,     0,     0,    45,    46,    47,
      48,    49,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,     0,     0,     0,     0,     0,    24,     0,     0,     0,
       0,    26,    27,    28,     0,    29,    30,    31,     0,    32,
      33,    34,     0,     0,    35,    36,    37,    38,    39,    40,
      41,     0,     0,     0,    43,    44,     0,   404,     0,     0,
       0,     0,    45,    46,    47,    48,    49,     3,     4,     5,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,     0,     0,     0,     0,
       0,    24,     0,     0,     0,     0,    26,    27,    28,     0,
      29,    30,    31,     0,    32,    33,    34,     0,     0,    35,
      36,    37,    38,    39,    40,    41,     0,     0,     0,    43,
      44,     0,     0,     0,   543,     0,     0,    45,    46,    47,
      48,    49,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,     0,     0,     0,     0,     0,    24,     0,     0,     0,
       0,    26,    27,    28,     0,    29,    30,    31,     0,    32,
      33,    34,     0,     0,    35,    36,    37,    38,    39,    40,
      41,     0,     0,     0,    43,    44,     3,     4,     5,     6,
       7,     0,    45,    46,    47,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,    26,    27,    28,     0,    29,
      30,    31,     0,    32,    33,    34,     0,     0,    35,    36,
      37,    38,    39,    40,    41,     0,     0,     0,    43,    44,
       3,     4,     5,     6,     7,     0,   373,    46,    47,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,   116,     0,
       0,     0,     0,     0,    24,     0,     0,     0,     0,     0,
      27,    28,     0,    29,    30,    31,     0,    32,    33,    34,
       0,     0,    35,    36,    37,    38,    39,    40,    41,     0,
       0,     0,   117,    44,     3,     4,     5,     6,     7,     0,
      45,    46,    47,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,    22,   116,     0,     0,     0,     0,     0,    24,     0,
       0,     0,     0,     0,    27,    28,     0,    29,    30,    31,
       0,    32,    33,    34,     0,     0,    35,    36,    37,    38,
      39,    40,    41,     0,     0,     0,   117,    44,     3,     4,
       5,     6,     7,     0,    45,    46,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    22,   116,     3,     4,     5,
       6,     7,    24,     0,     0,     0,     0,     0,    27,    28,
       0,    29,    30,    31,     0,    32,    33,    34,     0,     0,
      35,    36,    37,    38,    39,    40,    41,     0,     0,     0,
     117,    44,     0,    21,    22,   387,     0,     0,    45,    46,
       0,    24,     0,     0,     0,     0,     0,    27,    28,     0,
      29,    30,    31,     0,    32,    33,    34,     0,     0,    35,
      36,    37,    38,    39,    40,    41,     0,     0,     0,   388,
      44,     0,     0,     0,     0,     0,     0,    45,    46
};

static const yytype_int16 yycheck[] =
{
      11,    50,    13,     8,   281,   224,   285,    20,   172,    23,
     138,   139,    18,   330,     0,    48,   369,    55,    53,   105,
      12,    60,   150,   151,    45,    17,    20,    21,    20,    43,
      41,    23,    77,    44,    46,    46,     5,    18,    60,    77,
      85,    80,    77,    60,    79,   491,    52,    53,    60,    52,
      88,    43,     6,     7,     8,     9,    10,    11,    20,    21,
      13,    82,    84,   491,    88,     0,    60,    61,    77,    75,
      82,    52,    53,     8,   520,    67,    79,    83,   431,   432,
     166,   245,   246,    46,    23,     7,     8,     9,    10,    11,
      77,    44,   520,    46,    75,    60,    61,    60,    60,    61,
      79,    80,   116,   117,    43,    16,    60,    61,    80,    88,
      60,    22,    47,    48,    79,    50,    67,   122,    47,    48,
      49,    50,    79,    80,   116,   117,    76,   160,    67,    78,
      61,    88,   143,    82,    84,   412,    78,    36,    60,    61,
      82,    79,    60,    70,    30,    72,    77,    74,    79,   141,
      88,   162,   144,   145,   167,    87,   142,    86,    76,    83,
      92,    93,   173,    90,    91,    81,    84,    83,   201,   202,
     203,    83,   183,    61,    86,   167,    64,   116,   117,   171,
      78,    60,    61,    81,   176,   313,   314,   122,    79,    80,
     204,    75,    83,   242,   205,   206,   229,    88,    61,    62,
      75,   365,   366,    66,    76,   144,    78,   142,    58,   223,
      60,    61,   204,   224,    64,    14,    15,   266,   535,    29,
     173,   232,    75,    61,    62,   160,    94,   162,    66,    77,
      78,   223,   171,    27,    28,    23,   455,    31,    32,    33,
      34,   252,   234,   254,    36,    37,    77,   258,   259,   260,
     261,   262,    78,   206,    83,   190,   191,   192,   193,   194,
     195,   196,   197,    81,    82,   204,   201,   202,   203,   548,
     547,    78,   283,   401,   402,    81,    82,    77,    78,   232,
      81,   273,   274,   275,   223,   290,   297,    45,    81,    82,
     225,    77,    78,   285,   229,   234,   190,   191,   192,   193,
     194,   195,    82,    83,   121,   338,    78,   242,   319,    16,
     321,   322,    77,    78,    88,   132,    79,    80,    77,    78,
      77,    78,    75,   328,   335,   336,    77,    78,    77,    78,
      17,   266,    77,    78,   273,   274,   275,    77,    78,   350,
     351,    77,    78,    23,   297,    77,    78,    81,    82,   439,
     440,   196,   197,   345,    75,   290,    82,   368,    77,    88,
      75,   296,    82,    37,   299,   300,   319,    76,    85,   361,
     187,    83,    83,   387,   388,    59,    82,    52,     8,    78,
      83,   373,    12,    77,    63,    76,    82,    60,   399,   400,
      78,    77,    75,   328,    87,   387,   388,    82,   526,   527,
      77,    79,    60,   338,    86,   222,    53,    75,    75,    81,
      76,   453,   423,    84,    83,   169,   427,    47,    48,    44,
     433,   536,   239,   518,   520,   380,   278,   361,   439,   439,
     441,   179,   179,   482,   299,    47,   300,    90,   532,   254,
     454,   433,   312,    -1,   455,    90,   457,   458,   387,   388,
     217,    90,   269,    -1,    -1,    -1,    -1,   468,    -1,    -1,
      -1,    -1,   454,   280,    -1,    -1,    -1,   472,    -1,    -1,
      -1,    -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   474,    -1,    -1,    -1,    -1,    -1,   499,   500,
      -1,    -1,   122,   485,    -1,    -1,    -1,    -1,    -1,   491,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,   329,    -1,    -1,   454,    -1,    -1,   453,   530,
      -1,    -1,    -1,   534,    -1,    -1,    -1,   532,   520,    -1,
     160,    -1,    -1,    -1,    -1,    -1,    -1,   472,   549,   550,
     551,    -1,    -1,    -1,   536,   362,   363,   482,    -1,    -1,
      -1,     7,     8,     9,    10,    11,   548,    -1,    -1,    -1,
     190,   191,   192,   193,   194,   195,   196,   197,    -1,   386,
      -1,   201,   202,   203,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,   413,   532,    -1,   229,
      56,    57,    58,    -1,    60,    61,    62,    -1,    64,    65,
      66,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    79,    80,    -1,    -1,    83,    -1,   446,
      -1,    87,    88,    89,    90,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   475,    -1,
     290,    -1,    -1,    -1,   481,   482,   296,    -1,    -1,   299,
     300,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   502,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     0,    -1,   328,    -1,
       4,     5,    -1,     7,     8,     9,    10,    11,   338,    13,
      -1,    -1,    16,    17,    -1,    -1,    20,    -1,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    38,    -1,    40,    41,    42,    43,
      44,    45,    -1,   373,    -1,    -1,    -1,    51,    -1,    -1,
      54,    -1,    56,    57,    58,    -1,    60,    61,    62,    -1,
      64,    65,    66,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    -1,    77,    -1,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    87,    88,    89,    90,    91,    -1,    -1,
      -1,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      13,    -1,    -1,    16,    17,    -1,    -1,    20,    -1,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,   453,    -1,    38,    -1,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    54,   472,    56,    57,    58,    -1,    60,    61,    62,
      -1,    64,    65,    66,    -1,   485,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    88,    89,    90,    91,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    13,    -1,
      -1,    16,    17,    -1,    -1,    20,    -1,    22,    -1,    24,
      25,    26,   532,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    38,    -1,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    54,
      -1,    56,    57,    58,    -1,    60,    61,    62,    -1,    64,
      65,    66,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    88,    89,    90,    91,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    13,    -1,    -1,    16,
      17,    -1,    -1,    20,    -1,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    54,    -1,    56,
      57,    58,    -1,    60,    61,    62,    -1,    64,    65,    66,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    91,     4,     5,    -1,     7,     8,
       9,    10,    11,    -1,    13,    -1,    -1,    16,    17,    -1,
      -1,    20,    -1,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,
      -1,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    54,    -1,    56,    57,    58,
      -1,    60,    61,    62,    -1,    64,    65,    66,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,
      89,    90,    91,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,
      -1,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    54,    -1,    56,    57,    58,    -1,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    -1,    77,    -1,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,
      91,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      13,    -1,    -1,    16,    17,    -1,    -1,    20,    -1,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    38,    -1,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    54,    -1,    56,    57,    58,    -1,    60,    61,    62,
      -1,    64,    65,    66,    -1,    -1,    69,    70,    71,    72,
      73,    74,    75,    -1,    77,    -1,    79,    80,     7,     8,
       9,    10,    11,    -1,    87,    88,    89,    90,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      -1,    60,    61,    62,    -1,    64,    65,    66,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      79,    80,     7,     8,     9,    10,    11,    -1,    87,    88,
      89,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    -1,    60,    61,    62,    -1,    64,
      65,    66,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    -1,    -1,    -1,    79,    80,    81,     7,     8,     9,
      10,    11,    87,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    56,    57,    58,    -1,
      60,    61,    62,    -1,    64,    65,    66,    -1,    -1,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,    79,
      80,    -1,    82,    -1,    -1,    -1,    -1,    87,    88,    89,
      90,    91,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    -1,    60,    61,    62,    -1,    64,
      65,    66,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    -1,    -1,    -1,    79,    80,    -1,    82,    -1,    -1,
      -1,    -1,    87,    88,    89,    90,    91,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    56,    57,    58,    -1,
      60,    61,    62,    -1,    64,    65,    66,    -1,    -1,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,    79,
      80,    -1,    -1,    -1,    84,    -1,    -1,    87,    88,    89,
      90,    91,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    -1,    60,    61,    62,    -1,    64,
      65,    66,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    -1,    -1,    -1,    79,    80,     7,     8,     9,    10,
      11,    -1,    87,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    -1,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    79,    80,
       7,     8,     9,    10,    11,    -1,    87,    88,    89,    90,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      57,    58,    -1,    60,    61,    62,    -1,    64,    65,    66,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    79,    80,     7,     8,     9,    10,    11,    -1,
      87,    88,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    58,    -1,    60,    61,    62,
      -1,    64,    65,    66,    -1,    -1,    69,    70,    71,    72,
      73,    74,    75,    -1,    -1,    -1,    79,    80,     7,     8,
       9,    10,    11,    -1,    87,    88,    -1,    90,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,     7,     8,     9,
      10,    11,    51,    -1,    -1,    -1,    -1,    -1,    57,    58,
      -1,    60,    61,    62,    -1,    64,    65,    66,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    -1,    -1,    -1,
      79,    80,    -1,    43,    44,    45,    -1,    -1,    87,    88,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    57,    58,    -1,
      60,    61,    62,    -1,    64,    65,    66,    -1,    -1,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     4,     5,     7,     8,     9,    10,    11,    13,    16,
      17,    20,    22,    24,    25,    26,    35,    38,    40,    41,
      42,    43,    44,    45,    51,    54,    56,    57,    58,    60,
      61,    62,    64,    65,    66,    69,    70,    71,    72,    73,
      74,    75,    77,    79,    80,    87,    88,    89,    90,    91,
      96,   100,   101,   106,   108,   112,   113,   114,   116,   117,
     127,   128,   130,   131,   133,   134,   158,   159,   162,   167,
     169,   171,   172,   173,   177,   184,   186,   188,   190,   193,
     195,   196,   197,   198,   209,   210,   212,   214,   215,   216,
     217,   218,   219,   221,   222,   223,   224,   236,   237,   238,
     239,   245,   246,   247,   248,   249,   251,   252,   253,   254,
     255,   256,   257,   258,   259,     5,    45,    79,   209,   239,
     247,   187,   191,   197,   239,   247,   253,   132,   196,   197,
      77,    77,   118,    61,   129,   160,   253,   129,   160,   246,
      16,    22,   168,    88,    79,    88,   175,   197,   234,   235,
     160,   246,   132,   196,   197,    80,   196,   197,   215,   245,
     220,     0,    75,    98,   100,    67,   115,    36,   119,   122,
     123,    79,   160,    83,   174,    75,    75,    14,    15,   178,
     179,   182,    77,    78,    18,    52,    53,   107,    30,    29,
      27,    28,    31,    32,    33,    34,    90,    91,   254,   256,
     259,    87,    92,    93,    79,    80,    83,   240,    47,    48,
      49,    50,    86,   208,    94,   250,   250,   241,   160,   246,
     160,   246,   185,    79,    80,    75,    98,   209,   135,    23,
      77,    98,    53,    77,    79,    61,    77,   208,   208,   109,
     247,    76,    96,    99,   197,    20,    21,   160,    46,    82,
     176,   253,    83,    76,    78,   208,   208,    81,    78,    45,
     225,    78,    45,    82,   245,    76,    96,   197,   250,   126,
     129,   120,   123,    20,    21,   160,    55,    77,   175,   196,
     170,   149,   150,   151,    84,   136,   137,   140,   147,   253,
     180,   183,   179,   182,   197,    16,   103,   102,    98,   211,
     213,   216,   216,   216,   216,   216,   216,   218,   218,   245,
     245,   245,     6,   160,   246,    83,   197,   242,   196,    88,
     244,   199,    75,   252,    98,   160,   246,   242,    17,   192,
      75,   245,   196,   160,    77,   204,   205,    98,    23,    76,
      82,   175,   175,    75,    82,    78,    82,   197,    76,   235,
     206,   207,    81,   197,   197,   227,    82,   197,   197,    76,
      98,    52,   124,    37,   121,   160,   160,   160,   163,   174,
      98,    76,   150,    87,   153,   154,   155,   156,   157,   197,
      83,    76,   137,   138,   209,    98,   189,    45,    79,   104,
     105,   239,   247,   196,   212,   214,   244,   208,   208,   243,
      83,    81,    82,    77,    82,   196,   197,   197,    81,    82,
     209,    98,   149,   194,    77,   197,   197,   245,    46,   253,
     197,   197,    81,    83,    85,    82,    82,    83,   176,    98,
      98,   175,   175,    59,   161,   197,   161,   247,    52,    78,
      83,    86,    61,    64,   146,    83,   181,    98,   160,   246,
     160,   246,    77,    78,    79,    80,    77,   200,   201,   197,
     197,   208,   208,    82,    63,    77,    76,    98,    60,   111,
      82,   197,   226,   197,    78,   125,   161,   161,   129,    75,
      77,   164,   152,   156,   157,    87,   157,   197,    77,   139,
     141,   142,    98,   105,   160,   246,   242,   197,   197,   202,
     203,   197,   110,    81,   209,   228,   229,   230,   247,    82,
      98,   166,   165,    98,    97,    98,   100,    77,    85,   143,
     144,   145,   146,   147,   148,   169,    81,    82,   197,   197,
      60,    98,    78,    81,    53,    75,    75,   141,   145,   208,
     208,   197,   229,    84,   197,   231,   232,   149,   136,   233,
      84,    83,    76,    76,   197,   197,   197
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    95,    96,    96,    96,    97,    97,    98,    98,    99,
      99,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   102,   101,   103,   101,   104,
     104,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     107,   106,   109,   108,   110,   108,   111,   111,   111,   112,
     114,   113,   115,   115,   116,   116,   118,   117,   120,   119,
     119,   121,   122,   122,   124,   123,   125,   123,   126,   123,
     127,   127,   128,   128,   129,   129,   130,   130,   131,   131,
     131,   132,   132,   133,   133,   135,   134,   136,   136,   138,
     137,   137,   139,   139,   140,   142,   141,   143,   144,   144,
     145,   145,   145,   146,   146,   147,   148,   149,   149,   151,
     152,   150,   153,   153,   154,   155,   155,   156,   156,   156,
     157,   158,   158,   158,   158,   159,   159,   160,   160,   161,
     161,   162,   163,   162,   164,   162,   162,   165,   162,   166,
     162,   168,   167,   170,   169,   169,   169,   169,   171,   172,
     173,   174,   174,   175,   175,   175,   175,   175,   176,   176,
     177,   177,   177,   177,   178,   178,   180,   181,   179,   183,
     182,   185,   184,   187,   186,   189,   188,   191,   192,   190,
     194,   193,   195,   196,   196,   197,   197,   199,   198,   200,
     198,   201,   198,   202,   198,   203,   198,   204,   198,   205,
     198,   206,   198,   207,   198,   198,   208,   208,   208,   208,
     208,   209,   211,   210,   210,   213,   212,   212,   214,   214,
     215,   215,   215,   215,   215,   215,   215,   216,   217,   217,
     217,   217,   217,   217,   218,   218,   218,   218,   220,   219,
     219,   219,   221,   221,   221,   221,   221,   222,   222,   222,
     222,   223,   223,   225,   226,   224,   227,   228,   228,   229,
     229,   230,   230,   231,   231,   232,   232,   233,   232,   234,
     234,   235,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   237,   238,   239,   239,   240,   239,   239,   239,   239,
     239,   239,   239,   241,   239,   239,   239,   242,   243,   242,
     242,   242,   242,   244,   244,   245,   246,   246,   246,   246,
     246,   247,   248,   248,   249,   249,   250,   251,   251,   252,
     252,   252,   253,   254,   255,   256,   257,   258,   259
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     5,     0,     5,     3,
       1,     1,     3,     3,     5,     5,     2,     2,     2,     2,
       0,     3,     0,     4,     0,     8,     0,     2,     4,     4,
       0,     2,     2,     1,     2,     1,     0,     3,     0,     3,
       1,     2,     2,     1,     0,     4,     0,     6,     0,     3,
       3,     5,     3,     4,     3,     1,     1,     1,     3,     2,
       2,     0,     1,     1,     1,     0,     6,     2,     1,     0,
       5,     4,     3,     1,     1,     0,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     0,
       0,     5,     1,     1,     3,     3,     1,     1,     1,     3,
       2,     1,     1,     1,     1,     2,     1,     1,     1,     0,
       2,     3,     0,     6,     0,     7,     6,     0,    10,     0,
      10,     0,     3,     0,     4,     4,     4,     4,     2,     4,
       4,     0,     2,     0,     2,     3,     3,     5,     3,     1,
       1,     2,     3,     2,     2,     1,     0,     0,     5,     0,
       3,     0,     4,     0,     6,     0,     5,     0,     0,     5,
       0,     6,     2,     3,     1,     1,     1,     0,     4,     0,
       6,     0,     6,     0,     7,     0,     7,     0,     5,     0,
       5,     0,     5,     0,     5,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     0,     4,     1,     2,     1,
       3,     3,     3,     3,     3,     3,     1,     1,     3,     3,
       2,     2,     2,     1,     3,     3,     3,     1,     0,     3,
       2,     1,     3,     4,     5,     7,     1,     5,     4,     5,
       7,     3,     4,     0,     0,     8,     1,     3,     1,     1,
       1,     3,     3,     3,     1,     3,     2,     0,     3,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     4,     3,     3,     0,     3,     4,     4,     2,
       2,     2,     2,     0,     3,     4,     1,     3,     0,     3,
       2,     1,     1,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
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
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
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

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
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
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
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
  return 0;
}
#endif /* YYERROR_VERBOSE */

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




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 11:
#line 216 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].integer) > 1) {
				for(int i=0; i<(yyvsp[0].integer); i++)
					g_op->pop_stack();
			}
			else {
				g_op->fast_pop_stack();
			}
		}
#line 2099 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 232 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->fast_pop_stack();
		}
#line 2107 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 236 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->fast_pop_stack();
		}
#line 2115 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 249 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->channel_in_start();
		}
#line 2123 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 253 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->channel_in_end((yyvsp[-1].integer));
		}
#line 2131 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 257 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->channel_out_start();
		}
#line 2139 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 261 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->channel_out_end((yyvsp[-1].integer));
		}
#line 2147 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 268 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[-2].integer) + 1;
		}
#line 2155 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 272 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = 1;
		}
#line 2163 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 279 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->assign_local((yyvsp[0].cp));
		}
#line 2171 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 283 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->assign_member((yyvsp[0].cp));
		}
#line 2179 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 287 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->assign_reserved((yyvsp[0].integer));
		}
#line 2187 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 291 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->assign_list(false);
		}
#line 2195 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 295 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->assign_list(true);
		}
#line 2203 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 299 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->assign_member((yyvsp[0].cp));
		}
#line 2212 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 304 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->assign_reserved((yyvsp[0].integer));
		}
#line 2221 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 309 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->assign_member((yyvsp[0].cp));
		}
#line 2230 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 314 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->assign_reserved((yyvsp[0].integer));
		}
#line 2239 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 322 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->do_scope_start();
		}
#line 2247 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 326 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->do_scope_end();
		}
#line 2255 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 334 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->parallel_start();
		}
#line 2263 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 338 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->parallel_end();
		}
#line 2271 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 342 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->parallel_for_start((yyvsp[-3].cp));
		}
#line 2279 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 346 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->parallel_for_end();
		}
#line 2287 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 353 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_integer(0);	// by
			g_op->push_integer(1);	// per
		}
#line 2296 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 358 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			int opt = 0;
			if (strncmp((yyvsp[-1].cp), "by", 2) == 0) {
				g_op->push_integer(1);
			}
			else if (strncmp((yyvsp[-1].cp), "per", 3) == 0) {
				g_op->push_integer(0);
				g_op->rotate();
			}
			else {
				yyerror("parallel option 'by' or 'per' expected");
			}
		}
#line 2314 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 372 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if (strncmp((yyvsp[-3].cp), "by", 2) != 0) {
				yyerror("parallel option 'by' expected");
			}

			if (strncmp((yyvsp[-1].cp), "per", 3) != 0) {
				yyerror("parallel option 'per' expected");
			}
		}
#line 2328 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 386 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->call((yyvsp[-1].integer));
		}
#line 2336 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 393 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_ROOT);
			g_op->find_member("os");
			g_op->find_member("run");
		}
#line 2346 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 399 "../src/parser/parser.y" /* yacc.c:1646  */
    {	
			g_op->call(1);
		}
#line 2354 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 408 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_string((yyvsp[0].cp));
		}
#line 2362 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 416 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->pop();
		}
#line 2370 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 425 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->push();
		}
#line 2378 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 429 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->goto_end();
		}
#line 2386 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 437 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->do_finally();
		}
#line 2394 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 441 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->goto_end();
		}
#line 2402 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 461 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->catch_start((yyvsp[0].cp));
		}
#line 2410 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 465 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->goto_finally();
		}
#line 2418 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 469 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vp = (name_list_t*)(yyvsp[0].vector_cp);
			g_ex->catch_start((yyvsp[-2].cp), vp);
		}
#line 2427 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 474 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->goto_finally();
		}
#line 2435 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 478 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->catch_start(NULL);
		}
#line 2443 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 482 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->goto_finally();
		}
#line 2451 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 490 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->do_throw((yyvsp[-1].cp), 0);
		}
#line 2459 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 494 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ex->do_throw((yyvsp[-3].cp), (yyvsp[-1].integer));
		}
#line 2467 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 502 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			code_top->using_object((yyvsp[-1].cp), NULL);
		}
#line 2475 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 506 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			code_top->using_object((yyvsp[-2].cp), (yyvsp[-1].cp));
		}
#line 2483 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 514 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			char buff[1024];
			sprintf(buff, "%s.%s", (yyvsp[-2].cp), (yyvsp[0].cp));
			(yyval.cp) = g_parser->strdup(buff);
		}
#line 2493 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 520 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = (yyvsp[0].cp);
		}
#line 2501 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 528 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->dump_stack();
		}
#line 2509 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 532 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->dump_local();
		}
#line 2517 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 540 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->do_return((yyvsp[-1].integer));
		}
#line 2525 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 544 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->do_continue();
		}
#line 2533 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 548 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->do_break();
		}
#line 2541 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 556 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = 0;
		}
#line 2549 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 560 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[0].integer);
		}
#line 2557 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 574 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_start();
		}
#line 2565 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 578 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_end();
		}
#line 2573 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 592 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_parse->set_current_bnf((yyvsp[0].bp));
		}
#line 2581 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 596 "../src/parser/parser.y" /* yacc.c:1646  */
    {

		}
#line 2589 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 600 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			bnf* b = (yyvsp[-1].bp);
			b->type = BNF_WS;
		}
#line 2598 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 620 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_bnf_right_num = 1;
			g_parse->current_bnf()->add_rule();
		}
#line 2607 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 635 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_bnf_right_num++;
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[0].bp));
		}
#line 2616 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 640 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[0].bp));
		}
#line 2624 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 655 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[0].cp));
		}
#line 2632 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 659 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[0].cp), true);
		}
#line 2640 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 667 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			string name = "`\a";
			name += (yyvsp[0].cp);
			(yyval.bp) = g_parse->get_nonterm_bnf(name);
		}
#line 2650 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 677 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.bp) = g_parse->get_action_bnf(g_bnf_right_num);
		}
#line 2658 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 690 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_pattern_start();
		}
#line 2666 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 694 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_pattern_shift();
		}
#line 2674 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 698 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_pattern_end();
		}
#line 2682 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 712 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_cut_list((yyvsp[-2].cp), (yyvsp[0].cp));
		}
#line 2690 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 720 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[-2].integer) + 1;
		}
#line 2698 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 724 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = 1;
		}
#line 2706 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 732 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_match_expr();
		}
#line 2714 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 736 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_shift((yyvsp[0].cp));
		}
#line 2722 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 740 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_match_and_assign((yyvsp[-2].cp));
		}
#line 2730 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 748 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = (yyvsp[0].cp);
		}
#line 2738 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 764 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = BIT_DEFINE_STATIC;
		}
#line 2746 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 768 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = 0;
		}
#line 2754 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 776 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = (yyvsp[0].cp);
		}
#line 2762 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 780 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = (yyvsp[0].cp);
		}
#line 2770 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 788 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = NULL;
		}
#line 2778 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 792 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = (yyvsp[0].cp);
		}
#line 2786 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 799 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			code_top->reg_object((yyvsp[-1].cp), (yyvsp[-2].integer));
		}
#line 2794 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 803 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			code_top->reg_object((yyvsp[-1].cp), (yyvsp[-2].integer));
			code_top->init_object_start((yyvsp[-1].cp));

			g_op->push_reserved(OP_PUSH_MY);
		}
#line 2805 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 810 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->assign_member((yyvsp[-4].cp));
			g_op->pop_stack();
			code_top->init_object_done();
		}
#line 2815 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 816 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vp = (name_list_t*)(yyvsp[-2].vector_cp);

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			parserCode::push_code_stack((yyvsp[-3].cp), vp, (yyvsp[-4].integer), (yyvsp[0].cp));

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}

			if ((yyvsp[-1].integer)) {
				code_top->make_super((yyvsp[-1].integer));
			}
		}
#line 2845 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 842 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			parserCode::pop_code_stack();
		}
#line 2853 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 846 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			const char* cp = get_context();
			print("get_context(): '%s'\n", cp);
			code_top->do_context((yyvsp[-3].cp), (yyvsp[-2].cp), cp);
			//TODO: fail check
		}
#line 2864 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 853 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vp = (name_list_t*)(yyvsp[-1].vector_cp);

			// check argv
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				yyerror("argv not allowed in parse object");
			}

			if (vp == NULL) {
				yyerror("at least 1 argument needed in parse object");
			}

			parserCode::push_code_stack((yyvsp[-2].cp), vp, (yyvsp[-5].integer), (yyvsp[0].cp));
			g_parse->do_parse_init();
		}
#line 2884 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 869 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			vector<char>& def = parserCode::get_def();

			g_parse->make_table();
			//g_parse->dump();
			g_parse->do_parse(def);
			g_parse->cleanup();

			parserCode::pop_code_stack();
		}
#line 2899 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 880 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vp = (name_list_t*)(yyvsp[-1].vector_cp);

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			parserCode::push_code_stack((yyvsp[-2].cp), vp, (yyvsp[-5].integer), (yyvsp[0].cp));

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}
			
			g_ctl->decode_func_start();
		}
#line 2927 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 904 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();
		}
#line 2936 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 913 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->once_start();
		}
#line 2944 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 917 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->once_end();
		}
#line 2952 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 925 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].integer)) {
				code_top->make_super((yyvsp[0].integer));
			}
		}
#line 2962 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 931 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			parserCode::pop_code_stack();
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[-3].cp));
		}
#line 2972 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 937 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			// for serial tagging
			static int count = 1;
			char name[256];
			sprintf(name, "__%s_%d_context", g_parser->module_name.c_str(), count++);

			const char* cp = get_context();
			//print("get_context(): '%s'\n", cp);
			code_top->do_context((yyvsp[-1].cp), name, cp);
			//TODO: fail check

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member(name);
		}
#line 2991 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 952 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[-3].cp));
		}
#line 3003 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 960 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			vector<char>& def = parserCode::get_def();

			g_parse->make_table();
			//g_parse->dump();
			g_parse->do_parse(def);
			g_parse->cleanup();

			parserCode::pop_code_stack();

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[-3].cp));
		}
#line 3021 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 978 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vp = (name_list_t*)(yyvsp[0].vector_cp);

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
			const char* name = g_parser->strdup(buff);
			parserCode::push_code_stack(name, vp, 0);

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}

			(yyval.cp) = name;
		}
#line 3053 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 1010 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vp = (name_list_t*)(yyvsp[0].vector_cp);

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
			sprintf(buff, "#%d_decode_lambda", count++);
			const char* name = g_parser->strdup(buff);
			parserCode::push_code_stack(name, vp, 0);

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}
			
			g_ctl->decode_func_start();

			(yyval.cp) = name;
		}
#line 3087 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 1044 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vp = (name_list_t*)(yyvsp[0].vector_cp);

			// check argv
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				yyerror("argv not allowed in parse object");
			}

			if (vp == NULL) {
				yyerror("at least 1 argument needed in parse object");
			}

			static int count = 1;
			char buff[256];
			sprintf(buff, "#%d_parse_lambda", count++);
			const char* name = g_parser->strdup(buff);
			parserCode::push_code_stack(name, vp);
			g_parse->do_parse_init();

			(yyval.cp) = name;
		}
#line 3113 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1070 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = 0;
		}
#line 3121 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 1074 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[0].integer);
		}
#line 3129 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1082 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.vector_cp) = 0;
		}
#line 3137 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1086 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.vector_cp) = 0;
		}
#line 3145 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1090 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vs = g_parser->new_name_list();
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
#line 3155 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1096 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.vector_cp) = (yyvsp[-1].vector_cp);
		}
#line 3163 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1100 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vs = (name_list_t*)(yyvsp[-3].vector_cp);
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
#line 3173 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1110 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vs = (name_list_t*)(yyvsp[-2].vector_cp);
			vs->push_back((yyvsp[0].cp));
			(yyval.vector_cp) = vs;
		}
#line 3183 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1116 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			name_list_t* vs = g_parser->new_name_list();
			vs->push_back((yyvsp[0].cp));
			(yyval.vector_cp) = vs;
		}
#line 3193 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 1126 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->if_end();
		}
#line 3201 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 1130 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->else_end();
		}
#line 3209 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 1134 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->else_end();
			for(int i=0; i<(yyvsp[-1].integer); i++)
				g_ctl->else_end();
		}
#line 3219 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 1140 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->if_end();
			for(int i=0; i<(yyvsp[0].integer); i++)
				g_ctl->else_end();
		}
#line 3229 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 1150 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[-1].integer) + 1;
		}
#line 3237 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 1154 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = 1;
		}
#line 3245 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 1162 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->else_start();
		}
#line 3253 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 1166 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->if_start();
		}
#line 3261 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 1175 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->else_start();
		}
#line 3269 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 1184 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->if_start();
		}
#line 3277 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 1193 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->do_start();
		}
#line 3285 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 1197 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->do_end();
		}
#line 3293 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 1205 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->times_start();
		}
#line 3301 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 1209 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->times_end();
		}
#line 3309 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 1217 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->while_start_1();
		}
#line 3317 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 1221 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->while_start_2();
		}
#line 3325 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 1225 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->while_end();
		}
#line 3333 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 1233 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->for_start((yyvsp[-2].cp));
		}
#line 3341 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 1237 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->for_end();
		}
#line 3349 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 1245 "../src/parser/parser.y" /* yacc.c:1646  */
    { 
			(yyval.integer) = (yyvsp[-1].integer); 
		}
#line 3357 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 1253 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[-2].integer) + 1;
		}
#line 3365 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 1257 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = 1;
		}
#line 3373 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 1272 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].integer) != '=') {
				g_op->push_lvar((yyvsp[-1].cp));
			}
		}
#line 3383 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 1278 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			switch ((yyvsp[-2].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_local((yyvsp[-3].cp));
		}
#line 3399 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 1290 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->clear_last_find_position();
			if ((yyvsp[0].integer) != '=') {
				g_op->dup();
				g_op->find_member((yyvsp[-1].cp));
			}
		}
#line 3411 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 1298 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			switch ((yyvsp[-2].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((yyvsp[-3].cp));
		}
#line 3427 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 1310 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].integer) != '=') {
				g_op->dup();
				g_op->find_reserved((yyvsp[-1].integer));
			}
		}
#line 3438 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 1317 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			switch ((yyvsp[-2].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((yyvsp[-3].integer));
		}
#line 3454 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 1329 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(false);
			}
		}
#line 3466 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 1337 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			switch ((yyvsp[-2].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			if ((yyvsp[-2].integer) != '=') {
				g_op->do_rc_dec();
			}

			g_op->assign_list(false);
		}
#line 3486 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 1353 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if ((yyvsp[0].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(true);
			}
		}
#line 3498 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 1361 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			switch ((yyvsp[-2].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			if ((yyvsp[-2].integer) != '=') {
				g_op->do_rc_dec();
			}

			g_op->assign_list(true);
		}
#line 3518 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 1377 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[0].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[-1].cp));
			}
		}
#line 3531 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 1386 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			switch ((yyvsp[-2].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((yyvsp[-3].cp));
		}
#line 3547 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 1398 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[0].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[-1].integer));
			}
		}
#line 3560 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 1407 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			switch ((yyvsp[-2].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((yyvsp[-3].integer));
		}
#line 3576 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 1419 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[0].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[-1].cp));
			}
		}
#line 3589 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 1428 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			switch ((yyvsp[-2].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((yyvsp[-3].cp));
		}
#line 3605 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 1440 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[0].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[-1].integer));
			}
		}
#line 3618 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 1449 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			switch ((yyvsp[-2].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((yyvsp[-3].integer));
		}
#line 3634 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 1466 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = '='; 
		}
#line 3642 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 1470 "../src/parser/parser.y" /* yacc.c:1646  */
    { 
			(yyval.integer) = '+'; 
		}
#line 3650 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 1474 "../src/parser/parser.y" /* yacc.c:1646  */
    { 
			(yyval.integer) = '-'; 
		}
#line 3658 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 1478 "../src/parser/parser.y" /* yacc.c:1646  */
    { 
			(yyval.integer) = '*'; 
		}
#line 3666 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 1482 "../src/parser/parser.y" /* yacc.c:1646  */
    { 
			(yyval.integer) = '/'; 
		}
#line 3674 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 1495 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->dup();
			g_ctl->if_start(false);
		}
#line 3683 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 1500 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->do_or();
			g_ctl->if_end();
		}
#line 3692 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 1510 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->dup();
			g_ctl->if_start();
		}
#line 3701 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 1515 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->do_and();
			g_ctl->if_end();
		}
#line 3710 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 1525 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->do_not();
		}
#line 3718 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 1534 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->gt();
		}
#line 3726 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 1538 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->ge();
		}
#line 3734 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 1542 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->lt();
		}
#line 3742 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 1546 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->le();
		}
#line 3750 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 1550 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->eq();
		}
#line 3758 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 1554 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->neq();
		}
#line 3766 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 1569 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->add();
		}
#line 3774 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 1573 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->sub();
		}
#line 3782 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 1577 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_integer((yyvsp[0].integer));
			g_op->add();
		}
#line 3791 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 1582 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_bignum('-', (yyvsp[0].cp));
			g_op->add();
		}
#line 3800 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 1587 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_real((yyvsp[0].real));
			g_op->add();
		}
#line 3809 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 1597 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->mul();
		}
#line 3817 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 1601 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->div();
		}
#line 3825 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 1605 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->mod();
		}
#line 3833 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 1614 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			unary_minus = true;
		}
#line 3841 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 1618 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if (unary_minus)
				g_op->minus();

			unary_minus = false;
		}
#line 3852 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 1631 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_list((yyvsp[-1].integer));
		}
#line 3860 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 1635 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_list((yyvsp[-2].integer));
		}
#line 3868 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 1639 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_list(-2);
		}
#line 3876 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 1643 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_list(-3);
		}
#line 3884 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 1652 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_tuple((yyvsp[-3].integer) + 1);
		}
#line 3892 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 1656 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_tuple((yyvsp[-2].integer));
		}
#line 3900 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 1660 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_tuple(-2);
		}
#line 3908 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 1664 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_tuple(-3);
		}
#line 3916 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 1672 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_map((yyvsp[-1].integer));
		}
#line 3924 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 1676 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_map((yyvsp[-2].integer));
		}
#line 3932 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 1684 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		}
#line 3941 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 254:
#line 1689 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->sbf_rule_start();
		}
#line 3949 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 1693 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->sbf_end();
			g_lvar_nil_check++;
		}
#line 3958 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 1713 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->sbf_rule();
		}
#line 3966 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 1717 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->sbf_in();
		}
#line 3974 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 1725 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->sbf_list_gen((yyvsp[-2].cp));
		}
#line 3982 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 1729 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_ctl->sbf_range_gen((yyvsp[-2].cp));
		}
#line 3990 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 1738 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_integer(1);
		}
#line 3998 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 1747 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_nil();
		}
#line 4006 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 1751 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_nil();
		}
#line 4014 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 1760 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[-2].integer) + 1;
		}
#line 4022 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 1764 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = 1;
		}
#line 4030 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 1781 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if (g_op->check_lvar((yyvsp[0].cp)) == false) {
				string msg = "variable ";
				msg += (yyvsp[0].cp);
				msg += " is not defined";
				yyerror(msg.c_str());
			}

			g_op->push_lvar((yyvsp[0].cp));
		}
#line 4045 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 1792 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_integer((yyvsp[0].integer));
		}
#line 4053 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 1796 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_integer((yyvsp[0].integer));
		}
#line 4061 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 279:
#line 1800 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_bignum('+', (yyvsp[0].cp));
		}
#line 4069 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 280:
#line 1804 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_bignum('-', (yyvsp[0].cp));
		}
#line 4077 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 281:
#line 1808 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_real((yyvsp[0].real));
		}
#line 4085 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 282:
#line 1812 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_real((yyvsp[0].real));
		}
#line 4093 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 283:
#line 1816 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_regex();
		}
#line 4101 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 284:
#line 1820 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			// already in stack
		}
#line 4109 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 285:
#line 1824 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved((yyvsp[0].integer));
		}
#line 4117 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 286:
#line 1828 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_boolean(true);
		}
#line 4125 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 287:
#line 1832 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_boolean(false);
		}
#line 4133 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 288:
#line 1836 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_nil();
		}
#line 4141 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 292:
#line 1851 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->eval();
		}
#line 4149 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 293:
#line 1858 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->set_last_find_position();
			g_op->find_member((yyvsp[0].cp));
		}
#line 4158 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 294:
#line 1863 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->find_reserved((yyvsp[0].integer));
		}
#line 4166 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 295:
#line 1867 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->clear_last_find_position();
		}
#line 4174 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 296:
#line 1871 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->call((yyvsp[0].integer));
		}
#line 4182 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 297:
#line 1875 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->listat(false);
		}
#line 4190 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 298:
#line 1879 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->listat(true);
		}
#line 4198 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 299:
#line 1883 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_member((yyvsp[0].cp));
		}
#line 4207 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 300:
#line 1888 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_reserved((yyvsp[0].integer));
		}
#line 4216 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 301:
#line 1893 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[0].cp));
		}
#line 4225 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 302:
#line 1898 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_reserved((yyvsp[0].integer));
		}
#line 4234 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 303:
#line 1903 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			if (g_op->push_mvar_using_space((yyvsp[0].cp)) == false) {
				yyerror("invalid object name in name'string' format");
			}
		}
#line 4244 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 304:
#line 1909 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->clone(1);
		}
#line 4252 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 305:
#line 1913 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->clone((yyvsp[0].integer));

			// this is not normal function call (virtual function call)
			// so it should mark that don't fast popping
			g_op->disable_fast_pop();
		}
#line 4264 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 307:
#line 1926 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_pair();
		}
#line 4272 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 308:
#line 1930 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_integer(0);
		}
#line 4280 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 309:
#line 1934 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->make_pair();
		}
#line 4288 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 310:
#line 1938 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
#line 4297 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 311:
#line 1943 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_integer(0);
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
#line 4307 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 313:
#line 1954 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = 0;
		}
#line 4315 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 314:
#line 1958 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[-1].integer);
		}
#line 4323 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 315:
#line 1966 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->fix_last_find_position();
		}
#line 4331 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 316:
#line 1974 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = OP_PUSH_OWNER;
		}
#line 4339 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 317:
#line 1978 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = OP_PUSH_CALLER;
		}
#line 4347 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 318:
#line 1982 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = OP_PUSH_ROOT;
		}
#line 4355 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 319:
#line 1986 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = OP_PUSH_MODULE;
		}
#line 4363 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 320:
#line 1990 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = OP_PUSH_MY;
		}
#line 4371 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 321:
#line 1998 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = (yyvsp[0].cp);
		}
#line 4379 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 323:
#line 2007 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_string((yyvsp[0].cp));
		}
#line 4387 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 325:
#line 2016 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_string((yyvsp[0].cp));
		}
#line 4395 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 326:
#line 2024 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->add();

			g_op->push_string((yyvsp[0].cp));

			g_op->add();
		}
#line 4407 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 327:
#line 2036 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_string((yyvsp[0].cp));
		}
#line 4415 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 329:
#line 2045 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_string((yyvsp[0].cp));
		}
#line 4423 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 331:
#line 2050 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			g_op->push_string((yyvsp[0].cp));
		}
#line 4431 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 332:
#line 2058 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = (yyvsp[0].cp);
		}
#line 4439 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 333:
#line 2066 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[0].integer);
		}
#line 4447 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 334:
#line 2074 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.integer) = (yyvsp[0].integer);
		}
#line 4455 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 335:
#line 2082 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = (yyvsp[0].cp);
		}
#line 4463 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 336:
#line 2090 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.cp) = (yyvsp[0].cp);
		}
#line 4471 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 337:
#line 2098 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.real) = (yyvsp[0].real);
		}
#line 4479 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;

  case 338:
#line 2106 "../src/parser/parser.y" /* yacc.c:1646  */
    {
			(yyval.real) = (yyvsp[0].real);
		}
#line 4487 "../src/parser/parser.cpp" /* yacc.c:1646  */
    break;


#line 4491 "../src/parser/parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2112 "../src/parser/parser.y" /* yacc.c:1906  */



