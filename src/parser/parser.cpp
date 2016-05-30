/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 11 "../src/parser/parser.y"

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


/* Line 371 of yacc.c  */
#line 102 "../src/parser/parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
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
     PURE = 306,
     NIL_ = 307,
     RIGHT_ARROW = 308,
     LEFT_ARROW = 309,
     PARALLEL = 310,
     ASSIGNMENT = 311,
     ONCE = 312,
     NAME = 313,
     STRING = 314,
     FORMAT_STRING_HEAD = 315,
     FORMAT_STRING_TAIL = 316,
     RE_STRING = 317,
     RE_FORMAT_STRING_HEAD = 318,
     HEX_STRING = 319,
     SHELL_STRING_HEAD = 320,
     CONTEXT = 321,
     NUMBER = 322,
     MINUS_NUMBER = 323,
     BIG_NUMBER = 324,
     MINUS_BIG_NUMBER = 325,
     REAL = 326,
     MINUS_REAL = 327
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 46 "../src/parser/parser.y"

	const char* cp;
	int integer;
	double real;
	void* vector_cp;	
	struct bnf* bp;	
	struct cp2_t cp2; 
	struct int2_t int2;


/* Line 387 of yacc.c  */
#line 228 "../src/parser/parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_SRC_PARSER_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 256 "../src/parser/parser.cpp"

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  160
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1859

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  160
/* YYNRULES -- Number of rules.  */
#define YYNRULES  317
/* YYNRULES -- Number of states.  */
#define YYNSTATES  507

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
     356,   358,   362,   365,   366,   369,   370,   373,   377,   381,
     387,   391,   393,   395,   398,   402,   405,   408,   410,   411,
     412,   419,   420,   425,   426,   432,   433,   440,   441,   447,
     448,   449,   456,   457,   465,   468,   472,   474,   478,   482,
     484,   486,   488,   489,   494,   495,   502,   503,   510,   511,
     519,   520,   528,   529,   535,   536,   542,   543,   549,   550,
     556,   558,   560,   562,   564,   566,   568,   570,   571,   576,
     578,   579,   584,   586,   589,   591,   595,   599,   603,   607,
     611,   615,   617,   619,   623,   627,   630,   633,   636,   638,
     642,   646,   650,   652,   653,   657,   660,   662,   666,   672,
     680,   682,   686,   692,   700,   704,   705,   706,   715,   717,
     721,   723,   725,   727,   731,   735,   739,   741,   745,   748,
     749,   753,   757,   759,   763,   765,   767,   769,   771,   773,
     775,   777,   779,   781,   783,   785,   787,   789,   791,   793,
     795,   797,   801,   805,   809,   810,   814,   819,   824,   827,
     830,   833,   836,   837,   841,   846,   848,   852,   853,   857,
     860,   862,   864,   867,   871,   873,   875,   877,   879,   881,
     883,   885,   888,   890,   893,   895,   900,   902,   904,   906,
     908,   910,   912,   914,   916,   918,   920,   922
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      94,     0,    -1,    94,    98,    -1,    94,    96,    -1,    98,
      -1,    98,    -1,    96,    -1,    73,    94,    74,    -1,    73,
      74,    -1,    94,    74,    -1,    74,    -1,   189,    -1,   124,
      -1,   126,    -1,   153,    -1,   158,    -1,   109,    -1,   121,
      -1,   105,    -1,   106,    -1,    99,    -1,   101,    -1,   129,
      -1,   123,    -1,    75,    -1,    -1,   192,   100,    96,    -1,
      -1,    55,    16,   102,    95,    -1,    -1,    55,    22,   240,
      23,   238,   104,    76,   103,    95,    -1,    -1,    58,   192,
      -1,    58,   192,    58,   192,    -1,   238,    76,   190,    75,
      -1,    -1,   107,   108,    -1,   108,   243,    -1,    65,    -1,
     110,   112,    -1,   120,    -1,    -1,    35,   111,    96,    -1,
      -1,   115,   113,   114,    -1,   115,    -1,    37,    96,    -1,
     115,   116,    -1,   116,    -1,    -1,    36,   122,   117,    96,
      -1,    -1,    36,   122,    76,   170,   118,    96,    -1,    -1,
      36,   119,    96,    -1,    38,   122,    75,    -1,    38,   122,
      77,   190,    75,    -1,    42,   122,    75,    -1,    42,   122,
      59,    75,    -1,   122,    78,   157,    -1,   157,    -1,    40,
      -1,    41,    -1,    24,   125,    75,    -1,    25,    75,    -1,
      26,    75,    -1,    -1,   190,    -1,   171,    -1,   127,    -1,
      -1,    20,   192,   128,    73,   144,    74,    -1,    -1,    21,
       5,   157,   169,   130,    73,   131,    74,    -1,   131,   132,
      -1,   132,    -1,    -1,   135,   133,    76,   134,    75,    -1,
      79,    76,   141,    75,    -1,   134,    80,   136,    -1,   136,
      -1,   142,    -1,    -1,   137,   138,    -1,   139,    -1,   139,
     140,    -1,   140,    -1,   141,    -1,   142,    -1,   143,    -1,
      59,    -1,    62,    -1,   246,    -1,   164,    -1,   144,   145,
      -1,   145,    -1,    -1,    -1,   146,   148,    53,   147,    95,
      -1,   150,    -1,   149,    -1,   152,    76,   152,    -1,   150,
      77,   151,    -1,   151,    -1,   192,    -1,   152,    -1,   152,
      81,   192,    -1,    82,   240,    -1,   187,    -1,   180,    -1,
     184,    -1,   182,    -1,   154,   155,    -1,   155,    -1,     4,
      -1,    51,    -1,   154,     5,    -1,     5,    -1,   246,    -1,
      59,    -1,   156,   157,    75,    -1,    -1,   156,   157,    56,
     159,   192,    75,    -1,    -1,   166,   168,   160,    96,    -1,
      -1,    20,   166,   161,    73,   144,    74,    -1,    -1,    57,
     163,    97,    -1,   167,    96,    -1,    66,    -1,   156,   157,
     169,    -1,   156,   169,    -1,    -1,    76,   190,    -1,    -1,
      83,    84,    -1,    83,    46,    84,    -1,    83,   170,    84,
      -1,    83,   170,    77,    46,    84,    -1,   170,    77,   246,
      -1,   246,    -1,   178,    -1,   178,   176,    -1,   178,   172,
     176,    -1,   178,   172,    -1,   172,   173,    -1,   173,    -1,
      -1,    -1,    14,   174,   204,    76,   175,    95,    -1,    -1,
      15,    76,   177,    95,    -1,    -1,    13,   204,    76,   179,
      95,    -1,    -1,    16,   181,    95,    17,   204,    75,    -1,
      -1,   192,    18,    16,   183,    95,    -1,    -1,    -1,    17,
     185,   204,    76,   186,    95,    -1,    -1,    22,   240,    23,
     238,    76,   188,    95,    -1,   190,    75,    -1,   190,    77,
     192,    -1,   192,    -1,   191,    77,   192,    -1,   192,    77,
     192,    -1,   193,    -1,   165,    -1,   162,    -1,    -1,   240,
     203,   194,   192,    -1,    -1,   232,    78,   157,   203,   195,
     192,    -1,    -1,   232,    78,   239,   203,   196,   192,    -1,
      -1,   232,    85,   235,    86,   203,   197,   192,    -1,    -1,
     232,    85,   235,    84,   203,   198,   192,    -1,    -1,    45,
     157,   203,   199,   192,    -1,    -1,    45,   239,   203,   200,
     192,    -1,    -1,    78,   157,   203,   201,   192,    -1,    -1,
      78,   239,   203,   202,   192,    -1,   204,    -1,    81,    -1,
      47,    -1,    48,    -1,    49,    -1,    50,    -1,   205,    -1,
      -1,   205,    30,   206,   207,    -1,   207,    -1,    -1,   207,
      29,   208,   209,    -1,   209,    -1,    87,   210,    -1,   210,
      -1,   211,    31,   211,    -1,   211,    32,   211,    -1,   211,
      33,   211,    -1,   211,    34,   211,    -1,   211,    27,   211,
      -1,   211,    28,   211,    -1,   211,    -1,   212,    -1,   212,
      88,   213,    -1,   212,    89,   213,    -1,   212,   247,    -1,
     212,   249,    -1,   212,   252,    -1,   213,    -1,   213,    90,
     238,    -1,   213,    91,   238,    -1,   213,    82,   238,    -1,
     214,    -1,    -1,    89,   215,   238,    -1,    88,   238,    -1,
     238,    -1,    85,   125,    86,    -1,    85,   192,    45,   192,
      86,    -1,    85,   192,    45,   192,    76,   192,    86,    -1,
     219,    -1,    83,   191,    84,    -1,    83,   192,    45,   192,
      84,    -1,    83,   192,    45,   192,    76,   192,    84,    -1,
      73,   229,    74,    -1,    -1,    -1,    82,    85,   220,   222,
      80,   221,   223,    86,    -1,   192,    -1,   223,    77,   224,
      -1,   224,    -1,   204,    -1,   225,    -1,   240,    54,   192,
      -1,   240,    54,   226,    -1,   227,    76,   192,    -1,   227,
      -1,   192,    79,   192,    -1,   192,    79,    -1,    -1,    79,
     228,   192,    -1,   229,    77,   230,    -1,   230,    -1,   192,
      76,   192,    -1,   216,    -1,   217,    -1,   218,    -1,   164,
      -1,   240,    -1,   248,    -1,   247,    -1,   250,    -1,   249,
      -1,   251,    -1,   252,    -1,   244,    -1,   245,    -1,   239,
      -1,    43,    -1,    44,    -1,    52,    -1,    83,   192,    84,
      -1,   232,    78,   157,    -1,   232,    78,   239,    -1,    -1,
     232,   233,   237,    -1,   232,    85,   235,    86,    -1,   232,
      85,   235,    84,    -1,    45,   157,    -1,    45,   239,    -1,
      78,   157,    -1,    78,   239,    -1,    -1,   246,   234,   245,
      -1,   232,    78,     6,   237,    -1,   231,    -1,   192,    76,
     192,    -1,    -1,    76,   236,   192,    -1,   192,    76,    -1,
      76,    -1,   192,    -1,    83,    84,    -1,    83,   190,    84,
      -1,   232,    -1,     8,    -1,     9,    -1,    10,    -1,    11,
      -1,     7,    -1,   246,    -1,   241,   243,    -1,    60,    -1,
     242,   243,    -1,    63,    -1,    92,    73,   192,    61,    -1,
      62,    -1,   242,    -1,    59,    -1,   241,    -1,    64,    -1,
      58,    -1,    68,    -1,    67,    -1,    70,    -1,    69,    -1,
      71,    -1,    72,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   180,   180,   181,   182,   187,   188,   193,   194,   199,
     200,   205,   215,   216,   217,   218,   219,   220,   221,   225,
     229,   230,   231,   232,   233,   239,   238,   251,   250,   259,
     258,   270,   274,   288,   302,   310,   310,   323,   324,   332,
     336,   342,   341,   354,   353,   361,   366,   371,   372,   378,
     377,   386,   385,   395,   394,   406,   410,   418,   422,   430,
     436,   444,   448,   456,   460,   464,   473,   476,   484,   485,
     491,   490,   503,   502,   533,   534,   540,   539,   547,   557,
     558,   563,   568,   568,   577,   582,   587,   595,   596,   597,
     602,   606,   614,   624,   632,   633,   638,   642,   638,   653,
     654,   659,   667,   671,   679,   683,   687,   695,   703,   704,
     705,   706,   711,   715,   723,   727,   735,   739,   747,   751,
     759,   764,   763,   777,   776,   787,   786,   801,   800,   812,
     822,   831,   856,   889,   892,   901,   904,   908,   914,   918,
     928,   934,   944,   948,   952,   958,   968,   972,   981,   985,
     980,   994,   993,  1003,  1002,  1012,  1011,  1024,  1023,  1036,
    1040,  1035,  1052,  1051,  1063,  1071,  1075,  1083,  1087,  1095,
    1096,  1097,  1103,  1102,  1121,  1120,  1141,  1140,  1160,  1159,
    1184,  1183,  1208,  1207,  1229,  1228,  1250,  1249,  1271,  1270,
    1291,  1296,  1300,  1304,  1308,  1312,  1320,  1326,  1325,  1335,
    1341,  1340,  1350,  1355,  1359,  1364,  1368,  1372,  1376,  1380,
    1384,  1388,  1393,  1398,  1402,  1406,  1411,  1416,  1421,  1426,
    1430,  1434,  1438,  1444,  1443,  1454,  1455,  1460,  1464,  1468,
    1472,  1477,  1481,  1485,  1493,  1502,  1507,  1501,  1519,  1524,
    1525,  1530,  1534,  1542,  1546,  1554,  1555,  1563,  1564,  1569,
    1568,  1577,  1581,  1589,  1594,  1595,  1596,  1597,  1598,  1609,
    1613,  1617,  1621,  1625,  1629,  1633,  1637,  1641,  1645,  1649,
    1653,  1657,  1662,  1667,  1672,  1671,  1679,  1683,  1687,  1692,
    1697,  1702,  1708,  1707,  1717,  1725,  1730,  1735,  1734,  1742,
    1747,  1753,  1758,  1762,  1770,  1778,  1782,  1786,  1790,  1794,
    1802,  1810,  1811,  1819,  1820,  1828,  1840,  1844,  1849,  1853,
    1854,  1862,  1870,  1878,  1886,  1894,  1902,  1910
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
  "$@19", "lambda_object", "context_expr", "define_start",
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
  "big_number", "real", "minus_real", YY_NULL
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
     325,   326,   327,   123,   125,    59,    58,    44,    46,   126,
     124,    61,    37,    40,    41,    91,    93,    33,    43,    45,
      42,    47,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
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
     158,   159,   158,   160,   158,   161,   158,   163,   162,   164,
     165,   166,   167,   168,   168,   169,   169,   169,   169,   169,
     170,   170,   171,   171,   171,   171,   172,   172,   174,   175,
     173,   177,   176,   179,   178,   181,   180,   183,   182,   185,
     186,   184,   188,   187,   189,   190,   190,   191,   191,   192,
     192,   192,   194,   193,   195,   193,   196,   193,   197,   193,
     198,   193,   199,   193,   200,   193,   201,   193,   202,   193,
     193,   203,   203,   203,   203,   203,   204,   206,   205,   205,
     208,   207,   207,   209,   209,   210,   210,   210,   210,   210,
     210,   210,   211,   212,   212,   212,   212,   212,   212,   213,
     213,   213,   213,   215,   214,   214,   214,   216,   216,   216,
     216,   217,   217,   217,   218,   220,   221,   219,   222,   223,
     223,   224,   224,   225,   225,   226,   226,   227,   227,   228,
     227,   229,   229,   230,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   232,   232,   233,   232,   232,   232,   232,   232,
     232,   232,   234,   232,   232,   232,   235,   236,   235,   235,
     235,   235,   237,   237,   238,   239,   239,   239,   239,   239,
     240,   241,   241,   242,   242,   243,   244,   244,   245,   245,
     245,   246,   247,   248,   249,   250,   251,   252
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
       1,     3,     2,     0,     2,     0,     2,     3,     3,     5,
       3,     1,     1,     2,     3,     2,     2,     1,     0,     0,
       6,     0,     4,     0,     5,     0,     6,     0,     5,     0,
       0,     6,     0,     7,     2,     3,     1,     3,     3,     1,
       1,     1,     0,     4,     0,     6,     0,     6,     0,     7,
       0,     7,     0,     5,     0,     5,     0,     5,     0,     5,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       0,     4,     1,     2,     1,     3,     3,     3,     3,     3,
       3,     1,     1,     3,     3,     2,     2,     2,     1,     3,
       3,     3,     1,     0,     3,     2,     1,     3,     5,     7,
       1,     3,     5,     7,     3,     0,     0,     8,     1,     3,
       1,     1,     1,     3,     3,     3,     1,     3,     2,     0,
       3,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     3,     4,     4,     2,     2,
       2,     2,     0,     3,     4,     1,     3,     0,     3,     2,
       1,     1,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      35,   114,   117,   299,   295,   296,   297,   298,     0,   155,
     159,     0,     0,     0,    66,     0,     0,    41,     0,    61,
      62,     0,   268,   269,     0,   115,   270,     0,   127,   311,
     308,   302,   306,   304,   310,   130,   313,   312,   315,   314,
     316,   317,     0,    24,     0,     0,     0,    66,     0,     0,
     223,    35,     4,    20,    21,    18,    19,     0,    16,     0,
      40,    17,    23,    12,    13,    69,    22,    14,     0,   113,
     135,    15,   171,   257,   170,   133,     0,    68,   142,   109,
     111,   110,   108,    11,     0,   166,   169,   190,   196,   199,
     202,   204,   211,   212,   218,   222,   254,   255,   256,   230,
     285,   294,   226,   267,   258,   309,   307,   265,   266,   300,
     260,   259,   262,   261,   263,   264,     0,     0,   135,     0,
     294,   226,   258,    35,     0,   135,   125,    70,     0,     0,
     300,     0,    67,   166,    64,    65,     0,   119,     0,    60,
     118,     0,   278,   279,    27,     0,    35,     0,     0,   252,
     280,   281,   235,     0,     0,     0,   166,   203,   225,     0,
       1,    35,     3,     2,    38,    36,    53,    39,    45,    48,
     116,   112,     0,   135,   132,     0,   123,    35,   129,   148,
       0,   145,   147,   143,   164,     0,     0,     0,   197,   200,
       0,     0,     0,     0,     0,     0,     0,     0,   215,   216,
     217,     0,     0,     0,     0,     0,     0,     0,   192,   193,
     194,   195,   191,   172,     0,   301,   303,     0,   278,   279,
     280,   281,   153,     0,     0,     0,     6,     5,     0,   135,
       0,     0,   135,     0,    63,    42,    55,     0,     0,     0,
      57,   182,   184,    35,     0,    10,    35,   128,     0,   234,
       0,   186,   188,     0,     0,   231,     0,     0,   271,   227,
       0,   224,     8,    35,   166,    37,     0,    49,     0,    47,
       0,   136,     0,   141,   121,   120,   131,   134,     0,     0,
     151,   146,   144,   165,   157,    26,     0,     0,   209,   210,
     205,   206,   207,   208,   213,   214,   221,   219,   220,     0,
     272,   273,   287,   291,     0,     0,   275,     0,     0,     0,
     283,    35,   272,   273,     0,     0,   160,    96,    96,    72,
       0,     0,    59,    58,     0,     0,    28,     0,     9,   253,
     251,     0,     0,   238,     0,   167,     0,   168,     0,     7,
      54,     0,     0,     0,    44,   137,     0,   138,     0,   124,
       0,    35,    35,   198,   201,   284,   174,   176,     0,   289,
     277,   276,   292,     0,    34,   173,     0,   154,   277,   276,
       0,    35,    96,    95,     0,    96,     0,   162,    56,   183,
     185,    31,   187,   189,   236,     0,   232,     0,   228,    51,
      50,    46,     0,   140,     0,   149,   152,   158,     0,     0,
     288,   286,   180,   178,   293,   305,   156,   161,   126,    94,
       0,     0,   100,    99,   103,   105,   104,    71,     0,    35,
       0,     0,     0,     0,     0,     0,     0,   139,   122,    35,
     175,   177,     0,     0,   107,    97,     0,     0,     0,     0,
       0,    75,    76,    81,    92,   163,    32,    29,   241,     0,
     240,   242,   258,   233,   229,    52,   150,   181,   179,    35,
     102,   105,     0,   101,   106,     0,    73,    74,     0,     0,
      35,     0,   237,     0,    98,    90,    91,     0,    82,    33,
      30,   239,   249,   243,   244,   246,    78,     0,    80,     0,
       0,   248,     0,    77,    82,    83,    84,    86,    87,    88,
      89,    93,   250,   247,   245,    79,    85
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   263,   225,   226,   247,   227,    53,   187,    54,   243,
     470,   421,    55,    56,    57,   165,    58,    59,   136,   167,
     268,   344,   168,   169,   342,   426,   266,    60,    61,   138,
      62,    63,   131,    64,    65,   231,    66,   376,   440,   441,
     468,   487,   442,   488,   489,   495,   496,   497,   498,   443,
     500,   372,   373,   374,   459,   411,   412,   413,   414,   415,
      67,    68,    69,   118,   139,    71,   348,   278,   230,    72,
     146,    73,    74,    75,    76,   176,   174,   272,    77,   181,
     182,   279,   429,   183,   351,    78,   311,    79,   123,    80,
     352,    81,   124,   371,    82,   419,    83,    84,   153,    85,
      86,   308,   398,   399,   433,   432,   324,   325,   331,   332,
     213,    87,    88,   286,    89,   287,    90,    91,    92,    93,
      94,    95,   159,    96,    97,    98,    99,   253,   422,   334,
     449,   450,   451,   484,   485,   490,   148,   149,   100,   101,
     206,   217,   304,   358,   306,   121,   103,   104,   105,   106,
     215,   107,   108,   109,   110,   111,   112,   113,   114,   115
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -374
static const yytype_int16 yypact[] =
{
    1086,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  1688,  -374,
    -374,  1516,    21,   -28,  1516,   -34,   -12,  -374,    86,  -374,
    -374,    86,  -374,  -374,    99,  -374,  -374,    73,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  1516,  -374,    99,     6,  1516,  1516,   510,  1774,
    -374,   641,  -374,  -374,  -374,  -374,  -374,     7,  -374,   124,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,    15,  -374,
     -25,  -374,  -374,  -374,  -374,    24,    49,  -374,   194,  -374,
    -374,  -374,  -374,  -374,   115,     0,  -374,  -374,   143,   125,
    -374,  -374,   185,    96,    47,  -374,  -374,  -374,  -374,  -374,
    -374,    64,   107,  -374,    36,   128,   128,  -374,  -374,   147,
    -374,  -374,  -374,  -374,  -374,  -374,    99,    99,   159,   150,
      91,  -374,  -374,  1172,  1688,   -25,  -374,  -374,    86,   226,
    -374,   183,   187,  -374,  -374,  -374,    49,  -374,   146,  -374,
    -374,    55,    36,    36,  -374,   -28,   742,   212,   104,  -374,
      36,    36,  -374,    17,   -16,   196,   244,  -374,  -374,  1774,
    -374,   828,  -374,  -374,  -374,   128,    86,  -374,   200,  -374,
    -374,  -374,    -2,    43,  -374,  1516,  -374,   828,  -374,  -374,
     214,   194,  -374,  -374,  -374,  1516,   275,    49,  -374,  -374,
     510,   510,   510,   510,   510,   510,   510,   510,  -374,  -374,
    -374,  1774,  1774,  1774,    39,  1258,   210,  1516,  -374,  -374,
    -374,  -374,  -374,  -374,   221,  -374,  -374,   193,  -374,  -374,
    -374,  -374,  -374,    39,  1258,   279,  -374,  -374,   224,   159,
     228,   229,   159,  1774,  -374,  -374,  -374,  1516,    86,   230,
    -374,  -374,  -374,  1172,   280,  -374,   914,  -374,  1516,  -374,
    1516,  -374,  -374,  1516,  1516,  -374,  1516,  1516,  -374,  -374,
    1516,  -374,  -374,  1000,    20,  -374,    49,   118,   267,  -374,
     222,  -374,   103,  -374,  -374,  -374,  -374,   187,    49,  1688,
    -374,  -374,  -374,  -374,  -374,  -374,  1688,  1688,  -374,  -374,
    -374,  -374,  -374,  -374,    47,    47,  -374,  -374,  -374,   210,
      36,    36,   116,   231,   177,  1344,  -374,   198,  1516,  1516,
    -374,  1172,  -374,  -374,   192,  1688,  -374,  -374,  -374,  -374,
     232,   206,  -374,  -374,  1516,  1516,  -374,  1774,  -374,  -374,
    -374,  1516,  1516,  -374,   236,  -374,    29,  -374,    -7,  -374,
    -374,   -28,    49,    49,  -374,  -374,   -18,  -374,  1516,  -374,
     233,  1172,  1172,   125,  -374,  -374,  -374,  -374,  1516,  1516,
      36,    36,  -374,   105,  -374,  -374,   250,  -374,  -374,  -374,
     237,  1172,   243,  -374,  1602,   245,   247,  -374,  -374,  -374,
    -374,   266,  -374,  -374,  -374,  1516,  -374,  1516,  -374,   248,
    -374,  -374,   242,  -374,   255,  -374,  -374,  -374,  1516,  1516,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
     -33,   278,  -374,   257,  -374,    60,  -374,  -374,    -4,  1172,
    1516,   256,  1688,   251,   253,   -28,    49,  -374,  -374,  1172,
    -374,  -374,  1516,  1516,  -374,  -374,  1602,   254,  1516,   261,
     -15,  -374,  -374,  -374,  -374,  -374,   283,  -374,  -374,    25,
    -374,  -374,   288,  -374,  -374,  -374,  -374,  -374,  -374,  1172,
    -374,   262,   -28,  -374,  -374,   171,  -374,  -374,   268,  1516,
    1172,  1688,  -374,  1430,  -374,  -374,  -374,   270,  -374,  -374,
    -374,  -374,  -374,   271,  -374,   276,  -374,    12,  -374,    19,
    1516,  1516,  1516,  -374,  -374,  -374,    19,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -374,    10,  -231,    14,  -374,     9,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,   178,  -374,  -374,  -374,  -374,  -374,   -14,
    -374,  -374,   300,  -374,  -374,  -374,  -374,  -374,  -374,   -85,
    -374,  -374,  -374,  -143,  -374,  -374,  -374,  -136,  -104,  -373,
    -374,    44,  -121,  -374,  -374,  -374,  -374,  -374,   -73,  -152,
    -374,  -374,   297,    16,    18,  -374,  -374,  -374,  -374,  -374,
    -374,  -365,  -374,   355,  -374,  -374,  -158,    28,  -374,  -374,
     189,  -374,  -374,   190,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,    -8,  -374,   -10,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -129,    -5,  -374,  -374,    88,  -374,    85,   328,    76,  -374,
      90,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,   -93,  -374,  -374,  -374,  -374,  -374,   129,  -374,   332,
    -374,  -374,   158,  -374,    84,     2,    11,   310,  -374,  -374,
     -89,  -374,   167,   -13,   292,  -374,   293,  -374,  -374,   298
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -291
static const yytype_int16 yytable[] =
{
     130,   127,   102,   119,   133,   140,   132,   141,   140,    52,
      51,   140,   326,   241,   242,   276,    70,   216,   186,     1,
     170,   251,   252,     1,     2,    29,   128,   125,   392,   256,
      29,   140,   147,    29,   137,   143,   154,   156,   186,   132,
      29,   134,   142,    29,   270,   299,     3,     4,     5,     6,
       7,   158,   152,   102,    29,   151,    29,   140,   172,   466,
     163,   257,   150,   135,   439,   162,    25,    70,   258,   387,
      25,   276,   164,   -25,   319,   439,   265,    29,   475,   388,
     367,   476,   271,   208,   209,   210,   211,   493,   173,   144,
     178,   152,   494,   -25,   254,   145,   248,    29,   137,   274,
     175,   255,   471,   140,   140,   385,     3,     4,     5,     6,
       7,   472,   140,   386,   239,   140,   499,   212,   275,   228,
     396,   397,   177,   499,   501,   102,   172,   219,   221,   201,
     240,   501,   130,   238,   218,   220,   437,   202,   203,    70,
     407,   438,   204,   229,    29,   137,   232,  -274,   102,   205,
     235,   264,   267,   140,   189,    52,   246,    29,   137,   273,
     166,   261,    70,   102,    37,   133,    39,   277,    41,   223,
      52,   356,   357,   188,  -274,   283,   224,    70,   249,   102,
     346,   250,   185,   207,   196,   197,    52,   347,   445,   404,
     184,   140,   185,    70,   341,   303,   238,   133,   456,   307,
    -290,   285,  -290,   296,   297,   298,  -282,  -282,   179,   180,
     140,  -282,   190,   191,   303,   301,   192,   193,   194,   195,
     214,   236,   300,   237,   238,   140,   222,   133,   474,   321,
     475,   402,   403,   476,   313,   320,   166,   -43,   329,   480,
     147,   312,   172,   333,   335,   102,   336,   337,   102,   233,
     338,   409,    30,    31,   409,   163,   322,    34,   234,    70,
     162,   360,    70,   361,   185,   102,   288,   289,   290,   291,
     292,   293,   163,   364,   350,   185,   368,   162,   369,    70,
     340,   378,   259,   185,   461,   463,   294,   295,   248,   260,
     280,   284,   349,   305,   309,   133,   315,   363,   365,   366,
     316,   317,   318,   327,   343,   323,   345,   359,   377,   395,
     370,   405,   406,   102,   379,   380,   384,   408,   122,   417,
     418,   382,   383,   129,   420,   425,   427,    70,   273,   381,
     428,   435,   447,   393,   436,   453,   462,   465,   394,   454,
     120,   469,   473,   438,   478,   486,   269,   155,   400,   401,
     491,   505,   492,   102,   102,   467,   390,   391,   122,   122,
     506,   477,   375,   460,   416,   171,   126,    70,    70,   389,
     281,   282,   354,   102,   353,   423,   157,   424,   481,   330,
     120,   120,   314,   355,   310,   198,   199,    70,   430,   431,
       0,   200,     0,     0,     0,     0,     0,   130,     0,     0,
       0,     0,     0,     0,     0,   444,     0,     0,     0,     0,
     446,     0,   393,     0,     0,     0,     0,   448,     0,     0,
       0,   102,   457,   458,     0,     0,   416,   444,   464,     0,
       0,   102,     0,     0,   122,    70,     0,     0,     0,     0,
     455,     0,     0,     0,     0,    70,     0,     0,     0,   130,
       0,     0,     0,     0,     0,   244,   120,     0,     0,   479,
       0,   102,     0,   483,     0,     0,   448,     0,     0,   122,
       0,     0,   102,     0,     0,    70,   444,     0,     0,     0,
     502,   503,   504,   444,     0,     0,    70,     0,     0,     0,
       0,   120,     0,     0,     0,     0,     0,     0,     0,     0,
     122,   122,   122,   122,   122,   122,   122,   122,     0,     0,
       0,   122,   122,   122,     1,     2,     0,     3,     4,     5,
       6,     7,   120,   120,   120,   120,   120,   120,   120,   120,
       0,     0,     0,   120,   120,   120,     0,     0,     0,     0,
       0,     0,     0,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    23,   116,     0,     0,     0,     0,
       0,    25,    26,     0,     0,   120,     0,     0,    29,    30,
      31,     0,    32,    33,    34,     0,     0,    36,    37,    38,
      39,    40,    41,    42,     0,     0,     0,     0,   117,   122,
       0,     0,    45,    46,     0,    47,   122,   122,    49,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120,     0,     0,     0,     0,     0,     0,   120,   120,
       0,     0,     0,     0,     0,   122,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   122,     0,     0,
       0,   160,     0,     0,     0,     1,     2,   120,     3,     4,
       5,     6,     7,     0,     8,     0,     0,     9,    10,   120,
       0,    11,    12,    13,     0,    14,    15,    16,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,     0,    18,
       0,    19,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,    25,    26,     0,     0,    27,     0,    28,    29,
      30,    31,     0,    32,    33,    34,     0,    35,    36,    37,
      38,    39,    40,    41,   161,     0,    43,     0,     0,    44,
     434,     0,     0,    45,    46,     0,    47,     0,    48,    49,
      50,     0,   452,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     2,     0,     3,
       4,     5,     6,     7,   120,     8,     0,     0,     9,    10,
       0,     0,    11,    12,    13,     0,    14,    15,    16,     0,
       0,     0,   434,     0,     0,     0,     0,    17,     0,     0,
      18,   452,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,     0,    25,    26,     0,     0,    27,     0,    28,
      29,    30,    31,   120,    32,    33,    34,     0,    35,    36,
      37,    38,    39,    40,    41,    42,   245,    43,     0,     0,
      44,     0,     0,     0,    45,    46,     0,    47,     0,    48,
      49,    50,     1,     2,     0,     3,     4,     5,     6,     7,
       0,     8,     0,     0,     9,    10,     0,     0,    11,    12,
      13,     0,    14,    15,    16,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,    18,     0,    19,    20,
      21,    22,    23,    24,     0,     0,     0,     0,     0,    25,
      26,     0,     0,    27,     0,    28,    29,    30,    31,     0,
      32,    33,    34,     0,    35,    36,    37,    38,    39,    40,
      41,    42,   262,    43,     0,     0,    44,     0,     0,     0,
      45,    46,     0,    47,     0,    48,    49,    50,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     8,     0,     0,
       9,    10,     0,     0,    11,    12,    13,     0,    14,    15,
      16,     0,     0,     0,     0,     0,     0,     0,     0,    17,
       0,     0,    18,     0,    19,    20,    21,    22,    23,    24,
       0,     0,     0,     0,     0,    25,    26,     0,     0,    27,
       0,    28,    29,    30,    31,     0,    32,    33,    34,     0,
      35,    36,    37,    38,    39,    40,    41,   161,   328,    43,
       0,     0,    44,     0,     0,     0,    45,    46,     0,    47,
       0,    48,    49,    50,     1,     2,     0,     3,     4,     5,
       6,     7,     0,     8,     0,     0,     9,    10,     0,     0,
      11,    12,    13,     0,    14,    15,    16,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,    18,     0,
      19,    20,    21,    22,    23,    24,     0,     0,     0,     0,
       0,    25,    26,     0,     0,    27,     0,    28,    29,    30,
      31,     0,    32,    33,    34,     0,    35,    36,    37,    38,
      39,    40,    41,   161,   339,    43,     0,     0,    44,     0,
       0,     0,    45,    46,     0,    47,     0,    48,    49,    50,
       1,     2,     0,     3,     4,     5,     6,     7,     0,     8,
       0,     0,     9,    10,     0,     0,    11,    12,    13,     0,
      14,    15,    16,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,     0,    18,     0,    19,    20,    21,    22,
      23,    24,     0,     0,     0,     0,     0,    25,    26,     0,
       0,    27,     0,    28,    29,    30,    31,     0,    32,    33,
      34,     0,    35,    36,    37,    38,    39,    40,    41,    42,
       0,    43,     0,     0,    44,     0,     0,     0,    45,    46,
       0,    47,     0,    48,    49,    50,     1,     2,     0,     3,
       4,     5,     6,     7,     0,     8,     0,     0,     9,    10,
       0,     0,    11,    12,    13,     0,    14,    15,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
      18,     0,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,     0,    25,    26,     0,     0,    27,     0,    28,
      29,    30,    31,     0,    32,    33,    34,     0,    35,    36,
      37,    38,    39,    40,    41,   161,     0,    43,     0,     0,
      44,     0,     0,     0,    45,    46,     0,    47,     0,    48,
      49,    50,     1,     2,     0,     3,     4,     5,     6,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,    23,    24,     0,     0,     0,     0,     0,    25,
      26,     0,     0,     0,     0,    28,    29,    30,    31,     0,
      32,    33,    34,     0,    35,    36,    37,    38,    39,    40,
      41,    42,     0,     0,   302,     0,    44,     0,     0,     0,
      45,    46,     0,    47,     0,    48,    49,    50,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,    24,
       0,     0,     0,     0,     0,    25,    26,     0,     0,     0,
       0,    28,    29,    30,    31,     0,    32,    33,    34,     0,
      35,    36,    37,    38,    39,    40,    41,    42,     0,     0,
       0,     0,    44,     0,     0,     0,    45,    46,   362,    47,
       0,    48,    49,    50,     1,     2,     0,     3,     4,     5,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    23,    24,     0,     0,     0,     0,
       0,    25,    26,     0,     0,     0,     0,    28,    29,    30,
      31,     0,    32,    33,    34,     0,    35,    36,    37,    38,
      39,    40,    41,    42,     0,     0,     0,     0,    44,   482,
       0,     0,    45,    46,     0,    47,     0,    48,    49,    50,
       1,     2,     0,     3,     4,     5,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
      23,    24,     0,     0,     0,     0,     0,    25,    26,     0,
       0,     0,     0,    28,    29,    30,    31,     0,    32,    33,
      34,     0,    35,    36,    37,    38,    39,    40,    41,    42,
       0,     0,     0,     0,    44,     0,     0,     0,    45,    46,
       0,    47,     0,    48,    49,    50,     1,     2,     0,     3,
       4,     5,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,    23,    24,     0,     0,
       0,     0,     0,    25,    26,     0,     0,     0,     0,    28,
      29,    30,    31,     0,    32,    33,    34,     0,    35,    36,
      37,    38,    39,    40,    41,    42,     0,     0,     0,     0,
      44,     0,     0,     0,   410,    46,     0,    47,     0,    48,
      49,    50,     1,     2,     0,     3,     4,     5,     6,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,    23,   116,     0,     0,     0,     0,     0,    25,
      26,     0,     0,     0,     0,     0,    29,    30,    31,     0,
      32,    33,    34,     0,     0,    36,    37,    38,    39,    40,
      41,    42,     0,     0,     0,     0,   117,     0,     0,     0,
      45,    46,     0,    47,     0,    48,    49,    50,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,   116,
       0,     0,     0,     0,     0,    25,    26,     0,     0,     0,
       0,     0,    29,    30,    31,     0,    32,    33,    34,     0,
       0,    36,    37,    38,    39,    40,    41,    42,     0,     0,
       0,     0,   117,     0,     0,     0,    45,    46,     0,    47
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-374)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      13,    11,     0,     8,    14,    18,    14,    21,    21,     0,
       0,    24,   243,   142,   143,   173,     0,   106,    18,     4,
       5,   150,   151,     4,     5,    58,     5,    11,    46,    45,
      58,    44,    42,    58,    59,    24,    46,    47,    18,    47,
      58,    75,    24,    58,    46,     6,     7,     8,     9,    10,
      11,    49,    85,    51,    58,    44,    58,    70,    83,    74,
      51,    77,    44,    75,    79,    51,    51,    51,    84,    76,
      51,   229,    65,    73,   232,    79,   165,    58,    59,    86,
     311,    62,    84,    47,    48,    49,    50,    75,    70,    16,
      76,    85,    80,    73,    77,    22,    76,    58,    59,    56,
      76,    84,    77,   116,   117,    76,     7,     8,     9,    10,
      11,    86,   125,    84,    59,   128,   489,    81,    75,   124,
     351,   352,    73,   496,   489,   123,    83,   116,   117,    82,
      75,   496,   145,    78,   116,   117,    76,    90,    91,   123,
     371,    81,    78,   125,    58,    59,   128,    83,   146,    85,
     136,   161,   166,   166,    29,   146,   146,    58,    59,   172,
      36,   159,   146,   161,    68,   175,    70,   175,    72,    78,
     161,   300,   301,    30,    83,   185,    85,   161,    74,   177,
      77,    77,    77,    76,    88,    89,   177,    84,   419,    84,
      75,   204,    77,   177,    76,   205,    78,   207,   429,   207,
      84,   187,    86,   201,   202,   203,    59,    60,    14,    15,
     223,    64,    27,    28,   224,   204,    31,    32,    33,    34,
      92,    75,   204,    77,    78,   238,    76,   237,   459,   237,
      59,   360,   361,    62,   223,   233,    36,    37,   248,   470,
     250,   223,    83,   253,   254,   243,   256,   257,   246,    23,
     260,   372,    59,    60,   375,   246,   238,    64,    75,   243,
     246,    84,   246,    86,    77,   263,   190,   191,   192,   193,
     194,   195,   263,    75,   279,    77,    84,   263,    86,   263,
     266,    75,    86,    77,   436,   437,   196,   197,    76,    45,
      76,    16,   278,    83,    73,   305,    17,   305,   308,   309,
      76,    73,    73,    23,    37,    75,    84,    76,    76,    76,
     315,    61,    75,   311,   324,   325,    80,    74,     8,    74,
      73,   331,   332,    13,    58,    77,    84,   311,   341,   327,
      75,    53,    76,   346,    77,    84,    82,    76,   348,    86,
       8,    58,    54,    81,    76,    75,   168,    47,   358,   359,
      79,   494,    76,   351,   352,   440,   342,   343,    48,    49,
     496,   465,   318,   436,   374,    68,    11,   351,   352,   341,
     181,   181,   287,   371,   286,   385,    48,   387,   471,   250,
      48,    49,   224,   299,   217,    93,    93,   371,   398,   399,
      -1,    93,    -1,    -1,    -1,    -1,    -1,   410,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   418,    -1,    -1,    -1,    -1,
     420,    -1,   425,    -1,    -1,    -1,    -1,   422,    -1,    -1,
      -1,   419,   432,   433,    -1,    -1,   436,   440,   438,    -1,
      -1,   429,    -1,    -1,   124,   419,    -1,    -1,    -1,    -1,
     426,    -1,    -1,    -1,    -1,   429,    -1,    -1,    -1,   462,
      -1,    -1,    -1,    -1,    -1,   145,   124,    -1,    -1,   469,
      -1,   459,    -1,   473,    -1,    -1,   471,    -1,    -1,   159,
      -1,    -1,   470,    -1,    -1,   459,   489,    -1,    -1,    -1,
     490,   491,   492,   496,    -1,    -1,   470,    -1,    -1,    -1,
      -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     190,   191,   192,   193,   194,   195,   196,   197,    -1,    -1,
      -1,   201,   202,   203,     4,     5,    -1,     7,     8,     9,
      10,    11,   190,   191,   192,   193,   194,   195,   196,   197,
      -1,    -1,    -1,   201,   202,   203,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   233,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,   233,    -1,    -1,    58,    59,
      60,    -1,    62,    63,    64,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,   279,
      -1,    -1,    82,    83,    -1,    85,   286,   287,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   279,    -1,    -1,    -1,    -1,    -1,    -1,   286,   287,
      -1,    -1,    -1,    -1,    -1,   315,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   327,    -1,    -1,
      -1,     0,    -1,    -1,    -1,     4,     5,   315,     7,     8,
       9,    10,    11,    -1,    13,    -1,    -1,    16,    17,   327,
      -1,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,
      -1,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    52,    -1,    -1,    55,    -1,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    75,    -1,    -1,    78,
     410,    -1,    -1,    82,    83,    -1,    85,    -1,    87,    88,
      89,    -1,   422,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,     7,
       8,     9,    10,    11,   422,    13,    -1,    -1,    16,    17,
      -1,    -1,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,   462,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      38,   471,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    55,    -1,    57,
      58,    59,    60,   471,    62,    63,    64,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,
      88,    89,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    55,    -1,    57,    58,    59,    60,    -1,
      62,    63,    64,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    78,    -1,    -1,    -1,
      82,    83,    -1,    85,    -1,    87,    88,    89,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    13,    -1,    -1,
      16,    17,    -1,    -1,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    -1,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,
      -1,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,
      -1,    87,    88,    89,     4,     5,    -1,     7,     8,     9,
      10,    11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    55,    -1,    57,    58,    59,
      60,    -1,    62,    63,    64,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    78,    -1,
      -1,    -1,    82,    83,    -1,    85,    -1,    87,    88,    89,
       4,     5,    -1,     7,     8,     9,    10,    11,    -1,    13,
      -1,    -1,    16,    17,    -1,    -1,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    38,    -1,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    55,    -1,    57,    58,    59,    60,    -1,    62,    63,
      64,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,
      -1,    85,    -1,    87,    88,    89,     4,     5,    -1,     7,
       8,     9,    10,    11,    -1,    13,    -1,    -1,    16,    17,
      -1,    -1,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      38,    -1,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    55,    -1,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    75,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,
      88,    89,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    -1,
      62,    63,    64,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    76,    -1,    78,    -1,    -1,    -1,
      82,    83,    -1,    85,    -1,    87,    88,    89,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    82,    83,    84,    85,
      -1,    87,    88,    89,     4,     5,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    -1,    62,    63,    64,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,    79,
      -1,    -1,    82,    83,    -1,    85,    -1,    87,    88,    89,
       4,     5,    -1,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    -1,    62,    63,
      64,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,
      -1,    85,    -1,    87,    88,    89,     4,     5,    -1,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,
      88,    89,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    -1,
      62,    63,    64,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      82,    83,    -1,    85,    -1,    87,    88,    89,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    -1,    62,    63,    64,    -1,
      -1,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     7,     8,     9,    10,    11,    13,    16,
      17,    20,    21,    22,    24,    25,    26,    35,    38,    40,
      41,    42,    43,    44,    45,    51,    52,    55,    57,    58,
      59,    60,    62,    63,    64,    66,    67,    68,    69,    70,
      71,    72,    73,    75,    78,    82,    83,    85,    87,    88,
      89,    94,    98,    99,   101,   105,   106,   107,   109,   110,
     120,   121,   123,   124,   126,   127,   129,   153,   154,   155,
     156,   158,   162,   164,   165,   166,   167,   171,   178,   180,
     182,   184,   187,   189,   190,   192,   193,   204,   205,   207,
     209,   210,   211,   212,   213,   214,   216,   217,   218,   219,
     231,   232,   238,   239,   240,   241,   242,   244,   245,   246,
     247,   248,   249,   250,   251,   252,    45,    78,   156,   204,
     232,   238,   240,   181,   185,   156,   166,   192,     5,   240,
     246,   125,   190,   192,    75,    75,   111,    59,   122,   157,
     246,   122,   157,   239,    16,    22,   163,   192,   229,   230,
     157,   239,    85,   191,   192,   125,   192,   210,   238,   215,
       0,    73,    96,    98,    65,   108,    36,   112,   115,   116,
       5,   155,    83,   157,   169,    76,   168,    73,    96,    14,
      15,   172,   173,   176,    75,    77,    18,   100,    30,    29,
      27,    28,    31,    32,    33,    34,    88,    89,   247,   249,
     252,    82,    90,    91,    78,    85,   233,    76,    47,    48,
      49,    50,    81,   203,    92,   243,   243,   234,   157,   239,
     157,   239,    76,    78,    85,    95,    96,    98,   204,   157,
     161,   128,   157,    23,    75,    96,    75,    77,    78,    59,
      75,   203,   203,   102,   240,    74,    94,    97,    76,    74,
      77,   203,   203,   220,    77,    84,    45,    77,    84,    86,
      45,   238,    74,    94,   192,   243,   119,   122,   113,   116,
      46,    84,   170,   246,    56,    75,   169,   190,   160,   174,
      76,   173,   176,   192,    16,    96,   206,   208,   211,   211,
     211,   211,   211,   211,   213,   213,   238,   238,   238,     6,
     157,   239,    76,   192,   235,    83,   237,   190,   194,    73,
     245,   179,   157,   239,   235,    17,    76,    73,    73,   169,
     238,   190,   157,    75,   199,   200,    95,    23,    74,   192,
     230,   201,   202,   192,   222,   192,   192,   192,   192,    74,
      96,    76,   117,    37,   114,    84,    77,    84,   159,    96,
     204,   177,   183,   207,   209,   237,   203,   203,   236,    76,
      84,    86,    84,   190,    75,   192,   192,    95,    84,    86,
     204,   186,   144,   145,   146,   144,   130,    76,    75,   192,
     192,   238,   192,   192,    80,    76,    84,    76,    86,   170,
      96,    96,    46,   246,   192,    76,    95,    95,   195,   196,
     192,   192,   203,   203,    84,    61,    75,    95,    74,   145,
      82,   148,   149,   150,   151,   152,   192,    74,    73,   188,
      58,   104,   221,   192,   192,    77,   118,    84,    75,   175,
     192,   192,   198,   197,   240,    53,    77,    76,    81,    79,
     131,   132,   135,   142,   246,    95,   192,    76,   204,   223,
     224,   225,   240,    84,    86,    96,    95,   192,   192,   147,
     151,   152,    82,   152,   192,    76,    74,   132,   133,    58,
     103,    77,    86,    54,    95,    59,    62,   141,    76,   192,
      95,   224,    79,   192,   226,   227,    75,   134,   136,   137,
     228,    79,    76,    75,    80,   138,   139,   140,   141,   142,
     143,   164,   192,   192,   192,   136,   140
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

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
/* Line 1792 of yacc.c  */
#line 206 "../src/parser/parser.y"
    {
			if ((yyvsp[(1) - (1)].integer) > 1) {
				for(int i=0; i<(yyvsp[(1) - (1)].integer); i++)
					g_op->pop_stack();
			}
			else {
				g_op->fast_pop_stack();
			}
		}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 222 "../src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 226 "../src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 239 "../src/parser/parser.y"
    {
			g_op->do_scope_start();
		}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 243 "../src/parser/parser.y"
    {
			g_op->do_scope_end();
		}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 251 "../src/parser/parser.y"
    {
			g_ctl->parallel_start();
		}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 255 "../src/parser/parser.y"
    {
			g_ctl->parallel_end();
		}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 259 "../src/parser/parser.y"
    {
			g_ctl->parallel_for_start((yyvsp[(3) - (7)].cp));
		}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 263 "../src/parser/parser.y"
    {
			g_ctl->parallel_for_end();
		}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 270 "../src/parser/parser.y"
    {
			g_op->push_integer(0);	// by
			g_op->push_integer(1);	// per
		}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 275 "../src/parser/parser.y"
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
		}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 289 "../src/parser/parser.y"
    {
			if (strncmp((yyvsp[(1) - (4)].cp), "by", 2) != 0) {
				yyerror("parallel option 'by' expected");
			}

			if (strncmp((yyvsp[(3) - (4)].cp), "per", 3) != 0) {
				yyerror("parallel option 'per' expected");
			}
		}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 303 "../src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (4)].integer));
		}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 310 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_ROOT);
			g_op->find_member("os");
			g_op->find_member("run");
		}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 316 "../src/parser/parser.y"
    {	
			g_op->call(1);
		}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 325 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 333 "../src/parser/parser.y"
    {
			g_ex->pop();
		}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 342 "../src/parser/parser.y"
    {
			g_ex->push();
		}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 346 "../src/parser/parser.y"
    {
			g_ex->goto_end();
		}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 354 "../src/parser/parser.y"
    {
			g_ex->do_finally();
		}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 358 "../src/parser/parser.y"
    {
			g_ex->goto_end();
		}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 378 "../src/parser/parser.y"
    {
			g_ex->catch_start((yyvsp[(2) - (2)].cp));
		}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 382 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 386 "../src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(4) - (4)].vector_cp);
			g_ex->catch_start((yyvsp[(2) - (4)].cp), vp);
		}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 391 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 395 "../src/parser/parser.y"
    {
			g_ex->catch_start(NULL);
		}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 399 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 407 "../src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (3)].cp), 0);
		}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 411 "../src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (5)].cp), (yyvsp[(4) - (5)].integer));
		}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 419 "../src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (3)].cp), NULL);
		}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 423 "../src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (4)].cp), (yyvsp[(3) - (4)].cp));
		}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 431 "../src/parser/parser.y"
    {
			char buff[1024];
			sprintf(buff, "%s.%s", (yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
			(yyval.cp) = parser_strdup(buff);
		}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 437 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 445 "../src/parser/parser.y"
    {
			g_op->dump_stack();
		}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 449 "../src/parser/parser.y"
    {
			g_op->dump_local();
		}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 457 "../src/parser/parser.y"
    {
			g_ctl->do_return((yyvsp[(2) - (3)].integer));
		}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 461 "../src/parser/parser.y"
    {
			g_ctl->do_continue();
		}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 465 "../src/parser/parser.y"
    {
			g_ctl->do_break();
		}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 473 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 477 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 491 "../src/parser/parser.y"
    {
			g_ctl->decode_start();
		}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 495 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
		}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 503 "../src/parser/parser.y"
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
		}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 519 "../src/parser/parser.y"
    {
			vector<char>& def = parserCode::get_def();

			g_parse->make_table();
			//g_parse->dump();
			g_parse->do_parse(def);
			g_parse->cleanup();

			parserCode::pop_code_stack();
		}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 540 "../src/parser/parser.y"
    {
			g_parse->set_current_bnf((yyvsp[(1) - (1)].bp));
		}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 544 "../src/parser/parser.y"
    {

		}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 548 "../src/parser/parser.y"
    {
			bnf* b = (yyvsp[(3) - (4)].bp);
			b->type = BNF_WS;
		}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 568 "../src/parser/parser.y"
    {
			g_bnf_right_num = 1;
			g_parse->current_bnf()->add_rule();
		}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 583 "../src/parser/parser.y"
    {
			g_bnf_right_num++;
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(2) - (2)].bp));
		}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 588 "../src/parser/parser.y"
    {
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(1) - (1)].bp));
		}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 603 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp));
		}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 607 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp), true);
		}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 615 "../src/parser/parser.y"
    {
			string name = "`\a";
			name += (yyvsp[(1) - (1)].cp);
			(yyval.bp) = g_parse->get_nonterm_bnf(name);
		}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 625 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_action_bnf(g_bnf_right_num);
		}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 638 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_start();
		}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 642 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_shift();
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 646 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_end();
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 660 "../src/parser/parser.y"
    {
			g_ctl->decode_cut_list((yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
		}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 668 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 672 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 680 "../src/parser/parser.y"
    {
			g_ctl->decode_match_expr();
		}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 684 "../src/parser/parser.y"
    {
			g_ctl->decode_shift((yyvsp[(1) - (1)].cp));
		}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 688 "../src/parser/parser.y"
    {
			g_ctl->decode_match_and_assign((yyvsp[(1) - (3)].cp));
		}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 696 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(2) - (2)].cp);
		}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 712 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer) | (yyvsp[(2) - (2)].integer);
		}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 716 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 724 "../src/parser/parser.y"
    {
			(yyval.integer) = BIT_DEFINE_STATIC;
		}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 728 "../src/parser/parser.y"
    {
			(yyval.integer) = BIT_DEFINE_PURE;
		}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 736 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer);
		}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 740 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 748 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 752 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 760 "../src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
		}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 764 "../src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
			code_top->init_object_start((yyvsp[(2) - (3)].cp));

			g_op->push_reserved(OP_PUSH_MY);
		}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 771 "../src/parser/parser.y"
    {
			g_op->assign_member((yyvsp[(2) - (6)].cp));
			g_op->pop_stack();
			code_top->init_object_done();
		}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 777 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer)) {
				code_top->make_super((yyvsp[(2) - (2)].integer));
			}
		}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 783 "../src/parser/parser.y"
    {
			parserCode::pop_code_stack();
		}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 787 "../src/parser/parser.y"
    {
			
			g_ctl->decode_func_start();
		}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 792 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 801 "../src/parser/parser.y"
    {
			g_ctl->once_start();
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 805 "../src/parser/parser.y"
    {
			g_ctl->once_end();
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 813 "../src/parser/parser.y"
    {
			parserCode::pop_code_stack();
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(1) - (2)].cp));
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 823 "../src/parser/parser.y"
    {
			cp2_t cp2 = (yyvsp[(1) - (1)].cp2);
			code_top->do_context(cp2.c1, cp2.c2);
		}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 832 "../src/parser/parser.y"
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
		}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 857 "../src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(2) - (2)].vector_cp);

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
			parserCode::push_code_stack(name, vp, (yyvsp[(1) - (2)].integer));

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}

			(yyval.cp) = name;
		}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 889 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 893 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (2)].integer);
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 901 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 905 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 909 "../src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 915 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = (yyvsp[(2) - (3)].vector_cp);
		}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 919 "../src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(2) - (5)].vector_cp);
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 929 "../src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(1) - (3)].vector_cp);
			vs->push_back((yyvsp[(3) - (3)].cp));
			(yyval.vector_cp) = vs;
		}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 935 "../src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back((yyvsp[(1) - (1)].cp));
			(yyval.vector_cp) = vs;
		}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 945 "../src/parser/parser.y"
    {
			g_ctl->if_end();
		}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 949 "../src/parser/parser.y"
    {
			g_ctl->else_end();
		}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 953 "../src/parser/parser.y"
    {
			g_ctl->else_end();
			for(int i=0; i<(yyvsp[(2) - (3)].integer); i++)
				g_ctl->else_end();
		}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 959 "../src/parser/parser.y"
    {
			g_ctl->if_end();
			for(int i=0; i<(yyvsp[(2) - (2)].integer); i++)
				g_ctl->else_end();
		}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 969 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer) + 1;
		}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 973 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 981 "../src/parser/parser.y"
    {
			g_ctl->else_start();
		}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 985 "../src/parser/parser.y"
    {
			g_ctl->if_start();
		}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 994 "../src/parser/parser.y"
    {
			g_ctl->else_start();
		}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1003 "../src/parser/parser.y"
    {
			g_ctl->if_start();
		}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1012 "../src/parser/parser.y"
    {
			g_ctl->do_start();
		}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1016 "../src/parser/parser.y"
    {
			g_ctl->do_end();
		}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1024 "../src/parser/parser.y"
    {
			g_ctl->times_start();
		}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1028 "../src/parser/parser.y"
    {
			g_ctl->times_end();
		}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1036 "../src/parser/parser.y"
    {
			g_ctl->while_start_1();
		}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1040 "../src/parser/parser.y"
    {
			g_ctl->while_start_2();
		}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1044 "../src/parser/parser.y"
    {
			g_ctl->while_end();
		}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1052 "../src/parser/parser.y"
    {
			g_ctl->for_start((yyvsp[(2) - (5)].cp));
		}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1056 "../src/parser/parser.y"
    {
			g_ctl->for_end();
		}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1064 "../src/parser/parser.y"
    { 
			(yyval.integer) = (yyvsp[(1) - (2)].integer); 
		}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1072 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1076 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1084 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1088 "../src/parser/parser.y"
    {
			(yyval.integer) = 2;
		}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1103 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer) != '=') {
				g_op->push_lvar((yyvsp[(1) - (2)].cp));
			}
		}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1109 "../src/parser/parser.y"
    {
			switch ((yyvsp[(2) - (4)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_local((yyvsp[(1) - (4)].cp));
		}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1121 "../src/parser/parser.y"
    {
			g_op->clear_last_find_position();
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_member((yyvsp[(3) - (4)].cp));
			}
		}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1129 "../src/parser/parser.y"
    {
			switch ((yyvsp[(4) - (6)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((yyvsp[(3) - (6)].cp));
		}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1141 "../src/parser/parser.y"
    {
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_reserved((yyvsp[(3) - (4)].integer));
			}
		}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1148 "../src/parser/parser.y"
    {
			switch ((yyvsp[(4) - (6)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((yyvsp[(3) - (6)].integer));
		}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1160 "../src/parser/parser.y"
    {
			if ((yyvsp[(5) - (5)].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(false);
			}
		}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1168 "../src/parser/parser.y"
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
		}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1184 "../src/parser/parser.y"
    {
			if ((yyvsp[(5) - (5)].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(true);
			}
		}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1192 "../src/parser/parser.y"
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
		}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1208 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[(2) - (3)].cp));
			}
		}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1217 "../src/parser/parser.y"
    {
			switch ((yyvsp[(3) - (5)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((yyvsp[(2) - (5)].cp));
		}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1229 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[(2) - (3)].integer));
			}
		}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1238 "../src/parser/parser.y"
    {
			switch ((yyvsp[(3) - (5)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((yyvsp[(2) - (5)].integer));
		}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1250 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[(2) - (3)].cp));
			}
		}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1259 "../src/parser/parser.y"
    {
			switch ((yyvsp[(3) - (5)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member((yyvsp[(2) - (5)].cp));
		}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1271 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[(2) - (3)].integer));
			}
		}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1280 "../src/parser/parser.y"
    {
			switch ((yyvsp[(3) - (5)].integer))
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved((yyvsp[(2) - (5)].integer));
		}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1297 "../src/parser/parser.y"
    {
			(yyval.integer) = '='; 
		}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1301 "../src/parser/parser.y"
    { 
			(yyval.integer) = '+'; 
		}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1305 "../src/parser/parser.y"
    { 
			(yyval.integer) = '-'; 
		}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1309 "../src/parser/parser.y"
    { 
			(yyval.integer) = '*'; 
		}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1313 "../src/parser/parser.y"
    { 
			(yyval.integer) = '/'; 
		}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1326 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start(false);
		}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1331 "../src/parser/parser.y"
    {
			g_op->do_or();
			g_ctl->if_end();
		}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1341 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start();
		}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1346 "../src/parser/parser.y"
    {
			g_op->do_and();
			g_ctl->if_end();
		}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1356 "../src/parser/parser.y"
    {
			g_op->do_not();
		}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1365 "../src/parser/parser.y"
    {
			g_op->gt();
		}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1369 "../src/parser/parser.y"
    {
			g_op->ge();
		}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1373 "../src/parser/parser.y"
    {
			g_op->lt();
		}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1377 "../src/parser/parser.y"
    {
			g_op->le();
		}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1381 "../src/parser/parser.y"
    {
			g_op->eq();
		}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1385 "../src/parser/parser.y"
    {
			g_op->neq();
		}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1399 "../src/parser/parser.y"
    {
			g_op->add();
		}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1403 "../src/parser/parser.y"
    {
			g_op->sub();
		}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1407 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(2) - (2)].integer));
			g_op->add();
		}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1412 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(2) - (2)].cp));
			g_op->add();
		}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1417 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(2) - (2)].real));
			g_op->add();
		}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1427 "../src/parser/parser.y"
    {
			g_op->mul();
		}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1431 "../src/parser/parser.y"
    {
			g_op->div();
		}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1435 "../src/parser/parser.y"
    {
			g_op->mod();
		}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1444 "../src/parser/parser.y"
    {
			unary_minus = true;
		}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1448 "../src/parser/parser.y"
    {
			if (unary_minus)
				g_op->minus();

			unary_minus = false;
		}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1461 "../src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (3)].integer));
		}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1465 "../src/parser/parser.y"
    {
			g_op->make_list(-2);
		}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1469 "../src/parser/parser.y"
    {
			g_op->make_list(-3);
		}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1478 "../src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (3)].integer));
		}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1482 "../src/parser/parser.y"
    {
			g_op->make_tuple(-2);
		}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1486 "../src/parser/parser.y"
    {
			g_op->make_tuple(-3);
		}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1494 "../src/parser/parser.y"
    {
			g_op->make_map((yyvsp[(2) - (3)].integer));
		}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1502 "../src/parser/parser.y"
    {
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1507 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule_start();
		}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1511 "../src/parser/parser.y"
    {
			g_ctl->sbf_end();
			g_lvar_nil_check++;
		}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 1531 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule();
		}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1535 "../src/parser/parser.y"
    {
			g_ctl->sbf_in();
		}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1543 "../src/parser/parser.y"
    {
			g_ctl->sbf_list_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1547 "../src/parser/parser.y"
    {
			g_ctl->sbf_range_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 1556 "../src/parser/parser.y"
    {
			g_op->push_integer(1);
		}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 1565 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 1569 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 1578 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1582 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 258:
/* Line 1792 of yacc.c  */
#line 1599 "../src/parser/parser.y"
    {
			if (g_op->check_lvar((yyvsp[(1) - (1)].cp)) == false) {
				string msg = "variable ";
				msg += (yyvsp[(1) - (1)].cp);
				msg += " is not defined";
				yyerror(msg.c_str());
			}

			g_op->push_lvar((yyvsp[(1) - (1)].cp));
		}
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 1610 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 260:
/* Line 1792 of yacc.c  */
#line 1614 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 1618 "../src/parser/parser.y"
    {
			g_op->push_bignum('+', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1622 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 1626 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1630 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 1634 "../src/parser/parser.y"
    {
			g_op->make_regex();
		}
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1638 "../src/parser/parser.y"
    {
			// already in stack
		}
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1642 "../src/parser/parser.y"
    {
			g_op->push_reserved((yyvsp[(1) - (1)].integer));
		}
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 1646 "../src/parser/parser.y"
    {
			g_op->push_boolean(true);
		}
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 1650 "../src/parser/parser.y"
    {
			g_op->push_boolean(false);
		}
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 1654 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 1663 "../src/parser/parser.y"
    {
			g_op->set_last_find_position();
			g_op->find_member((yyvsp[(3) - (3)].cp));
		}
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 1668 "../src/parser/parser.y"
    {
			g_op->find_reserved((yyvsp[(3) - (3)].integer));
		}
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 1672 "../src/parser/parser.y"
    {
			g_op->clear_last_find_position();
		}
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 1676 "../src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (3)].integer));
		}
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1680 "../src/parser/parser.y"
    {
			g_op->listat(false);
		}
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1684 "../src/parser/parser.y"
    {
			g_op->listat(true);
		}
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 1688 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1693 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 1698 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 1703 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 1708 "../src/parser/parser.y"
    {
			if (g_op->push_mvar_using_space((yyvsp[(1) - (1)].cp)) == false) {
				yyerror("invalid object name in name'string' format");
			}
		}
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 1714 "../src/parser/parser.y"
    {
			g_op->clone(1);
		}
    break;

  case 284:
/* Line 1792 of yacc.c  */
#line 1718 "../src/parser/parser.y"
    {
			g_op->clone((yyvsp[(4) - (4)].integer));

			// this is not normal function call (virtual function call)
			// so it should mark that don't fast popping
			g_op->disable_fast_pop();
		}
    break;

  case 286:
/* Line 1792 of yacc.c  */
#line 1731 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 287:
/* Line 1792 of yacc.c  */
#line 1735 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
		}
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 1739 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 289:
/* Line 1792 of yacc.c  */
#line 1743 "../src/parser/parser.y"
    {
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1748 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 292:
/* Line 1792 of yacc.c  */
#line 1759 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 293:
/* Line 1792 of yacc.c  */
#line 1763 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (3)].integer);
		}
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 1771 "../src/parser/parser.y"
    {
			g_op->fix_last_find_position();
		}
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 1779 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_OWNER;
		}
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 1783 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_CALLER;
		}
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 1787 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_ROOT;
		}
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 1791 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MODULE;
		}
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 1795 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MY;
		}
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 1803 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 302:
/* Line 1792 of yacc.c  */
#line 1812 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 1821 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 305:
/* Line 1792 of yacc.c  */
#line 1829 "../src/parser/parser.y"
    {
			g_op->add();

			g_op->push_string((yyvsp[(4) - (4)].cp));

			g_op->add();
		}
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 1841 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 308:
/* Line 1792 of yacc.c  */
#line 1850 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 1855 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 311:
/* Line 1792 of yacc.c  */
#line 1863 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 1871 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 313:
/* Line 1792 of yacc.c  */
#line 1879 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 1887 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 1895 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 1903 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 1911 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;


/* Line 1792 of yacc.c  */
#line 4400 "../src/parser/parser.cpp"
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


/* Line 2055 of yacc.c  */
#line 1917 "../src/parser/parser.y"



