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
#line 49 "../src/parser/parser.y"

	const char* cp;
	int integer;
	double real;
	void* vector_cp;	
	struct bnf* bp;	
	struct cp2_t cp2; 
	struct int2_t int2;


/* Line 387 of yacc.c  */
#line 231 "../src/parser/parser.cpp"
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
#line 259 "../src/parser/parser.cpp"

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
#define YYFINAL  163
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2011

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  160
/* YYNRULES -- Number of rules.  */
#define YYNRULES  321
/* YYNRULES -- Number of states.  */
#define YYNSTATES  520

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
     322,   326,   327,   334,   335,   340,   341,   348,   354,   355,
     359,   362,   364,   369,   373,   376,   377,   380,   381,   384,
     388,   392,   398,   402,   404,   406,   409,   413,   416,   419,
     421,   422,   423,   430,   431,   436,   437,   443,   444,   451,
     452,   458,   459,   460,   467,   468,   476,   479,   483,   485,
     489,   493,   496,   498,   500,   501,   506,   507,   514,   515,
     522,   523,   531,   532,   540,   541,   547,   548,   554,   555,
     561,   562,   568,   570,   572,   574,   576,   578,   580,   582,
     583,   588,   590,   591,   596,   598,   601,   603,   607,   611,
     615,   619,   623,   627,   629,   631,   635,   639,   642,   645,
     648,   650,   654,   658,   662,   664,   665,   669,   672,   674,
     678,   683,   689,   697,   699,   703,   708,   714,   722,   726,
     727,   728,   737,   739,   743,   745,   747,   749,   753,   757,
     761,   763,   767,   770,   771,   775,   779,   781,   785,   787,
     789,   791,   793,   795,   797,   799,   801,   803,   805,   807,
     809,   811,   813,   815,   817,   819,   823,   827,   831,   832,
     836,   841,   846,   849,   852,   855,   858,   859,   863,   868,
     870,   874,   875,   879,   882,   884,   886,   889,   893,   895,
     897,   899,   901,   903,   905,   907,   910,   912,   915,   917,
     922,   924,   926,   928,   930,   932,   934,   936,   938,   940,
     942,   944
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
      -1,    20,   166,   161,    73,   144,    74,    -1,     5,    78,
     246,   246,    73,    -1,    -1,    57,   163,    97,    -1,   167,
      96,    -1,   165,    -1,     5,    78,   246,    73,    -1,   156,
     157,   169,    -1,   156,   169,    -1,    -1,    76,   190,    -1,
      -1,    83,    84,    -1,    83,    46,    84,    -1,    83,   170,
      84,    -1,    83,   170,    77,    46,    84,    -1,   170,    77,
     246,    -1,   246,    -1,   178,    -1,   178,   176,    -1,   178,
     172,   176,    -1,   178,   172,    -1,   172,   173,    -1,   173,
      -1,    -1,    -1,    14,   174,   204,    76,   175,    95,    -1,
      -1,    15,    76,   177,    95,    -1,    -1,    13,   204,    76,
     179,    95,    -1,    -1,    16,   181,    95,    17,   204,    75,
      -1,    -1,   192,    18,    16,   183,    95,    -1,    -1,    -1,
      17,   185,   204,    76,   186,    95,    -1,    -1,    22,   240,
      23,   238,    76,   188,    95,    -1,   190,    75,    -1,   190,
      77,   192,    -1,   192,    -1,   191,    77,   192,    -1,   192,
      77,   192,    -1,   192,    77,    -1,   193,    -1,   162,    -1,
      -1,   240,   203,   194,   192,    -1,    -1,   232,    78,   157,
     203,   195,   192,    -1,    -1,   232,    78,   239,   203,   196,
     192,    -1,    -1,   232,    85,   235,    86,   203,   197,   192,
      -1,    -1,   232,    85,   235,    84,   203,   198,   192,    -1,
      -1,    45,   157,   203,   199,   192,    -1,    -1,    45,   239,
     203,   200,   192,    -1,    -1,    78,   157,   203,   201,   192,
      -1,    -1,    78,   239,   203,   202,   192,    -1,   204,    -1,
      81,    -1,    47,    -1,    48,    -1,    49,    -1,    50,    -1,
     205,    -1,    -1,   205,    30,   206,   207,    -1,   207,    -1,
      -1,   207,    29,   208,   209,    -1,   209,    -1,    87,   210,
      -1,   210,    -1,   211,    31,   211,    -1,   211,    32,   211,
      -1,   211,    33,   211,    -1,   211,    34,   211,    -1,   211,
      27,   211,    -1,   211,    28,   211,    -1,   211,    -1,   212,
      -1,   212,    88,   213,    -1,   212,    89,   213,    -1,   212,
     247,    -1,   212,   249,    -1,   212,   252,    -1,   213,    -1,
     213,    90,   238,    -1,   213,    91,   238,    -1,   213,    82,
     238,    -1,   214,    -1,    -1,    89,   215,   238,    -1,    88,
     238,    -1,   238,    -1,    85,   125,    86,    -1,    85,   190,
      77,    86,    -1,    85,   192,    45,   192,    86,    -1,    85,
     192,    45,   192,    76,   192,    86,    -1,   219,    -1,    83,
     191,    84,    -1,    83,   190,    77,    84,    -1,    83,   192,
      45,   192,    84,    -1,    83,   192,    45,   192,    76,   192,
      84,    -1,    73,   229,    74,    -1,    -1,    -1,    82,    85,
     220,   222,    80,   221,   223,    86,    -1,   192,    -1,   223,
      77,   224,    -1,   224,    -1,   204,    -1,   225,    -1,   240,
      54,   192,    -1,   240,    54,   226,    -1,   227,    76,   192,
      -1,   227,    -1,   192,    79,   192,    -1,   192,    79,    -1,
      -1,    79,   228,   192,    -1,   229,    77,   230,    -1,   230,
      -1,   192,    76,   192,    -1,   216,    -1,   217,    -1,   218,
      -1,   164,    -1,   240,    -1,   248,    -1,   247,    -1,   250,
      -1,   249,    -1,   251,    -1,   252,    -1,   244,    -1,   245,
      -1,   239,    -1,    43,    -1,    44,    -1,    52,    -1,    83,
     192,    84,    -1,   232,    78,   157,    -1,   232,    78,   239,
      -1,    -1,   232,   233,   237,    -1,   232,    85,   235,    86,
      -1,   232,    85,   235,    84,    -1,    45,   157,    -1,    45,
     239,    -1,    78,   157,    -1,    78,   239,    -1,    -1,   246,
     234,   245,    -1,   232,    78,     6,   237,    -1,   231,    -1,
     192,    76,   192,    -1,    -1,    76,   236,   192,    -1,   192,
      76,    -1,    76,    -1,   192,    -1,    83,    84,    -1,    83,
     190,    84,    -1,   232,    -1,     8,    -1,     9,    -1,    10,
      -1,    11,    -1,     7,    -1,   246,    -1,   241,   243,    -1,
      60,    -1,   242,   243,    -1,    63,    -1,    92,    73,   192,
      61,    -1,    62,    -1,   242,    -1,    59,    -1,   241,    -1,
      64,    -1,    58,    -1,    68,    -1,    67,    -1,    70,    -1,
      69,    -1,    71,    -1,    72,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   183,   183,   184,   185,   190,   191,   196,   197,   202,
     203,   208,   218,   219,   220,   221,   222,   223,   224,   228,
     232,   233,   234,   235,   236,   242,   241,   254,   253,   262,
     261,   273,   277,   291,   305,   313,   313,   326,   327,   335,
     339,   345,   344,   357,   356,   364,   369,   374,   375,   381,
     380,   389,   388,   398,   397,   409,   413,   421,   425,   433,
     439,   447,   451,   459,   463,   467,   476,   479,   487,   488,
     494,   493,   506,   505,   536,   537,   543,   542,   550,   560,
     561,   566,   571,   571,   580,   585,   590,   598,   599,   600,
     605,   609,   617,   627,   635,   636,   641,   645,   641,   656,
     657,   662,   670,   674,   682,   686,   690,   698,   706,   707,
     708,   709,   714,   718,   726,   730,   738,   742,   750,   754,
     762,   767,   766,   780,   779,   790,   789,   799,   811,   810,
     822,   828,   833,   852,   877,   910,   913,   922,   925,   929,
     935,   939,   949,   955,   965,   969,   973,   979,   989,   993,
    1002,  1006,  1001,  1015,  1014,  1024,  1023,  1033,  1032,  1045,
    1044,  1057,  1061,  1056,  1073,  1072,  1084,  1092,  1096,  1104,
    1108,  1112,  1120,  1121,  1127,  1126,  1145,  1144,  1165,  1164,
    1184,  1183,  1208,  1207,  1232,  1231,  1253,  1252,  1274,  1273,
    1295,  1294,  1315,  1320,  1324,  1328,  1332,  1336,  1344,  1350,
    1349,  1359,  1365,  1364,  1374,  1379,  1383,  1388,  1392,  1396,
    1400,  1404,  1408,  1412,  1417,  1422,  1426,  1430,  1435,  1440,
    1445,  1450,  1454,  1458,  1462,  1468,  1467,  1478,  1479,  1484,
    1488,  1492,  1496,  1500,  1505,  1509,  1513,  1517,  1525,  1534,
    1539,  1533,  1551,  1556,  1557,  1562,  1566,  1574,  1578,  1586,
    1587,  1595,  1596,  1601,  1600,  1609,  1613,  1621,  1626,  1627,
    1628,  1629,  1630,  1641,  1645,  1649,  1653,  1657,  1661,  1665,
    1669,  1673,  1677,  1681,  1685,  1689,  1694,  1699,  1704,  1703,
    1711,  1715,  1719,  1724,  1729,  1734,  1740,  1739,  1749,  1757,
    1762,  1767,  1766,  1774,  1779,  1785,  1790,  1794,  1802,  1810,
    1814,  1818,  1822,  1826,  1834,  1842,  1843,  1851,  1852,  1860,
    1872,  1876,  1881,  1885,  1886,  1894,  1902,  1910,  1918,  1926,
    1934,  1942
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
     216,   216,   216,   216,   217,   217,   217,   217,   218,   220,
     221,   219,   222,   223,   223,   224,   224,   225,   225,   226,
     226,   227,   227,   228,   227,   229,   229,   230,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   232,   232,   233,   232,
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
       4,     5,     7,     1,     3,     4,     5,     7,     3,     0,
       0,     8,     1,     3,     1,     1,     1,     3,     3,     3,
       1,     3,     2,     0,     3,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     0,     3,
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
      35,   114,   117,   303,   299,   300,   301,   302,     0,   157,
     161,     0,     0,     0,    66,     0,     0,    41,     0,    61,
      62,     0,   272,   273,     0,   115,   274,     0,   128,   315,
     312,   306,   310,   308,   314,   317,   316,   319,   318,   320,
     321,     0,    24,     0,     0,     0,    66,     0,     0,   225,
      35,     4,    20,    21,    18,    19,     0,    16,     0,    40,
      17,    23,    12,    13,    69,    22,    14,     0,   113,   137,
      15,   173,   261,   131,   135,     0,    68,   144,   109,   111,
     110,   108,    11,     0,   168,   172,   192,   198,   201,   204,
     206,   213,   214,   220,   224,   258,   259,   260,   233,   289,
     298,   228,   271,   262,   313,   311,   269,   270,   304,   264,
     263,   266,   265,   267,   268,     0,   117,     0,     0,   137,
       0,   298,   228,   262,    35,     0,   137,   125,    70,     0,
       0,   304,     0,    67,   168,    64,    65,     0,   119,     0,
      60,   118,     0,   282,   283,    27,     0,    35,     0,     0,
     256,   284,   285,   239,     0,     0,     0,     0,    67,   168,
     205,   227,     0,     1,    35,     3,     2,    38,    36,    53,
      39,    45,    48,   116,   112,     0,   137,   134,     0,   123,
      35,   130,   150,     0,   147,   149,   145,   166,     0,     0,
       0,   199,   202,     0,     0,     0,     0,     0,     0,     0,
       0,   217,   218,   219,     0,     0,     0,     0,     0,     0,
       0,   194,   195,   196,   197,   193,   174,     0,   305,   307,
       0,     0,     0,   282,   283,   284,   285,   155,     0,     0,
       0,     6,     5,     0,   137,     0,     0,   137,     0,    63,
      42,    55,     0,     0,     0,    57,   184,   186,    35,     0,
      10,    35,   129,     0,   238,     0,   188,   190,     0,     0,
       0,   234,     0,   171,   275,   229,     0,     0,   226,     8,
      35,   168,    37,     0,    49,     0,    47,     0,   138,     0,
     143,   121,   120,   133,   136,     0,     0,   153,   148,   146,
     167,   159,    26,     0,     0,   211,   212,   207,   208,   209,
     210,   215,   216,   223,   221,   222,     0,   276,   277,   291,
     295,     0,     0,   279,     0,     0,     0,   287,   132,     0,
       0,    35,   276,   277,     0,     0,   162,    96,    96,    72,
       0,     0,    59,    58,     0,     0,    28,     0,     9,   257,
     255,     0,     0,   242,     0,   235,   169,     0,   170,   230,
       0,     7,    54,     0,     0,     0,    44,   139,     0,   140,
       0,   124,     0,    35,    35,   200,   203,   288,   176,   178,
       0,   293,   281,   280,   296,     0,    34,   175,     0,   127,
     156,   281,   280,     0,    35,    96,    95,     0,    96,     0,
     164,    56,   185,   187,    31,   189,   191,   240,     0,   236,
       0,   231,    51,    50,    46,     0,   142,     0,   151,   154,
     160,     0,     0,   292,   290,   182,   180,   297,   309,   158,
     163,   126,    94,     0,     0,   100,    99,   103,   105,   104,
      71,     0,    35,     0,     0,     0,     0,     0,     0,     0,
     141,   122,    35,   177,   179,     0,     0,   107,    97,     0,
       0,     0,     0,     0,    75,    76,    81,    92,   165,    32,
      29,   245,     0,   244,   246,   262,   237,   232,    52,   152,
     183,   181,    35,   102,   105,     0,   101,   106,     0,    73,
      74,     0,     0,    35,     0,   241,     0,    98,    90,    91,
       0,    82,    33,    30,   243,   253,   247,   248,   250,    78,
       0,    80,     0,     0,   252,     0,    77,    82,    83,    84,
      86,    87,    88,    89,    93,   254,   251,   249,    79,    85
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   270,   230,   231,   252,   232,    52,   190,    53,   248,
     483,   434,    54,    55,    56,   168,    57,    58,   137,   170,
     275,   356,   171,   172,   354,   439,   273,    59,    60,   139,
      61,    62,   132,    63,    64,   236,    65,   389,   453,   454,
     481,   500,   455,   501,   502,   508,   509,   510,   511,   456,
     513,   385,   386,   387,   472,   424,   425,   426,   427,   428,
      66,    67,    68,   119,   140,    70,   360,   285,   235,    71,
     147,    72,    73,    74,    75,   179,   177,   279,    76,   184,
     185,   286,   442,   186,   363,    77,   321,    78,   124,    79,
     364,    80,   125,   384,    81,   432,    82,    83,   155,    84,
      85,   315,   411,   412,   446,   445,   334,   335,   341,   342,
     216,    86,    87,   293,    88,   294,    89,    90,    91,    92,
      93,    94,   162,    95,    96,    97,    98,   258,   435,   344,
     462,   463,   464,   497,   498,   503,   149,   150,    99,   100,
     209,   220,   311,   370,   313,   122,   102,   103,   104,   105,
     218,   106,   107,   108,   109,   110,   111,   112,   113,   114
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -336
static const yytype_int16 yypact[] =
{
    1066,  -336,   -44,  -336,  -336,  -336,  -336,  -336,  1754,  -336,
    -336,  1582,   123,     3,  1582,   -30,    65,  -336,   169,  -336,
    -336,   169,  -336,  -336,    56,  -336,  -336,   116,  -336,  -336,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  1582,  -336,    56,   -16,  1582,  1582,  1840,  1926,  -336,
     627,  -336,  -336,  -336,  -336,  -336,    85,  -336,   137,  -336,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,    39,  -336,    -7,
    -336,  -336,  -336,  -336,   105,   114,  -336,   240,  -336,  -336,
    -336,  -336,  -336,    94,     2,  -336,  -336,   175,   170,  -336,
    -336,   264,    57,    44,  -336,  -336,  -336,  -336,  -336,  -336,
      64,   147,  -336,   -22,   118,   118,  -336,  -336,   124,  -336,
    -336,  -336,  -336,  -336,  -336,     3,   151,    56,    56,   153,
     164,    70,  -336,  -336,  1152,  1754,    -7,  -336,  -336,   169,
     223,  -336,   176,   187,  -336,  -336,  -336,   114,  -336,   143,
    -336,  -336,    32,   -22,   -22,  -336,     3,   722,   207,    67,
    -336,   -22,   -22,  -336,   208,   -61,   -27,   200,   210,   243,
    -336,  -336,  1926,  -336,   808,  -336,  -336,  -336,   118,   169,
    -336,   237,  -336,  -336,  -336,    36,   -15,  -336,  1582,  -336,
     808,  -336,  -336,   213,   240,  -336,  -336,  -336,  1582,   278,
     114,  -336,  -336,  1840,  1840,  1840,  1840,  1840,  1840,  1840,
    1840,  -336,  -336,  -336,  1926,  1926,  1926,    78,   513,   216,
    1582,  -336,  -336,  -336,  -336,  -336,  -336,   234,  -336,  -336,
     152,   -41,     3,  -336,  -336,  -336,  -336,  -336,    78,   513,
     291,  -336,  -336,   233,   153,   238,   247,   153,  1926,  -336,
    -336,  -336,  1582,   169,   235,  -336,  -336,  -336,  1152,   298,
    -336,   894,  -336,  1582,  -336,  1582,  -336,  -336,  1582,  1238,
    1582,  -336,  1582,  1582,  -336,  -336,  1324,  1582,  -336,  -336,
     980,    -3,  -336,   114,   101,   285,  -336,   239,  -336,    40,
    -336,  -336,  -336,  -336,   187,   114,  1754,  -336,  -336,  -336,
    -336,  -336,  -336,  1754,  1754,  -336,  -336,  -336,  -336,  -336,
    -336,    44,    44,  -336,  -336,  -336,   216,   -22,   -22,   140,
     250,   149,  1410,  -336,   183,  1582,  1582,  -336,  -336,   254,
     257,  1152,  -336,  -336,   181,  1754,  -336,  -336,  -336,  -336,
     258,   195,  -336,  -336,  1582,  1582,  -336,  1926,  -336,  -336,
    -336,  1582,  1582,  -336,   255,  -336,  -336,   -55,  -336,  -336,
      45,  -336,  -336,     3,   114,   114,  -336,  -336,    60,  -336,
    1582,  -336,   260,  1152,  1152,   170,  -336,  -336,  -336,  -336,
    1582,  1582,   -22,   -22,  -336,    88,  -336,  -336,   272,  -336,
    -336,  -336,  -336,   262,  1152,   265,  -336,  1668,   267,   269,
    -336,  -336,  -336,  -336,   280,  -336,  -336,  -336,  1582,  -336,
    1582,  -336,   266,  -336,  -336,   263,  -336,   271,  -336,  -336,
    -336,  1582,  1582,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,   -39,   295,  -336,   274,  -336,    17,  -336,
    -336,    20,  1152,  1582,   273,  1754,   268,   270,     3,   114,
    -336,  -336,  1152,  -336,  -336,  1582,  1582,  -336,  -336,  1668,
     275,  1582,   277,    21,  -336,  -336,  -336,  -336,  -336,   297,
    -336,  -336,    53,  -336,  -336,   304,  -336,  -336,  -336,  -336,
    -336,  -336,  1152,  -336,   281,     3,  -336,  -336,   134,  -336,
    -336,   283,  1582,  1152,  1754,  -336,  1496,  -336,  -336,  -336,
     289,  -336,  -336,  -336,  -336,  -336,   286,  -336,   290,  -336,
     110,  -336,    50,  1582,  1582,  1582,  -336,  -336,  -336,    50,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -336,    14,  -241,   -26,  -336,    12,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,   196,  -336,  -336,  -336,  -336,  -336,   -11,
    -336,  -336,   322,  -336,  -336,  -336,  -336,  -336,  -336,   -84,
    -336,  -336,  -336,  -136,  -336,  -336,  -336,  -137,  -105,  -335,
    -336,    46,  -171,  -336,  -336,  -336,  -336,  -336,   -74,  -174,
    -336,  -336,   309,    42,    34,  -336,  -336,  -336,  -336,  -336,
    -336,  -327,  -336,   368,  -336,  -336,  -163,    27,  -336,  -336,
     197,  -336,  -336,   198,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,    -8,  -336,   -10,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -104,    -6,  -336,  -336,    92,  -336,    93,   339,   120,  -336,
      79,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,   -95,  -336,  -336,  -336,  -336,  -336,   136,  -336,   336,
    -336,  -336,   163,  -336,    87,    33,   -21,   253,  -336,  -336,
     -96,  -336,   174,   -13,   303,  -336,   306,  -336,  -336,   308
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -295
static const yytype_int16 yytable[] =
{
     131,   128,   120,   144,   134,   141,   133,   336,   141,   219,
     142,   141,    51,   283,    50,   189,   260,    29,   262,    29,
     189,   398,   152,   261,   165,   211,   212,   213,   214,   399,
     141,   148,   318,   101,   115,   156,   159,   154,   158,   246,
     247,   281,    69,     1,   173,   135,   153,   256,   257,   181,
     263,    29,   138,   126,     1,   116,   141,   264,   143,   215,
     282,    29,   166,     3,     4,     5,     6,     7,   175,   153,
     -25,   283,   272,   253,   329,   -25,   175,   151,    29,    29,
     380,   161,   277,   101,   306,     3,     4,     5,     6,     7,
      25,   244,    69,   450,    29,   479,   224,   226,   451,   452,
     452,    25,   221,   176,   141,   141,   405,   245,    29,   488,
     243,   240,   489,   141,    29,   138,   141,   358,    29,   233,
     278,   400,   409,   410,   359,    36,   204,    38,   129,    40,
     484,   401,   145,   131,   205,   206,    29,   138,   146,   485,
     136,   254,   207,   420,   255,   199,   200,  -278,   228,   208,
     167,   223,   225,  -278,   271,   229,   141,   101,   274,    51,
     234,   251,   280,   237,   292,   188,    69,   512,   134,   187,
     284,   188,   417,   169,   512,   514,    51,   353,   290,   243,
     101,   178,   514,  -286,  -286,   506,   308,   180,  -286,    69,
     507,   458,    51,   488,   141,   268,   489,   101,   310,   192,
     134,   469,   314,   368,   369,   191,    69,   323,   319,   320,
     217,    30,    31,   101,   422,   141,    34,   422,   241,   310,
     242,   243,    69,   210,  -294,   165,  -294,    29,   138,   222,
     141,   487,   134,   372,   331,   373,   175,   303,   304,   305,
     227,   307,   493,   339,   165,   148,   238,   352,   343,   290,
     346,   239,   347,   348,   182,   183,   290,   350,   376,   361,
     188,   123,   322,   166,   188,   381,   130,   382,   415,   416,
     391,   330,   188,   169,   -43,   474,   476,   332,   301,   302,
     362,   101,   166,   253,   101,   259,   265,   266,   267,   287,
      69,   193,   194,    69,   291,   195,   196,   197,   198,   312,
     123,   123,   134,   101,   375,   377,   378,   316,   325,   326,
     333,   327,    69,   295,   296,   297,   298,   299,   300,   383,
     328,   337,   355,   357,   392,   393,   371,   379,   403,   404,
     318,   395,   396,   418,   390,   397,   408,   419,   433,   421,
     280,   430,   431,   438,   121,   406,   441,   440,   448,   460,
     407,   449,   466,   478,   101,   482,   467,   475,   486,   491,
     413,   414,   451,    69,   499,   504,   505,   276,   157,   480,
     394,   518,   519,   490,   388,   473,   174,   429,   123,   127,
     402,   288,   289,   121,   121,   365,   160,   366,   436,   494,
     437,   340,   324,   367,   317,   201,   101,   101,   202,   249,
     203,   443,   444,     0,     0,    69,    69,     0,     0,     0,
     131,     0,     0,   468,     0,   123,     0,   101,   457,     0,
       0,     0,     0,   459,     0,   406,    69,     0,     0,   461,
       0,     0,     0,     0,     0,   470,   471,     0,     0,   429,
     457,   477,     0,     0,     0,     0,   123,   123,   123,   123,
     123,   123,   123,   123,     0,     0,     0,   123,   123,   123,
       0,   121,   131,     0,     0,   101,     0,     0,     0,     0,
       0,     0,   492,     0,    69,   101,   496,     0,   461,     0,
       0,     0,     0,     0,    69,     0,     0,     0,     0,   457,
       0,   123,     0,   515,   516,   517,   457,     0,   121,     0,
       0,     0,     0,     0,     0,   101,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,   101,     1,   116,     0,
       3,     4,     5,     6,     7,    69,     0,     0,     0,   121,
     121,   121,   121,   121,   121,   121,   121,     0,     0,   123,
     121,   121,   121,     0,     0,     0,   123,   123,     0,     0,
       0,     0,     0,     0,     0,     0,    22,    23,    24,     0,
       0,     0,     0,     0,    25,    26,     0,     0,     0,     0,
      28,    29,    30,    31,   121,    32,    33,    34,   123,     0,
      35,    36,    37,    38,    39,    40,    41,     0,     0,   309,
     123,    43,     0,     0,     0,    44,    45,     0,    46,     0,
      47,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,     0,     0,     0,     0,   163,     0,   121,
     121,     1,     2,     0,     3,     4,     5,     6,     7,     0,
       8,     0,     0,     9,    10,     0,     0,    11,    12,    13,
       0,    14,    15,    16,     0,     0,     0,     0,     0,     0,
       0,   121,    17,     0,     0,    18,     0,    19,    20,    21,
      22,    23,    24,   121,     0,     0,   447,     0,    25,    26,
       0,     0,    27,     0,    28,    29,    30,    31,   465,    32,
      33,    34,     0,     0,    35,    36,    37,    38,    39,    40,
     164,     0,    42,     0,     0,    43,     0,     0,     0,    44,
      45,     0,    46,     0,    47,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     2,   447,     3,
       4,     5,     6,     7,     0,     8,     0,   465,     9,    10,
       0,     0,    11,    12,    13,     0,    14,    15,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
      18,     0,    19,    20,    21,    22,    23,    24,     0,     0,
       0,   121,     0,    25,    26,     0,     0,    27,     0,    28,
      29,    30,    31,     0,    32,    33,    34,     0,     0,    35,
      36,    37,    38,    39,    40,    41,   250,    42,     0,     0,
      43,     0,     0,     0,    44,    45,     0,    46,     0,    47,
      48,    49,     1,     2,     0,     3,     4,     5,     6,     7,
     121,     8,     0,     0,     9,    10,     0,     0,    11,    12,
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
      38,    39,    40,   164,   351,    42,     0,     0,    43,     0,
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
      40,    41,     0,     0,     0,     0,    43,     0,     0,     0,
      44,    45,   345,    46,     0,    47,    48,    49,     1,   116,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,    24,
       0,     0,     0,     0,     0,    25,    26,     0,     0,     0,
       0,    28,    29,    30,    31,     0,    32,    33,    34,     0,
       0,    35,    36,    37,    38,    39,    40,    41,     0,     0,
       0,     0,    43,     0,     0,     0,    44,    45,     0,    46,
     349,    47,    48,    49,     1,   116,     0,     3,     4,     5,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    23,    24,     0,     0,     0,     0,
       0,    25,    26,     0,     0,     0,     0,    28,    29,    30,
      31,     0,    32,    33,    34,     0,     0,    35,    36,    37,
      38,    39,    40,    41,     0,     0,     0,     0,    43,     0,
       0,     0,    44,    45,   374,    46,     0,    47,    48,    49,
       1,   116,     0,     3,     4,     5,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
      23,    24,     0,     0,     0,     0,     0,    25,    26,     0,
       0,     0,     0,    28,    29,    30,    31,     0,    32,    33,
      34,     0,     0,    35,    36,    37,    38,    39,    40,    41,
       0,     0,     0,     0,    43,   495,     0,     0,    44,    45,
       0,    46,     0,    47,    48,    49,     1,   116,     0,     3,
       4,     5,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,    23,    24,     0,     0,
       0,     0,     0,    25,    26,     0,     0,     0,     0,    28,
      29,    30,    31,     0,    32,    33,    34,     0,     0,    35,
      36,    37,    38,    39,    40,    41,     0,     0,     0,     0,
      43,     0,     0,     0,    44,    45,     0,    46,     0,    47,
      48,    49,     1,   116,     0,     3,     4,     5,     6,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,    23,    24,     0,     0,     0,     0,     0,    25,
      26,     0,     0,     0,     0,    28,    29,    30,    31,     0,
      32,    33,    34,     0,     0,    35,    36,    37,    38,    39,
      40,    41,     0,     0,     0,     0,    43,     0,     0,     0,
     423,    45,     0,    46,     0,    47,    48,    49,     1,   116,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    23,   117,
       0,     0,     0,     0,     0,    25,    26,     0,     0,     0,
       0,     0,    29,    30,    31,     0,    32,    33,    34,     0,
       0,    35,    36,    37,    38,    39,    40,    41,     0,     0,
       0,     0,   118,     0,     0,     0,    44,    45,     0,    46,
       0,    47,    48,    49,     1,   116,     0,     3,     4,     5,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    23,   117,     0,     0,     0,     0,
       0,    25,    26,     0,     0,     0,     0,     0,    29,    30,
      31,     0,    32,    33,    34,     0,     0,    35,    36,    37,
      38,    39,    40,    41,     0,     0,     0,     0,   118,     0,
       0,     0,    44,    45,     0,    46,     0,     0,    48,    49,
       1,   116,     0,     3,     4,     5,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
      23,   117,     0,     0,     0,     0,     0,    25,    26,     0,
       0,     0,     0,     0,    29,    30,    31,     0,    32,    33,
      34,     0,     0,    35,    36,    37,    38,    39,    40,    41,
       0,     0,     0,     0,   118,     0,     0,     0,    44,    45,
       0,    46
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-336)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      13,    11,     8,    24,    14,    18,    14,   248,    21,   105,
      21,    24,     0,   176,     0,    18,    77,    58,    45,    58,
      18,    76,    43,    84,    50,    47,    48,    49,    50,    84,
      43,    41,    73,     0,    78,    45,    46,    45,    46,   143,
     144,    56,     0,     4,     5,    75,    85,   151,   152,    75,
      77,    58,    59,    11,     4,     5,    69,    84,    24,    81,
      75,    58,    50,     7,     8,     9,    10,    11,    83,    85,
      73,   234,   168,    76,   237,    73,    83,    43,    58,    58,
     321,    48,    46,    50,     6,     7,     8,     9,    10,    11,
      51,    59,    50,    76,    58,    74,   117,   118,    81,    79,
      79,    51,   115,    69,   117,   118,    46,    75,    58,    59,
      78,   137,    62,   126,    58,    59,   129,    77,    58,   125,
      84,    76,   363,   364,    84,    68,    82,    70,     5,    72,
      77,    86,    16,   146,    90,    91,    58,    59,    22,    86,
      75,    74,    78,   384,    77,    88,    89,    83,    78,    85,
      65,   117,   118,    83,   164,    85,   169,   124,   169,   147,
     126,   147,   175,   129,   190,    77,   124,   502,   178,    75,
     178,    77,    84,    36,   509,   502,   164,    76,   188,    78,
     147,    76,   509,    59,    60,    75,   207,    73,    64,   147,
      80,   432,   180,    59,   207,   162,    62,   164,   208,    29,
     210,   442,   210,   307,   308,    30,   164,   228,   221,   222,
      92,    59,    60,   180,   385,   228,    64,   388,    75,   229,
      77,    78,   180,    76,    84,   251,    86,    58,    59,    78,
     243,   472,   242,    84,   242,    86,    83,   204,   205,   206,
      76,   207,   483,   253,   270,   255,    23,   273,   258,   259,
     260,    75,   262,   263,    14,    15,   266,   267,    75,   285,
      77,     8,   228,   251,    77,    84,    13,    86,   372,   373,
      75,   238,    77,    36,    37,   449,   450,   243,   199,   200,
     286,   248,   270,    76,   251,    77,    86,    77,    45,    76,
     248,    27,    28,   251,    16,    31,    32,    33,    34,    83,
      47,    48,   312,   270,   312,   315,   316,    73,    17,    76,
      75,    73,   270,   193,   194,   195,   196,   197,   198,   325,
      73,    23,    37,    84,   334,   335,    76,    73,   354,   355,
      73,   341,   342,    61,    76,    80,    76,    75,    58,    74,
     353,    74,    73,    77,     8,   358,    75,    84,    53,    76,
     360,    77,    84,    76,   321,    58,    86,    82,    54,    76,
     370,   371,    81,   321,    75,    79,    76,   171,    46,   453,
     337,   507,   509,   478,   328,   449,    67,   387,   125,    11,
     353,   184,   184,    47,    48,   293,    47,   294,   398,   484,
     400,   255,   229,   306,   220,    92,   363,   364,    92,   146,
      92,   411,   412,    -1,    -1,   363,   364,    -1,    -1,    -1,
     423,    -1,    -1,   439,    -1,   162,    -1,   384,   431,    -1,
      -1,    -1,    -1,   433,    -1,   438,   384,    -1,    -1,   435,
      -1,    -1,    -1,    -1,    -1,   445,   446,    -1,    -1,   449,
     453,   451,    -1,    -1,    -1,    -1,   193,   194,   195,   196,
     197,   198,   199,   200,    -1,    -1,    -1,   204,   205,   206,
      -1,   125,   475,    -1,    -1,   432,    -1,    -1,    -1,    -1,
      -1,    -1,   482,    -1,   432,   442,   486,    -1,   484,    -1,
      -1,    -1,    -1,    -1,   442,    -1,    -1,    -1,    -1,   502,
      -1,   238,    -1,   503,   504,   505,   509,    -1,   162,    -1,
      -1,    -1,    -1,    -1,    -1,   472,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   472,    -1,   483,     4,     5,    -1,
       7,     8,     9,    10,    11,   483,    -1,    -1,    -1,   193,
     194,   195,   196,   197,   198,   199,   200,    -1,    -1,   286,
     204,   205,   206,    -1,    -1,    -1,   293,   294,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,   238,    62,    63,    64,   325,    -1,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    76,
     337,    78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   286,    -1,    -1,    -1,    -1,     0,    -1,   293,
     294,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      13,    -1,    -1,    16,    17,    -1,    -1,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   325,    35,    -1,    -1,    38,    -1,    40,    41,    42,
      43,    44,    45,   337,    -1,    -1,   423,    -1,    51,    52,
      -1,    -1,    55,    -1,    57,    58,    59,    60,   435,    62,
      63,    64,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    82,
      83,    -1,    85,    -1,    87,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,   475,     7,
       8,     9,    10,    11,    -1,    13,    -1,   484,    16,    17,
      -1,    -1,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      38,    -1,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,   435,    -1,    51,    52,    -1,    -1,    55,    -1,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,
      88,    89,     4,     5,    -1,     7,     8,     9,    10,    11,
     484,    13,    -1,    -1,    16,    17,    -1,    -1,    20,    21,
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
      72,    73,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      82,    83,    84,    85,    -1,    87,    88,    89,     4,     5,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      -1,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,
      86,    87,    88,    89,     4,     5,    -1,     7,     8,     9,
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
      -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    82,    83,
      -1,    85,    -1,    87,    88,    89,     4,     5,    -1,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,
      88,    89,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    -1,
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
      -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,
      -1,    87,    88,    89,     4,     5,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    -1,    62,    63,    64,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    82,    83,    -1,    85,    -1,    -1,    88,    89,
       4,     5,    -1,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    -1,    62,    63,
      64,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,
      -1,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
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
     230,   201,   202,   192,   222,    84,   192,   192,   192,    86,
     192,    74,    96,    76,   117,    37,   114,    84,    77,    84,
     159,    96,   204,   177,   183,   207,   209,   237,   203,   203,
     236,    76,    84,    86,    84,   190,    75,   192,   192,    73,
      95,    84,    86,   204,   186,   144,   145,   146,   144,   130,
      76,    75,   192,   192,   238,   192,   192,    80,    76,    84,
      76,    86,   170,    96,    96,    46,   246,   192,    76,    95,
      95,   195,   196,   192,   192,   203,   203,    84,    61,    75,
      95,    74,   145,    82,   148,   149,   150,   151,   152,   192,
      74,    73,   188,    58,   104,   221,   192,   192,    77,   118,
      84,    75,   175,   192,   192,   198,   197,   240,    53,    77,
      76,    81,    79,   131,   132,   135,   142,   246,    95,   192,
      76,   204,   223,   224,   225,   240,    84,    86,    96,    95,
     192,   192,   147,   151,   152,    82,   152,   192,    76,    74,
     132,   133,    58,   103,    77,    86,    54,    95,    59,    62,
     141,    76,   192,    95,   224,    79,   192,   226,   227,    75,
     134,   136,   137,   228,    79,    76,    75,    80,   138,   139,
     140,   141,   142,   143,   164,   192,   192,   192,   136,   140
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
#line 209 "../src/parser/parser.y"
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
#line 225 "../src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 229 "../src/parser/parser.y"
    {
			g_op->fast_pop_stack();
		}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 242 "../src/parser/parser.y"
    {
			g_op->do_scope_start();
		}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 246 "../src/parser/parser.y"
    {
			g_op->do_scope_end();
		}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 254 "../src/parser/parser.y"
    {
			g_ctl->parallel_start();
		}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 258 "../src/parser/parser.y"
    {
			g_ctl->parallel_end();
		}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 262 "../src/parser/parser.y"
    {
			g_ctl->parallel_for_start((yyvsp[(3) - (7)].cp));
		}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 266 "../src/parser/parser.y"
    {
			g_ctl->parallel_for_end();
		}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 273 "../src/parser/parser.y"
    {
			g_op->push_integer(0);	// by
			g_op->push_integer(1);	// per
		}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 278 "../src/parser/parser.y"
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
#line 292 "../src/parser/parser.y"
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
#line 306 "../src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (4)].integer));
		}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 313 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_ROOT);
			g_op->find_member("os");
			g_op->find_member("run");
		}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 319 "../src/parser/parser.y"
    {	
			g_op->call(1);
		}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 328 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 336 "../src/parser/parser.y"
    {
			g_ex->pop();
		}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 345 "../src/parser/parser.y"
    {
			g_ex->push();
		}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 349 "../src/parser/parser.y"
    {
			g_ex->goto_end();
		}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 357 "../src/parser/parser.y"
    {
			g_ex->do_finally();
		}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 361 "../src/parser/parser.y"
    {
			g_ex->goto_end();
		}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 381 "../src/parser/parser.y"
    {
			g_ex->catch_start((yyvsp[(2) - (2)].cp));
		}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 385 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 389 "../src/parser/parser.y"
    {
			name_list_t* vp = (name_list_t*)(yyvsp[(4) - (4)].vector_cp);
			g_ex->catch_start((yyvsp[(2) - (4)].cp), vp);
		}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 394 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 398 "../src/parser/parser.y"
    {
			g_ex->catch_start(NULL);
		}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 402 "../src/parser/parser.y"
    {
			g_ex->goto_finally();
		}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 410 "../src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (3)].cp), 0);
		}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 414 "../src/parser/parser.y"
    {
			g_ex->do_throw((yyvsp[(2) - (5)].cp), (yyvsp[(4) - (5)].integer));
		}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 422 "../src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (3)].cp), NULL);
		}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 426 "../src/parser/parser.y"
    {
			code_top->using_object((yyvsp[(2) - (4)].cp), (yyvsp[(3) - (4)].cp));
		}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 434 "../src/parser/parser.y"
    {
			char buff[1024];
			sprintf(buff, "%s.%s", (yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
			(yyval.cp) = parser_strdup(buff);
		}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 440 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 448 "../src/parser/parser.y"
    {
			g_op->dump_stack();
		}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 452 "../src/parser/parser.y"
    {
			g_op->dump_local();
		}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 460 "../src/parser/parser.y"
    {
			g_ctl->do_return((yyvsp[(2) - (3)].integer));
		}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 464 "../src/parser/parser.y"
    {
			g_ctl->do_continue();
		}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 468 "../src/parser/parser.y"
    {
			g_ctl->do_break();
		}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 476 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 480 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 494 "../src/parser/parser.y"
    {
			g_ctl->decode_start();
		}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 498 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
		}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 506 "../src/parser/parser.y"
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
#line 522 "../src/parser/parser.y"
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
#line 543 "../src/parser/parser.y"
    {
			g_parse->set_current_bnf((yyvsp[(1) - (1)].bp));
		}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 547 "../src/parser/parser.y"
    {

		}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 551 "../src/parser/parser.y"
    {
			bnf* b = (yyvsp[(3) - (4)].bp);
			b->type = BNF_WS;
		}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 571 "../src/parser/parser.y"
    {
			g_bnf_right_num = 1;
			g_parse->current_bnf()->add_rule();
		}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 586 "../src/parser/parser.y"
    {
			g_bnf_right_num++;
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(2) - (2)].bp));
		}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 591 "../src/parser/parser.y"
    {
			g_parse->current_bnf()->current_rule()->push_bnf((yyvsp[(1) - (1)].bp));
		}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 606 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp));
		}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 610 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_term_bnf((yyvsp[(1) - (1)].cp), true);
		}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 618 "../src/parser/parser.y"
    {
			string name = "`\a";
			name += (yyvsp[(1) - (1)].cp);
			(yyval.bp) = g_parse->get_nonterm_bnf(name);
		}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 628 "../src/parser/parser.y"
    {
			(yyval.bp) = g_parse->get_action_bnf(g_bnf_right_num);
		}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 641 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_start();
		}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 645 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_shift();
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 649 "../src/parser/parser.y"
    {
			g_ctl->decode_pattern_end();
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 663 "../src/parser/parser.y"
    {
			g_ctl->decode_cut_list((yyvsp[(1) - (3)].cp), (yyvsp[(3) - (3)].cp));
		}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 671 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 675 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 683 "../src/parser/parser.y"
    {
			g_ctl->decode_match_expr();
		}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 687 "../src/parser/parser.y"
    {
			g_ctl->decode_shift((yyvsp[(1) - (1)].cp));
		}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 691 "../src/parser/parser.y"
    {
			g_ctl->decode_match_and_assign((yyvsp[(1) - (3)].cp));
		}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 699 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(2) - (2)].cp);
		}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 715 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer) | (yyvsp[(2) - (2)].integer);
		}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 719 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 727 "../src/parser/parser.y"
    {
			(yyval.integer) = BIT_DEFINE_STATIC;
		}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 731 "../src/parser/parser.y"
    {
			(yyval.integer) = BIT_DEFINE_PURE;
		}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 739 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer);
		}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 743 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 751 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 755 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 763 "../src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
		}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 767 "../src/parser/parser.y"
    {
			code_top->reg_object((yyvsp[(2) - (3)].cp), (yyvsp[(1) - (3)].integer));
			code_top->init_object_start((yyvsp[(2) - (3)].cp));

			g_op->push_reserved(OP_PUSH_MY);
		}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 774 "../src/parser/parser.y"
    {
			g_op->assign_member((yyvsp[(2) - (6)].cp));
			g_op->pop_stack();
			code_top->init_object_done();
		}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 780 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer)) {
				code_top->make_super((yyvsp[(2) - (2)].integer));
			}
		}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 786 "../src/parser/parser.y"
    {
			parserCode::pop_code_stack();
		}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 790 "../src/parser/parser.y"
    {
			
			g_ctl->decode_func_start();
		}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 795 "../src/parser/parser.y"
    {
			g_ctl->decode_end();
			parserCode::pop_code_stack();
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 800 "../src/parser/parser.y"
    {
			const char* cp = get_context();
			print("get_context(): '%s'\n", cp);
			code_top->do_context((yyvsp[(3) - (5)].cp), (yyvsp[(4) - (5)].cp), cp);
			//TODO: fail check
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 811 "../src/parser/parser.y"
    {
			g_ctl->once_start();
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 815 "../src/parser/parser.y"
    {
			g_ctl->once_end();
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 823 "../src/parser/parser.y"
    {
			parserCode::pop_code_stack();
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(1) - (2)].cp));
		}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 834 "../src/parser/parser.y"
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

  case 133:
/* Line 1792 of yacc.c  */
#line 853 "../src/parser/parser.y"
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

  case 134:
/* Line 1792 of yacc.c  */
#line 878 "../src/parser/parser.y"
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

  case 135:
/* Line 1792 of yacc.c  */
#line 910 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 914 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (2)].integer);
		}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 922 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 926 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = 0;
		}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 930 "../src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 936 "../src/parser/parser.y"
    {
			(yyval.vector_cp) = (yyvsp[(2) - (3)].vector_cp);
		}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 940 "../src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(2) - (5)].vector_cp);
			vs->push_back("...");
			(yyval.vector_cp) = vs;
		}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 950 "../src/parser/parser.y"
    {
			name_list_t* vs = (name_list_t*)(yyvsp[(1) - (3)].vector_cp);
			vs->push_back((yyvsp[(3) - (3)].cp));
			(yyval.vector_cp) = vs;
		}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 956 "../src/parser/parser.y"
    {
			name_list_t* vs = parser_new_name_list();
			vs->push_back((yyvsp[(1) - (1)].cp));
			(yyval.vector_cp) = vs;
		}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 966 "../src/parser/parser.y"
    {
			g_ctl->if_end();
		}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 970 "../src/parser/parser.y"
    {
			g_ctl->else_end();
		}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 974 "../src/parser/parser.y"
    {
			g_ctl->else_end();
			for(int i=0; i<(yyvsp[(2) - (3)].integer); i++)
				g_ctl->else_end();
		}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 980 "../src/parser/parser.y"
    {
			g_ctl->if_end();
			for(int i=0; i<(yyvsp[(2) - (2)].integer); i++)
				g_ctl->else_end();
		}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 990 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (2)].integer) + 1;
		}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 994 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1002 "../src/parser/parser.y"
    {
			g_ctl->else_start();
		}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1006 "../src/parser/parser.y"
    {
			g_ctl->if_start();
		}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1015 "../src/parser/parser.y"
    {
			g_ctl->else_start();
		}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1024 "../src/parser/parser.y"
    {
			g_ctl->if_start();
		}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1033 "../src/parser/parser.y"
    {
			g_ctl->do_start();
		}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1037 "../src/parser/parser.y"
    {
			g_ctl->do_end();
		}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1045 "../src/parser/parser.y"
    {
			g_ctl->times_start();
		}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1049 "../src/parser/parser.y"
    {
			g_ctl->times_end();
		}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1057 "../src/parser/parser.y"
    {
			g_ctl->while_start_1();
		}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1061 "../src/parser/parser.y"
    {
			g_ctl->while_start_2();
		}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1065 "../src/parser/parser.y"
    {
			g_ctl->while_end();
		}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1073 "../src/parser/parser.y"
    {
			g_ctl->for_start((yyvsp[(2) - (5)].cp));
		}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1077 "../src/parser/parser.y"
    {
			g_ctl->for_end();
		}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1085 "../src/parser/parser.y"
    { 
			(yyval.integer) = (yyvsp[(1) - (2)].integer); 
		}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1093 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1097 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1105 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1109 "../src/parser/parser.y"
    {
			(yyval.integer) = 2;
		}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1113 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1127 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer) != '=') {
				g_op->push_lvar((yyvsp[(1) - (2)].cp));
			}
		}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1133 "../src/parser/parser.y"
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

  case 176:
/* Line 1792 of yacc.c  */
#line 1145 "../src/parser/parser.y"
    {
			g_op->clear_last_find_position();
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_member((yyvsp[(3) - (4)].cp));
			}
		}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1153 "../src/parser/parser.y"
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

  case 178:
/* Line 1792 of yacc.c  */
#line 1165 "../src/parser/parser.y"
    {
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_reserved((yyvsp[(3) - (4)].integer));
			}
		}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1172 "../src/parser/parser.y"
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

  case 180:
/* Line 1792 of yacc.c  */
#line 1184 "../src/parser/parser.y"
    {
			if ((yyvsp[(5) - (5)].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(false);
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

			g_op->assign_list(false);
		}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1208 "../src/parser/parser.y"
    {
			if ((yyvsp[(5) - (5)].integer) != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(true);
			}
		}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1216 "../src/parser/parser.y"
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

  case 184:
/* Line 1792 of yacc.c  */
#line 1232 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[(2) - (3)].cp));
			}
		}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1241 "../src/parser/parser.y"
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
#line 1253 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[(2) - (3)].integer));
			}
		}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1262 "../src/parser/parser.y"
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

  case 188:
/* Line 1792 of yacc.c  */
#line 1274 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_member((yyvsp[(2) - (3)].cp));
			}
		}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1283 "../src/parser/parser.y"
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

  case 190:
/* Line 1792 of yacc.c  */
#line 1295 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);

			if ((yyvsp[(3) - (3)].integer) != '=') {
				g_op->dup(); 
				g_op->find_reserved((yyvsp[(2) - (3)].integer));
			}
		}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1304 "../src/parser/parser.y"
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

  case 193:
/* Line 1792 of yacc.c  */
#line 1321 "../src/parser/parser.y"
    {
			(yyval.integer) = '='; 
		}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1325 "../src/parser/parser.y"
    { 
			(yyval.integer) = '+'; 
		}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1329 "../src/parser/parser.y"
    { 
			(yyval.integer) = '-'; 
		}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1333 "../src/parser/parser.y"
    { 
			(yyval.integer) = '*'; 
		}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1337 "../src/parser/parser.y"
    { 
			(yyval.integer) = '/'; 
		}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1350 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start(false);
		}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1355 "../src/parser/parser.y"
    {
			g_op->do_or();
			g_ctl->if_end();
		}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1365 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start();
		}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1370 "../src/parser/parser.y"
    {
			g_op->do_and();
			g_ctl->if_end();
		}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1380 "../src/parser/parser.y"
    {
			g_op->do_not();
		}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1389 "../src/parser/parser.y"
    {
			g_op->gt();
		}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1393 "../src/parser/parser.y"
    {
			g_op->ge();
		}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1397 "../src/parser/parser.y"
    {
			g_op->lt();
		}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1401 "../src/parser/parser.y"
    {
			g_op->le();
		}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1405 "../src/parser/parser.y"
    {
			g_op->eq();
		}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1409 "../src/parser/parser.y"
    {
			g_op->neq();
		}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1423 "../src/parser/parser.y"
    {
			g_op->add();
		}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1427 "../src/parser/parser.y"
    {
			g_op->sub();
		}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1431 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(2) - (2)].integer));
			g_op->add();
		}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1436 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(2) - (2)].cp));
			g_op->add();
		}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1441 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(2) - (2)].real));
			g_op->add();
		}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1451 "../src/parser/parser.y"
    {
			g_op->mul();
		}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1455 "../src/parser/parser.y"
    {
			g_op->div();
		}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1459 "../src/parser/parser.y"
    {
			g_op->mod();
		}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1468 "../src/parser/parser.y"
    {
			unary_minus = true;
		}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1472 "../src/parser/parser.y"
    {
			if (unary_minus)
				g_op->minus();

			unary_minus = false;
		}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1485 "../src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (3)].integer));
		}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1489 "../src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (4)].integer));
		}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1493 "../src/parser/parser.y"
    {
			g_op->make_list(-2);
		}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1497 "../src/parser/parser.y"
    {
			g_op->make_list(-3);
		}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1506 "../src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (3)].integer));
		}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1510 "../src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (4)].integer));
		}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1514 "../src/parser/parser.y"
    {
			g_op->make_tuple(-2);
		}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1518 "../src/parser/parser.y"
    {
			g_op->make_tuple(-3);
		}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1526 "../src/parser/parser.y"
    {
			g_op->make_map((yyvsp[(2) - (3)].integer));
		}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1534 "../src/parser/parser.y"
    {
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 1539 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule_start();
		}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 1543 "../src/parser/parser.y"
    {
			g_ctl->sbf_end();
			g_lvar_nil_check++;
		}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1563 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule();
		}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 1567 "../src/parser/parser.y"
    {
			g_ctl->sbf_in();
		}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1575 "../src/parser/parser.y"
    {
			g_ctl->sbf_list_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 1579 "../src/parser/parser.y"
    {
			g_ctl->sbf_range_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 1588 "../src/parser/parser.y"
    {
			g_op->push_integer(1);
		}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1597 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 1601 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 1610 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 1614 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1631 "../src/parser/parser.y"
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

  case 263:
/* Line 1792 of yacc.c  */
#line 1642 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1646 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 1650 "../src/parser/parser.y"
    {
			g_op->push_bignum('+', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1654 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1658 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 1662 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 1666 "../src/parser/parser.y"
    {
			g_op->make_regex();
		}
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 1670 "../src/parser/parser.y"
    {
			// already in stack
		}
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 1674 "../src/parser/parser.y"
    {
			g_op->push_reserved((yyvsp[(1) - (1)].integer));
		}
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 1678 "../src/parser/parser.y"
    {
			g_op->push_boolean(true);
		}
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 1682 "../src/parser/parser.y"
    {
			g_op->push_boolean(false);
		}
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 1686 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1695 "../src/parser/parser.y"
    {
			g_op->set_last_find_position();
			g_op->find_member((yyvsp[(3) - (3)].cp));
		}
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1700 "../src/parser/parser.y"
    {
			g_op->find_reserved((yyvsp[(3) - (3)].integer));
		}
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 1704 "../src/parser/parser.y"
    {
			g_op->clear_last_find_position();
		}
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1708 "../src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (3)].integer));
		}
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 1712 "../src/parser/parser.y"
    {
			g_op->listat(false);
		}
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 1716 "../src/parser/parser.y"
    {
			g_op->listat(true);
		}
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 1720 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 1725 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 284:
/* Line 1792 of yacc.c  */
#line 1730 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 1735 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 286:
/* Line 1792 of yacc.c  */
#line 1740 "../src/parser/parser.y"
    {
			if (g_op->push_mvar_using_space((yyvsp[(1) - (1)].cp)) == false) {
				yyerror("invalid object name in name'string' format");
			}
		}
    break;

  case 287:
/* Line 1792 of yacc.c  */
#line 1746 "../src/parser/parser.y"
    {
			g_op->clone(1);
		}
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 1750 "../src/parser/parser.y"
    {
			g_op->clone((yyvsp[(4) - (4)].integer));

			// this is not normal function call (virtual function call)
			// so it should mark that don't fast popping
			g_op->disable_fast_pop();
		}
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1763 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 1767 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
		}
    break;

  case 292:
/* Line 1792 of yacc.c  */
#line 1771 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 293:
/* Line 1792 of yacc.c  */
#line 1775 "../src/parser/parser.y"
    {
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 1780 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 1791 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 1795 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (3)].integer);
		}
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 1803 "../src/parser/parser.y"
    {
			g_op->fix_last_find_position();
		}
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 1811 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_OWNER;
		}
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 1815 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_CALLER;
		}
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 1819 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_ROOT;
		}
    break;

  case 302:
/* Line 1792 of yacc.c  */
#line 1823 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MODULE;
		}
    break;

  case 303:
/* Line 1792 of yacc.c  */
#line 1827 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MY;
		}
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 1835 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 1844 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 308:
/* Line 1792 of yacc.c  */
#line 1853 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 309:
/* Line 1792 of yacc.c  */
#line 1861 "../src/parser/parser.y"
    {
			g_op->add();

			g_op->push_string((yyvsp[(4) - (4)].cp));

			g_op->add();
		}
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 1873 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 1882 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 1887 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
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
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 1911 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 318:
/* Line 1792 of yacc.c  */
#line 1919 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 319:
/* Line 1792 of yacc.c  */
#line 1927 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 320:
/* Line 1792 of yacc.c  */
#line 1935 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;

  case 321:
/* Line 1792 of yacc.c  */
#line 1943 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;


/* Line 1792 of yacc.c  */
#line 4489 "../src/parser/parser.cpp"
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
#line 1949 "../src/parser/parser.y"



