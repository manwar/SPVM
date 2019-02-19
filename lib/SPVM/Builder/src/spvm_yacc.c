/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse SPVM_yyparse
#define yylex   SPVM_yylex
#define yyerror SPVM_yyerror
#define yylval  SPVM_yylval
#define yychar  SPVM_yychar
#define yydebug SPVM_yydebug
#define yynerrs SPVM_yynerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PACKAGE = 258,
     HAS = 259,
     SUB = 260,
     OUR = 261,
     ENUM = 262,
     MY = 263,
     SELF = 264,
     USE = 265,
     REQUIRE = 266,
     DESCRIPTOR = 267,
     IF = 268,
     UNLESS = 269,
     ELSIF = 270,
     ELSE = 271,
     FOR = 272,
     WHILE = 273,
     LAST = 274,
     NEXT = 275,
     SWITCH = 276,
     CASE = 277,
     DEFAULT = 278,
     EVAL = 279,
     NAME = 280,
     VAR_NAME = 281,
     CONSTANT = 282,
     PACKAGE_VAR_NAME = 283,
     EXCEPTION_VAR = 284,
     UNDEF = 285,
     VOID = 286,
     BYTE = 287,
     SHORT = 288,
     INT = 289,
     LONG = 290,
     FLOAT = 291,
     DOUBLE = 292,
     STRING = 293,
     OBJECT = 294,
     DOT3 = 295,
     FATCAMMA = 296,
     RW = 297,
     RO = 298,
     WO = 299,
     BEGIN = 300,
     NEW = 301,
     RETURN = 302,
     WEAKEN = 303,
     CROAK = 304,
     CURRENT_PACKAGE = 305,
     UNWEAKEN = 306,
     SPECIAL_ASSIGN = 307,
     ASSIGN = 308,
     LOGICAL_OR = 309,
     LOGICAL_AND = 310,
     BIT_XOR = 311,
     BIT_OR = 312,
     STRNE = 313,
     STREQ = 314,
     NUMNE = 315,
     NUMEQ = 316,
     ISA = 317,
     STRLE = 318,
     STRLT = 319,
     STRGE = 320,
     STRGT = 321,
     NUMLE = 322,
     NUMLT = 323,
     NUMGE = 324,
     NUMGT = 325,
     SHIFT = 326,
     REMAINDER = 327,
     DIVIDE = 328,
     MULTIPLY = 329,
     REFCNT = 330,
     ISWEAK = 331,
     LENGTH = 332,
     SCALAR = 333,
     CONVERT = 334,
     MINUS = 335,
     PLUS = 336,
     DEREF = 337,
     REF = 338,
     BIT_NOT = 339,
     LOGICAL_NOT = 340,
     DEC = 341,
     INC = 342,
     ARROW = 343
   };
#endif
/* Tokens.  */
#define PACKAGE 258
#define HAS 259
#define SUB 260
#define OUR 261
#define ENUM 262
#define MY 263
#define SELF 264
#define USE 265
#define REQUIRE 266
#define DESCRIPTOR 267
#define IF 268
#define UNLESS 269
#define ELSIF 270
#define ELSE 271
#define FOR 272
#define WHILE 273
#define LAST 274
#define NEXT 275
#define SWITCH 276
#define CASE 277
#define DEFAULT 278
#define EVAL 279
#define NAME 280
#define VAR_NAME 281
#define CONSTANT 282
#define PACKAGE_VAR_NAME 283
#define EXCEPTION_VAR 284
#define UNDEF 285
#define VOID 286
#define BYTE 287
#define SHORT 288
#define INT 289
#define LONG 290
#define FLOAT 291
#define DOUBLE 292
#define STRING 293
#define OBJECT 294
#define DOT3 295
#define FATCAMMA 296
#define RW 297
#define RO 298
#define WO 299
#define BEGIN 300
#define NEW 301
#define RETURN 302
#define WEAKEN 303
#define CROAK 304
#define CURRENT_PACKAGE 305
#define UNWEAKEN 306
#define SPECIAL_ASSIGN 307
#define ASSIGN 308
#define LOGICAL_OR 309
#define LOGICAL_AND 310
#define BIT_XOR 311
#define BIT_OR 312
#define STRNE 313
#define STREQ 314
#define NUMNE 315
#define NUMEQ 316
#define ISA 317
#define STRLE 318
#define STRLT 319
#define STRGE 320
#define STRGT 321
#define NUMLE 322
#define NUMLT 323
#define NUMGE 324
#define NUMGT 325
#define SHIFT 326
#define REMAINDER 327
#define DIVIDE 328
#define MULTIPLY 329
#define REFCNT 330
#define ISWEAK 331
#define LENGTH 332
#define SCALAR 333
#define CONVERT 334
#define MINUS 335
#define PLUS 336
#define DEREF 337
#define REF 338
#define BIT_NOT 339
#define LOGICAL_NOT 340
#define DEC 341
#define INC 342
#define ARROW 343




/* Copy the first part of user declarations.  */
#line 5 "yacc/spvm_yacc.y"

  #include <stdio.h>
  
  #include "spvm_compiler.h"
  #include "spvm_yacc_util.h"
  #include "spvm_toke.h"
  #include "spvm_op.h"
  #include "spvm_dumper.h"
  #include "spvm_constant.h"
  #include "spvm_type.h"
  #include "spvm_block.h"
  #include "spvm_list.h"
  #include "spvm_package.h"


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 305 "spvm_yacc.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2363

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  219
/* YYNRULES -- Number of states.  */
#define YYNSTATES  426

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   343

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,     2,
      54,   100,     2,    76,   101,    77,    78,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    97,    99,
       2,     2,     2,     2,    82,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,   102,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    98,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    52,    55,    56,    57,
      58,    59,    60,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    79,    80,    81,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    17,    23,
      27,    28,    30,    33,    35,    37,    39,    41,    44,    46,
      48,    51,    55,    62,    65,    68,    72,    73,    75,    79,
      82,    84,    86,    90,    96,   103,   114,   125,   135,   148,
     149,   151,   153,   157,   161,   163,   167,   168,   170,   174,
     175,   177,   180,   182,   183,   185,   188,   190,   192,   194,
     196,   198,   200,   202,   204,   206,   208,   211,   214,   217,
     220,   224,   227,   231,   234,   237,   239,   249,   255,   261,
     265,   268,   274,   281,   288,   289,   292,   299,   303,   307,
     308,   310,   312,   314,   315,   317,   319,   321,   323,   325,
     327,   329,   331,   333,   335,   337,   339,   341,   343,   345,
     347,   349,   351,   353,   355,   357,   359,   361,   365,   367,
     369,   371,   373,   375,   378,   382,   385,   387,   390,   393,
     396,   399,   402,   405,   408,   412,   416,   420,   424,   428,
     432,   436,   440,   444,   448,   450,   454,   458,   462,   466,
     470,   474,   478,   482,   486,   490,   494,   498,   502,   506,
     510,   514,   517,   521,   525,   528,   531,   533,   537,   542,
     548,   553,   558,   563,   570,   574,   581,   585,   591,   597,
     602,   607,   614,   621,   628,   631,   636,   640,   646,   649,
     652,   655,   660,   663,   665,   667,   669,   671,   673,   675,
     677,   679,   681,   683,   685,   687,   689,   691,   694,   698,
     702,   707,   712,   714,   716,   718,   720,   721,   723,   727
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     104,     0,    -1,   105,    -1,    -1,   106,    -1,   106,   107,
      -1,   107,    -1,     3,   177,   108,    -1,     3,   177,    97,
     129,   108,    -1,    53,   109,    98,    -1,    -1,   110,    -1,
     110,   111,    -1,   111,    -1,   121,    -1,   122,    -1,   115,
      -1,   120,    99,    -1,   113,    -1,   112,    -1,    45,   142,
      -1,    10,   177,    99,    -1,    10,   177,    54,   184,   100,
      99,    -1,    11,   177,    -1,     7,   116,    -1,    53,   117,
      98,    -1,    -1,   118,    -1,   118,   101,   119,    -1,   118,
     101,    -1,   119,    -1,   183,    -1,   183,    56,    27,    -1,
       6,    28,    97,   129,   176,    -1,     4,   182,    97,   129,
     176,    99,    -1,   129,     5,   183,    97,   181,    54,   124,
     127,   100,   142,    -1,   129,     5,   183,    97,   181,    54,
     124,   127,   100,    99,    -1,   129,     5,    97,   181,    54,
     124,   127,   100,   142,    -1,    51,   125,   102,   129,     5,
      97,   181,    54,   124,   127,   100,   142,    -1,    -1,   125,
      -1,   128,    -1,   128,   101,   125,    -1,   125,   101,   126,
      -1,   126,    -1,   174,    97,   176,    -1,    -1,    40,    -1,
     174,    97,     9,    -1,    -1,   130,    -1,   130,    12,    -1,
      12,    -1,    -1,   132,    -1,   132,   133,    -1,   133,    -1,
     140,    -1,   134,    -1,   135,    -1,   142,    -1,   136,    -1,
     137,    -1,   138,    -1,   143,    -1,   139,    -1,   147,    99,
      -1,    19,    99,    -1,    20,    99,    -1,    47,    99,    -1,
      47,   147,    99,    -1,    49,    99,    -1,    49,   147,    99,
      -1,   166,    99,    -1,   167,    99,    -1,    99,    -1,    17,
      54,   146,    99,   145,    99,   146,   100,   142,    -1,    18,
      54,   145,   100,   142,    -1,    21,    54,   147,   100,   142,
      -1,    22,   147,    97,    -1,    23,    97,    -1,    13,    54,
     114,   100,   142,    -1,    13,    54,   145,   100,   142,   141,
      -1,    14,    54,   145,   100,   142,   141,    -1,    -1,    16,
     142,    -1,    15,    54,   145,   100,   142,   141,    -1,    53,
     131,    98,    -1,    24,   142,    99,    -1,    -1,   149,    -1,
     147,    -1,   154,    -1,    -1,   147,    -1,   174,    -1,    29,
      -1,   175,    -1,    27,    -1,    30,    -1,   164,    -1,   165,
      -1,   163,    -1,   162,    -1,   160,    -1,   161,    -1,   169,
      -1,   170,    -1,   148,    -1,   173,    -1,   153,    -1,   150,
      -1,   172,    -1,   171,    -1,   159,    -1,   151,    -1,   152,
      -1,    54,   149,   100,    -1,    50,    -1,   168,    -1,   155,
      -1,   156,    -1,   157,    -1,    83,   147,    -1,   149,   101,
     147,    -1,   149,   101,    -1,   147,    -1,    76,   147,    -1,
      77,   147,    -1,    92,   147,    -1,    95,   147,    -1,   147,
      95,    -1,    94,   147,    -1,   147,    94,    -1,   147,    76,
     147,    -1,   147,    77,   147,    -1,   147,    81,   147,    -1,
     147,    80,   147,    -1,   147,    79,   147,    -1,   147,    59,
     147,    -1,   147,    61,   147,    -1,   147,    60,   147,    -1,
     147,    75,   147,    -1,   147,    78,   147,    -1,   158,    -1,
      54,   154,   100,    -1,   147,    65,   147,    -1,   147,    64,
     147,    -1,   147,    74,   147,    -1,   147,    73,   147,    -1,
     147,    72,   147,    -1,   147,    71,   147,    -1,   147,    63,
     147,    -1,   147,    62,   147,    -1,   147,    70,   147,    -1,
     147,    69,   147,    -1,   147,    68,   147,    -1,   147,    67,
     147,    -1,   147,    66,   176,    -1,   145,    57,   145,    -1,
     145,    58,   145,    -1,    93,   145,    -1,   147,    56,   147,
      -1,   147,    55,   147,    -1,    46,   177,    -1,    46,   180,
      -1,   123,    -1,    51,   144,   102,    -1,    54,   176,   100,
     147,    -1,   147,    96,    51,   147,   102,    -1,   163,    51,
     147,   102,    -1,   165,    51,   147,   102,    -1,    25,    54,
     144,   100,    -1,   177,    96,   183,    54,   144,   100,    -1,
     177,    96,   183,    -1,   147,    96,   183,    54,   144,   100,
      -1,   147,    96,   183,    -1,   147,    96,    54,   144,   100,
      -1,   147,    96,    53,   182,    98,    -1,   165,    53,   182,
      98,    -1,   163,    53,   182,    98,    -1,    48,   174,    96,
      53,   182,    98,    -1,    52,   174,    96,    53,   182,    98,
      -1,    84,   174,    96,    53,   182,    98,    -1,    82,   147,
      -1,    82,    53,   147,    98,    -1,    86,    82,   147,    -1,
      86,    82,    53,   147,    98,    -1,    85,   147,    -1,    90,
     174,    -1,    91,   174,    -1,     8,   174,    97,   176,    -1,
       8,   174,    -1,    26,    -1,    28,    -1,   177,    -1,   179,
      -1,   178,    -1,    25,    -1,    32,    -1,    33,    -1,    34,
      -1,    35,    -1,    36,    -1,    37,    -1,    39,    -1,    38,
      -1,   177,    61,    -1,   177,    51,   102,    -1,   179,    51,
     102,    -1,   177,    51,   147,   102,    -1,   179,    51,   147,
     102,    -1,   176,    -1,    31,    -1,    25,    -1,    25,    -1,
      -1,   185,    -1,   185,   101,   183,    -1,   183,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    64,    64,    72,    75,    88,   102,   105,   109,   115,
     124,   127,   139,   153,   156,   157,   158,   159,   160,   161,
     164,   173,   177,   183,   190,   196,   205,   208,   221,   235,
     239,   242,   246,   252,   258,   264,   268,   274,   278,   294,
     297,   308,   316,   335,   349,   352,   359,   362,   365,   376,
     379,   392,   406,   410,   413,   426,   440,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   456,   457,   458,
     462,   466,   470,   474,   475,   476,   482,   488,   494,   500,
     506,   509,   517,   528,   542,   545,   549,   555,   563,   570,
     573,   586,   587,   591,   594,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   608,   609,   610,   611,
     612,   613,   614,   615,   616,   617,   618,   619,   635,   636,
     637,   638,   639,   642,   648,   662,   666,   672,   677,   682,
     688,   693,   700,   705,   712,   717,   722,   726,   730,   734,
     738,   743,   747,   751,   757,   758,   764,   768,   772,   776,
     780,   784,   790,   794,   798,   802,   806,   810,   816,   822,
     826,   830,   836,   840,   846,   850,   854,   877,   884,   891,
     895,   899,   905,   909,   913,   918,   922,   927,   933,   937,
     941,   947,   954,   961,   968,   973,   978,   983,   990,   996,
    1002,  1009,  1013,  1019,  1025,  1031,  1032,  1033,  1036,  1040,
    1046,  1052,  1058,  1064,  1070,  1076,  1082,  1090,  1096,  1100,
    1106,  1110,  1116,  1117,  1123,  1126,  1130,  1133,  1146,  1160
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PACKAGE", "HAS", "SUB", "OUR", "ENUM",
  "MY", "SELF", "USE", "REQUIRE", "DESCRIPTOR", "IF", "UNLESS", "ELSIF",
  "ELSE", "FOR", "WHILE", "LAST", "NEXT", "SWITCH", "CASE", "DEFAULT",
  "EVAL", "NAME", "VAR_NAME", "CONSTANT", "PACKAGE_VAR_NAME",
  "EXCEPTION_VAR", "UNDEF", "VOID", "BYTE", "SHORT", "INT", "LONG",
  "FLOAT", "DOUBLE", "STRING", "OBJECT", "DOT3", "FATCAMMA", "RW", "RO",
  "WO", "BEGIN", "NEW", "RETURN", "WEAKEN", "CROAK", "CURRENT_PACKAGE",
  "'['", "UNWEAKEN", "'{'", "'('", "SPECIAL_ASSIGN", "ASSIGN",
  "LOGICAL_OR", "LOGICAL_AND", "BIT_XOR", "BIT_OR", "'&'", "STRNE",
  "STREQ", "NUMNE", "NUMEQ", "ISA", "STRLE", "STRLT", "STRGE", "STRGT",
  "NUMLE", "NUMLT", "NUMGE", "NUMGT", "SHIFT", "'+'", "'-'", "'.'",
  "REMAINDER", "DIVIDE", "MULTIPLY", "'@'", "REFCNT", "ISWEAK", "LENGTH",
  "SCALAR", "CONVERT", "MINUS", "PLUS", "DEREF", "REF", "BIT_NOT",
  "LOGICAL_NOT", "DEC", "INC", "ARROW", "':'", "'}'", "';'", "')'", "','",
  "']'", "$accept", "grammar", "opt_packages", "packages", "package",
  "package_block", "opt_declarations", "declarations", "declaration",
  "begin_block", "use", "require", "enumeration", "enumeration_block",
  "opt_enumeration_values", "enumeration_values", "enumeration_value",
  "our", "has", "sub", "anon_sub", "opt_args", "args", "arg", "opt_vaarg",
  "invocant", "opt_descriptors", "descriptors", "opt_statements",
  "statements", "statement", "for_statement", "while_statement",
  "switch_statement", "case_statement", "default_statement",
  "if_require_statement", "if_statement", "else_statement", "block",
  "eval_block", "opt_expressions", "term", "opt_expression", "expression",
  "refcnt", "expressions", "unary_op", "inc", "dec", "binary_op",
  "condition", "num_comparison_op", "str_comparison_op", "isa",
  "logical_op", "assign", "new", "array_init", "convert", "array_access",
  "call_sub", "field_access", "weaken_field", "unweaken_field",
  "isweak_field", "array_length", "string_length", "deref", "ref",
  "my_var", "var", "package_var_access", "type", "basic_type", "ref_type",
  "array_type", "array_type_with_length", "type_or_void", "field_name",
  "sub_name", "opt_sub_names", "sub_names", 0
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
     305,    91,   306,   123,    40,   307,   308,   309,   310,   311,
     312,    38,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,    43,    45,    46,   327,
     328,   329,    64,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,    58,   125,    59,
      41,    44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   103,   104,   105,   105,   106,   106,   107,   107,   108,
     109,   109,   110,   110,   111,   111,   111,   111,   111,   111,
     112,   113,   113,   114,   115,   116,   117,   117,   118,   118,
     118,   119,   119,   120,   121,   122,   122,   123,   123,   124,
     124,   124,   124,   125,   125,   126,   127,   127,   128,   129,
     129,   130,   130,   131,   131,   132,   132,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   134,   135,   136,   137,
     138,   139,   140,   140,   141,   141,   141,   142,   143,   144,
     144,   145,   145,   146,   146,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   148,   149,   149,   149,   150,   150,   150,
     151,   151,   152,   152,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   154,   154,   155,   155,   155,   155,
     155,   155,   156,   156,   156,   156,   156,   156,   157,   158,
     158,   158,   159,   159,   160,   160,   160,   161,   162,   163,
     163,   163,   164,   164,   164,   164,   164,   164,   165,   165,
     165,   166,   167,   168,   169,   169,   169,   169,   170,   171,
     172,   173,   173,   174,   175,   176,   176,   176,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   178,   179,   179,
     180,   180,   181,   181,   182,   183,   184,   184,   185,   185
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     3,     5,     3,
       0,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       2,     3,     6,     2,     2,     3,     0,     1,     3,     2,
       1,     1,     3,     5,     6,    10,    10,     9,    12,     0,
       1,     1,     3,     3,     1,     3,     0,     1,     3,     0,
       1,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       3,     2,     3,     2,     2,     1,     9,     5,     5,     3,
       2,     5,     6,     6,     0,     2,     6,     3,     3,     0,
       1,     1,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     2,     3,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     2,     2,     1,     3,     4,     5,
       4,     4,     4,     6,     3,     6,     3,     5,     5,     4,
       4,     6,     6,     6,     2,     4,     3,     5,     2,     2,
       2,     4,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     3,
       4,     4,     1,     1,     1,     1,     0,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     4,     6,   198,   199,   200,   201,
     202,   203,   204,   206,   205,     0,     1,     5,    10,    49,
       7,     0,     0,     0,     0,    52,     0,     0,    11,    13,
      19,    18,    16,     0,    14,    15,     0,    50,     0,   214,
       0,     0,    26,    24,     0,    49,    20,     9,    12,    17,
       0,    51,     8,    49,    49,   215,     0,    27,    30,    31,
     216,    21,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,   198,   193,    98,   194,    96,    99,     0,
      49,     0,    49,   118,    49,     0,    49,    49,    49,    49,
      49,     0,    49,     0,     0,     0,    49,    49,    49,    75,
     166,     0,     0,    49,    56,    58,    59,    61,    62,    63,
      65,    57,    60,    64,     0,   108,   111,   115,   116,   110,
     120,   121,   122,   114,   104,   105,   103,   102,   100,   101,
       0,     0,   119,   106,   107,   113,   112,   109,    95,    97,
       0,     0,     0,     0,    25,    29,     0,   219,     0,   217,
     192,    49,    49,    49,    49,    67,    68,    49,     0,    80,
       0,    49,   164,     0,   165,    69,     0,     0,    71,     0,
       0,    44,     0,   126,    90,    95,     0,     0,     0,   195,
     197,   196,   127,   128,    49,   184,   123,     0,   188,    49,
     189,   190,   129,   132,   130,     0,    87,    55,    49,    49,
      49,    49,    49,    49,    49,    49,    49,     0,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,   133,   131,     0,    66,    49,     0,    49,
       0,    73,    74,     0,     0,     0,   195,    33,    28,    32,
       0,     0,     0,     0,    49,    49,     0,     0,    91,    92,
     144,     0,     0,    94,     0,     0,    79,    88,     0,    49,
      49,    70,     0,    72,     0,    49,   167,   125,     0,     0,
     117,    49,     0,   207,     0,     0,     0,    49,   186,     0,
     163,   162,   139,   141,   140,   153,   152,   147,   146,   158,
     157,   156,   155,   154,   151,   150,   149,   148,   142,   134,
     135,   143,   138,   137,   136,    49,     0,    49,   176,     0,
       0,     0,     0,   174,   213,   212,     0,    34,    22,   218,
     191,    23,     0,    91,    92,   161,     0,    49,    49,     0,
       0,    49,     0,     0,   172,   208,     0,   209,     0,     0,
      43,     0,     0,   124,    45,     0,   168,   185,     0,     0,
       0,     0,     0,     0,    49,   170,   180,   171,   179,    49,
      39,   145,    81,   159,   160,    84,    84,     0,    77,    78,
     210,   211,     0,     0,     0,     0,   187,    39,   169,   178,
     177,     0,     0,    46,    40,    41,     0,     0,     0,    82,
      83,    49,   181,     0,   182,   183,    46,   175,   173,    47,
       0,     0,     0,    49,    85,     0,     0,     0,     0,    42,
      48,     0,     0,    39,     0,    36,    35,     0,    76,    46,
      37,    84,     0,    86,     0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    20,    27,    28,    29,    30,
      31,   246,    32,    43,    56,    57,    58,    33,    34,    35,
     100,   383,   384,   171,   400,   385,   101,    37,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   389,   112,
     113,   172,   247,   252,   248,   115,   174,   116,   117,   118,
     119,   249,   120,   121,   122,   250,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   315,   140,   180,   181,   164,   316,    40,
      59,   148,   149
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -370
static const yytype_int16 yypact[] =
{
      18,   278,    61,  -370,    18,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,   -29,  -370,  -370,    91,    63,
    -370,    85,    55,    59,   278,  -370,    62,    13,    91,  -370,
    -370,  -370,  -370,    15,  -370,  -370,   111,   105,    65,  -370,
      22,    24,    98,  -370,   -41,   786,  -370,  -370,  -370,  -370,
      98,  -370,  -370,    63,    63,  -370,    27,    26,  -370,    73,
      98,  -370,   107,    80,    86,    95,   103,    75,    92,   104,
    1628,   101,    62,   106,  -370,  -370,  -370,  -370,  -370,   278,
     955,   107,  1036,  -370,   377,   107,  1628,  1628,  1628,  1378,
    1628,   107,  1628,    82,   107,   107,  1628,  1628,  1628,  -370,
    -370,   190,   102,   874,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  1974,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,  -370,    31,  -370,    41,
     100,   108,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
     112,   113,   278,   278,  -370,    98,   176,  -370,   115,   117,
     122,  1290,  1459,  1117,  1459,  -370,  -370,  1628,  2188,  -370,
     121,   620,   153,   161,  -370,  -370,  2016,   125,  -370,  2058,
     -56,  -370,   120,  2231,   123,   126,   129,     6,   128,   -22,
    -370,   178,   -15,   -15,  1628,   -15,   -15,   134,   -15,  1547,
    -370,  -370,   -15,    -7,    -7,   135,  -370,  -370,  1628,  1628,
    1628,  1628,  1628,  1628,  1628,  1628,  1628,   278,  1628,  1628,
    1628,  1628,  1628,  1628,  1628,  1628,  1628,  1628,  1628,  1628,
    1628,  1628,  1628,  -370,  -370,    51,  -370,  1628,    85,  1628,
      85,  -370,  -370,    98,   248,   136,    16,  -370,  -370,  -370,
     137,    98,   278,   278,  1459,  1459,   139,   -48,  2231,  -370,
    -370,   -38,   138,  2231,   -27,  1932,  -370,  -370,   140,   458,
     539,  -370,   192,  -370,   107,    63,  -370,  1205,   278,   193,
    -370,  1628,   146,  -370,   147,  2100,   197,  1628,   -15,   248,
    2231,  2231,  2267,  2267,   694,   779,   779,   779,   779,  -370,
     300,   300,   300,   300,   300,   300,   300,   300,    67,    58,
      58,    58,   -15,   -15,   -15,  1628,    85,   620,   198,  1669,
     164,  1713,   165,   210,  -370,  -370,   211,  -370,  -370,  -370,
    -370,  -370,    42,  1889,   151,  -370,    62,  1459,  1459,    62,
      62,  1459,    62,    62,  -370,  -370,  1757,  -370,  1801,    85,
    -370,   126,   261,  2231,  -370,    85,   -15,  -370,    85,  2144,
     214,  1845,   171,   170,   620,  -370,  -370,  -370,  -370,   620,
     107,  -370,  -370,   213,  -370,    93,    93,    14,  -370,  -370,
    -370,  -370,   177,   179,   194,   195,  -370,   107,  -370,  -370,
    -370,   188,   191,   237,   189,   196,   199,   240,    62,  -370,
    -370,   701,  -370,   248,  -370,  -370,   237,  -370,  -370,  -370,
     200,   107,   222,  1459,  -370,   204,   241,   207,   -39,   189,
    -370,   -14,    62,   107,    62,  -370,  -370,    62,  -370,   237,
    -370,    93,   219,  -370,    62,  -370
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -370,  -370,  -370,  -370,   294,   282,  -370,  -370,   271,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,   180,  -370,  -370,  -370,
    -370,  -344,   -79,    60,  -369,  -370,   -12,  -370,  -370,  -370,
     220,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -355,   -24,
    -370,  -157,  -114,   -64,   -33,  -370,   -85,  -370,  -370,  -370,
    -370,    84,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,   -59,  -370,   -52,    -1,  -370,   250,  -370,  -271,  -213,
     -32,  -370,  -370
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -127
static const yytype_int16 yytable[] =
{
      15,   177,    46,   150,   258,   170,    36,    38,   350,   327,
     328,   390,   114,    60,    45,   310,    36,   312,   141,   327,
     328,     1,   167,    44,    18,   175,   176,   407,   147,   272,
     327,   328,   187,   396,   178,   190,   191,   158,   251,   273,
     254,   142,   143,   327,   328,   264,   265,   166,   160,   169,
     422,   173,   329,   173,   182,   183,   185,   186,    61,   188,
     415,    16,   330,   192,   193,   194,   423,   272,    19,   419,
     114,   327,   328,   332,   233,    25,    55,   273,   162,   223,
     224,   225,   227,    41,   228,   179,   417,  -127,  -127,   225,
     235,   237,   229,   352,   230,    21,   -49,    22,    23,   327,
     328,    24,   305,    25,   306,   307,   270,   267,   387,   388,
      39,    47,    42,   391,    49,    45,    50,    51,    18,    53,
     253,    54,   406,    55,   255,   144,   372,   145,   173,   146,
     322,   325,   374,    74,   151,   375,    26,   220,   221,   222,
     152,   236,   236,   217,   218,   219,   220,   221,   222,   153,
     353,   275,   223,   224,   225,   289,   278,   154,   157,   177,
     161,   223,   224,   225,   189,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   155,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     320,   156,   178,   308,   309,   195,   311,   381,   159,   231,
     196,   313,   382,   239,   259,   341,   236,   232,   233,   319,
     234,   323,   260,   363,   364,   240,   344,   367,   241,   242,
     257,   262,   266,   268,   267,   269,   336,   338,   271,   274,
     276,   410,   279,   236,   343,   317,   318,   331,   346,   326,
     334,   236,   321,   179,   349,   339,   345,     6,   335,   337,
     348,   361,   354,   342,     7,     8,     9,    10,    11,    12,
      13,    14,   356,   358,   359,   360,   373,   236,   377,   379,
     380,   328,   351,     6,   173,   392,   393,   399,   236,   314,
       7,     8,     9,    10,    11,    12,    13,    14,   397,   411,
     264,   398,   394,   395,   403,   413,   402,   401,    17,    48,
     408,   386,   362,     6,   412,   365,   366,   414,   368,   369,
       7,     8,     9,    10,    11,    12,    13,    14,   386,   424,
      52,   173,   409,   197,   340,   238,   173,   405,   324,   163,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   341,     0,     0,     0,     0,     0,     0,     0,
     344,     0,     0,     0,   386,     0,     0,     0,   253,     0,
       0,     0,     0,     0,   404,     0,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,   216,   217,   218,   219,   220,
     221,   222,     0,     0,   416,    62,     0,     0,   418,    25,
     420,     0,   236,   421,   223,   224,   225,     0,     0,     0,
     425,   236,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    79,     0,     0,     0,    83,    84,     0,
       0,    86,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,     0,     0,    62,    94,    95,    96,
      25,    97,    98,     0,     0,     0,     0,     0,     0,   -89,
       0,     0,     0,    73,    74,    75,    76,    77,    78,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,    79,     0,     0,     0,    83,    84,
       0,     0,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    87,    88,     0,     0,     0,     0,
      89,    90,    91,    92,    93,     0,     0,    62,    94,    95,
      96,    25,    97,    98,     0,     0,     0,     0,     0,     0,
     335,     0,     0,     0,    73,    74,    75,    76,    77,    78,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,    79,     0,     0,     0,    83,
      84,     0,     0,    86,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    87,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,     0,     0,    62,    94,
      95,    96,    25,    97,    98,     0,     0,     0,     0,     0,
       0,   337,     0,     0,     0,    73,    74,    75,    76,    77,
      78,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,    79,     0,     0,     0,
      83,    84,     0,     0,    86,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,     0,     0,    62,
      94,    95,    96,    25,    97,    98,     0,     0,     0,     0,
     -89,     0,     0,     0,     0,     0,    73,    74,    75,    76,
      77,    78,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,     0,    79,     0,     0,
       0,    83,    84,     0,     0,    86,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,     0,    87,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,   223,   224,
     225,    94,    95,    96,    62,    97,    98,     0,    25,    63,
      64,   -93,     0,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,    79,    80,    81,    82,    83,    84,    85,    45,
      86,  -127,  -127,  -127,  -127,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,     0,    87,    88,     0,     0,     0,     0,    89,    90,
      91,    92,    93,   223,   224,   225,    94,    95,    96,     0,
      97,    98,    62,     0,   -53,    99,    25,    63,    64,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,     0,
      79,    80,    81,    82,    83,    84,    85,    45,    86,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      87,    88,     0,     0,     0,     0,    89,    90,    91,    92,
      93,     0,     0,    62,    94,    95,    96,    25,    97,    98,
       0,     0,   -54,    99,     0,     0,     0,     0,     0,     0,
      73,    74,    75,    76,    77,    78,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,    79,     0,     0,     0,    83,    84,     0,     0,    86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    87,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,     0,     0,    62,    94,    95,    96,    25,    97,
      98,     0,     0,     0,   165,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,    79,     0,     0,     0,    83,    84,     0,     0,
      86,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    87,    88,     0,     0,     0,     0,    89,    90,
      91,    92,    93,     0,     0,    62,    94,    95,    96,    25,
      97,    98,     0,     0,     0,   168,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    79,     0,     0,     0,    83,    84,     0,
       0,    86,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,     0,     0,     0,    94,    95,    96,
     -49,    97,    98,    62,     0,     0,   -93,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,    74,    75,    76,    77,    78,     0,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,     0,     0,
       0,    79,     0,     0,     0,    83,    84,     0,     0,    86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    87,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,     0,     0,     0,    94,    95,    96,    62,    97,
      98,   243,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,    74,    75,    76,    77,
      78,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,    79,     0,     0,     0,
      83,    84,     0,     0,   244,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,     0,     0,     0,
      94,    95,    96,   245,    97,    98,    62,     0,     0,     0,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,    78,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,    79,     0,     0,     0,    83,    84,
       0,   184,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    87,    88,     0,     0,     0,     0,
      89,    90,    91,    92,    93,     0,     0,    62,    94,    95,
      96,    25,    97,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    73,    74,    75,    76,    77,    78,
       0,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,    79,     0,     0,     0,    83,
      84,     0,     0,   244,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    87,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,     0,     0,     0,    94,
      95,    96,   245,    97,    98,    62,     0,     0,     0,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,     0,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    79,     0,     0,     0,    83,    84,     0,
     277,    86,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,     0,     0,    62,    94,    95,    96,
      25,    97,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,    78,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,     0,    79,     0,     0,     0,    83,    84,
       0,     0,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    87,    88,     0,     0,     0,     0,
      89,    90,    91,    92,    93,     0,     0,     0,    94,    95,
      96,     0,    97,    98,   198,   199,     0,     0,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   223,   224,   225,     0,     0,   198,   199,
       0,   355,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   223,   224,   225,
       0,     0,   198,   199,     0,   357,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   223,   224,   225,     0,     0,   198,   199,     0,   370,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   223,   224,   225,     0,     0,
     198,   199,     0,   371,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   223,
     224,   225,     0,     0,   198,   199,     0,   378,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   223,   224,   225,     0,   198,   199,  -126,
    -126,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   223,   224,   225,   198,
     199,     0,   333,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   223,   224,
     225,   198,   199,   226,     0,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     223,   224,   225,   198,   199,   261,     0,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   223,   224,   225,   198,   199,   263,     0,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   223,   224,   225,     0,   347,   198,
     199,     0,     0,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   223,   224,
     225,     0,   376,   198,   199,     0,     0,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   223,   224,   225,   256,   198,   199,     0,     0,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   223,   224,   225,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   223,   224,   225
};

static const yytype_int16 yycheck[] =
{
       1,    86,    26,    62,   161,    84,    18,    19,   279,    57,
      58,   366,    45,    54,    53,   228,    28,   230,    50,    57,
      58,     3,    81,    24,    53,    84,    85,   396,    60,    51,
      57,    58,    91,   377,    86,    94,    95,    70,   152,    61,
     154,    53,    54,    57,    58,   101,   102,    80,    72,    82,
     419,    84,   100,    86,    87,    88,    89,    90,    99,    92,
      99,     0,   100,    96,    97,    98,   421,    51,    97,   413,
     103,    57,    58,   100,    96,    12,    25,    61,    79,    94,
      95,    96,    51,    28,    53,    86,   100,    94,    95,    96,
     142,   143,    51,   306,    53,     4,     5,     6,     7,    57,
      58,    10,    51,    12,    53,    54,   100,   101,    15,    16,
      25,    98,    53,    99,    99,    53,     5,    12,    53,    97,
     153,    97,   393,    25,   157,    98,   339,   101,   161,    56,
     244,   245,   345,    26,    54,   348,    45,    79,    80,    81,
      54,   142,   143,    76,    77,    78,    79,    80,    81,    54,
     307,   184,    94,    95,    96,   207,   189,    54,    54,   244,
      54,    94,    95,    96,    82,   198,   199,   200,   201,   202,
     203,   204,   205,   206,    99,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     242,    99,   244,   225,   227,     5,   229,   354,    97,    99,
      98,   233,   359,    27,    51,   264,   207,    99,    96,   241,
      97,   244,    51,   327,   328,   100,   268,   331,   101,    97,
      99,    96,   102,    97,   101,    96,   259,   260,   100,    51,
      96,     9,    97,   234,   267,    99,    99,    99,   271,   100,
     100,   242,   243,   244,   277,    53,    53,    25,   102,   102,
      53,   100,    54,   265,    32,    33,    34,    35,    36,    37,
      38,    39,    98,    98,    54,    54,     5,   268,    54,    98,
     100,    58,   305,    25,   307,    98,    97,    40,   279,    31,
      32,    33,    34,    35,    36,    37,    38,    39,   100,   403,
     101,   100,    98,    98,    54,    54,    97,   101,     4,    28,
     100,   360,   326,    25,   100,   329,   330,   100,   332,   333,
      32,    33,    34,    35,    36,    37,    38,    39,   377,   100,
      38,   354,   401,   103,   264,   145,   359,   391,   244,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   401,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     402,    -1,    -1,    -1,   413,    -1,    -1,    -1,   391,    -1,
      -1,    -1,    -1,    -1,   388,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,   408,     8,    -1,    -1,   412,    12,
     414,    -1,   393,   417,    94,    95,    96,    -1,    -1,    -1,
     424,   402,    25,    26,    27,    28,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    82,
      83,    84,    85,    86,    -1,    -1,     8,    90,    91,    92,
      12,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,   102,
      -1,    -1,    -1,    25,    26,    27,    28,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,
      82,    83,    84,    85,    86,    -1,    -1,     8,    90,    91,
      92,    12,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    -1,    -1,    25,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,
      51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    82,    83,    84,    85,    86,    -1,    -1,     8,    90,
      91,    92,    12,    94,    95,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,    -1,    -1,    25,    26,    27,    28,    29,
      30,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      50,    51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,
      -1,    -1,    82,    83,    84,    85,    86,    -1,    -1,     8,
      90,    91,    92,    12,    94,    95,    -1,    -1,    -1,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      -1,    50,    51,    -1,    -1,    54,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    76,    77,    -1,
      -1,    -1,    -1,    82,    83,    84,    85,    86,    94,    95,
      96,    90,    91,    92,     8,    94,    95,    -1,    12,    13,
      14,   100,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    76,    77,    -1,    -1,    -1,    -1,    82,    83,
      84,    85,    86,    94,    95,    96,    90,    91,    92,    -1,
      94,    95,     8,    -1,    98,    99,    12,    13,    14,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    -1,    -1,    -1,    -1,    82,    83,    84,    85,
      86,    -1,    -1,     8,    90,    91,    92,    12,    94,    95,
      -1,    -1,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    -1,    -1,    -1,    -1,    82,    83,    84,
      85,    86,    -1,    -1,     8,    90,    91,    92,    12,    94,
      95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,    27,    28,    29,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    82,    83,
      84,    85,    86,    -1,    -1,     8,    90,    91,    92,    12,
      94,    95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    26,    27,    28,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    82,
      83,    84,    85,    86,    -1,    -1,    -1,    90,    91,    92,
       5,    94,    95,     8,    -1,    -1,    99,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    -1,    -1,    -1,    -1,    82,    83,    84,
      85,    86,    -1,    -1,    -1,    90,    91,    92,     8,    94,
      95,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,
      30,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      50,    51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,
      -1,    -1,    82,    83,    84,    85,    86,    -1,    -1,    -1,
      90,    91,    92,    93,    94,    95,     8,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    28,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,
      82,    83,    84,    85,    86,    -1,    -1,     8,    90,    91,
      92,    12,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,
      51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,
      -1,    82,    83,    84,    85,    86,    -1,    -1,    -1,    90,
      91,    92,    93,    94,    95,     8,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    26,    27,    28,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    82,
      83,    84,    85,    86,    -1,    -1,     8,    90,    91,    92,
      12,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    28,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,
      82,    83,    84,    85,    86,    -1,    -1,    -1,    90,    91,
      92,    -1,    94,    95,    55,    56,    -1,    -1,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    95,    96,    -1,    -1,    55,    56,
      -1,   102,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,
      -1,    -1,    55,    56,    -1,   102,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    95,    96,    -1,    -1,    55,    56,    -1,   102,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    95,    96,    -1,    -1,
      55,    56,    -1,   102,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      95,    96,    -1,    -1,    55,    56,    -1,   102,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,    95,    96,    -1,    55,    56,   100,
     101,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    55,
      56,    -1,   100,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    55,    56,    99,    -1,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    55,    56,    99,    -1,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    95,    96,    55,    56,    99,    -1,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    96,    -1,    98,    55,
      56,    -1,    -1,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    -1,    98,    55,    56,    -1,    -1,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    95,    96,    97,    55,    56,    -1,    -1,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    95,    96,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    95,    96
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   104,   105,   106,   107,    25,    32,    33,    34,
      35,    36,    37,    38,    39,   177,     0,   107,    53,    97,
     108,     4,     6,     7,    10,    12,    45,   109,   110,   111,
     112,   113,   115,   120,   121,   122,   129,   130,   129,    25,
     182,    28,    53,   116,   177,    53,   142,    98,   111,    99,
       5,    12,   108,    97,    97,    25,   117,   118,   119,   183,
      54,    99,     8,    13,    14,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    46,
      47,    48,    49,    50,    51,    52,    54,    76,    77,    82,
      83,    84,    85,    86,    90,    91,    92,    94,    95,    99,
     123,   129,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   142,   143,   147,   148,   150,   151,   152,   153,
     155,   156,   157,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     177,   183,   129,   129,    98,   101,    56,   183,   184,   185,
     174,    54,    54,    54,    54,    99,    99,    54,   147,    97,
     142,    54,   177,   179,   180,    99,   147,   174,    99,   147,
     125,   126,   144,   147,   149,   174,   174,   149,   176,   177,
     178,   179,   147,   147,    53,   147,   147,   174,   147,    82,
     174,   174,   147,   147,   147,     5,    98,   133,    55,    56,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    94,    95,    96,    99,    51,    53,    51,
      53,    99,    99,    96,    97,   176,   177,   176,   119,    27,
     100,   101,    97,    11,    54,    93,   114,   145,   147,   154,
     158,   145,   146,   147,   145,   147,    97,    99,   144,    51,
      51,    99,    96,    99,   101,   102,   102,   101,    97,    96,
     100,   100,    51,    61,    51,   147,    96,    53,   147,    97,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   176,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,    51,    53,    54,   183,   147,
     182,   147,   182,   183,    31,   176,   181,    99,    99,   183,
     176,   177,   145,   147,   154,   145,   100,    57,    58,   100,
     100,    99,   100,   100,   100,   102,   147,   102,   147,    53,
     126,   174,   129,   147,   176,    53,   147,    98,    53,   147,
     181,   147,   182,   144,    54,   102,    98,   102,    98,    54,
      54,   100,   142,   145,   145,   142,   142,   145,   142,   142,
     102,   102,   182,     5,   182,   182,    98,    54,   102,    98,
     100,   144,   144,   124,   125,   128,   174,    15,    16,   141,
     141,    99,    98,    97,    98,    98,   124,   100,   100,    40,
     127,   101,    97,    54,   142,   146,   181,   127,   100,   125,
       9,   145,   100,    54,   100,    99,   142,   100,   142,   124,
     142,   142,   127,   141,   100,   142
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
      yyerror (compiler, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, compiler)
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
		  Type, Value, compiler); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, SPVM_COMPILER* compiler)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, compiler)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    SPVM_COMPILER* compiler;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (compiler);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, SPVM_COMPILER* compiler)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, compiler)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    SPVM_COMPILER* compiler;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, compiler);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, SPVM_COMPILER* compiler)
#else
static void
yy_reduce_print (yyvsp, yyrule, compiler)
    YYSTYPE *yyvsp;
    int yyrule;
    SPVM_COMPILER* compiler;
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , compiler);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, compiler); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, SPVM_COMPILER* compiler)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, compiler)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    SPVM_COMPILER* compiler;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (compiler);

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
int yyparse (SPVM_COMPILER* compiler);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






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
yyparse (SPVM_COMPILER* compiler)
#else
int
yyparse (compiler)
    SPVM_COMPILER* compiler;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 2:
#line 65 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_grammar(compiler, (yyvsp[(1) - (1)].opval));
      compiler->op_grammar = (yyval.opval);
    ;}
    break;

  case 3:
#line 72 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 4:
#line 76 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 5:
#line 89 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (2)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (2)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 7:
#line 106 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), (yyvsp[(3) - (3)].opval), NULL);
    ;}
    break;

  case 8:
#line 110 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(5) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 9:
#line 116 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_class_block;
    ;}
    break;

  case 10:
#line 124 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 11:
#line 128 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        (yyval.opval) = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, (yyval.opval), (yyval.opval)->last, (yyvsp[(1) - (1)].opval));
      }
    ;}
    break;

  case 12:
#line 140 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (2)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (2)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 20:
#line 165 "yacc/spvm_yacc.y"
    { 
      SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUB, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "BEGIN", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_sub(compiler, op_sub, op_sub_name, op_void_type, NULL, NULL, (yyvsp[(2) - (2)].opval), NULL, NULL, 1);
    ;}
    break;

  case 21:
#line 174 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval), NULL, 0);
    ;}
    break;

  case 22:
#line 178 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_use(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), 0);
    ;}
    break;

  case 23:
#line 184 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_use(compiler, op_use, (yyvsp[(2) - (2)].opval), NULL, 1);
    ;}
    break;

  case 24:
#line 191 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 25:
#line 197 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_enum_block;
    ;}
    break;

  case 26:
#line 205 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 27:
#line 209 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 28:
#line 222 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (3)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (3)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 29:
#line 236 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 31:
#line 243 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (1)].opval), NULL);
    ;}
    break;

  case 32:
#line 247 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_enumeration_value(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 33:
#line 253 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_our(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(2) - (5)].opval), (yyvsp[(4) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 34:
#line 259 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_has(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(2) - (6)].opval), (yyvsp[(4) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 35:
#line 265 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), (yyvsp[(10) - (10)].opval), NULL, (yyvsp[(8) - (10)].opval), 0);
     ;}
    break;

  case 36:
#line 269 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (10)].opval), (yyvsp[(3) - (10)].opval), (yyvsp[(5) - (10)].opval), (yyvsp[(7) - (10)].opval), (yyvsp[(1) - (10)].opval), NULL, NULL, (yyvsp[(8) - (10)].opval), 0);
     ;}
    break;

  case 37:
#line 275 "yacc/spvm_yacc.y"
    {
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(2) - (9)].opval), NULL, (yyvsp[(4) - (9)].opval), (yyvsp[(6) - (9)].opval), (yyvsp[(1) - (9)].opval), (yyvsp[(9) - (9)].opval), NULL, (yyvsp[(7) - (9)].opval), 0);
     ;}
    break;

  case 38:
#line 279 "yacc/spvm_yacc.y"
    {
       SPVM_OP* op_list_args;
       if ((yyvsp[(2) - (12)].opval)->id == SPVM_OP_C_ID_LIST) {
         op_list_args = (yyvsp[(2) - (12)].opval);
       }
       else {
         op_list_args = SPVM_OP_new_op_list(compiler, (yyvsp[(2) - (12)].opval)->file, (yyvsp[(2) - (12)].opval)->line);
         SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, (yyvsp[(2) - (12)].opval));
       }
       
       (yyval.opval) = SPVM_OP_build_sub(compiler, (yyvsp[(5) - (12)].opval), NULL, (yyvsp[(7) - (12)].opval), (yyvsp[(9) - (12)].opval), (yyvsp[(4) - (12)].opval), (yyvsp[(12) - (12)].opval), op_list_args, (yyvsp[(10) - (12)].opval), 0);
     ;}
    break;

  case 39:
#line 294 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 40:
#line 298 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 41:
#line 309 "yacc/spvm_yacc.y"
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, (yyvsp[(1) - (1)].opval));
       
       (yyval.opval) = op_args;
    ;}
    break;

  case 42:
#line 317 "yacc/spvm_yacc.y"
    {
      // Add invocant to arguments
      SPVM_OP* op_args;
      if ((yyvsp[(3) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_args = (yyvsp[(3) - (3)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
        op_args = op_list;
      }
      
      SPVM_OP_insert_child(compiler, op_args, op_args->first, (yyvsp[(1) - (3)].opval));
       
      (yyval.opval) = op_args;
    ;}
    break;

  case 43:
#line 336 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (3)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (3)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 45:
#line 353 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 46:
#line 359 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = NULL;
    ;}
    break;

  case 48:
#line 366 "yacc/spvm_yacc.y"
    {
      SPVM_TYPE* type = SPVM_TYPE_new(compiler);
      type->is_self = 1;
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, (yyvsp[(3) - (3)].opval)->file, (yyvsp[(3) - (3)].opval)->line);
      
      (yyval.opval) = SPVM_OP_build_arg(compiler, (yyvsp[(1) - (3)].opval), op_type);
    ;}
    break;

  case 49:
#line 376 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 50:
#line 380 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 51:
#line 393 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (2)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (2)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 53:
#line 410 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 54:
#line 414 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 55:
#line 427 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (2)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (2)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (2)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(2) - (2)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 66:
#line 453 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_expression_statement(compiler, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 69:
#line 459 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 70:
#line 463 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_return(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 71:
#line 467 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (2)].opval), NULL);
    ;}
    break;

  case 72:
#line 471 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_croak(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 75:
#line 477 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 76:
#line 483 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_for_statement(compiler, (yyvsp[(1) - (9)].opval), (yyvsp[(3) - (9)].opval), (yyvsp[(5) - (9)].opval), (yyvsp[(7) - (9)].opval), (yyvsp[(9) - (9)].opval));
    ;}
    break;

  case 77:
#line 489 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_while_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 78:
#line 495 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_switch_statement(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 79:
#line 501 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_case_statement(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 81:
#line 510 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      (yyval.opval) = SPVM_OP_build_if_require_statement(compiler, op_if_require, (yyvsp[(3) - (5)].opval), (yyvsp[(5) - (5)].opval));
    ;}
    break;

  case 82:
#line 518 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 83:
#line 529 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (6)].opval)->file, (yyvsp[(1) - (6)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      (yyval.opval) = op_block;
    ;}
    break;

  case 84:
#line 542 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 85:
#line 546 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (2)].opval);
    ;}
    break;

  case 86:
#line 550 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_if_statement(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval), (yyvsp[(6) - (6)].opval));
    ;}
    break;

  case 87:
#line 556 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, (yyvsp[(2) - (3)].opval));
      (yyval.opval) = op_block;
    ;}
    break;

  case 88:
#line 564 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_eval(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 89:
#line 570 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 90:
#line 574 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 93:
#line 591 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 117:
#line 620 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(2) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
			  SPVM_OP* op_term = (yyvsp[(2) - (3)].opval)->first;
	      SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->cur_file, compiler->cur_line);
			  while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
			    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term);
  	      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_term);
  	      op_term = op_stab;
			  }
			  (yyval.opval) = op_sequence;
      }
      else {
        (yyval.opval) = (yyvsp[(2) - (3)].opval);
      }
    ;}
    break;

  case 123:
#line 643 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_refcnt(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 124:
#line 649 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (3)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (3)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;

  case 125:
#line 663 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (2)].opval);
    ;}
    break;

  case 126:
#line 667 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(1) - (1)].opval);
    ;}
    break;

  case 127:
#line 673 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 128:
#line 678 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, op_negate, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 129:
#line 683 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_unary_op(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 130:
#line 689 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 131:
#line 694 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_inc(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 132:
#line 701 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 133:
#line 706 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, (yyvsp[(2) - (2)].opval)->file, (yyvsp[(2) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_dec(compiler, op, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 134:
#line 713 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 135:
#line 718 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 136:
#line 723 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 137:
#line 727 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 138:
#line 731 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 139:
#line 735 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 140:
#line 739 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BIT_AND, (yyvsp[(2) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, op, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 141:
#line 744 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 142:
#line 748 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 143:
#line 752 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_concat(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 145:
#line 759 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = (yyvsp[(2) - (3)].opval);
    ;}
    break;

  case 146:
#line 765 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 147:
#line 769 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 148:
#line 773 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 149:
#line 777 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 150:
#line 781 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 151:
#line 785 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 152:
#line 791 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 153:
#line 795 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 154:
#line 799 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 155:
#line 803 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 156:
#line 807 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 157:
#line 811 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_binary_op(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 158:
#line 817 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_isa(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 159:
#line 823 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_or(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 160:
#line 827 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_and(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 161:
#line 831 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_not(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 162:
#line 837 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 163:
#line 841 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_special_assign(compiler, (yyvsp[(2) - (3)].opval), (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 164:
#line 847 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 165:
#line 851 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_new(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 166:
#line 855 "yacc/spvm_yacc.y"
    {
      // Package
      SPVM_OP* op_package = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PACKAGE, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      // Create class block
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      SPVM_OP* op_list_declarations = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_list_declarations, op_list_declarations->last, (yyvsp[(1) - (1)].opval));
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, op_list_declarations);
      
      // Build package
      SPVM_OP_build_package(compiler, op_package, NULL, op_class_block, NULL);

      // Type
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, op_package->uv.package->op_type->uv.type, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      (yyval.opval) = SPVM_OP_build_new(compiler, op_new, op_type, NULL);
    ;}
    break;

  case 167:
#line 878 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_init(compiler, op_array_init, (yyvsp[(2) - (3)].opval));
    ;}
    break;

  case 168:
#line 885 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, (yyvsp[(2) - (4)].opval)->file, (yyvsp[(2) - (4)].opval)->line);
      (yyval.opval) = SPVM_OP_build_convert(compiler, op_convert, (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 169:
#line 892 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 170:
#line 896 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 171:
#line 900 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 172:
#line 906 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, NULL, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 173:
#line 910 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 174:
#line 914 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_expressions);
    ;}
    break;

  case 175:
#line 919 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (6)].opval), (yyvsp[(3) - (6)].opval), (yyvsp[(5) - (6)].opval));
    ;}
    break;

  case 176:
#line 923 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(2) - (3)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (3)].opval), (yyvsp[(3) - (3)].opval), op_expressions);
    ;}
    break;

  case 177:
#line 928 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", (yyvsp[(2) - (5)].opval)->file, (yyvsp[(2) - (5)].opval)->line);
      (yyval.opval) = SPVM_OP_build_call_sub(compiler, (yyvsp[(1) - (5)].opval), op_sub_name, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 178:
#line 934 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (5)].opval), (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 179:
#line 938 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 180:
#line 942 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_field_access(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 181:
#line 948 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[(2) - (6)].opval), (yyvsp[(5) - (6)].opval));
      (yyval.opval) = SPVM_OP_build_weaken_field(compiler, (yyvsp[(1) - (6)].opval), op_field_access);
    ;}
    break;

  case 182:
#line 955 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[(2) - (6)].opval), (yyvsp[(5) - (6)].opval));
      (yyval.opval) = SPVM_OP_build_unweaken_field(compiler, (yyvsp[(1) - (6)].opval), op_field_access);
    ;}
    break;

  case 183:
#line 962 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, (yyvsp[(2) - (6)].opval), (yyvsp[(5) - (6)].opval));
      (yyval.opval) = SPVM_OP_build_isweak_field(compiler, (yyvsp[(1) - (6)].opval), op_field_access);
    ;}
    break;

  case 184:
#line 969 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 185:
#line 974 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 186:
#line 979 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(3) - (3)].opval));
    ;}
    break;

  case 187:
#line 984 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      (yyval.opval) = SPVM_OP_build_array_length(compiler, op_array_length, (yyvsp[(4) - (5)].opval));
    ;}
    break;

  case 188:
#line 991 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_string_length(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 189:
#line 997 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_deref(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 190:
#line 1003 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, (yyvsp[(1) - (2)].opval)->file, (yyvsp[(1) - (2)].opval)->line);
      (yyval.opval) = SPVM_OP_build_ref(compiler, op_ref, (yyvsp[(2) - (2)].opval));
    ;}
    break;

  case 191:
#line 1010 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(2) - (4)].opval), (yyvsp[(4) - (4)].opval));
    ;}
    break;

  case 192:
#line 1014 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_my(compiler, (yyvsp[(1) - (2)].opval), (yyvsp[(2) - (2)].opval), NULL);
    ;}
    break;

  case 193:
#line 1020 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_var(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 194:
#line 1026 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_package_var_access(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 198:
#line 1037 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_basic_type(compiler, (yyvsp[(1) - (1)].opval));
    ;}
    break;

  case 199:
#line 1041 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 200:
#line 1047 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 201:
#line 1053 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 202:
#line 1059 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 203:
#line 1065 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 204:
#line 1071 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 205:
#line 1077 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 206:
#line 1083 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
      
      (yyval.opval) = op_type;
    ;}
    break;

  case 207:
#line 1091 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_ref_type(compiler, (yyvsp[(1) - (2)].opval));
    ;}
    break;

  case 208:
#line 1097 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 209:
#line 1101 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (3)].opval), NULL);
    ;}
    break;

  case 210:
#line 1107 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 211:
#line 1111 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_build_array_type(compiler, (yyvsp[(1) - (4)].opval), (yyvsp[(3) - (4)].opval));
    ;}
    break;

  case 213:
#line 1118 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 216:
#line 1130 "yacc/spvm_yacc.y"
    {
      (yyval.opval) = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    ;}
    break;

  case 217:
#line 1134 "yacc/spvm_yacc.y"
    {
      if ((yyvsp[(1) - (1)].opval)->id == SPVM_OP_C_ID_LIST) {
        (yyval.opval) = (yyvsp[(1) - (1)].opval);
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (1)].opval)->file, (yyvsp[(1) - (1)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (1)].opval));
        (yyval.opval) = op_list;
      }
    ;}
    break;

  case 218:
#line 1147 "yacc/spvm_yacc.y"
    {
      SPVM_OP* op_list;
      if ((yyvsp[(1) - (3)].opval)->id == SPVM_OP_C_ID_LIST) {
        op_list = (yyvsp[(1) - (3)].opval);
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, (yyvsp[(1) - (3)].opval)->file, (yyvsp[(1) - (3)].opval)->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(1) - (3)].opval));
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, (yyvsp[(3) - (3)].opval));
      
      (yyval.opval) = op_list;
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3639 "spvm_yacc.tab.c"
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
      yyerror (compiler, YY_("syntax error"));
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
	    yyerror (compiler, yymsg);
	  }
	else
	  {
	    yyerror (compiler, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval, compiler);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
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
		  yystos[yystate], yyvsp, compiler);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (compiler, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, compiler);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, compiler);
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


#line 1162 "yacc/spvm_yacc.y"


