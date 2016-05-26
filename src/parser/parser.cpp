
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 11 "./src/parser/parser.y"

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



/* Line 189 of yacc.c  */
#line 108 "./src/parser/parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     LAMBDA = 306,
     PURE = 307,
     NIL_ = 308,
     RIGHT_ARROW = 309,
     LEFT_ARROW = 310,
     PARALLEL = 311,
     ASSIGNMENT = 312,
     ONCE = 313,
     NAME = 314,
     STRING = 315,
     FORMAT_STRING_HEAD = 316,
     FORMAT_STRING_TAIL = 317,
     RE_STRING = 318,
     RE_FORMAT_STRING_HEAD = 319,
     HEX_STRING = 320,
     SHELL_STRING_HEAD = 321,
     CONTEXT = 322,
     NUMBER = 323,
     MINUS_NUMBER = 324,
     BIG_NUMBER = 325,
     MINUS_BIG_NUMBER = 326,
     REAL = 327,
     MINUS_REAL = 328
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 46 "./src/parser/parser.y"

	const char* cp;
	int integer;
	double real;
	void* vector_cp;	
	struct bnf* bp;	
	struct cp2_t cp2; 
	struct int2_t int2;



/* Line 214 of yacc.c  */
#line 229 "./src/parser/parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 241 "./src/parser/parser.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  160
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1923

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  160
/* YYNRULES -- Number of rules.  */
#define YYNRULES  317
/* YYNRULES -- Number of states.  */
#define YYNSTATES  506

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    88,     2,     2,    93,    83,     2,     2,
      84,    85,    91,    89,    78,    90,    79,    92,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    77,    76,
       2,    82,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    86,     2,    87,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    81,    75,    80,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    11,    13,    15,    19,    22,
      25,    27,    29,    31,    33,    35,    37,    39,    41,    43,
      45,    47,    49,    51,    53,    55,    56,    60,    61,    66,
      67,    77,    78,    81,    86,    91,    92,    95,    98,   100,
     103,   105,   106,   110,   111,   115,   117,   120,   123,   125,
     126,   131,   132,   139,   140,   144,   148,   154,   158,   163,
     167,   169,   171,   173,   177,   180,   183,   184,   186,   188,
     190,   191,   198,   199,   208,   211,   213,   214,   220,   225,
     229,   231,   233,   234,   237,   239,   242,   244,   246,   248,
     250,   252,   254,   256,   258,   261,   263,   264,   265,   271,
     273,   275,   279,   283,   285,   287,   289,   293,   296,   298,
     300,   302,   304,   307,   309,   311,   313,   316,   318,   320,
     322,   326,   327,   334,   335,   340,   341,   348,   349,   353,
     356,   358,   360,   364,   365,   368,   369,   372,   376,   380,
     386,   390,   392,   394,   397,   401,   404,   407,   409,   410,
     411,   418,   419,   424,   425,   431,   432,   439,   440,   446,
     447,   448,   455,   456,   464,   467,   471,   473,   477,   481,
     483,   485,   487,   489,   490,   495,   496,   503,   504,   511,
     512,   520,   521,   529,   530,   536,   537,   543,   544,   550,
     551,   557,   559,   561,   563,   565,   567,   569,   571,   572,
     577,   579,   580,   585,   587,   590,   592,   596,   600,   604,
     608,   612,   616,   618,   620,   624,   628,   631,   634,   637,
     639,   643,   647,   651,   653,   654,   658,   661,   663,   667,
     673,   681,   683,   687,   693,   701,   705,   706,   707,   716,
     718,   722,   724,   726,   728,   732,   736,   740,   742,   746,
     749,   750,   754,   758,   760,   764,   766,   768,   770,   772,
     774,   776,   778,   780,   782,   784,   786,   788,   790,   792,
     794,   796,   800,   804,   808,   809,   813,   818,   823,   826,
     829,   832,   835,   836,   840,   845,   847,   851,   852,   856,
     859,   861,   863,   866,   870,   872,   874,   876,   878,   880,
     882,   884,   887,   889,   892,   894,   899,   901,   903,   905,
     907,   909,   911,   913,   915,   917,   919,   921
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      95,     0,    -1,    95,    99,    -1,    95,    97,    -1,    99,
      -1,    99,    -1,    97,    -1,    74,    95,    75,    -1,    74,
      75,    -1,    95,    75,    -1,    75,    -1,   190,    -1,   125,
      -1,   127,    -1,   154,    -1,   159,    -1,   110,    -1,   122,
      -1,   106,    -1,   107,    -1,   100,    -1,   102,    -1,   130,
      -1,   124,    -1,    76,    -1,    -1,   193,   101,    97,    -1,
      -1,    56,    16,   103,    96,    -1,    -1,    56,    22,   241,
      23,   239,   105,    77,   104,    96,    -1,    -1,    59,   193,
      -1,    59,   193,    59,   193,    -1,   239,    77,   191,    76,
      -1,    -1,   108,   109,    -1,   109,   244,    -1,    66,    -1,
     111,   113,    -1,   121,    -1,    -1,    35,   112,    97,    -1,
      -1,   116,   114,   115,    -1,   116,    -1,    37,    97,    -1,
     116,   117,    -1,   117,    -1,    -1,    36,   123,   118,    97,
      -1,    -1,    36,   123,    77,   171,   119,    97,    -1,    -1,
      36,   120,    97,    -1,    38,   123,    76,    -1,    38,   123,
      78,   191,    76,    -1,    42,   123,    76,    -1,    42,   123,
      60,    76,    -1,   123,    79,   158,    -1,   158,    -1,    40,
      -1,    41,    -1,    24,   126,    76,    -1,    25,    76,    -1,
      26,    76,    -1,    -1,   191,    -1,   172,    -1,   128,    -1,
      -1,    20,   193,   129,    74,   145,    75,    -1,    -1,    21,
       5,   158,   170,   131,    74,   132,    75,    -1,   132,   133,
      -1,   133,    -1,    -1,   136,   134,    77,   135,    76,    -1,
      80,    77,   142,    76,    -1,   135,    81,   137,    -1,   137,
      -1,   143,    -1,    -1,   138,   139,    -1,   140,    -1,   140,
     141,    -1,   141,    -1,   142,    -1,   143,    -1,   144,    -1,
      60,    -1,    63,    -1,   247,    -1,   165,    -1,   145,   146,
      -1,   146,    -1,    -1,    -1,   147,   149,    54,   148,    96,
      -1,   151,    -1,   150,    -1,   153,    77,   153,    -1,   151,
      78,   152,    -1,   152,    -1,   193,    -1,   153,    -1,   153,
      82,   193,    -1,    83,   241,    -1,   188,    -1,   181,    -1,
     185,    -1,   183,    -1,   155,   156,    -1,   156,    -1,     4,
      -1,    52,    -1,   155,     5,    -1,     5,    -1,   247,    -1,
      60,    -1,   157,   158,    76,    -1,    -1,   157,   158,    57,
     160,   193,    76,    -1,    -1,   168,   169,   161,    97,    -1,
      -1,    20,   168,   162,    74,   145,    75,    -1,    -1,    58,
     164,    98,    -1,   166,    98,    -1,    51,    -1,    67,    -1,
     157,   158,   170,    -1,    -1,    77,   191,    -1,    -1,    84,
      85,    -1,    84,    46,    85,    -1,    84,   171,    85,    -1,
      84,   171,    78,    46,    85,    -1,   171,    78,   247,    -1,
     247,    -1,   179,    -1,   179,   177,    -1,   179,   173,   177,
      -1,   179,   173,    -1,   173,   174,    -1,   174,    -1,    -1,
      -1,    14,   175,   205,    77,   176,    96,    -1,    -1,    15,
      77,   178,    96,    -1,    -1,    13,   205,    77,   180,    96,
      -1,    -1,    16,   182,    96,    17,   205,    76,    -1,    -1,
     193,    18,    16,   184,    96,    -1,    -1,    -1,    17,   186,
     205,    77,   187,    96,    -1,    -1,    22,   241,    23,   239,
      77,   189,    96,    -1,   191,    76,    -1,   191,    78,   193,
      -1,   193,    -1,   192,    78,   193,    -1,   193,    78,   193,
      -1,   194,    -1,   165,    -1,   167,    -1,   163,    -1,    -1,
     241,   204,   195,   193,    -1,    -1,   233,    79,   158,   204,
     196,   193,    -1,    -1,   233,    79,   240,   204,   197,   193,
      -1,    -1,   233,    86,   236,    87,   204,   198,   193,    -1,
      -1,   233,    86,   236,    85,   204,   199,   193,    -1,    -1,
      45,   158,   204,   200,   193,    -1,    -1,    45,   240,   204,
     201,   193,    -1,    -1,    79,   158,   204,   202,   193,    -1,
      -1,    79,   240,   204,   203,   193,    -1,   205,    -1,    82,
      -1,    47,    -1,    48,    -1,    49,    -1,    50,    -1,   206,
      -1,    -1,   206,    30,   207,   208,    -1,   208,    -1,    -1,
     208,    29,   209,   210,    -1,   210,    -1,    88,   211,    -1,
     211,    -1,   212,    31,   212,    -1,   212,    32,   212,    -1,
     212,    33,   212,    -1,   212,    34,   212,    -1,   212,    27,
     212,    -1,   212,    28,   212,    -1,   212,    -1,   213,    -1,
     213,    89,   214,    -1,   213,    90,   214,    -1,   213,   248,
      -1,   213,   250,    -1,   213,   253,    -1,   214,    -1,   214,
      91,   239,    -1,   214,    92,   239,    -1,   214,    83,   239,
      -1,   215,    -1,    -1,    90,   216,   239,    -1,    89,   239,
      -1,   239,    -1,    86,   126,    87,    -1,    86,   193,    45,
     193,    87,    -1,    86,   193,    45,   193,    77,   193,    87,
      -1,   220,    -1,    84,   192,    85,    -1,    84,   193,    45,
     193,    85,    -1,    84,   193,    45,   193,    77,   193,    85,
      -1,    74,   230,    75,    -1,    -1,    -1,    83,    86,   221,
     223,    81,   222,   224,    87,    -1,   193,    -1,   224,    78,
     225,    -1,   225,    -1,   205,    -1,   226,    -1,   241,    55,
     193,    -1,   241,    55,   227,    -1,   228,    77,   193,    -1,
     228,    -1,   193,    80,   193,    -1,   193,    80,    -1,    -1,
      80,   229,   193,    -1,   230,    78,   231,    -1,   231,    -1,
     193,    77,   193,    -1,   217,    -1,   218,    -1,   219,    -1,
     241,    -1,   249,    -1,   248,    -1,   251,    -1,   250,    -1,
     252,    -1,   253,    -1,   245,    -1,   246,    -1,   240,    -1,
      43,    -1,    44,    -1,    53,    -1,    84,   193,    85,    -1,
     233,    79,   158,    -1,   233,    79,   240,    -1,    -1,   233,
     234,   238,    -1,   233,    86,   236,    87,    -1,   233,    86,
     236,    85,    -1,    45,   158,    -1,    45,   240,    -1,    79,
     158,    -1,    79,   240,    -1,    -1,   247,   235,   246,    -1,
     233,    79,     6,   238,    -1,   232,    -1,   193,    77,   193,
      -1,    -1,    77,   237,   193,    -1,   193,    77,    -1,    77,
      -1,   193,    -1,    84,    85,    -1,    84,   191,    85,    -1,
     233,    -1,     8,    -1,     9,    -1,    10,    -1,    11,    -1,
       7,    -1,   247,    -1,   242,   244,    -1,    61,    -1,   243,
     244,    -1,    64,    -1,    93,    74,   193,    62,    -1,    63,
      -1,   243,    -1,    60,    -1,   242,    -1,    65,    -1,    59,
      -1,    69,    -1,    68,    -1,    71,    -1,    70,    -1,    72,
      -1,    73,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   182,   182,   183,   184,   189,   190,   195,   196,   201,
     202,   207,   217,   218,   219,   220,   221,   222,   223,   227,
     231,   232,   233,   234,   235,   241,   240,   253,   252,   261,
     260,   272,   276,   290,   304,   312,   312,   325,   326,   334,
     338,   344,   343,   356,   355,   363,   368,   373,   374,   380,
     379,   388,   387,   397,   396,   408,   412,   420,   424,   432,
     438,   446,   450,   458,   462,   466,   475,   478,   486,   487,
     493,   492,   505,   504,   535,   536,   542,   541,   549,   559,
     560,   565,   570,   570,   579,   584,   589,   597,   598,   599,
     604,   608,   616,   626,   634,   635,   640,   644,   640,   655,
     656,   661,   669,   673,   681,   685,   689,   697,   705,   706,
     707,   708,   713,   717,   725,   729,   737,   741,   749,   753,
     761,   766,   765,   779,   778,   789,   788,   803,   802,   814,
     824,   841,   850,   877,   880,   889,   892,   896,   902,   906,
     916,   922,   932,   936,   940,   946,   956,   960,   969,   973,
     968,   982,   981,   991,   990,  1000,   999,  1012,  1011,  1024,
    1028,  1023,  1040,  1039,  1051,  1059,  1063,  1071,  1075,  1083,
    1084,  1085,  1086,  1092,  1091,  1110,  1109,  1130,  1129,  1149,
    1148,  1173,  1172,  1197,  1196,  1218,  1217,  1239,  1238,  1260,
    1259,  1280,  1285,  1289,  1293,  1297,  1301,  1309,  1315,  1314,
    1324,  1330,  1329,  1339,  1344,  1348,  1353,  1357,  1361,  1365,
    1369,  1373,  1377,  1382,  1387,  1391,  1395,  1400,  1405,  1410,
    1415,  1419,  1423,  1427,  1433,  1432,  1443,  1444,  1449,  1453,
    1457,  1461,  1466,  1470,  1474,  1482,  1491,  1496,  1490,  1508,
    1513,  1514,  1519,  1523,  1531,  1535,  1543,  1544,  1551,  1552,
    1557,  1556,  1565,  1569,  1577,  1582,  1583,  1584,  1585,  1596,
    1600,  1604,  1608,  1612,  1616,  1620,  1624,  1628,  1632,  1636,
    1640,  1644,  1649,  1654,  1659,  1658,  1666,  1670,  1674,  1679,
    1684,  1689,  1695,  1694,  1704,  1712,  1717,  1722,  1721,  1729,
    1734,  1740,  1745,  1749,  1757,  1765,  1769,  1773,  1777,  1781,
    1789,  1797,  1798,  1806,  1807,  1815,  1827,  1831,  1836,  1840,
    1841,  1849,  1857,  1865,  1873,  1881,  1889,  1897
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "LAMBDA", "PURE", "NIL_",
  "RIGHT_ARROW", "LEFT_ARROW", "PARALLEL", "ASSIGNMENT", "ONCE", "NAME",
  "STRING", "FORMAT_STRING_HEAD", "FORMAT_STRING_TAIL", "RE_STRING",
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
  "$@19", "lambda_expr", "lambda", "context_expr", "define_start",
  "opt_superclass", "opt_argument_list", "name_list", "if_elif_else_stmt",
  "elif_stmt_list", "elif_stmt", "$@20", "$@21", "else_stmt", "$@22",
  "if_stmt", "$@23", "do_stmt", "$@24", "times_stmt", "$@25", "while_stmt",
  "$@26", "$@27", "for_stmt", "$@28", "expression_stmt", "expression_list",
  "tuple_expression_list", "expression", "assign_expr", "$@29", "$@30",
  "$@31", "$@32", "$@33", "$@34", "$@35", "$@36", "$@37", "assign_type",
  "bool_expr", "or_expr", "$@38", "and_expr", "$@39", "not_expr",
  "logical_expr", "numeric_expr", "add_expr", "mul_expr", "unary_expr",
  "$@40", "list", "tuple", "map", "sbf", "$@41", "$@42", "sbf_result",
  "sbf_rule_list", "sbf_rule", "in_expr", "range_expr", "range_expr_sub",
  "$@43", "pair_list", "pair_expression", "primary_object",
  "postfix_object", "$@44", "$@45", "slice_expression", "$@46",
  "calling_body", "object", "reserved_object", "lvar", "format_string",
  "re_format_string", "format_object", "regex", "string", "name",
  "minus_number", "number", "minus_big_number", "big_number", "real",
  "minus_real", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   123,   125,    59,    58,    44,    46,
     126,   124,    61,    37,    40,    41,    91,    93,    33,    43,
      45,    42,    47,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,   101,   100,   103,   102,   104,
     102,   105,   105,   105,   106,   108,   107,   109,   109,   110,
     110,   112,   111,   114,   113,   113,   115,   116,   116,   118,
     117,   119,   117,   120,   117,   121,   121,   122,   122,   123,
     123,   124,   124,   125,   125,   125,   126,   126,   127,   127,
     129,   128,   131,   130,   132,   132,   134,   133,   133,   135,
     135,   136,   138,   137,   139,   140,   140,   141,   141,   141,
     142,   142,   143,   144,   145,   145,   147,   148,   146,   149,
     149,   150,   151,   151,   152,   152,   152,   153,   154,   154,
     154,   154,   155,   155,   156,   156,   157,   157,   158,   158,
     159,   160,   159,   161,   159,   162,   159,   164,   163,   165,
     166,   167,   168,   169,   169,   170,   170,   170,   170,   170,
     171,   171,   172,   172,   172,   172,   173,   173,   175,   176,
     174,   178,   177,   180,   179,   182,   181,   184,   183,   186,
     187,   185,   189,   188,   190,   191,   191,   192,   192,   193,
     193,   193,   193,   195,   194,   196,   194,   197,   194,   198,
     194,   199,   194,   200,   194,   201,   194,   202,   194,   203,
     194,   194,   204,   204,   204,   204,   204,   205,   207,   206,
     206,   209,   208,   208,   210,   210,   211,   211,   211,   211,
     211,   211,   211,   212,   213,   213,   213,   213,   213,   213,
     214,   214,   214,   214,   216,   215,   215,   215,   217,   217,
     217,   217,   218,   218,   218,   219,   221,   222,   220,   223,
     224,   224,   225,   225,   226,   226,   227,   227,   228,   228,
     229,   228,   230,   230,   231,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   233,   233,   234,   233,   233,   233,   233,   233,
     233,   233,   235,   233,   233,   233,   236,   237,   236,   236,
     236,   236,   238,   238,   239,   240,   240,   240,   240,   240,
     241,   242,   242,   243,   243,   244,   245,   245,   246,   246,
     246,   247,   248,   249,   250,   251,   252,   253
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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
       3,     0,     6,     0,     4,     0,     6,     0,     3,     2,
       1,     1,     3,     0,     2,     0,     2,     3,     3,     5,
       3,     1,     1,     2,     3,     2,     2,     1,     0,     0,
       6,     0,     4,     0,     5,     0,     6,     0,     5,     0,
       0,     6,     0,     7,     2,     3,     1,     3,     3,     1,
       1,     1,     1,     0,     4,     0,     6,     0,     6,     0,
       7,     0,     7,     0,     5,     0,     5,     0,     5,     0,
       5,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     4,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     1,     1,     3,     3,     2,     2,     2,     1,
       3,     3,     3,     1,     0,     3,     2,     1,     3,     5,
       7,     1,     3,     5,     7,     3,     0,     0,     8,     1,
       3,     1,     1,     1,     3,     3,     3,     1,     3,     2,
       0,     3,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     3,     4,     4,     2,     2,
       2,     2,     0,     3,     4,     1,     3,     0,     3,     2,
       1,     1,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      35,   114,   117,   299,   295,   296,   297,   298,     0,   155,
     159,     0,     0,     0,    66,     0,     0,    41,     0,    61,
      62,     0,   268,   269,     0,   130,   115,   270,     0,   127,
     311,   308,   302,   306,   304,   310,   131,   313,   312,   315,
     314,   316,   317,     0,    24,     0,     0,     0,    66,     0,
       0,   224,    35,     4,    20,    21,    18,    19,     0,    16,
       0,    40,    17,    23,    12,    13,    69,    22,    14,     0,
     113,     0,    15,   172,   170,    35,   171,   133,    68,   142,
     109,   111,   110,   108,    11,     0,   166,   169,   191,   197,
     200,   203,   205,   212,   213,   219,   223,   255,   256,   257,
     231,   285,   294,   227,   267,   258,   309,   307,   265,   266,
     300,   260,   259,   262,   261,   263,   264,     0,     0,     0,
     294,   227,   258,    35,     0,     0,   125,    70,     0,     0,
     300,     0,    67,   166,    64,    65,     0,   119,     0,    60,
     118,     0,   278,   279,    27,     0,    35,     0,     0,   253,
     280,   281,   236,     0,     0,     0,   166,   204,   226,     0,
       1,    35,     3,     2,    38,    36,    53,    39,    45,    48,
     116,   112,   135,    10,    35,   129,     0,   123,   148,     0,
     145,   147,   143,   164,     0,     0,     0,   198,   201,     0,
       0,     0,     0,     0,     0,     0,     0,   216,   217,   218,
       0,     0,     0,     0,     0,     0,     0,   193,   194,   195,
     196,   192,   173,     0,   301,   303,     0,   278,   279,   280,
     281,   153,     0,     0,     0,     6,     5,     0,   135,     0,
       0,   135,     0,    63,    35,    42,    55,     0,     0,     0,
      57,   183,   185,    35,     0,   128,     0,   235,     0,   187,
     189,     0,     0,   232,     0,     0,   271,   228,     0,   225,
       8,    35,   166,    37,     0,    49,     0,    47,   121,   120,
       0,   132,     9,   134,     0,     0,   151,   146,   144,   165,
     157,    26,     0,     0,   210,   211,   206,   207,   208,   209,
     214,   215,   222,   220,   221,     0,   272,   273,   287,   291,
       0,     0,   275,     0,     0,     0,   283,    35,   272,   273,
       0,     0,   160,    96,    96,    72,     0,     0,    59,    58,
       0,     0,    28,     0,   254,   252,     0,     0,   239,     0,
     167,     0,   168,     0,     7,    54,     0,     0,     0,    44,
       0,     0,   136,     0,   141,   124,     0,    35,    35,   199,
     202,   284,   175,   177,     0,   289,   277,   276,   292,     0,
      34,   174,     0,   154,   277,   276,     0,    35,    96,    95,
       0,    96,     0,   162,    56,   184,   186,    31,   188,   190,
     237,     0,   233,     0,   229,    51,    50,    46,     0,   137,
       0,   138,   149,   152,   158,     0,     0,   288,   286,   181,
     179,   293,   305,   156,   161,   126,    94,     0,     0,   100,
      99,   103,   105,   104,    71,     0,    35,     0,     0,     0,
       0,     0,     0,     0,   122,     0,   140,    35,   176,   178,
       0,     0,   107,    97,     0,     0,     0,     0,     0,    75,
      76,    81,    92,   163,    32,    29,   242,     0,   241,   243,
     258,   234,   230,    52,   139,   150,   182,   180,    35,   102,
     105,     0,   101,   106,     0,    73,    74,     0,     0,    35,
       0,   238,     0,    98,    90,    91,     0,    82,    33,    30,
     240,   250,   244,   245,   247,    78,     0,    80,     0,     0,
     249,     0,    77,    82,    83,    84,    86,    87,    88,    89,
      93,   251,   248,   246,    79,    85
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   174,   224,   225,   175,   226,    54,   186,    55,   243,
     469,   418,    56,    57,    58,   165,    59,    60,   136,   167,
     266,   339,   168,   169,   337,   423,   264,    61,    62,   138,
      63,    64,   131,    65,    66,   230,    67,   372,   438,   439,
     467,   486,   440,   487,   488,   494,   495,   496,   497,   441,
     499,   368,   369,   370,   458,   408,   409,   410,   411,   412,
      68,    69,    70,    71,   139,    72,   340,   274,   229,    73,
     146,    74,    75,    76,    77,   177,   271,   343,    78,   180,
     181,   275,   427,   182,   347,    79,   307,    80,   123,    81,
     348,    82,   124,   367,    83,   416,    84,    85,   153,    86,
      87,   304,   395,   396,   431,   430,   320,   321,   326,   327,
     212,    88,    89,   282,    90,   283,    91,    92,    93,    94,
      95,    96,   159,    97,    98,    99,   100,   251,   419,   329,
     447,   448,   449,   483,   484,   489,   148,   149,   101,   102,
     205,   216,   300,   354,   302,   121,   104,   105,   106,   107,
     214,   108,   109,   110,   111,   112,   113,   114,   115,   116
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -372
static const yytype_int16 yypact[] =
{
     991,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  1669,  -372,
    -372,  1165,    29,    22,  1501,     9,    25,  -372,     7,  -372,
    -372,     7,  -372,  -372,    37,  -372,  -372,  -372,   100,  -372,
    -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,
    -372,  -372,  -372,  1501,  -372,    37,    34,  1501,  1501,  1753,
    1837,  -372,   556,  -372,  -372,  -372,  -372,  -372,    62,  -372,
     109,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,    13,
    -372,     7,  -372,  -372,  -372,   643,  -372,   101,  -372,   122,
    -372,  -372,  -372,  -372,  -372,    76,    -2,  -372,  -372,   135,
     129,  -372,  -372,   148,    54,     1,  -372,  -372,  -372,  -372,
    -372,  -372,    27,   125,  -372,    60,   110,   110,  -372,  -372,
      74,  -372,  -372,  -372,  -372,  -372,  -372,    37,    37,   137,
      35,  -372,  -372,  1078,  1669,     7,  -372,  -372,     7,   200,
    -372,   152,   146,  -372,  -372,  -372,   156,  -372,    83,  -372,
    -372,     0,    60,    60,  -372,    22,   643,   154,    72,  -372,
      60,    60,  -372,     2,   -26,   163,   188,  -372,  -372,  1837,
    -372,   730,  -372,  -372,  -372,   110,     7,  -372,   133,  -372,
    -372,  -372,   -27,  -372,   817,  -372,  1501,  -372,  -372,   158,
     122,  -372,  -372,  -372,  1501,   223,   156,  -372,  -372,  1753,
    1753,  1753,  1753,  1753,  1753,  1753,  1753,  -372,  -372,  -372,
    1837,  1837,  1837,    15,  1249,   159,  1501,  -372,  -372,  -372,
    -372,  -372,  -372,   177,  -372,  -372,   107,  -372,  -372,  -372,
    -372,  -372,    15,  1249,   235,  -372,  -372,   176,   170,   182,
     184,   170,  1837,  -372,   730,  -372,  -372,  1501,     7,   185,
    -372,  -372,  -372,  1078,   237,  -372,  1501,  -372,  1501,  -372,
    -372,  1501,  1501,  -372,  1501,  1501,  -372,  -372,  1501,  -372,
    -372,   904,    -4,  -372,   156,   116,   226,  -372,  -372,  -372,
     -17,  -372,  -372,   146,   156,  1669,  -372,  -372,  -372,  -372,
    -372,  -372,  1669,  1669,  -372,  -372,  -372,  -372,  -372,  -372,
       1,     1,  -372,  -372,  -372,   159,    60,    60,   112,   201,
     113,  1333,  -372,   134,  1501,  1501,  -372,  1078,  -372,  -372,
     130,  1669,  -372,  -372,  -372,  -372,   202,   142,  -372,  -372,
    1501,  1501,  -372,  1837,  -372,  -372,  1501,  1501,  -372,   199,
    -372,   -46,  -372,   -37,  -372,  -372,    22,   156,   156,  -372,
    1501,   180,  -372,     5,  -372,  -372,   207,  1078,  1078,   129,
    -372,  -372,  -372,  -372,  1501,  1501,    60,    60,  -372,    17,
    -372,  -372,   224,  -372,  -372,  -372,   209,  1078,   212,  -372,
    1585,   227,   225,  -372,  -372,  -372,  -372,   239,  -372,  -372,
    -372,  1501,  -372,  1501,  -372,   228,  -372,  -372,   231,  -372,
     -31,  -372,  -372,  -372,  -372,  1501,  1501,  -372,  -372,  -372,
    -372,  -372,  -372,  -372,  -372,  -372,  -372,   -23,   249,  -372,
     234,  -372,    21,  -372,  -372,   -39,  1078,  1501,   232,  1669,
     219,   238,    22,   156,  -372,   229,  -372,  1078,  -372,  -372,
    1501,  1501,  -372,  -372,  1585,   236,  1501,   241,   -24,  -372,
    -372,  -372,  -372,  -372,   256,  -372,  -372,    -1,  -372,  -372,
     266,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  1078,  -372,
     242,    22,  -372,  -372,   128,  -372,  -372,   250,  1501,  1078,
    1669,  -372,  1417,  -372,  -372,  -372,   252,  -372,  -372,  -372,
    -372,  -372,   246,  -372,   261,  -372,   -12,  -372,    97,  1501,
    1501,  1501,  -372,  -372,  -372,    97,  -372,  -372,  -372,  -372,
    -372,  -372,  -372,  -372,  -372,  -372
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -372,    12,  -161,   -45,   193,     3,  -372,  -372,  -372,  -372,
    -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,
    -372,  -372,  -372,   172,  -372,  -372,  -372,  -372,  -372,   -11,
    -372,  -372,   293,  -372,  -372,  -372,  -372,  -372,  -372,   -96,
    -372,  -372,  -372,  -150,  -372,  -372,  -372,  -149,  -117,  -371,
    -372,    38,  -179,  -372,  -372,  -372,  -372,  -372,   -86,  -251,
    -372,  -372,   282,   342,   305,  -372,  -372,  -372,  -372,  -372,
    -372,  -362,  -372,  -372,   343,  -372,   124,    23,  -372,  -372,
     178,  -372,  -372,   181,  -372,  -372,  -372,  -372,  -372,  -372,
    -372,  -372,  -372,  -372,  -372,  -372,  -372,    -5,  -372,   -10,
    -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,
     -89,    -6,  -372,  -372,    75,  -372,    79,   316,   143,  -372,
      26,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,  -372,
    -372,  -104,  -372,  -372,  -372,  -372,  -372,   119,  -372,   251,
    -372,  -372,   145,  -372,    77,    88,   -18,    81,  -372,  -372,
     -94,  -372,   153,   -13,   276,  -372,   280,  -372,  -372,   285
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -291
static const yytype_int16 yytable[] =
{
     130,   127,   119,    53,   133,   140,   143,   162,   140,   132,
     141,   140,    52,   215,   185,   425,   185,     1,   170,   254,
      30,   295,     3,     4,     5,     6,     7,   151,    30,   341,
     268,   381,   140,   147,   128,    30,    30,   154,   156,   382,
     383,   437,    30,   132,     3,     4,     5,     6,     7,   269,
     384,   465,   255,   241,   242,   163,   437,   270,   140,   256,
     239,   249,   250,   152,   492,    26,    30,   137,   342,   493,
     -25,   263,   -25,   246,    30,   137,   240,   470,    53,   238,
     252,    30,   322,   390,   200,   134,   471,   253,   103,   122,
     391,   235,   201,   202,   129,   184,    30,   137,   435,   218,
     220,   135,   401,   436,   140,   140,   203,   207,   208,   209,
     210,  -274,   140,   204,   222,   140,   144,   498,   227,  -274,
     152,   223,   145,    38,   498,    40,   500,    42,   164,   162,
     122,   122,   130,   500,  -282,  -282,   178,   179,   158,  -282,
     103,   281,   211,   195,   196,   166,   363,   247,    25,    53,
     248,   262,   183,   140,   184,   265,    30,   474,   188,   236,
     475,   237,   238,   103,    53,   187,   133,    31,    32,   166,
     -43,   273,    35,   261,   279,   189,   190,   163,   176,   191,
     192,   193,   194,   460,   462,   297,   393,   394,   474,   406,
     140,   475,   406,   336,   299,   238,   133,  -290,   356,  -290,
     357,   303,   206,   213,   309,   122,   404,   352,   353,   140,
     360,   103,   184,   299,   221,   364,   162,   365,   374,   335,
     184,   290,   291,   232,   184,   140,   244,   133,   233,   345,
     234,   246,   317,   258,   103,   276,   324,    53,   147,   280,
     122,   328,   330,   301,   331,   332,   261,   259,   333,   103,
     257,   305,   311,   312,   270,   443,   313,   344,   314,   120,
     323,   319,   103,   338,   163,   389,   455,   399,   400,   346,
     122,   122,   122,   122,   122,   122,   122,   122,   355,   373,
     380,   122,   122,   122,   392,   403,   402,   405,   292,   293,
     294,   133,   386,   387,   361,   362,   359,   473,   417,   415,
     120,   120,   414,   433,   451,   366,   422,   424,   479,   445,
     375,   376,   434,   122,   454,   468,   378,   379,   464,   461,
     316,   472,   103,   344,   436,   452,   490,   477,   485,   142,
     388,   103,   284,   285,   286,   287,   288,   289,   491,   245,
     267,   155,   466,   504,   397,   398,   505,   476,   459,   103,
     150,   171,   371,   125,   126,   315,   122,   349,   277,   385,
     413,   278,   350,   122,   122,   157,   480,   325,   310,   306,
     197,   420,   351,   421,   198,   120,   172,   426,   453,   199,
       0,     0,     0,     0,     0,   428,   429,     0,     0,     0,
       0,     0,   122,     0,   130,   103,     0,     0,     0,     0,
       0,     0,   442,     0,   122,     0,     0,   444,     0,   426,
     120,   377,     0,   446,     0,     0,     0,     0,     0,     0,
     456,   457,   217,   219,   413,   442,   463,     0,     0,     0,
     228,     0,     0,   231,     0,   103,   103,     0,     0,     0,
     120,   120,   120,   120,   120,   120,   120,   120,   130,     0,
       0,   120,   120,   120,     0,   103,     0,     0,   478,     0,
       0,     0,   482,     0,   446,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   442,     0,     0,     0,   501,
     502,   503,   442,   120,     0,     0,     0,     0,   432,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     450,     0,     0,     0,   103,     0,     0,     0,   296,     0,
       0,     0,     0,     0,     0,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   120,   308,     0,     0,
       0,     0,     0,   120,   120,     0,     0,     0,     0,     0,
       0,     0,   432,   318,     0,     0,   103,     0,     0,     0,
       0,   450,     0,     0,     0,     0,   160,   103,     0,     0,
       1,     2,   120,     3,     4,     5,     6,     7,     0,     8,
       0,     0,     9,    10,   120,     0,    11,    12,    13,     0,
      14,    15,    16,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,     0,    18,     0,    19,    20,    21,    22,
      23,    24,     0,     0,     0,     0,     0,    25,    26,    27,
       0,     0,    28,     0,    29,    30,    31,    32,     0,    33,
      34,    35,     0,    36,    37,    38,    39,    40,    41,    42,
     161,     0,    44,     0,     0,    45,     0,     0,     0,    46,
      47,     0,    48,     0,    49,    50,    51,     1,     2,     0,
       3,     4,     5,     6,     7,     0,     8,     0,     0,     9,
      10,     0,     0,    11,    12,    13,     0,    14,    15,    16,
     120,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,    18,     0,    19,    20,    21,    22,    23,    24,     0,
       0,     0,     0,     0,    25,    26,    27,     0,     0,    28,
       0,    29,    30,    31,    32,     0,    33,    34,    35,     0,
      36,    37,    38,    39,    40,    41,    42,    43,   173,    44,
       0,   120,    45,     0,     0,     0,    46,    47,     0,    48,
       0,    49,    50,    51,     1,     2,     0,     3,     4,     5,
       6,     7,     0,     8,     0,     0,     9,    10,     0,     0,
      11,    12,    13,     0,    14,    15,    16,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,    18,     0,
      19,    20,    21,    22,    23,    24,     0,     0,     0,     0,
       0,    25,    26,    27,     0,     0,    28,     0,    29,    30,
      31,    32,     0,    33,    34,    35,     0,    36,    37,    38,
      39,    40,    41,    42,    43,   260,    44,     0,     0,    45,
       0,     0,     0,    46,    47,     0,    48,     0,    49,    50,
      51,     1,     2,     0,     3,     4,     5,     6,     7,     0,
       8,     0,     0,     9,    10,     0,     0,    11,    12,    13,
       0,    14,    15,    16,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,    18,     0,    19,    20,    21,
      22,    23,    24,     0,     0,     0,     0,     0,    25,    26,
      27,     0,     0,    28,     0,    29,    30,    31,    32,     0,
      33,    34,    35,     0,    36,    37,    38,    39,    40,    41,
      42,   161,   272,    44,     0,     0,    45,     0,     0,     0,
      46,    47,     0,    48,     0,    49,    50,    51,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     8,     0,     0,
       9,    10,     0,     0,    11,    12,    13,     0,    14,    15,
      16,     0,     0,     0,     0,     0,     0,     0,     0,    17,
       0,     0,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,     0,     0,     0,    25,    26,    27,     0,     0,
      28,     0,    29,    30,    31,    32,     0,    33,    34,    35,
       0,    36,    37,    38,    39,    40,    41,    42,   161,   334,
      44,     0,     0,    45,     0,     0,     0,    46,    47,     0,
      48,     0,    49,    50,    51,     1,     2,     0,     3,     4,
       5,     6,     7,     0,     8,     0,     0,     9,    10,     0,
       0,    11,    12,    13,     0,    14,    15,    16,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,     0,    18,
       0,    19,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,    25,    26,    27,     0,     0,    28,     0,    29,
      30,    31,    32,     0,    33,    34,    35,     0,    36,    37,
      38,    39,    40,    41,    42,    43,     0,    44,     0,     0,
      45,     0,     0,     0,    46,    47,     0,    48,     0,    49,
      50,    51,     1,     2,     0,     3,     4,     5,     6,     7,
       0,     8,     0,     0,     9,    10,     0,     0,    11,    12,
      13,     0,    14,    15,    16,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,    18,     0,    19,    20,
      21,    22,    23,    24,     0,     0,     0,     0,     0,    25,
      26,    27,     0,     0,    28,     0,    29,    30,    31,    32,
       0,    33,    34,    35,     0,    36,    37,    38,    39,    40,
      41,    42,   161,     0,    44,     0,     0,    45,     0,     0,
       0,    46,    47,     0,    48,     0,    49,    50,    51,     1,
       2,     0,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    22,    23,
      24,     0,     0,     0,     0,     0,    25,    26,    27,     0,
       0,     0,     0,    29,    30,    31,    32,     0,    33,    34,
      35,     0,    36,    37,    38,    39,    40,    41,    42,    43,
       0,     0,     0,     0,    45,     0,     0,     0,    46,    47,
       0,    48,     0,    49,    50,    51,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,    23,    24,     0,     0,     0,     0,     0,
      25,     0,    27,     0,     0,     0,     0,    29,    30,    31,
      32,     0,    33,    34,    35,     0,    36,    37,    38,    39,
      40,    41,    42,    43,     0,     0,   298,     0,    45,     0,
       0,     0,    46,    47,     0,    48,     0,    49,    50,    51,
       3,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,    23,    24,     0,
       0,     0,     0,     0,    25,     0,    27,     0,     0,     0,
       0,    29,    30,    31,    32,     0,    33,    34,    35,     0,
      36,    37,    38,    39,    40,    41,    42,    43,     0,     0,
       0,     0,    45,     0,     0,     0,    46,    47,   358,    48,
       0,    49,    50,    51,     3,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,    23,    24,     0,     0,     0,     0,     0,    25,     0,
      27,     0,     0,     0,     0,    29,    30,    31,    32,     0,
      33,    34,    35,     0,    36,    37,    38,    39,    40,    41,
      42,    43,     0,     0,     0,     0,    45,   481,     0,     0,
      46,    47,     0,    48,     0,    49,    50,    51,     3,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    22,    23,    24,     0,     0,     0,
       0,     0,    25,     0,    27,     0,     0,     0,     0,    29,
      30,    31,    32,     0,    33,    34,    35,     0,    36,    37,
      38,    39,    40,    41,    42,    43,     0,     0,     0,     0,
      45,     0,     0,     0,    46,    47,     0,    48,     0,    49,
      50,    51,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    22,    23,
      24,     0,     0,     0,     0,     0,    25,     0,    27,     0,
       0,     0,     0,    29,    30,    31,    32,     0,    33,    34,
      35,     0,    36,    37,    38,    39,    40,    41,    42,    43,
       0,     0,     0,     0,    45,     0,     0,     0,   407,    47,
       0,    48,     0,    49,    50,    51,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,    23,   117,     0,     0,     0,     0,     0,
       0,     0,    27,     0,     0,     0,     0,     0,    30,    31,
      32,     0,    33,    34,    35,     0,     0,    37,    38,    39,
      40,    41,    42,    43,     0,     0,     0,     0,   118,     0,
       0,     0,    46,    47,     0,    48,     0,    49,    50,    51,
       3,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,    23,   117,     0,
       0,     0,     0,     0,     0,     0,    27,     0,     0,     0,
       0,     0,    30,    31,    32,     0,    33,    34,    35,     0,
       0,    37,    38,    39,    40,    41,    42,    43,     0,     0,
       0,     0,   118,     0,     0,     0,    46,    47,     0,    48,
       0,     0,    50,    51,     3,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,    23,   117,     0,     0,     0,     0,     0,     0,     0,
      27,     0,     0,     0,     0,     0,    30,    31,    32,     0,
      33,    34,    35,     0,     0,    37,    38,    39,    40,    41,
      42,    43,     0,     0,     0,     0,   118,     0,     0,     0,
      46,    47,     0,    48
};

static const yytype_int16 yycheck[] =
{
      13,    11,     8,     0,    14,    18,    24,    52,    21,    14,
      21,    24,     0,   107,    18,    46,    18,     4,     5,    45,
      59,     6,     7,     8,     9,    10,    11,    45,    59,    46,
      57,    77,    45,    43,     5,    59,    59,    47,    48,    85,
      77,    80,    59,    48,     7,     8,     9,    10,    11,    76,
      87,    75,    78,   142,   143,    52,    80,    84,    71,    85,
      60,   150,   151,    86,    76,    52,    59,    60,    85,    81,
      74,   165,    74,    77,    59,    60,    76,    78,    75,    79,
      78,    59,   243,    78,    83,    76,    87,    85,     0,     8,
      85,   136,    91,    92,    13,    78,    59,    60,    77,   117,
     118,    76,    85,    82,   117,   118,    79,    47,    48,    49,
      50,    84,   125,    86,    79,   128,    16,   488,   124,    84,
      86,    86,    22,    69,   495,    71,   488,    73,    66,   174,
      49,    50,   145,   495,    60,    61,    14,    15,    50,    65,
      52,   186,    82,    89,    90,    36,   307,    75,    51,   146,
      78,   161,    76,   166,    78,   166,    59,    60,    29,    76,
      63,    78,    79,    75,   161,    30,   176,    60,    61,    36,
      37,   176,    65,   161,   184,    27,    28,   174,    77,    31,
      32,    33,    34,   434,   435,   203,   347,   348,    60,   368,
     203,    63,   371,    77,   204,    79,   206,    85,    85,    87,
      87,   206,    77,    93,   222,   124,   367,   296,   297,   222,
      76,   123,    78,   223,    77,    85,   261,    87,    76,   264,
      78,   195,   196,    23,    78,   238,   145,   237,    76,   274,
      74,    77,   237,    45,   146,    77,   246,   234,   248,    16,
     159,   251,   252,    84,   254,   255,   234,   159,   258,   161,
      87,    74,    17,    77,    84,   416,    74,   270,    74,     8,
      23,    76,   174,    37,   261,    85,   427,   356,   357,   275,
     189,   190,   191,   192,   193,   194,   195,   196,    77,    77,
      81,   200,   201,   202,    77,    76,    62,    75,   200,   201,
     202,   301,   337,   338,   304,   305,   301,   458,    59,    74,
      49,    50,    75,    54,    85,   311,    78,    76,   469,    77,
     320,   321,    78,   232,    85,    59,   326,   327,    77,    83,
     232,    55,   234,   336,    82,    87,    80,    77,    76,    24,
     340,   243,   189,   190,   191,   192,   193,   194,    77,   146,
     168,    48,   438,   493,   354,   355,   495,   464,   434,   261,
      45,    69,   314,    11,    11,   231,   275,   282,   180,   336,
     370,   180,   283,   282,   283,    49,   470,   248,   223,   216,
      94,   381,   295,   383,    94,   124,    71,   390,   423,    94,
      -1,    -1,    -1,    -1,    -1,   395,   396,    -1,    -1,    -1,
      -1,    -1,   311,    -1,   407,   307,    -1,    -1,    -1,    -1,
      -1,    -1,   415,    -1,   323,    -1,    -1,   417,    -1,   422,
     159,   323,    -1,   419,    -1,    -1,    -1,    -1,    -1,    -1,
     430,   431,   117,   118,   434,   438,   436,    -1,    -1,    -1,
     125,    -1,    -1,   128,    -1,   347,   348,    -1,    -1,    -1,
     189,   190,   191,   192,   193,   194,   195,   196,   461,    -1,
      -1,   200,   201,   202,    -1,   367,    -1,    -1,   468,    -1,
      -1,    -1,   472,    -1,   470,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   488,    -1,    -1,    -1,   489,
     490,   491,   495,   232,    -1,    -1,    -1,    -1,   407,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     419,    -1,    -1,    -1,   416,    -1,    -1,    -1,   203,    -1,
      -1,    -1,    -1,    -1,    -1,   427,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   275,   222,    -1,    -1,
      -1,    -1,    -1,   282,   283,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   461,   238,    -1,    -1,   458,    -1,    -1,    -1,
      -1,   470,    -1,    -1,    -1,    -1,     0,   469,    -1,    -1,
       4,     5,   311,     7,     8,     9,    10,    11,    -1,    13,
      -1,    -1,    16,    17,   323,    -1,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    38,    -1,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    -1,    56,    -1,    58,    59,    60,    61,    -1,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    76,    -1,    -1,    79,    -1,    -1,    -1,    83,
      84,    -1,    86,    -1,    88,    89,    90,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    13,    -1,    -1,    16,
      17,    -1,    -1,    20,    21,    22,    -1,    24,    25,    26,
     419,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    -1,    -1,    56,
      -1,    58,    59,    60,    61,    -1,    63,    64,    65,    -1,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      -1,   470,    79,    -1,    -1,    -1,    83,    84,    -1,    86,
      -1,    88,    89,    90,     4,     5,    -1,     7,     8,     9,
      10,    11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    -1,    56,    -1,    58,    59,
      60,    61,    -1,    63,    64,    65,    -1,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    79,
      -1,    -1,    -1,    83,    84,    -1,    86,    -1,    88,    89,
      90,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      13,    -1,    -1,    16,    17,    -1,    -1,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    38,    -1,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    -1,    -1,    56,    -1,    58,    59,    60,    61,    -1,
      63,    64,    65,    -1,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    -1,    -1,    79,    -1,    -1,    -1,
      83,    84,    -1,    86,    -1,    88,    89,    90,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    13,    -1,    -1,
      16,    17,    -1,    -1,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    -1,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    -1,
      56,    -1,    58,    59,    60,    61,    -1,    63,    64,    65,
      -1,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    -1,    -1,    79,    -1,    -1,    -1,    83,    84,    -1,
      86,    -1,    88,    89,    90,     4,     5,    -1,     7,     8,
       9,    10,    11,    -1,    13,    -1,    -1,    16,    17,    -1,
      -1,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,
      -1,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    -1,    -1,    56,    -1,    58,
      59,    60,    61,    -1,    63,    64,    65,    -1,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    76,    -1,    -1,
      79,    -1,    -1,    -1,    83,    84,    -1,    86,    -1,    88,
      89,    90,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    -1,    56,    -1,    58,    59,    60,    61,
      -1,    63,    64,    65,    -1,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    76,    -1,    -1,    79,    -1,    -1,
      -1,    83,    84,    -1,    86,    -1,    88,    89,    90,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    -1,    63,    64,
      65,    -1,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,    84,
      -1,    86,    -1,    88,    89,    90,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    53,    -1,    -1,    -1,    -1,    58,    59,    60,
      61,    -1,    63,    64,    65,    -1,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    77,    -1,    79,    -1,
      -1,    -1,    83,    84,    -1,    86,    -1,    88,    89,    90,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,
      -1,    58,    59,    60,    61,    -1,    63,    64,    65,    -1,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    83,    84,    85,    86,
      -1,    88,    89,    90,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      53,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    -1,
      63,    64,    65,    -1,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    79,    80,    -1,    -1,
      83,    84,    -1,    86,    -1,    88,    89,    90,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    -1,    63,    64,    65,    -1,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    83,    84,    -1,    86,    -1,    88,
      89,    90,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    53,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    -1,    63,    64,
      65,    -1,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,    84,
      -1,    86,    -1,    88,    89,    90,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    -1,    63,    64,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    83,    84,    -1,    86,    -1,    88,    89,    90,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    59,    60,    61,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    83,    84,    -1,    86,
      -1,    -1,    89,    90,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      83,    84,    -1,    86
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     7,     8,     9,    10,    11,    13,    16,
      17,    20,    21,    22,    24,    25,    26,    35,    38,    40,
      41,    42,    43,    44,    45,    51,    52,    53,    56,    58,
      59,    60,    61,    63,    64,    65,    67,    68,    69,    70,
      71,    72,    73,    74,    76,    79,    83,    84,    86,    88,
      89,    90,    95,    99,   100,   102,   106,   107,   108,   110,
     111,   121,   122,   124,   125,   127,   128,   130,   154,   155,
     156,   157,   159,   163,   165,   166,   167,   168,   172,   179,
     181,   183,   185,   188,   190,   191,   193,   194,   205,   206,
     208,   210,   211,   212,   213,   214,   215,   217,   218,   219,
     220,   232,   233,   239,   240,   241,   242,   243,   245,   246,
     247,   248,   249,   250,   251,   252,   253,    45,    79,   205,
     233,   239,   241,   182,   186,   157,   168,   193,     5,   241,
     247,   126,   191,   193,    76,    76,   112,    60,   123,   158,
     247,   123,   158,   240,    16,    22,   164,   193,   230,   231,
     158,   240,    86,   192,   193,   126,   193,   211,   239,   216,
       0,    74,    97,    99,    66,   109,    36,   113,   116,   117,
       5,   156,   158,    75,    95,    98,    77,   169,    14,    15,
     173,   174,   177,    76,    78,    18,   101,    30,    29,    27,
      28,    31,    32,    33,    34,    89,    90,   248,   250,   253,
      83,    91,    92,    79,    86,   234,    77,    47,    48,    49,
      50,    82,   204,    93,   244,   244,   235,   158,   240,   158,
     240,    77,    79,    86,    96,    97,    99,   205,   158,   162,
     129,   158,    23,    76,    74,    97,    76,    78,    79,    60,
      76,   204,   204,   103,   241,    98,    77,    75,    78,   204,
     204,   221,    78,    85,    45,    78,    85,    87,    45,   239,
      75,    95,   193,   244,   120,   123,   114,   117,    57,    76,
      84,   170,    75,   191,   161,   175,    77,   174,   177,   193,
      16,    97,   207,   209,   212,   212,   212,   212,   212,   212,
     214,   214,   239,   239,   239,     6,   158,   240,    77,   193,
     236,    84,   238,   191,   195,    74,   246,   180,   158,   240,
     236,    17,    77,    74,    74,   170,   239,   191,   158,    76,
     200,   201,    96,    23,   193,   231,   202,   203,   193,   223,
     193,   193,   193,   193,    75,    97,    77,   118,    37,   115,
     160,    46,    85,   171,   247,    97,   205,   178,   184,   208,
     210,   238,   204,   204,   237,    77,    85,    87,    85,   191,
      76,   193,   193,    96,    85,    87,   205,   187,   145,   146,
     147,   145,   131,    77,    76,   193,   193,   239,   193,   193,
      81,    77,    85,    77,    87,   171,    97,    97,   193,    85,
      78,    85,    77,    96,    96,   196,   197,   193,   193,   204,
     204,    85,    62,    76,    96,    75,   146,    83,   149,   150,
     151,   152,   153,   193,    75,    74,   189,    59,   105,   222,
     193,   193,    78,   119,    76,    46,   247,   176,   193,   193,
     199,   198,   241,    54,    78,    77,    82,    80,   132,   133,
     136,   143,   247,    96,   193,    77,   205,   224,   225,   226,
     241,    85,    87,    97,    85,    96,   193,   193,   148,   152,
     153,    83,   153,   193,    77,    75,   133,   134,    59,   104,
      78,    87,    55,    96,    60,    63,   142,    77,   193,    96,
     225,    80,   193,   227,   228,    76,   135,   137,   138,   229,
      80,    77,    76,    81,   139,   140,   141,   142,   143,   144,
     165,   193,   193,   193,   137,   141
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 208 "./src/parser/parser.y"
    {
			if ((yyvsp[(1) - (1)].integer) > 1) {
				for(int i=0; i<(yyvsp[(1) - (1)].integer); i++)
					g_op->pop_stack();
			}
			else {
				g_op->fast_pop_stack();
			}
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 224 "./src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 228 "./src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 241 "./src/parser/parser.y"
    {
			g_op->do_scope_start();
		;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 245 "./src/parser/parser.y"
    {
			g_op->do_scope_end();
		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 253 "./src/parser/parser.y"
    {
			g_ctl->parallel_start();
		;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 257 "./src/parser/parser.y"
    {
			g_ctl->parallel_end();
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 261 "./src/parser/parser.y"
    {
			g_ctl->parallel_for_start((yyvsp[(3) - (7)].cp));
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 265 "./src/parser/parser.y"
    {
			g_ctl->parallel_for_end();
		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 272 "./src/parser/parser.y"
    {
			g_op->push_integer(0);	// by
			g_op->push_integer(1);	// per
		;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 277 "./src/parser/parser.y"
    {
			int opt = 0;
			if (strncmp((yyvsp[(1) - (2)].cp), "by", 2) == 0) {
				g_op->push_integer(1);
			}
			else if (strncmp((yyvsp[(1) - (2)].cp), "per", 3) == 0) {
				g_op->push_integer(0);
				g_op->rotate();
			}
			else {
				yyerror("parallel option 'by' or 'per' expected");
			}
		;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 291 "./src/parser/parser.y"
    {
			if (strncmp((yyvsp[(1) - (4)].cp), "by", 2) != 0) {
				yyerror("parallel option 'by' expected");
			}

			if (strncmp((yyvsp[(3) - (4)].cp), "per", 3) != 0) {
				yyerror("parallel option 'per' expected");
			}
		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 305 "./src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (4)].integer));
		;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 312 "./src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_ROOT);
			g_op->find_member("os");
			g_op->find_member("run");
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 318 "./src/parser/parser.y"
    {	
			g_op->call(1);
		;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 327 "./src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 335 "./src/parser/parser.y"
    {
			g_ex->pop();
		;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 344 "./src/parser/parser.y"
    {
			g_ex->push();
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 348 "./src/parser/parser.y"
    {
			g_ex->goto_end();
		;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 356 "./src/parser/parser.y"
    {
			g_ex->do_finally();
		;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 360 "./src/parser/parser.y"
    {
			g_ex->goto_end();
		;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 380 "./src/parser/parser.y"
    {
			g_ex->catch_start((yyvsp[(2) - (2)].cp));
		;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 384 "./src/parser/parser.y"
    {
			g_ex->goto_finally();
		;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 388 "./src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(4) - (4)].vector_cp);
			g_ex->catch_start((yyvsp[(2) - (4)].cp), vp);
		;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 393 "./src/parser/parser.y"
    {
			g_ex->goto_finally();
		;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 397 "./src/parser/parser.y"
    {
			g_ex->catch_start(NULL);
		;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 401 "./src/parser/parser.y"
    {
			g_ex->goto_finally();
		;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 409 "./src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (3)].cp), 0);
		;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 413 "./src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (5)].cp), (yyvsp[(4) - (5)].integer));
		;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 421 "./src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (3)].cp), NULL);
		;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 425 "./src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (4)].cp), (yyvsp[(3) - (4)].cp));
		;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 433 "./src/parser/parser.y"
    {
			char buff[1024];
			sprintf(buff, "%s.%s", (yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
			(yyval.cp) = parser_strdup(buff);
		;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 439 "./src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 447 "./src/parser/parser.y"
    {
			g_op->dump_stack();
		;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 451 "./src/parser/parser.y"
    {
			g_op->dump_local();
		;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 459 "./src/parser/parser.y"
    {
			g_ctl->do_return((yyvsp[(2) - (3)].integer));
		;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 463 "./src/parser/parser.y"
    {
			g_ctl->do_continue();
		;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 467 "./src/parser/parser.y"
    {
			g_ctl->do_break();
		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 475 "./src/parser/parser.y"
    {
			(yyval.integer) = 0;
		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 479 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 493 "./src/parser/parser.y"
    {
			g_ctl->decode_start();
		;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 497 "./src/parser/parser.y"
    {
			g_ctl->decode_end();
		;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 505 "./src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(4) - (4)].vector_cp);

			// check argv
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				yyerror("argv not allowed in parse object");
			}

			if (vp == NULL) {
				yyerror("at least 1 argument needed in parse object");
			}

			parserCode::push_code_stack((yyvsp[(3) - (4)].cp), vp);
			g_parse->do_parse_init();
		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 521 "./src/parser/parser.y"
    {
			vector<char>& def = parserCode::get_def();

			g_parse->make_table();
			//g_parse->dump();
			g_parse->do_parse(def);
			g_parse->cleanup();

			parserCode::pop_code_stack();
		;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 542 "./src/parser/parser.y"
    {
			g_parse->set_current_bnf((yyvsp[(1) - (1)].bp));
		;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 546 "./src/parser/parser.y"
    {

		;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 550 "./src/parser/parser.y"
    {
			bnf* b = (yyvsp[(3) - (4)].bp);
			b->type = BNF_WS;
		;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 570 "./src/parser/parser.y"
    {
			g_bnf_right_num = 1;
			g_parse->current_bnf()->add_rule();
		;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 585 "./src/parser/parser.y"
    {
			g_bnf_right_num++;
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(2) - (2)].bp));
		;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 590 "./src/parser/parser.y"
    {
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(1) - (1)].bp));
		;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 605 "./src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp));
		;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 609 "./src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp), true);
		;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 617 "./src/parser/parser.y"
    {
			string name = "`\a";
			name += (yyvsp[(1) - (1)].cp);
			(yyval.bp) = g_parse->get_nonterm_bnf(name);
		;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 627 "./src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_action_bnf(g_bnf_right_num);
		;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 640 "./src/parser/parser.y"
    {
			g_ctl->decode_pattern_start();
		;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 644 "./src/parser/parser.y"
    {
			g_ctl->decode_pattern_shift();
		;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 648 "./src/parser/parser.y"
    {
			g_ctl->decode_pattern_end();
		;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 662 "./src/parser/parser.y"
    {
			g_ctl->decode_cut_list((yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
		;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 670 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 674 "./src/parser/parser.y"
    {
			(yyval.integer) = 1;
		;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 682 "./src/parser/parser.y"
    {
			g_ctl->decode_match_expr();
		;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 686 "./src/parser/parser.y"
    {
			g_ctl->decode_shift((yyvsp[(1) - (1)].cp));
		;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 690 "./src/parser/parser.y"
    {
			g_ctl->decode_match_and_assign((yyvsp[(1) - (3)].cp));
		;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 698 "./src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(2) - (2)].cp);
		;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 714 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer) | (yyvsp[(2) - (2)].integer);
		;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 718 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 726 "./src/parser/parser.y"
    {
			(yyval.integer) = BIT_DEFINE_STATIC;
		;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 730 "./src/parser/parser.y"
    {
			(yyval.integer) = BIT_DEFINE_PURE;
		;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 738 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer);
		;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 742 "./src/parser/parser.y"
    {
			(yyval.integer) = 0;
		;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 750 "./src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 754 "./src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 762 "./src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
		;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 766 "./src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
			code_top->init_object_start((yyvsp[(2) - (3)].cp));

			g_op->push_reserved(OP_PUSH_MY);
		;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 773 "./src/parser/parser.y"
    {
			g_op->assign_member((yyvsp[(2) - (6)].cp));
			g_op->pop_stack();
			code_top->init_object_done();
		;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 779 "./src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer)) {
				code_top->make_super((yyvsp[(2) - (2)].integer));
			}
		;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 785 "./src/parser/parser.y"
    {
			parserCode::pop_code_stack();
		;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 789 "./src/parser/parser.y"
    {
			
			g_ctl->decode_func_start();
		;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 794 "./src/parser/parser.y"
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();
		;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 803 "./src/parser/parser.y"
    {
			g_ctl->once_start();
		;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 807 "./src/parser/parser.y"
    {
			g_ctl->once_end();
		;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 815 "./src/parser/parser.y"
    {
			parserCode::pop_code_stack();
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(1) - (2)].cp));
		;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 825 "./src/parser/parser.y"
    {
			static int count = 1;
			char buff[256];
			sprintf(buff, "#%d_lambda", count++);
			const char* name = parser_strdup(buff);
			
			parserCode::push_code_stack(name);
			code_top->find_lvar("argv");
			code_top->set_argv_on();

			(yyval.cp) = name;
		;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 842 "./src/parser/parser.y"
    {
			cp2_t cp2 = (yyvsp[(1) - (1)].cp2);
			code_top->do_context(cp2.c1, cp2.c2);
		;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 851 "./src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(3) - (3)].vector_cp);

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			parserCode::push_code_stack((yyvsp[(2) - (3)].cp), vp, (yyvsp[(1) - (3)].integer));

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}
		;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 877 "./src/parser/parser.y"
    {
			(yyval.integer) = 0;
		;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 881 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (2)].integer);
		;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 889 "./src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 893 "./src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 897 "./src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 903 "./src/parser/parser.y"
    {
			(yyval.vector_cp) = (yyvsp[(2) - (3)].vector_cp);
		;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 907 "./src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(2) - (5)].vector_cp);
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 917 "./src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(1) - (3)].vector_cp);
			vs->push_back((yyvsp[(3) - (3)].cp));
			(yyval.vector_cp) = vs;
		;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 923 "./src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back((yyvsp[(1) - (1)].cp));
			(yyval.vector_cp) = vs;
		;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 933 "./src/parser/parser.y"
    {
			g_ctl->if_end();
		;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 937 "./src/parser/parser.y"
    {
			g_ctl->else_end();
		;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 941 "./src/parser/parser.y"
    {
			g_ctl->else_end();
			for(int i=0; i<(yyvsp[(2) - (3)].integer); i++)
				g_ctl->else_end();
		;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 947 "./src/parser/parser.y"
    {
			g_ctl->if_end();
			for(int i=0; i<(yyvsp[(2) - (2)].integer); i++)
				g_ctl->else_end();
		;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 957 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer) + 1;
		;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 961 "./src/parser/parser.y"
    {
			(yyval.integer) = 1;
		;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 969 "./src/parser/parser.y"
    {
			g_ctl->else_start();
		;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 973 "./src/parser/parser.y"
    {
			g_ctl->if_start();
		;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 982 "./src/parser/parser.y"
    {
			g_ctl->else_start();
		;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 991 "./src/parser/parser.y"
    {
			g_ctl->if_start();
		;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1000 "./src/parser/parser.y"
    {
			g_ctl->do_start();
		;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1004 "./src/parser/parser.y"
    {
			g_ctl->do_end();
		;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1012 "./src/parser/parser.y"
    {
			g_ctl->times_start();
		;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1016 "./src/parser/parser.y"
    {
			g_ctl->times_end();
		;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1024 "./src/parser/parser.y"
    {
			g_ctl->while_start_1();
		;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1028 "./src/parser/parser.y"
    {
			g_ctl->while_start_2();
		;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1032 "./src/parser/parser.y"
    {
			g_ctl->while_end();
		;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1040 "./src/parser/parser.y"
    {
			g_ctl->for_start((yyvsp[(2) - (5)].cp));
		;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1044 "./src/parser/parser.y"
    {
			g_ctl->for_end();
		;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1052 "./src/parser/parser.y"
    { 
			(yyval.integer) = (yyvsp[(1) - (2)].integer); 
		;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1060 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1064 "./src/parser/parser.y"
    {
			(yyval.integer) = 1;
		;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1072 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1076 "./src/parser/parser.y"
    {
			(yyval.integer) = 2;
		;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1092 "./src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer) != '=') {
				g_op->push_lvar((yyvsp[(1) - (2)].cp));
			}
		;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1098 "./src/parser/parser.y"
    {
			switch ((yyvsp[(2) - (4)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_local((yyvsp[(1) - (4)].cp));
		;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1110 "./src/parser/parser.y"
    {
			g_op->clear_last_find_position();
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_member((yyvsp[(3) - (4)].cp));
			}
		;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1118 "./src/parser/parser.y"
    {
			switch ((yyvsp[(4) - (6)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((yyvsp[(3) - (6)].cp));
		;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1130 "./src/parser/parser.y"
    {
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_reserved((yyvsp[(3) - (4)].integer));
			}
		;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1137 "./src/parser/parser.y"
    {
			switch ((yyvsp[(4) - (6)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((yyvsp[(3) - (6)].integer));
		;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1149 "./src/parser/parser.y"
    {
			if ((yyvsp[(5) - (5)].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(false);
			}
		;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1157 "./src/parser/parser.y"
    {
			switch ((yyvsp[(5) - (7)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			if ((yyvsp[(5) - (7)].integer) != '=') {
				g_op->do_rc_dec();
			}

			g_op->assign_list(false);
		;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1173 "./src/parser/parser.y"
    {
			if ((yyvsp[(5) - (5)].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(true);
			}
		;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1181 "./src/parser/parser.y"
    {
			switch ((yyvsp[(5) - (7)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			if ((yyvsp[(5) - (7)].integer) != '=') {
				g_op->do_rc_dec();
			}

			g_op->assign_list(true);
		;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1197 "./src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[(2) - (3)].cp));
			}
		;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1206 "./src/parser/parser.y"
    {
			switch ((yyvsp[(3) - (5)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((yyvsp[(2) - (5)].cp));
		;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1218 "./src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[(2) - (3)].integer));
			}
		;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1227 "./src/parser/parser.y"
    {
			switch ((yyvsp[(3) - (5)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((yyvsp[(2) - (5)].integer));
		;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1239 "./src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[(2) - (3)].cp));
			}
		;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1248 "./src/parser/parser.y"
    {
			switch ((yyvsp[(3) - (5)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((yyvsp[(2) - (5)].cp));
		;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1260 "./src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[(2) - (3)].integer));
			}
		;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1269 "./src/parser/parser.y"
    {
			switch ((yyvsp[(3) - (5)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((yyvsp[(2) - (5)].integer));
		;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1286 "./src/parser/parser.y"
    {
			(yyval.integer) = '='; 
		;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1290 "./src/parser/parser.y"
    { 
			(yyval.integer) = '+'; 
		;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1294 "./src/parser/parser.y"
    { 
			(yyval.integer) = '-'; 
		;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1298 "./src/parser/parser.y"
    { 
			(yyval.integer) = '*'; 
		;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1302 "./src/parser/parser.y"
    { 
			(yyval.integer) = '/'; 
		;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1315 "./src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start(false);
		;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1320 "./src/parser/parser.y"
    {
			g_op->do_or();
			g_ctl->if_end();
		;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1330 "./src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start();
		;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1335 "./src/parser/parser.y"
    {
			g_op->do_and();
			g_ctl->if_end();
		;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1345 "./src/parser/parser.y"
    {
			g_op->do_not();
		;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1354 "./src/parser/parser.y"
    {
			g_op->gt();
		;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1358 "./src/parser/parser.y"
    {
			g_op->ge();
		;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1362 "./src/parser/parser.y"
    {
			g_op->lt();
		;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1366 "./src/parser/parser.y"
    {
			g_op->le();
		;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1370 "./src/parser/parser.y"
    {
			g_op->eq();
		;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1374 "./src/parser/parser.y"
    {
			g_op->neq();
		;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1388 "./src/parser/parser.y"
    {
			g_op->add();
		;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1392 "./src/parser/parser.y"
    {
			g_op->sub();
		;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1396 "./src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(2) - (2)].integer));
			g_op->add();
		;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1401 "./src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(2) - (2)].cp));
			g_op->add();
		;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1406 "./src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(2) - (2)].real));
			g_op->add();
		;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1416 "./src/parser/parser.y"
    {
			g_op->mul();
		;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1420 "./src/parser/parser.y"
    {
			g_op->div();
		;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1424 "./src/parser/parser.y"
    {
			g_op->mod();
		;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1433 "./src/parser/parser.y"
    {
			unary_minus = true;
		;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1437 "./src/parser/parser.y"
    {
			if (unary_minus)
				g_op->minus();

			unary_minus = false;
		;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1450 "./src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (3)].integer));
		;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1454 "./src/parser/parser.y"
    {
			g_op->make_list(-2);
		;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1458 "./src/parser/parser.y"
    {
			g_op->make_list(-3);
		;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1467 "./src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (3)].integer));
		;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1471 "./src/parser/parser.y"
    {
			g_op->make_tuple(-2);
		;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1475 "./src/parser/parser.y"
    {
			g_op->make_tuple(-3);
		;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1483 "./src/parser/parser.y"
    {
			g_op->make_map((yyvsp[(2) - (3)].integer));
		;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1491 "./src/parser/parser.y"
    {
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1496 "./src/parser/parser.y"
    {
			g_ctl->sbf_rule_start();
		;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1500 "./src/parser/parser.y"
    {
			g_ctl->sbf_end();
			g_lvar_nil_check++;
		;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1520 "./src/parser/parser.y"
    {
			g_ctl->sbf_rule();
		;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1524 "./src/parser/parser.y"
    {
			g_ctl->sbf_in();
		;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1532 "./src/parser/parser.y"
    {
			g_ctl->sbf_list_gen((yyvsp[(1) - (3)].cp));
		;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1536 "./src/parser/parser.y"
    {
			g_ctl->sbf_range_gen((yyvsp[(1) - (3)].cp));
		;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1545 "./src/parser/parser.y"
    {
			g_op->push_integer(1);
		;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1553 "./src/parser/parser.y"
    {
			g_op->push_nil();
		;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1557 "./src/parser/parser.y"
    {
			g_op->push_nil();
		;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1566 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1570 "./src/parser/parser.y"
    {
			(yyval.integer) = 1;
		;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1586 "./src/parser/parser.y"
    {
			if (g_op->check_lvar((yyvsp[(1) - (1)].cp)) == false) {
				string msg = "variable ";
				msg += (yyvsp[(1) - (1)].cp);
				msg += " is not defined";
				yyerror(msg.c_str());
			}

			g_op->push_lvar((yyvsp[(1) - (1)].cp));
		;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1597 "./src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1601 "./src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1605 "./src/parser/parser.y"
    {
			g_op->push_bignum('+', (yyvsp[(1) - (1)].cp));
		;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1609 "./src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(1) - (1)].cp));
		;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1613 "./src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1617 "./src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1621 "./src/parser/parser.y"
    {
			g_op->make_regex();
		;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1625 "./src/parser/parser.y"
    {
			// already in stack
		;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1629 "./src/parser/parser.y"
    {
			g_op->push_reserved((yyvsp[(1) - (1)].integer));
		;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1633 "./src/parser/parser.y"
    {
			g_op->push_boolean(true);
		;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1637 "./src/parser/parser.y"
    {
			g_op->push_boolean(false);
		;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1641 "./src/parser/parser.y"
    {
			g_op->push_nil();
		;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1650 "./src/parser/parser.y"
    {
			g_op->set_last_find_position();
			g_op->find_member((yyvsp[(3) - (3)].cp));
		;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1655 "./src/parser/parser.y"
    {
			g_op->find_reserved((yyvsp[(3) - (3)].integer));
		;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1659 "./src/parser/parser.y"
    {
			g_op->clear_last_find_position();
		;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1663 "./src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (3)].integer));
		;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1667 "./src/parser/parser.y"
    {
			g_op->listat(false);
		;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1671 "./src/parser/parser.y"
    {
			g_op->listat(true);
		;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1675 "./src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1680 "./src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1685 "./src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1690 "./src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1695 "./src/parser/parser.y"
    {
			if (g_op->push_mvar_using_space((yyvsp[(1) - (1)].cp)) == false) {
				yyerror("invalid object name in name'string' format");
			}
		;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1701 "./src/parser/parser.y"
    {
			g_op->clone(1);
		;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1705 "./src/parser/parser.y"
    {
			g_op->clone((yyvsp[(4) - (4)].integer));

			// this is not normal function call (virtual function call)
			// so it should mark that don't fast popping
			g_op->disable_fast_pop();
		;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1718 "./src/parser/parser.y"
    {
			g_op->make_pair();
		;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1722 "./src/parser/parser.y"
    {
			g_op->push_integer(0);
		;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1726 "./src/parser/parser.y"
    {
			g_op->make_pair();
		;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 1730 "./src/parser/parser.y"
    {
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 1735 "./src/parser/parser.y"
    {
			g_op->push_integer(0);
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 1746 "./src/parser/parser.y"
    {
			(yyval.integer) = 0;
		;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 1750 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (3)].integer);
		;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 1758 "./src/parser/parser.y"
    {
			g_op->fix_last_find_position();
		;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 1766 "./src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_OWNER;
		;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 1770 "./src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_CALLER;
		;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 1774 "./src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_ROOT;
		;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 1778 "./src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MODULE;
		;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 1782 "./src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MY;
		;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 1790 "./src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 1799 "./src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 1808 "./src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 1816 "./src/parser/parser.y"
    {
			g_op->add();

			g_op->push_string((yyvsp[(4) - (4)].cp));

			g_op->add();
		;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 1828 "./src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 1837 "./src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 1842 "./src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 1850 "./src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 1858 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 1866 "./src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 1874 "./src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 1882 "./src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 1890 "./src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 1898 "./src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		;}
    break;



/* Line 1455 of yacc.c  */
#line 4620 "./src/parser/parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1904 "./src/parser/parser.y"




