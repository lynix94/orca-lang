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


const char* get_context();


/* Line 371 of yacc.c  */
#line 105 "../src/parser/parser.cpp"

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
     NAME = 312,
     STRING = 313,
     FORMAT_STRING_HEAD = 314,
     FORMAT_STRING_TAIL = 315,
     RE_STRING = 316,
     RE_FORMAT_STRING_HEAD = 317,
     HEX_STRING = 318,
     SHELL_STRING_HEAD = 319,
     CONTEXT = 320,
     NUMBER = 321,
     MINUS_NUMBER = 322,
     BIG_NUMBER = 323,
     MINUS_BIG_NUMBER = 324,
     REAL = 325,
     MINUS_REAL = 326
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 49 "../src/parser/parser.y"

	const char* cp;
	int integer;
	double real;
	void* vector_cp;	
	struct bnf* bp;	
	struct cp2_t cp2; 
	struct int2_t int2;


/* Line 387 of yacc.c  */
#line 230 "../src/parser/parser.cpp"
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
#line 258 "../src/parser/parser.cpp"

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
#define YYFINAL  154
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  158
/* YYNRULES -- Number of rules.  */
#define YYNRULES  318
/* YYNRULES -- Number of states.  */
#define YYNSTATES  524

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   326

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    86,     2,     2,    91,    81,     2,     2,
      82,    83,    89,    87,    76,    88,    77,    90,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    75,    74,
       2,    80,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    84,     2,    85,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,    79,    73,    78,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71
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
     825,   827,   829,   833,   837,   841,   842,   846,   851,   856,
     859,   862,   865,   868,   869,   873,   878,   880,   884,   885,
     889,   892,   894,   896,   899,   903,   905,   907,   909,   911,
     913,   915,   917,   920,   922,   925,   927,   932,   934,   936,
     938,   940,   942,   944,   946,   948,   950,   952,   954
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      93,     0,    -1,    93,    97,    -1,    93,    95,    -1,    97,
      -1,    97,    -1,    95,    -1,    72,    93,    73,    -1,    72,
      73,    -1,    93,    73,    -1,    73,    -1,   187,    -1,   123,
      -1,   125,    -1,   150,    -1,   153,    -1,   108,    -1,   120,
      -1,   104,    -1,   105,    -1,    98,    -1,   100,    -1,   122,
      -1,    74,    -1,    -1,   189,    99,    95,    -1,    -1,    54,
      16,   101,    94,    -1,    -1,    54,    22,   237,    23,   235,
     103,    75,   102,    94,    -1,    -1,    57,   189,    -1,    57,
     189,    57,   189,    -1,   229,    75,   188,    74,    -1,    -1,
     106,   107,    -1,   107,   240,    -1,    64,    -1,   109,   111,
      -1,   119,    -1,    -1,    35,   110,    95,    -1,    -1,   114,
     112,   113,    -1,   114,    -1,    37,    95,    -1,   114,   115,
      -1,   115,    -1,    -1,    36,   121,   116,    95,    -1,    -1,
      36,   121,    75,   168,   117,    95,    -1,    -1,    36,   118,
      95,    -1,    38,   121,    74,    -1,    38,   121,    76,   188,
      74,    -1,    42,   121,    74,    -1,    42,   121,    58,    74,
      -1,   121,    77,   152,    -1,   152,    -1,    40,    -1,    41,
      -1,    24,   124,    74,    -1,    25,    74,    -1,    26,    74,
      -1,    -1,   188,    -1,   169,    -1,   126,    -1,    -1,    20,
     189,   127,    72,   141,    73,    -1,   128,   129,    -1,   129,
      -1,    -1,   132,   130,    75,   131,    74,    -1,    78,    75,
     138,    74,    -1,   131,    79,   133,    -1,   133,    -1,   139,
      -1,    -1,   134,   135,    -1,   136,    -1,   136,   137,    -1,
     137,    -1,   138,    -1,   139,    -1,   140,    -1,    58,    -1,
      61,    -1,   243,    -1,   161,    -1,   141,   142,    -1,   142,
      -1,    -1,    -1,   143,   145,    52,   144,    94,    -1,   147,
      -1,   146,    -1,   149,    75,   149,    -1,   147,    76,   148,
      -1,   148,    -1,   189,    -1,   149,    -1,   149,    80,   189,
      -1,    81,   237,    -1,   185,    -1,   178,    -1,   182,    -1,
     180,    -1,     4,     5,    -1,     5,    -1,   243,    -1,    58,
      -1,   151,   152,    74,    -1,    -1,   151,   152,    55,   154,
     189,    74,    -1,    -1,   158,   166,   155,    95,    -1,   151,
      77,   152,   152,    72,    -1,    -1,   151,    77,    21,   152,
     167,   156,    72,   128,    73,    -1,    -1,   151,    77,    20,
     152,   167,   157,    72,   141,    73,    -1,   151,   152,   167,
      -1,    -1,    56,   160,    96,    -1,    -1,   163,   166,   162,
      95,    -1,   151,    77,   243,    72,    -1,   164,    72,   141,
      73,    -1,   165,    72,   128,    73,    -1,   151,   167,    -1,
     151,    77,    20,   167,    -1,   151,    77,    21,   167,    -1,
      -1,    75,   188,    -1,    -1,    82,    83,    -1,    82,    46,
      83,    -1,    82,   168,    83,    -1,    82,   168,    76,    46,
      83,    -1,   168,    76,   243,    -1,   243,    -1,   176,    -1,
     176,   174,    -1,   176,   170,   174,    -1,   176,   170,    -1,
     170,   171,    -1,   171,    -1,    -1,    -1,    14,   172,   201,
      75,   173,    94,    -1,    -1,    15,    75,   175,    94,    -1,
      -1,    13,   201,    75,   177,    94,    -1,    -1,    16,   179,
      94,    17,   201,    74,    -1,    -1,   189,    18,    16,   181,
      94,    -1,    -1,    -1,    17,   183,   201,    75,   184,    94,
      -1,    -1,    22,   237,    23,   235,    75,   186,    94,    -1,
     188,    74,    -1,   188,    76,   189,    -1,   189,    -1,   190,
      -1,   159,    -1,    -1,   237,   200,   191,   189,    -1,    -1,
     229,    77,   152,   200,   192,   189,    -1,    -1,   229,    77,
     236,   200,   193,   189,    -1,    -1,   229,    84,   232,    85,
     200,   194,   189,    -1,    -1,   229,    84,   232,    83,   200,
     195,   189,    -1,    -1,    45,   152,   200,   196,   189,    -1,
      -1,    45,   236,   200,   197,   189,    -1,    -1,    77,   152,
     200,   198,   189,    -1,    -1,    77,   236,   200,   199,   189,
      -1,   201,    -1,    80,    -1,    47,    -1,    48,    -1,    49,
      -1,    50,    -1,   202,    -1,    -1,   202,    30,   203,   204,
      -1,   204,    -1,    -1,   204,    29,   205,   206,    -1,   206,
      -1,    86,   207,    -1,   207,    -1,   208,    31,   208,    -1,
     208,    32,   208,    -1,   208,    33,   208,    -1,   208,    34,
     208,    -1,   208,    27,   208,    -1,   208,    28,   208,    -1,
     208,    -1,   209,    -1,   209,    87,   210,    -1,   209,    88,
     210,    -1,   209,   244,    -1,   209,   246,    -1,   209,   249,
      -1,   210,    -1,   210,    89,   235,    -1,   210,    90,   235,
      -1,   210,    81,   235,    -1,   211,    -1,    -1,    88,   212,
     235,    -1,    87,   235,    -1,   235,    -1,    84,   124,    85,
      -1,    84,   188,    76,    85,    -1,    84,   189,    45,   189,
      85,    -1,    84,   189,    45,   189,    75,   189,    85,    -1,
     216,    -1,    82,   188,    76,   189,    83,    -1,    82,   188,
      76,    83,    -1,    82,   189,    45,   189,    83,    -1,    82,
     189,    45,   189,    75,   189,    83,    -1,    72,   226,    73,
      -1,    72,   226,    76,    73,    -1,    -1,    -1,    81,    84,
     217,   219,    79,   218,   220,    85,    -1,   189,    -1,   220,
      76,   221,    -1,   221,    -1,   201,    -1,   222,    -1,   237,
      53,   189,    -1,   237,    53,   223,    -1,   224,    75,   189,
      -1,   224,    -1,   189,    78,   189,    -1,   189,    78,    -1,
      -1,    78,   225,   189,    -1,   226,    76,   227,    -1,   227,
      -1,   189,    75,   189,    -1,   213,    -1,   214,    -1,   215,
      -1,   161,    -1,   237,    -1,   245,    -1,   244,    -1,   247,
      -1,   246,    -1,   248,    -1,   249,    -1,   241,    -1,   242,
      -1,   236,    -1,    43,    -1,    44,    -1,    51,    -1,    82,
     189,    83,    -1,   229,    77,   152,    -1,   229,    77,   236,
      -1,    -1,   229,   230,   234,    -1,   229,    84,   232,    85,
      -1,   229,    84,   232,    83,    -1,    45,   152,    -1,    45,
     236,    -1,    77,   152,    -1,    77,   236,    -1,    -1,   243,
     231,   242,    -1,   229,    77,     6,   234,    -1,   228,    -1,
     189,    75,   189,    -1,    -1,    75,   233,   189,    -1,   189,
      75,    -1,    75,    -1,   189,    -1,    82,    83,    -1,    82,
     188,    83,    -1,   229,    -1,     8,    -1,     9,    -1,    10,
      -1,    11,    -1,     7,    -1,   243,    -1,   238,   240,    -1,
      59,    -1,   239,   240,    -1,    62,    -1,    91,    72,   189,
      60,    -1,    61,    -1,   239,    -1,    58,    -1,   238,    -1,
      63,    -1,    57,    -1,    67,    -1,    66,    -1,    69,    -1,
      68,    -1,    70,    -1,    71,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   181,   181,   182,   183,   188,   189,   194,   195,   200,
     201,   206,   216,   217,   218,   219,   220,   221,   222,   226,
     230,   231,   232,   233,   239,   238,   251,   250,   259,   258,
     270,   274,   288,   302,   310,   310,   323,   324,   332,   336,
     342,   341,   354,   353,   361,   366,   371,   372,   378,   377,
     386,   385,   395,   394,   406,   410,   418,   422,   430,   436,
     444,   448,   456,   460,   464,   473,   476,   484,   485,   491,
     490,   502,   503,   509,   508,   516,   526,   527,   532,   537,
     537,   546,   551,   556,   564,   565,   566,   571,   575,   583,
     593,   601,   602,   607,   611,   607,   622,   623,   628,   636,
     640,   648,   652,   656,   664,   672,   673,   674,   675,   680,
     684,   692,   696,   704,   709,   708,   722,   721,   731,   739,
     738,   766,   765,   798,   825,   824,   837,   836,   848,   863,
     871,   889,   921,   955,   982,   985,   994,   997,  1001,  1007,
    1011,  1021,  1027,  1037,  1041,  1045,  1051,  1061,  1065,  1074,
    1078,  1073,  1087,  1086,  1096,  1095,  1105,  1104,  1117,  1116,
    1129,  1133,  1128,  1145,  1144,  1156,  1164,  1168,  1176,  1177,
    1183,  1182,  1201,  1200,  1221,  1220,  1240,  1239,  1264,  1263,
    1288,  1287,  1309,  1308,  1330,  1329,  1351,  1350,  1371,  1376,
    1380,  1384,  1388,  1392,  1400,  1406,  1405,  1415,  1421,  1420,
    1430,  1435,  1439,  1444,  1448,  1452,  1456,  1460,  1464,  1468,
    1473,  1478,  1482,  1486,  1491,  1496,  1501,  1506,  1510,  1514,
    1518,  1524,  1523,  1534,  1535,  1540,  1544,  1548,  1552,  1556,
    1561,  1565,  1569,  1573,  1581,  1585,  1594,  1599,  1593,  1611,
    1616,  1617,  1622,  1626,  1634,  1638,  1646,  1647,  1655,  1656,
    1661,  1660,  1669,  1673,  1681,  1686,  1687,  1688,  1689,  1690,
    1701,  1705,  1709,  1713,  1717,  1721,  1725,  1729,  1733,  1737,
    1741,  1745,  1749,  1754,  1759,  1764,  1763,  1771,  1775,  1779,
    1784,  1789,  1794,  1800,  1799,  1809,  1817,  1822,  1827,  1826,
    1834,  1839,  1845,  1850,  1854,  1862,  1870,  1874,  1878,  1882,
    1886,  1894,  1902,  1903,  1911,  1912,  1920,  1932,  1936,  1941,
    1945,  1946,  1954,  1962,  1970,  1978,  1986,  1994,  2002
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
  "pair_expression", "primary_object", "postfix_object", "$@45", "$@46",
  "slice_expression", "$@47", "calling_body", "object", "reserved_object",
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
     325,   326,   123,   125,    59,    58,    44,    46,   126,   124,
      61,    37,    40,    41,    91,    93,    33,    43,    45,    42,
      47,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    93,    93,    94,    94,    95,    95,    96,
      96,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    99,    98,   101,   100,   102,   100,
     103,   103,   103,   104,   106,   105,   107,   107,   108,   108,
     110,   109,   112,   111,   111,   113,   114,   114,   116,   115,
     117,   115,   118,   115,   119,   119,   120,   120,   121,   121,
     122,   122,   123,   123,   123,   124,   124,   125,   125,   127,
     126,   128,   128,   130,   129,   129,   131,   131,   132,   134,
     133,   135,   136,   136,   137,   137,   137,   138,   138,   139,
     140,   141,   141,   143,   144,   142,   145,   145,   146,   147,
     147,   148,   148,   148,   149,   150,   150,   150,   150,   151,
     151,   152,   152,   153,   154,   153,   155,   153,   153,   156,
     153,   157,   153,   158,   160,   159,   162,   161,   161,   161,
     161,   163,   164,   165,   166,   166,   167,   167,   167,   167,
     167,   168,   168,   169,   169,   169,   169,   170,   170,   172,
     173,   171,   175,   174,   177,   176,   179,   178,   181,   180,
     183,   184,   182,   186,   185,   187,   188,   188,   189,   189,
     191,   190,   192,   190,   193,   190,   194,   190,   195,   190,
     196,   190,   197,   190,   198,   190,   199,   190,   190,   200,
     200,   200,   200,   200,   201,   203,   202,   202,   205,   204,
     204,   206,   206,   207,   207,   207,   207,   207,   207,   207,
     208,   209,   209,   209,   209,   209,   209,   210,   210,   210,
     210,   212,   211,   211,   211,   213,   213,   213,   213,   213,
     214,   214,   214,   214,   215,   215,   217,   218,   216,   219,
     220,   220,   221,   221,   222,   222,   223,   223,   224,   224,
     225,   224,   226,   226,   227,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   229,   229,   230,   229,   229,   229,   229,
     229,   229,   229,   231,   229,   229,   229,   232,   233,   232,
     232,   232,   232,   234,   234,   235,   236,   236,   236,   236,
     236,   237,   238,   238,   239,   239,   240,   241,   241,   242,
     242,   242,   243,   244,   245,   246,   247,   248,   249
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
       1,     1,     3,     3,     3,     0,     3,     4,     4,     2,
       2,     2,     2,     0,     3,     4,     1,     3,     0,     3,
       2,     1,     1,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      34,     0,   110,   300,   296,   297,   298,   299,     0,   156,
     160,     0,     0,    65,     0,     0,    40,     0,    60,    61,
       0,   269,   270,     0,   271,     0,   124,   312,   309,   303,
     307,   305,   311,   314,   313,   316,   315,   317,   318,     0,
      23,     0,     0,     0,    65,     0,     0,   221,    34,     4,
      20,    21,    18,    19,     0,    16,     0,    39,    17,    22,
      12,    13,    68,    14,   136,    15,   134,   169,   258,   134,
       0,     0,    67,   143,   106,   108,   107,   105,    11,     0,
     167,   168,   188,   194,   197,   200,   202,   209,   210,   216,
     220,   255,   256,   257,   229,   286,   295,   224,   268,   259,
     310,   308,   266,   267,   301,   261,   260,   263,   262,   264,
     265,   109,     0,     0,   136,     0,   295,   259,    34,     0,
      69,   295,     0,   301,     0,    66,   167,    63,    64,     0,
     112,     0,    59,   111,     0,   279,   280,    26,     0,    34,
       0,     0,   253,   281,   282,   236,     0,   167,     0,    66,
     167,   201,   223,     0,     1,    34,     3,     2,    37,    35,
      52,    38,    44,    47,     0,     0,   136,   131,     0,   116,
     126,    93,     0,   149,     0,   146,   148,   144,   165,     0,
       0,     0,   195,   198,     0,     0,     0,     0,     0,     0,
       0,     0,   213,   214,   215,     0,     0,     0,     0,     0,
       0,     0,   190,   191,   192,   193,   189,   170,     0,   302,
     304,     0,   279,   280,   281,   282,     0,   154,     0,     0,
       0,     6,     5,     0,     0,     0,    62,    34,    41,    54,
       0,     0,     0,    56,   180,   182,    34,     0,    10,    34,
     125,     0,   234,     0,   184,   186,     0,     0,     0,   272,
     225,     0,     0,   222,     8,    34,   167,    36,     0,    48,
       0,    46,   136,   136,     0,   111,     0,   137,     0,   142,
     114,   113,   123,   135,     0,     0,    93,    92,     0,     0,
       0,    72,    73,    78,    89,     0,   152,   147,   145,   166,
     158,    25,     0,     0,   207,   208,   203,   204,   205,   206,
     211,   212,   219,   217,   218,     0,     0,   273,   274,   288,
     292,     0,     0,   276,     0,     0,   284,   136,   136,     0,
      34,   273,   274,     0,     0,   161,    93,     0,     0,    58,
      57,     0,     0,    27,     0,     9,   254,   235,   252,     0,
       0,   239,     0,   231,   166,     0,   226,     0,     7,    53,
       0,     0,     0,    43,   136,   132,   136,   133,     0,   128,
     138,     0,   139,     0,   117,   127,   129,    91,     0,     0,
      97,    96,   100,   102,   101,     0,   130,    71,     0,     0,
      34,    34,   196,   199,    33,   285,   172,   174,     0,   290,
     278,   277,   293,     0,   171,     0,   155,   278,   277,     0,
      34,    93,   163,    55,   181,   183,    30,   185,   187,   237,
     230,     0,   232,     0,   227,    50,    49,    45,   121,   119,
     118,     0,   141,     0,   104,    94,     0,     0,     0,    87,
      88,     0,    79,   150,   153,   159,     0,     0,   289,   287,
     178,   176,   294,   306,   157,   162,    70,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   140,   115,    34,
      99,   102,     0,    98,   103,    75,     0,    77,     0,    34,
     173,   175,     0,     0,   164,    31,    28,   242,     0,   241,
     243,   259,   233,   228,    51,    93,     0,    95,    74,    79,
      80,    81,    83,    84,    85,    86,    90,   151,   179,   177,
       0,    34,     0,   238,     0,    93,     0,    76,    82,    32,
      29,   240,   250,   244,   245,   247,   122,   120,     0,   249,
       0,   251,   248,   246
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   255,   220,   221,   240,   222,    50,   181,    51,   236,
     501,   449,    52,    53,    54,   159,    55,    56,   129,   161,
     260,   353,   162,   163,   351,   454,   258,    57,    58,   131,
      59,    60,   124,    61,    62,   224,   280,   281,   378,   466,
     282,   467,   468,   490,   491,   492,   493,   283,   495,   276,
     277,   278,   459,   369,   370,   371,   372,   373,    63,   114,
     132,    65,   363,   274,   456,   455,    66,    67,   139,    68,
     275,    69,    70,    71,   169,   167,   268,    72,   175,   176,
     285,   469,   177,   380,    73,   320,    74,   118,    75,   381,
      76,   119,   400,    77,   447,    78,    79,    80,    81,   314,
     436,   437,   473,   472,   331,   332,   339,   340,   207,    82,
      83,   292,    84,   293,    85,    86,    87,    88,    89,    90,
     153,    91,    92,    93,    94,   246,   450,   342,   478,   479,
     480,   514,   515,   518,   141,   142,    95,   121,   201,   211,
     311,   388,   313,    97,    98,    99,   100,   101,   209,   102,
     103,   104,   105,   106,   107,   108,   109,   110
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -440
static const yytype_int16 yypact[] =
{
    1079,    22,  -440,  -440,  -440,  -440,  -440,  -440,  1929,  -440,
    -440,  1759,     4,  1759,    45,    49,  -440,   221,  -440,  -440,
     221,  -440,  -440,    88,  -440,   102,  -440,  -440,  -440,  -440,
    -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,  1759,
    -440,    88,    16,  1759,  1759,  2014,  2099,  -440,   648,  -440,
    -440,  -440,  -440,  -440,    83,  -440,    41,  -440,  -440,  -440,
    -440,  -440,  -440,  -440,    44,  -440,    89,  -440,  -440,    89,
     121,   139,  -440,    73,  -440,  -440,  -440,  -440,  -440,    53,
      -7,  -440,  -440,   144,   162,  -440,  -440,   243,    71,    26,
    -440,  -440,  -440,  -440,  -440,  -440,   113,  -440,  -440,    -4,
     116,   116,  -440,  -440,   141,  -440,  -440,  -440,  -440,  -440,
    -440,  -440,    88,    88,    -3,   147,    59,  -440,  1164,  1929,
    -440,   119,   216,  -440,   182,   189,  -440,  -440,  -440,   217,
    -440,   152,  -440,  -440,   103,    -4,    -4,  -440,     4,   739,
     223,   158,  -440,    -4,    -4,  -440,   229,   -33,   207,   247,
     274,  -440,  -440,  2099,  -440,   824,  -440,  -440,  -440,   116,
     221,  -440,   275,  -440,    -1,   -32,   -40,  -440,  1759,  -440,
    -440,  -440,     2,  -440,   252,    73,  -440,  -440,  -440,  1759,
     309,   217,  -440,  -440,  2014,  2014,  2014,  2014,  2014,  2014,
    2014,  2014,  -440,  -440,  -440,  2099,  2099,  2099,  1759,    75,
    1249,   256,  -440,  -440,  -440,  -440,  -440,  -440,   270,  -440,
    -440,   250,  -440,  -440,  -440,  -440,     3,  -440,    75,  1249,
     326,  -440,  -440,   269,   273,  2099,  -440,   824,  -440,  -440,
    1759,   221,   272,  -440,  -440,  -440,  1164,   324,  -440,   909,
    -440,  1759,  -440,  1334,  -440,  -440,  1759,  1419,  1759,  -440,
    -440,  1504,  1759,  -440,  -440,   994,     0,  -440,   217,   -13,
     312,  -440,     9,     9,   221,   278,   268,  -440,    77,  -440,
    -440,  -440,  -440,   189,   217,   217,   280,  -440,  1844,   279,
      32,  -440,  -440,  -440,  -440,  1929,  -440,  -440,  -440,  -440,
    -440,  -440,  1929,  1929,  -440,  -440,  -440,  -440,  -440,  -440,
      26,    26,  -440,  -440,  -440,   187,   256,    -4,    -4,    54,
     282,   132,  1589,  -440,  1759,  1759,  -440,   276,   276,   278,
    1164,  -440,  -440,   179,  1929,  -440,  -440,   284,   210,  -440,
    -440,  1759,  1759,  -440,  2099,  -440,  -440,  -440,  -440,  1759,
    1759,  -440,   281,  -440,   285,   -44,  -440,    19,  -440,  -440,
       4,   217,   217,  -440,   276,  -440,   276,  -440,   290,  -440,
    -440,   -10,  -440,  1759,  -440,  -440,  -440,  -440,   -31,   311,
    -440,   288,  -440,    90,  -440,   117,  -440,  -440,   292,   294,
    1164,  1164,   162,  -440,  -440,  -440,  -440,  -440,  1759,  1759,
      -4,    -4,  -440,   100,  -440,   313,  -440,  -440,  -440,   300,
    1164,   303,  -440,  -440,  -440,  -440,   322,  -440,  -440,  -440,
    -440,  1759,  -440,  1759,  -440,   304,  -440,  -440,  -440,  -440,
    -440,   298,  -440,   308,  -440,  -440,  1844,   305,  1759,  -440,
    -440,   310,  -440,  -440,  -440,  -440,  1759,  1759,  -440,  -440,
    -440,  -440,  -440,  -440,  -440,  -440,  -440,  1164,  1759,   314,
    1929,   302,   306,     4,   217,   318,   320,  -440,  -440,  1164,
    -440,   315,     4,  -440,  -440,  -440,   135,  -440,    12,  1164,
    -440,  -440,  1759,  1759,  -440,   339,  -440,  -440,    37,  -440,
    -440,   350,  -440,  -440,  -440,  -440,     2,  -440,  -440,  -440,
    -440,    12,  -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,
    1759,  1164,  1929,  -440,  1674,   331,    57,  -440,  -440,  -440,
    -440,  -440,  -440,   327,  -440,   332,  -440,  -440,  1759,  1759,
    1759,  -440,  -440,  -440
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -440,    13,  -214,    42,  -440,    30,  -440,  -440,  -440,  -440,
    -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,
    -440,  -440,  -440,   244,  -440,  -440,  -440,  -440,  -440,   -12,
    -440,  -440,   364,  -440,  -440,  -440,   -77,  -279,  -440,  -440,
    -440,   -79,  -440,  -440,  -440,   -80,    38,  -439,  -440,  -322,
    -267,  -440,  -440,  -440,  -440,  -440,   -14,   -90,  -440,    55,
     202,  -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,  -433,
    -440,  -440,  -440,  -440,   345,  -112,    66,  -440,  -440,   246,
    -440,  -440,   248,  -440,  -440,  -440,  -440,  -440,  -440,  -440,
    -440,  -440,  -440,  -440,  -440,  -440,    -6,   -11,  -440,  -440,
    -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,   -95,    -2,
    -440,  -440,   126,  -440,   129,   374,   146,  -440,   150,  -440,
    -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,  -440,   -78,
    -440,  -440,  -440,  -440,  -440,   184,  -440,    63,  -440,  -440,
     209,  -440,   123,   -41,   -20,   353,  -440,  -440,   -91,  -440,
     219,   108,   343,  -440,   344,  -440,  -440,   346
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -292
static const yytype_int16 yytable[] =
{
     120,   377,   126,   136,   401,   152,   115,   125,   134,   367,
     210,   180,   248,    48,   266,   270,     1,     2,   180,   262,
     263,   144,   333,   317,   318,    27,    27,   111,   140,   494,
      49,   411,   147,   150,   271,   496,   421,   146,   149,   412,
     234,   235,   165,   202,   203,   204,   205,    27,   244,   245,
     249,   267,   494,   145,   272,    64,    27,   130,   496,    27,
      27,    27,   350,    96,   231,   -24,    27,   130,   257,    27,
     429,   116,   -24,   430,   216,   241,   206,   160,   157,   165,
     279,   306,     3,     4,     5,     6,     7,   173,   174,    27,
     156,   165,   213,   215,   413,     3,     4,     5,     6,     7,
     145,    27,   130,    64,   414,   376,   396,   195,   116,   116,
     279,    96,   253,   502,    27,   196,   197,   223,   137,   127,
     123,   164,   503,   128,   138,   133,   165,   178,   133,   179,
     517,   133,    27,   130,   367,   279,   218,  -291,    34,  -291,
      36,  -275,    38,   219,   256,    27,   130,   158,   259,   133,
     355,   357,   239,   361,   302,   303,   304,   126,   190,   191,
     362,   232,   273,   505,   168,   427,   434,   435,   289,    49,
     428,   228,   133,    64,   182,   429,   179,   233,   430,   308,
     231,    96,   116,   442,   327,    49,   445,   126,   198,   310,
     199,   183,   305,   171,    64,  -275,   199,   200,   322,  -283,
    -283,  -275,    96,   200,  -283,   355,   357,   208,   310,   488,
      64,   172,   386,   387,   489,   390,   116,   391,    96,   126,
     133,   133,   217,   291,   328,   135,   229,   377,   230,   231,
     336,   242,   140,   474,   243,   341,   344,   345,   367,   225,
     289,   347,   418,   143,   419,   487,   123,   116,   116,   116,
     116,   116,   116,   116,   116,   497,   226,    49,   116,   116,
     116,   384,   397,   179,   398,   179,   166,   374,   133,   157,
     184,   185,   265,   269,   186,   187,   188,   189,    27,   130,
     284,   156,    64,   379,   403,   157,   179,   510,   116,   227,
      96,    64,   250,   406,    64,   440,   441,   156,   241,    96,
     349,   126,    96,   394,   395,   247,   393,   133,    28,    29,
      64,   160,   -42,    32,   212,   214,   364,   365,    96,   252,
     404,   405,   399,   251,   319,   290,   133,   286,   407,   408,
     294,   295,   296,   297,   298,   299,   461,   463,   312,   133,
     300,   301,   315,   324,   325,   326,   330,   334,   116,   352,
     359,   360,   423,   366,   375,   116,   116,   389,   165,   402,
     409,   117,   420,   425,   426,   122,   264,   432,   410,   433,
     133,   133,   133,   443,   444,    64,   446,   438,   439,   448,
     453,   457,   458,    96,   465,   482,   462,   116,   284,   476,
     485,   483,   486,   416,   417,   428,   500,   116,   117,   117,
     451,   307,   452,   504,   516,   519,   261,   520,   148,   506,
     507,   508,   460,   431,   170,   374,   415,   464,   382,   151,
     321,   287,   383,   288,   511,   470,   471,   338,   323,   385,
     316,   192,   193,   329,   194,    64,    64,   475,     0,     0,
       0,     0,     0,    96,    96,     0,     0,     0,   477,     0,
       0,     0,     0,     0,     0,    64,     0,     0,   269,     0,
       0,   498,   499,    96,   354,   356,   358,     0,     0,   422,
       0,     0,   117,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   509,
       0,   237,     0,   513,     0,     0,   484,     0,     0,     0,
     477,     0,    64,     0,     0,     0,   117,   521,   522,   523,
      96,     0,     0,   116,    64,     0,     0,     0,     0,     0,
       0,     0,    96,     0,    64,     0,     0,     0,     0,     0,
       0,     0,    96,     0,     0,     0,     0,   117,   117,   117,
     117,   117,   117,   117,   117,     0,     0,     0,   117,   117,
     117,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,   422,     0,     0,    96,   116,     0,     0,     0,     0,
     123,     0,     0,     0,     0,     0,   284,     0,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   284,     0,     0,     0,     0,   284,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   284,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,     0,
       0,     0,     0,     0,     0,   117,   117,     0,   154,     0,
       0,     0,     1,     2,     0,     3,     4,     5,     6,     7,
       0,     8,     0,     0,     9,    10,     0,     0,    11,     0,
      12,     0,    13,    14,    15,     0,     0,   117,     0,     0,
       0,     0,     0,    16,     0,     0,    17,   117,    18,    19,
      20,    21,    22,    23,     0,     0,     0,     0,     0,    24,
       0,     0,    25,     0,    26,    27,    28,    29,     0,    30,
      31,    32,     0,     0,    33,    34,    35,    36,    37,    38,
     155,   424,    40,     0,     0,    41,     0,     0,     0,    42,
      43,     0,    44,     0,    45,    46,    47,     0,     0,     0,
       0,     0,     0,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     8,     0,     0,     9,    10,     0,     0,    11,
       0,    12,     0,    13,    14,    15,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     0,     0,    17,     0,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,    25,     0,    26,    27,    28,    29,     0,
      30,    31,    32,   481,     0,    33,    34,    35,    36,    37,
      38,    39,   238,    40,     0,   424,    41,     0,     0,     0,
      42,    43,     0,    44,     0,    45,    46,    47,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     8,     0,     0,
       9,    10,     0,     0,    11,     0,    12,     0,    13,    14,
      15,     0,     0,     0,     0,   481,     0,     0,     0,    16,
       0,     0,    17,     0,    18,    19,    20,    21,    22,    23,
       0,     0,     0,     0,     0,    24,     0,     0,    25,     0,
      26,    27,    28,    29,     0,    30,    31,    32,     0,     0,
      33,    34,    35,    36,    37,    38,    39,   254,    40,     0,
       0,    41,     0,     0,     0,    42,    43,     0,    44,     0,
      45,    46,    47,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     8,     0,     0,     9,    10,     0,     0,    11,
       0,    12,     0,    13,    14,    15,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     0,     0,    17,     0,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,    25,     0,    26,    27,    28,    29,     0,
      30,    31,    32,     0,     0,    33,    34,    35,    36,    37,
      38,   155,   335,    40,     0,     0,    41,     0,     0,     0,
      42,    43,     0,    44,     0,    45,    46,    47,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     8,     0,     0,
       9,    10,     0,     0,    11,     0,    12,     0,    13,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,    16,
       0,     0,    17,     0,    18,    19,    20,    21,    22,    23,
       0,     0,     0,     0,     0,    24,     0,     0,    25,     0,
      26,    27,    28,    29,     0,    30,    31,    32,     0,     0,
      33,    34,    35,    36,    37,    38,   155,   348,    40,     0,
       0,    41,     0,     0,     0,    42,    43,     0,    44,     0,
      45,    46,    47,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     8,     0,     0,     9,    10,     0,     0,    11,
       0,    12,     0,    13,    14,    15,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     0,     0,    17,     0,    18,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,    25,     0,    26,    27,    28,    29,     0,
      30,    31,    32,     0,     0,    33,    34,    35,    36,    37,
      38,    39,     0,    40,     0,     0,    41,     0,     0,     0,
      42,    43,     0,    44,     0,    45,    46,    47,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     8,     0,     0,
       9,    10,     0,     0,    11,     0,    12,     0,    13,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,    16,
       0,     0,    17,     0,    18,    19,    20,    21,    22,    23,
       0,     0,     0,     0,     0,    24,     0,     0,    25,     0,
      26,    27,    28,    29,     0,    30,    31,    32,     0,     0,
      33,    34,    35,    36,    37,    38,   155,     0,    40,     0,
       0,    41,     0,     0,     0,    42,    43,     0,    44,     0,
      45,    46,    47,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,    26,    27,    28,    29,     0,
      30,    31,    32,     0,     0,    33,    34,    35,    36,    37,
      38,    39,     0,     0,   309,     0,    41,     0,     0,     0,
      42,    43,     0,    44,     0,    45,    46,    47,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
       0,     0,     0,     0,     0,    24,     0,     0,     0,     0,
      26,    27,    28,    29,     0,    30,    31,    32,     0,     0,
      33,    34,    35,    36,    37,    38,    39,   337,     0,     0,
       0,    41,     0,     0,     0,    42,    43,     0,    44,     0,
      45,    46,    47,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,    26,    27,    28,    29,     0,
      30,    31,    32,     0,     0,    33,    34,    35,    36,    37,
      38,    39,     0,     0,     0,     0,    41,     0,     0,     0,
      42,    43,   343,    44,     0,    45,    46,    47,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
       0,     0,     0,     0,     0,    24,     0,     0,     0,     0,
      26,    27,    28,    29,     0,    30,    31,    32,     0,     0,
      33,    34,    35,    36,    37,    38,    39,     0,     0,     0,
       0,    41,     0,     0,     0,    42,    43,     0,    44,   346,
      45,    46,    47,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,    26,    27,    28,    29,     0,
      30,    31,    32,     0,     0,    33,    34,    35,    36,    37,
      38,    39,     0,     0,     0,     0,    41,     0,     0,     0,
      42,    43,   392,    44,     0,    45,    46,    47,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
       0,     0,     0,     0,     0,    24,     0,     0,     0,     0,
      26,    27,    28,    29,     0,    30,    31,    32,     0,     0,
      33,    34,    35,    36,    37,    38,    39,     0,     0,     0,
       0,    41,   512,     0,     0,    42,    43,     0,    44,     0,
      45,    46,    47,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,    26,    27,    28,    29,     0,
      30,    31,    32,     0,     0,    33,    34,    35,    36,    37,
      38,    39,     0,     0,     0,     0,    41,     0,     0,     0,
      42,    43,     0,    44,     0,    45,    46,    47,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
       0,     0,     0,     0,     0,    24,     0,     0,     0,     0,
      26,    27,    28,    29,     0,    30,    31,    32,     0,     0,
      33,    34,    35,    36,    37,    38,    39,     0,     0,     0,
       0,    41,     0,     0,     0,   368,    43,     0,    44,     0,
      45,    46,    47,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,   112,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,     0,    27,    28,    29,     0,
      30,    31,    32,     0,     0,    33,    34,    35,    36,    37,
      38,    39,     0,     0,     0,     0,   113,     0,     0,     0,
      42,    43,     0,    44,     0,    45,    46,    47,     1,     2,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,   112,
       0,     0,     0,     0,     0,    24,     0,     0,     0,     0,
       0,    27,    28,    29,     0,    30,    31,    32,     0,     0,
      33,    34,    35,    36,    37,    38,    39,     0,     0,     0,
       0,   113,     0,     0,     0,    42,    43,     0,    44,     0,
       0,    46,    47,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,   112,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,     0,    27,    28,    29,     0,
      30,    31,    32,     0,     0,    33,    34,    35,    36,    37,
      38,    39,     0,     0,     0,     0,   113,     0,     0,     0,
      42,    43,     0,    44
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-440)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      11,   280,    13,    23,   326,    46,     8,    13,    20,   276,
     101,    18,    45,     0,    46,    55,     4,     5,    18,    20,
      21,    41,   236,    20,    21,    57,    57,     5,    39,   468,
       0,    75,    43,    44,    74,   468,    46,    43,    44,    83,
     135,   136,    82,    47,    48,    49,    50,    57,   143,   144,
      83,    83,   491,    84,   166,     0,    57,    58,   491,    57,
      57,    57,    75,     0,    77,    72,    57,    58,   159,    57,
      58,     8,    72,    61,    77,    75,    80,    36,    48,    82,
      78,     6,     7,     8,     9,    10,    11,    14,    15,    57,
      48,    82,   112,   113,    75,     7,     8,     9,    10,    11,
      84,    57,    58,    48,    85,    73,   320,    81,    45,    46,
      78,    48,   153,    76,    57,    89,    90,   119,    16,    74,
      12,    77,    85,    74,    22,    17,    82,    74,    20,    76,
      73,    23,    57,    58,   401,    78,    77,    83,    67,    85,
      69,    82,    71,    84,   155,    57,    58,    64,   160,    41,
     262,   263,   139,    76,   195,   196,   197,   168,    87,    88,
      83,    58,   168,   485,    75,    75,   380,   381,   179,   139,
      80,   129,    64,   118,    30,    58,    76,    74,    61,   199,
      77,   118,   119,    83,   225,   155,   400,   198,    75,   200,
      77,    29,   198,    72,   139,    82,    77,    84,   218,    58,
      59,    82,   139,    84,    63,   317,   318,    91,   219,    74,
     155,    72,   307,   308,    79,    83,   153,    85,   155,   230,
     112,   113,    75,   181,   230,    23,    74,   506,    76,    77,
     241,    73,   243,   447,    76,   246,   247,   248,   505,    23,
     251,   252,   354,    41,   356,   459,   138,   184,   185,   186,
     187,   188,   189,   190,   191,   469,    74,   227,   195,   196,
     197,    74,    83,    76,    85,    76,    64,   278,   160,   239,
      27,    28,   164,   165,    31,    32,    33,    34,    57,    58,
     172,   239,   227,   285,    74,   255,    76,   501,   225,    72,
     227,   236,    85,   334,   239,   390,   391,   255,    75,   236,
     258,   312,   239,   314,   315,    76,   312,   199,    58,    59,
     255,    36,    37,    63,   112,   113,   274,   275,   255,    45,
     331,   332,   324,    76,   216,    16,   218,    75,   339,   340,
     184,   185,   186,   187,   188,   189,   426,   427,    82,   231,
     190,   191,    72,    17,    75,    72,    74,    23,   285,    37,
      72,    83,   363,    73,    75,   292,   293,    75,    82,    75,
      79,     8,    72,    52,    76,    12,   164,    75,    83,    75,
     262,   263,   264,    60,    74,   320,    73,   388,   389,    57,
      76,    83,    74,   320,    74,    83,    81,   324,   280,    75,
      72,    85,    72,   351,   352,    80,    57,   334,    45,    46,
     411,   199,   413,    53,    73,    78,   162,    75,    44,   486,
     489,   491,   426,   375,    69,   426,   350,   428,   292,    45,
     218,   175,   293,   175,   502,   436,   437,   243,   219,   306,
     211,    88,    88,   231,    88,   380,   381,   448,    -1,    -1,
      -1,    -1,    -1,   380,   381,    -1,    -1,    -1,   450,    -1,
      -1,    -1,    -1,    -1,    -1,   400,    -1,    -1,   350,    -1,
      -1,   472,   473,   400,   262,   263,   264,    -1,    -1,   361,
      -1,    -1,   119,    -1,    -1,    -1,   368,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   500,
      -1,   138,    -1,   504,    -1,    -1,   454,    -1,    -1,    -1,
     502,    -1,   447,    -1,    -1,    -1,   153,   518,   519,   520,
     447,    -1,    -1,   450,   459,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   459,    -1,   469,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   469,    -1,    -1,    -1,    -1,   184,   185,   186,
     187,   188,   189,   190,   191,    -1,    -1,    -1,   195,   196,
     197,    -1,    -1,    -1,    -1,    -1,   501,    -1,    -1,    -1,
      -1,   453,    -1,    -1,   501,   502,    -1,    -1,    -1,    -1,
     462,    -1,    -1,    -1,    -1,    -1,   468,    -1,   225,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   486,    -1,    -1,    -1,    -1,   491,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   506,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   285,    -1,
      -1,    -1,    -1,    -1,    -1,   292,   293,    -1,     0,    -1,
      -1,    -1,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,    -1,
      22,    -1,    24,    25,    26,    -1,    -1,   324,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    38,   334,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    54,    -1,    56,    57,    58,    59,    -1,    61,
      62,    63,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,   368,    74,    -1,    -1,    77,    -1,    -1,    -1,    81,
      82,    -1,    84,    -1,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,
      -1,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    54,    -1,    56,    57,    58,    59,    -1,
      61,    62,    63,   450,    -1,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,   462,    77,    -1,    -1,    -1,
      81,    82,    -1,    84,    -1,    86,    87,    88,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    13,    -1,    -1,
      16,    17,    -1,    -1,    20,    -1,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,   502,    -1,    -1,    -1,    35,
      -1,    -1,    38,    -1,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    54,    -1,
      56,    57,    58,    59,    -1,    61,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    -1,    84,    -1,
      86,    87,    88,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,
      -1,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    54,    -1,    56,    57,    58,    59,    -1,
      61,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    -1,    84,    -1,    86,    87,    88,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    13,    -1,    -1,
      16,    17,    -1,    -1,    20,    -1,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    -1,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    54,    -1,
      56,    57,    58,    59,    -1,    61,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    -1,    84,    -1,
      86,    87,    88,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,
      -1,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    54,    -1,    56,    57,    58,    59,    -1,
      61,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    -1,    84,    -1,    86,    87,    88,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    13,    -1,    -1,
      16,    17,    -1,    -1,    20,    -1,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    -1,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    54,    -1,
      56,    57,    58,    59,    -1,    61,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    -1,    74,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    -1,    84,    -1,
      86,    87,    88,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    -1,
      61,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    75,    -1,    77,    -1,    -1,    -1,
      81,    82,    -1,    84,    -1,    86,    87,    88,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    -1,    61,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    -1,    84,    -1,
      86,    87,    88,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    -1,
      61,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    83,    84,    -1,    86,    87,    88,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    -1,    61,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    -1,    84,    85,
      86,    87,    88,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    -1,
      61,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    83,    84,    -1,    86,    87,    88,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    -1,    61,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    77,    78,    -1,    -1,    81,    82,    -1,    84,    -1,
      86,    87,    88,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    -1,
      61,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    -1,    84,    -1,    86,    87,    88,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    -1,    61,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    -1,    84,    -1,
      86,    87,    88,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,
      61,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    -1,    84,    -1,    86,    87,    88,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    -1,    61,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    -1,    84,    -1,
      -1,    87,    88,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,
      61,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    82,    -1,    84
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     7,     8,     9,    10,    11,    13,    16,
      17,    20,    22,    24,    25,    26,    35,    38,    40,    41,
      42,    43,    44,    45,    51,    54,    56,    57,    58,    59,
      61,    62,    63,    66,    67,    68,    69,    70,    71,    72,
      74,    77,    81,    82,    84,    86,    87,    88,    93,    97,
      98,   100,   104,   105,   106,   108,   109,   119,   120,   122,
     123,   125,   126,   150,   151,   153,   158,   159,   161,   163,
     164,   165,   169,   176,   178,   180,   182,   185,   187,   188,
     189,   190,   201,   202,   204,   206,   207,   208,   209,   210,
     211,   213,   214,   215,   216,   228,   229,   235,   236,   237,
     238,   239,   241,   242,   243,   244,   245,   246,   247,   248,
     249,     5,    45,    77,   151,   201,   229,   237,   179,   183,
     189,   229,   237,   243,   124,   188,   189,    74,    74,   110,
      58,   121,   152,   243,   121,   152,   236,    16,    22,   160,
     189,   226,   227,   152,   236,    84,   188,   189,   124,   188,
     189,   207,   235,   212,     0,    72,    95,    97,    64,   107,
      36,   111,   114,   115,    77,    82,   152,   167,    75,   166,
     166,    72,    72,    14,    15,   170,   171,   174,    74,    76,
      18,    99,    30,    29,    27,    28,    31,    32,    33,    34,
      87,    88,   244,   246,   249,    81,    89,    90,    75,    77,
      84,   230,    47,    48,    49,    50,    80,   200,    91,   240,
     240,   231,   152,   236,   152,   236,    77,    75,    77,    84,
      94,    95,    97,   201,   127,    23,    74,    72,    95,    74,
      76,    77,    58,    74,   200,   200,   101,   237,    73,    93,
      96,    75,    73,    76,   200,   200,   217,    76,    45,    83,
      85,    76,    45,   235,    73,    93,   189,   240,   118,   121,
     112,   115,    20,    21,   152,   243,    46,    83,   168,   243,
      55,    74,   167,   188,   155,   162,   141,   142,   143,    78,
     128,   129,   132,   139,   243,   172,    75,   171,   174,   189,
      16,    95,   203,   205,   208,   208,   208,   208,   208,   208,
     210,   210,   235,   235,   235,   188,     6,   152,   236,    75,
     189,   232,    82,   234,   191,    72,   242,    20,    21,   243,
     177,   152,   236,   232,    17,    75,    72,   235,   188,   152,
      74,   196,   197,    94,    23,    73,   189,    73,   227,   198,
     199,   189,   219,    83,   189,   189,    85,   189,    73,    95,
      75,   116,    37,   113,   152,   167,   152,   167,   152,    72,
      83,    76,    83,   154,    95,    95,    73,   142,    81,   145,
     146,   147,   148,   149,   189,    75,    73,   129,   130,   201,
     175,   181,   204,   206,    74,   234,   200,   200,   233,    75,
      83,    85,    83,   188,   189,   189,    94,    83,    85,   201,
     184,   141,    75,    74,   189,   189,   235,   189,   189,    79,
      83,    75,    83,    75,    85,   168,    95,    95,   167,   167,
      72,    46,   243,   189,   237,    52,    76,    75,    80,    58,
      61,   138,    75,    75,    94,    94,   192,   193,   189,   189,
     200,   200,    83,    60,    74,    94,    73,   186,    57,   103,
     218,   189,   189,    76,   117,   157,   156,    83,    74,   144,
     148,   149,    81,   149,   189,    74,   131,   133,   134,   173,
     189,   189,   195,   194,    94,   189,    75,   201,   220,   221,
     222,   237,    83,    85,    95,    72,    72,    94,    74,    79,
     135,   136,   137,   138,   139,   140,   161,    94,   189,   189,
      57,   102,    76,    85,    53,   141,   128,   133,   137,   189,
      94,   221,    78,   189,   223,   224,    73,    73,   225,    78,
      75,   189,   189,   189
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
#line 207 "../src/parser/parser.y"
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
#line 223 "../src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 227 "../src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 239 "../src/parser/parser.y"
    {
			g_op->do_scope_start();
		}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 243 "../src/parser/parser.y"
    {
			g_op->do_scope_end();
		}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 251 "../src/parser/parser.y"
    {
			g_ctl->parallel_start();
		}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 255 "../src/parser/parser.y"
    {
			g_ctl->parallel_end();
		}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 259 "../src/parser/parser.y"
    {
			g_ctl->parallel_for_start((yyvsp[(3) - (7)].cp));
		}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 263 "../src/parser/parser.y"
    {
			g_ctl->parallel_for_end();
		}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 270 "../src/parser/parser.y"
    {
			g_op->push_integer(0);	// by
			g_op->push_integer(1);	// per
		}
    break;

  case 31:
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

  case 32:
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

  case 33:
/* Line 1792 of yacc.c  */
#line 303 "../src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (4)].integer));
		}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 310 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_ROOT);
			g_op->find_member("os");
			g_op->find_member("run");
		}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 316 "../src/parser/parser.y"
    {	
			g_op->call(1);
		}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 325 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 333 "../src/parser/parser.y"
    {
			g_ex->pop();
		}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 342 "../src/parser/parser.y"
    {
			g_ex->push();
		}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 346 "../src/parser/parser.y"
    {
			g_ex->goto_end();
		}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 354 "../src/parser/parser.y"
    {
			g_ex->do_finally();
		}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 358 "../src/parser/parser.y"
    {
			g_ex->goto_end();
		}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 378 "../src/parser/parser.y"
    {
			g_ex->catch_start((yyvsp[(2) - (2)].cp));
		}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 382 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 386 "../src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(4) - (4)].vector_cp);
			g_ex->catch_start((yyvsp[(2) - (4)].cp), vp);
		}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 391 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 395 "../src/parser/parser.y"
    {
			g_ex->catch_start(NULL);
		}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 399 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 407 "../src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (3)].cp), 0);
		}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 411 "../src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (5)].cp), (yyvsp[(4) - (5)].integer));
		}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 419 "../src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (3)].cp), NULL);
		}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 423 "../src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (4)].cp), (yyvsp[(3) - (4)].cp));
		}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 431 "../src/parser/parser.y"
    {
			char buff[1024];
			sprintf(buff, "%s.%s", (yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
			(yyval.cp) = parser_strdup(buff);
		}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 437 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 445 "../src/parser/parser.y"
    {
			g_op->dump_stack();
		}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 449 "../src/parser/parser.y"
    {
			g_op->dump_local();
		}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 457 "../src/parser/parser.y"
    {
			g_ctl->do_return((yyvsp[(2) - (3)].integer));
		}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 461 "../src/parser/parser.y"
    {
			g_ctl->do_continue();
		}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 465 "../src/parser/parser.y"
    {
			g_ctl->do_break();
		}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 473 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 477 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 491 "../src/parser/parser.y"
    {
			g_ctl->decode_start();
		}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 495 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
		}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 509 "../src/parser/parser.y"
    {
			g_parse->set_current_bnf((yyvsp[(1) - (1)].bp));
		}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 513 "../src/parser/parser.y"
    {

		}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 517 "../src/parser/parser.y"
    {
			bnf* b = (yyvsp[(3) - (4)].bp);
			b->type = BNF_WS;
		}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 537 "../src/parser/parser.y"
    {
			g_bnf_right_num = 1;
			g_parse->current_bnf()->add_rule();
		}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 552 "../src/parser/parser.y"
    {
			g_bnf_right_num++;
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(2) - (2)].bp));
		}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 557 "../src/parser/parser.y"
    {
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(1) - (1)].bp));
		}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 572 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp));
		}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 576 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp), true);
		}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 584 "../src/parser/parser.y"
    {
			string name = "`\a";
			name += (yyvsp[(1) - (1)].cp);
			(yyval.bp) = g_parse->get_nonterm_bnf(name);
		}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 594 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_action_bnf(g_bnf_right_num);
		}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 607 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_start();
		}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 611 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_shift();
		}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 615 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_end();
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 629 "../src/parser/parser.y"
    {
			g_ctl->decode_cut_list((yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
		}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 637 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 641 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 649 "../src/parser/parser.y"
    {
			g_ctl->decode_match_expr();
		}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 653 "../src/parser/parser.y"
    {
			g_ctl->decode_shift((yyvsp[(1) - (1)].cp));
		}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 657 "../src/parser/parser.y"
    {
			g_ctl->decode_match_and_assign((yyvsp[(1) - (3)].cp));
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 665 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(2) - (2)].cp);
		}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 681 "../src/parser/parser.y"
    {
			(yyval.integer) = BIT_DEFINE_STATIC;
		}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 685 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 693 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 697 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 705 "../src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
		}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 709 "../src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
			code_top->init_object_start((yyvsp[(2) - (3)].cp));

			g_op->push_reserved(OP_PUSH_MY);
		}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 716 "../src/parser/parser.y"
    {
			g_op->assign_member((yyvsp[(2) - (6)].cp));
			g_op->pop_stack();
			code_top->init_object_done();
		}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 722 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer)) {
				code_top->make_super((yyvsp[(2) - (2)].integer));
			}
		}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 728 "../src/parser/parser.y"
    {
			parserCode::pop_code_stack();
		}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 732 "../src/parser/parser.y"
    {
			const char* cp = get_context();
			print("get_context(): '%s'\n", cp);
			code_top->do_context((yyvsp[(3) - (5)].cp), (yyvsp[(4) - (5)].cp), cp);
			//TODO: fail check
		}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 739 "../src/parser/parser.y"
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
#line 755 "../src/parser/parser.y"
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
#line 766 "../src/parser/parser.y"
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
#line 790 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();
		}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 799 "../src/parser/parser.y"
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
#line 825 "../src/parser/parser.y"
    {
			g_ctl->once_start();
		}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 829 "../src/parser/parser.y"
    {
			g_ctl->once_end();
		}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 837 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer)) {
				code_top->make_super((yyvsp[(2) - (2)].integer));
			}
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 843 "../src/parser/parser.y"
    {
			parserCode::pop_code_stack();
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(1) - (4)].cp));
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 849 "../src/parser/parser.y"
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
#line 864 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(1) - (4)].cp));
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 872 "../src/parser/parser.y"
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
#line 890 "../src/parser/parser.y"
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
#line 922 "../src/parser/parser.y"
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
#line 956 "../src/parser/parser.y"
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
#line 982 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 986 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (2)].integer);
		}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 994 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 998 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1002 "../src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1008 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = (yyvsp[(2) - (3)].vector_cp);
		}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1012 "../src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(2) - (5)].vector_cp);
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1022 "../src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(1) - (3)].vector_cp);
			vs->push_back((yyvsp[(3) - (3)].cp));
			(yyval.vector_cp) = vs;
		}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1028 "../src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back((yyvsp[(1) - (1)].cp));
			(yyval.vector_cp) = vs;
		}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1038 "../src/parser/parser.y"
    {
			g_ctl->if_end();
		}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1042 "../src/parser/parser.y"
    {
			g_ctl->else_end();
		}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1046 "../src/parser/parser.y"
    {
			g_ctl->else_end();
			for(int i=0; i<(yyvsp[(2) - (3)].integer); i++)
				g_ctl->else_end();
		}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1052 "../src/parser/parser.y"
    {
			g_ctl->if_end();
			for(int i=0; i<(yyvsp[(2) - (2)].integer); i++)
				g_ctl->else_end();
		}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1062 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer) + 1;
		}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1066 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1074 "../src/parser/parser.y"
    {
			g_ctl->else_start();
		}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1078 "../src/parser/parser.y"
    {
			g_ctl->if_start();
		}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1087 "../src/parser/parser.y"
    {
			g_ctl->else_start();
		}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1096 "../src/parser/parser.y"
    {
			g_ctl->if_start();
		}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1105 "../src/parser/parser.y"
    {
			g_ctl->do_start();
		}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1109 "../src/parser/parser.y"
    {
			g_ctl->do_end();
		}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1117 "../src/parser/parser.y"
    {
			g_ctl->times_start();
		}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1121 "../src/parser/parser.y"
    {
			g_ctl->times_end();
		}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1129 "../src/parser/parser.y"
    {
			g_ctl->while_start_1();
		}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1133 "../src/parser/parser.y"
    {
			g_ctl->while_start_2();
		}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1137 "../src/parser/parser.y"
    {
			g_ctl->while_end();
		}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1145 "../src/parser/parser.y"
    {
			g_ctl->for_start((yyvsp[(2) - (5)].cp));
		}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1149 "../src/parser/parser.y"
    {
			g_ctl->for_end();
		}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1157 "../src/parser/parser.y"
    { 
			(yyval.integer) = (yyvsp[(1) - (2)].integer); 
		}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1165 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1169 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1183 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer) != '=') {
				g_op->push_lvar((yyvsp[(1) - (2)].cp));
			}
		}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1189 "../src/parser/parser.y"
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
#line 1201 "../src/parser/parser.y"
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
#line 1209 "../src/parser/parser.y"
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
#line 1221 "../src/parser/parser.y"
    {
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_reserved((yyvsp[(3) - (4)].integer));
			}
		}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1228 "../src/parser/parser.y"
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
#line 1240 "../src/parser/parser.y"
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
#line 1248 "../src/parser/parser.y"
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
#line 1264 "../src/parser/parser.y"
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
#line 1272 "../src/parser/parser.y"
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
#line 1288 "../src/parser/parser.y"
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
#line 1297 "../src/parser/parser.y"
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
#line 1309 "../src/parser/parser.y"
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
#line 1318 "../src/parser/parser.y"
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
#line 1330 "../src/parser/parser.y"
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
#line 1339 "../src/parser/parser.y"
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
#line 1351 "../src/parser/parser.y"
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
#line 1360 "../src/parser/parser.y"
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
#line 1377 "../src/parser/parser.y"
    {
			(yyval.integer) = '='; 
		}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1381 "../src/parser/parser.y"
    { 
			(yyval.integer) = '+'; 
		}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1385 "../src/parser/parser.y"
    { 
			(yyval.integer) = '-'; 
		}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1389 "../src/parser/parser.y"
    { 
			(yyval.integer) = '*'; 
		}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1393 "../src/parser/parser.y"
    { 
			(yyval.integer) = '/'; 
		}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1406 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start(false);
		}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1411 "../src/parser/parser.y"
    {
			g_op->do_or();
			g_ctl->if_end();
		}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1421 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start();
		}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1426 "../src/parser/parser.y"
    {
			g_op->do_and();
			g_ctl->if_end();
		}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1436 "../src/parser/parser.y"
    {
			g_op->do_not();
		}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1445 "../src/parser/parser.y"
    {
			g_op->gt();
		}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1449 "../src/parser/parser.y"
    {
			g_op->ge();
		}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1453 "../src/parser/parser.y"
    {
			g_op->lt();
		}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1457 "../src/parser/parser.y"
    {
			g_op->le();
		}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1461 "../src/parser/parser.y"
    {
			g_op->eq();
		}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1465 "../src/parser/parser.y"
    {
			g_op->neq();
		}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1479 "../src/parser/parser.y"
    {
			g_op->add();
		}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1483 "../src/parser/parser.y"
    {
			g_op->sub();
		}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1487 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(2) - (2)].integer));
			g_op->add();
		}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1492 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(2) - (2)].cp));
			g_op->add();
		}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1497 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(2) - (2)].real));
			g_op->add();
		}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1507 "../src/parser/parser.y"
    {
			g_op->mul();
		}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1511 "../src/parser/parser.y"
    {
			g_op->div();
		}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1515 "../src/parser/parser.y"
    {
			g_op->mod();
		}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1524 "../src/parser/parser.y"
    {
			unary_minus = true;
		}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1528 "../src/parser/parser.y"
    {
			if (unary_minus)
				g_op->minus();

			unary_minus = false;
		}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1541 "../src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (3)].integer));
		}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1545 "../src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (4)].integer));
		}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1549 "../src/parser/parser.y"
    {
			g_op->make_list(-2);
		}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1553 "../src/parser/parser.y"
    {
			g_op->make_list(-3);
		}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1562 "../src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (5)].integer) + 1);
		}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1566 "../src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (4)].integer));
		}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1570 "../src/parser/parser.y"
    {
			g_op->make_tuple(-2);
		}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1574 "../src/parser/parser.y"
    {
			g_op->make_tuple(-3);
		}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1582 "../src/parser/parser.y"
    {
			g_op->make_map((yyvsp[(2) - (3)].integer));
		}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1586 "../src/parser/parser.y"
    {
			g_op->make_map((yyvsp[(2) - (4)].integer));
		}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1594 "../src/parser/parser.y"
    {
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1599 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule_start();
		}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1603 "../src/parser/parser.y"
    {
			g_ctl->sbf_end();
			g_lvar_nil_check++;
		}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1623 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule();
		}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1627 "../src/parser/parser.y"
    {
			g_ctl->sbf_in();
		}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1635 "../src/parser/parser.y"
    {
			g_ctl->sbf_list_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1639 "../src/parser/parser.y"
    {
			g_ctl->sbf_range_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1648 "../src/parser/parser.y"
    {
			g_op->push_integer(1);
		}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 1657 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 1661 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1670 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 1674 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 1691 "../src/parser/parser.y"
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
#line 1702 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 1706 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1710 "../src/parser/parser.y"
    {
			g_op->push_bignum('+', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 1714 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1718 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 1722 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1726 "../src/parser/parser.y"
    {
			g_op->make_regex();
		}
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1730 "../src/parser/parser.y"
    {
			// already in stack
		}
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 1734 "../src/parser/parser.y"
    {
			g_op->push_reserved((yyvsp[(1) - (1)].integer));
		}
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 1738 "../src/parser/parser.y"
    {
			g_op->push_boolean(true);
		}
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 1742 "../src/parser/parser.y"
    {
			g_op->push_boolean(false);
		}
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 1746 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 1755 "../src/parser/parser.y"
    {
			g_op->set_last_find_position();
			g_op->find_member((yyvsp[(3) - (3)].cp));
		}
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 1760 "../src/parser/parser.y"
    {
			g_op->find_reserved((yyvsp[(3) - (3)].integer));
		}
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 1764 "../src/parser/parser.y"
    {
			g_op->clear_last_find_position();
		}
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1768 "../src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (3)].integer));
		}
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1772 "../src/parser/parser.y"
    {
			g_op->listat(false);
		}
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 1776 "../src/parser/parser.y"
    {
			g_op->listat(true);
		}
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1780 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 1785 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 1790 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 1795 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 1800 "../src/parser/parser.y"
    {
			if (g_op->push_mvar_using_space((yyvsp[(1) - (1)].cp)) == false) {
				yyerror("invalid object name in name'string' format");
			}
		}
    break;

  case 284:
/* Line 1792 of yacc.c  */
#line 1806 "../src/parser/parser.y"
    {
			g_op->clone(1);
		}
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 1810 "../src/parser/parser.y"
    {
			g_op->clone((yyvsp[(4) - (4)].integer));

			// this is not normal function call (virtual function call)
			// so it should mark that don't fast popping
			g_op->disable_fast_pop();
		}
    break;

  case 287:
/* Line 1792 of yacc.c  */
#line 1823 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 1827 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
		}
    break;

  case 289:
/* Line 1792 of yacc.c  */
#line 1831 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1835 "../src/parser/parser.y"
    {
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 1840 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 293:
/* Line 1792 of yacc.c  */
#line 1851 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 1855 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (3)].integer);
		}
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 1863 "../src/parser/parser.y"
    {
			g_op->fix_last_find_position();
		}
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 1871 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_OWNER;
		}
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 1875 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_CALLER;
		}
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 1879 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_ROOT;
		}
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 1883 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MODULE;
		}
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 1887 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MY;
		}
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 1895 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 303:
/* Line 1792 of yacc.c  */
#line 1904 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 305:
/* Line 1792 of yacc.c  */
#line 1913 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 1921 "../src/parser/parser.y"
    {
			g_op->add();

			g_op->push_string((yyvsp[(4) - (4)].cp));

			g_op->add();
		}
    break;

  case 307:
/* Line 1792 of yacc.c  */
#line 1933 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 309:
/* Line 1792 of yacc.c  */
#line 1942 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 311:
/* Line 1792 of yacc.c  */
#line 1947 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 1955 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 313:
/* Line 1792 of yacc.c  */
#line 1963 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 1971 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 1979 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 1987 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 1995 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;

  case 318:
/* Line 1792 of yacc.c  */
#line 2003 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;


/* Line 1792 of yacc.c  */
#line 4592 "../src/parser/parser.cpp"
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
#line 2009 "../src/parser/parser.y"



