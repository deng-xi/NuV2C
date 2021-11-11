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


/* Substitute the variable and function names.  */
#define yyparse         yyvhdlparse
#define yylex           yyvhdllex
#define yyerror         yyvhdlerror
#define yydebug         yyvhdldebug
#define yynerrs         yyvhdlnerrs

#define yylval          yyvhdllval
#define yychar          yyvhdlchar

/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */


// Based on BNF Syntax at
// http://tams-www.informatik.uni-hamburg.de/vhdl/tools/grammar/vhdl93-bnf.html

#include <cstring>
#include <iostream>

#include <util/dstring.h>

#include "vhdl_parser.h"

#define PARSER vhdl_parser
#define YYSTYPE unsigned
#define YYSTYPE_IS_TRIVIAL 1

#define mto(x, y) stack(x).move_to_operands(stack(y))
#define mts(x, y) stack(x).move_to_sub((irept &)stack(y))

int yyvhdllex();
extern char *yyvhdltext;

/*******************************************************************\

Function: yyvhdlerror

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

int yyvhdlerror(const char *error_str)
{
  PARSER.parse_error(error_str, yyvhdltext);
  return strlen(error_str)+1;
}

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void init(exprt &expr)
{
  expr.clear();
  PARSER.set_source_location(expr);
}

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void init(YYSTYPE &expr)
{
  newstack(expr);
  init(stack(expr));
}

/*******************************************************************\

Function: make_nil

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void make_nil(YYSTYPE &expr)
{
  newstack(expr);
  stack(expr).make_nil();
}

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void init(YYSTYPE &expr, const irep_idt &id)
{
  init(expr);
  stack(expr).id(id);
}


#line 188 "y.tab.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.hpp".  */
#ifndef YY_YYVHDL_Y_TAB_HPP_INCLUDED
# define YY_YYVHDL_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yyvhdldebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ORL = 258,
    ANDL = 259,
    TOK_OR = 260,
    TOK_XOR = 261,
    TOK_AND = 262,
    TOK_MOD = 263,
    BIGEQ = 264,
    LESSEQ = 265,
    NOTEQ = 266,
    EQUAL = 267,
    UMINUS = 268,
    UPLUS = 269,
    NOTL = 270,
    TOK_NOT = 271,
    TOK_ABS = 272,
    TOK_ACCESS = 273,
    TOK_AFTER = 274,
    TOK_ALIAS = 275,
    TOK_ALL = 276,
    TOK_ARCHITECTURE = 277,
    TOK_ARRAY = 278,
    TOK_ASSERT = 279,
    TOK_ATTRIBUTE = 280,
    TOK_BEGIN = 281,
    TOK_BLOCK = 282,
    TOK_BODY = 283,
    TOK_BUFFER = 284,
    TOK_BUS = 285,
    TOK_CASE = 286,
    TOK_COMPONENT = 287,
    TOK_CONFIGURATION = 288,
    TOK_CONSTANT = 289,
    TOK_DISCONNENT = 290,
    TOK_DOWNTO = 291,
    TOK_ELSE = 292,
    TOK_ELSIF = 293,
    TOK_END = 294,
    TOK_ENTITY = 295,
    TOK_EXIT = 296,
    TOK_FILE = 297,
    TOK_FOR = 298,
    TOK_FUNCTION = 299,
    TOK_GENERATE = 300,
    TOK_GENERIC = 301,
    TOK_GROUP = 302,
    TOK_GUARDED = 303,
    TOK_IF = 304,
    TOK_IMPURE = 305,
    TOK_IN = 306,
    TOK_INERTIAL = 307,
    TOK_INOUT = 308,
    TOK_IS = 309,
    TOK_LABEL = 310,
    TOK_LIBRARY = 311,
    TOK_LINKAGE = 312,
    TOK_LITERAL = 313,
    TOK_LOOP = 314,
    TOK_MAP = 315,
    TOK_NAND = 316,
    TOK_NEW = 317,
    TOK_NEXT = 318,
    TOK_NOR = 319,
    TOK_NULL = 320,
    TOK_OF = 321,
    TOK_ON = 322,
    TOK_OPEN = 323,
    TOK_OTHERS = 324,
    TOK_OUT = 325,
    TOK_PACKAGE = 326,
    TOK_PORT = 327,
    TOK_POSTPONED = 328,
    TOK_PROCEDURE = 329,
    TOK_PROCESS = 330,
    TOK_PROTECTED = 331,
    TOK_PURE = 332,
    TOK_RANGE = 333,
    TOK_RECORD = 334,
    TOK_REGISTER = 335,
    TOK_REJECT = 336,
    TOK_REM = 337,
    TOK_REPORT = 338,
    TOK_RETURN = 339,
    TOK_ROL = 340,
    TOK_ROR = 341,
    TOK_SELECT = 342,
    TOK_SEVERITY = 343,
    TOK_SIGNAL = 344,
    TOK_SLA = 345,
    TOK_SLL = 346,
    TOK_SRA = 347,
    TOK_SRL = 348,
    TOK_SUBTYPE = 349,
    TOK_THEN = 350,
    TOK_TO = 351,
    TOK_TRANSPORT = 352,
    TOK_TYPE = 353,
    TOK_UNAFFECTED = 354,
    TOK_UNITS = 355,
    TOK_UNTIL = 356,
    TOK_USE = 357,
    TOK_VARIABLE = 358,
    TOK_WAIT = 359,
    TOK_WHEN = 360,
    TOK_WHILE = 361,
    TOK_WITH = 362,
    TOK_XNOR = 363,
    TOK_NATURAL = 364,
    TOK_BASED_INTEGER = 365,
    TOK_STRING = 366,
    TOK_BIT_STRING = 367,
    TOK_CHAR = 368,
    TOK_IDENTIFIER = 369
  };
#endif
/* Tokens.  */
#define ORL 258
#define ANDL 259
#define TOK_OR 260
#define TOK_XOR 261
#define TOK_AND 262
#define TOK_MOD 263
#define BIGEQ 264
#define LESSEQ 265
#define NOTEQ 266
#define EQUAL 267
#define UMINUS 268
#define UPLUS 269
#define NOTL 270
#define TOK_NOT 271
#define TOK_ABS 272
#define TOK_ACCESS 273
#define TOK_AFTER 274
#define TOK_ALIAS 275
#define TOK_ALL 276
#define TOK_ARCHITECTURE 277
#define TOK_ARRAY 278
#define TOK_ASSERT 279
#define TOK_ATTRIBUTE 280
#define TOK_BEGIN 281
#define TOK_BLOCK 282
#define TOK_BODY 283
#define TOK_BUFFER 284
#define TOK_BUS 285
#define TOK_CASE 286
#define TOK_COMPONENT 287
#define TOK_CONFIGURATION 288
#define TOK_CONSTANT 289
#define TOK_DISCONNENT 290
#define TOK_DOWNTO 291
#define TOK_ELSE 292
#define TOK_ELSIF 293
#define TOK_END 294
#define TOK_ENTITY 295
#define TOK_EXIT 296
#define TOK_FILE 297
#define TOK_FOR 298
#define TOK_FUNCTION 299
#define TOK_GENERATE 300
#define TOK_GENERIC 301
#define TOK_GROUP 302
#define TOK_GUARDED 303
#define TOK_IF 304
#define TOK_IMPURE 305
#define TOK_IN 306
#define TOK_INERTIAL 307
#define TOK_INOUT 308
#define TOK_IS 309
#define TOK_LABEL 310
#define TOK_LIBRARY 311
#define TOK_LINKAGE 312
#define TOK_LITERAL 313
#define TOK_LOOP 314
#define TOK_MAP 315
#define TOK_NAND 316
#define TOK_NEW 317
#define TOK_NEXT 318
#define TOK_NOR 319
#define TOK_NULL 320
#define TOK_OF 321
#define TOK_ON 322
#define TOK_OPEN 323
#define TOK_OTHERS 324
#define TOK_OUT 325
#define TOK_PACKAGE 326
#define TOK_PORT 327
#define TOK_POSTPONED 328
#define TOK_PROCEDURE 329
#define TOK_PROCESS 330
#define TOK_PROTECTED 331
#define TOK_PURE 332
#define TOK_RANGE 333
#define TOK_RECORD 334
#define TOK_REGISTER 335
#define TOK_REJECT 336
#define TOK_REM 337
#define TOK_REPORT 338
#define TOK_RETURN 339
#define TOK_ROL 340
#define TOK_ROR 341
#define TOK_SELECT 342
#define TOK_SEVERITY 343
#define TOK_SIGNAL 344
#define TOK_SLA 345
#define TOK_SLL 346
#define TOK_SRA 347
#define TOK_SRL 348
#define TOK_SUBTYPE 349
#define TOK_THEN 350
#define TOK_TO 351
#define TOK_TRANSPORT 352
#define TOK_TYPE 353
#define TOK_UNAFFECTED 354
#define TOK_UNITS 355
#define TOK_UNTIL 356
#define TOK_USE 357
#define TOK_VARIABLE 358
#define TOK_WAIT 359
#define TOK_WHEN 360
#define TOK_WHILE 361
#define TOK_WITH 362
#define TOK_XNOR 363
#define TOK_NATURAL 364
#define TOK_BASED_INTEGER 365
#define TOK_STRING 366
#define TOK_BIT_STRING 367
#define TOK_CHAR 368
#define TOK_IDENTIFIER 369

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yyvhdllval;

int yyvhdlparse (void);

#endif /* !YY_YYVHDL_Y_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 467 "y.tab.cpp" /* yacc.c:358  */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   866

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  131
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  494

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   369

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    18,   129,
     126,   127,    19,    16,   124,    17,   125,    20,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   128,   123,
      10,     3,    11,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   130,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     4,     5,
       6,     7,     8,     9,    12,    13,    14,    15,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   237,   237,   239,   243,   244,   248,   249,   253,   254,
     258,   264,   269,   277,   284,   288,   294,   302,   306,   307,
     311,   312,   316,   319,   323,   324,   328,   331,   335,   339,
     346,   351,   359,   362,   368,   373,   381,   388,   392,   399,
     402,   405,   408,   412,   413,   417,   421,   425,   429,   434,
     438,   442,   446,   451,   459,   463,   468,   476,   477,   481,
     482,   485,   489,   494,   502,   503,   507,   510,   516,   524,
     527,   535,   538,   541,   544,   548,   555,   560,   569,   572,
     580,   583,   586,   589,   593,   596,   599,   602,   609,   612,
     617,   620,   627,   630,   633,   639,   644,   652,   659,   662,
     670,   673,   680,   683,   691,   697,   700,   706,   709,   712,
     715,   718,   725,   728,   734,   741,   744,   750,   755,   763,
     764,   768,   773,   781,   785,   790,   799,   801,   807,   812,
     820,   821,   827,   832,   840,   846,   847,   852,   860,   864,
     865,   869,   873,   874,   879,   880,   883,   886,   889,   892,
     895,   898,   903,   908,   913,   918,   923,   928,   933,   938,
     943,   948,   953,   958,   964,   971,   976,   984,   985,   989,
     994,   999,  1007,  1012,  1017,  1022,  1027,  1032
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "ORL", "ANDL", "\"OR\"",
  "\"XOR\"", "\"AND\"", "\"MOD\"", "'<'", "'>'", "BIGEQ", "LESSEQ",
  "NOTEQ", "EQUAL", "'+'", "'-'", "'&'", "'*'", "'/'", "UMINUS", "UPLUS",
  "NOTL", "\"NOT\"", "\"ABS\"", "\"ACCESS\"", "\"AFTER\"", "\"ALIAS\"",
  "\"ALL\"", "\"ARCHITECTURE\"", "\"ARRAY\"", "\"ASSERT\"",
  "\"ATTRIBUTE\"", "\"BEGIN\"", "\"BLOCK\"", "\"BODY\"", "\"BUFFER\"",
  "\"BUS\"", "\"CASE\"", "\"COMPONENT\"", "\"CONFIGURATION\"",
  "\"CONSTANT\"", "\"DISCONNENT\"", "\"DOWNTO\"", "\"ELSE\"", "\"ELSIF\"",
  "\"END\"", "\"ENTITY\"", "\"EXIT\"", "\"FILE\"", "\"FOR\"",
  "\"FUNCTION\"", "\"GENERATE\"", "\"GENERIC\"", "\"GROUP\"",
  "\"GUARDED\"", "\"IF\"", "\"IMPURE\"", "\"IN\"", "\"INERTIAL\"",
  "\"INOUT\"", "\"IS\"", "\"LABEL\"", "\"LIBRARY\"", "\"LINKAGE\"",
  "\"LITERAL\"", "\"LOOP\"", "\"MAP\"", "\"NAND\"", "\"NEW\"", "\"NEXT\"",
  "\"NOR\"", "\"NULL\"", "\"OF\"", "\"ON\"", "\"OPEN\"", "\"OTHERS\"",
  "\"OUT\"", "\"PACKAGE\"", "\"PORT\"", "\"POSTPONED\"", "\"PROCEDURE\"",
  "\"PROCESS\"", "\"PROTECTED\"", "\"PURE\"", "\"RANGE\"", "\"RECORD\"",
  "\"REGISTER\"", "\"REJECT\"", "\"REM\"", "\"REPORT\"", "\"RETURN\"",
  "\"ROL\"", "\"ROR\"", "\"SELECT\"", "\"SEVERITY\"", "\"SIGNAL\"",
  "\"SLA\"", "\"SLL\"", "\"SRA\"", "\"SRL\"", "\"SUBTYPE\"", "\"THEN\"",
  "\"TO\"", "\"TRANSPORT\"", "\"TYPE\"", "\"UNAFFECTED\"", "\"UNITS\"",
  "\"UNTIL\"", "\"USE\"", "\"VARIABLE\"", "\"WAIT\"", "\"WHEN\"",
  "\"WHILE\"", "\"WITH\"", "\"XNOR\"", "TOK_NATURAL", "TOK_BASED_INTEGER",
  "TOK_STRING", "TOK_BIT_STRING", "TOK_CHAR", "TOK_IDENTIFIER", "';'",
  "','", "'.'", "'('", "')'", "':'", "'\\''", "'|'", "$accept",
  "design_file", "design_unit", "context_clause", "context_item",
  "use_clause", "name_list", "name", "selected_name", "library_clause",
  "library_unit", "primary_unit", "package_declaration",
  "package_declarative_part", "secondary_unit", "package",
  "package_body_declarative_part", "entity_declaration", "generic_list",
  "generic", "port_list", "port", "dir", "type",
  "element_declaration_list", "element_declaration", "identifier_list",
  "index_constraint_list", "index_constraint", "enumeration_literal_list",
  "enumeration_literal", "updown", "architecture",
  "architecture_decl_list", "architecture_decl", "s_list",
  "architecture_body", "architecture_item", "name_opt", "label_opt",
  "with_list", "with_item_list", "with_item", "process_decl_list",
  "process_decl", "process_body", "process_item", "elsepart", "cases",
  "with_value_list", "with_value", "signal_list", "sigvalue", "delay_opt",
  "map_list", "map_item", "generic_map_list", "generic_map_item", "signal",
  "choice", "choices", "element_association", "element_association_list",
  "expr", "expr_list", "conditional_expr", "comparison", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    61,   258,   259,   260,   261,   262,   263,
      60,    62,   264,   265,   266,   267,    43,    45,    38,    42,
      47,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,    59,    44,    46,    40,    41,    58,    39,
     124
};
# endif

#define YYPACT_NINF -338

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-338)))

#define YYTABLE_NINF -61

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -338,   329,  -338,    46,    46,    46,   -15,    46,  -338,   517,
    -338,  -338,  -338,  -338,  -338,  -338,  -338,  -338,  -338,  -338,
    -338,   -47,  -338,   -49,   123,    32,    46,   -32,   141,  -338,
    -338,    46,    -9,    -5,  -338,    46,   -31,  -338,  -338,    59,
    -338,  -338,   -12,    74,    32,  -338,   159,  -338,    46,    46,
     168,   114,   300,    32,   -75,  -338,    93,   235,  -338,   222,
     181,  -338,  -338,    46,    46,    46,    46,  -338,    46,   241,
      46,   513,    46,   247,   253,  -338,    -7,    79,     3,   251,
     120,  -338,   190,    32,   513,   152,   236,   308,   472,   274,
     283,   169,   207,   229,  -338,   360,  -338,  -338,   513,    46,
     472,   193,  -338,    -4,   407,   299,   317,   513,   513,   328,
     356,  -338,   472,   513,   361,   472,   472,   472,   349,  -338,
    -338,  -338,   435,   290,  -338,   624,  -338,   -11,  -338,   -56,
    -338,  -338,  -338,   174,  -338,   472,   496,    46,  -338,    32,
     390,   663,   472,    46,    46,   503,   376,   519,    46,    46,
     395,   403,    46,    46,   366,   263,  -338,   624,  -338,  -338,
    -338,  -338,  -338,  -338,  -338,  -338,     6,  -338,   322,   170,
     472,   472,   472,   472,   472,   472,   472,   472,   472,   472,
    -338,  -338,   472,   442,  -338,  -338,   513,   169,  -338,   182,
     155,   472,   409,  -338,    46,   223,   624,   138,   298,   471,
     503,   447,   828,   117,  -338,    46,   472,   258,   259,   531,
    -338,   326,   265,   472,   472,   462,   472,   527,   463,   463,
    -338,  -338,   624,   331,   701,   846,   658,   384,   441,   441,
     441,  -338,  -338,   800,    46,   418,  -338,    83,  -338,   472,
     800,  -338,   532,   459,   472,   481,   483,   472,  -338,  -338,
      81,    11,   472,    34,   103,   113,   503,   503,  -338,   341,
    -338,  -338,   795,   430,   437,   472,   439,   448,   240,  -338,
     513,   800,   472,  -338,  -338,   472,  -338,  -338,  -338,   445,
     450,   234,   571,   451,   268,   453,   454,   641,  -338,   833,
     472,   833,   472,   833,   472,   335,   335,   134,    46,  -338,
     465,   -59,   504,   536,   319,  -338,   538,   501,  -338,   800,
     800,  -338,  -338,  -338,   472,  -338,  -338,    46,    46,   472,
     472,   833,   833,   833,   535,  -338,    -8,    46,   503,  -338,
     469,   561,  -338,    46,   477,   487,   485,  -338,   795,    19,
     484,   488,    22,   489,   490,  -338,   775,   780,    46,  -338,
      46,  -338,    32,    35,    46,   494,   495,   370,  -338,   472,
     500,   615,   554,    46,   626,   515,    46,  -338,  -338,   523,
     146,   312,   472,  -338,   321,  -338,  -338,  -338,   795,   136,
     472,   583,  -338,    46,  -338,  -338,   147,   151,  -338,   472,
     573,   550,    46,   503,   568,  -338,    -2,   513,  -338,   569,
     580,  -338,  -338,    32,   566,  -338,   800,   576,  -338,   644,
     651,   748,    46,  -338,   654,    49,  -338,   702,   711,    86,
     668,   180,   379,    46,    46,    46,   603,   610,   472,  -338,
     472,   472,  -338,   741,   706,  -338,  -338,   620,   625,   628,
     184,   705,  -338,   646,   649,  -338,   467,   472,   630,   636,
    -338,  -338,   746,    13,   721,   472,   472,  -338,   503,   714,
    -338,   498,  -338,  -338,   751,   758,   647,   718,   723,   187,
      77,   716,  -338,  -338,  -338,  -338,  -338,  -338,  -338,   652,
     187,   650,   232,   486,   649,  -338,  -338,   707,   709,  -338,
     655,   656,  -338,  -338
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     3,     0,
       6,     9,     8,     5,    18,    21,    19,    25,    20,    24,
      13,     0,    14,     0,     0,    11,     0,     0,     0,     7,
       4,     0,     0,     0,    17,     0,     0,    23,    10,     0,
      16,    15,     0,     0,    12,    27,     0,    69,     0,     0,
       0,     0,     0,    76,     0,    30,     0,     0,    34,     0,
       0,    22,    78,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,    26,    90,     0,     0,     0,
       0,    31,     0,    77,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    33,    35,     0,    37,    38,     0,    88,
       0,   135,    79,     0,     0,     0,     0,     0,     0,     0,
       0,    48,     0,     0,     0,     0,     0,     0,   148,   145,
     146,   147,     0,   135,   144,     0,    55,     0,    52,     0,
      49,    65,    64,     0,    62,     0,     0,    88,    36,    89,
       0,     0,     0,    91,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   135,     0,    57,     0,    50,    51,
     153,   152,   159,   149,   138,   139,     0,   142,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,    67,     0,     0,    53,    56,     0,     0,    44,   135,
       0,     0,     0,    68,     0,   135,     0,     0,   135,     0,
       0,     0,     0,     0,   167,     0,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     150,   164,   165,     0,   161,   162,   160,   158,   154,   155,
     151,   156,   157,    45,    88,     0,    63,     0,    40,     0,
      32,    28,     0,     0,     0,     0,     0,     0,   159,   171,
       0,     0,     0,     0,     0,     0,     0,     0,    78,     0,
     121,    80,   126,     0,     0,     0,     0,     0,   135,    58,
       0,    61,     0,   140,   143,     0,   163,    47,    54,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   172,
       0,   175,     0,   173,     0,   170,   169,    90,     0,    98,
       0,     0,     0,     0,     0,    73,     0,     0,    46,   141,
     166,    41,    42,    39,     0,   137,   136,     0,     0,     0,
       0,   176,   174,   177,     0,   122,     0,     0,     0,   123,
       0,     0,    72,    88,     0,     0,    92,    95,   126,     0,
       0,   132,   135,     0,   128,   130,     0,     0,    88,   102,
       0,    99,   127,     0,     0,     0,     0,   137,    81,     0,
       0,     0,     0,     0,     0,     0,     0,    78,    78,     0,
       0,     0,     0,   124,     0,    74,    29,    96,   126,     0,
       0,     0,   133,     0,    82,   129,    90,    90,    85,     0,
       0,     0,     0,     0,     0,   103,     0,     0,   125,     0,
       0,    94,   119,   120,    97,   117,   134,     0,   131,     0,
       0,     0,    88,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,    88,    88,     0,     0,     0,   102,
       0,     0,   100,     0,     0,    93,   118,     0,     0,     0,
       0,     0,    84,     0,   112,   105,     0,     0,     0,     0,
      87,    86,     0,     0,     0,     0,     0,   102,     0,     0,
     104,     0,    75,    83,     0,     0,     0,     0,     0,   114,
       0,     0,   101,   102,   102,   109,   102,   102,   102,     0,
     116,     0,     0,     0,   112,   106,   115,     0,     0,   113,
       0,     0,   108,   107
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -338,  -338,  -338,  -338,   768,  -338,   773,    -3,  -338,  -338,
     796,  -338,  -338,  -338,  -338,  -338,  -338,  -338,   673,   755,
    -142,   752,  -338,   -74,  -338,   698,  -338,  -338,   612,  -338,
     640,  -113,  -338,  -338,  -338,   -30,  -202,  -338,  -132,  -338,
    -338,  -338,   470,  -338,  -338,   129,  -338,   346,   351,   401,
     421,  -338,  -313,  -296,  -337,  -338,   493,  -338,   -70,   639,
    -338,   642,  -338,   256,  -338,  -186,  -338
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     8,     9,    10,    11,    24,   123,    22,    12,
      13,    14,    15,    46,    16,    17,    50,    18,    54,    55,
      57,    58,    98,    93,   127,   128,   129,   155,   156,   133,
     134,   244,    19,    52,    67,    59,    76,   102,   140,   103,
     335,   336,   337,   326,   351,   370,   395,   459,   441,   404,
     405,   259,   261,   301,   343,   344,   340,   341,   124,   165,
     166,   167,   168,   202,   223,   203,   204
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      21,    23,    25,    27,    25,   192,   104,   208,   417,   217,
     111,   212,   182,    33,   249,   251,   465,   256,    56,   257,
      40,    26,   361,    36,   138,   364,   349,    31,    39,   385,
      37,    45,    44,   150,   151,    79,   183,   290,    56,   158,
      99,   256,   360,   257,   216,    53,    53,   144,    68,    42,
     115,   116,    69,   145,   328,   256,   297,   257,   117,   398,
      77,    78,    53,    80,   329,    53,   185,    83,    92,    53,
     295,   296,   186,   101,   199,    43,    32,   239,    32,   146,
     372,    92,   400,   256,   252,   257,   437,   171,   172,   173,
     174,   253,   254,    32,    32,    92,   139,   175,   176,   177,
     178,   255,   277,   350,    92,    92,   292,    20,   100,   154,
      92,   126,   235,    41,    48,    20,   294,   445,    56,   115,
     116,    47,   211,   256,   242,   257,   418,   117,    32,   115,
     116,   107,   189,   105,   139,   260,   218,   117,   288,   195,
     197,   198,   353,   422,    32,    53,    53,    32,   142,    53,
      53,   118,   429,   119,   120,   121,    20,    32,   373,   106,
     122,   171,   172,   173,   174,   386,   387,   195,    20,   279,
     258,   175,   176,   177,   178,   179,   171,   172,   173,   174,
     478,   324,   109,    92,    32,   389,   175,   176,   177,   178,
     179,   198,   245,   390,   409,   391,   308,   392,   410,   180,
      49,   356,   198,   393,    32,   280,    51,   415,   221,   432,
     268,   154,   374,   401,   433,    60,   369,    70,   246,   394,
     118,    71,   119,   120,   121,    20,   389,   104,   325,   122,
     118,   139,   119,   120,   121,    20,   391,    61,   392,   122,
     171,   172,   173,   174,   393,    32,    34,    35,   345,   100,
     175,   176,   177,   178,   179,   402,    20,   435,    20,   181,
     394,   452,   100,    32,    38,    35,   100,    92,    20,    20,
     110,   389,   470,    20,   171,   172,   173,   174,   112,   487,
     427,   391,   238,   392,   175,   176,   177,   178,   179,   393,
     131,   132,   438,   439,   101,   198,   345,   221,   187,   402,
     396,   188,    20,   402,    75,   394,    20,    32,   170,    20,
     113,   237,    96,   408,   339,   342,   104,   104,    32,   142,
     371,   143,   414,   419,   352,   171,   172,   173,   174,     2,
     139,    97,    32,   135,    62,   175,   176,   177,   178,   179,
      63,   256,    64,   257,   125,   139,    70,    53,    32,   170,
      74,    53,   243,   345,    20,   114,   141,   136,    72,     3,
     339,   313,    73,   342,    82,    32,   170,   198,   157,   307,
      95,   160,   161,   162,   396,    70,   403,     4,   169,   108,
     198,    68,    72,   101,   101,   263,   264,   214,    72,   198,
     215,   190,   267,     5,    92,   316,   126,    65,   196,   396,
     175,   176,   177,   178,   179,   130,    66,   137,     6,   139,
     396,   396,   396,   396,   396,    32,   170,   147,   403,   403,
     342,   139,   139,    32,   142,   148,   222,   224,   225,   226,
     227,   228,   229,   230,   231,   232,    70,   403,   233,     7,
     397,   198,   332,   149,    72,   159,   219,   240,   399,   220,
      70,   115,   116,   266,   152,   275,   248,   250,   276,   117,
     178,   179,   262,   115,   116,   298,   198,   163,   299,   222,
     157,   200,   271,   171,   172,   173,   174,   198,   198,   198,
     198,   198,   153,   175,   176,   177,   178,   179,   115,   116,
     -59,    32,   213,   -59,   -60,   281,   117,   -60,   402,   191,
     284,    20,   205,   287,   171,   172,   173,   174,   289,   291,
     293,   232,   164,   193,   175,   176,   177,   178,   179,   115,
     116,   304,   206,   209,   164,   389,   210,   200,   309,   234,
     247,   310,   241,   488,   265,   391,   270,   392,   272,    84,
     164,   278,   282,   393,    85,   283,   321,     3,   322,   285,
     323,   286,   118,   302,   119,   120,   121,    20,   444,   394,
     303,   122,   305,    86,   118,     4,   119,   120,   121,    20,
     338,   306,   311,   201,   314,   346,   347,   312,   315,   317,
     318,     5,   327,   331,   330,   333,   469,   334,   348,   118,
     460,   119,   120,   121,    20,   354,     6,    87,   122,    88,
      89,   355,   480,   481,   357,   482,   483,   484,    20,   359,
     358,   362,   363,   379,   366,   378,   365,   375,   376,    90,
     118,   472,   119,   120,   121,    20,   380,     7,   262,   201,
     171,   172,   173,   174,   381,    20,   406,   383,   384,    91,
     175,   176,   177,   178,   179,   411,   388,   171,   172,   173,
     174,   407,   171,   172,   173,   174,   412,   175,   176,   177,
     178,   179,   175,   176,   177,   178,   179,   174,   180,   171,
     172,   173,   174,   413,   175,   176,   177,   178,   179,   175,
     176,   177,   178,   179,   443,   319,   262,   446,   389,   389,
     455,   416,   420,   421,   457,   458,   422,   424,   391,   391,
     392,   392,   423,   461,   425,   430,   393,   393,   172,   173,
     174,   467,   468,   428,   431,   434,   440,   175,   176,   177,
     178,   179,   394,   394,   171,   172,   173,   174,   181,   171,
     172,   173,   174,   442,   175,   176,   177,   178,   179,   175,
     176,   177,   178,   179,   447,   320,   448,   449,   450,   464,
     456,   451,   454,   462,   171,   172,   173,   174,   194,   463,
     466,   471,   473,   440,   175,   176,   177,   178,   179,   474,
     475,    20,    20,   479,   490,   485,   491,    29,   492,   493,
      28,   171,   172,   173,   174,   476,   171,   172,   173,   174,
     477,   175,   176,   177,   178,   179,   175,   176,   177,   178,
     179,   171,   172,   173,   174,    30,   171,   172,   173,   174,
     426,   175,   176,   177,   178,   179,   175,   176,   177,   178,
     179,   207,   300,    81,    94,   184,   269,   236,   367,   377,
     489,   252,   486,   368,   171,   172,   173,   174,   253,   254,
     172,   453,   174,   436,   175,   176,   177,   178,   255,   175,
     176,   177,   178,   179,   173,   174,   382,   273,     0,     0,
       0,   274,   175,   176,   177,   178,   179
};

static const yytype_int16 yycheck[] =
{
       3,     4,     5,     6,     7,   137,    76,   149,    10,     3,
      84,   153,   125,    62,   200,   201,     3,     6,    48,     8,
      29,    36,     3,    26,    98,     3,    34,    74,    31,   366,
      62,    62,    35,   107,   108,    65,    47,     3,    68,   113,
      47,     6,   338,     8,   157,    48,    49,    51,   123,    54,
      16,    17,   127,    57,   113,     6,   258,     8,    24,   372,
      63,    64,    65,    66,   123,    68,   122,    70,    71,    72,
     256,   257,   128,    76,   144,    80,   125,   190,   125,    83,
      45,    84,   378,     6,     3,     8,   423,     6,     7,     8,
       9,    10,    11,   125,   125,    98,    99,    16,    17,    18,
      19,    20,   234,   111,   107,   108,     3,   122,   115,   112,
     113,   122,   186,   122,   126,   122,     3,   430,   148,    16,
      17,    62,   152,     6,   194,     8,   128,    24,   125,    16,
      17,   128,   135,    54,   137,   205,   130,    24,   127,   142,
     143,   144,   328,   130,   125,   148,   149,   125,   126,   152,
     153,   117,   103,   119,   120,   121,   122,   125,   123,    80,
     126,     6,     7,     8,     9,   367,   368,   170,   122,    86,
      53,    16,    17,    18,    19,    20,     6,     7,     8,     9,
     103,    47,    62,   186,   125,    39,    16,    17,    18,    19,
      20,   194,    54,    47,    47,    49,   270,    51,    47,    44,
     126,   333,   205,    57,   125,   122,    47,   393,   127,   123,
     213,   214,   354,    77,   128,    47,   348,   124,    80,    73,
     117,   128,   119,   120,   121,   122,    39,   297,   298,   126,
     117,   234,   119,   120,   121,   122,    49,   123,    51,   126,
       6,     7,     8,     9,    57,   125,   123,   124,   318,   115,
      16,    17,    18,    19,    20,   119,   122,    77,   122,   104,
      73,    77,   115,   125,   123,   124,   115,   270,   122,   122,
      80,    39,   458,   122,     6,     7,     8,     9,   126,    47,
     412,    49,   127,    51,    16,    17,    18,    19,    20,    57,
     121,   122,   424,   425,   297,   298,   366,   127,   124,   119,
     370,   127,   122,   119,   123,    73,   122,   125,   126,   122,
      74,   129,    59,   383,   317,   318,   386,   387,   125,   126,
     350,   128,   392,   397,   327,     6,     7,     8,     9,     0,
     333,    78,   125,   126,    34,    16,    17,    18,    19,    20,
      40,     6,    42,     8,    88,   348,   124,   350,   125,   126,
     128,   354,   129,   423,   122,    47,   100,   128,   123,    30,
     363,   127,   127,   366,   123,   125,   126,   370,   112,   129,
     123,   115,   116,   117,   444,   124,   379,    48,   122,   128,
     383,   123,   123,   386,   387,   127,   127,   124,   123,   392,
     127,   135,   127,    64,   397,   127,   122,    97,   142,   469,
      16,    17,    18,    19,    20,   122,   106,    47,    79,   412,
     480,   481,   482,   483,   484,   125,   126,    10,   421,   422,
     423,   424,   425,   125,   126,   126,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   124,   440,   182,   110,
     128,   444,   123,   126,   123,    84,   124,   191,   127,   127,
     124,    16,    17,   127,   126,   124,   200,   201,   127,    24,
      19,    20,   206,    16,    17,   124,   469,   118,   127,   213,
     214,    24,   216,     6,     7,     8,     9,   480,   481,   482,
     483,   484,   126,    16,    17,    18,    19,    20,    16,    17,
     124,   125,   126,   127,   124,   239,    24,   127,   119,     3,
     244,   122,   126,   247,     6,     7,     8,     9,   252,   253,
     254,   255,    77,   123,    16,    17,    18,    19,    20,    16,
      17,   265,     3,   128,    77,    39,   123,    24,   272,    87,
      59,   275,   123,    47,     3,    49,    74,    51,    11,    26,
      77,   123,    10,    57,    31,    86,   290,    30,   292,    68,
     294,    68,   117,   123,   119,   120,   121,   122,   429,    73,
     123,   126,   123,    50,   117,    48,   119,   120,   121,   122,
     314,   123,   127,   126,     3,   319,   320,   127,   127,   126,
     126,    64,   117,    47,    80,    47,   457,    86,    53,   117,
     123,   119,   120,   121,   122,   126,    79,    84,   126,    86,
      87,    40,   473,   474,   127,   476,   477,   478,   122,   124,
     123,   127,   124,   113,   124,   359,   127,   123,   123,   106,
     117,   123,   119,   120,   121,   122,    11,   110,   372,   126,
       6,     7,     8,     9,    80,   122,   380,    11,   123,   126,
      16,    17,    18,    19,    20,   389,   123,     6,     7,     8,
       9,    68,     6,     7,     8,     9,    83,    16,    17,    18,
      19,    20,    16,    17,    18,    19,    20,     9,    44,     6,
       7,     8,     9,   123,    16,    17,    18,    19,    20,    16,
      17,    18,    19,    20,   428,    44,   430,   431,    39,    39,
      44,   123,   123,   113,    45,    46,   130,    53,    49,    49,
      51,    51,   126,   447,    53,     3,    57,    57,     7,     8,
       9,   455,   456,    59,     3,    47,   113,    16,    17,    18,
      19,    20,    73,    73,     6,     7,     8,     9,   104,     6,
       7,     8,     9,   123,    16,    17,    18,    19,    20,    16,
      17,    18,    19,    20,     3,   104,    40,   127,   123,     3,
     104,   123,    47,   123,     6,     7,     8,     9,    95,   123,
      39,    47,    11,   113,    16,    17,    18,    19,    20,    11,
     123,   122,   122,    57,    67,   123,    67,     9,   123,   123,
       7,     6,     7,     8,     9,    67,     6,     7,     8,     9,
      67,    16,    17,    18,    19,    20,    16,    17,    18,    19,
      20,     6,     7,     8,     9,     9,     6,     7,     8,     9,
      62,    16,    17,    18,    19,    20,    16,    17,    18,    19,
      20,   148,    27,    68,    72,   127,   214,   187,    53,   359,
     484,     3,   481,    53,     6,     7,     8,     9,    10,    11,
       7,   440,     9,   422,    16,    17,    18,    19,    20,    16,
      17,    18,    19,    20,     8,     9,   363,   218,    -1,    -1,
      -1,   219,    16,    17,    18,    19,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   132,     0,    30,    48,    64,    79,   110,   133,   134,
     135,   136,   140,   141,   142,   143,   145,   146,   148,   163,
     122,   138,   139,   138,   137,   138,    36,   138,   137,   135,
     141,    74,   125,    62,   123,   124,   138,    62,   123,   138,
      29,   122,    54,    80,   138,    62,   144,    62,   126,   126,
     147,    47,   164,   138,   149,   150,   166,   151,   152,   166,
      47,   123,    34,    40,    42,    97,   106,   165,   123,   127,
     124,   128,   123,   127,   128,   123,   167,   138,   138,   166,
     138,   150,   123,   138,    26,    31,    50,    84,    86,    87,
     106,   126,   138,   154,   152,   123,    59,    78,   153,    47,
     115,   138,   168,   170,   189,    54,    80,   128,   128,    62,
      80,   154,   126,    74,    47,    16,    17,    24,   117,   119,
     120,   121,   126,   138,   189,   194,   122,   155,   156,   157,
     122,   121,   122,   160,   161,   126,   128,    47,   154,   138,
     169,   194,   126,   128,    51,    57,    83,    10,   126,   126,
     154,   154,   126,   126,   138,   158,   159,   194,   154,    84,
     194,   194,   194,   118,    77,   190,   191,   192,   193,   194,
     126,     6,     7,     8,     9,    16,    17,    18,    19,    20,
      44,   104,   162,    47,   156,   122,   128,   124,   127,   138,
     194,     3,   169,   123,    95,   138,   194,   138,   138,   189,
      24,   126,   194,   196,   197,   126,     3,   149,   151,   128,
     123,   166,   151,   126,   124,   127,   162,     3,   130,   124,
     127,   127,   194,   195,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,    87,   154,   161,   129,   127,   162,
     194,   123,   189,   129,   162,    54,    80,    59,   194,   196,
     194,   196,     3,    10,    11,    20,     6,     8,    53,   182,
     189,   183,   194,   127,   127,     3,   127,   127,   138,   159,
      74,   194,    11,   190,   192,   124,   127,   169,   123,    86,
     122,   194,    10,    86,   194,    68,    68,   194,   127,   194,
       3,   194,     3,   194,     3,   196,   196,   167,   124,   127,
      27,   184,   123,   123,   194,   123,   123,   129,   154,   194,
     194,   127,   127,   127,     3,   127,   127,   126,   126,    44,
     104,   194,   194,   194,    47,   189,   174,   117,   113,   123,
      80,    47,   123,    47,    86,   171,   172,   173,   194,   138,
     187,   188,   138,   185,   186,   189,   194,   194,    53,    34,
     111,   175,   138,   196,   126,    40,   169,   127,   123,   124,
     184,     3,   127,   124,     3,   127,   124,    53,    53,   169,
     176,   166,    45,   123,   151,   123,   123,   173,   194,   113,
      11,    80,   187,    11,   123,   185,   167,   167,   123,    39,
      47,    49,    51,    57,    73,   177,   189,   128,   183,   127,
     184,    77,   119,   138,   180,   181,   194,    68,   189,    47,
      47,   194,    83,   123,   189,   196,   123,    10,   128,   154,
     123,   113,   130,   126,    53,    53,    62,   169,    59,   103,
       3,     3,   123,   128,    47,    77,   181,   185,   169,   169,
     113,   179,   123,   194,   176,   183,   194,     3,    40,   127,
     123,   123,    77,   180,    47,    44,   104,    45,    46,   178,
     123,   194,   123,   123,     3,     3,    39,   194,   194,   176,
     196,    47,   123,    11,    11,   123,    67,    67,   103,    57,
     176,   176,   176,   176,   176,   123,   179,    47,    47,   178,
      67,    67,   123,   123
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     136,   137,   137,   138,   138,   139,   139,   140,   141,   141,
     142,   142,   143,   144,   145,   145,   146,   147,   148,   148,
     149,   149,   150,   150,   151,   151,   152,   153,   153,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   155,   155,   156,   157,   157,   158,   158,   159,
     159,   159,   160,   160,   161,   161,   162,   162,   163,   164,
     164,   165,   165,   165,   165,   165,   166,   166,   167,   167,
     168,   168,   168,   168,   168,   168,   168,   168,   169,   169,
     170,   170,   171,   171,   171,   172,   172,   173,   174,   174,
     175,   175,   176,   176,   177,   177,   177,   177,   177,   177,
     177,   177,   178,   178,   178,   179,   179,   180,   180,   181,
     181,   182,   182,   183,   183,   183,   184,   184,   185,   185,
     186,   186,   187,   187,   188,   189,   189,   189,   190,   191,
     191,   192,   193,   193,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   195,   195,   196,   196,   196,
     196,   196,   197,   197,   197,   197,   197,   197
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     2,     1,     1,
       3,     1,     3,     1,     1,     3,     3,     3,     1,     1,
       1,     1,     6,     0,     1,     1,     7,     0,    11,    16,
       1,     3,     6,     3,     1,     3,     4,     1,     1,     6,
       4,     6,     6,     1,     3,     4,     6,     5,     2,     2,
       3,     3,     1,     2,     4,     1,     2,     1,     3,     1,
       6,     3,     1,     3,     1,     1,     1,     1,    11,     0,
       2,     5,     8,     7,    10,    15,     1,     3,     0,     2,
       4,     8,     9,    14,    12,     9,    13,    13,     0,     1,
       0,     2,     1,     6,     4,     1,     3,     4,     0,     2,
       5,     8,     0,     2,     5,     4,     8,    11,    11,     7,
       2,     2,     0,     5,     2,     6,     5,     1,     3,     1,
       1,     1,     3,     3,     5,     6,     0,     3,     1,     3,
       1,     4,     1,     3,     4,     1,     6,     6,     1,     1,
       3,     4,     1,     3,     1,     1,     1,     1,     1,     2,
       3,     3,     2,     2,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     4,     3,     1,     3,     1,     3,     3,
       3,     2,     3,     3,     4,     3,     4,     4
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
        case 10:
#line 259 "parser.y" /* yacc.c:1646  */
    {
       }
#line 1978 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 265 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 1987 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 270 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 1996 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 278 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[0]);
         irep_idt id=stack((yyval)).id();
         stack((yyval)).id(ID_symbol);
         stack((yyval)).set(ID_identifier, id);
       }
#line 2007 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 289 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_member);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])));
         stack((yyval)).set(ID_component_name, stack((yyvsp[0])).id());
       }
#line 2017 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 295 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_all);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])));
       }
#line 2026 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 336 "parser.y" /* yacc.c:1646  */
    {
         //PARSER.new_entity();
       }
#line 2034 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 341 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2041 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 347 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2050 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 352 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 2059 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 360 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2066 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 363 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2073 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 369 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2082 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 374 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 2091 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 382 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_port);
       }
#line 2099 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 389 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_input);
       }
#line 2107 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 393 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_output);
       }
#line 2115 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 400 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2122 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 403 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2129 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 406 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2136 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 409 "parser.y" /* yacc.c:1646  */
    {
         // relevant for id'event
       }
#line 2144 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 414 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_enum);
       }
#line 2152 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 418 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_range);
       }
#line 2160 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 422 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_array);
       }
#line 2168 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 426 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_struct);
       }
#line 2176 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 430 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_reference);
         stack_type((yyval)).subtype()=stack_type((yyvsp[0]));
       }
#line 2185 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 435 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
       }
#line 2193 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 439 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
       }
#line 2201 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 447 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2210 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 452 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-1]);
         mts((yyval), (yyvsp[0]));
       }
#line 2219 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 464 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2228 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 469 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-1]);
         mts((yyval), (yyvsp[0]));
       }
#line 2237 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 483 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2244 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 490 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2253 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 495 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 2262 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 508 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2269 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 511 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2276 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 518 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2283 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 524 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
       }
#line 2291 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 528 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-1]);
         mts((yyval), (yyvsp[0]));
       }
#line 2300 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 536 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2307 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 539 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2314 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 542 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2321 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 546 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2328 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 550 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2335 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 556 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2344 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 561 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 2353 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 569 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
       }
#line 2361 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 573 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-1]);
         mto((yyval), (yyvsp[0]));
       }
#line 2370 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 581 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2377 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 584 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2384 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 587 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2391 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 591 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2398 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 594 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2405 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 597 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2412 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 600 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2419 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 603 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2426 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 609 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_nil);
       }
#line 2434 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 617 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_nil);
       }
#line 2442 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 621 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-1]);
       }
#line 2450 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 628 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2457 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 631 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2464 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 634 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2471 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 640 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mto((yyval), (yyvsp[0]));
       }
#line 2480 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 645 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mto((yyval), (yyvsp[0]));
       }
#line 2489 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 653 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2496 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 659 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
       }
#line 2504 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 663 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-1]);
         mts((yyval), (yyvsp[0]));
       }
#line 2513 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 671 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2520 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 674 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2527 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 680 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
       }
#line 2535 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 684 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-1]);
         mto((yyval), (yyvsp[0]));
       }
#line 2544 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 692 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_code);
         stack((yyval)).set(ID_statement, ID_assign);
         stack((yyval)).move_to_operands(stack((yyvsp[-4])), stack((yyvsp[-1])));
       }
#line 2554 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 698 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2561 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 701 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_code);
         stack((yyval)).set(ID_statement, ID_ifthenelse);
         stack((yyval)).move_to_operands(stack((yyvsp[-6])), stack((yyvsp[-4])), stack((yyvsp[-3])));
       }
#line 2571 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 707 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2578 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 710 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2585 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 713 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2592 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 716 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2599 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 719 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2606 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 725 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_nil);
       }
#line 2614 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 729 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_code);
         stack((yyval)).set(ID_statement, ID_ifthenelse);
         stack((yyval)).move_to_operands(stack((yyvsp[-3])), stack((yyvsp[-1])), stack((yyvsp[0])));
       }
#line 2624 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 735 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[0]);
       }
#line 2632 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 742 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2639 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 745 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2646 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 751 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2655 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 756 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 2664 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 769 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2673 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 774 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 2682 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 782 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
       }
#line 2690 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 786 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_when);
         stack((yyval)).move_to_operands(stack((yyvsp[-4])), stack((yyvsp[-1])));
       }
#line 2699 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 791 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_when);
         stack((yyval)).move_to_operands(stack((yyvsp[-5])), stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2708 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 799 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2715 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 802 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2722 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 808 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2731 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 813 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 2740 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 822 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2747 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 828 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2756 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 833 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 2765 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 841 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2772 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 848 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_extractbits);
         stack((yyval)).move_to_operands(stack((yyvsp[-5])), stack((yyvsp[-3])), stack((yyvsp[-1])));
       }
#line 2781 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 853 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_extractbits);
       }
#line 2789 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 881 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2796 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 884 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2803 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 887 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2810 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 890 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2817 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 893 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2824 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 896 "parser.y" /* yacc.c:1646  */
    {
       }
#line 2831 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 899 "parser.y" /* yacc.c:1646  */
    { // Vector chaining
         init((yyval), ID_concatenation);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2840 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 904 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_unary_minus);
         mto((yyval), (yyvsp[0]));
       }
#line 2849 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 909 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_unary_plus);
         mto((yyval), (yyvsp[0]));
       }
#line 2858 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 914 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_plus);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2867 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 919 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_minus);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2876 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 924 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_mult);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2885 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 929 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_div);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2894 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 934 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_mod);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2903 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 939 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_not);
         mto((yyval), (yyvsp[0]));
       }
#line 2912 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 944 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_and);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2921 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 949 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_or);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2930 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 954 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_xor);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2939 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 959 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_side_effect);
         stack((yyval)).set(ID_statement, ID_function_call);
         stack((yyval)).add(ID_operands).get_sub().swap(stack((yyvsp[-1])).get_sub());
       }
#line 2949 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 965 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-1]);
       }
#line 2957 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 972 "parser.y" /* yacc.c:1646  */
    {
         init((yyval));
         mts((yyval), (yyvsp[0]));
       }
#line 2966 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 977 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-2]);
         mts((yyval), (yyvsp[0]));
       }
#line 2975 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 986 "parser.y" /* yacc.c:1646  */
    {
         (yyval)=(yyvsp[-1]);
       }
#line 2983 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 990 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_and);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 2992 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 995 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_or);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 3001 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 1000 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_not);
         mto((yyval), (yyvsp[0]));
       }
#line 3010 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 1008 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_equal);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 3019 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 1013 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_gt);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 3028 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 1018 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_ge);
         stack((yyval)).move_to_operands(stack((yyvsp[-3])), stack((yyvsp[0])));
       }
#line 3037 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 1023 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_lt);
         stack((yyval)).move_to_operands(stack((yyvsp[-2])), stack((yyvsp[0])));
       }
#line 3046 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 1028 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_le);
         stack((yyval)).move_to_operands(stack((yyvsp[-3])), stack((yyvsp[0])));
       }
#line 3055 "y.tab.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 1033 "parser.y" /* yacc.c:1646  */
    {
         init((yyval), ID_notequal);
         stack((yyval)).move_to_operands(stack((yyvsp[-3])), stack((yyvsp[0])));
       }
#line 3064 "y.tab.cpp" /* yacc.c:1646  */
    break;


#line 3068 "y.tab.cpp" /* yacc.c:1646  */
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
