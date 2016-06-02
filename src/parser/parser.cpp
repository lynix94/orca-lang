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
#define YYFINAL  162
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2244

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  159
/* YYNRULES -- Number of rules.  */
#define YYNRULES  319
/* YYNRULES -- Number of states.  */
#define YYNSTATES  517

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
     487,   489,   490,   495,   496,   503,   504,   511,   512,   520,
     521,   529,   530,   536,   537,   543,   544,   550,   551,   557,
     559,   561,   563,   565,   567,   569,   571,   572,   577,   579,
     580,   585,   587,   590,   592,   596,   600,   604,   608,   612,
     616,   618,   620,   624,   628,   631,   634,   637,   639,   643,
     647,   651,   653,   654,   658,   661,   663,   667,   672,   678,
     686,   688,   694,   699,   705,   713,   717,   722,   723,   724,
     733,   735,   739,   741,   743,   745,   749,   753,   757,   759,
     763,   766,   767,   771,   775,   777,   781,   783,   785,   787,
     789,   791,   793,   795,   797,   799,   801,   803,   805,   807,
     809,   811,   813,   815,   819,   823,   827,   828,   832,   837,
     842,   845,   848,   851,   854,   855,   859,   864,   866,   870,
     871,   875,   878,   880,   882,   885,   889,   891,   893,   895,
     897,   899,   901,   903,   906,   908,   911,   913,   918,   920,
     922,   924,   926,   928,   930,   932,   934,   936,   938,   940
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      94,     0,    -1,    94,    98,    -1,    94,    96,    -1,    98,
      -1,    98,    -1,    96,    -1,    73,    94,    74,    -1,    73,
      74,    -1,    94,    74,    -1,    74,    -1,   189,    -1,   124,
      -1,   126,    -1,   153,    -1,   158,    -1,   109,    -1,   121,
      -1,   105,    -1,   106,    -1,    99,    -1,   101,    -1,   129,
      -1,   123,    -1,    75,    -1,    -1,   191,   100,    96,    -1,
      -1,    55,    16,   102,    95,    -1,    -1,    55,    22,   239,
      23,   237,   104,    76,   103,    95,    -1,    -1,    58,   191,
      -1,    58,   191,    58,   191,    -1,   231,    76,   190,    75,
      -1,    -1,   107,   108,    -1,   108,   242,    -1,    65,    -1,
     110,   112,    -1,   120,    -1,    -1,    35,   111,    96,    -1,
      -1,   115,   113,   114,    -1,   115,    -1,    37,    96,    -1,
     115,   116,    -1,   116,    -1,    -1,    36,   122,   117,    96,
      -1,    -1,    36,   122,    76,   170,   118,    96,    -1,    -1,
      36,   119,    96,    -1,    38,   122,    75,    -1,    38,   122,
      77,   190,    75,    -1,    42,   122,    75,    -1,    42,   122,
      59,    75,    -1,   122,    78,   157,    -1,   157,    -1,    40,
      -1,    41,    -1,    24,   125,    75,    -1,    25,    75,    -1,
      26,    75,    -1,    -1,   190,    -1,   171,    -1,   127,    -1,
      -1,    20,   191,   128,    73,   144,    74,    -1,    -1,    21,
       5,   157,   169,   130,    73,   131,    74,    -1,   131,   132,
      -1,   132,    -1,    -1,   135,   133,    76,   134,    75,    -1,
      79,    76,   141,    75,    -1,   134,    80,   136,    -1,   136,
      -1,   142,    -1,    -1,   137,   138,    -1,   139,    -1,   139,
     140,    -1,   140,    -1,   141,    -1,   142,    -1,   143,    -1,
      59,    -1,    62,    -1,   245,    -1,   164,    -1,   144,   145,
      -1,   145,    -1,    -1,    -1,   146,   148,    53,   147,    95,
      -1,   150,    -1,   149,    -1,   152,    76,   152,    -1,   150,
      77,   151,    -1,   151,    -1,   191,    -1,   152,    -1,   152,
      81,   191,    -1,    82,   239,    -1,   187,    -1,   180,    -1,
     184,    -1,   182,    -1,   154,   155,    -1,   155,    -1,     4,
      -1,    51,    -1,   154,     5,    -1,     5,    -1,   245,    -1,
      59,    -1,   156,   157,    75,    -1,    -1,   156,   157,    56,
     159,   191,    75,    -1,    -1,   166,   168,   160,    96,    -1,
      -1,    20,   166,   161,    73,   144,    74,    -1,     5,    78,
     245,   245,    73,    -1,    -1,    57,   163,    97,    -1,   167,
      96,    -1,   165,    -1,     5,    78,   245,    73,    -1,   156,
     157,   169,    -1,   156,   169,    -1,    -1,    76,   190,    -1,
      -1,    83,    84,    -1,    83,    46,    84,    -1,    83,   170,
      84,    -1,    83,   170,    77,    46,    84,    -1,   170,    77,
     245,    -1,   245,    -1,   178,    -1,   178,   176,    -1,   178,
     172,   176,    -1,   178,   172,    -1,   172,   173,    -1,   173,
      -1,    -1,    -1,    14,   174,   203,    76,   175,    95,    -1,
      -1,    15,    76,   177,    95,    -1,    -1,    13,   203,    76,
     179,    95,    -1,    -1,    16,   181,    95,    17,   203,    75,
      -1,    -1,   191,    18,    16,   183,    95,    -1,    -1,    -1,
      17,   185,   203,    76,   186,    95,    -1,    -1,    22,   239,
      23,   237,    76,   188,    95,    -1,   190,    75,    -1,   190,
      77,   191,    -1,   191,    -1,   192,    -1,   162,    -1,    -1,
     239,   202,   193,   191,    -1,    -1,   231,    78,   157,   202,
     194,   191,    -1,    -1,   231,    78,   238,   202,   195,   191,
      -1,    -1,   231,    85,   234,    86,   202,   196,   191,    -1,
      -1,   231,    85,   234,    84,   202,   197,   191,    -1,    -1,
      45,   157,   202,   198,   191,    -1,    -1,    45,   238,   202,
     199,   191,    -1,    -1,    78,   157,   202,   200,   191,    -1,
      -1,    78,   238,   202,   201,   191,    -1,   203,    -1,    81,
      -1,    47,    -1,    48,    -1,    49,    -1,    50,    -1,   204,
      -1,    -1,   204,    30,   205,   206,    -1,   206,    -1,    -1,
     206,    29,   207,   208,    -1,   208,    -1,    87,   209,    -1,
     209,    -1,   210,    31,   210,    -1,   210,    32,   210,    -1,
     210,    33,   210,    -1,   210,    34,   210,    -1,   210,    27,
     210,    -1,   210,    28,   210,    -1,   210,    -1,   211,    -1,
     211,    88,   212,    -1,   211,    89,   212,    -1,   211,   246,
      -1,   211,   248,    -1,   211,   251,    -1,   212,    -1,   212,
      90,   237,    -1,   212,    91,   237,    -1,   212,    82,   237,
      -1,   213,    -1,    -1,    89,   214,   237,    -1,    88,   237,
      -1,   237,    -1,    85,   125,    86,    -1,    85,   190,    77,
      86,    -1,    85,   191,    45,   191,    86,    -1,    85,   191,
      45,   191,    76,   191,    86,    -1,   218,    -1,    83,   190,
      77,   191,    84,    -1,    83,   190,    77,    84,    -1,    83,
     191,    45,   191,    84,    -1,    83,   191,    45,   191,    76,
     191,    84,    -1,    73,   228,    74,    -1,    73,   228,    77,
      74,    -1,    -1,    -1,    82,    85,   219,   221,    80,   220,
     222,    86,    -1,   191,    -1,   222,    77,   223,    -1,   223,
      -1,   203,    -1,   224,    -1,   239,    54,   191,    -1,   239,
      54,   225,    -1,   226,    76,   191,    -1,   226,    -1,   191,
      79,   191,    -1,   191,    79,    -1,    -1,    79,   227,   191,
      -1,   228,    77,   229,    -1,   229,    -1,   191,    76,   191,
      -1,   215,    -1,   216,    -1,   217,    -1,   164,    -1,   239,
      -1,   247,    -1,   246,    -1,   249,    -1,   248,    -1,   250,
      -1,   251,    -1,   243,    -1,   244,    -1,   238,    -1,    43,
      -1,    44,    -1,    52,    -1,    83,   191,    84,    -1,   231,
      78,   157,    -1,   231,    78,   238,    -1,    -1,   231,   232,
     236,    -1,   231,    85,   234,    86,    -1,   231,    85,   234,
      84,    -1,    45,   157,    -1,    45,   238,    -1,    78,   157,
      -1,    78,   238,    -1,    -1,   245,   233,   244,    -1,   231,
      78,     6,   236,    -1,   230,    -1,   191,    76,   191,    -1,
      -1,    76,   235,   191,    -1,   191,    76,    -1,    76,    -1,
     191,    -1,    83,    84,    -1,    83,   190,    84,    -1,   231,
      -1,     8,    -1,     9,    -1,    10,    -1,    11,    -1,     7,
      -1,   245,    -1,   240,   242,    -1,    60,    -1,   241,   242,
      -1,    63,    -1,    92,    73,   191,    61,    -1,    62,    -1,
     241,    -1,    59,    -1,   240,    -1,    64,    -1,    58,    -1,
      68,    -1,    67,    -1,    70,    -1,    69,    -1,    71,    -1,
      72,    -1
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
    1044,  1057,  1061,  1056,  1073,  1072,  1084,  1092,  1096,  1120,
    1121,  1127,  1126,  1145,  1144,  1165,  1164,  1184,  1183,  1208,
    1207,  1232,  1231,  1253,  1252,  1274,  1273,  1295,  1294,  1315,
    1320,  1324,  1328,  1332,  1336,  1344,  1350,  1349,  1359,  1365,
    1364,  1374,  1379,  1383,  1388,  1392,  1396,  1400,  1404,  1408,
    1412,  1417,  1422,  1426,  1430,  1435,  1440,  1445,  1450,  1454,
    1458,  1462,  1468,  1467,  1478,  1479,  1484,  1488,  1492,  1496,
    1500,  1505,  1509,  1513,  1517,  1525,  1529,  1538,  1543,  1537,
    1555,  1560,  1561,  1566,  1570,  1578,  1582,  1590,  1591,  1599,
    1600,  1605,  1604,  1613,  1617,  1625,  1630,  1631,  1632,  1633,
    1634,  1645,  1649,  1653,  1657,  1661,  1665,  1669,  1673,  1677,
    1681,  1685,  1689,  1693,  1698,  1703,  1708,  1707,  1715,  1719,
    1723,  1728,  1733,  1738,  1744,  1743,  1753,  1761,  1766,  1771,
    1770,  1778,  1783,  1789,  1794,  1798,  1806,  1814,  1818,  1822,
    1826,  1830,  1838,  1846,  1847,  1855,  1856,  1864,  1876,  1880,
    1885,  1889,  1890,  1898,  1906,  1914,  1922,  1930,  1938,  1946
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
  "expression_stmt", "expression_list", "expression", "assign_expr",
  "$@29", "$@30", "$@31", "$@32", "$@33", "$@34", "$@35", "$@36", "$@37",
  "assign_type", "bool_expr", "or_expr", "$@38", "and_expr", "$@39",
  "not_expr", "logical_expr", "numeric_expr", "add_expr", "mul_expr",
  "unary_expr", "$@40", "list", "tuple", "map", "sbf", "$@41", "$@42",
  "sbf_result", "sbf_rule_list", "sbf_rule", "in_expr", "range_expr",
  "range_expr_sub", "$@43", "pair_list", "pair_expression",
  "primary_object", "postfix_object", "$@44", "$@45", "slice_expression",
  "$@46", "calling_body", "object", "reserved_object", "lvar",
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
     191,   193,   192,   194,   192,   195,   192,   196,   192,   197,
     192,   198,   192,   199,   192,   200,   192,   201,   192,   192,
     202,   202,   202,   202,   202,   203,   205,   204,   204,   207,
     206,   206,   208,   208,   209,   209,   209,   209,   209,   209,
     209,   210,   211,   211,   211,   211,   211,   211,   212,   212,
     212,   212,   214,   213,   213,   213,   215,   215,   215,   215,
     215,   216,   216,   216,   216,   217,   217,   219,   220,   218,
     221,   222,   222,   223,   223,   224,   224,   225,   225,   226,
     226,   227,   226,   228,   228,   229,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   231,   231,   232,   231,   231,   231,
     231,   231,   231,   231,   233,   231,   231,   231,   234,   235,
     234,   234,   234,   234,   236,   236,   237,   238,   238,   238,
     238,   238,   239,   240,   240,   241,   241,   242,   243,   243,
     244,   244,   244,   245,   246,   247,   248,   249,   250,   251
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
       5,     0,     0,     6,     0,     7,     2,     3,     1,     1,
       1,     0,     4,     0,     6,     0,     6,     0,     7,     0,
       7,     0,     5,     0,     5,     0,     5,     0,     5,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       4,     1,     2,     1,     3,     3,     3,     3,     3,     3,
       1,     1,     3,     3,     2,     2,     2,     1,     3,     3,
       3,     1,     0,     3,     2,     1,     3,     4,     5,     7,
       1,     5,     4,     5,     7,     3,     4,     0,     0,     8,
       1,     3,     1,     1,     1,     3,     3,     3,     1,     3,
       2,     0,     3,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     0,     3,     4,     4,
       2,     2,     2,     2,     0,     3,     4,     1,     3,     0,
       3,     2,     1,     1,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      35,   114,   117,   301,   297,   298,   299,   300,     0,   157,
     161,     0,     0,     0,    66,     0,     0,    41,     0,    61,
      62,     0,   270,   271,     0,   115,   272,     0,   128,   313,
     310,   304,   308,   306,   312,   315,   314,   317,   316,   318,
     319,     0,    24,     0,     0,     0,    66,     0,     0,   222,
      35,     4,    20,    21,    18,    19,     0,    16,     0,    40,
      17,    23,    12,    13,    69,    22,    14,     0,   113,   137,
      15,   170,   259,   131,   135,     0,    68,   144,   109,   111,
     110,   108,    11,     0,   168,   169,   189,   195,   198,   201,
     203,   210,   211,   217,   221,   256,   257,   258,   230,   287,
     296,   225,   269,   260,   311,   309,   267,   268,   302,   262,
     261,   264,   263,   265,   266,     0,   117,     0,     0,   137,
       0,   296,   260,    35,     0,   137,   125,    70,   296,     0,
       0,   302,     0,    67,   168,    64,    65,     0,   119,     0,
      60,   118,     0,   280,   281,    27,     0,    35,     0,     0,
     254,   282,   283,   237,     0,   168,     0,    67,   168,   202,
     224,     0,     1,    35,     3,     2,    38,    36,    53,    39,
      45,    48,   116,   112,     0,   137,   134,     0,   123,    35,
     130,   150,     0,   147,   149,   145,   166,     0,     0,     0,
     196,   199,     0,     0,     0,     0,     0,     0,     0,     0,
     214,   215,   216,     0,     0,     0,     0,     0,     0,     0,
     191,   192,   193,   194,   190,   171,     0,   303,   305,     0,
       0,     0,   280,   281,   282,   283,   155,     0,     0,     0,
       6,     5,     0,   137,     0,     0,   137,     0,    63,    42,
      55,     0,     0,     0,    57,   181,   183,    35,     0,    10,
      35,   129,     0,   235,     0,   185,   187,     0,     0,     0,
     273,   226,     0,     0,   223,     8,    35,   168,    37,     0,
      49,     0,    47,     0,   138,     0,   143,   121,   120,   133,
     136,     0,     0,   153,   148,   146,   167,   159,    26,     0,
       0,   208,   209,   204,   205,   206,   207,   212,   213,   220,
     218,   219,     0,     0,   274,   275,   289,   293,     0,     0,
     277,     0,     0,   285,   132,     0,     0,    35,   274,   275,
       0,     0,   162,    96,    96,    72,     0,     0,    59,    58,
       0,     0,    28,     0,     9,   255,   236,   253,     0,     0,
     240,     0,   232,   167,     0,   227,     0,     7,    54,     0,
       0,     0,    44,   139,     0,   140,     0,   124,     0,    35,
      35,   197,   200,    34,   286,   173,   175,     0,   291,   279,
     278,   294,     0,   172,     0,   127,   156,   279,   278,     0,
      35,    96,    95,     0,    96,     0,   164,    56,   182,   184,
      31,   186,   188,   238,   231,     0,   233,     0,   228,    51,
      50,    46,     0,   142,     0,   151,   154,   160,     0,     0,
     290,   288,   179,   177,   295,   307,   158,   163,   126,    94,
       0,     0,   100,    99,   103,   105,   104,    71,     0,    35,
       0,     0,     0,     0,     0,     0,     0,   141,   122,    35,
     174,   176,     0,     0,   107,    97,     0,     0,     0,     0,
       0,    75,    76,    81,    92,   165,    32,    29,   243,     0,
     242,   244,   260,   234,   229,    52,   152,   180,   178,    35,
     102,   105,     0,   101,   106,     0,    73,    74,     0,     0,
      35,     0,   239,     0,    98,    90,    91,     0,    82,    33,
      30,   241,   251,   245,   246,   248,    78,     0,    80,     0,
       0,   250,     0,    77,    82,    83,    84,    86,    87,    88,
      89,    93,   252,   249,   247,    79,    85
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   266,   229,   230,   251,   231,    52,   189,    53,   247,
     480,   431,    54,    55,    56,   167,    57,    58,   137,   169,
     271,   352,   170,   171,   350,   436,   269,    59,    60,   139,
      61,    62,   132,    63,    64,   235,    65,   385,   450,   451,
     478,   497,   452,   498,   499,   505,   506,   507,   508,   453,
     510,   381,   382,   383,   469,   421,   422,   423,   424,   425,
      66,    67,    68,   119,   140,    70,   356,   281,   234,    71,
     147,    72,    73,    74,    75,   178,   176,   275,    76,   183,
     184,   282,   439,   185,   359,    77,   317,    78,   123,    79,
     360,    80,   124,   380,    81,   429,    82,    83,    84,    85,
     311,   408,   409,   443,   442,   330,   331,   338,   339,   215,
      86,    87,   289,    88,   290,    89,    90,    91,    92,    93,
      94,   161,    95,    96,    97,    98,   257,   432,   341,   459,
     460,   461,   494,   495,   500,   149,   150,    99,   128,   209,
     219,   308,   367,   310,   101,   102,   103,   104,   105,   217,
     106,   107,   108,   109,   110,   111,   112,   113,   114
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -379
static const yytype_int16 yypact[] =
{
    1127,  -379,   -23,  -379,  -379,  -379,  -379,  -379,  1987,  -379,
    -379,  1815,    44,    45,  1815,    38,    66,  -379,   -15,  -379,
    -379,   -15,  -379,  -379,    59,  -379,  -379,   150,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
    -379,  1815,  -379,    59,    64,  1815,  1815,  2073,  2159,  -379,
     635,  -379,  -379,  -379,  -379,  -379,   100,  -379,   145,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,    14,  -379,   -32,
    -379,  -379,  -379,  -379,   113,   120,  -379,   160,  -379,  -379,
    -379,  -379,  -379,   157,    -1,  -379,  -379,   180,   168,  -379,
    -379,   151,    74,    61,  -379,  -379,  -379,  -379,  -379,  -379,
      54,  -379,  -379,    42,   134,   134,  -379,  -379,   128,  -379,
    -379,  -379,  -379,  -379,  -379,    45,   172,    59,    59,   155,
     170,    46,  -379,  1213,  1987,   -32,  -379,  -379,    62,   -15,
     220,  -379,   188,   193,  -379,  -379,  -379,   120,  -379,   144,
    -379,  -379,    22,    42,    42,  -379,    45,   783,   196,   146,
    -379,    42,    42,  -379,   199,   -31,   191,   202,   243,  -379,
    -379,  2159,  -379,   869,  -379,  -379,  -379,   134,   -15,  -379,
     167,  -379,  -379,  -379,   -30,   -35,  -379,  1815,  -379,   869,
    -379,  -379,   213,   160,  -379,  -379,  -379,  1815,   274,   120,
    -379,  -379,  2073,  2073,  2073,  2073,  2073,  2073,  2073,  2073,
    -379,  -379,  -379,  2159,  2159,  2159,  1815,    52,  1299,   208,
    -379,  -379,  -379,  -379,  -379,  -379,   219,  -379,  -379,   153,
      25,    45,  -379,  -379,  -379,  -379,  -379,    52,  1299,   277,
    -379,  -379,   221,   155,   222,   223,   155,  2159,  -379,  -379,
    -379,  1815,   -15,   225,  -379,  -379,  -379,  1213,   275,  -379,
     955,  -379,  1815,  -379,  1385,  -379,  -379,  1815,  1471,  1815,
    -379,  -379,  1557,  1815,  -379,  -379,  1041,     4,  -379,   120,
       8,   267,  -379,   224,  -379,    24,  -379,  -379,  -379,  -379,
     193,   120,  1987,  -379,  -379,  -379,  -379,  -379,  -379,  1987,
    1987,  -379,  -379,  -379,  -379,  -379,  -379,    61,    61,  -379,
    -379,  -379,   164,   208,    42,    42,   175,   230,   176,  1643,
    -379,  1815,  1815,  -379,  -379,   234,   239,  1213,  -379,  -379,
     182,  1987,  -379,  -379,  -379,  -379,   237,   194,  -379,  -379,
    1815,  1815,  -379,  2159,  -379,  -379,  -379,  -379,  1815,  1815,
    -379,   235,  -379,   232,    11,  -379,    33,  -379,  -379,    45,
     120,   120,  -379,  -379,   -26,  -379,  1815,  -379,   238,  1213,
    1213,   168,  -379,  -379,  -379,  -379,  -379,  1815,  1815,    42,
      42,  -379,    30,  -379,   256,  -379,  -379,  -379,  -379,   247,
    1213,   244,  -379,  1901,   249,   251,  -379,  -379,  -379,  -379,
     268,  -379,  -379,  -379,  -379,  1815,  -379,  1815,  -379,   250,
    -379,  -379,   248,  -379,   258,  -379,  -379,  -379,  1815,  1815,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
     -21,   278,  -379,   257,  -379,   114,  -379,  -379,    27,  1213,
    1815,   261,  1987,   255,   254,    45,   120,  -379,  -379,  1213,
    -379,  -379,  1815,  1815,  -379,  -379,  1901,   260,  1815,   269,
     -29,  -379,  -379,  -379,  -379,  -379,   285,  -379,  -379,    48,
    -379,  -379,   290,  -379,  -379,  -379,  -379,  -379,  -379,  1213,
    -379,   266,    45,  -379,  -379,   165,  -379,  -379,   272,  1815,
    1213,  1987,  -379,  1729,  -379,  -379,  -379,   280,  -379,  -379,
    -379,  -379,  -379,   270,  -379,   276,  -379,   126,  -379,    20,
    1815,  1815,  1815,  -379,  -379,  -379,    20,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -379,     3,  -224,   -41,  -379,     7,  -379,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
    -379,  -379,  -379,   186,  -379,  -379,  -379,  -379,  -379,    -8,
    -379,  -379,   313,  -379,  -379,  -379,  -379,  -379,  -379,   -90,
    -379,  -379,  -379,  -143,  -379,  -379,  -379,  -144,  -112,  -378,
    -379,    43,  -151,  -379,  -379,  -379,  -379,  -379,   -80,  -192,
    -379,  -379,   301,    88,    51,  -379,  -379,  -379,  -379,  -379,
    -379,  -335,  -379,   358,  -379,  -379,  -160,    21,  -379,  -379,
     189,  -379,  -379,   192,  -379,  -379,  -379,  -379,  -379,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,    -4,   -10,  -379,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -105,
      -2,  -379,  -379,    82,  -379,    84,   329,    89,  -379,    76,
    -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,  -379,
    -104,  -379,  -379,  -379,  -379,  -379,   124,  -379,   303,  -379,
    -379,   152,  -379,    78,   -46,     9,   317,  -379,  -379,   -93,
    -379,   163,   -13,   287,  -379,   291,  -379,  -379,   292
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -293
static const yytype_int16 yytable[] =
{
     131,   127,   160,    50,   134,   141,   120,    51,   141,   164,
     133,   141,   218,   142,   259,   279,   273,   188,     1,   172,
     402,   277,   188,   332,     1,   116,    29,   138,    29,    29,
     141,   148,    29,   144,   180,   155,   158,    29,   245,   246,
     278,   154,   157,    29,   138,   476,   255,   256,   174,   129,
     449,   174,   152,   260,   274,   115,   141,   165,   303,     3,
       4,     5,     6,     7,   153,    25,     3,     4,     5,     6,
       7,    25,   -25,   279,   268,   143,   325,   -25,    29,   485,
     252,   243,   486,    29,   349,    29,   242,   395,    69,   210,
     211,   212,   213,   376,   151,   396,   239,   244,   314,   125,
     242,   354,   220,    29,   141,   141,   449,   187,   355,   397,
      29,   138,   141,   135,   414,   264,   141,    29,   138,   398,
     175,   509,   232,   214,   227,   481,   223,   225,   509,  -276,
     206,   228,   207,   131,   482,   406,   407,  -276,    69,   208,
     207,   136,    36,   203,    38,  -276,    40,   208,   288,   153,
     250,   204,   205,   267,    51,   141,   417,   299,   300,   301,
     270,   276,   198,   199,   511,   166,   145,   134,   222,   224,
      51,   511,   146,   280,   181,   182,   233,   286,   192,   193,
     236,   168,   194,   195,   196,   197,    51,  -284,  -284,   177,
     447,   326,  -284,   179,   141,   448,   134,   191,   307,   365,
     366,   503,   302,   168,   -43,   455,   504,   315,   316,   164,
     190,    69,    30,    31,   141,   466,   305,    34,   307,   240,
     253,   241,   242,   254,   485,   164,   216,   486,   348,   141,
     419,   134,   186,   419,   187,    69,   319,   327,   174,   363,
     357,   187,   335,   237,   148,   484,   226,   340,   343,   344,
     221,    69,   286,   346,   471,   473,   490,   165,   304,  -292,
     369,  -292,   370,   238,   412,   413,   377,    69,   378,   387,
     187,   187,   252,   165,   297,   298,   258,   261,   318,   262,
     358,   291,   292,   293,   294,   295,   296,   390,   263,   283,
     287,   309,   312,   328,   321,   323,   324,   322,   333,   134,
     329,   373,   374,   100,   351,   372,   368,   375,   353,   400,
     401,   121,   314,   386,   405,   393,   394,   415,   418,   379,
     388,   389,   416,   427,   428,   122,   430,   435,   391,   392,
     130,   445,   437,   438,   446,    69,   276,   457,    69,   463,
     464,   403,   472,   479,   483,   475,   404,   448,   488,   501,
     121,   121,   502,   100,    69,   496,   272,   410,   411,   156,
     477,   515,   516,   487,   122,   122,   470,   384,   173,   126,
     399,   361,   284,   426,   362,   285,   159,   491,   337,   200,
     320,   364,   313,   201,   202,   433,     0,   434,     0,     0,
       0,     0,     0,     0,     0,   465,     0,     0,   440,   441,
       0,     0,     0,     0,     0,    69,     0,   131,     0,     0,
       0,     0,     0,     0,     0,   454,     0,     0,     0,     0,
     456,     0,   403,     0,     0,     0,   100,   121,     0,     0,
     458,     0,   467,   468,     0,     0,   426,   454,   474,     0,
       0,   122,     0,     0,     0,     0,     0,    69,    69,     0,
     100,     0,     0,     0,     0,     0,     0,     0,     0,   131,
       0,     0,     0,   248,   121,     0,   100,     0,    69,   489,
       0,     0,     0,   493,     0,     0,     0,     0,   122,   458,
       0,     0,   100,     0,     0,     0,   454,     0,     0,     0,
     512,   513,   514,   454,     0,   121,   121,   121,   121,   121,
     121,   121,   121,     0,     0,     0,   121,   121,   121,   122,
     122,   122,   122,   122,   122,   122,   122,    69,     0,     0,
     122,   122,   122,     0,     0,     0,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     100,     0,     0,   100,   122,     0,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    69,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   121,     0,     0,     0,     0,
       0,     0,   121,   121,     0,     0,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,   122,   122,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     100,     0,     0,     0,   121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   162,   121,     0,   122,     1,
       2,     0,     3,     4,     5,     6,     7,     0,     8,     0,
     122,     9,    10,     0,     0,    11,    12,    13,     0,    14,
      15,    16,   100,   100,     0,     0,     0,     0,     0,     0,
      17,     0,     0,    18,     0,    19,    20,    21,    22,    23,
      24,     0,     0,   100,     0,     0,    25,    26,     0,     0,
      27,     0,    28,    29,    30,    31,     0,    32,    33,    34,
       0,     0,    35,    36,    37,    38,    39,    40,   163,     0,
      42,     0,     0,    43,     0,     0,     0,    44,    45,     0,
      46,     0,    47,    48,    49,     0,     0,     0,     0,     0,
       0,     0,   100,     0,     0,   121,     0,   444,     0,     0,
       0,     0,   100,     0,     0,     0,     0,     0,     0,   462,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   100,   121,     0,     0,     1,     2,   444,
       3,     4,     5,     6,     7,     0,     8,     0,   462,     9,
      10,     0,     0,    11,    12,    13,     0,    14,    15,    16,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,    18,     0,    19,    20,    21,    22,    23,    24,     0,
       0,     0,     0,     0,    25,    26,     0,     0,    27,     0,
      28,    29,    30,    31,     0,    32,    33,    34,     0,     0,
      35,    36,    37,    38,    39,    40,    41,   249,    42,     0,
       0,    43,     0,     0,     0,    44,    45,     0,    46,     0,
      47,    48,    49,     1,     2,     0,     3,     4,     5,     6,
       7,     0,     8,     0,     0,     9,    10,     0,     0,    11,
      12,    13,     0,    14,    15,    16,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,    18,     0,    19,
      20,    21,    22,    23,    24,     0,     0,     0,     0,     0,
      25,    26,     0,     0,    27,     0,    28,    29,    30,    31,
       0,    32,    33,    34,     0,     0,    35,    36,    37,    38,
      39,    40,    41,   265,    42,     0,     0,    43,     0,     0,
       0,    44,    45,     0,    46,     0,    47,    48,    49,     1,
       2,     0,     3,     4,     5,     6,     7,     0,     8,     0,
       0,     9,    10,     0,     0,    11,    12,    13,     0,    14,
      15,    16,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,     0,    18,     0,    19,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,    25,    26,     0,     0,
      27,     0,    28,    29,    30,    31,     0,    32,    33,    34,
       0,     0,    35,    36,    37,    38,    39,    40,   163,   334,
      42,     0,     0,    43,     0,     0,     0,    44,    45,     0,
      46,     0,    47,    48,    49,     1,     2,     0,     3,     4,
       5,     6,     7,     0,     8,     0,     0,     9,    10,     0,
       0,    11,    12,    13,     0,    14,    15,    16,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,     0,    18,
       0,    19,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,    25,    26,     0,     0,    27,     0,    28,    29,
      30,    31,     0,    32,    33,    34,     0,     0,    35,    36,
      37,    38,    39,    40,   163,   347,    42,     0,     0,    43,
       0,     0,     0,    44,    45,     0,    46,     0,    47,    48,
      49,     1,     2,     0,     3,     4,     5,     6,     7,     0,
       8,     0,     0,     9,    10,     0,     0,    11,    12,    13,
       0,    14,    15,    16,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,    18,     0,    19,    20,    21,
      22,    23,    24,     0,     0,     0,     0,     0,    25,    26,
       0,     0,    27,     0,    28,    29,    30,    31,     0,    32,
      33,    34,     0,     0,    35,    36,    37,    38,    39,    40,
      41,     0,    42,     0,     0,    43,     0,     0,     0,    44,
      45,     0,    46,     0,    47,    48,    49,     1,     2,     0,
       3,     4,     5,     6,     7,     0,     8,     0,     0,     9,
      10,     0,     0,    11,    12,    13,     0,    14,    15,    16,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,    18,     0,    19,    20,    21,    22,    23,    24,     0,
       0,     0,     0,     0,    25,    26,     0,     0,    27,     0,
      28,    29,    30,    31,     0,    32,    33,    34,     0,     0,
      35,    36,    37,    38,    39,    40,   163,     0,    42,     0,
       0,    43,     0,     0,     0,    44,    45,     0,    46,     0,
      47,    48,    49,     1,   116,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,    23,    24,     0,     0,     0,     0,     0,
      25,    26,     0,     0,     0,     0,    28,    29,    30,    31,
       0,    32,    33,    34,     0,     0,    35,    36,    37,    38,
      39,    40,    41,     0,     0,   306,     0,    43,     0,     0,
       0,    44,    45,     0,    46,     0,    47,    48,    49,     1,
     116,     0,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    22,    23,
      24,     0,     0,     0,     0,     0,    25,    26,     0,     0,
       0,     0,    28,    29,    30,    31,     0,    32,    33,    34,
       0,     0,    35,    36,    37,    38,    39,    40,    41,   336,
       0,     0,     0,    43,     0,     0,     0,    44,    45,     0,
      46,     0,    47,    48,    49,     1,   116,     0,     3,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    22,    23,    24,     0,     0,     0,
       0,     0,    25,    26,     0,     0,     0,     0,    28,    29,
      30,    31,     0,    32,    33,    34,     0,     0,    35,    36,
      37,    38,    39,    40,    41,     0,     0,     0,     0,    43,
       0,     0,     0,    44,    45,   342,    46,     0,    47,    48,
      49,     1,   116,     0,     3,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,    23,    24,     0,     0,     0,     0,     0,    25,    26,
       0,     0,     0,     0,    28,    29,    30,    31,     0,    32,
      33,    34,     0,     0,    35,    36,    37,    38,    39,    40,
      41,     0,     0,     0,     0,    43,     0,     0,     0,    44,
      45,     0,    46,   345,    47,    48,    49,     1,   116,     0,
       3,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,    23,    24,     0,
       0,     0,     0,     0,    25,    26,     0,     0,     0,     0,
      28,    29,    30,    31,     0,    32,    33,    34,     0,     0,
      35,    36,    37,    38,    39,    40,    41,     0,     0,     0,
       0,    43,     0,     0,     0,    44,    45,   371,    46,     0,
      47,    48,    49,     1,   116,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,    23,    24,     0,     0,     0,     0,     0,
      25,    26,     0,     0,     0,     0,    28,    29,    30,    31,
       0,    32,    33,    34,     0,     0,    35,    36,    37,    38,
      39,    40,    41,     0,     0,     0,     0,    43,   492,     0,
       0,    44,    45,     0,    46,     0,    47,    48,    49,     1,
     116,     0,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    22,    23,
      24,     0,     0,     0,     0,     0,    25,    26,     0,     0,
       0,     0,    28,    29,    30,    31,     0,    32,    33,    34,
       0,     0,    35,    36,    37,    38,    39,    40,    41,     0,
       0,     0,     0,    43,     0,     0,     0,    44,    45,     0,
      46,     0,    47,    48,    49,     1,   116,     0,     3,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    22,    23,    24,     0,     0,     0,
       0,     0,    25,    26,     0,     0,     0,     0,    28,    29,
      30,    31,     0,    32,    33,    34,     0,     0,    35,    36,
      37,    38,    39,    40,    41,     0,     0,     0,     0,    43,
       0,     0,     0,   420,    45,     0,    46,     0,    47,    48,
      49,     1,   116,     0,     3,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,    23,   117,     0,     0,     0,     0,     0,    25,    26,
       0,     0,     0,     0,     0,    29,    30,    31,     0,    32,
      33,    34,     0,     0,    35,    36,    37,    38,    39,    40,
      41,     0,     0,     0,     0,   118,     0,     0,     0,    44,
      45,     0,    46,     0,    47,    48,    49,     1,   116,     0,
       3,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,    23,   117,     0,
       0,     0,     0,     0,    25,    26,     0,     0,     0,     0,
       0,    29,    30,    31,     0,    32,    33,    34,     0,     0,
      35,    36,    37,    38,    39,    40,    41,     0,     0,     0,
       0,   118,     0,     0,     0,    44,    45,     0,    46,     0,
       0,    48,    49,     1,   116,     0,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,    23,   117,     0,     0,     0,     0,     0,
      25,    26,     0,     0,     0,     0,     0,    29,    30,    31,
       0,    32,    33,    34,     0,     0,    35,    36,    37,    38,
      39,    40,    41,     0,     0,     0,     0,   118,     0,     0,
       0,    44,    45,     0,    46
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-379)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      13,    11,    48,     0,    14,    18,     8,     0,    21,    50,
      14,    24,   105,    21,    45,   175,    46,    18,     4,     5,
      46,    56,    18,   247,     4,     5,    58,    59,    58,    58,
      43,    41,    58,    24,    75,    45,    46,    58,   143,   144,
      75,    45,    46,    58,    59,    74,   151,   152,    83,     5,
      79,    83,    43,    84,    84,    78,    69,    50,     6,     7,
       8,     9,    10,    11,    85,    51,     7,     8,     9,    10,
      11,    51,    73,   233,   167,    24,   236,    73,    58,    59,
      76,    59,    62,    58,    76,    58,    78,    76,     0,    47,
      48,    49,    50,   317,    43,    84,   137,    75,    73,    11,
      78,    77,   115,    58,   117,   118,    79,    77,    84,    76,
      58,    59,   125,    75,    84,   161,   129,    58,    59,    86,
      69,   499,   124,    81,    78,    77,   117,   118,   506,    83,
      76,    85,    78,   146,    86,   359,   360,    83,    50,    85,
      78,    75,    68,    82,    70,    83,    72,    85,   189,    85,
     147,    90,    91,   163,   147,   168,   380,   203,   204,   205,
     168,   174,    88,    89,   499,    65,    16,   177,   117,   118,
     163,   506,    22,   177,    14,    15,   125,   187,    27,    28,
     129,    36,    31,    32,    33,    34,   179,    59,    60,    76,
      76,   237,    64,    73,   207,    81,   206,    29,   208,   304,
     305,    75,   206,    36,    37,   429,    80,   220,   221,   250,
      30,   123,    59,    60,   227,   439,   207,    64,   228,    75,
      74,    77,    78,    77,    59,   266,    92,    62,   269,   242,
     381,   241,    75,   384,    77,   147,   227,   241,    83,    75,
     281,    77,   252,    23,   254,   469,    76,   257,   258,   259,
      78,   163,   262,   263,   446,   447,   480,   250,   207,    84,
      84,    86,    86,    75,   369,   370,    84,   179,    86,    75,
      77,    77,    76,   266,   198,   199,    77,    86,   227,    77,
     282,   192,   193,   194,   195,   196,   197,   333,    45,    76,
      16,    83,    73,   242,    17,    73,    73,    76,    23,   309,
      75,   311,   312,     0,    37,   309,    76,    73,    84,   350,
     351,     8,    73,    76,    76,    80,    84,    61,    74,   321,
     330,   331,    75,    74,    73,     8,    58,    77,   338,   339,
      13,    53,    84,    75,    77,   247,   349,    76,   250,    84,
      86,   354,    82,    58,    54,    76,   356,    81,    76,    79,
      47,    48,    76,    50,   266,    75,   170,   367,   368,    46,
     450,   504,   506,   475,    47,    48,   446,   324,    67,    11,
     349,   289,   183,   383,   290,   183,    47,   481,   254,    92,
     228,   303,   219,    92,    92,   395,    -1,   397,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   436,    -1,    -1,   408,   409,
      -1,    -1,    -1,    -1,    -1,   317,    -1,   420,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   428,    -1,    -1,    -1,    -1,
     430,    -1,   435,    -1,    -1,    -1,   123,   124,    -1,    -1,
     432,    -1,   442,   443,    -1,    -1,   446,   450,   448,    -1,
      -1,   124,    -1,    -1,    -1,    -1,    -1,   359,   360,    -1,
     147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   472,
      -1,    -1,    -1,   146,   161,    -1,   163,    -1,   380,   479,
      -1,    -1,    -1,   483,    -1,    -1,    -1,    -1,   161,   481,
      -1,    -1,   179,    -1,    -1,    -1,   499,    -1,    -1,    -1,
     500,   501,   502,   506,    -1,   192,   193,   194,   195,   196,
     197,   198,   199,    -1,    -1,    -1,   203,   204,   205,   192,
     193,   194,   195,   196,   197,   198,   199,   429,    -1,    -1,
     203,   204,   205,    -1,    -1,    -1,    -1,   439,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     237,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     247,    -1,    -1,   250,   237,    -1,    -1,   469,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   480,   266,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   282,    -1,    -1,    -1,    -1,
      -1,    -1,   289,   290,    -1,    -1,    -1,    -1,    -1,   282,
      -1,    -1,    -1,    -1,    -1,    -1,   289,   290,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     317,    -1,    -1,    -1,   321,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     0,   333,    -1,   321,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    13,    -1,
     333,    16,    17,    -1,    -1,    20,    21,    22,    -1,    24,
      25,    26,   359,   360,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    38,    -1,    40,    41,    42,    43,    44,
      45,    -1,    -1,   380,    -1,    -1,    51,    52,    -1,    -1,
      55,    -1,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    -1,
      75,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,
      85,    -1,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   429,    -1,    -1,   432,    -1,   420,    -1,    -1,
      -1,    -1,   439,    -1,    -1,    -1,    -1,    -1,    -1,   432,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   469,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   480,   481,    -1,    -1,     4,     5,   472,
       7,     8,     9,    10,    11,    -1,    13,    -1,   481,    16,
      17,    -1,    -1,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,    -1,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,
      87,    88,    89,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    13,    -1,    -1,    16,    17,    -1,    -1,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    52,    -1,    -1,    55,    -1,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    78,    -1,    -1,
      -1,    82,    83,    -1,    85,    -1,    87,    88,    89,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    13,    -1,
      -1,    16,    17,    -1,    -1,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    38,    -1,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      55,    -1,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,
      85,    -1,    87,    88,    89,     4,     5,    -1,     7,     8,
       9,    10,    11,    -1,    13,    -1,    -1,    16,    17,    -1,
      -1,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,
      -1,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    52,    -1,    -1,    55,    -1,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    -1,    -1,    78,
      -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,    88,
      89,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      13,    -1,    -1,    16,    17,    -1,    -1,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    38,    -1,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    55,    -1,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    82,
      83,    -1,    85,    -1,    87,    88,    89,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    13,    -1,    -1,    16,
      17,    -1,    -1,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,    -1,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    -1,    75,    -1,
      -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,
      87,    88,    89,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    76,    -1,    78,    -1,    -1,
      -1,    82,    83,    -1,    85,    -1,    87,    88,    89,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,
      85,    -1,    87,    88,    89,     4,     5,    -1,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    82,    83,    84,    85,    -1,    87,    88,
      89,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,
      83,    -1,    85,    86,    87,    88,    89,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    82,    83,    84,    85,    -1,
      87,    88,    89,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    78,    79,    -1,
      -1,    82,    83,    -1,    85,    -1,    87,    88,    89,     4,
       5,    -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    83,    -1,
      85,    -1,    87,    88,    89,     4,     5,    -1,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    82,    83,    -1,    85,    -1,    87,    88,
      89,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    -1,    62,
      63,    64,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,
      83,    -1,    85,    -1,    87,    88,    89,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    -1,    62,    63,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    82,    83,    -1,    85,    -1,
      -1,    88,    89,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,
      -1,    62,    63,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    82,    83,    -1,    85
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
     184,   187,   189,   190,   191,   192,   203,   204,   206,   208,
     209,   210,   211,   212,   213,   215,   216,   217,   218,   230,
     231,   237,   238,   239,   240,   241,   243,   244,   245,   246,
     247,   248,   249,   250,   251,    78,     5,    45,    78,   156,
     203,   231,   239,   181,   185,   156,   166,   191,   231,     5,
     239,   245,   125,   190,   191,    75,    75,   111,    59,   122,
     157,   245,   122,   157,   238,    16,    22,   163,   191,   228,
     229,   157,   238,    85,   190,   191,   125,   190,   191,   209,
     237,   214,     0,    73,    96,    98,    65,   108,    36,   112,
     115,   116,     5,   155,    83,   157,   169,    76,   168,    73,
      96,    14,    15,   172,   173,   176,    75,    77,    18,   100,
      30,    29,    27,    28,    31,    32,    33,    34,    88,    89,
     246,   248,   251,    82,    90,    91,    76,    78,    85,   232,
      47,    48,    49,    50,    81,   202,    92,   242,   242,   233,
     245,    78,   157,   238,   157,   238,    76,    78,    85,    95,
      96,    98,   203,   157,   161,   128,   157,    23,    75,    96,
      75,    77,    78,    59,    75,   202,   202,   102,   239,    74,
      94,    97,    76,    74,    77,   202,   202,   219,    77,    45,
      84,    86,    77,    45,   237,    74,    94,   191,   242,   119,
     122,   113,   116,    46,    84,   170,   245,    56,    75,   169,
     190,   160,   174,    76,   173,   176,   191,    16,    96,   205,
     207,   210,   210,   210,   210,   210,   210,   212,   212,   237,
     237,   237,   190,     6,   157,   238,    76,   191,   234,    83,
     236,   193,    73,   244,    73,   245,   245,   179,   157,   238,
     234,    17,    76,    73,    73,   169,   237,   190,   157,    75,
     198,   199,    95,    23,    74,   191,    74,   229,   200,   201,
     191,   221,    84,   191,   191,    86,   191,    74,    96,    76,
     117,    37,   114,    84,    77,    84,   159,    96,   203,   177,
     183,   206,   208,    75,   236,   202,   202,   235,    76,    84,
      86,    84,   190,   191,   191,    73,    95,    84,    86,   203,
     186,   144,   145,   146,   144,   130,    76,    75,   191,   191,
     237,   191,   191,    80,    84,    76,    84,    76,    86,   170,
      96,    96,    46,   245,   191,    76,    95,    95,   194,   195,
     191,   191,   202,   202,    84,    61,    75,    95,    74,   145,
      82,   148,   149,   150,   151,   152,   191,    74,    73,   188,
      58,   104,   220,   191,   191,    77,   118,    84,    75,   175,
     191,   191,   197,   196,   239,    53,    77,    76,    81,    79,
     131,   132,   135,   142,   245,    95,   191,    76,   203,   222,
     223,   224,   239,    84,    86,    96,    95,   191,   191,   147,
     151,   152,    82,   152,   191,    76,    74,   132,   133,    58,
     103,    77,    86,    54,    95,    59,    62,   141,    76,   191,
      95,   223,    79,   191,   225,   226,    75,   134,   136,   137,
     227,    79,    76,    75,    80,   138,   139,   140,   141,   142,
     143,   164,   191,   191,   191,   136,   140
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

  case 171:
/* Line 1792 of yacc.c  */
#line 1127 "../src/parser/parser.y"
    {
			if ((yyvsp[(2) - (2)].integer) != '=') {
				g_op->push_lvar((yyvsp[(1) - (2)].cp));
			}
		}
    break;

  case 172:
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

  case 173:
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

  case 174:
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

  case 175:
/* Line 1792 of yacc.c  */
#line 1165 "../src/parser/parser.y"
    {
			if ((yyvsp[(4) - (4)].integer) != '=') {
				g_op->dup();
				g_op->find_reserved((yyvsp[(3) - (4)].integer));
			}
		}
    break;

  case 176:
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

  case 177:
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

  case 178:
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

  case 179:
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

  case 180:
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

  case 181:
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

  case 182:
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

  case 183:
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

  case 184:
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

  case 185:
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

  case 186:
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

  case 187:
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

  case 188:
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

  case 190:
/* Line 1792 of yacc.c  */
#line 1321 "../src/parser/parser.y"
    {
			(yyval.integer) = '='; 
		}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1325 "../src/parser/parser.y"
    { 
			(yyval.integer) = '+'; 
		}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1329 "../src/parser/parser.y"
    { 
			(yyval.integer) = '-'; 
		}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1333 "../src/parser/parser.y"
    { 
			(yyval.integer) = '*'; 
		}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1337 "../src/parser/parser.y"
    { 
			(yyval.integer) = '/'; 
		}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1350 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start(false);
		}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1355 "../src/parser/parser.y"
    {
			g_op->do_or();
			g_ctl->if_end();
		}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1365 "../src/parser/parser.y"
    {
			g_op->dup();
			g_ctl->if_start();
		}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1370 "../src/parser/parser.y"
    {
			g_op->do_and();
			g_ctl->if_end();
		}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1380 "../src/parser/parser.y"
    {
			g_op->do_not();
		}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1389 "../src/parser/parser.y"
    {
			g_op->gt();
		}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1393 "../src/parser/parser.y"
    {
			g_op->ge();
		}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1397 "../src/parser/parser.y"
    {
			g_op->lt();
		}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1401 "../src/parser/parser.y"
    {
			g_op->le();
		}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1405 "../src/parser/parser.y"
    {
			g_op->eq();
		}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1409 "../src/parser/parser.y"
    {
			g_op->neq();
		}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1423 "../src/parser/parser.y"
    {
			g_op->add();
		}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1427 "../src/parser/parser.y"
    {
			g_op->sub();
		}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1431 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(2) - (2)].integer));
			g_op->add();
		}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1436 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(2) - (2)].cp));
			g_op->add();
		}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1441 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(2) - (2)].real));
			g_op->add();
		}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1451 "../src/parser/parser.y"
    {
			g_op->mul();
		}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1455 "../src/parser/parser.y"
    {
			g_op->div();
		}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1459 "../src/parser/parser.y"
    {
			g_op->mod();
		}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1468 "../src/parser/parser.y"
    {
			unary_minus = true;
		}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1472 "../src/parser/parser.y"
    {
			if (unary_minus)
				g_op->minus();

			unary_minus = false;
		}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1485 "../src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (3)].integer));
		}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1489 "../src/parser/parser.y"
    {
			g_op->make_list((yyvsp[(2) - (4)].integer));
		}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1493 "../src/parser/parser.y"
    {
			g_op->make_list(-2);
		}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1497 "../src/parser/parser.y"
    {
			g_op->make_list(-3);
		}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1506 "../src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (5)].integer) + 1);
		}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1510 "../src/parser/parser.y"
    {
			g_op->make_tuple((yyvsp[(2) - (4)].integer));
		}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1514 "../src/parser/parser.y"
    {
			g_op->make_tuple(-2);
		}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1518 "../src/parser/parser.y"
    {
			g_op->make_tuple(-3);
		}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1526 "../src/parser/parser.y"
    {
			g_op->make_map((yyvsp[(2) - (3)].integer));
		}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1530 "../src/parser/parser.y"
    {
			g_op->make_map((yyvsp[(2) - (4)].integer));
		}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1538 "../src/parser/parser.y"
    {
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1543 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule_start();
		}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1547 "../src/parser/parser.y"
    {
			g_ctl->sbf_end();
			g_lvar_nil_check++;
		}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1567 "../src/parser/parser.y"
    {
			g_ctl->sbf_rule();
		}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1571 "../src/parser/parser.y"
    {
			g_ctl->sbf_in();
		}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1579 "../src/parser/parser.y"
    {
			g_ctl->sbf_list_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 1583 "../src/parser/parser.y"
    {
			g_ctl->sbf_range_gen((yyvsp[(1) - (3)].cp));
		}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 1592 "../src/parser/parser.y"
    {
			g_op->push_integer(1);
		}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 1601 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 1605 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 1614 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (3)].integer) + 1;
		}
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 1618 "../src/parser/parser.y"
    {
			(yyval.integer) = 1;
		}
    break;

  case 260:
/* Line 1792 of yacc.c  */
#line 1635 "../src/parser/parser.y"
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

  case 261:
/* Line 1792 of yacc.c  */
#line 1646 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 1650 "../src/parser/parser.y"
    {
			g_op->push_integer((yyvsp[(1) - (1)].integer));
		}
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 1654 "../src/parser/parser.y"
    {
			g_op->push_bignum('+', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 1658 "../src/parser/parser.y"
    {
			g_op->push_bignum('-', (yyvsp[(1) - (1)].cp));
		}
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 1662 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 1666 "../src/parser/parser.y"
    {
			g_op->push_real((yyvsp[(1) - (1)].real));
		}
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 1670 "../src/parser/parser.y"
    {
			g_op->make_regex();
		}
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 1674 "../src/parser/parser.y"
    {
			// already in stack
		}
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 1678 "../src/parser/parser.y"
    {
			g_op->push_reserved((yyvsp[(1) - (1)].integer));
		}
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 1682 "../src/parser/parser.y"
    {
			g_op->push_boolean(true);
		}
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 1686 "../src/parser/parser.y"
    {
			g_op->push_boolean(false);
		}
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 1690 "../src/parser/parser.y"
    {
			g_op->push_nil();
		}
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 1699 "../src/parser/parser.y"
    {
			g_op->set_last_find_position();
			g_op->find_member((yyvsp[(3) - (3)].cp));
		}
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 1704 "../src/parser/parser.y"
    {
			g_op->find_reserved((yyvsp[(3) - (3)].integer));
		}
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 1708 "../src/parser/parser.y"
    {
			g_op->clear_last_find_position();
		}
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 1712 "../src/parser/parser.y"
    {
			g_op->call((yyvsp[(3) - (3)].integer));
		}
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 1716 "../src/parser/parser.y"
    {
			g_op->listat(false);
		}
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 1720 "../src/parser/parser.y"
    {
			g_op->listat(true);
		}
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 1724 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 1729 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 1734 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member((yyvsp[(2) - (2)].cp));
		}
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 1739 "../src/parser/parser.y"
    {
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_reserved((yyvsp[(2) - (2)].integer));
		}
    break;

  case 284:
/* Line 1792 of yacc.c  */
#line 1744 "../src/parser/parser.y"
    {
			if (g_op->push_mvar_using_space((yyvsp[(1) - (1)].cp)) == false) {
				yyerror("invalid object name in name'string' format");
			}
		}
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 1750 "../src/parser/parser.y"
    {
			g_op->clone(1);
		}
    break;

  case 286:
/* Line 1792 of yacc.c  */
#line 1754 "../src/parser/parser.y"
    {
			g_op->clone((yyvsp[(4) - (4)].integer));

			// this is not normal function call (virtual function call)
			// so it should mark that don't fast popping
			g_op->disable_fast_pop();
		}
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 1767 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 289:
/* Line 1792 of yacc.c  */
#line 1771 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
		}
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 1775 "../src/parser/parser.y"
    {
			g_op->make_pair();
		}
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 1779 "../src/parser/parser.y"
    {
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 292:
/* Line 1792 of yacc.c  */
#line 1784 "../src/parser/parser.y"
    {
			g_op->push_integer(0);
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 1795 "../src/parser/parser.y"
    {
			(yyval.integer) = 0;
		}
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 1799 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(2) - (3)].integer);
		}
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 1807 "../src/parser/parser.y"
    {
			g_op->fix_last_find_position();
		}
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 1815 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_OWNER;
		}
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 1819 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_CALLER;
		}
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 1823 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_ROOT;
		}
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 1827 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MODULE;
		}
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 1831 "../src/parser/parser.y"
    {
			(yyval.integer) = OP_PUSH_MY;
		}
    break;

  case 302:
/* Line 1792 of yacc.c  */
#line 1839 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 1848 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 1857 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 307:
/* Line 1792 of yacc.c  */
#line 1865 "../src/parser/parser.y"
    {
			g_op->add();

			g_op->push_string((yyvsp[(4) - (4)].cp));

			g_op->add();
		}
    break;

  case 308:
/* Line 1792 of yacc.c  */
#line 1877 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 1886 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 1891 "../src/parser/parser.y"
    {
			g_op->push_string((yyvsp[(1) - (1)].cp));
		}
    break;

  case 313:
/* Line 1792 of yacc.c  */
#line 1899 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 1907 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 1915 "../src/parser/parser.y"
    {
			(yyval.integer) = (yyvsp[(1) - (1)].integer);
		}
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 1923 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 1931 "../src/parser/parser.y"
    {
			(yyval.cp) = (yyvsp[(1) - (1)].cp);
		}
    break;

  case 318:
/* Line 1792 of yacc.c  */
#line 1939 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;

  case 319:
/* Line 1792 of yacc.c  */
#line 1947 "../src/parser/parser.y"
    {
			(yyval.real) = (yyvsp[(1) - (1)].real);
		}
    break;


/* Line 1792 of yacc.c  */
#line 4515 "../src/parser/parser.cpp"
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
#line 1953 "../src/parser/parser.y"



