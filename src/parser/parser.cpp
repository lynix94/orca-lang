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


/* Line 371 of yacc.c  */
#line 109 "../src/parser/parser.cpp"

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
     NIL_ = 306,
     RIGHT_ARROW = 307,
     LEFT_ARROW = 308,
     PARALLEL = 309,
     ASSIGNMENT = 310,
     ONCE = 311,
     EVAL = 312,
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
#line 53 "../src/parser/parser.y"

	const char* cp;
	int integer;
	double real;
	void* vector_cp;	
	struct bnf* bp;	
	struct cp2_t cp2; 
	struct int2_t int2;


/* Line 387 of yacc.c  */
#line 235 "../src/parser/parser.cpp"
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
#line 263 "../src/parser/parser.cpp"

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
#define YYFINAL  158
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  160
/* YYNRULES -- Number of rules.  */
#define YYNRULES  321
/* YYNRULES -- Number of states.  */
#define YYNSTATES  529

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
      45,    47,    49,    51,    53,    54,    58,    59,    64,    65,
      75,    76,    79,    84,    89,    90,    93,    96,    98,   101,
     103,   104,   108,   109,   113,   115,   118,   121,   123,   124,
     129,   130,   137,   138,   142,   146,   152,   156,   161,   165,
     167,   169,   171,   175,   178,   181,   182,   184,   186,   188,
     189,   196,   199,   201,   202,   208,   213,   217,   219,   221,
     222,   225,   227,   230,   232,   234,   236,   238,   240,   242,
     244,   246,   249,   251,   252,   253,   259,   261,   263,   267,
     271,   273,   275,   277,   281,   284,   286,   288,   290,   292,
     295,   297,   299,   301,   305,   306,   313,   314,   319,   325,
     326,   336,   337,   347,   351,   352,   356,   357,   362,   367,
     372,   377,   380,   385,   390,   391,   394,   395,   398,   402,
     406,   412,   416,   418,   420,   423,   427,   430,   433,   435,
     436,   437,   444,   445,   450,   451,   457,   458,   465,   466,
     472,   473,   474,   481,   482,   490,   493,   497,   499,   501,
     503,   504,   509,   510,   517,   518,   525,   526,   534,   535,
     543,   544,   550,   551,   557,   558,   564,   565,   571,   573,
     575,   577,   579,   581,   583,   585,   586,   591,   593,   594,
     599,   601,   604,   606,   610,   614,   618,   622,   626,   630,
     632,   634,   638,   642,   645,   648,   651,   653,   657,   661,
     665,   667,   668,   672,   675,   677,   681,   686,   692,   700,
     702,   708,   713,   719,   727,   731,   736,   737,   738,   747,
     749,   753,   755,   757,   759,   763,   767,   771,   773,   777,
     780,   781,   785,   789,   791,   795,   797,   799,   801,   803,
     805,   807,   809,   811,   813,   815,   817,   819,   821,   823,
     825,   827,   829,   833,   835,   837,   842,   846,   850,   851,
     855,   860,   865,   868,   871,   874,   877,   878,   882,   887,
     889,   893,   894,   898,   901,   903,   905,   908,   912,   914,
     916,   918,   920,   922,   924,   926,   929,   931,   934,   936,
     941,   943,   945,   947,   949,   951,   953,   955,   957,   959,
     961,   963
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      94,     0,    -1,    94,    98,    -1,    94,    96,    -1,    98,
      -1,    98,    -1,    96,    -1,    73,    94,    74,    -1,    73,
      74,    -1,    94,    74,    -1,    74,    -1,   188,    -1,   124,
      -1,   126,    -1,   151,    -1,   154,    -1,   109,    -1,   121,
      -1,   105,    -1,   106,    -1,    99,    -1,   101,    -1,   123,
      -1,    75,    -1,    -1,   190,   100,    96,    -1,    -1,    54,
      16,   102,    95,    -1,    -1,    54,    22,   240,    23,   238,
     104,    76,   103,    95,    -1,    -1,    58,   190,    -1,    58,
     190,    58,   190,    -1,   232,    76,   189,    75,    -1,    -1,
     107,   108,    -1,   108,   243,    -1,    65,    -1,   110,   112,
      -1,   120,    -1,    -1,    35,   111,    96,    -1,    -1,   115,
     113,   114,    -1,   115,    -1,    37,    96,    -1,   115,   116,
      -1,   116,    -1,    -1,    36,   122,   117,    96,    -1,    -1,
      36,   122,    76,   169,   118,    96,    -1,    -1,    36,   119,
      96,    -1,    38,   122,    75,    -1,    38,   122,    77,   189,
      75,    -1,    42,   122,    75,    -1,    42,   122,    59,    75,
      -1,   122,    78,   153,    -1,   153,    -1,    40,    -1,    41,
      -1,    24,   125,    75,    -1,    25,    75,    -1,    26,    75,
      -1,    -1,   189,    -1,   170,    -1,   127,    -1,    -1,    20,
     190,   128,    73,   142,    74,    -1,   129,   130,    -1,   130,
      -1,    -1,   133,   131,    76,   132,    75,    -1,    79,    76,
     139,    75,    -1,   132,    80,   134,    -1,   134,    -1,   140,
      -1,    -1,   135,   136,    -1,   137,    -1,   137,   138,    -1,
     138,    -1,   139,    -1,   140,    -1,   141,    -1,    59,    -1,
      62,    -1,   246,    -1,   162,    -1,   142,   143,    -1,   143,
      -1,    -1,    -1,   144,   146,    52,   145,    95,    -1,   148,
      -1,   147,    -1,   150,    76,   150,    -1,   148,    77,   149,
      -1,   149,    -1,   190,    -1,   150,    -1,   150,    81,   190,
      -1,    82,   240,    -1,   186,    -1,   179,    -1,   183,    -1,
     181,    -1,     4,     5,    -1,     5,    -1,   246,    -1,    59,
      -1,   152,   153,    75,    -1,    -1,   152,   153,    55,   155,
     190,    75,    -1,    -1,   159,   167,   156,    96,    -1,   152,
      78,   153,   153,    73,    -1,    -1,   152,    78,    21,   153,
     168,   157,    73,   129,    74,    -1,    -1,   152,    78,    20,
     153,   168,   158,    73,   142,    74,    -1,   152,   153,   168,
      -1,    -1,    56,   161,    97,    -1,    -1,   164,   167,   163,
      96,    -1,   152,    78,   153,    73,    -1,   165,    73,   142,
      74,    -1,   166,    73,   129,    74,    -1,   152,   168,    -1,
     152,    78,    20,   168,    -1,   152,    78,    21,   168,    -1,
      -1,    76,   189,    -1,    -1,    83,    84,    -1,    83,    46,
      84,    -1,    83,   169,    84,    -1,    83,   169,    77,    46,
      84,    -1,   169,    77,   246,    -1,   246,    -1,   177,    -1,
     177,   175,    -1,   177,   171,   175,    -1,   177,   171,    -1,
     171,   172,    -1,   172,    -1,    -1,    -1,    14,   173,   202,
      76,   174,    95,    -1,    -1,    15,    76,   176,    95,    -1,
      -1,    13,   202,    76,   178,    95,    -1,    -1,    16,   180,
      95,    17,   202,    75,    -1,    -1,   190,    18,    16,   182,
      95,    -1,    -1,    -1,    17,   184,   202,    76,   185,    95,
      -1,    -1,    22,   240,    23,   238,    76,   187,    95,    -1,
     189,    75,    -1,   189,    77,   190,    -1,   190,    -1,   191,
      -1,   160,    -1,    -1,   240,   201,   192,   190,    -1,    -1,
     232,    78,   153,   201,   193,   190,    -1,    -1,   232,    78,
     239,   201,   194,   190,    -1,    -1,   232,    85,   235,    86,
     201,   195,   190,    -1,    -1,   232,    85,   235,    84,   201,
     196,   190,    -1,    -1,    45,   153,   201,   197,   190,    -1,
      -1,    45,   239,   201,   198,   190,    -1,    -1,    78,   153,
     201,   199,   190,    -1,    -1,    78,   239,   201,   200,   190,
      -1,   202,    -1,    81,    -1,    47,    -1,    48,    -1,    49,
      -1,    50,    -1,   203,    -1,    -1,   203,    30,   204,   205,
      -1,   205,    -1,    -1,   205,    29,   206,   207,    -1,   207,
      -1,    87,   208,    -1,   208,    -1,   209,    31,   209,    -1,
     209,    32,   209,    -1,   209,    33,   209,    -1,   209,    34,
     209,    -1,   209,    27,   209,    -1,   209,    28,   209,    -1,
     209,    -1,   210,    -1,   210,    88,   211,    -1,   210,    89,
     211,    -1,   210,   247,    -1,   210,   249,    -1,   210,   252,
      -1,   211,    -1,   211,    90,   238,    -1,   211,    91,   238,
      -1,   211,    82,   238,    -1,   212,    -1,    -1,    89,   213,
     238,    -1,    88,   238,    -1,   238,    -1,    85,   125,    86,
      -1,    85,   189,    77,    86,    -1,    85,   190,    45,   190,
      86,    -1,    85,   190,    45,   190,    76,   190,    86,    -1,
     217,    -1,    83,   189,    77,   190,    84,    -1,    83,   189,
      77,    84,    -1,    83,   190,    45,   190,    84,    -1,    83,
     190,    45,   190,    76,   190,    84,    -1,    73,   227,    74,
      -1,    73,   227,    77,    74,    -1,    -1,    -1,    82,    85,
     218,   220,    80,   219,   221,    86,    -1,   190,    -1,   221,
      77,   222,    -1,   222,    -1,   202,    -1,   223,    -1,   240,
      53,   190,    -1,   240,    53,   224,    -1,   225,    76,   190,
      -1,   225,    -1,   190,    79,   190,    -1,   190,    79,    -1,
      -1,    79,   226,   190,    -1,   227,    77,   228,    -1,   228,
      -1,   190,    76,   190,    -1,   214,    -1,   215,    -1,   216,
      -1,   162,    -1,   240,    -1,   248,    -1,   247,    -1,   250,
      -1,   249,    -1,   251,    -1,   252,    -1,   244,    -1,   245,
      -1,   239,    -1,    43,    -1,    44,    -1,    51,    -1,    83,
     190,    84,    -1,   230,    -1,   231,    -1,    57,    83,   190,
      84,    -1,   232,    78,   153,    -1,   232,    78,   239,    -1,
      -1,   232,   233,   237,    -1,   232,    85,   235,    86,    -1,
     232,    85,   235,    84,    -1,    45,   153,    -1,    45,   239,
      -1,    78,   153,    -1,    78,   239,    -1,    -1,   246,   234,
     245,    -1,   232,    78,     6,   237,    -1,   229,    -1,   190,
      76,   190,    -1,    -1,    76,   236,   190,    -1,   190,    76,
      -1,    76,    -1,   190,    -1,    83,    84,    -1,    83,   189,
      84,    -1,   232,    -1,     8,    -1,     9,    -1,    10,    -1,
      11,    -1,     7,    -1,   246,    -1,   241,   243,    -1,    60,
      -1,   242,   243,    -1,    63,    -1,    92,    73,   190,    61,
      -1,    62,    -1,   242,    -1,    59,    -1,   241,    -1,    64,
      -1,    58,    -1,    68,    -1,    67,    -1,    70,    -1,    69,
      -1,    71,    -1,    72,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   186,   186,   187,   188,   193,   194,   199,   200,   205,
     206,   211,   221,   222,   223,   224,   225,   226,   227,   231,
     235,   236,   237,   238,   244,   243,   256,   255,   264,   263,
     275,   279,   293,   307,   315,   315,   328,   329,   337,   341,
     347,   346,   359,   358,   366,   371,   376,   377,   383,   382,
     391,   390,   400,   399,   411,   415,   423,   427,   435,   441,
     449,   453,   461,   465,   469,   478,   481,   489,   490,   496,
     495,   507,   508,   514,   513,   521,   531,   532,   537,   542,
     542,   551,   556,   561,   569,   570,   571,   576,   580,   588,
     598,   606,   607,   612,   616,   612,   627,   628,   633,   641,
     645,   653,   657,   661,   669,   677,   678,   679,   680,   685,
     689,   697,   701,   709,   714,   713,   727,   726,   736,   744,
     743,   771,   770,   803,   830,   829,   842,   841,   853,   868,
     876,   894,   926,   960,   987,   990,   999,  1002,  1006,  1012,
    1016,  1026,  1032,  1042,  1046,  1050,  1056,  1066,  1070,  1079,
    1083,  1078,  1092,  1091,  1101,  1100,  1110,  1109,  1122,  1121,
    1134,  1138,  1133,  1150,  1149,  1161,  1169,  1173,  1181,  1182,
    1188,  1187,  1206,  1205,  1226,  1225,  1245,  1244,  1269,  1268,
    1293,  1292,  1314,  1313,  1335,  1334,  1356,  1355,  1376,  1381,
    1385,  1389,  1393,  1397,  1405,  1411,  1410,  1420,  1426,  1425,
    1435,  1440,  1444,  1449,  1453,  1457,  1461,  1465,  1469,  1473,
    1478,  1483,  1487,  1491,  1496,  1501,  1506,  1511,  1515,  1519,
    1523,  1529,  1528,  1539,  1540,  1545,  1549,  1553,  1557,  1561,
    1566,  1570,  1574,  1578,  1586,  1590,  1599,  1604,  1598,  1616,
    1621,  1622,  1627,  1631,  1639,  1643,  1651,  1652,  1660,  1661,
    1666,  1665,  1674,  1678,  1686,  1691,  1692,  1693,  1694,  1695,
    1706,  1710,  1714,  1718,  1722,  1726,  1730,  1734,  1738,  1742,
    1746,  1750,  1754,  1755,  1760,  1765,  1772,  1777,  1782,  1781,
    1789,  1793,  1797,  1802,  1807,  1812,  1818,  1817,  1827,  1835,
    1840,  1845,  1844,  1852,  1857,  1863,  1868,  1872,  1880,  1888,
    1892,  1896,  1900,  1904,  1912,  1920,  1921,  1929,  1930,  1938,
    1950,  1954,  1959,  1963,  1964,  1972,  1980,  1988,  1996,  2004,
    2012,  2020
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
  "LEFT_ARROW", "PARALLEL", "ASSIGNMENT", "ONCE", "EVAL", "NAME", "STRING",
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
  "bnf_stmt_list", "bnf_stmt", "$@11", "bnf_right_list", "bnf_left",
  "bnf_right", "$@12", "bnf_right_", "bnf_node_list", "bnf_node",
  "terminal", "non_terminal", "action_code", "decode_pattern_stmt_list",
  "decode_pattern_stmt", "$@13", "$@14", "decode_pattern", "list_pattern",
  "pattern_list", "pattern", "p_var", "loop_stmt", "def", "name_or_string",
  "define_stmt", "$@15", "$@16", "$@17", "$@18", "define_header",
  "once_expr", "$@19", "lambda_object", "$@20", "lambda_define_header",
  "lambda_decode_header", "lambda_parse_header", "opt_superclass",
  "opt_argument_list", "name_list", "if_elif_else_stmt", "elif_stmt_list",
  "elif_stmt", "$@21", "$@22", "else_stmt", "$@23", "if_stmt", "$@24",
  "do_stmt", "$@25", "times_stmt", "$@26", "while_stmt", "$@27", "$@28",
  "for_stmt", "$@29", "expression_stmt", "expression_list", "expression",
  "assign_expr", "$@30", "$@31", "$@32", "$@33", "$@34", "$@35", "$@36",
  "$@37", "$@38", "assign_type", "bool_expr", "or_expr", "$@39",
  "and_expr", "$@40", "not_expr", "logical_expr", "numeric_expr",
  "add_expr", "mul_expr", "unary_expr", "$@41", "list", "tuple", "map",
  "sbf", "$@42", "$@43", "sbf_result", "sbf_rule_list", "sbf_rule",
  "in_expr", "range_expr", "range_expr_sub", "$@44", "pair_list",
  "pair_expression", "primary_object", "reserved_functions",
  "eval_function", "postfix_object", "$@45", "$@46", "slice_expression",
  "$@47", "calling_body", "object", "reserved_object", "lvar",
  "format_string", "re_format_string", "format_object", "regex", "string",
  "name", "minus_number", "number", "minus_big_number", "big_number",
  "real", "minus_real", YY_NULL
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
      98,    98,    98,    98,   100,    99,   102,   101,   103,   101,
     104,   104,   104,   105,   107,   106,   108,   108,   109,   109,
     111,   110,   113,   112,   112,   114,   115,   115,   117,   116,
     118,   116,   119,   116,   120,   120,   121,   121,   122,   122,
     123,   123,   124,   124,   124,   125,   125,   126,   126,   128,
     127,   129,   129,   131,   130,   130,   132,   132,   133,   135,
     134,   136,   137,   137,   138,   138,   138,   139,   139,   140,
     141,   142,   142,   144,   145,   143,   146,   146,   147,   148,
     148,   149,   149,   149,   150,   151,   151,   151,   151,   152,
     152,   153,   153,   154,   155,   154,   156,   154,   154,   157,
     154,   158,   154,   159,   161,   160,   163,   162,   162,   162,
     162,   164,   165,   166,   167,   167,   168,   168,   168,   168,
     168,   169,   169,   170,   170,   170,   170,   171,   171,   173,
     174,   172,   176,   175,   178,   177,   180,   179,   182,   181,
     184,   185,   183,   187,   186,   188,   189,   189,   190,   190,
     192,   191,   193,   191,   194,   191,   195,   191,   196,   191,
     197,   191,   198,   191,   199,   191,   200,   191,   191,   201,
     201,   201,   201,   201,   202,   204,   203,   203,   206,   205,
     205,   207,   207,   208,   208,   208,   208,   208,   208,   208,
     209,   210,   210,   210,   210,   210,   210,   211,   211,   211,
     211,   213,   212,   212,   212,   214,   214,   214,   214,   214,
     215,   215,   215,   215,   216,   216,   218,   219,   217,   220,
     221,   221,   222,   222,   223,   223,   224,   224,   225,   225,
     226,   225,   227,   227,   228,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   230,   231,   232,   232,   233,   232,
     232,   232,   232,   232,   232,   232,   234,   232,   232,   232,
     235,   236,   235,   235,   235,   235,   237,   237,   238,   239,
     239,   239,   239,   239,   240,   241,   241,   242,   242,   243,
     244,   244,   245,   245,   245,   246,   247,   248,   249,   250,
     251,   252
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     3,     0,     4,     0,     9,
       0,     2,     4,     4,     0,     2,     2,     1,     2,     1,
       0,     3,     0,     3,     1,     2,     2,     1,     0,     4,
       0,     6,     0,     3,     3,     5,     3,     4,     3,     1,
       1,     1,     3,     2,     2,     0,     1,     1,     1,     0,
       6,     2,     1,     0,     5,     4,     3,     1,     1,     0,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     0,     0,     5,     1,     1,     3,     3,
       1,     1,     1,     3,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     3,     0,     6,     0,     4,     5,     0,
       9,     0,     9,     3,     0,     3,     0,     4,     4,     4,
       4,     2,     4,     4,     0,     2,     0,     2,     3,     3,
       5,     3,     1,     1,     2,     3,     2,     2,     1,     0,
       0,     6,     0,     4,     0,     5,     0,     6,     0,     5,
       0,     0,     6,     0,     7,     2,     3,     1,     1,     1,
       0,     4,     0,     6,     0,     6,     0,     7,     0,     7,
       0,     5,     0,     5,     0,     5,     0,     5,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     0,     4,
       1,     2,     1,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     3,     2,     2,     2,     1,     3,     3,     3,
       1,     0,     3,     2,     1,     3,     4,     5,     7,     1,
       5,     4,     5,     7,     3,     4,     0,     0,     8,     1,
       3,     1,     1,     1,     3,     3,     3,     1,     3,     2,
       0,     3,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     4,     3,     3,     0,     3,
       4,     4,     2,     2,     2,     2,     0,     3,     4,     1,
       3,     0,     3,     2,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      34,     0,   110,   303,   299,   300,   301,   302,     0,   156,
     160,     0,     0,    65,     0,     0,    40,     0,    60,    61,
       0,   269,   270,     0,   271,     0,   124,     0,   315,   312,
     306,   310,   308,   314,   317,   316,   319,   318,   320,   321,
       0,    23,     0,     0,     0,    65,     0,     0,   221,    34,
       4,    20,    21,    18,    19,     0,    16,     0,    39,    17,
      22,    12,    13,    68,    14,   136,    15,   134,   169,   258,
     134,     0,     0,    67,   143,   106,   108,   107,   105,    11,
       0,   167,   168,   188,   194,   197,   200,   202,   209,   210,
     216,   220,   255,   256,   257,   229,   289,   273,   274,   298,
     224,   268,   259,   313,   311,   266,   267,   304,   261,   260,
     263,   262,   264,   265,   109,     0,     0,   136,     0,   298,
     259,    34,     0,    69,   298,     0,   304,     0,    66,   167,
      63,    64,     0,   112,     0,    59,   111,     0,   282,   283,
      26,     0,    34,     0,     0,     0,   253,   284,   285,   236,
       0,   167,     0,    66,   167,   201,   223,     0,     1,    34,
       3,     2,    37,    35,    52,    38,    44,    47,     0,     0,
     136,   131,     0,   116,   126,    93,     0,   149,     0,   146,
     148,   144,   165,     0,     0,     0,   195,   198,     0,     0,
       0,     0,     0,     0,     0,     0,   213,   214,   215,     0,
       0,     0,     0,     0,     0,     0,   190,   191,   192,   193,
     189,   170,     0,   305,   307,     0,   282,   283,   284,   285,
       0,   154,     0,     0,     0,     6,     5,     0,     0,     0,
      62,    34,    41,    54,     0,     0,     0,    56,   180,   182,
      34,     0,    10,    34,   125,     0,     0,   234,     0,   184,
     186,     0,     0,     0,   272,   225,     0,     0,   222,     8,
      34,   167,    36,     0,    48,     0,    46,   136,   136,     0,
       0,   137,     0,   142,   114,   113,   123,   135,     0,     0,
      93,    92,     0,     0,     0,    72,    73,    78,    89,     0,
     152,   147,   145,   166,   158,    25,     0,     0,   207,   208,
     203,   204,   205,   206,   211,   212,   219,   217,   218,     0,
       0,   276,   277,   291,   295,     0,     0,   279,     0,     0,
     287,   136,   136,     0,    34,   276,   277,     0,     0,   161,
      93,     0,     0,    58,    57,     0,     0,    27,     0,     9,
     275,   254,   235,   252,     0,     0,   239,     0,   231,   166,
       0,   226,     0,     7,    53,     0,     0,     0,    43,   136,
     132,   136,   133,   128,     0,   138,     0,   139,     0,   117,
     127,   129,    91,     0,     0,    97,    96,   100,   102,   101,
       0,   130,    71,     0,     0,    34,    34,   196,   199,    33,
     288,   172,   174,     0,   293,   281,   280,   296,     0,   171,
       0,   155,   281,   280,     0,    34,    93,   163,    55,   181,
     183,    30,   185,   187,   237,   230,     0,   232,     0,   227,
      50,    49,    45,   121,   119,   118,     0,   141,     0,   104,
      94,     0,     0,     0,    87,    88,     0,    79,   150,   153,
     159,     0,     0,   292,   290,   178,   176,   297,   309,   157,
     162,    70,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   140,   115,    34,    99,   102,     0,    98,   103,
      75,     0,    77,     0,    34,   173,   175,     0,     0,   164,
      31,    28,   242,     0,   241,   243,   259,   233,   228,    51,
      93,     0,    95,    74,    79,    80,    81,    83,    84,    85,
      86,    90,   151,   179,   177,     0,    34,     0,   238,     0,
      93,     0,    76,    82,    32,    29,   240,   250,   244,   245,
     247,   122,   120,     0,   249,     0,   251,   248,   246
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   260,   224,   225,   244,   226,    51,   185,    52,   240,
     506,   454,    53,    54,    55,   163,    56,    57,   132,   165,
     265,   358,   166,   167,   356,   459,   263,    58,    59,   134,
      60,    61,   127,    62,    63,   228,   284,   285,   383,   471,
     286,   472,   473,   495,   496,   497,   498,   287,   500,   280,
     281,   282,   464,   374,   375,   376,   377,   378,    64,   117,
     135,    66,   368,   278,   461,   460,    67,    68,   142,    69,
     279,    70,    71,    72,   173,   171,   272,    73,   179,   180,
     289,   474,   181,   385,    74,   324,    75,   121,    76,   386,
      77,   122,   405,    78,   452,    79,    80,    81,    82,   318,
     441,   442,   478,   477,   335,   336,   344,   345,   211,    83,
      84,   296,    85,   297,    86,    87,    88,    89,    90,    91,
     157,    92,    93,    94,    95,   251,   455,   347,   483,   484,
     485,   519,   520,   523,   145,   146,    96,    97,    98,   124,
     205,   215,   315,   393,   317,   100,   101,   102,   103,   104,
     213,   105,   106,   107,   108,   109,   110,   111,   112,   113
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -404
static const yytype_int16 yypact[] =
{
    1097,    23,  -404,  -404,  -404,  -404,  -404,  -404,  1957,  -404,
    -404,  1785,   -10,  1785,    56,    70,  -404,   252,  -404,  -404,
     252,  -404,  -404,    43,  -404,    10,  -404,   -19,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    1785,  -404,    43,    97,  1785,  1785,  2043,  2129,  -404,   662,
    -404,  -404,  -404,  -404,  -404,    13,  -404,    72,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,    22,  -404,   114,  -404,  -404,
     114,    82,   125,  -404,   298,  -404,  -404,  -404,  -404,  -404,
     132,    -5,  -404,  -404,   172,   197,  -404,  -404,   248,    46,
     -25,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,   118,
    -404,  -404,    39,   140,   140,  -404,  -404,   174,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,    43,    43,    28,   160,    58,
    -404,  1183,  1957,  -404,   121,   216,  -404,   185,   190,  -404,
    -404,  -404,   201,  -404,    21,  -404,  -404,    71,    39,    39,
    -404,   -10,   753,  1785,   207,   109,  -404,    39,    39,  -404,
     200,   -28,   204,   210,   255,  -404,  -404,  2129,  -404,   839,
    -404,  -404,  -404,   140,   252,  -404,   280,  -404,     2,     1,
      20,  -404,  1785,  -404,  -404,  -404,    49,  -404,   217,   298,
    -404,  -404,  -404,  1785,   304,   201,  -404,  -404,  2043,  2043,
    2043,  2043,  2043,  2043,  2043,  2043,  -404,  -404,  -404,  2129,
    2129,  2129,  1785,    33,  1269,   249,  -404,  -404,  -404,  -404,
    -404,  -404,   268,  -404,  -404,   225,  -404,  -404,  -404,  -404,
      25,  -404,    33,  1269,   325,  -404,  -404,   267,   271,  2129,
    -404,   839,  -404,  -404,  1785,   252,   270,  -404,  -404,  -404,
    1183,   323,  -404,   925,  -404,   263,  1785,  -404,  1355,  -404,
    -404,  1785,  1441,  1785,  -404,  -404,  1527,  1785,  -404,  -404,
    1011,     3,  -404,   201,   135,   311,  -404,   -47,   -47,    81,
     265,  -404,    79,  -404,  -404,  -404,  -404,   190,   201,   201,
     276,  -404,  1871,   275,    59,  -404,  -404,  -404,  -404,  1957,
    -404,  -404,  -404,  -404,  -404,  -404,  1957,  1957,  -404,  -404,
    -404,  -404,  -404,  -404,   -25,   -25,  -404,  -404,  -404,   142,
     249,    39,    39,   164,   278,   184,  1613,  -404,  1785,  1785,
    -404,   272,   272,   283,  1183,  -404,  -404,   213,  1957,  -404,
    -404,   282,   227,  -404,  -404,  1785,  1785,  -404,  2129,  -404,
    -404,  -404,  -404,  -404,  1785,  1785,  -404,   281,  -404,   279,
      53,  -404,   -14,  -404,  -404,   -10,   201,   201,  -404,   272,
    -404,   272,  -404,  -404,   289,  -404,    36,  -404,  1785,  -404,
    -404,  -404,  -404,   -27,   312,  -404,   288,  -404,    90,  -404,
     162,  -404,  -404,   290,   291,  1183,  1183,   197,  -404,  -404,
    -404,  -404,  -404,  1785,  1785,    39,    39,  -404,    91,  -404,
     307,  -404,  -404,  -404,   294,  1183,   299,  -404,  -404,  -404,
    -404,   316,  -404,  -404,  -404,  -404,  1785,  -404,  1785,  -404,
     300,  -404,  -404,  -404,  -404,  -404,   292,  -404,   303,  -404,
    -404,  1871,   302,  1785,  -404,  -404,   305,  -404,  -404,  -404,
    -404,  1785,  1785,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  1183,  1785,   310,  1957,   297,   306,   -10,   201,
     315,   317,  -404,  -404,  1183,  -404,   308,   -10,  -404,  -404,
    -404,    94,  -404,    15,  1183,  -404,  -404,  1785,  1785,  -404,
     335,  -404,  -404,    67,  -404,  -404,   342,  -404,  -404,  -404,
    -404,    49,  -404,  -404,  -404,  -404,    15,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  1785,  1183,  1957,  -404,  1699,
     322,    68,  -404,  -404,  -404,  -404,  -404,  -404,   318,  -404,
     324,  -404,  -404,  1785,  1785,  1785,  -404,  -404,  -404
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -404,     9,  -205,   -35,  -404,    18,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,   232,  -404,  -404,  -404,  -404,  -404,   -12,
    -404,  -404,   354,  -404,  -404,  -404,   -89,  -281,  -404,  -404,
    -404,   -91,  -404,  -404,  -404,   -92,    26,  -403,  -404,  -326,
    -279,  -404,  -404,  -404,  -404,  -404,   -23,  -103,  -404,    55,
     371,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -383,
    -404,  -404,  -404,  -404,   341,  -143,    57,  -404,  -404,   235,
    -404,  -404,   236,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,    -7,   -11,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -123,    -1,
    -404,  -404,   120,  -404,   124,   377,   147,  -404,   136,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,   -82,
    -404,  -404,  -404,  -404,  -404,   178,  -404,  -404,  -404,    63,
    -404,  -404,   205,  -404,   117,   -42,     7,   363,  -404,  -404,
     -94,  -404,   214,   150,   343,  -404,   344,  -404,  -404,   346
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -295
static const yytype_int16 yytable[] =
{
     123,   372,   129,   382,   406,   156,   128,   118,   137,    49,
     214,    28,   133,   184,   160,   238,   239,   253,    50,     1,
       2,   184,   267,   268,   249,   250,   140,   276,   114,   144,
     139,    28,   141,   151,   154,   337,   169,   150,   153,   310,
       3,     4,     5,     6,     7,   321,   322,   270,    28,   148,
       3,     4,     5,     6,     7,    65,   254,   199,   149,    28,
      28,   133,   418,    99,   143,   200,   201,   161,   -24,   262,
     499,   119,   419,    28,   434,   274,   -24,   435,   162,   246,
      28,   133,   426,    28,   133,   271,   206,   207,   208,   209,
     501,    28,   133,   499,    28,   275,   233,   232,   234,   235,
     168,    28,   133,   169,    65,   169,   220,    28,   164,   119,
     119,   169,    99,   501,    35,   258,    37,    28,    39,   401,
     210,   227,   217,   219,   360,   362,    28,   372,   283,   416,
     236,   130,   245,   381,   194,   195,   222,   417,   283,    28,
     133,  -278,   522,   223,   507,   131,   237,   283,   261,   235,
     295,   243,   264,   508,   363,   175,   366,   306,   307,   308,
      50,   129,   126,   367,   510,   277,   432,   136,   183,   493,
     136,   433,   293,   136,   494,   447,    65,    50,   360,   362,
     439,   440,   149,   247,    99,   119,   248,   331,   391,   392,
     172,   129,   136,   314,   202,   309,   203,    65,   176,   203,
     450,  -278,   186,   204,  -278,    99,   204,   182,   160,   183,
     312,   355,   314,   235,    65,   136,   423,   389,   424,   183,
     119,   434,    99,   129,   435,   160,   187,   332,   354,   326,
     382,   372,   212,  -286,  -286,   341,   221,   144,  -286,   229,
     346,   349,   350,   369,   370,   293,   352,   479,  -294,    50,
    -294,   119,   119,   119,   119,   119,   119,   119,   119,   492,
     230,   161,   119,   119,   119,   136,   136,   183,   395,   502,
     396,   379,   445,   446,   231,   188,   189,   252,   161,   190,
     191,   192,   193,   246,    29,    30,    65,   256,   384,    33,
     255,   126,   119,   290,    99,    65,   411,   402,    65,   403,
     257,   515,   408,    99,   183,   129,    99,   399,   400,   398,
      28,   133,   177,   178,   136,    65,   164,   -42,   136,   273,
     294,   421,   422,    99,   409,   410,   288,   404,   466,   468,
     304,   305,   316,   412,   413,   298,   299,   300,   301,   302,
     303,   319,   328,   329,   330,   334,   338,   340,   357,   365,
     371,   380,   119,   136,   394,   169,   363,   428,   407,   119,
     119,   414,   425,   415,   430,   431,   437,   438,   448,   449,
     136,   120,   136,   451,   453,   125,   462,   458,   463,    65,
     470,   487,   443,   444,   467,   136,   481,    99,   490,   433,
     491,   119,   488,   505,   138,   509,   521,   524,   266,   152,
     525,   119,   511,   512,   513,   456,   436,   457,   465,   120,
     120,   174,   420,   147,   291,   292,   387,   136,   136,   136,
     379,   388,   469,   155,   489,   516,   343,   390,   327,   320,
     475,   476,   196,   197,   288,   198,   170,     0,     0,     0,
      65,    65,   480,     0,     0,     0,     0,     0,    99,    99,
       0,     0,     0,     0,   482,     0,     0,     0,     0,     0,
      65,     0,     0,     0,     0,     0,   503,   504,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   120,   216,   218,     0,     0,
       0,     0,     0,     0,   514,     0,     0,     0,   518,     0,
       0,     0,     0,     0,   241,   273,   482,    65,     0,     0,
       0,     0,   526,   527,   528,    99,   427,     0,   119,    65,
     120,     0,     0,   126,     0,     0,     0,    99,     0,    65,
       0,     0,     0,     0,     0,     0,     0,    99,     0,   269,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120,   120,   120,   120,   120,   120,   120,   120,     0,
       0,    65,   120,   120,   120,     0,     0,     0,     0,    99,
     119,     0,     0,     0,   311,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   323,   120,   325,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   333,     0,   427,     0,
       0,     0,     0,     0,     0,     0,     0,   126,     0,     0,
       0,     0,     0,   288,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   359,   361,
     364,   288,     0,     0,     0,     0,   288,     0,     0,     0,
       0,     0,   120,     0,     0,     0,     0,     0,     0,   120,
     120,   288,   158,     0,     0,     0,     1,     2,     0,     3,
       4,     5,     6,     7,     0,     8,     0,     0,     9,    10,
       0,     0,    11,     0,    12,     0,    13,    14,    15,     0,
       0,   120,     0,     0,     0,     0,     0,    16,     0,     0,
      17,   120,    18,    19,    20,    21,    22,    23,     0,     0,
       0,     0,     0,    24,     0,     0,    25,     0,    26,    27,
      28,    29,    30,     0,    31,    32,    33,     0,     0,    34,
      35,    36,    37,    38,    39,   159,   429,    41,     0,     0,
      42,     0,     0,     0,    43,    44,     0,    45,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     1,     2,     0,
       3,     4,     5,     6,     7,     0,     8,     0,     0,     9,
      10,     0,     0,    11,     0,    12,     0,    13,    14,    15,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
       0,    17,     0,    18,    19,    20,    21,    22,    23,     0,
       0,     0,     0,     0,    24,     0,     0,    25,     0,    26,
      27,    28,    29,    30,     0,    31,    32,    33,   486,     0,
      34,    35,    36,    37,    38,    39,    40,   242,    41,     0,
     429,    42,     0,     0,     0,    43,    44,     0,    45,     0,
      46,    47,    48,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     8,     0,     0,     9,    10,     0,     0,    11,
       0,    12,     0,    13,    14,    15,     0,     0,     0,     0,
     486,     0,     0,     0,    16,     0,     0,    17,     0,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,    25,     0,    26,    27,    28,    29,    30,
       0,    31,    32,    33,     0,     0,    34,    35,    36,    37,
      38,    39,    40,   259,    41,     0,     0,    42,     0,     0,
       0,    43,    44,     0,    45,     0,    46,    47,    48,     1,
       2,     0,     3,     4,     5,     6,     7,     0,     8,     0,
       0,     9,    10,     0,     0,    11,     0,    12,     0,    13,
      14,    15,     0,     0,     0,     0,     0,     0,     0,     0,
      16,     0,     0,    17,     0,    18,    19,    20,    21,    22,
      23,     0,     0,     0,     0,     0,    24,     0,     0,    25,
       0,    26,    27,    28,    29,    30,     0,    31,    32,    33,
       0,     0,    34,    35,    36,    37,    38,    39,   159,   339,
      41,     0,     0,    42,     0,     0,     0,    43,    44,     0,
      45,     0,    46,    47,    48,     1,     2,     0,     3,     4,
       5,     6,     7,     0,     8,     0,     0,     9,    10,     0,
       0,    11,     0,    12,     0,    13,    14,    15,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,     0,    17,
       0,    18,    19,    20,    21,    22,    23,     0,     0,     0,
       0,     0,    24,     0,     0,    25,     0,    26,    27,    28,
      29,    30,     0,    31,    32,    33,     0,     0,    34,    35,
      36,    37,    38,    39,   159,   353,    41,     0,     0,    42,
       0,     0,     0,    43,    44,     0,    45,     0,    46,    47,
      48,     1,     2,     0,     3,     4,     5,     6,     7,     0,
       8,     0,     0,     9,    10,     0,     0,    11,     0,    12,
       0,    13,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,     0,    17,     0,    18,    19,    20,
      21,    22,    23,     0,     0,     0,     0,     0,    24,     0,
       0,    25,     0,    26,    27,    28,    29,    30,     0,    31,
      32,    33,     0,     0,    34,    35,    36,    37,    38,    39,
      40,     0,    41,     0,     0,    42,     0,     0,     0,    43,
      44,     0,    45,     0,    46,    47,    48,     1,     2,     0,
       3,     4,     5,     6,     7,     0,     8,     0,     0,     9,
      10,     0,     0,    11,     0,    12,     0,    13,    14,    15,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
       0,    17,     0,    18,    19,    20,    21,    22,    23,     0,
       0,     0,     0,     0,    24,     0,     0,    25,     0,    26,
      27,    28,    29,    30,     0,    31,    32,    33,     0,     0,
      34,    35,    36,    37,    38,    39,   159,     0,    41,     0,
       0,    42,     0,     0,     0,    43,    44,     0,    45,     0,
      46,    47,    48,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,    26,    27,    28,    29,    30,
       0,    31,    32,    33,     0,     0,    34,    35,    36,    37,
      38,    39,    40,     0,     0,   313,     0,    42,     0,     0,
       0,    43,    44,     0,    45,     0,    46,    47,    48,     1,
       2,     0,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,     0,     0,     0,     0,     0,    24,     0,     0,     0,
       0,    26,    27,    28,    29,    30,     0,    31,    32,    33,
       0,     0,    34,    35,    36,    37,    38,    39,    40,   342,
       0,     0,     0,    42,     0,     0,     0,    43,    44,     0,
      45,     0,    46,    47,    48,     1,     2,     0,     3,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    22,    23,     0,     0,     0,
       0,     0,    24,     0,     0,     0,     0,    26,    27,    28,
      29,    30,     0,    31,    32,    33,     0,     0,    34,    35,
      36,    37,    38,    39,    40,     0,     0,     0,     0,    42,
       0,     0,     0,    43,    44,   348,    45,     0,    46,    47,
      48,     1,     2,     0,     3,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,    22,    23,     0,     0,     0,     0,     0,    24,     0,
       0,     0,     0,    26,    27,    28,    29,    30,     0,    31,
      32,    33,     0,     0,    34,    35,    36,    37,    38,    39,
      40,     0,     0,     0,     0,    42,     0,     0,     0,    43,
      44,     0,    45,   351,    46,    47,    48,     1,     2,     0,
       3,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,    23,     0,
       0,     0,     0,     0,    24,     0,     0,     0,     0,    26,
      27,    28,    29,    30,     0,    31,    32,    33,     0,     0,
      34,    35,    36,    37,    38,    39,    40,     0,     0,     0,
       0,    42,     0,     0,     0,    43,    44,   397,    45,     0,
      46,    47,    48,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,    26,    27,    28,    29,    30,
       0,    31,    32,    33,     0,     0,    34,    35,    36,    37,
      38,    39,    40,     0,     0,     0,     0,    42,   517,     0,
       0,    43,    44,     0,    45,     0,    46,    47,    48,     1,
       2,     0,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,     0,     0,     0,     0,     0,    24,     0,     0,     0,
       0,    26,    27,    28,    29,    30,     0,    31,    32,    33,
       0,     0,    34,    35,    36,    37,    38,    39,    40,     0,
       0,     0,     0,    42,     0,     0,     0,    43,    44,     0,
      45,     0,    46,    47,    48,     1,     2,     0,     3,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    22,    23,     0,     0,     0,
       0,     0,    24,     0,     0,     0,     0,    26,    27,    28,
      29,    30,     0,    31,    32,    33,     0,     0,    34,    35,
      36,    37,    38,    39,    40,     0,     0,     0,     0,    42,
       0,     0,     0,   373,    44,     0,    45,     0,    46,    47,
      48,     1,     2,     0,     3,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,    22,   115,     0,     0,     0,     0,     0,    24,     0,
       0,     0,     0,     0,    27,    28,    29,    30,     0,    31,
      32,    33,     0,     0,    34,    35,    36,    37,    38,    39,
      40,     0,     0,     0,     0,   116,     0,     0,     0,    43,
      44,     0,    45,     0,    46,    47,    48,     1,     2,     0,
       3,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,   115,     0,
       0,     0,     0,     0,    24,     0,     0,     0,     0,     0,
      27,    28,    29,    30,     0,    31,    32,    33,     0,     0,
      34,    35,    36,    37,    38,    39,    40,     0,     0,     0,
       0,   116,     0,     0,     0,    43,    44,     0,    45,     0,
       0,    47,    48,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,   115,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,     0,    27,    28,    29,    30,
       0,    31,    32,    33,     0,     0,    34,    35,    36,    37,
      38,    39,    40,     0,     0,     0,     0,   116,     0,     0,
       0,    43,    44,     0,    45
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-404)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      11,   280,    13,   284,   330,    47,    13,     8,    20,     0,
     104,    58,    59,    18,    49,   138,   139,    45,     0,     4,
       5,    18,    20,    21,   147,   148,    16,   170,     5,    40,
      23,    58,    22,    44,    45,   240,    83,    44,    45,     6,
       7,     8,     9,    10,    11,    20,    21,    46,    58,    42,
       7,     8,     9,    10,    11,     0,    84,    82,    85,    58,
      58,    59,    76,     0,    83,    90,    91,    49,    73,   163,
     473,     8,    86,    58,    59,    55,    73,    62,    65,    76,
      58,    59,    46,    58,    59,    84,    47,    48,    49,    50,
     473,    58,    59,   496,    58,    75,    75,   132,    77,    78,
      78,    58,    59,    83,    49,    83,    78,    58,    36,    46,
      47,    83,    49,   496,    68,   157,    70,    58,    72,   324,
      81,   122,   115,   116,   267,   268,    58,   406,    79,    76,
      59,    75,   143,    74,    88,    89,    78,    84,    79,    58,
      59,    83,    74,    85,    77,    75,    75,    79,   159,    78,
     185,   142,   164,    86,    73,    73,    77,   199,   200,   201,
     142,   172,    12,    84,   490,   172,    76,    17,    77,    75,
      20,    81,   183,    23,    80,    84,   121,   159,   321,   322,
     385,   386,    85,    74,   121,   122,    77,   229,   311,   312,
      76,   202,    42,   204,    76,   202,    78,   142,    73,    78,
     405,    83,    30,    85,    83,   142,    85,    75,   243,    77,
     203,    76,   223,    78,   159,    65,   359,    75,   361,    77,
     157,    59,   159,   234,    62,   260,    29,   234,   263,   222,
     511,   510,    92,    59,    60,   246,    76,   248,    64,    23,
     251,   252,   253,   278,   279,   256,   257,   452,    84,   231,
      86,   188,   189,   190,   191,   192,   193,   194,   195,   464,
      75,   243,   199,   200,   201,   115,   116,    77,    84,   474,
      86,   282,   395,   396,    73,    27,    28,    77,   260,    31,
      32,    33,    34,    76,    59,    60,   231,    77,   289,    64,
      86,   141,   229,    76,   231,   240,   338,    84,   243,    86,
      45,   506,    75,   240,    77,   316,   243,   318,   319,   316,
      58,    59,    14,    15,   164,   260,    36,    37,   168,   169,
      16,   356,   357,   260,   335,   336,   176,   328,   431,   432,
     194,   195,    83,   344,   345,   188,   189,   190,   191,   192,
     193,    73,    17,    76,    73,    75,    23,    84,    37,    84,
      74,    76,   289,   203,    76,    83,    73,   368,    76,   296,
     297,    80,    73,    84,    52,    77,    76,    76,    61,    75,
     220,     8,   222,    74,    58,    12,    84,    77,    75,   324,
      75,    84,   393,   394,    82,   235,    76,   324,    73,    81,
      73,   328,    86,    58,    23,    53,    74,    79,   166,    45,
      76,   338,   491,   494,   496,   416,   380,   418,   431,    46,
      47,    70,   355,    42,   179,   179,   296,   267,   268,   269,
     431,   297,   433,    46,   459,   507,   248,   310,   223,   215,
     441,   442,    89,    89,   284,    89,    65,    -1,    -1,    -1,
     385,   386,   453,    -1,    -1,    -1,    -1,    -1,   385,   386,
      -1,    -1,    -1,    -1,   455,    -1,    -1,    -1,    -1,    -1,
     405,    -1,    -1,    -1,    -1,    -1,   477,   478,   405,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   122,   115,   116,    -1,    -1,
      -1,    -1,    -1,    -1,   505,    -1,    -1,    -1,   509,    -1,
      -1,    -1,    -1,    -1,   141,   355,   507,   452,    -1,    -1,
      -1,    -1,   523,   524,   525,   452,   366,    -1,   455,   464,
     157,    -1,    -1,   373,    -1,    -1,    -1,   464,    -1,   474,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   474,    -1,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   188,   189,   190,   191,   192,   193,   194,   195,    -1,
      -1,   506,   199,   200,   201,    -1,    -1,    -1,    -1,   506,
     507,    -1,    -1,    -1,   203,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   220,   229,   222,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   235,    -1,   458,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   467,    -1,    -1,
      -1,    -1,    -1,   473,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   267,   268,
     269,   491,    -1,    -1,    -1,    -1,   496,    -1,    -1,    -1,
      -1,    -1,   289,    -1,    -1,    -1,    -1,    -1,    -1,   296,
     297,   511,     0,    -1,    -1,    -1,     4,     5,    -1,     7,
       8,     9,    10,    11,    -1,    13,    -1,    -1,    16,    17,
      -1,    -1,    20,    -1,    22,    -1,    24,    25,    26,    -1,
      -1,   328,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      38,   338,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    54,    -1,    56,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,   373,    75,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    13,    -1,    -1,    16,
      17,    -1,    -1,    20,    -1,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    54,    -1,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,   455,    -1,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
     467,    78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,
      87,    88,    89,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,
      -1,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,
     507,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    54,    -1,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    78,    -1,    -1,
      -1,    82,    83,    -1,    85,    -1,    87,    88,    89,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    13,    -1,
      -1,    16,    17,    -1,    -1,    20,    -1,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    38,    -1,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    54,
      -1,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,
      85,    -1,    87,    88,    89,     4,     5,    -1,     7,     8,
       9,    10,    11,    -1,    13,    -1,    -1,    16,    17,    -1,
      -1,    20,    -1,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,
      -1,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    54,    -1,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    -1,    -1,    78,
      -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,    88,
      89,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      13,    -1,    -1,    16,    17,    -1,    -1,    20,    -1,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    38,    -1,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    54,    -1,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    82,
      83,    -1,    85,    -1,    87,    88,    89,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    13,    -1,    -1,    16,
      17,    -1,    -1,    20,    -1,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    54,    -1,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    -1,    75,    -1,
      -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,
      87,    88,    89,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    76,    -1,    78,    -1,    -1,
      -1,    82,    83,    -1,    85,    -1,    87,    88,    89,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,
      85,    -1,    87,    88,    89,     4,     5,    -1,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    82,    83,    84,    85,    -1,    87,    88,
      89,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,
      83,    -1,    85,    86,    87,    88,    89,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    82,    83,    84,    85,    -1,
      87,    88,    89,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    78,    79,    -1,
      -1,    82,    83,    -1,    85,    -1,    87,    88,    89,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,
      85,    -1,    87,    88,    89,     4,     5,    -1,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,    88,
      89,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,
      83,    -1,    85,    -1,    87,    88,    89,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,
      -1,    88,    89,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    82,    83,    -1,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     7,     8,     9,    10,    11,    13,    16,
      17,    20,    22,    24,    25,    26,    35,    38,    40,    41,
      42,    43,    44,    45,    51,    54,    56,    57,    58,    59,
      60,    62,    63,    64,    67,    68,    69,    70,    71,    72,
      73,    75,    78,    82,    83,    85,    87,    88,    89,    94,
      98,    99,   101,   105,   106,   107,   109,   110,   120,   121,
     123,   124,   126,   127,   151,   152,   154,   159,   160,   162,
     164,   165,   166,   170,   177,   179,   181,   183,   186,   188,
     189,   190,   191,   202,   203,   205,   207,   208,   209,   210,
     211,   212,   214,   215,   216,   217,   229,   230,   231,   232,
     238,   239,   240,   241,   242,   244,   245,   246,   247,   248,
     249,   250,   251,   252,     5,    45,    78,   152,   202,   232,
     240,   180,   184,   190,   232,   240,   246,   125,   189,   190,
      75,    75,   111,    59,   122,   153,   246,   122,   153,   239,
      16,    22,   161,    83,   190,   227,   228,   153,   239,    85,
     189,   190,   125,   189,   190,   208,   238,   213,     0,    73,
      96,    98,    65,   108,    36,   112,   115,   116,    78,    83,
     153,   168,    76,   167,   167,    73,    73,    14,    15,   171,
     172,   175,    75,    77,    18,   100,    30,    29,    27,    28,
      31,    32,    33,    34,    88,    89,   247,   249,   252,    82,
      90,    91,    76,    78,    85,   233,    47,    48,    49,    50,
      81,   201,    92,   243,   243,   234,   153,   239,   153,   239,
      78,    76,    78,    85,    95,    96,    98,   202,   128,    23,
      75,    73,    96,    75,    77,    78,    59,    75,   201,   201,
     102,   240,    74,    94,    97,   190,    76,    74,    77,   201,
     201,   218,    77,    45,    84,    86,    77,    45,   238,    74,
      94,   190,   243,   119,   122,   113,   116,    20,    21,   153,
      46,    84,   169,   246,    55,    75,   168,   189,   156,   163,
     142,   143,   144,    79,   129,   130,   133,   140,   246,   173,
      76,   172,   175,   190,    16,    96,   204,   206,   209,   209,
     209,   209,   209,   209,   211,   211,   238,   238,   238,   189,
       6,   153,   239,    76,   190,   235,    83,   237,   192,    73,
     245,    20,    21,   153,   178,   153,   239,   235,    17,    76,
      73,   238,   189,   153,    75,   197,   198,    95,    23,    74,
      84,   190,    74,   228,   199,   200,   190,   220,    84,   190,
     190,    86,   190,    74,    96,    76,   117,    37,   114,   153,
     168,   153,   168,    73,   153,    84,    77,    84,   155,    96,
      96,    74,   143,    82,   146,   147,   148,   149,   150,   190,
      76,    74,   130,   131,   202,   176,   182,   205,   207,    75,
     237,   201,   201,   236,    76,    84,    86,    84,   189,   190,
     190,    95,    84,    86,   202,   185,   142,    76,    75,   190,
     190,   238,   190,   190,    80,    84,    76,    84,    76,    86,
     169,    96,    96,   168,   168,    73,    46,   246,   190,   240,
      52,    77,    76,    81,    59,    62,   139,    76,    76,    95,
      95,   193,   194,   190,   190,   201,   201,    84,    61,    75,
      95,    74,   187,    58,   104,   219,   190,   190,    77,   118,
     158,   157,    84,    75,   145,   149,   150,    82,   150,   190,
      75,   132,   134,   135,   174,   190,   190,   196,   195,    95,
     190,    76,   202,   221,   222,   223,   240,    84,    86,    96,
      73,    73,    95,    75,    80,   136,   137,   138,   139,   140,
     141,   162,    95,   190,   190,    58,   103,    77,    86,    53,
     142,   129,   134,   138,   190,    95,   222,    79,   190,   224,
     225,    74,    74,   226,    79,    76,   190,   190,   190
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
#line 212 "../src/parser/parser.y"
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
#line 228 "../src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 232 "../src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 244 "../src/parser/parser.y"
    {
			g_op->do_scope_start();
		}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 248 "../src/parser/parser.y"
    {
			g_op->do_scope_end();
		}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 256 "../src/parser/parser.y"
    {
			g_ctl->parallel_start();
		}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 260 "../src/parser/parser.y"
    {
			g_ctl->parallel_end();
		}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 264 "../src/parser/parser.y"
    {
			g_ctl->parallel_for_start((yyvsp[(3) - (7)].cp));
		}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 268 "../src/parser/parser.y"
    {
			g_ctl->parallel_for_end();
		}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 275 "../src/parser/parser.y"
    {
			g_op->push_integer(0);	// by
			g_op->push_integer(1);	// per
		}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 280 "../src/parser/parser.y"
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

  case 32:
/* Line 1792 of yacc.c  */
#line 294 "../src/parser/parser.y"
    {
			if (strncmp((yyvsp[(1) - (4)].cp), "by", 2) != 0) {
				yyerror("parallel option 'by' expected");
			}

			if (strncmp((yyvsp[(3) - (4)].cp), "per", 3) != 0) {
				yyerror("parallel option 'per' expected");
			}
		}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 308 "../src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (4)].integer));
		}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 315 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_ROOT);
			g_op->find_member("os");
			g_op->find_member("run");
		}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 321 "../src/parser/parser.y"
    {	
			g_op->call(1);
		}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 330 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 338 "../src/parser/parser.y"
    {
			g_ex->pop();
		}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 347 "../src/parser/parser.y"
    {
			g_ex->push();
		}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 351 "../src/parser/parser.y"
    {
			g_ex->goto_end();
		}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 359 "../src/parser/parser.y"
    {
			g_ex->do_finally();
		}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 363 "../src/parser/parser.y"
    {
			g_ex->goto_end();
		}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 383 "../src/parser/parser.y"
    {
			g_ex->catch_start((yyvsp[(2) - (2)].cp));
		}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 387 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 391 "../src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(4) - (4)].vector_cp);
			g_ex->catch_start((yyvsp[(2) - (4)].cp), vp);
		}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 396 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 400 "../src/parser/parser.y"
    {
			g_ex->catch_start(NULL);
		}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 404 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 412 "../src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (3)].cp), 0);
		}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 416 "../src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (5)].cp), (yyvsp[(4) - (5)].integer));
		}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 424 "../src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (3)].cp), NULL);
		}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 428 "../src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (4)].cp), (yyvsp[(3) - (4)].cp));
		}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 436 "../src/parser/parser.y"
    {
			char buff[1024];
			sprintf(buff, "%s.%s", (yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
			(yyval.cp) = parser_strdup(buff);
		}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 442 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 450 "../src/parser/parser.y"
    {
			g_op->dump_stack();
		}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 454 "../src/parser/parser.y"
    {
			g_op->dump_local();
		}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 462 "../src/parser/parser.y"
    {
			g_ctl->do_return((yyvsp[(2) - (3)].integer));
		}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 466 "../src/parser/parser.y"
    {
			g_ctl->do_continue();
		}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 470 "../src/parser/parser.y"
    {
			g_ctl->do_break();
		}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 478 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 482 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 496 "../src/parser/parser.y"
    {
			g_ctl->decode_start();
		}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 500 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
		}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 514 "../src/parser/parser.y"
    {
			g_parse->set_current_bnf((yyvsp[(1) - (1)].bp));
		}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 518 "../src/parser/parser.y"
    {

		}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 522 "../src/parser/parser.y"
    {
			bnf* b = (yyvsp[(3) - (4)].bp);
			b->type = BNF_WS;
		}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 542 "../src/parser/parser.y"
    {
			g_bnf_right_num = 1;
			g_parse->current_bnf()->add_rule();
		}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 557 "../src/parser/parser.y"
    {
			g_bnf_right_num++;
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(2) - (2)].bp));
		}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 562 "../src/parser/parser.y"
    {
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(1) - (1)].bp));
		}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 577 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp));
		}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 581 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp), true);
		}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 589 "../src/parser/parser.y"
    {
			string name = "`\a";
			name += (yyvsp[(1) - (1)].cp);
			(yyval.bp) = g_parse->get_nonterm_bnf(name);
		}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 599 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_action_bnf(g_bnf_right_num);
		}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 612 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_start();
		}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 616 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_shift();
		}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 620 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_end();
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 634 "../src/parser/parser.y"
    {
			g_ctl->decode_cut_list((yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
		}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 642 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 646 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 654 "../src/parser/parser.y"
    {
			g_ctl->decode_match_expr();
		}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 658 "../src/parser/parser.y"
    {
			g_ctl->decode_shift((yyvsp[(1) - (1)].cp));
		}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 662 "../src/parser/parser.y"
    {
			g_ctl->decode_match_and_assign((yyvsp[(1) - (3)].cp));
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 670 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(2) - (2)].cp);
		}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 686 "../src/parser/parser.y"
    {
			(yyval.integer) = BIT_DEFINE_STATIC;
		}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 690 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 698 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 702 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 710 "../src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
		}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 714 "../src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
			code_top->init_object_start((yyvsp[(2) - (3)].cp));

			g_op->push_reserved(OP_PUSH_MY);
		}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 721 "../src/parser/parser.y"
    {
			g_op->assign_member((yyvsp[(2) - (6)].cp));
			g_op->pop_stack();
			code_top->init_object_done();
		}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 727 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer)) {
				code_top->make_super((yyvsp[(2) - (2)].integer));
			}
		}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 733 "../src/parser/parser.y"
    {
			parserCode::pop_code_stack();
		}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 737 "../src/parser/parser.y"
    {
			const char* cp = get_context();
			print("get_context(): '%s'\n", cp);
			code_top->do_context((yyvsp[(3) - (5)].cp), (yyvsp[(4) - (5)].cp), cp);
			//TODO: fail check
		}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 744 "../src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(5) - (5)].vector_cp);

			// check argv
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				yyerror("argv not allowed in parse object");
			}

			if (vp == NULL) {
				yyerror("at least 1 argument needed in parse object");
			}

			parserCode::push_code_stack((yyvsp[(4) - (5)].cp), vp);
			g_parse->do_parse_init();
		}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 760 "../src/parser/parser.y"
    {
			vector<char>& def = parserCode::get_def();

			g_parse->make_table();
			//g_parse->dump();
			g_parse->do_parse(def);
			g_parse->cleanup();

			parserCode::pop_code_stack();
		}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 771 "../src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(5) - (5)].vector_cp);

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			parserCode::push_code_stack((yyvsp[(4) - (5)].cp), vp, (yyvsp[(1) - (5)].integer));

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}
			
			g_ctl->decode_func_start();
		}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 795 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();
		}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 804 "../src/parser/parser.y"
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

  case 124:
/* Line 1792 of yacc.c  */
#line 830 "../src/parser/parser.y"
    {
			g_ctl->once_start();
		}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 834 "../src/parser/parser.y"
    {
			g_ctl->once_end();
		}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 842 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer)) {
				code_top->make_super((yyvsp[(2) - (2)].integer));
			}
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 848 "../src/parser/parser.y"
    {
			parserCode::pop_code_stack();
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(1) - (4)].cp));
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 854 "../src/parser/parser.y"
    {
			// for serial tagging
			static int count = 1;
			char name[256];
			sprintf(name, "__%s_%d_context", g_parse_module_name.c_str(), count++);

			const char* cp = get_context();
			//print("get_context(): '%s'\n", cp);
			code_top->do_context((yyvsp[(3) - (4)].cp), name, cp);
			//TODO: fail check

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member(name);
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 869 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(1) - (4)].cp));
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 877 "../src/parser/parser.y"
    {
			vector<char>& def = parserCode::get_def();

			g_parse->make_table();
			//g_parse->dump();
			g_parse->do_parse(def);
			g_parse->cleanup();

			parserCode::pop_code_stack();

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(1) - (4)].cp));
		}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 895 "../src/parser/parser.y"
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

  case 132:
/* Line 1792 of yacc.c  */
#line 927 "../src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(4) - (4)].vector_cp);

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
			const char* name = parser_strdup(buff);
			parserCode::push_code_stack(name, vp, (yyvsp[(1) - (4)].integer));

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}
			
			g_ctl->decode_func_start();

			(yyval.cp) = name;
		}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 961 "../src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(4) - (4)].vector_cp);

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
			const char* name = parser_strdup(buff);
			parserCode::push_code_stack(name, vp);
			g_parse->do_parse_init();

			(yyval.cp) = name;
		}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 987 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 991 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (2)].integer);
		}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 999 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1003 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1007 "../src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1013 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = (yyvsp[(2) - (3)].vector_cp);
		}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1017 "../src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(2) - (5)].vector_cp);
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1027 "../src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(1) - (3)].vector_cp);
			vs->push_back((yyvsp[(3) - (3)].cp));
			(yyval.vector_cp) = vs;
		}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1033 "../src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back((yyvsp[(1) - (1)].cp));
			(yyval.vector_cp) = vs;
		}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1043 "../src/parser/parser.y"
    {
			g_ctl->if_end();
		}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1047 "../src/parser/parser.y"
    {
			g_ctl->else_end();
		}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1051 "../src/parser/parser.y"
    {
			g_ctl->else_end();
			for(int i=0; i<(yyvsp[(2) - (3)].integer); i++)
				g_ctl->else_end();
		}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1057 "../src/parser/parser.y"
    {
			g_ctl->if_end();
			for(int i=0; i<(yyvsp[(2) - (2)].integer); i++)
				g_ctl->else_end();
		}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1067 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer) + 1;
		}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1071 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1079 "../src/parser/parser.y"
    {
			g_ctl->else_start();
		}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1083 "../src/parser/parser.y"
    {
			g_ctl->if_start();
		}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1092 "../src/parser/parser.y"
    {
			g_ctl->else_start();
		}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1101 "../src/parser/parser.y"
    {
			g_ctl->if_start();
		}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1110 "../src/parser/parser.y"
    {
			g_ctl->do_start();
		}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1114 "../src/parser/parser.y"
    {
			g_ctl->do_end();
		}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1122 "../src/parser/parser.y"
    {
			g_ctl->times_start();
		}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1126 "../src/parser/parser.y"
    {
			g_ctl->times_end();
		}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1134 "../src/parser/parser.y"
    {
			g_ctl->while_start_1();
		}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1138 "../src/parser/parser.y"
    {
			g_ctl->while_start_2();
		}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1142 "../src/parser/parser.y"
    {
			g_ctl->while_end();
		}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1150 "../src/parser/parser.y"
    {
			g_ctl->for_start((yyvsp[(2) - (5)].cp));
		}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1154 "../src/parser/parser.y"
    {
			g_ctl->for_end();
		}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1162 "../src/parser/parser.y"
    { 
			(yyval.integer) = (yyvsp[(1) - (2)].integer); 
		}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1170 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1174 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1188 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer) != '=') {
				g_op->push_lvar((yyvsp[(1) - (2)].cp));
			}
		}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1194 "../src/parser/parser.y"
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

  case 172:
/* Line 1792 of yacc.c  */
#line 1206 "../src/parser/parser.y"
    {
			g_op->clear_last_find_position();
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_member((yyvsp[(3) - (4)].cp));
			}
		}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1214 "../src/parser/parser.y"
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

  case 174:
/* Line 1792 of yacc.c  */
#line 1226 "../src/parser/parser.y"
    {
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_reserved((yyvsp[(3) - (4)].integer));
			}
		}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1233 "../src/parser/parser.y"
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

  case 176:
/* Line 1792 of yacc.c  */
#line 1245 "../src/parser/parser.y"
    {
			if ((yyvsp[(5) - (5)].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(false);
			}
		}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1253 "../src/parser/parser.y"
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

  case 178:
/* Line 1792 of yacc.c  */
#line 1269 "../src/parser/parser.y"
    {
			if ((yyvsp[(5) - (5)].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(true);
			}
		}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1277 "../src/parser/parser.y"
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

  case 180:
/* Line 1792 of yacc.c  */
#line 1293 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[(2) - (3)].cp));
			}
		}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1302 "../src/parser/parser.y"
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

  case 182:
/* Line 1792 of yacc.c  */
#line 1314 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[(2) - (3)].integer));
			}
		}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1323 "../src/parser/parser.y"
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

  case 184:
/* Line 1792 of yacc.c  */
#line 1335 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[(2) - (3)].cp));
			}
		}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1344 "../src/parser/parser.y"
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

  case 186:
/* Line 1792 of yacc.c  */
#line 1356 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[(2) - (3)].integer));
			}
		}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1365 "../src/parser/parser.y"
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

  case 189:
/* Line 1792 of yacc.c  */
#line 1382 "../src/parser/parser.y"
    {
			(yyval.integer) = '='; 
		}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1386 "../src/parser/parser.y"
    { 
			(yyval.integer) = '+'; 
		}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1390 "../src/parser/parser.y"
    { 
			(yyval.integer) = '-'; 
		}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1394 "../src/parser/parser.y"
    { 
			(yyval.integer) = '*'; 
		}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1398 "../src/parser/parser.y"
    { 
			(yyval.integer) = '/'; 
		}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1411 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start(false);
		}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1416 "../src/parser/parser.y"
    {
			g_op->do_or();
			g_ctl->if_end();
		}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1426 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start();
		}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1431 "../src/parser/parser.y"
    {
			g_op->do_and();
			g_ctl->if_end();
		}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1441 "../src/parser/parser.y"
    {
			g_op->do_not();
		}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1450 "../src/parser/parser.y"
    {
			g_op->gt();
		}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1454 "../src/parser/parser.y"
    {
			g_op->ge();
		}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1458 "../src/parser/parser.y"
    {
			g_op->lt();
		}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1462 "../src/parser/parser.y"
    {
			g_op->le();
		}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1466 "../src/parser/parser.y"
    {
			g_op->eq();
		}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1470 "../src/parser/parser.y"
    {
			g_op->neq();
		}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1484 "../src/parser/parser.y"
    {
			g_op->add();
		}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1488 "../src/parser/parser.y"
    {
			g_op->sub();
		}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1492 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(2) - (2)].integer));
			g_op->add();
		}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1497 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(2) - (2)].cp));
			g_op->add();
		}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1502 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(2) - (2)].real));
			g_op->add();
		}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1512 "../src/parser/parser.y"
    {
			g_op->mul();
		}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1516 "../src/parser/parser.y"
    {
			g_op->div();
		}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1520 "../src/parser/parser.y"
    {
			g_op->mod();
		}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1529 "../src/parser/parser.y"
    {
			unary_minus = true;
		}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1533 "../src/parser/parser.y"
    {
			if (unary_minus)
				g_op->minus();

			unary_minus = false;
		}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1546 "../src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (3)].integer));
		}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1550 "../src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (4)].integer));
		}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1554 "../src/parser/parser.y"
    {
			g_op->make_list(-2);
		}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1558 "../src/parser/parser.y"
    {
			g_op->make_list(-3);
		}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1567 "../src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (5)].integer) + 1);
		}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1571 "../src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (4)].integer));
		}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1575 "../src/parser/parser.y"
    {
			g_op->make_tuple(-2);
		}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1579 "../src/parser/parser.y"
    {
			g_op->make_tuple(-3);
		}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1587 "../src/parser/parser.y"
    {
			g_op->make_map((yyvsp[(2) - (3)].integer));
		}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1591 "../src/parser/parser.y"
    {
			g_op->make_map((yyvsp[(2) - (4)].integer));
		}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1599 "../src/parser/parser.y"
    {
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1604 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule_start();
		}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1608 "../src/parser/parser.y"
    {
			g_ctl->sbf_end();
			g_lvar_nil_check++;
		}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1628 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule();
		}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1632 "../src/parser/parser.y"
    {
			g_ctl->sbf_in();
		}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1640 "../src/parser/parser.y"
    {
			g_ctl->sbf_list_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1644 "../src/parser/parser.y"
    {
			g_ctl->sbf_range_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1653 "../src/parser/parser.y"
    {
			g_op->push_integer(1);
		}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 1662 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 1666 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1675 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 1679 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 1696 "../src/parser/parser.y"
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

  case 260:
/* Line 1792 of yacc.c  */
#line 1707 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 1711 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1715 "../src/parser/parser.y"
    {
			g_op->push_bignum('+', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 1719 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1723 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 1727 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1731 "../src/parser/parser.y"
    {
			g_op->make_regex();
		}
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1735 "../src/parser/parser.y"
    {
			// already in stack
		}
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 1739 "../src/parser/parser.y"
    {
			g_op->push_reserved((yyvsp[(1) - (1)].integer));
		}
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 1743 "../src/parser/parser.y"
    {
			g_op->push_boolean(true);
		}
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 1747 "../src/parser/parser.y"
    {
			g_op->push_boolean(false);
		}
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 1751 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 1766 "../src/parser/parser.y"
    {
			g_op->eval();
		}
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1773 "../src/parser/parser.y"
    {
			g_op->set_last_find_position();
			g_op->find_member((yyvsp[(3) - (3)].cp));
		}
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1778 "../src/parser/parser.y"
    {
			g_op->find_reserved((yyvsp[(3) - (3)].integer));
		}
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 1782 "../src/parser/parser.y"
    {
			g_op->clear_last_find_position();
		}
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1786 "../src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (3)].integer));
		}
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 1790 "../src/parser/parser.y"
    {
			g_op->listat(false);
		}
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 1794 "../src/parser/parser.y"
    {
			g_op->listat(true);
		}
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 1798 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 1803 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 284:
/* Line 1792 of yacc.c  */
#line 1808 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 1813 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 286:
/* Line 1792 of yacc.c  */
#line 1818 "../src/parser/parser.y"
    {
			if (g_op->push_mvar_using_space((yyvsp[(1) - (1)].cp)) == false) {
				yyerror("invalid object name in name'string' format");
			}
		}
    break;

  case 287:
/* Line 1792 of yacc.c  */
#line 1824 "../src/parser/parser.y"
    {
			g_op->clone(1);
		}
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 1828 "../src/parser/parser.y"
    {
			g_op->clone((yyvsp[(4) - (4)].integer));

			// this is not normal function call (virtual function call)
			// so it should mark that don't fast popping
			g_op->disable_fast_pop();
		}
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1841 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 1845 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
		}
    break;

  case 292:
/* Line 1792 of yacc.c  */
#line 1849 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 293:
/* Line 1792 of yacc.c  */
#line 1853 "../src/parser/parser.y"
    {
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 1858 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 1869 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 1873 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (3)].integer);
		}
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 1881 "../src/parser/parser.y"
    {
			g_op->fix_last_find_position();
		}
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 1889 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_OWNER;
		}
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 1893 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_CALLER;
		}
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 1897 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_ROOT;
		}
    break;

  case 302:
/* Line 1792 of yacc.c  */
#line 1901 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MODULE;
		}
    break;

  case 303:
/* Line 1792 of yacc.c  */
#line 1905 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MY;
		}
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 1913 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 1922 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 308:
/* Line 1792 of yacc.c  */
#line 1931 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 309:
/* Line 1792 of yacc.c  */
#line 1939 "../src/parser/parser.y"
    {
			g_op->add();

			g_op->push_string((yyvsp[(4) - (4)].cp));

			g_op->add();
		}
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 1951 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 1960 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 1965 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 1973 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 1981 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 1989 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 318:
/* Line 1792 of yacc.c  */
#line 1997 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 319:
/* Line 1792 of yacc.c  */
#line 2005 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 320:
/* Line 1792 of yacc.c  */
#line 2013 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;

  case 321:
/* Line 1792 of yacc.c  */
#line 2021 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;


/* Line 1792 of yacc.c  */
#line 4617 "../src/parser/parser.cpp"
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
#line 2027 "../src/parser/parser.y"



