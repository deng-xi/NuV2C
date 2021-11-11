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
#define yyparse         yyverilogparse
#define yylex           yyveriloglex
#define yyerror         yyverilogerror
#define yydebug         yyverilogdebug
#define yynerrs         yyverilognerrs

#define yylval          yyveriloglval
#define yychar          yyverilogchar

/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

/*******************************************************************\

Module: Verilog Parser

Author: Daniel Kroening, kroening@cs.cmu.edu

\*******************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <util/expr_util.h>
#include <util/std_expr.h>

#include "verilog_parser.h"

#define PARSER verilog_parser
#define YYSTYPE unsigned
#define YYSTYPE_IS_TRIVIAL 1

//#define YYDEBUG 1

#define mto(x, y) stack(x).move_to_operands(stack(y))
#define mts(x, y) stack(x).move_to_sub((irept &)stack(y))
#define swapop(x, y) stack(x).operands().swap(stack(y).operands())
#define addswap(x, y, z) stack(x).add(y).swap(stack(z))

int yyveriloglex();
extern char *yyverilogtext;

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void init(exprt &expr)
{
  expr.clear();
  verilog_parser.set_source_location(expr);
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

/*******************************************************************\

Function: new_symbol

  Inputs:

 Outputs:

 Purpose:


\*******************************************************************/

inline static void new_symbol(YYSTYPE &dest, YYSTYPE &src)
{
  init(dest, ID_symbol);
  addswap(dest, ID_identifier, src);
}

/*******************************************************************\

Function: extractbit

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

static void extractbit(YYSTYPE &expr, YYSTYPE &identifier, YYSTYPE &part)
{
  init(expr, ID_extractbit);
  mto(expr, identifier);
  stack(expr).move_to_operands(stack(part).op0());
}

/*******************************************************************\

Function: extractbits

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

static void extractbits(YYSTYPE &expr, YYSTYPE &identifier, YYSTYPE &range)
{
  init(expr, ID_extractbits);
  mto(expr, identifier);
  
  if(stack(range).id()==ID_part_select)
  {
    stack(expr).move_to_operands(stack(range).op0(),
                                 stack(range).op1());
  }
  else if(stack(range).id()==ID_indexed_part_select_plus)
  {
    exprt offset=minus_exprt(stack(range).op1(), gen_one(integer_typet()));
    stack(expr).copy_to_operands(stack(range).op0(),
                                 plus_exprt(stack(range).op0(), offset));
  }
  else if(stack(range).id()==ID_indexed_part_select_minus)
  {
    exprt offset=minus_exprt(stack(range).op1(), gen_one(integer_typet()));
    stack(expr).copy_to_operands(stack(range).op0(),
                                 minus_exprt(stack(range).op1(), offset));
  }
  else
    assert(false);
}

/*******************************************************************\

Function: add_as_subtype

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

static void add_as_subtype(typet &dest, typet &what)
{
  // this is recursive and quadratic-time, so not super.
  if(what.is_nil())
  {
    // do nothing
  }
  else if(dest.is_nil() || dest.id()==irep_idt())
    dest.swap(what);
  else
  {
    typet &subtype=dest.subtype();
    add_as_subtype(subtype, what);
  }
}

/*******************************************************************\

Function: yyverilogerror

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

int yyverilogerror(const char *error)
{
  verilog_parser.parse_error(error, yyverilogtext);
  return strlen(error)+1;
}


#line 302 "verilog_y.tab.cpp" /* yacc.c:339  */

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
   by #include "verilog_y.tab.hpp".  */
#ifndef YY_YYVERILOG_VERILOG_Y_TAB_HPP_INCLUDED
# define YY_YYVERILOG_VERILOG_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yyverilogdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_PARSE_LANGUAGE = 258,
    TOK_PARSE_EXPRESSION = 259,
    TOK_PARSE_TYPE = 260,
    TOK_PARENASTERIC = 261,
    TOK_ASTERICPAREN = 262,
    TOK_EXCLAM = 263,
    TOK_TILDE = 264,
    TOK_AMPER = 265,
    TOK_TILDEAMPER = 266,
    TOK_TILDEVERTBAR = 267,
    TOK_CARET = 268,
    TOK_TILDECARET = 269,
    TOK_CARETTILDE = 270,
    TOK_MINUSGREATER = 271,
    TOK_ASTERIC = 272,
    TOK_SLASH = 273,
    TOK_PERCENT = 274,
    TOK_EQUALEQUAL = 275,
    TOK_EXCLAMEQUAL = 276,
    TOK_EQUALEQUALEQUAL = 277,
    TOK_EXCLAMEQUALEQUAL = 278,
    TOK_AMPERAMPER = 279,
    TOK_VERTBARVERTBAR = 280,
    TOK_LESS = 281,
    TOK_LESSEQUAL = 282,
    TOK_GREATER = 283,
    TOK_GREATEREQUAL = 284,
    TOK_GREATERGREATER = 285,
    TOK_GREATERGREATERGREATER = 286,
    TOK_LESSLESS = 287,
    TOK_LESSLESSLESS = 288,
    TOK_PLUS = 289,
    TOK_MINUS = 290,
    TOK_VERTBAR = 291,
    TOK_QUESTION = 292,
    TOK_COLON = 293,
    TOK_ALWAYS = 294,
    TOK_AND = 295,
    TOK_ASSIGN = 296,
    TOK_AUTOMATIC = 297,
    TOK_BEGIN = 298,
    TOK_BUF = 299,
    TOK_BUFIF0 = 300,
    TOK_BUFIF1 = 301,
    TOK_CASE = 302,
    TOK_CASEX = 303,
    TOK_CASEZ = 304,
    TOK_CMOS = 305,
    TOK_DEASSIGN = 306,
    TOK_DEFAULT = 307,
    TOK_DEFPARAM = 308,
    TOK_DISABLE = 309,
    TOK_EDGE = 310,
    TOK_ELSE = 311,
    TOK_END = 312,
    TOK_ENDCASE = 313,
    TOK_ENDFUNCTION = 314,
    TOK_ENDGENERATE = 315,
    TOK_ENDMODULE = 316,
    TOK_ENDPRIMITIVE = 317,
    TOK_ENDSPECIFY = 318,
    TOK_ENDTABLE = 319,
    TOK_ENDTASK = 320,
    TOK_EVENT = 321,
    TOK_FOR = 322,
    TOK_FORCE = 323,
    TOK_FOREVER = 324,
    TOK_FORK = 325,
    TOK_FUNCTION = 326,
    TOK_GENERATE = 327,
    TOK_GENVAR = 328,
    TOK_HIGHZ0 = 329,
    TOK_HIGHZ1 = 330,
    TOK_IF = 331,
    TOK_IFNONE = 332,
    TOK_INITIAL = 333,
    TOK_INOUT = 334,
    TOK_INPUT = 335,
    TOK_INTEGER = 336,
    TOK_JOIN = 337,
    TOK_LARGE = 338,
    TOK_LOCALPARAM = 339,
    TOK_MACROMODULE = 340,
    TOK_MEDIUM = 341,
    TOK_MODULE = 342,
    TOK_NAND = 343,
    TOK_NEGEDGE = 344,
    TOK_NMOS = 345,
    TOK_NOR = 346,
    TOK_NOT = 347,
    TOK_NOTIF0 = 348,
    TOK_NOTIF1 = 349,
    TOK_OR = 350,
    TOK_OUTPUT = 351,
    TOK_PARAMETER = 352,
    TOK_PMOS = 353,
    TOK_POSEDGE = 354,
    TOK_PRIMITIVE = 355,
    TOK_PULL0 = 356,
    TOK_PULL1 = 357,
    TOK_PULLDOWN = 358,
    TOK_PULLUP = 359,
    TOK_RCMOS = 360,
    TOK_REAL = 361,
    TOK_REALTIME = 362,
    TOK_REG = 363,
    TOK_RELEASE = 364,
    TOK_REPEAT = 365,
    TOK_RNMOS = 366,
    TOK_RPMOS = 367,
    TOK_RTRAN = 368,
    TOK_RTRANIF0 = 369,
    TOK_RTRANIF1 = 370,
    TOK_SCALARED = 371,
    TOK_SIGNED = 372,
    TOK_SMALL = 373,
    TOK_SPECIFY = 374,
    TOK_SPECPARAM = 375,
    TOK_STRONG0 = 376,
    TOK_STRONG1 = 377,
    TOK_SUPPLY0 = 378,
    TOK_SUPPLY1 = 379,
    TOK_TABLE = 380,
    TOK_TASK = 381,
    TOK_TIME = 382,
    TOK_TRAN = 383,
    TOK_TRANIF0 = 384,
    TOK_TRANIF1 = 385,
    TOK_TRI = 386,
    TOK_TRI0 = 387,
    TOK_TRI1 = 388,
    TOK_TRIAND = 389,
    TOK_TRIOR = 390,
    TOK_TRIREG = 391,
    TOK_UNSIGNED = 392,
    TOK_VECTORED = 393,
    TOK_WAIT = 394,
    TOK_WAND = 395,
    TOK_WEAK0 = 396,
    TOK_WEAK1 = 397,
    TOK_WHILE = 398,
    TOK_WIRE = 399,
    TOK_WOR = 400,
    TOK_XNOR = 401,
    TOK_XOR = 402,
    TOK_SETUP = 403,
    TOK_HOLD = 404,
    TOK_RECOVERY = 405,
    TOK_REMOVAL = 406,
    TOK_WIDTH = 407,
    TOK_SKEW = 408,
    TOK_VERTBARMINUSGREATER = 409,
    TOK_VERTBAREQUALGREATER = 410,
    TOK_PLUSPLUS = 411,
    TOK_MINUSMINUS = 412,
    TOK_PLUSEQUAL = 413,
    TOK_PLUSCOLON = 414,
    TOK_MINUSEQUAL = 415,
    TOK_MINUSCOLON = 416,
    TOK_ASTERICEQUAL = 417,
    TOK_SLASHEQUAL = 418,
    TOK_PERCENTEQUAL = 419,
    TOK_AMPEREQUAL = 420,
    TOK_CARETEQUAL = 421,
    TOK_VERTBAREQUAL = 422,
    TOK_LESSLESSEQUAL = 423,
    TOK_GREATERGREATEREQUAL = 424,
    TOK_LESSLESSLESSEQUAL = 425,
    TOK_GREATERGREATERGREATEREQUAL = 426,
    TOK_HASHHASH = 427,
    TOK_ACCEPT_ON = 428,
    TOK_ALIAS = 429,
    TOK_ALWAYS_COMB = 430,
    TOK_ALWAYS_FF = 431,
    TOK_ALWAYS_LATCH = 432,
    TOK_ASSERT = 433,
    TOK_ASSUME = 434,
    TOK_BEFORE = 435,
    TOK_BIND = 436,
    TOK_BINS = 437,
    TOK_BINSOF = 438,
    TOK_BIT = 439,
    TOK_BREAK = 440,
    TOK_BYTE = 441,
    TOK_CHANDLE = 442,
    TOK_CHECKER = 443,
    TOK_CLASS = 444,
    TOK_CLOCKING = 445,
    TOK_CONFIG = 446,
    TOK_CONST = 447,
    TOK_CONSTRAINT = 448,
    TOK_CONTEXT = 449,
    TOK_CONTINUE = 450,
    TOK_COVER = 451,
    TOK_COVERGROUP = 452,
    TOK_COVERPOINT = 453,
    TOK_CROSS = 454,
    TOK_DIST = 455,
    TOK_DO = 456,
    TOK_ENDCLASS = 457,
    TOK_ENDCLOCKING = 458,
    TOK_ENDCONFIG = 459,
    TOK_ENDGROUP = 460,
    TOK_ENDINTERFACE = 461,
    TOK_ENDPACKAGE = 462,
    TOK_ENDPROGRAM = 463,
    TOK_ENDPROPERTY = 464,
    TOK_ENDSEQUENCE = 465,
    TOK_ENUM = 466,
    TOK_EVENTUALLY = 467,
    TOK_EXPECT = 468,
    TOK_EXPORT = 469,
    TOK_EXTENDS = 470,
    TOK_EXTERN = 471,
    TOK_FINAL = 472,
    TOK_FIRST_MATCH = 473,
    TOK_FOREACH = 474,
    TOK_IFF = 475,
    TOK_IGNORE_BINS = 476,
    TOK_ILLEGAL_BINS = 477,
    TOK_IMPORT = 478,
    TOK_INSIDE = 479,
    TOK_INT = 480,
    TOK_INTERFACE = 481,
    TOK_INTERSECT = 482,
    TOK_JOIN_ANY = 483,
    TOK_JOIN_NONE = 484,
    TOK_LOCAL = 485,
    TOK_LOGIC = 486,
    TOK_LONGINT = 487,
    TOK_MATCHES = 488,
    TOK_MODPORT = 489,
    TOK_NEW = 490,
    TOK_NEXTTIME = 491,
    TOK_NULL = 492,
    TOK_PACKAGE = 493,
    TOK_PACKED = 494,
    TOK_PRIORITY = 495,
    TOK_PROGRAM = 496,
    TOK_PROPERTY = 497,
    TOK_PROTECTED = 498,
    TOK_PURE = 499,
    TOK_RAND = 500,
    TOK_RANDC = 501,
    TOK_RANDCASE = 502,
    TOK_RANDSEQUENCE = 503,
    TOK_REF = 504,
    TOK_RETURN = 505,
    TOK_S_ALWAYS = 506,
    TOK_S_EVENTUALLY = 507,
    TOK_S_NEXTTIME = 508,
    TOK_S_UNTIL = 509,
    TOK_S_UNTIL_WITH = 510,
    TOK_SEQUENCE = 511,
    TOK_SHORTINT = 512,
    TOK_SHORTREAL = 513,
    TOK_SOLVE = 514,
    TOK_STATIC = 515,
    TOK_STRING = 516,
    TOK_STRUCT = 517,
    TOK_SUPER = 518,
    TOK_TAGGED = 519,
    TOK_THIS = 520,
    TOK_THROUGHOUT = 521,
    TOK_TIMEPRECISION = 522,
    TOK_TIMEUNIT = 523,
    TOK_TYPE = 524,
    TOK_TYPEDEF = 525,
    TOK_UNION = 526,
    TOK_UNIQUE = 527,
    TOK_UNTIL = 528,
    TOK_UNTIL_WITH = 529,
    TOK_VAR = 530,
    TOK_VIRTUAL = 531,
    TOK_VOID = 532,
    TOK_WAIT_ORDER = 533,
    TOK_WILDCARD = 534,
    TOK_WITH = 535,
    TOK_WITHIN = 536,
    TOK_ENDOFFILE = 537,
    TOK_CHARSTR = 538,
    TOK_NUMBER = 539,
    TOK_QSTRING = 540,
    TOK_SYSIDENT = 541,
    TOK_SCANNER_ERROR = 542,
    TOK_AMPERTILDE = 543,
    TOK_ASTERICASTERIC = 544,
    LT_TOK_ELSE = 545
  };
#endif
/* Tokens.  */
#define TOK_PARSE_LANGUAGE 258
#define TOK_PARSE_EXPRESSION 259
#define TOK_PARSE_TYPE 260
#define TOK_PARENASTERIC 261
#define TOK_ASTERICPAREN 262
#define TOK_EXCLAM 263
#define TOK_TILDE 264
#define TOK_AMPER 265
#define TOK_TILDEAMPER 266
#define TOK_TILDEVERTBAR 267
#define TOK_CARET 268
#define TOK_TILDECARET 269
#define TOK_CARETTILDE 270
#define TOK_MINUSGREATER 271
#define TOK_ASTERIC 272
#define TOK_SLASH 273
#define TOK_PERCENT 274
#define TOK_EQUALEQUAL 275
#define TOK_EXCLAMEQUAL 276
#define TOK_EQUALEQUALEQUAL 277
#define TOK_EXCLAMEQUALEQUAL 278
#define TOK_AMPERAMPER 279
#define TOK_VERTBARVERTBAR 280
#define TOK_LESS 281
#define TOK_LESSEQUAL 282
#define TOK_GREATER 283
#define TOK_GREATEREQUAL 284
#define TOK_GREATERGREATER 285
#define TOK_GREATERGREATERGREATER 286
#define TOK_LESSLESS 287
#define TOK_LESSLESSLESS 288
#define TOK_PLUS 289
#define TOK_MINUS 290
#define TOK_VERTBAR 291
#define TOK_QUESTION 292
#define TOK_COLON 293
#define TOK_ALWAYS 294
#define TOK_AND 295
#define TOK_ASSIGN 296
#define TOK_AUTOMATIC 297
#define TOK_BEGIN 298
#define TOK_BUF 299
#define TOK_BUFIF0 300
#define TOK_BUFIF1 301
#define TOK_CASE 302
#define TOK_CASEX 303
#define TOK_CASEZ 304
#define TOK_CMOS 305
#define TOK_DEASSIGN 306
#define TOK_DEFAULT 307
#define TOK_DEFPARAM 308
#define TOK_DISABLE 309
#define TOK_EDGE 310
#define TOK_ELSE 311
#define TOK_END 312
#define TOK_ENDCASE 313
#define TOK_ENDFUNCTION 314
#define TOK_ENDGENERATE 315
#define TOK_ENDMODULE 316
#define TOK_ENDPRIMITIVE 317
#define TOK_ENDSPECIFY 318
#define TOK_ENDTABLE 319
#define TOK_ENDTASK 320
#define TOK_EVENT 321
#define TOK_FOR 322
#define TOK_FORCE 323
#define TOK_FOREVER 324
#define TOK_FORK 325
#define TOK_FUNCTION 326
#define TOK_GENERATE 327
#define TOK_GENVAR 328
#define TOK_HIGHZ0 329
#define TOK_HIGHZ1 330
#define TOK_IF 331
#define TOK_IFNONE 332
#define TOK_INITIAL 333
#define TOK_INOUT 334
#define TOK_INPUT 335
#define TOK_INTEGER 336
#define TOK_JOIN 337
#define TOK_LARGE 338
#define TOK_LOCALPARAM 339
#define TOK_MACROMODULE 340
#define TOK_MEDIUM 341
#define TOK_MODULE 342
#define TOK_NAND 343
#define TOK_NEGEDGE 344
#define TOK_NMOS 345
#define TOK_NOR 346
#define TOK_NOT 347
#define TOK_NOTIF0 348
#define TOK_NOTIF1 349
#define TOK_OR 350
#define TOK_OUTPUT 351
#define TOK_PARAMETER 352
#define TOK_PMOS 353
#define TOK_POSEDGE 354
#define TOK_PRIMITIVE 355
#define TOK_PULL0 356
#define TOK_PULL1 357
#define TOK_PULLDOWN 358
#define TOK_PULLUP 359
#define TOK_RCMOS 360
#define TOK_REAL 361
#define TOK_REALTIME 362
#define TOK_REG 363
#define TOK_RELEASE 364
#define TOK_REPEAT 365
#define TOK_RNMOS 366
#define TOK_RPMOS 367
#define TOK_RTRAN 368
#define TOK_RTRANIF0 369
#define TOK_RTRANIF1 370
#define TOK_SCALARED 371
#define TOK_SIGNED 372
#define TOK_SMALL 373
#define TOK_SPECIFY 374
#define TOK_SPECPARAM 375
#define TOK_STRONG0 376
#define TOK_STRONG1 377
#define TOK_SUPPLY0 378
#define TOK_SUPPLY1 379
#define TOK_TABLE 380
#define TOK_TASK 381
#define TOK_TIME 382
#define TOK_TRAN 383
#define TOK_TRANIF0 384
#define TOK_TRANIF1 385
#define TOK_TRI 386
#define TOK_TRI0 387
#define TOK_TRI1 388
#define TOK_TRIAND 389
#define TOK_TRIOR 390
#define TOK_TRIREG 391
#define TOK_UNSIGNED 392
#define TOK_VECTORED 393
#define TOK_WAIT 394
#define TOK_WAND 395
#define TOK_WEAK0 396
#define TOK_WEAK1 397
#define TOK_WHILE 398
#define TOK_WIRE 399
#define TOK_WOR 400
#define TOK_XNOR 401
#define TOK_XOR 402
#define TOK_SETUP 403
#define TOK_HOLD 404
#define TOK_RECOVERY 405
#define TOK_REMOVAL 406
#define TOK_WIDTH 407
#define TOK_SKEW 408
#define TOK_VERTBARMINUSGREATER 409
#define TOK_VERTBAREQUALGREATER 410
#define TOK_PLUSPLUS 411
#define TOK_MINUSMINUS 412
#define TOK_PLUSEQUAL 413
#define TOK_PLUSCOLON 414
#define TOK_MINUSEQUAL 415
#define TOK_MINUSCOLON 416
#define TOK_ASTERICEQUAL 417
#define TOK_SLASHEQUAL 418
#define TOK_PERCENTEQUAL 419
#define TOK_AMPEREQUAL 420
#define TOK_CARETEQUAL 421
#define TOK_VERTBAREQUAL 422
#define TOK_LESSLESSEQUAL 423
#define TOK_GREATERGREATEREQUAL 424
#define TOK_LESSLESSLESSEQUAL 425
#define TOK_GREATERGREATERGREATEREQUAL 426
#define TOK_HASHHASH 427
#define TOK_ACCEPT_ON 428
#define TOK_ALIAS 429
#define TOK_ALWAYS_COMB 430
#define TOK_ALWAYS_FF 431
#define TOK_ALWAYS_LATCH 432
#define TOK_ASSERT 433
#define TOK_ASSUME 434
#define TOK_BEFORE 435
#define TOK_BIND 436
#define TOK_BINS 437
#define TOK_BINSOF 438
#define TOK_BIT 439
#define TOK_BREAK 440
#define TOK_BYTE 441
#define TOK_CHANDLE 442
#define TOK_CHECKER 443
#define TOK_CLASS 444
#define TOK_CLOCKING 445
#define TOK_CONFIG 446
#define TOK_CONST 447
#define TOK_CONSTRAINT 448
#define TOK_CONTEXT 449
#define TOK_CONTINUE 450
#define TOK_COVER 451
#define TOK_COVERGROUP 452
#define TOK_COVERPOINT 453
#define TOK_CROSS 454
#define TOK_DIST 455
#define TOK_DO 456
#define TOK_ENDCLASS 457
#define TOK_ENDCLOCKING 458
#define TOK_ENDCONFIG 459
#define TOK_ENDGROUP 460
#define TOK_ENDINTERFACE 461
#define TOK_ENDPACKAGE 462
#define TOK_ENDPROGRAM 463
#define TOK_ENDPROPERTY 464
#define TOK_ENDSEQUENCE 465
#define TOK_ENUM 466
#define TOK_EVENTUALLY 467
#define TOK_EXPECT 468
#define TOK_EXPORT 469
#define TOK_EXTENDS 470
#define TOK_EXTERN 471
#define TOK_FINAL 472
#define TOK_FIRST_MATCH 473
#define TOK_FOREACH 474
#define TOK_IFF 475
#define TOK_IGNORE_BINS 476
#define TOK_ILLEGAL_BINS 477
#define TOK_IMPORT 478
#define TOK_INSIDE 479
#define TOK_INT 480
#define TOK_INTERFACE 481
#define TOK_INTERSECT 482
#define TOK_JOIN_ANY 483
#define TOK_JOIN_NONE 484
#define TOK_LOCAL 485
#define TOK_LOGIC 486
#define TOK_LONGINT 487
#define TOK_MATCHES 488
#define TOK_MODPORT 489
#define TOK_NEW 490
#define TOK_NEXTTIME 491
#define TOK_NULL 492
#define TOK_PACKAGE 493
#define TOK_PACKED 494
#define TOK_PRIORITY 495
#define TOK_PROGRAM 496
#define TOK_PROPERTY 497
#define TOK_PROTECTED 498
#define TOK_PURE 499
#define TOK_RAND 500
#define TOK_RANDC 501
#define TOK_RANDCASE 502
#define TOK_RANDSEQUENCE 503
#define TOK_REF 504
#define TOK_RETURN 505
#define TOK_S_ALWAYS 506
#define TOK_S_EVENTUALLY 507
#define TOK_S_NEXTTIME 508
#define TOK_S_UNTIL 509
#define TOK_S_UNTIL_WITH 510
#define TOK_SEQUENCE 511
#define TOK_SHORTINT 512
#define TOK_SHORTREAL 513
#define TOK_SOLVE 514
#define TOK_STATIC 515
#define TOK_STRING 516
#define TOK_STRUCT 517
#define TOK_SUPER 518
#define TOK_TAGGED 519
#define TOK_THIS 520
#define TOK_THROUGHOUT 521
#define TOK_TIMEPRECISION 522
#define TOK_TIMEUNIT 523
#define TOK_TYPE 524
#define TOK_TYPEDEF 525
#define TOK_UNION 526
#define TOK_UNIQUE 527
#define TOK_UNTIL 528
#define TOK_UNTIL_WITH 529
#define TOK_VAR 530
#define TOK_VIRTUAL 531
#define TOK_VOID 532
#define TOK_WAIT_ORDER 533
#define TOK_WILDCARD 534
#define TOK_WITH 535
#define TOK_WITHIN 536
#define TOK_ENDOFFILE 537
#define TOK_CHARSTR 538
#define TOK_NUMBER 539
#define TOK_QSTRING 540
#define TOK_SYSIDENT 541
#define TOK_SCANNER_ERROR 542
#define TOK_AMPERTILDE 543
#define TOK_ASTERICASTERIC 544
#define LT_TOK_ELSE 545

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yyveriloglval;

int yyverilogparse (void);

#endif /* !YY_YYVERILOG_VERILOG_Y_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 933 "verilog_y.tab.cpp" /* yacc.c:358  */

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
#define YYFINAL  48
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3458

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  304
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  266
/* YYNRULES -- Number of rules.  */
#define YYNRULES  595
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1082

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   545

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,   301,   303,     2,     2,     2,
     297,   298,     2,     2,   294,     2,   299,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   291,
       2,   300,     2,     2,   302,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   295,     2,   296,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   292,     2,   293,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   564,   564,   564,   565,   567,   571,   573,   575,   579,
     580,   581,   582,   583,   584,   585,   586,   594,   598,   605,
     609,   613,   617,   622,   627,   635,   638,   640,   642,   644,
     649,   650,   658,   662,   664,   669,   670,   671,   674,   678,
     682,   685,   694,   699,   700,   714,   715,   720,   721,   730,
     731,   739,   744,   748,   753,   759,   764,   765,   768,   772,
     775,   780,   782,   786,   787,   791,   792,   793,   797,   801,
     805,   808,   812,   813,   817,   818,   821,   824,   828,   829,
     832,   833,   836,   838,   840,   845,   854,   863,   865,   869,
     871,   875,   891,   906,   911,   912,   917,   921,   922,   925,
     927,   931,   933,   938,   951,   952,   953,   957,   965,   970,
     978,   986,   988,   992,   997,  1004,  1005,  1009,  1010,  1011,
    1015,  1020,  1025,  1027,  1031,  1039,  1040,  1049,  1050,  1054,
    1055,  1056,  1068,  1074,  1075,  1080,  1081,  1082,  1083,  1084,
    1088,  1089,  1093,  1095,  1099,  1102,  1108,  1109,  1113,  1114,
    1115,  1119,  1132,  1135,  1140,  1142,  1147,  1148,  1149,  1153,
    1155,  1156,  1157,  1159,  1160,  1161,  1162,  1163,  1164,  1168,
    1169,  1170,  1171,  1173,  1174,  1175,  1179,  1180,  1181,  1184,
    1187,  1191,  1196,  1198,  1202,  1207,  1209,  1214,  1216,  1220,
    1228,  1231,  1232,  1236,  1244,  1252,  1257,  1265,  1272,  1282,
    1283,  1287,  1288,  1293,  1294,  1298,  1299,  1304,  1305,  1310,
    1312,  1317,  1325,  1327,  1331,  1333,  1338,  1345,  1354,  1355,
    1358,  1361,  1366,  1371,  1376,  1378,  1383,  1388,  1397,  1398,
    1399,  1402,  1403,  1404,  1405,  1406,  1407,  1408,  1409,  1410,
    1411,  1421,  1423,  1427,  1434,  1439,  1441,  1445,  1450,  1451,
    1454,  1455,  1456,  1457,  1461,  1465,  1481,  1482,  1487,  1488,
    1490,  1492,  1494,  1499,  1501,  1506,  1507,  1511,  1525,  1526,
    1531,  1532,  1533,  1534,  1538,  1539,  1540,  1542,  1544,  1550,
    1551,  1558,  1563,  1565,  1569,  1574,  1578,  1581,  1584,  1588,
    1590,  1599,  1601,  1603,  1605,  1607,  1609,  1611,  1613,  1615,
    1620,  1621,  1625,  1626,  1627,  1628,  1632,  1633,  1634,  1635,
    1639,  1640,  1641,  1642,  1643,  1644,  1648,  1649,  1653,  1654,
    1655,  1656,  1660,  1661,  1665,  1667,  1672,  1681,  1682,  1685,
    1692,  1701,  1702,  1707,  1708,  1712,  1714,  1719,  1721,  1726,
    1729,  1736,  1739,  1741,  1746,  1750,  1752,  1757,  1761,  1762,
    1766,  1768,  1773,  1777,  1779,  1784,  1795,  1800,  1802,  1806,
    1810,  1812,  1816,  1824,  1829,  1830,  1831,  1832,  1833,  1834,
    1835,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,
    1845,  1846,  1847,  1848,  1849,  1853,  1858,  1859,  1863,  1870,
    1874,  1882,  1883,  1886,  1889,  1892,  1894,  1902,  1907,  1910,
    1916,  1923,  1925,  1930,  1931,  1937,  1938,  1945,  1946,  1953,
    1957,  1959,  1961,  1966,  1968,  1970,  1973,  1979,  1981,  1985,
    1990,  1991,  1992,  1993,  1994,  1995,  1996,  1997,  1998,  1999,
    2000,  2001,  2002,  2006,  2008,  2013,  2018,  2019,  2020,  2024,
    2026,  2028,  2033,  2034,  2035,  2040,  2044,  2049,  2051,  2053,
    2057,  2061,  2068,  2073,  2075,  2077,  2082,  2084,  2086,  2091,
    2093,  2098,  2101,  2104,  2110,  2112,  2117,  2119,  2124,  2132,
    2134,  2136,  2138,  2142,  2145,  2149,  2150,  2154,  2156,  2163,
    2181,  2182,  2186,  2189,  2199,  2202,  2203,  2205,  2207,  2223,
    2224,  2228,  2230,  2234,  2237,  2238,  2244,  2245,  2249,  2251,
    2256,  2257,  2259,  2260,  2262,  2264,  2266,  2268,  2270,  2272,
    2274,  2276,  2278,  2280,  2282,  2284,  2286,  2288,  2290,  2292,
    2294,  2296,  2298,  2300,  2302,  2304,  2306,  2308,  2313,  2315,
    2321,  2322,  2323,  2324,  2325,  2326,  2327,  2329,  2330,  2331,
    2332,  2333,  2334,  2335,  2336,  2337,  2338,  2342,  2343,  2345,
    2347,  2349,  2354,  2356,  2358,  2363,  2364,  2365,  2366,  2367,
    2368,  2369,  2370,  2371,  2375,  2377,  2379,  2381,  2385,  2386,
    2387,  2389,  2391,  2392,  2393,  2394,  2396,  2400,  2403,  2407,
    2412,  2414,  2418,  2428,  2435,  2439,  2440,  2448,  2453,  2466,
    2479,  2581,  2582,  2586,  2590,  2593
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_PARSE_LANGUAGE",
  "TOK_PARSE_EXPRESSION", "TOK_PARSE_TYPE", "\"(*\"", "\"*)\"", "\"!\"",
  "\"~\"", "\"&\"", "\"~&\"", "\"~|\"", "\"^\"", "\"~^\"", "\"^~\"",
  "\"->\"", "\"*\"", "\"/\"", "\"%\"", "\"==\"", "\"!=\"", "\"===\"",
  "\"!==\"", "\"&&\"", "\"||\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"",
  "\">>\"", "\">>>\"", "\"<<\"", "\"<<<\"", "\"+\"", "\"-\"", "\"|\"",
  "\"?\"", "\":\"", "\"always\"", "\"and\"", "\"assign\"", "\"automatic\"",
  "\"begin\"", "\"buf\"", "\"bufif0\"", "\"bufif1\"", "\"case\"",
  "\"casex\"", "\"casez\"", "\"cmos\"", "\"deassign\"", "\"default\"",
  "\"defparam\"", "\"disable\"", "\"edge\"", "\"else\"", "\"end\"",
  "\"endcase\"", "\"endfunction\"", "\"endgenerate\"", "\"endmodule\"",
  "\"endprimitive\"", "\"endspecify\"", "\"endtable\"", "\"endtask\"",
  "\"event\"", "\"for\"", "\"force\"", "\"forever\"", "\"fork\"",
  "\"function\"", "\"generate\"", "\"genvar\"", "\"highz0\"", "\"highz1\"",
  "\"if\"", "\"ifnone\"", "\"initial\"", "\"inout\"", "\"input\"",
  "\"integer\"", "\"join\"", "\"large\"", "\"localparam\"",
  "\"macromodule\"", "\"medium\"", "\"module\"", "\"nand\"", "\"negedge\"",
  "\"nmos\"", "\"nor\"", "\"not\"", "\"notif0\"", "\"notif1\"", "\"or\"",
  "\"output\"", "\"parameter\"", "\"pmos\"", "\"posedge\"",
  "\"primitive\"", "\"pull0\"", "\"pull1\"", "\"pulldown\"", "\"pullup\"",
  "\"rcmos\"", "\"real\"", "\"realtime\"", "\"reg\"", "\"release\"",
  "\"repeat\"", "\"rnmos\"", "\"rpmos\"", "\"rtran\"", "\"rtranif0\"",
  "\"rtranif1\"", "\"scalared\"", "\"signed\"", "\"small\"", "\"specify\"",
  "\"specparam\"", "\"strong0\"", "\"strong1\"", "\"supply0\"",
  "\"supply1\"", "\"table\"", "\"task\"", "\"time\"", "\"tran\"",
  "\"tranif0\"", "\"tranif1\"", "\"tri\"", "\"tri0\"", "\"tri1\"",
  "\"triand\"", "\"trior\"", "\"trireg\"", "\"unsigned\"", "\"vectored\"",
  "\"wait\"", "\"wand\"", "\"weak0\"", "\"weak1\"", "\"while\"",
  "\"wire\"", "\"wor\"", "\"xnor\"", "\"xor\"", "\"setup\"", "\"hold\"",
  "\"recovery\"", "\"removal\"", "\"width\"", "\"skew\"", "\"|->\"",
  "\"|=>\"", "\"++\"", "\"--\"", "\"+=\"", "\"+:\"", "\"-=\"", "\"-:\"",
  "\"*=\"", "\"/=\"", "\"%=\"", "\"&=\"", "\"^=\"", "\"|=\"", "\"<<=\"",
  "\">>=\"", "\"<<<=\"", "\">>>=\"", "\"##\"", "\"accept_on\"",
  "\"alias\"", "\"always_comb\"", "\"always_ff\"", "\"always_latch\"",
  "\"assert\"", "\"assume\"", "\"before\"", "\"bind\"", "\"bins\"",
  "\"binsof\"", "\"bit\"", "\"break\"", "\"byte\"", "\"chandle\"",
  "\"checker\"", "\"class\"", "\"clocking\"", "\"config\"", "\"const\"",
  "\"constraint\"", "\"context\"", "\"continue\"", "\"cover\"",
  "\"covergroup\"", "\"coverpoint\"", "\"cross\"", "\"dist\"", "\"do\"",
  "\"endclass\"", "\"endclocking\"", "\"endconfig\"", "\"endgroup\"",
  "\"endinterface\"", "\"endpackage\"", "\"endprogram\"",
  "\"endproperty\"", "\"endsequence\"", "\"enum\"", "\"eventually\"",
  "\"expect\"", "\"export\"", "\"extends\"", "\"extern\"", "\"final\"",
  "\"first_match\"", "\"foreach\"", "\"iff\"", "\"ignore_bins\"",
  "\"illegal_bins\"", "\"import\"", "\"inside\"", "\"int\"",
  "\"interface\"", "\"intersect\"", "\"join_any\"", "\"join_none\"",
  "\"local\"", "\"logic\"", "\"longint\"", "\"matches\"", "\"modport\"",
  "\"new\"", "\"nexttime\"", "\"null\"", "\"package\"", "\"packed\"",
  "\"priority\"", "\"program\"", "\"property\"", "\"protected\"",
  "\"pure\"", "\"rand\"", "\"randc\"", "\"randcase\"", "\"randsequence\"",
  "\"ref\"", "\"return\"", "\"s_always\"", "\"s_eventually\"",
  "\"s_nexttime\"", "\"s_until\"", "\"s_until_with\"", "\"sequence\"",
  "\"shortint\"", "\"shortreal\"", "\"solve\"", "\"static\"", "\"string\"",
  "\"struct\"", "\"super\"", "\"tagged\"", "\"this\"", "\"throughout\"",
  "\"timeprecision\"", "\"timeunit\"", "\"type\"", "\"typedef\"",
  "\"union\"", "\"unique\"", "\"until\"", "\"until_with\"", "\"var\"",
  "\"virtual\"", "\"void\"", "\"wait_order\"", "\"wildcard\"", "\"with\"",
  "\"within\"", "TOK_ENDOFFILE", "TOK_CHARSTR", "TOK_NUMBER",
  "TOK_QSTRING", "TOK_SYSIDENT", "TOK_SCANNER_ERROR", "TOK_AMPERTILDE",
  "TOK_ASTERICASTERIC", "LT_TOK_ELSE", "';'", "'{'", "'}'", "','", "'['",
  "']'", "'('", "')'", "'.'", "'='", "'#'", "'@'", "'$'", "$accept",
  "grammar", "$@1", "source_text", "description_brace", "description",
  "program_declaration", "package_declaration", "config_declaration",
  "interface_declaration", "bind_directive", "type_declaration",
  "data_type", "enum_name_declaration", "enum_name_declaration_list",
  "integer_vector_type", "integer_atom_type", "class_type",
  "struct_union_member_list", "enum_base_type_opt", "interface_identifier",
  "interface_opt", "packed_opt", "packed_dimension_brace",
  "unpacked_dimension_brace", "packed_dimension", "unpacked_dimension",
  "unsized_dimension", "struct_union", "type_identifier",
  "udp_declaration", "udp_identifier", "udp_port_list",
  "udp_port_declaration_brace", "udp_port_declaration",
  "udp_output_declaration", "udp_input_declaration", "udp_reg_declaration",
  "udp_declaration_port_list", "udp_input_declaration_brace",
  "port_identifier_brace", "udp_body", "udp_initial_statement_opt",
  "table_entry_brace", "table_entry", "input_list",
  "output_or_level_symbol", "next_state", "module_declaration",
  "module_identifier_opt", "module_nonansi_header", "module_ansi_header",
  "list_of_port_declarations", "list_of_ports_opt",
  "module_parameter_port_list_opt", "module_keyword", "module_identifier",
  "list_of_ports", "port_declaration_brace", "module_port_declaration",
  "module_port_input_declaration", "module_port_output_declaration",
  "module_port_inout_declaration", "port_brace", "port",
  "port_expression_opt", "port_reference", "bit_select", "part_select",
  "indexed_part_select", "port_identifier", "module_item_brace",
  "module_item", "non_port_module_item", "generated_instantiation",
  "generate_item_brace", "generate_item", "generate_item_or_null",
  "generate_conditional_statement", "constant_expression",
  "generate_case_statement", "genvar_case_item_brace", "genvar_case_item",
  "generate_loop_statement", "generate_block_identifier",
  "genvar_assignment", "generate_block", "port_declaration",
  "module_or_generate_item", "module_or_generate_item_declaration",
  "package_or_generate_item_declaration",
  "concurrent_assertion_item_declaration", "property_declaration",
  "genvar_declaration", "list_of_genvar_identifiers", "genvar_identifier",
  "parameter_declaration", "list_of_param_assign", "param_assign",
  "param_identifier", "data_type_or_implicit", "implicit_data_type",
  "input_declaration", "output_declaration", "inout_declaration",
  "port_type", "net_type_or_trireg_opt", "net_type_or_trireg",
  "signing_opt", "signing", "automatic_opt", "list_of_port_identifiers",
  "reg_declaration", "decl_register_identifier",
  "list_of_register_identifiers", "register_name", "register_identifier",
  "range_opt", "range", "integer_declaration", "realtime_declaration",
  "real_declaration", "list_of_real_identifiers", "net_declaration",
  "vectored_scalared_opt", "net_type", "list_of_net_names", "net_name",
  "net_identifier", "list_of_net_decl_assignments", "net_decl_assignment",
  "delay3_opt", "delay3", "delay_value", "function_declaration",
  "range_or_type_opt", "range_or_type", "function_item_declaration_brace",
  "function_item_declaration", "task_declaration",
  "task_item_declaration_brace", "task_item_declaration",
  "block_item_declaration", "attribute_instance_brace",
  "attribute_instance", "attr_spec_list", "attr_spec", "attr_name",
  "block_reg_declaration", "event_declaration",
  "list_of_event_identifiers", "gate_instantiation", "cmos_switchtype",
  "enable_gatetype", "mos_switchtype", "n_input_gatetype",
  "n_output_gatetype", "pass_en_switchtype", "pass_switchtype",
  "gate_instance_brace", "gate_instance", "name_of_gate_instance_opt",
  "name_of_gate_instance", "module_instantiation",
  "param_value_assign_opt", "list_of_parameter_assignments",
  "ordered_parameter_assignment_brace", "named_parameter_assignment_brace",
  "ordered_parameter_assignment", "named_parameter_assignment",
  "parameter_identifier", "module_instance_brace", "module_instance",
  "name_of_instance", "list_of_module_connections_opt",
  "list_of_module_connections", "ordered_port_connection_brace",
  "ordered_port_connection", "named_port_connection_brace",
  "named_port_connection", "continuous_assign", "list_of_net_assignments",
  "net_assignment", "variable_assignment", "initial_construct",
  "always_construct", "statement", "statement_item",
  "subroutine_call_statement", "subroutine_call", "tf_call",
  "system_tf_call", "statement_or_null", "event_trigger",
  "hierarchical_event_identifier", "par_block", "disable_statement",
  "assert_property_statement", "property_identifier",
  "cover_property_statement", "action_block",
  "concurrent_assert_statement", "concurrent_cover_statement",
  "immediate_assert_statement", "hierarchical_task_or_block_identifier",
  "hierarchical_tf_identifier", "wait_statement",
  "procedural_continuous_assignments", "blocking_assignment",
  "operator_assignment", "assignment_operator", "nonblocking_assignment",
  "procedural_timing_control_statement", "procedural_timing_control",
  "cycle_delay", "delay_or_event_control", "delay_control",
  "event_control", "event_identifier", "ored_event_expression",
  "event_expression", "conditional_statement", "case_statement",
  "case_item_brace", "case_item", "loop_statement", "for_initialization",
  "for_step", "for_step_assignment", "seq_block", "block_identifier",
  "statement_or_null_brace", "task_identifier", "system_task_name",
  "net_lvalue", "variable_lvalue", "indexed_variable_lvalue",
  "hierarchical_variable_identifier", "variable_identifier",
  "const_expression", "mintypmax_expression", "expression_opt",
  "expression_brace", "expression", "property_expr", "sequence_expr",
  "cycle_delay_range", "unary_operator", "inc_or_dec_expression",
  "primary", "primary_literal", "number", "concatenation", "replication",
  "function_subroutine_call", "function_identifier", "unsigned_number",
  "hierarchical_identifier", "identifier", "pulldown_strength_opt",
  "pullup_strength_opt", "drive_strength_opt",
  "list_of_specparam_assignments", "specparam_declaration",
  "specparam_assignment", "specparam_identifier", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,    59,   123,   125,    44,    91,    93,    40,    41,    46,
      61,    35,    64,    36
};
# endif

#define YYPACT_NINF -816

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-816)))

#define YYTABLE_NINF -489

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     506,  -816,  2156,   -15,   101,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  2156,  2156,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  2156,  2156,  -816,  -816,  -816,  -190,
    -152,  -816,    45,  -816,  3415,  -816,  -816,  -816,  -816,  -816,
      56,  -816,  -816,  -816,  -146,  -816,   637,  -816,  -816,  -816,
     158,   606,   606,    61,    61,   243,  2775,  -129,  3255,  2156,
    2156,    79,  2156,  -816,    81,    88,  2156,  2156,  2156,  2156,
    2156,  2156,  2156,  2156,  2156,  2156,  2156,  2156,  2156,  2156,
    2156,  2156,  2156,  2156,  2156,  2156,  2156,  2156,  2156,  2156,
      42,  -109,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,   -45,  -816,   102,   102,  -816,
     -55,   -85,  -816,  -816,  -816,    58,  -816,    12,    75,   109,
     870,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,   107,  -109,  2156,  -816,  -816,    51,  -816,    25,  -816,
    -816,  2156,    70,    97,  -816,  2156,  -183,  3415,   164,  -816,
    -816,   106,  2697,  1442,  1278,  1278,  -816,  -816,  -816,  1138,
    1138,  1138,  1138,  2189,  2893,   627,   627,   627,   627,   456,
     456,   456,   456,   606,   606,  3150,  3348,    51,  -816,  -816,
    -816,    59,  -816,  -816,  -816,  -816,  -816,   102,  -816,  -816,
      67,   110,  -816,    64,  -816,  -816,  -816,    65,  -816,  -816,
    -816,   133,   385,   405,  -816,  -816,   189,  -816,  -816,   210,
      29,  -816,   204,  -816,  -816,  -816,  3415,  -816,  -816,  3386,
    -816,  -816,  2156,  2156,  2156,  -816,  2156,  -816,  -816,   236,
    -816,    64,   232,  -816,   -85,  2156,    64,  2025,  -816,  -816,
    -816,   257,   210,  -816,  -816,   263,  -816,  2891,   210,  -816,
     292,  -816,  -816,  -816,  -109,  2156,  2156,   264,  3415,   269,
     271,  3415,  -816,  -816,   333,  -816,  -816,  3415,  -816,   541,
    -816,  -816,  -816,  -816,  -816,  -816,   283,  -816,  -816,  -816,
    -816,   316,   549,  -816,   321,  -816,   590,   590,   -85,   102,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  3126,   102,  -816,
    -816,  -816,  -816,   -85,   -85,  -816,  -816,  -816,  -816,  -816,
     320,  -816,  -816,  -109,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -137,   328,
     375,   328,   581,   329,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,   283,  -816,   283,  -816,  -816,
     283,   338,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
     601,  -816,  -816,   358,   350,  -816,  -816,  3415,  3415,  -816,
    -816,  -816,  -816,   236,   356,  2156,  1474,  -816,   -14,   173,
    -816,  -816,   114,  -816,  -816,   102,   404,  -816,   136,  -816,
    -816,   358,   102,  -816,   358,   149,   247,  -816,  -816,   358,
     358,   251,   338,   338,  -816,   253,   255,  2156,  -816,   367,
    -816,   354,    25,   355,  -816,   618,   632,   368,   462,   377,
     392,    77,   338,   283,   338,   283,   283,   338,  -816,   261,
    -816,   320,  -816,   215,  -816,   378,   387,   384,   390,    60,
     234,   408,   410,  -816,  -816,  -816,   406,   316,   173,   666,
     414,   415,   420,   173,  -109,   423,   173,  -816,   689,   431,
     173,   435,   436,   440,    86,   140,    24,    36,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,   447,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,   449,   450,  -816,   451,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,   132,   455,   463,  -816,
    -816,   262,  -816,   452,  -816,  -816,   316,    82,   715,   458,
    -816,   459,   460,  -816,  -816,  -816,  -816,  -816,  -816,  3012,
    -816,   321,  -816,   464,  -816,   464,  -816,  -816,   102,    -6,
     464,   464,  -816,   268,   270,  -816,   -85,  -816,   722,  -816,
     275,  -816,   461,  -185,   471,  1499,  2156,  2156,  2156,  -816,
     216,  -816,   280,  -816,   467,  -816,  -816,   637,   282,   338,
     287,   338,   338,   289,  -816,   392,   468,  -816,  -816,   475,
    -816,   476,   358,   358,   358,   198,  -816,   200,  -816,  -816,
    -816,   473,   308,  -816,  -816,    64,  -816,   478,  -816,  -816,
    -816,   487,   714,  2156,  2156,  2156,  -816,   482,  -816,   173,
    -816,  -816,   487,   693,  2156,  -816,  2156,  2156,  2156,  2156,
    -816,  -816,  2156,  2156,  -816,   479,  -816,  1624,  -816,  -816,
    -816,  -816,  -816,  1310,  -816,  -816,  1389,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   -21,
    2156,  -816,   222,  -816,   173,  2156,  -816,  -816,  -816,  -816,
    -816,  -816,  -109,  -816,   493,   319,  2156,   321,  2156,  -816,
     483,   358,    64,  -816,  -816,   480,  -816,  -816,  -816,  -816,
     367,  2156,  -816,  1499,  1499,    94,  1499,   485,  1499,  1499,
    1499,  1499,  1499,  1499,  1499,  1499,   490,  3192,    62,  -816,
    1653,  2803,  2831,   771,   496,   511,   516,   517,  -816,  -816,
    3415,  -816,   392,  1551,   283,  -816,   294,  -816,   304,   306,
    -816,  -816,  1551,  -816,  -816,   514,    98,  -816,   520,  -816,
    -816,   518,   358,  -816,  -185,  -816,  2156,  -816,  -816,   590,
     590,  3126,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    2338,  2387,  2437,  -816,  -816,   525,   527,  -816,  -816,  2465,
    2493,  2521,  2549,  2577,  2620,   519,  -816,   522,  2156,  2156,
     -23,  -816,  3415,  -816,   526,  2156,  -816,  -816,  3415,  2156,
    3415,   463,  -816,  -816,  3415,   354,    25,  -816,  -816,  -816,
     524,   537,   533,   547,  2156,  -816,  -816,  2156,  -816,  -816,
    -816,  -816,  -816,   463,  -816,  -816,  1653,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,  -816,  1499,  1653,  1653,  1499,  1499,
    1499,  1499,  -816,  -816,  -816,  -816,  -816,  -816,   538,  -816,
    2156,   550,  -816,   358,   548,  -816,   557,  -816,   558,  -816,
    -816,  3415,   570,  -816,  -816,  -816,   556,   730,  -816,   566,
     568,   572,   301,  -816,   358,   799,   739,   358,   358,  -816,
    -816,  -816,   358,   358,   358,   358,   808,  2057,  2057,  2057,
    2156,   784,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    3415,  3415,  1690,  1690,  -816,  2156,  3415,  3415,   241,   576,
     438,  2102,  2156,  2156,   130,   832,  2747,   483,  -816,  -816,
    -816,   982,   806,   834,   577,    66,  -816,  -816,  -816,   836,
     246,   246,   818,  -816,  -816,  2156,  -816,  -816,   585,  -816,
    2156,   579,  -816,   311,  -816,   593,   318,  -816,  -816,  -816,
     833,  -816,  -816,  -816,   611,   464,  -816,  -816,  -816,   598,
    -816,  -816,  -816,  -816,  -816,   859,  1804,  -816,    16,  1865,
    1943,  2859,  -816,   844,  -816,  -816,  -816,  -816,  -816,  -816,
    2669,   463,  -816,   822,  -816,   129,  1996,  -816,    17,   612,
    -816,  -816,  -816,   848,  2156,  -816,  -816,   614,   615,   616,
     182,  -816,   201,   219,  -816,  -104,  -816,  -816,  -816,   613,
    2156,  -816,  -816,  -816,   570,  2156,    64,  -816,   570,  -816,
    -816,  -816,   845,  -816,   872,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,   -60,  -816,   610,   617,   623,   822,  -816,
    -816,   379,   130,  -816,  -816,  -816,   130,   321,   130,   625,
    -816,  -816,  -816,   626,   628,  -816,  -816,   629,  -816,  -816,
    3415,   593,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   630,
    -816,   721,  -816,  -816,  -816,  -816,  -816,  -816,  1146,   864,
    -816,  -816,  -816,  -816,  -816,   631,  -816,  -816,  -816,  -816,
    -816,    18,  -816,  -816,  -816,   882,  -816,  -816,  -816,  -816,
     635,  -816
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     2,     0,     0,     0,     7,   556,   555,   557,   558,
     560,   561,   563,   562,     0,     0,   559,   279,   279,   576,
     587,   584,   529,   483,     0,     0,   582,   386,   387,     0,
     389,   279,   569,   489,     4,   279,   502,   500,   568,   577,
     572,   573,   574,   578,   491,   585,   203,     5,     1,     3,
     279,   505,   506,     0,     0,     0,   498,     0,   494,     0,
       0,     0,     0,   490,   570,   571,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    37,   205,   206,    35,    28,    39,    41,
      38,    36,    27,    56,    57,    43,   191,   203,   203,    30,
      45,     0,   192,    47,   204,     0,   279,     0,     0,     0,
       0,     8,    12,    13,    15,    11,    16,    10,     9,   125,
     125,     0,     0,     0,   280,   564,   485,   488,   491,   565,
     579,     0,     0,     0,   575,     0,     0,   498,     0,   566,
     567,     0,   493,   520,   522,   523,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   526,
     527,   524,   525,   503,   504,   521,     0,   569,   501,   572,
     586,     0,    44,    42,    47,    24,    46,   203,   217,   214,
       0,   213,    47,   193,    19,    87,    88,     0,    20,    18,
      17,     0,   279,   279,    98,    97,     0,    21,    14,     0,
       0,   282,   285,   286,   486,   487,   499,   580,   581,     0,
     388,   390,     0,     0,     0,   120,     0,   570,   571,     0,
      29,    23,     0,   211,     0,     0,   216,     0,    48,    52,
      58,     0,    89,   126,   128,     0,   129,     0,    89,    61,
       0,    99,    96,   281,     0,     0,     0,     0,   493,     0,
       0,   528,    32,    33,     0,    40,   215,   212,    55,     0,
      22,    85,    90,   127,   279,   310,   248,   316,   302,   303,
     300,     0,   207,   133,     0,   279,   199,   199,     0,   203,
     311,   306,   312,   317,   304,   305,   313,   199,   203,   307,
     588,   589,   301,     0,     0,   308,   309,   318,   319,   320,
     218,   234,   238,     0,   321,   322,   323,   232,   237,   233,
     236,   240,   202,   235,   231,   239,   314,   315,     0,     0,
       0,     0,    99,   331,   130,   159,   169,   168,   179,   175,
     160,   157,   158,   156,   590,   170,   171,   173,   172,   176,
     201,   178,   177,   174,   162,   248,   590,   248,   590,   590,
     248,   327,   163,   161,   164,   165,   405,   407,   166,   167,
       0,   131,    86,   279,    94,   283,   284,   144,   495,   121,
     122,   123,    26,     0,     0,     0,     0,   362,     0,     0,
     249,   452,     0,   289,   208,   203,   279,   184,     0,   182,
     361,     0,   203,   200,     0,     0,     0,   187,    47,     0,
       0,     0,   327,   327,   224,     0,     0,     0,   220,     0,
     219,    94,   482,     0,   401,     0,     0,     0,     0,     0,
     345,   228,   327,   248,   327,   248,   248,   327,   329,     0,
     324,   218,   328,     0,   124,     0,     0,     0,     0,     0,
     279,     0,     0,    95,    34,    47,     0,     0,     0,   480,
       0,     0,     0,     0,     0,     0,     0,   279,   480,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   287,   368,
     366,   365,   367,   363,   375,     0,   377,   379,   376,   364,
     372,   384,   383,     0,     0,   418,     0,   380,   279,   438,
     436,   437,   373,   371,   378,   382,   279,     0,     0,   250,
     254,     0,   357,     0,   484,   288,     0,   256,   133,     0,
     132,     0,     0,   134,   135,   136,   137,   138,   139,     0,
     181,     0,    49,   197,    47,   194,   221,   186,   203,     0,
     196,   195,   185,     0,     0,   223,     0,   222,     0,   595,
       0,   591,     0,   115,     0,     0,     0,     0,     0,   180,
       0,   346,     0,   342,     0,   230,   229,   203,     0,   327,
       0,   327,   327,     0,   297,   345,     0,   406,   408,     0,
     279,     0,     0,     0,     0,     0,   101,     0,   111,   113,
     116,   117,     0,    92,    91,    25,    51,     0,   394,   360,
     413,     0,   279,     0,     0,     0,   414,     0,   410,     0,
     415,   469,     0,   279,     0,   416,     0,     0,     0,     0,
     439,   440,     0,     0,   445,     0,   449,     0,   447,   385,
     381,   369,   370,     0,   391,   435,     0,   421,   422,   423,
     424,   425,   426,   428,   427,   429,   430,   431,   432,   420,
       0,   374,     0,   356,     0,     0,   290,   259,   260,   261,
     262,   258,     0,   257,     0,   279,     0,     0,     0,   183,
     209,     0,   198,   188,   190,     0,   298,   299,   225,   593,
       0,     0,   268,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   547,     0,   530,
       0,     0,     0,     0,     0,     0,   333,   334,   335,   337,
     339,   330,   345,   496,   248,   291,     0,   293,     0,     0,
     296,   325,   496,   279,    72,   279,     0,    77,    62,    74,
      68,     0,   279,    93,   115,   100,     0,   118,   119,   199,
     199,   199,   105,   106,   104,   393,   479,   480,   477,   481,
       0,     0,     0,   397,   473,     0,     0,   480,   395,     0,
       0,     0,     0,     0,     0,     0,   451,     0,     0,     0,
       0,   453,   456,   392,     0,     0,   442,   443,   433,     0,
     419,     0,   251,   358,   359,    94,   583,   152,   133,   154,
       0,     0,     0,     0,     0,    50,    49,     0,   592,   594,
     279,   537,   531,     0,   552,   538,     0,   539,   540,   541,
     542,   543,   544,   545,   546,     0,     0,     0,     0,     0,
       0,     0,   279,   548,   399,   400,   279,   341,     0,   332,
       0,     0,   343,     0,     0,   347,   348,   350,   349,   353,
     352,   497,     0,   292,   294,   295,     0,   279,    63,     0,
       0,     0,     0,    73,     0,     0,     0,     0,   115,   102,
     103,   112,     0,     0,     0,     0,   279,     0,     0,     0,
       0,   279,   279,   279,   279,   279,   441,   279,   446,   450,
     458,   457,     0,     0,   448,     0,   434,   417,     0,     0,
     279,     0,     0,     0,   279,     0,   493,   210,   189,   269,
     270,     0,     0,     0,     0,     0,   551,   549,   533,   532,
     534,   535,   403,   398,   402,   496,   336,   338,     0,   344,
     496,     0,   244,     0,   241,    47,     0,   245,   326,    64,
       0,    65,    66,    67,     0,    69,    60,    82,    75,     0,
     110,   107,   109,   108,   478,   279,     0,   464,     0,     0,
       0,     0,   396,   459,   470,   412,   471,   409,   454,   455,
       0,     0,   252,   279,   155,   279,     0,   146,     0,     0,
     153,   141,   140,   142,     0,    54,   277,     0,     0,     0,
     276,   278,   274,   275,   267,     0,   550,   536,   279,     0,
     496,   351,   354,   226,     0,     0,   243,   227,     0,    59,
     492,    70,    82,    78,     0,   114,   279,   468,   461,   465,
     279,   462,   463,     0,   279,     0,     0,     0,   279,   263,
     265,     0,   279,   150,   145,   147,   279,     0,   279,     0,
     271,   272,   273,     0,     0,   404,   340,     0,   242,    47,
     247,     0,   246,    76,    79,    83,   467,   466,   475,     0,
     474,   279,   476,   460,   444,   253,   266,   264,     0,     0,
     276,   274,   275,   149,   148,     0,   143,    53,   554,   553,
     355,     0,   279,   420,   255,     0,    84,    80,   472,   151,
       0,    81
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -110,   551,  -816,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,   -37,   134,  -816,  -816,  -816,  -816,  -816,
    -816,  -816,  -816,  -816,    84,   564,  -503,  -816,  -816,  -816,
    -816,    91,  -816,  -816,   -63,  -816,  -816,  -816,  -816,   692,
     828,   829,  -816,  -393,  -816,  -816,  -164,  -816,  -816,   217,
    -816,  -816,  -816,  -816,   213,    92,  -816,   360,     5,    26,
    -114,   823,  -816,  -816,  -816,  -472,  -372,  -567,  -816,  -580,
    -816,  -816,   -12,  -816,  -816,   -75,  -120,  -816,   426,  -816,
    -816,  -816,  -816,  -816,  -816,  -227,  -187,   658,   419,  -816,
     391,  -816,  -238,    63,    72,  -262,  -816,  -257,   -27,  -816,
    -816,  -366,    14,  -155,   671,  -816,  -816,   534,   443,  -379,
    -186,  -816,   657,  -174,  -816,  -816,  -816,   -20,  -676,  -816,
     -19,  -265,  -816,  -449,  -816,  -816,  -816,  -816,   -38,  -816,
    -816,  -816,   177,   -17,  -816,  -816,   728,  -816,  -810,  -378,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   138,
    -816,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   153,   154,
    -816,  -816,  -512,  -816,   265,  -816,  -816,    69,  -816,    71,
    -816,  -816,  -339,   528,  -816,  -816,  -259,  -816,  -816,  -370,
    -816,  -816,  -420,  -816,  -816,  -816,  -816,  -200,   -89,  -179,
    -723,  -816,  -816,  -816,  -816,  -816,  -816,  -816,   381,   -29,
    -816,  -816,  -816,  -816,  -816,   337,  -403,  -380,  -267,  -816,
    -249,  -816,  -816,  -232,  -443,  -816,  -816,  -816,  -816,  -816,
    -198,  -410,   529,  -816,  -816,   -32,   -41,  -816,  -816,   -58,
    -539,  -815,    10,    50,   148,  -486,   298,  -816,  -375,   907,
    -816,  -451,   -51,   946,  -816,  -816,  -368,   -22,   -50,  -816,
    -816,   171,  -816,  -816,   323,  -816
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    49,    50,   121,   122,   123,   124,   125,
     208,   126,   106,   263,   264,   107,   108,   109,   384,   181,
     230,   183,   187,   996,   670,   238,   795,   239,   110,   241,
     127,   250,   445,   847,   848,   849,   850,   851,   447,   725,
     728,   855,   856,  1002,  1003,  1004,  1071,  1080,   128,   271,
     129,   130,   451,   452,   374,   209,   272,   453,   585,   586,
     742,   743,   744,   587,   588,   589,   590,    63,   418,    65,
     532,   202,   243,   244,   334,   396,   972,   973,   524,   376,
     525,   966,   967,   526,   788,   791,   527,   245,   528,   335,
     336,   337,   338,   339,   398,   792,   976,   406,   407,   675,
     111,   112,  1017,   342,   343,   401,   402,   344,   408,   114,
     395,   533,   478,   189,   190,   191,   192,   419,   420,   346,
     981,   348,   415,   480,   567,   350,   923,   924,   925,   926,
     927,   389,   390,   509,   351,   662,   663,  1018,  1019,   352,
     800,   899,  1020,   633,   134,   210,   211,   212,   481,   353,
     392,   354,   355,   356,   357,   358,   359,   360,   361,   439,
     440,   441,   442,   362,   430,   705,   706,   707,   708,   709,
     828,   562,   563,   564,   834,   835,   836,   837,   838,   839,
     363,   511,   599,   600,   364,   365,   634,   483,   484,    26,
      27,    28,   749,   486,   597,   487,   488,   489,   425,   490,
     913,   368,   369,   491,   607,    29,   492,   493,   494,   495,
     650,   496,   497,   498,   499,   775,   500,   696,   393,   770,
     771,   502,   503,   946,   947,   504,   755,  1049,  1050,   505,
     370,   602,   421,    30,   513,    31,    32,    33,  1001,   548,
      57,   840,   948,   697,   698,   699,   700,    35,    36,    37,
      38,    39,    40,    41,    42,   785,    43,    44,    45,   412,
     413,   431,   550,   371,   551,   552
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,    54,   137,   137,   151,   142,   501,   479,   482,   341,
     201,   507,   136,   136,    61,   387,   485,    47,    90,   113,
     510,   135,   139,   620,   523,   404,   400,   624,   554,   403,
     403,   138,   138,   131,    55,   410,   253,    64,   535,   179,
     403,   180,   625,   540,   541,   252,   665,   366,   132,   177,
     512,  -485,    34,   626,  1010,  1026,  1076,   399,   613,   652,
     340,   347,  -488,   721,    51,    52,   132,   132,   367,   146,
     148,   132,   882,   349,    56,    58,   193,   724,   635,   266,
     184,   185,   213,   333,   765,   132,   790,  -486,   793,   774,
     432,   982,   434,    46,  -487,   437,    17,    18,   444,   197,
     989,    48,   818,   914,   132,   423,   818,    59,   510,   147,
     147,   141,   152,   132,   584,   220,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     510,   214,   799,    55,   222,    60,   424,   231,   414,   414,
     204,  -411,   205,    91,   957,   236,   583,   819,    -6,   636,
     232,   819,   215,   657,   257,   259,   260,  1022,   569,   144,
     571,   572,   518,   518,    20,  1037,   519,   519,   854,   269,
      21,   182,   227,   147,   186,   247,   247,   409,   658,   659,
     598,   216,   204,   565,   205,   219,   521,   521,   188,  1033,
     832,  -485,  -485,   228,   213,   522,   522,   206,   611,   660,
     628,  1061,  -488,  -488,   823,   566,   820,   821,   198,    94,
     820,   821,   853,    20,     6,     7,     8,     9,    10,    11,
      12,    13,   133,   776,   804,   149,   150,  -486,  -486,    95,
     426,  -368,   428,   577,  -487,  -487,   776,  -368,   982,   656,
      14,    15,    16,   501,   479,   482,   777,   386,   507,   448,
    -365,   345,   194,   485,   578,   223,  -365,   224,   386,   777,
      21,   883,   258,   258,   258,   884,   261,   674,  -367,    19,
     476,   477,   199,   508,  -367,   267,   818,   258,   207,   237,
     637,   422,   638,   523,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   669,   377,   378,   132,    21,  1077,
     141,   141,   969,   970,   132,   783,   890,   200,  1039,   391,
     904,   623,  1041,   254,    91,    20,    21,   456,    23,   366,
     906,   907,   888,   627,    24,   137,   591,   866,   137,    25,
      62,   819,   340,   347,    20,   136,    62,   871,   136,   115,
     367,   229,   903,   133,   506,   349,   449,   514,   233,   237,
     822,   234,   518,   217,   987,   333,   519,   138,   517,    20,
      21,   539,    17,    18,   116,   534,   789,   417,    21,   529,
     902,   854,   423,   619,   117,   132,   521,   739,   740,   803,
     218,   678,   889,   328,   329,   522,   118,   583,  1023,   119,
     820,   821,   912,   747,   741,   515,   912,   137,   516,   934,
     235,   330,   137,   510,   757,   137,   240,   136,   595,   137,
     971,   971,   136,   424,   621,   136,   514,   530,   120,   136,
     531,   606,   649,   592,   514,   258,   138,   622,   615,   591,
     536,   138,   422,   234,   138,   281,   242,   518,   138,   842,
     386,   519,   953,    19,   955,  1063,    20,   912,   141,  1064,
     288,  1066,   221,   289,   520,   133,   248,   258,   729,   730,
     731,   521,   249,    69,    70,    71,   298,   862,   863,   865,
     522,   518,   403,   403,   403,   519,   304,    46,   935,    61,
      86,    87,   732,   251,   734,   964,   733,   672,   735,    20,
      21,    22,    23,  1009,   255,   521,  1009,  1009,    24,     1,
       2,     3,  1016,    25,   522,   704,   781,   444,   523,   262,
     782,   501,   980,   983,   265,  1007,   507,   433,  -115,   435,
     436,   485,  -115,   584,  1034,   961,   140,   141,   537,   962,
     113,   538,   542,   345,   545,   538,   547,   546,   270,   546,
     543,   544,   574,   653,   273,   575,   654,   796,   137,   676,
     379,   677,   575,   726,   575,   380,   679,   381,   136,   680,
     568,   711,   570,   715,   712,   573,   575,   756,   717,   385,
     720,   575,   137,   575,   388,   843,  1046,   138,   575,   373,
    1047,   394,   136,   510,  1053,   844,   738,   845,   575,   391,
     575,   506,   993,   137,   397,   994,   701,   702,   703,   997,
     710,   424,   998,   136,   954,   417,   956,   427,   860,  -479,
     591,   438,   514,    69,    70,    71,   382,   383,   246,   246,
     429,   864,   138,   958,   959,  1054,   949,   950,  1052,   443,
     786,   444,  1060,  1062,    69,    70,    71,   450,   529,   455,
     549,   553,   555,   750,   751,   752,   556,    82,    83,    84,
      85,    86,    87,   977,   759,   558,   760,   761,   762,   763,
     557,   559,   764,    58,   560,   561,   579,   772,   501,   980,
     983,   580,   581,   507,   582,   637,   778,   638,   485,   639,
     640,   641,   642,   643,   644,   645,   646,   647,   648,   593,
     780,   594,   596,    92,   601,   784,   852,   716,   726,   718,
     719,   603,   604,   311,   312,   592,   377,   605,   377,   918,
     609,   317,   318,   319,   320,   321,   322,   612,   614,  1035,
     323,    58,   616,   617,   324,   325,   895,   618,   629,   898,
     630,   631,   632,   938,   591,    93,   651,    21,   940,   941,
     942,   943,   655,   664,    94,   666,   667,   668,   671,  1059,
     222,   681,   682,   841,   713,   722,   723,   727,   736,   745,
     746,   748,   841,   753,    95,   758,   787,   766,   794,   827,
     797,    66,   806,   901,    67,    68,   152,   815,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,   829,
     830,   831,   -71,  1078,   857,   858,   870,   878,   880,   881,
     879,    96,   891,   885,    97,   886,    98,   649,   892,   887,
     852,   801,   802,   893,   805,   915,   807,   808,   809,   810,
     811,   812,   813,   814,   896,   894,   919,   258,    99,   704,
     137,   920,   921,   922,   928,   -77,   386,   931,   386,   932,
     136,   936,   100,   933,   937,   944,   952,   963,   101,   506,
     974,   984,   985,   529,   988,   986,   818,   529,   833,   637,
     710,   638,   990,   639,   640,   641,   642,   643,   644,   645,
     646,   647,   648,   995,  1000,   999,  1005,  1006,   102,   103,
    1014,   968,   287,  1027,  1028,  1030,  1031,  1032,   104,  1043,
    1045,  1036,   477,   105,  1056,  1055,  1029,   147,   147,   147,
     951,  1067,  1068,  1074,  1069,   518,  1081,  1070,  1072,  1075,
     897,   929,   772,   772,   454,   960,    92,   446,   930,  1044,
     372,   147,   377,   377,   195,   196,  1021,   861,   529,   859,
     939,   737,  1065,   203,  1025,  1079,   411,   673,   714,   405,
     661,   416,   137,   905,   978,   841,   908,   909,   910,   911,
     841,   386,   136,   979,  1038,   576,   968,   900,    93,  1042,
    1057,  1051,   375,   916,  1048,   917,   779,   846,   132,   991,
     754,   138,   992,   608,   610,   817,   147,   178,   457,   147,
     147,  1058,   143,   798,     0,   529,     0,   137,     0,   529,
       0,   529,     0,     0,     0,     0,   147,   136,     0,     0,
       0,  1073,     0,   458,   258,   459,   506,     0,     0,   460,
     461,   462,     0,   463,    61,     0,   464,     0,     0,     0,
     841,     0,     0,     0,     0,  1040,     0,     0,   281,   465,
     466,   467,   468,     0,    96,   386,     0,    97,   469,    98,
       0,   286,   287,   288,     0,     0,   289,     0,     0,   826,
       0,     0,     0,     0,     0,     0,     0,     0,   297,   298,
       0,    99,     0,     0,     0,     0,     0,     0,     0,   304,
      46,   470,   471,     0,     0,   100,     0,     0,     0,     0,
       0,   101,     0,     0,     0,   311,   312,     0,     0,     0,
       0,     0,     0,   317,   318,   319,   320,   321,   322,     0,
       0,   472,   323,     0,     0,   473,   324,   325,     0,     0,
       0,   102,   103,     0,     0,     0,     0,     0,    17,    18,
       0,   104,     0,     0,     0,     0,   105,     0,     0,     0,
       0,     0,   132,     0,   474,    69,    70,    71,     0,     0,
     475,   329,   457,     0,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,     0,     0,     0,     0,   330,     0,
       0,     0,     0,     0,     0,     0,     0,   458,     0,   459,
       0,     0,     0,   460,   461,   462,     0,   463,     0,     0,
     464,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   281,   465,   466,   467,   468,     0,     0,     0,
       0,     0,   469,     0,     0,     0,     0,   288,     0,     0,
     289,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   298,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   304,    46,   470,   471,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,     0,    23,   311,
     312,     0,     0,   773,   133,     0,     0,   317,   318,   319,
     320,   321,   322,   476,   477,   472,   323,     0,    66,   473,
     324,   325,     0,     0,     0,    69,    70,    71,    72,    73,
      74,    75,    17,    18,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,     0,     0,   132,     0,   474,     0,
       0,     0,     0,     0,   475,   329,   457,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   330,     0,     0,     0,     0,     0,     0,     0,
       0,   458,     0,   459,     0,     0,     0,   460,   461,   462,
       0,   463,     0,     0,   464,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   281,   465,   466,   467,
     468,     0,     0,     0,     0,     0,   469,     0,     0,     0,
       0,   288,     0,     0,     0,     0,     0,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,   470,
     471,     0,     0,    14,    15,    16,     0,     0,     0,    20,
       0,     0,    23,   311,   312,     0,     0,     0,   133,     0,
       0,   317,   318,   319,   320,   321,   322,   476,   477,   472,
     323,     0,     0,   473,   324,   325,     0,     0,     0,    69,
      70,    71,    72,    73,    74,    75,    17,    18,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,     0,     0,
     132,     0,   474,     0,     0,     0,     0,     0,   475,   329,
     457,     0,     0,     0,     0,     0,     0,     0,     0,   774,
       0,     0,     0,     0,     0,     0,   330,     6,     7,     8,
       9,    10,    11,    12,    13,   458,     0,   459,     0,     0,
       0,   460,   461,   462,     0,   463,     0,     0,   464,     0,
       0,     0,     0,    14,    15,    16,     0,     0,   683,     0,
     281,   465,   466,   467,   468,    17,    18,     0,     0,     0,
     469,     0,     0,     0,     0,   288,     0,     0,     0,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,   470,   471,    14,    15,    16,     0,     0,
       0,   684,     0,    20,     0,     0,    23,   311,   312,     0,
       0,   773,   133,     0,     0,   317,   318,   319,   320,   321,
     322,   476,   477,   472,   323,     0,     0,   473,   324,   325,
       0,     0,     0,     0,     0,     0,    19,     0,     0,     0,
      17,    18,     6,     7,     8,     9,    10,    11,    12,    13,
       0,   767,     0,     0,     0,     0,   474,     0,     0,     0,
       0,     0,   475,   329,     0,    17,    18,     0,    14,    15,
      16,     6,     7,     8,     9,    10,    11,    12,    13,     0,
     330,   685,    20,    21,    22,    23,     0,     0,     0,     0,
       0,    24,     0,     0,     0,     0,    25,    14,    15,    16,
     476,   477,     0,     0,     0,     0,     0,     0,     6,     7,
       8,     9,    10,    11,    12,    13,     0,    17,    18,     0,
       0,   686,     0,   768,     0,     0,     0,   687,     0,     0,
       0,     0,     0,   769,    14,    15,    16,     0,     0,     0,
       0,     0,     0,     0,     0,   688,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     689,   690,   691,   692,   693,     0,     0,    20,     0,     0,
      23,     0,     0,     0,     0,     0,   133,     0,     0,     0,
       0,     0,   694,   695,     0,   476,   477,     0,     0,   768,
      17,    18,    20,    21,    22,    23,     0,     0,    19,   769,
       0,    24,     0,     0,     0,     0,    25,     0,     0,     0,
       0,   477,     0,     0,     0,     0,     0,     0,     0,    17,
      18,     0,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,   685,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    14,    15,
      16,     0,     0,    24,     0,     0,    17,    18,    25,     0,
     833,     0,     0,     0,     0,     0,   945,     0,     0,     0,
       0,    19,  1008,     0,     0,     0,     0,     0,     0,     0,
       0,   687,     0,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      15,    16,     0,     0,     0,     0,     0,    20,    21,    22,
      23,     0,     0,     0,     0,     0,    24,   945,     0,     0,
       0,    25,     0,  1011,     0,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,     0,    20,    21,    22,    23,
       0,     0,     0,     0,     0,    24,     0,     0,     0,     0,
      25,     6,     7,     8,     9,    10,    11,    12,    13,     0,
      17,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    14,    15,    16,
       0,     0,    24,     0,     0,     0,     0,    25,     0,     0,
       0,     0,     0,     0,     0,   945,     0,     0,     0,     0,
       0,  1012,     0,     0,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    18,     0,     0,     0,     0,     0,     0,     0,
      14,    15,    16,     6,     7,     8,     9,    10,    11,    12,
      13,    19,     0,     0,     0,     0,     0,     0,   965,     0,
       0,     0,     0,     0,  1024,     0,     0,     0,     0,    14,
      15,    16,     0,     0,     0,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    14,    15,    16,     0,     0,    24,     0,     0,    17,
      18,    25,    19,     0,     0,     0,     0,     0,     0,   945,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    14,    15,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,    21,
      22,    23,    17,    18,   965,     0,     0,    24,     0,     0,
       0,     0,    25,     0,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
      19,    17,    18,     0,     0,     0,     0,     0,     0,     0,
      14,    15,    16,     0,     0,     0,     0,     0,     0,    66,
       0,     0,    67,    68,     0,     0,    69,    70,    71,    72,
      73,    74,    75,    17,    18,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    20,    21,    22,    23,
       0,     0,     0,    19,     0,    24,     0,     0,     0,     0,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    18,
       0,     0,    19,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,     0,     0,     0,     0,     0,    24,     0,
       0,     0,     0,    25,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,    21,
      22,    23,    17,    18,     0,     0,     0,    24,     0,     0,
       0,   268,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
      20,    21,    22,    23,     0,     0,     0,     0,    66,    24,
       0,    67,    68,     0,    25,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    21,    22,    23,     0,
       0,     0,     0,    19,    24,     0,     0,    66,     0,    25,
      67,    68,     0,     0,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,     0,     0,     0,     0,    66,    24,     0,
      67,    68,     0,    25,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    66,     0,     0,    67,    68,
       0,     0,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    66,     0,     0,    67,    68,     0,     0,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    66,     0,     0,    67,    68,     0,     0,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    66,
       0,     0,    67,    68,     0,     0,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    66,     0,     0,
      67,    68,     0,     0,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,     0,     0,    67,    68,     0,   867,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    66,
       0,     0,    67,    68,     0,   868,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    66,     0,     0,
      67,    68,     0,     0,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,   869,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    66,     0,     0,
      67,    68,     0,   872,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    66,     0,     0,    67,    68,
       0,   873,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    66,     0,     0,    67,    68,     0,   874,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    66,     0,     0,    67,    68,     0,   875,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    66,
       0,     0,    67,    68,     0,   876,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   132,     0,     0,
       0,     0,     0,    66,     0,     0,    67,    68,     0,     0,
      69,    70,    71,    72,    73,    74,    75,    76,   877,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
     274,   275,   276,     0,     0,   277,   278,   279,     0,     0,
       0,   280,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   281,     0,     0,
       0,     0,   282,   283,   284,     0,     0,  1015,     0,   285,
     286,   287,   288,     0,     0,   289,     0,     0,     0,   290,
       0,   291,   292,   293,   294,   295,   296,   297,   298,   299,
       0,     0,     0,   225,   300,   301,   302,   303,   304,    46,
       0,     0,   305,   306,   307,   308,   309,     0,     0,     0,
       0,   310,     0,     0,   311,   312,     0,   313,   132,   314,
     315,   316,   317,   318,   319,   320,   321,   322,     0,     0,
       0,   323,     0,     0,     0,   324,   325,   326,   327,     0,
       0,     0,     0,   975,     0,     0,     0,     0,     0,     0,
       0,   274,   275,   276,     0,     0,   277,   278,   279,     0,
       0,     0,   280,     0,     0,     0,     0,    24,     0,   328,
     329,     0,     0,     0,     0,     0,     0,     0,   281,     0,
       0,     0,     0,   282,     0,   284,     0,   330,     0,     0,
     285,     0,     0,   288,   824,     0,   289,     0,     0,     0,
     290,     0,   291,   292,   293,   294,   295,   296,     0,   298,
     299,     0,     0,     0,     0,   300,   301,   302,   303,   304,
      46,     0,   825,   305,   306,   307,   308,   309,     0,     0,
       0,     0,     0,   331,     0,   311,   312,     0,   313,     0,
     314,   315,   316,   317,   318,   319,   320,   321,   322,     0,
    1013,     0,   323,     0,     0,     0,   324,   325,   326,   327,
      66,     0,     0,    67,    68,     0,     0,    69,    70,    71,
      72,    73,    74,    75,   332,     0,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     0,     0,     0,     0,
     328,   329,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,    67,    68,     0,   330,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   311,
     312,     0,     0,     0,   331,     0,     0,   317,   318,   319,
     320,   321,   322,     0,     0,    66,   323,     0,    67,    68,
     324,   325,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   145,     0,   332,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      96,     0,     0,    97,     0,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   100,     0,     0,     0,     0,     0,   101,    66,     0,
       0,    67,    68,     0,   685,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   226,   102,   103,     0,
       0,     0,     0,     0,     0,     0,    66,   104,     0,    67,
      68,     0,   105,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,   256,    66,     0,     0,    67,    68,
       0,     0,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,     0,     0,     0,     0,     0,   816
};

static const yytype_int16 yycheck[] =
{
      17,    18,    53,    54,    62,    56,   386,   386,   386,   247,
     120,   386,    53,    54,    31,   274,   386,     3,    35,    46,
     388,    53,    54,   474,   396,   287,   285,   476,   421,   286,
     287,    53,    54,    50,    24,   297,     7,    32,   404,    90,
     297,    91,     6,   409,   410,   209,   518,   247,     6,    90,
     389,     6,     2,    17,    38,    38,    38,   284,   468,   508,
     247,   247,     6,   575,    14,    15,     6,     6,   247,    59,
      60,     6,    95,   247,    24,    25,   113,   580,   498,   234,
     107,   108,   132,   247,   623,     6,   666,     6,   668,   110,
     355,   901,   357,   108,     6,   360,   156,   157,   283,   116,
     915,     0,    40,   826,     6,   242,    40,   297,   476,    59,
      60,   294,    62,     6,   299,   298,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
     508,   136,   681,   133,    38,   297,   283,   184,   303,   304,
      85,   297,    87,   299,   877,   192,    96,    95,     0,    27,
     187,    95,   136,    81,   222,   223,   224,    38,   433,   298,
     435,   436,    43,    43,   283,   990,    47,    47,    80,   237,
     284,   226,   177,   133,   239,   202,   203,   297,   106,   107,
     457,   141,    85,   116,    87,   145,    67,    67,   283,   303,
     712,   156,   157,   177,   254,    76,    76,   100,   467,   127,
     477,  1021,   156,   157,   700,   138,   154,   155,   206,   117,
     154,   155,   725,   283,     8,     9,    10,    11,    12,    13,
      14,    15,   292,   636,   685,   156,   157,   156,   157,   137,
     329,    59,   331,   443,   156,   157,   649,    65,  1058,   516,
      34,    35,    36,   633,   633,   633,   636,   274,   633,   373,
      59,   247,   204,   633,   443,   159,    65,   161,   285,   649,
     284,   294,   222,   223,   224,   298,   226,   283,    59,   237,
     301,   302,   207,   297,    65,   235,    40,   237,   181,   295,
     158,   313,   160,   665,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   531,   255,   256,     6,   284,   291,
     294,   294,   892,   893,     6,   654,   788,   208,   994,   283,
     806,   297,   998,   294,   299,   283,   284,   385,   286,   529,
     816,   817,   781,   297,   292,   386,   450,   747,   389,   297,
     295,    95,   529,   529,   283,   386,   295,   757,   389,   191,
     529,   292,   803,   292,   386,   529,   373,   389,   291,   295,
     298,   294,    43,   293,   298,   529,    47,   389,   395,   283,
     284,   408,   156,   157,   216,   402,    57,   295,   284,   396,
     800,    80,   242,   297,   226,     6,    67,    79,    80,   295,
     293,   546,   785,   178,   179,    76,   238,    96,   965,   241,
     154,   155,   822,   601,    96,   291,   826,   458,   294,   108,
     300,   196,   463,   781,   612,   466,   283,   458,   455,   470,
     291,   291,   463,   283,   474,   466,   458,   291,   270,   470,
     294,   463,   300,   450,   466,   385,   458,   297,   470,   553,
     291,   463,   464,   294,   466,    66,    61,    43,   470,   714,
     467,    47,   872,   237,   874,  1022,   283,   877,   294,  1026,
      81,  1028,   298,    84,    60,   292,    61,   417,   582,   583,
     584,    67,   283,    17,    18,    19,    97,   739,   740,   741,
      76,    43,   739,   740,   741,    47,   107,   108,   854,   506,
      34,    35,   294,   283,   294,    57,   298,   534,   298,   283,
     284,   285,   286,   946,   300,    67,   949,   950,   292,     3,
       4,     5,   961,   297,    76,   299,   294,   283,   890,   283,
     298,   901,   901,   901,   292,   945,   901,   356,   294,   358,
     359,   901,   298,   299,   985,   294,   293,   294,   291,   298,
     567,   294,   291,   529,   291,   294,   291,   294,   291,   294,
     412,   413,   291,   291,   291,   294,   294,   671,   609,   291,
     296,   291,   294,   580,   294,   296,   291,   296,   609,   294,
     432,   291,   434,   291,   294,   437,   294,   609,   291,    38,
     291,   294,   633,   294,   301,   291,  1006,   609,   294,   297,
    1010,    42,   633,   961,  1014,   291,   591,   291,   294,   283,
     294,   633,   291,   654,   283,   294,   556,   557,   558,   291,
     560,   283,   294,   654,   873,   295,   875,   242,   732,    38,
     734,   283,   654,    17,    18,    19,   293,   294,   202,   203,
     301,   741,   654,   882,   883,  1015,   868,   869,  1013,    38,
     662,   283,  1021,  1021,    17,    18,    19,   297,   665,   293,
     283,   297,   297,   603,   604,   605,    38,    30,    31,    32,
      33,    34,    35,   901,   614,   297,   616,   617,   618,   619,
      38,   209,   622,   623,   297,   283,   298,   627,  1058,  1058,
    1058,   294,   298,  1058,   294,   158,   636,   160,  1058,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   291,
     650,   291,   296,    66,    38,   655,   723,   569,   725,   571,
     572,   297,   297,   123,   124,   732,   666,   297,   668,   833,
     297,   131,   132,   133,   134,   135,   136,    38,   297,   988,
     140,   681,   297,   297,   144,   145,   794,   297,   291,   797,
     291,   291,   291,   857,   858,   108,   291,   284,   862,   863,
     864,   865,   300,    38,   117,   297,   297,   297,   294,  1018,
      38,   300,   291,   713,   297,   297,   291,   291,   295,   291,
     283,    57,   722,   291,   137,    82,   283,   298,   295,   283,
     300,    10,   297,   800,    13,    14,   736,   297,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,   298,
     294,   294,   298,  1072,   294,   297,   291,   298,   768,   769,
     298,   184,   298,   297,   187,   775,   189,   300,   291,   779,
     847,   683,   684,   300,   686,   297,   688,   689,   690,   691,
     692,   693,   694,   695,   794,   298,   298,   797,   211,   299,
     901,   294,   294,   283,   298,   125,   873,   291,   875,   291,
     901,    62,   225,   291,   125,    57,    82,   291,   231,   901,
      38,    65,    38,   890,    56,   298,    40,   894,   299,   158,
     830,   160,   297,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   300,   283,    62,   298,    38,   261,   262,
      56,   891,    80,   291,    56,   291,   291,   291,   271,    64,
      38,   298,   302,   276,   291,   298,   974,   867,   868,   869,
     870,   296,   296,    59,   296,    43,   291,   298,   298,   298,
     796,   847,   882,   883,   383,   885,    66,   373,   847,  1002,
     248,   891,   892,   893,   116,   116,   963,   734,   965,   732,
     858,   591,  1027,   130,   966,  1075,   298,   538,   567,   288,
     517,   304,  1013,   815,   901,   915,   818,   819,   820,   821,
     920,   988,  1013,   901,   994,   441,   966,   800,   108,   998,
    1018,  1013,   254,   830,  1013,   831,   649,   722,     6,   920,
     609,  1013,   921,   464,   466,   697,   946,    90,    16,   949,
     950,  1018,    56,   680,    -1,  1022,    -1,  1058,    -1,  1026,
      -1,  1028,    -1,    -1,    -1,    -1,   966,  1058,    -1,    -1,
      -1,   300,    -1,    41,   974,    43,  1058,    -1,    -1,    47,
      48,    49,    -1,    51,  1051,    -1,    54,    -1,    -1,    -1,
     990,    -1,    -1,    -1,    -1,   995,    -1,    -1,    66,    67,
      68,    69,    70,    -1,   184,  1072,    -1,   187,    76,   189,
      -1,    79,    80,    81,    -1,    -1,    84,    -1,    -1,   298,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    97,
      -1,   211,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,
     108,   109,   110,    -1,    -1,   225,    -1,    -1,    -1,    -1,
      -1,   231,    -1,    -1,    -1,   123,   124,    -1,    -1,    -1,
      -1,    -1,    -1,   131,   132,   133,   134,   135,   136,    -1,
      -1,   139,   140,    -1,    -1,   143,   144,   145,    -1,    -1,
      -1,   261,   262,    -1,    -1,    -1,    -1,    -1,   156,   157,
      -1,   271,    -1,    -1,    -1,    -1,   276,    -1,    -1,    -1,
      -1,    -1,     6,    -1,   172,    17,    18,    19,    -1,    -1,
     178,   179,    16,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,   196,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    43,
      -1,    -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   107,   108,   109,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   283,    -1,    -1,   286,   123,
     124,    -1,    -1,   291,   292,    -1,    -1,   131,   132,   133,
     134,   135,   136,   301,   302,   139,   140,    -1,    10,   143,
     144,   145,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,   156,   157,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,     6,    -1,   172,    -1,
      -1,    -1,    -1,    -1,   178,   179,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   196,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    43,    -1,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,
     110,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,   283,
      -1,    -1,   286,   123,   124,    -1,    -1,    -1,   292,    -1,
      -1,   131,   132,   133,   134,   135,   136,   301,   302,   139,
     140,    -1,    -1,   143,   144,   145,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,   156,   157,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
       6,    -1,   172,    -1,    -1,    -1,    -1,    -1,   178,   179,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,   196,     8,     9,    10,
      11,    12,    13,    14,    15,    41,    -1,    43,    -1,    -1,
      -1,    47,    48,    49,    -1,    51,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    34,    35,    36,    -1,    -1,    39,    -1,
      66,    67,    68,    69,    70,   156,   157,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,   110,    34,    35,    36,    -1,    -1,
      -1,    92,    -1,   283,    -1,    -1,   286,   123,   124,    -1,
      -1,   291,   292,    -1,    -1,   131,   132,   133,   134,   135,
     136,   301,   302,   139,   140,    -1,    -1,   143,   144,   145,
      -1,    -1,    -1,    -1,    -1,    -1,   237,    -1,    -1,    -1,
     156,   157,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    -1,   172,    -1,    -1,    -1,
      -1,    -1,   178,   179,    -1,   156,   157,    -1,    34,    35,
      36,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
     196,   172,   283,   284,   285,   286,    -1,    -1,    -1,    -1,
      -1,   292,    -1,    -1,    -1,    -1,   297,    34,    35,    36,
     301,   302,    -1,    -1,    -1,    -1,    -1,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,   156,   157,    -1,
      -1,   212,    -1,    89,    -1,    -1,    -1,   218,    -1,    -1,
      -1,    -1,    -1,    99,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   236,   237,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     251,   252,   253,   254,   255,    -1,    -1,   283,    -1,    -1,
     286,    -1,    -1,    -1,    -1,    -1,   292,    -1,    -1,    -1,
      -1,    -1,   273,   274,    -1,   301,   302,    -1,    -1,    89,
     156,   157,   283,   284,   285,   286,    -1,    -1,   237,    99,
      -1,   292,    -1,    -1,    -1,    -1,   297,    -1,    -1,    -1,
      -1,   302,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,   172,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   283,   284,   285,   286,    34,    35,
      36,    -1,    -1,   292,    -1,    -1,   156,   157,   297,    -1,
     299,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,   237,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   218,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     237,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,   283,   284,   285,
     286,    -1,    -1,    -1,    -1,    -1,   292,    52,    -1,    -1,
      -1,   297,    -1,    58,    -1,    -1,    -1,   237,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   283,   284,   285,   286,
      -1,    -1,    -1,    -1,    -1,   292,    -1,    -1,    -1,    -1,
     297,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
     156,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   283,   284,   285,   286,    34,    35,    36,
      -1,    -1,   292,    -1,    -1,    -1,    -1,   297,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,     8,     9,    10,    11,    12,    13,    14,
      15,   237,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   283,   284,   285,
     286,    34,    35,    36,    -1,    -1,   292,    -1,    -1,   156,
     157,   297,   237,    -1,    -1,    -1,    -1,    -1,    -1,    52,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   283,   284,
     285,   286,   156,   157,    52,    -1,    -1,   292,    -1,    -1,
      -1,    -1,   297,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     237,   156,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    10,
      -1,    -1,    13,    14,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,   156,   157,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,   283,   284,   285,   286,
      -1,    -1,    -1,   237,    -1,   292,    -1,    -1,    -1,    -1,
     297,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,   157,
      -1,    -1,   237,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   283,
     284,   285,   286,    -1,    -1,    -1,    -1,    -1,   292,    -1,
      -1,    -1,    -1,   297,   237,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   283,   284,
     285,   286,   156,   157,    -1,    -1,    -1,   292,    -1,    -1,
      -1,   296,   297,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   237,
     283,   284,   285,   286,    -1,    -1,    -1,    -1,    10,   292,
      -1,    13,    14,    -1,   297,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   283,   284,   285,   286,    -1,
      -1,    -1,    -1,   237,   292,    -1,    -1,    10,    -1,   297,
      13,    14,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   283,
     284,   285,   286,    -1,    -1,    -1,    -1,    10,   292,    -1,
      13,    14,    -1,   297,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    10,    -1,    -1,    13,    14,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    10,    -1,    -1,    13,    14,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    10,    -1,    -1,    13,    14,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    10,
      -1,    -1,    13,    14,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    10,    -1,    -1,
      13,    14,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      10,    -1,    -1,    13,    14,    -1,   298,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    10,
      -1,    -1,    13,    14,    -1,   298,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    10,    -1,    -1,
      13,    14,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,   298,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    10,    -1,    -1,
      13,    14,    -1,   298,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    10,    -1,    -1,    13,    14,
      -1,   298,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    10,    -1,    -1,    13,    14,    -1,   298,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    10,    -1,    -1,    13,    14,    -1,   298,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    10,
      -1,    -1,    13,    14,    -1,   298,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,     6,    -1,    -1,
      -1,    -1,    -1,    10,    -1,    -1,    13,    14,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,   298,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      39,    40,    41,    -1,    -1,    44,    45,    46,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    71,    72,    73,    -1,    -1,   298,    -1,    78,
      79,    80,    81,    -1,    -1,    84,    -1,    -1,    -1,    88,
      -1,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,   296,   103,   104,   105,   106,   107,   108,
      -1,    -1,   111,   112,   113,   114,   115,    -1,    -1,    -1,
      -1,   120,    -1,    -1,   123,   124,    -1,   126,     6,   128,
     129,   130,   131,   132,   133,   134,   135,   136,    -1,    -1,
      -1,   140,    -1,    -1,    -1,   144,   145,   146,   147,    -1,
      -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    -1,    -1,    44,    45,    46,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,   292,    -1,   178,
     179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    71,    -1,    73,    -1,   196,    -1,    -1,
      78,    -1,    -1,    81,   291,    -1,    84,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    97,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,   106,   107,
     108,    -1,   291,   111,   112,   113,   114,   115,    -1,    -1,
      -1,    -1,    -1,   242,    -1,   123,   124,    -1,   126,    -1,
     128,   129,   130,   131,   132,   133,   134,   135,   136,    -1,
     291,    -1,   140,    -1,    -1,    -1,   144,   145,   146,   147,
      10,    -1,    -1,    13,    14,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,   283,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
     178,   179,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    10,    -1,    -1,    13,    14,    -1,   196,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,
     124,    -1,    -1,    -1,   242,    -1,    -1,   131,   132,   133,
     134,   135,   136,    -1,    -1,    10,   140,    -1,    13,    14,
     144,   145,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,   283,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,    -1,    -1,   187,    -1,   189,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,    -1,    -1,    -1,    -1,    -1,   231,    10,    -1,
      -1,    13,    14,    -1,   172,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,   261,   262,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    10,   271,    -1,    13,
      14,    -1,   276,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    10,    -1,    -1,    13,    14,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,   266
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,   305,   306,     8,     9,    10,    11,
      12,    13,    14,    15,    34,    35,    36,   156,   157,   237,
     283,   284,   285,   286,   292,   297,   493,   494,   495,   509,
     537,   539,   540,   541,   547,   551,   552,   553,   554,   555,
     556,   557,   558,   560,   561,   562,   108,   416,     0,   307,
     308,   547,   547,   447,   447,   546,   547,   544,   547,   297,
     297,   447,   295,   371,   372,   373,    10,    13,    14,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
     447,   299,    66,   108,   117,   137,   184,   187,   189,   211,
     225,   231,   261,   262,   271,   276,   316,   319,   320,   321,
     332,   404,   405,   412,   413,   191,   216,   226,   238,   241,
     270,   309,   310,   311,   312,   313,   315,   334,   352,   354,
     355,   447,     6,   292,   448,   539,   540,   556,   561,   539,
     293,   294,   556,   557,   298,    38,   546,   547,   546,   156,
     157,   543,   547,   547,   547,   547,   547,   547,   547,   547,
     547,   547,   547,   547,   547,   547,   547,   547,   547,   547,
     547,   547,   547,   547,   547,   547,   547,   540,   553,   556,
     562,   323,   226,   325,   412,   412,   239,   326,   283,   417,
     418,   419,   420,   327,   204,   354,   355,   447,   206,   207,
     208,   316,   375,   375,    85,    87,   100,   181,   314,   359,
     449,   450,   451,   562,   372,   373,   547,   293,   293,   547,
     298,   298,    38,   159,   161,   296,    38,   372,   373,   292,
     324,   327,   412,   291,   294,   300,   327,   295,   329,   331,
     283,   333,    61,   376,   377,   391,   392,   447,    61,   283,
     335,   283,   360,     7,   294,   300,    38,   543,   547,   543,
     543,   547,   283,   317,   318,   292,   417,   547,   296,   543,
     291,   353,   360,   291,    39,    40,    41,    44,    45,    46,
      50,    66,    71,    72,    73,    78,    79,    80,    81,    84,
      88,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     103,   104,   105,   106,   107,   111,   112,   113,   114,   115,
     120,   123,   124,   126,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   140,   144,   145,   146,   147,   178,   179,
     196,   242,   283,   360,   378,   393,   394,   395,   396,   397,
     400,   406,   407,   408,   411,   416,   423,   424,   425,   427,
     429,   438,   443,   453,   455,   456,   457,   458,   459,   460,
     461,   462,   467,   484,   488,   489,   501,   503,   505,   506,
     534,   567,   353,   297,   358,   450,   383,   547,   547,   296,
     296,   296,   293,   294,   322,    38,   447,   490,   301,   435,
     436,   283,   454,   522,    42,   414,   379,   283,   398,   399,
     490,   409,   410,   411,   409,   418,   401,   402,   412,   316,
     409,   401,   563,   564,   417,   426,   426,   295,   372,   421,
     422,   536,   561,   242,   283,   502,   502,   242,   502,   301,
     468,   565,   435,   565,   435,   565,   565,   435,   283,   463,
     464,   465,   466,    38,   283,   336,   339,   342,   374,   447,
     297,   356,   357,   361,   317,   293,   543,    16,    41,    43,
      47,    48,    49,    51,    54,    67,    68,    69,    70,    76,
     109,   110,   139,   143,   172,   178,   301,   302,   416,   423,
     427,   452,   453,   491,   492,   493,   497,   499,   500,   501,
     503,   507,   510,   511,   512,   513,   515,   516,   517,   518,
     520,   521,   525,   526,   529,   533,   539,   552,   297,   437,
     560,   485,   486,   538,   539,   291,   294,   412,    43,    47,
      60,    67,    76,   380,   382,   384,   387,   390,   392,   447,
     291,   294,   374,   415,   412,   415,   291,   291,   294,   327,
     415,   415,   291,   463,   463,   291,   294,   291,   543,   283,
     566,   568,   569,   297,   357,   297,    38,    38,   297,   209,
     297,   283,   475,   476,   477,   116,   138,   428,   463,   435,
     463,   435,   435,   463,   291,   294,   421,   501,   503,   298,
     294,   298,   294,    96,   299,   362,   363,   367,   368,   369,
     370,   374,   447,   291,   291,   327,   296,   498,   522,   486,
     487,    38,   535,   297,   297,   297,   539,   508,   536,   297,
     487,   490,    38,   535,   297,   539,   297,   297,   297,   297,
     555,   562,   297,   297,   437,     6,    17,   297,   522,   291,
     291,   291,   291,   447,   490,   496,    27,   158,   160,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   300,
     514,   291,   437,   291,   294,   300,   522,    81,   106,   107,
     127,   422,   439,   440,    38,   379,   297,   297,   297,   399,
     328,   294,   327,   402,   283,   403,   291,   291,   417,   291,
     294,   300,   291,    39,    92,   172,   212,   218,   236,   251,
     252,   253,   254,   255,   273,   274,   521,   547,   548,   549,
     550,   547,   547,   547,   299,   469,   470,   471,   472,   473,
     547,   291,   294,   297,   404,   291,   463,   291,   463,   463,
     291,   476,   297,   291,   340,   343,   447,   291,   344,   374,
     374,   374,   294,   298,   294,   298,   295,   371,   372,    79,
      80,    96,   364,   365,   366,   291,   283,   534,    57,   496,
     547,   547,   547,   291,   512,   530,   539,   534,    82,   547,
     547,   547,   547,   547,   547,   544,   298,    17,    89,    99,
     523,   524,   547,   291,   110,   519,   520,   521,   547,   519,
     547,   294,   298,   486,   547,   559,   561,   283,   388,    57,
     383,   389,   399,   383,   295,   330,   374,   300,   568,   544,
     444,   548,   548,   295,   555,   548,   297,   548,   548,   548,
     548,   548,   548,   548,   548,   297,   266,   550,    40,    95,
     154,   155,   298,   549,   291,   291,   298,   283,   474,   298,
     294,   294,   476,   299,   478,   479,   480,   481,   482,   483,
     545,   547,   435,   291,   291,   291,   478,   337,   338,   339,
     340,   341,   447,   340,    80,   345,   346,   294,   297,   363,
     374,   368,   409,   409,   316,   409,   535,   298,   298,   298,
     291,   535,   298,   298,   298,   298,   298,   298,   298,   298,
     547,   547,    95,   294,   298,   297,   547,   547,   437,   357,
     379,   298,   291,   300,   298,   543,   547,   328,   543,   445,
     446,   447,   496,   555,   549,   548,   549,   549,   548,   548,
     548,   548,   496,   504,   504,   297,   472,   473,   374,   298,
     294,   294,   283,   430,   431,   432,   433,   434,   298,   338,
     345,   291,   291,   291,   108,   415,    62,   125,   374,   369,
     374,   374,   374,   374,    57,    52,   527,   528,   546,   527,
     527,   547,    82,   496,   490,   496,   490,   504,   524,   524,
     547,   294,   298,   291,    57,    52,   385,   386,   546,   383,
     383,   291,   380,   381,    38,   296,   400,   406,   407,   408,
     423,   424,   452,   453,    65,    38,   298,   298,    56,   545,
     297,   481,   483,   291,   294,   300,   327,   291,   294,    62,
     283,   542,   347,   348,   349,   298,    38,   496,    58,   528,
      38,    58,    58,   291,    56,   298,   437,   406,   441,   442,
     446,   447,    38,   381,    58,   386,    38,   291,    56,   543,
     291,   291,   291,   303,   555,   490,   298,   545,   431,   432,
     547,   432,   434,    64,   348,    38,   496,   496,   513,   531,
     532,   539,   552,   496,   521,   298,   291,   442,   447,   490,
     423,   452,   453,   381,   381,   389,   381,   296,   296,   296,
     298,   350,   298,   300,    59,   298,    38,   291,   490,   390,
     351,   291
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   304,   306,   305,   305,   305,   307,   308,   308,   309,
     309,   309,   309,   309,   309,   309,   309,   310,   311,   312,
     313,   314,   315,   316,   316,   316,   316,   316,   316,   316,
     316,   316,   317,   318,   318,   319,   319,   319,   320,   321,
     322,   323,   324,   325,   325,   326,   326,   327,   327,   328,
     328,   329,   329,   330,   330,   331,   332,   332,   333,   334,
     334,   335,   336,   337,   337,   338,   338,   338,   339,   340,
     341,   342,   343,   343,   344,   344,   345,   346,   347,   347,
     348,   348,   349,   350,   351,   352,   352,   352,   352,   353,
     353,   354,   355,   356,   357,   357,   358,   359,   359,   360,
     361,   362,   362,   362,   363,   363,   363,   364,   365,   365,
     366,   367,   367,   368,   368,   369,   369,   370,   370,   370,
     371,   372,   373,   373,   374,   375,   375,   376,   376,   377,
     377,   377,   378,   379,   379,   380,   380,   380,   380,   380,
     381,   381,   382,   382,   383,   384,   385,   385,   386,   386,
     386,   387,   388,   389,   390,   390,   391,   391,   391,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   393,
     393,   393,   393,   393,   393,   393,   394,   394,   394,   395,
     396,   397,   398,   398,   399,   400,   400,   401,   401,   402,
     403,   404,   404,   405,   406,   407,   407,   408,   409,   410,
     410,   411,   411,   412,   412,   413,   413,   414,   414,   415,
     415,   416,   417,   417,   418,   418,   419,   420,   421,   421,
     422,   423,   424,   425,   426,   426,   427,   427,   428,   428,
     428,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   430,   430,   431,   432,   433,   433,   434,   435,   435,
     436,   436,   436,   436,   437,   438,   439,   439,   440,   440,
     440,   440,   440,   441,   441,   442,   442,   443,   444,   444,
     445,   445,   445,   445,   446,   446,   446,   446,   446,   447,
     447,   448,   449,   449,   450,   450,   451,   452,   453,   454,
     454,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     456,   456,   457,   457,   457,   457,   458,   458,   458,   458,
     459,   459,   459,   459,   459,   459,   460,   460,   461,   461,
     461,   461,   462,   462,   463,   463,   464,   465,   465,   466,
     467,   468,   468,   469,   469,   470,   470,   471,   471,   472,
     473,   474,   475,   475,   476,   477,   477,   478,   479,   479,
     480,   480,   481,   482,   482,   483,   484,   485,   485,   486,
     487,   488,   489,   490,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   492,   493,   493,   494,   495,
     495,   496,   496,   497,   498,   499,   499,   500,   501,   501,
     501,   502,   503,   504,   504,   505,   505,   506,   506,   507,
     508,   509,   510,   511,   511,   511,   511,   512,   512,   513,
     514,   514,   514,   514,   514,   514,   514,   514,   514,   514,
     514,   514,   514,   515,   515,   516,   517,   517,   517,   518,
     518,   518,   519,   519,   519,   520,   520,   521,   521,   521,
     521,   521,   522,   523,   523,   523,   524,   524,   524,   525,
     525,   526,   526,   526,   527,   527,   528,   528,   528,   529,
     529,   529,   529,   530,   531,   532,   532,   533,   533,   534,
     535,   535,   536,   537,   538,   539,   539,   539,   539,   540,
     540,   541,   542,   543,   544,   544,   545,   545,   546,   546,
     547,   547,   547,   547,   547,   547,   547,   547,   547,   547,
     547,   547,   547,   547,   547,   547,   547,   547,   547,   547,
     547,   547,   547,   547,   547,   547,   547,   547,   547,   547,
     548,   548,   548,   548,   548,   548,   548,   548,   548,   548,
     548,   548,   548,   548,   548,   548,   548,   549,   549,   549,
     549,   549,   550,   550,   550,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   552,   552,   552,   552,   553,   553,
     553,   553,   553,   553,   553,   553,   553,   554,   555,   556,
     557,   557,   558,   559,   560,   561,   561,   562,   563,   564,
     565,   566,   566,   567,   568,   569
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     2,     2,     1,     0,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     2,
       2,     1,     4,     3,     2,     7,     5,     1,     1,     3,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       0,     0,     0,     0,     1,     0,     1,     0,     2,     0,
       2,     5,     1,     5,     3,     2,     1,     1,     1,    10,
       9,     1,     3,     1,     2,     2,     2,     2,     3,     3,
       3,     3,     1,     2,     1,     3,     4,     0,     1,     2,
       4,     6,     0,     0,     0,     4,     4,     2,     2,     0,
       1,     6,     6,     3,     0,     1,     0,     1,     1,     1,
       3,     1,     3,     3,     2,     2,     2,     3,     3,     3,
       3,     1,     3,     1,     5,     0,     1,     1,     2,     2,
       3,     5,     5,     5,     1,     0,     2,     2,     1,     1,
       2,     2,     3,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     5,     7,     1,     6,     1,     2,     3,     3,
       2,     9,     1,     3,     3,     5,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     3,     1,     3,     3,     1,     3,     5,
       1,     1,     1,     2,     3,     3,     3,     3,     3,     0,
       1,     1,     1,     0,     1,     1,     1,     0,     1,     2,
       4,     4,     3,     1,     1,     3,     2,     1,     0,     1,
       1,     3,     3,     3,     1,     3,     7,     7,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     1,     1,     3,     3,     0,     1,
       2,     4,     6,     8,     1,    10,     0,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     7,     0,     2,
       1,     3,     3,     3,     2,     2,     2,     2,     2,     0,
       2,     3,     1,     3,     3,     1,     1,     1,     3,     1,
       3,     4,     5,     4,     5,     5,     4,     3,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     0,     1,     1,
       4,     0,     4,     1,     1,     1,     3,     1,     3,     1,
       5,     1,     1,     3,     4,     0,     1,     1,     1,     1,
       1,     3,     1,     1,     3,     5,     4,     1,     3,     3,
       1,     2,     2,     2,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     2,     1,     1,     4,     1,
       4,     1,     2,     3,     1,     3,     5,     3,     6,     5,
       5,     1,     6,     1,     3,     1,     3,     1,     3,     5,
       1,     1,     5,     2,     2,     2,     2,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     4,     2,     1,     1,     1,     2,
       2,     4,     1,     1,     5,     2,     4,     2,     4,     2,
       4,     3,     1,     1,     3,     3,     1,     2,     2,     5,
       7,     6,     6,     6,     1,     2,     3,     3,     2,     2,
       5,     5,     9,     1,     1,     1,     1,     3,     5,     1,
       0,     2,     1,     1,     1,     1,     2,     2,     1,     1,
       2,     1,     1,     1,     1,     5,     0,     1,     1,     3,
       1,     3,     1,     3,     3,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     1,
       1,     2,     3,     3,     3,     3,     4,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     2,     3,
       4,     3,     2,     6,     6,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     1,     1,
       2,     2,     1,     1,     1,     3,     1,     1,     1,     3,
       4,     4,     1,     1,     1,     1,     3,     1,     0,     0,
       0,     1,     3,     4,     3,     1
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
        case 2:
#line 564 "parser.y" /* yacc.c:1646  */
    { /*yydebug=1;*/ }
#line 3454 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 566 "parser.y" /* yacc.c:1646  */
    { PARSER.parse_tree.expr.swap(stack((yyvsp[0]))); }
#line 3460 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 568 "parser.y" /* yacc.c:1646  */
    { PARSER.parse_tree.expr.swap(stack((yyvsp[0]))); }
#line 3466 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 618 "parser.y" /* yacc.c:1646  */
    { PARSER.parse_tree.create_typedef(stack((yyvsp[-2])), stack((yyvsp[-1]))); }
#line 3472 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 623 "parser.y" /* yacc.c:1646  */
    {
                  (yyval)=(yyvsp[0]);
                  add_as_subtype(stack_type((yyval)), stack_type((yyvsp[-1])));
                }
#line 3481 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 628 "parser.y" /* yacc.c:1646  */
    {
                  (yyval)=(yyvsp[-1]);
                  add_as_subtype(stack_type((yyval)), stack_type((yyvsp[0])));
                }
#line 3490 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 637 "parser.y" /* yacc.c:1646  */
    { /* todo */ }
#line 3496 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 639 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_enum); }
#line 3502 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 641 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_string); }
#line 3508 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 643 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_chandle); }
#line 3514 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 645 "parser.y" /* yacc.c:1646  */
    { init((yyval), "virtual_interface"); }
#line 3520 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 651 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_event); }
#line 3526 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 663 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mts((yyval), (yyvsp[0])); }
#line 3532 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 665 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]); mts((yyval), (yyvsp[0])); }
#line 3538 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 669 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_bit); }
#line 3544 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 670 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_logic); }
#line 3550 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 671 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_reg); }
#line 3556 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 675 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_int); }
#line 3562 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 679 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_class); }
#line 3568 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 699 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 3574 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 700 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_interface); }
#line 3580 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 714 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 3586 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 715 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_packed); }
#line 3592 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 720 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 3598 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 722 "parser.y" /* yacc.c:1646  */
    {
	    (yyval)=(yyvsp[-1]);
	    add_as_subtype(stack_type((yyval)), stack_type((yyvsp[0])));
	  }
#line 3607 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 730 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 3613 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 732 "parser.y" /* yacc.c:1646  */
    {
	    (yyval)=(yyvsp[-1]);
	    add_as_subtype(stack_type((yyval)), stack_type((yyvsp[0])));
	  }
#line 3622 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 740 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_array);
		  stack_type((yyval)).subtype().make_nil();
		  exprt &range=static_cast<exprt &>(stack_type((yyval)).add(ID_range));
		  range.copy_to_operands(stack((yyvsp[-3])), stack((yyvsp[-1]))); }
#line 3631 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 749 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_array);
		  stack_type((yyval)).subtype().make_nil();
		  exprt &range=static_cast<exprt &>(stack_type((yyval)).add(ID_range));
		  range.copy_to_operands(stack((yyvsp[-3])), stack((yyvsp[-1]))); }
#line 3640 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 754 "parser.y" /* yacc.c:1646  */
    {
	  (yyval)=(yyvsp[-1]);
	}
#line 3648 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 760 "parser.y" /* yacc.c:1646  */
    { init((yyval), "unsized"); }
#line 3654 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 764 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_struct); }
#line 3660 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 765 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_union); }
#line 3666 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 769 "parser.y" /* yacc.c:1646  */
    { new_symbol((yyval), (yyvsp[0])); }
#line 3672 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 846 "parser.y" /* yacc.c:1646  */
    {
            PARSER.parse_tree.create_module(
              stack((yyvsp[-3])).operands()[0],
              stack((yyvsp[-3])).operands()[1],
              stack((yyvsp[-3])).operands()[2],
              stack((yyvsp[-3])).operands()[4],
              stack((yyvsp[-2])));
          }
#line 3685 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 855 "parser.y" /* yacc.c:1646  */
    {
            PARSER.parse_tree.create_module(
              stack((yyvsp[-3])).operands()[0],
              stack((yyvsp[-3])).operands()[1],
              stack((yyvsp[-3])).operands()[2],
              stack((yyvsp[-3])).operands()[4],
              stack((yyvsp[-2])));
          }
#line 3698 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 880 "parser.y" /* yacc.c:1646  */
    { 
            init((yyval)); stack((yyval)).operands().resize(5);
            stack((yyval)).operands()[0].swap(stack((yyvsp[-5])));
            stack((yyval)).operands()[1].swap(stack((yyvsp[-4])));
            stack((yyval)).operands()[2].swap(stack((yyvsp[-3])));
            stack((yyval)).operands()[3].swap(stack((yyvsp[-2])));
            stack((yyval)).operands()[4].swap(stack((yyvsp[-1])));
          }
#line 3711 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 896 "parser.y" /* yacc.c:1646  */
    { 
            init((yyval)); stack((yyval)).operands().resize(5);
            stack((yyval)).operands()[0].swap(stack((yyvsp[-5])));
            stack((yyval)).operands()[1].swap(stack((yyvsp[-4])));
            stack((yyval)).operands()[2].swap(stack((yyvsp[-3])));
            stack((yyval)).operands()[3].swap(stack((yyvsp[-2])));
            stack((yyval)).operands()[4].swap(stack((yyvsp[-1])));
          }
#line 3724 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 906 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); }
#line 3730 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 911 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 3736 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 917 "parser.y" /* yacc.c:1646  */
    { init((yyval)); }
#line 3742 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 921 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_module); }
#line 3748 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 922 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_macromodule); }
#line 3754 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 927 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 3760 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 932 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mts((yyval), (yyvsp[0])); }
#line 3766 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 934 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]); mts((yyval), (yyvsp[0])); }
#line 3772 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 939 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);
		  exprt decl(ID_decl);
		  decl.move_to_operands(stack((yyvsp[0])));
		  // grab the type and class from previous!
		  const irept &prev=stack((yyval)).get_sub().back();
                  decl.set(ID_type, prev.find(ID_type));
                  decl.set(ID_class, prev.find(ID_class));
		  stack((yyval)).move_to_sub(decl);
		}
#line 3786 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 951 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 3792 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 952 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 3798 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 953 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 3804 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 958 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_input);
                  addswap((yyval), ID_type, (yyvsp[-1]));
                  mto((yyval), (yyvsp[0])); }
#line 3813 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 966 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_output);
                  addswap((yyval), ID_type, (yyvsp[-1]));
                  mto((yyval), (yyvsp[0])); }
#line 3822 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 971 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_output_register);
                  addswap((yyval), ID_type, (yyvsp[-1]));
                  mto((yyval), (yyvsp[0])); }
#line 3831 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 979 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_inout);
                  addswap((yyval), ID_type, (yyvsp[-1]));
                  mto((yyval), (yyvsp[0])); }
#line 3840 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 987 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mts((yyval), (yyvsp[0])); }
#line 3846 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 989 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mts((yyval), (yyvsp[0])); }
#line 3852 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 993 "parser.y" /* yacc.c:1646  */
    { if(stack((yyvsp[0])).is_nil())
		    (yyval)=(yyvsp[0]);
		  else { init((yyval), ID_decl);  mto((yyval), (yyvsp[0])); }
		}
#line 3861 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 998 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
		  make_nil((yyval)); /* Not supported */ }
#line 3868 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 1004 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 3874 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 1010 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); /* Not supported */ }
#line 3880 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 1011 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); /* Not supported */ }
#line 3886 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 1016 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_bit_select); mto((yyval), (yyvsp[-1])); }
#line 3892 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 1021 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_part_select); mto((yyval), (yyvsp[-3])); mto((yyval), (yyvsp[-1])); }
#line 3898 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 1026 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_indexed_part_select_plus); mto((yyval), (yyvsp[-3])); mto((yyval), (yyvsp[-1])); }
#line 3904 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 1028 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_indexed_part_select_minus); mto((yyval), (yyvsp[-3])); mto((yyval), (yyvsp[-1])); }
#line 3910 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 1032 "parser.y" /* yacc.c:1646  */
    { new_symbol((yyval), (yyvsp[0])); }
#line 3916 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 1039 "parser.y" /* yacc.c:1646  */
    { init((yyval)); }
#line 3922 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 1041 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); mts((yyval), (yyvsp[0])); }
#line 3928 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 1055 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 3934 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 1056 "parser.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]); }
#line 3940 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 1069 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_generate_block); swapop((yyval), (yyvsp[-1])); }
#line 3946 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 1074 "parser.y" /* yacc.c:1646  */
    { init((yyval)); }
#line 3952 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 1076 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); mto((yyval), (yyvsp[0])); }
#line 3958 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 1089 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_generate_skip); }
#line 3964 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 1094 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_generate_if); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 3970 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 1096 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_generate_if); mto((yyval), (yyvsp[-4])); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 3976 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 1104 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_generate_case); mto((yyval), (yyvsp[-3])); }
#line 3982 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 1123 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_generate_for);
          	  stack((yyval)).reserve_operands(4);
          	  mto((yyval), (yyvsp[-6]));
          	  mto((yyval), (yyvsp[-4]));
          	  mto((yyval), (yyvsp[-2]));
          	  mto((yyval), (yyvsp[0]));
          	}
#line 3994 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1136 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_generate_assign); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 4000 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1141 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_generate_block); }
#line 4006 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1143 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_generate_block); stack((yyval)).operands().swap(stack((yyvsp[-1])).operands()); }
#line 4012 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1147 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4018 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1148 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4024 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1149 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4030 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1153 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4036 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 1155 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4042 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 1156 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4048 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 1157 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4054 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 1159 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4060 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 1160 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4066 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 1161 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4072 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 1162 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4078 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 1163 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4084 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 1164 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4090 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 1192 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl); stack((yyval)).set(ID_class, ID_genvar); swapop((yyval), (yyvsp[-1])); }
#line 4096 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 1197 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4102 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 1199 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 4108 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 1203 "parser.y" /* yacc.c:1646  */
    { new_symbol((yyval), (yyvsp[0])); }
#line 4114 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 1208 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_parameter_decl); swapop((yyval), (yyvsp[-1])); }
#line 4120 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 1210 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_local_parameter_decl); swapop((yyval), (yyvsp[-1])); }
#line 4126 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 1215 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4132 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 1217 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 4138 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 1221 "parser.y" /* yacc.c:1646  */
    { // $1 and $2 implement Verilog 2000 sized parameters,
		  // which can be ignored
		  init((yyval), ID_parameter);
		  addswap((yyval), ID_identifier, (yyvsp[-2]));
		  addswap((yyval), ID_value, (yyvsp[0])); }
#line 4148 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 1237 "parser.y" /* yacc.c:1646  */
    {
                  (yyval)=(yyvsp[0]);
                  add_as_subtype(stack_type((yyval)), stack_type((yyvsp[-1])));
                }
#line 4157 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 1245 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_input);
                  addswap((yyval), ID_type, (yyvsp[-1]));
                  swapop((yyval), (yyvsp[0])); }
#line 4166 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 1253 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_output);
                  addswap((yyval), ID_type, (yyvsp[-1]));
                  swapop((yyval), (yyvsp[0])); }
#line 4175 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 1258 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_output_register);
                  addswap((yyval), ID_type, (yyvsp[-1]));
                  swapop((yyval), (yyvsp[0])); }
#line 4184 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 1266 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_inout);
                  addswap((yyval), ID_type, (yyvsp[-1]));
                  swapop((yyval), (yyvsp[0])); }
#line 4193 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 1273 "parser.y" /* yacc.c:1646  */
    {
                  (yyval)=(yyvsp[0]);
                  add_as_subtype(stack_type((yyval)), stack_type((yyvsp[-1])));
                  // the net type is ignored right now
                }
#line 4203 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 1282 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_nil); }
#line 4209 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 1289 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_trireg); }
#line 4215 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 1293 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 4221 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 1298 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_signed); }
#line 4227 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 1299 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_unsigned); }
#line 4233 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 1304 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 4239 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 1306 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_automatic); }
#line 4245 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 1311 "parser.y" /* yacc.c:1646  */
    { init((yyval)); stack((yyvsp[-1])).type().swap(stack((yyvsp[0]))); mto((yyval), (yyvsp[-1])); }
#line 4251 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 1313 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-3]);    stack((yyvsp[-1])).type().swap(stack((yyvsp[0]))); mto((yyval), (yyvsp[-1])); }
#line 4257 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 1318 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
		  stack((yyval)).set(ID_class, ID_reg);
                  addswap((yyval), ID_type, (yyvsp[-2]));
		  swapop((yyval), (yyvsp[-1])); }
#line 4266 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 1326 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_equal); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 4272 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 1332 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4278 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 1334 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 4284 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 1339 "parser.y" /* yacc.c:1646  */
    { 
            (yyval)=(yyvsp[-1]);
            stack((yyval)).add(ID_type)=stack((yyvsp[0]));
          }
#line 4293 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 1346 "parser.y" /* yacc.c:1646  */
    { new_symbol((yyval), (yyvsp[0])); }
#line 4299 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 1354 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 4305 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 1362 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl); stack((yyval)).set(ID_class, ID_integer); swapop((yyval), (yyvsp[-1])); }
#line 4311 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 1367 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl); stack((yyval)).set(ID_class, ID_realtime); swapop((yyval), (yyvsp[-1])); }
#line 4317 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 1372 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl); stack((yyval)).set(ID_class, ID_realtime); swapop((yyval), (yyvsp[-1])); }
#line 4323 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 1377 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4329 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 1379 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 4335 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 1384 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  addswap((yyval), ID_class, (yyvsp[-6]));
                  addswap((yyval), ID_type, (yyvsp[-3]));
                  swapop((yyval), (yyvsp[-1])); }
#line 4344 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 1389 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  addswap((yyval), ID_class, (yyvsp[-6]));
                  addswap((yyval), ID_type, (yyvsp[-3]));
                  swapop((yyval), (yyvsp[-1])); }
#line 4353 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 1397 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 4359 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 1398 "parser.y" /* yacc.c:1646  */
    { init((yyval), "vectored"); }
#line 4365 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 1399 "parser.y" /* yacc.c:1646  */
    { init((yyval), "scalared"); }
#line 4371 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 1402 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_wire); }
#line 4377 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 1403 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_tri); }
#line 4383 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 1404 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_tri1); }
#line 4389 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 1405 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_supply0); }
#line 4395 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 1406 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_wand); }
#line 4401 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 1407 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_triand); }
#line 4407 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 1408 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_tri0); }
#line 4413 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 1409 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_supply1); }
#line 4419 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 1410 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_wor); }
#line 4425 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 1411 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_trior); }
#line 4431 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 1422 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4437 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 1424 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 4443 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 1428 "parser.y" /* yacc.c:1646  */
    {
            (yyval)=(yyvsp[-1]);
            stack((yyval)).add(ID_type)=stack((yyvsp[0]));
          }
#line 4452 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 1435 "parser.y" /* yacc.c:1646  */
    { new_symbol((yyval), (yyvsp[0])); }
#line 4458 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 1440 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4464 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 1442 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 4470 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 1446 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_equal); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 4476 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 1450 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 4482 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 1454 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4488 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 1455 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); }
#line 4494 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 1456 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-3]); }
#line 4500 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 1457 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-5]); }
#line 4506 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 1468 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_function); 
                  addswap((yyval), ID_signed, (yyvsp[-7]));
		  addswap((yyval), ID_range, (yyvsp[-6]));
		  addswap((yyval), ID_symbol, (yyvsp[-5]));
		  addswap((yyval), ID_ports, (yyvsp[-4]));
		  addswap((yyval), "declarations", (yyvsp[-2]));
		  addswap((yyval), ID_body, (yyvsp[-1]));
		}
#line 4520 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 1481 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 4526 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 1483 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 4532 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 1489 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_integer); }
#line 4538 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 1491 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_real); }
#line 4544 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 1493 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_realtime); }
#line 4550 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 1495 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_time); }
#line 4556 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 1500 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mts((yyval), (yyvsp[0])); }
#line 4562 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 1502 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); mts((yyval), (yyvsp[0])); }
#line 4568 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 1514 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_decl);
                  stack((yyval)).set(ID_class, ID_task); 
		  addswap((yyval), ID_symbol, (yyvsp[-5]));
		  addswap((yyval), ID_ports, (yyvsp[-4]));
		  addswap((yyval), "declarations", (yyvsp[-2]));
		  addswap((yyval), ID_body, (yyvsp[-1]));
                }
#line 4580 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 1525 "parser.y" /* yacc.c:1646  */
    { init((yyval)); }
#line 4586 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 1527 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); mts((yyval), (yyvsp[0])); }
#line 4592 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 1532 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); }
#line 4598 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 1533 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); }
#line 4604 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 273:
#line 1534 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); }
#line 4610 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 274:
#line 1538 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4616 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 275:
#line 1539 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4622 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 1540 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4628 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 1542 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4634 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 1544 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 4640 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 279:
#line 1550 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_verilog_attribute); }
#line 4646 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 280:
#line 1552 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]);
		  Forall_irep(it, stack((yyvsp[0])).get_sub())
		    stack((yyval)).move_to_sub(*it);
		}
#line 4655 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 281:
#line 1559 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); }
#line 4661 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 282:
#line 1564 "parser.y" /* yacc.c:1646  */
    { init((yyval)); }
#line 4667 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 283:
#line 1566 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]); mts((yyval), (yyvsp[0])); }
#line 4673 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 284:
#line 1570 "parser.y" /* yacc.c:1646  */
    { init((yyval), "attribute");
		  stack((yyval)).add(ID_name).swap(stack((yyvsp[-2])));
		  stack((yyval)).add(ID_value).swap(stack((yyvsp[0])));
		}
#line 4682 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 285:
#line 1575 "parser.y" /* yacc.c:1646  */
    { init((yyval), "attribute"); stack((yyval)).add(ID_name).swap(stack((yyvsp[0]))); }
#line 4688 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 289:
#line 1589 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4694 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 290:
#line 1591 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 4700 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 291:
#line 1600 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst_builtin); addswap((yyval), ID_module, (yyvsp[-3])); swapop((yyval), (yyvsp[-1])); }
#line 4706 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 292:
#line 1602 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst_builtin); addswap((yyval), ID_module, (yyvsp[-4])); swapop((yyval), (yyvsp[-1])); }
#line 4712 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 293:
#line 1604 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst_builtin); addswap((yyval), ID_module, (yyvsp[-3])); swapop((yyval), (yyvsp[-1])); }
#line 4718 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 294:
#line 1606 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst_builtin); addswap((yyval), ID_module, (yyvsp[-4])); swapop((yyval), (yyvsp[-1])); }
#line 4724 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 295:
#line 1608 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst_builtin); addswap((yyval), ID_module, (yyvsp[-4])); swapop((yyval), (yyvsp[-1])); }
#line 4730 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 296:
#line 1610 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst_builtin); addswap((yyval), ID_module, (yyvsp[-3])); swapop((yyval), (yyvsp[-1])); }
#line 4736 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 297:
#line 1612 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst_builtin); addswap((yyval), ID_module, (yyvsp[-2])); swapop((yyval), (yyvsp[-1])); }
#line 4742 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 298:
#line 1614 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst_builtin); stack((yyval)).set(ID_module, ID_pulldown); swapop((yyval), (yyvsp[-1])); }
#line 4748 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 299:
#line 1616 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst_builtin); stack((yyval)).set(ID_module, ID_pullup);   swapop((yyval), (yyvsp[-1])); }
#line 4754 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 300:
#line 1620 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_cmos); }
#line 4760 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 301:
#line 1621 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_rcmos); }
#line 4766 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 302:
#line 1625 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_bufif0); }
#line 4772 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 303:
#line 1626 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_bufif1); }
#line 4778 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 304:
#line 1627 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_notif0); }
#line 4784 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 305:
#line 1628 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_notif1); }
#line 4790 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 306:
#line 1632 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_nmos); }
#line 4796 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 307:
#line 1633 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_pmos); }
#line 4802 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 308:
#line 1634 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_rnmos); }
#line 4808 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 309:
#line 1635 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_rpmos); }
#line 4814 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 310:
#line 1639 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_and); }
#line 4820 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 311:
#line 1640 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_nand); }
#line 4826 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 312:
#line 1641 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_nor); }
#line 4832 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 313:
#line 1642 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_or); }
#line 4838 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 314:
#line 1643 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_nor); }
#line 4844 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 315:
#line 1644 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_xor); }
#line 4850 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 316:
#line 1648 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_buf); }
#line 4856 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 317:
#line 1649 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_not); }
#line 4862 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 318:
#line 1653 "parser.y" /* yacc.c:1646  */
    { init((yyval), "rtran"); }
#line 4868 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 319:
#line 1654 "parser.y" /* yacc.c:1646  */
    { init((yyval), "rtranif0"); }
#line 4874 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 320:
#line 1655 "parser.y" /* yacc.c:1646  */
    { init((yyval), "rtranif0"); }
#line 4880 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 321:
#line 1656 "parser.y" /* yacc.c:1646  */
    { init((yyval), "rtranif1"); }
#line 4886 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 322:
#line 1660 "parser.y" /* yacc.c:1646  */
    { init((yyval), "tranif0"); }
#line 4892 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 323:
#line 1661 "parser.y" /* yacc.c:1646  */
    { init((yyval), "tranif1"); }
#line 4898 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 324:
#line 1666 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4904 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 325:
#line 1668 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 4910 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 326:
#line 1673 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst); addswap((yyval), ID_instance, (yyvsp[-4]));
                  swapop((yyval), (yyvsp[-1]));
                  addswap((yyval), ID_range, (yyvsp[-3]));
                }
#line 4919 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 327:
#line 1681 "parser.y" /* yacc.c:1646  */
    { init((yyval), "$_&#ANON" + PARSER.get_dummy_id()); }
#line 4925 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 330:
#line 1693 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst);
                  addswap((yyval), ID_module, (yyvsp[-3]));
		  addswap((yyval), ID_parameter_assignments, (yyvsp[-2]));
                  swapop((yyval), (yyvsp[-1])); }
#line 4934 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 331:
#line 1701 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 4940 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 332:
#line 1703 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 4946 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 335:
#line 1713 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4952 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 336:
#line 1715 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]); mto((yyval), (yyvsp[0])); }
#line 4958 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 337:
#line 1720 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4964 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 338:
#line 1722 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]); mto((yyval), (yyvsp[0])); }
#line 4970 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 340:
#line 1730 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_named_parameter_assignment);
	  	  stack((yyval)).add(ID_parameter).swap(stack((yyvsp[-3])));
	  	  stack((yyval)).add(ID_value).swap(stack((yyvsp[-1])));
	  	}
#line 4979 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 342:
#line 1740 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 4985 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 343:
#line 1742 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 4991 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 344:
#line 1747 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_inst); addswap((yyval), ID_instance, (yyvsp[-3])); swapop((yyval), (yyvsp[-1])); }
#line 4997 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 345:
#line 1750 "parser.y" /* yacc.c:1646  */
    { init((yyval), "$_&#ANON" + PARSER.get_dummy_id());}
#line 5003 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 350:
#line 1767 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 5009 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 351:
#line 1769 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 5015 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 353:
#line 1778 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 5021 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 354:
#line 1780 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 5027 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 355:
#line 1785 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_named_port_connection);
                  mto((yyval), (yyvsp[-3]));
                  mto((yyval), (yyvsp[-1])); }
#line 5035 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 356:
#line 1796 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_continuous_assign); swapop((yyval), (yyvsp[-1])); }
#line 5041 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 357:
#line 1801 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 5047 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 358:
#line 1803 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 5053 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 359:
#line 1807 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_equal); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5059 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 361:
#line 1813 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_initial); mto((yyval), (yyvsp[0])); }
#line 5065 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 362:
#line 1817 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_always); mto((yyval), (yyvsp[0])); }
#line 5071 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 363:
#line 1825 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 5077 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 369:
#line 1834 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 5083 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 370:
#line 1835 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 5089 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 385:
#line 1854 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); }
#line 5095 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 388:
#line 1864 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_function_call);
		  stack((yyval)).operands().reserve(2);
		  mto((yyval), (yyvsp[-3])); mto((yyval), (yyvsp[-1])); }
#line 5103 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 389:
#line 1871 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_function_call);
		  stack((yyval)).operands().resize(2);
		  stack((yyval)).operands()[0].swap(stack((yyvsp[0]))); }
#line 5111 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 390:
#line 1875 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_function_call);
		  stack((yyval)).operands().reserve(2);
		  mto((yyval), (yyvsp[-3])); mto((yyval), (yyvsp[-1])); }
#line 5119 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 392:
#line 1883 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_skip); }
#line 5125 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 395:
#line 1893 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_fork); swapop((yyval), (yyvsp[-1])); }
#line 5131 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 396:
#line 1896 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_block);
                  swapop((yyval), (yyvsp[-1]));
                  addswap((yyval), ID_identifier, (yyvsp[-2])); }
#line 5139 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 397:
#line 1903 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_disable); mto((yyval), (yyvsp[-1])); }
#line 5145 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 398:
#line 1908 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_assert); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5151 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 399:
#line 1911 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_assert); stack((yyval)).operands().resize(2);
		  stack((yyval)).op0().swap(stack((yyvsp[-1]))); stack((yyval)).op1().make_nil();
		  stack((yyval)).set(ID_identifier, stack((yyvsp[-3])).id());
		}
#line 5160 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 400:
#line 1917 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_assume); stack((yyval)).operands().resize(2);
		  stack((yyval)).op0().swap(stack((yyvsp[-1]))); stack((yyval)).op1().make_nil();
		  stack((yyval)).set(ID_identifier, stack((yyvsp[-3])).id());
		}
#line 5169 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 402:
#line 1926 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_cover); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5175 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 404:
#line 1932 "parser.y" /* yacc.c:1646  */
    { init((yyval), "action-else"); stack((yyval)).operands().resize(2);
                  stack((yyval)).op0().swap(stack((yyvsp[-3]))); stack((yyval)).op1().swap(stack((yyvsp[-1]))); }
#line 5182 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 406:
#line 1939 "parser.y" /* yacc.c:1646  */
    { 
		  (yyval)=(yyvsp[0]);
		  stack((yyval)).set(ID_identifier, stack((yyvsp[-2])).id());
		}
#line 5191 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 408:
#line 1947 "parser.y" /* yacc.c:1646  */
    { 
		  (yyval)=(yyvsp[0]);
		  stack((yyval)).set(ID_identifier, stack((yyvsp[-2])).id());
		}
#line 5200 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 409:
#line 1954 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_assert); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5206 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 412:
#line 1962 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_wait); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5212 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 413:
#line 1967 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_continuous_assign); mto((yyval), (yyvsp[0])); }
#line 5218 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 414:
#line 1969 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_deassign); mto((yyval), (yyvsp[0])); }
#line 5224 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 415:
#line 1971 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_force); swapop((yyval), (yyvsp[0])); }
#line 5230 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 416:
#line 1974 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_release); mto((yyval), (yyvsp[0])); }
#line 5236 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 417:
#line 1980 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_blocking_assign); mto((yyval), (yyvsp[-3])); mto((yyval), (yyvsp[0])); }
#line 5242 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 419:
#line 1986 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_blocking_assign); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5248 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 433:
#line 2007 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_non_blocking_assign); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5254 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 434:
#line 2009 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_non_blocking_assign); mto((yyval), (yyvsp[-3])); mto((yyval), (yyvsp[0])); }
#line 5260 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 435:
#line 2014 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); mto((yyval), (yyvsp[0])); }
#line 5266 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 439:
#line 2025 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_verilog_cycle_delay); mto((yyval), (yyvsp[0])); }
#line 5272 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 440:
#line 2027 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_verilog_cycle_delay); mto((yyval), (yyvsp[0])); }
#line 5278 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 441:
#line 2029 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_verilog_cycle_delay); mto((yyval), (yyvsp[-1])); }
#line 5284 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 444:
#line 2036 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_repeat); }
#line 5290 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 445:
#line 2041 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_delay); mto((yyval), (yyvsp[0])); }
#line 5296 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 446:
#line 2045 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_delay); mto((yyval), (yyvsp[-2])); }
#line 5302 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 447:
#line 2050 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_event_guard); mto((yyval), (yyvsp[0])); }
#line 5308 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 448:
#line 2052 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_event_guard); mto((yyval), (yyvsp[-1])); }
#line 5314 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 449:
#line 2054 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_event_guard);
		  stack((yyval)).operands().resize(1);
	          stack((yyval)).op0().id(ID_verilog_star_event); }
#line 5322 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 450:
#line 2058 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_event_guard);
		  stack((yyval)).operands().resize(1);
	          stack((yyval)).op0().id(ID_verilog_star_event); }
#line 5330 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 451:
#line 2062 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_event_guard);
		  stack((yyval)).operands().resize(1);
	          stack((yyval)).op0().id(ID_verilog_star_event); }
#line 5338 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 452:
#line 2069 "parser.y" /* yacc.c:1646  */
    { new_symbol((yyval), (yyvsp[0])); }
#line 5344 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 453:
#line 2074 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_event); mto((yyval), (yyvsp[0])); }
#line 5350 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 454:
#line 2076 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]); mto((yyval), (yyvsp[0])); }
#line 5356 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 455:
#line 2078 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]); mto((yyval), (yyvsp[0])); }
#line 5362 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 456:
#line 2083 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 5368 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 457:
#line 2085 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_posedge); mto((yyval), (yyvsp[0])); }
#line 5374 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 458:
#line 2087 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_negedge); mto((yyval), (yyvsp[0])); }
#line 5380 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 459:
#line 2092 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_if); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5386 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 460:
#line 2094 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_if); mto((yyval), (yyvsp[-4])); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5392 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 461:
#line 2099 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_case);  mto((yyval), (yyvsp[-3]));
                  Forall_operands(it, stack((yyvsp[-1]))) stack((yyval)).move_to_operands(*it); }
#line 5399 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 462:
#line 2102 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_casex); mto((yyval), (yyvsp[-3]));
                  Forall_operands(it, stack((yyvsp[-1]))) stack((yyval)).move_to_operands(*it); }
#line 5406 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 463:
#line 2105 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_casez); mto((yyval), (yyvsp[-3]));
                  Forall_operands(it, stack((yyvsp[-1]))) stack((yyval)).move_to_operands(*it); }
#line 5413 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 464:
#line 2111 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 5419 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 465:
#line 2113 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); mto((yyval), (yyvsp[0])); }
#line 5425 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 466:
#line 2118 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_case_item); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5431 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 467:
#line 2120 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_case_item);
                  stack((yyval)).operands().resize(1);
                  stack((yyval)).op0().id(ID_default);
                  mto((yyval), (yyvsp[0])); }
#line 5440 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 468:
#line 2125 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_case_item);
                  stack((yyval)).operands().resize(1);
                  stack((yyval)).op0().id(ID_default);
                  mto((yyval), (yyvsp[0])); }
#line 5449 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 469:
#line 2133 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_forever); mto((yyval), (yyvsp[0])); }
#line 5455 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 470:
#line 2135 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_repeat); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5461 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 471:
#line 2137 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_while); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5467 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 472:
#line 2139 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_for); mto((yyval), (yyvsp[-6])); mto((yyval), (yyvsp[-4])); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5473 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 477:
#line 2155 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_block); swapop((yyval), (yyvsp[-1])); }
#line 5479 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 478:
#line 2158 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_block);
                  swapop((yyval), (yyvsp[-1]));
                  addswap((yyval), ID_identifier, (yyvsp[-2])); }
#line 5487 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 480:
#line 2181 "parser.y" /* yacc.c:1646  */
    { init((yyval)); }
#line 5493 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 481:
#line 2183 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); mto((yyval), (yyvsp[0])); }
#line 5499 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 483:
#line 2190 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_symbol);
                  stack((yyval)).set(ID_identifier, stack((yyvsp[0])).id());
                }
#line 5507 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 486:
#line 2204 "parser.y" /* yacc.c:1646  */
    { extractbits((yyval), (yyvsp[-1]), (yyvsp[0])); }
#line 5513 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 487:
#line 2206 "parser.y" /* yacc.c:1646  */
    { extractbits((yyval), (yyvsp[-1]), (yyvsp[0])); }
#line 5519 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 490:
#line 2225 "parser.y" /* yacc.c:1646  */
    { extractbit((yyval), (yyvsp[-1]), (yyvsp[0])); }
#line 5525 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 492:
#line 2231 "parser.y" /* yacc.c:1646  */
    { new_symbol((yyval), (yyvsp[0])); }
#line 5531 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 495:
#line 2239 "parser.y" /* yacc.c:1646  */
    { init((yyval), "mintypmax"); mto((yyval), (yyvsp[-4])); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5537 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 496:
#line 2244 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 5543 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 498:
#line 2250 "parser.y" /* yacc.c:1646  */
    { init((yyval)); mto((yyval), (yyvsp[0])); }
#line 5549 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 499:
#line 2252 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]);    mto((yyval), (yyvsp[0])); }
#line 5555 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 501:
#line 2258 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-2]); mto((yyval), (yyvsp[0])); }
#line 5561 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 503:
#line 2261 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_plus); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5567 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 504:
#line 2263 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_minus); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5573 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 505:
#line 2265 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_unary_plus); mto((yyval), (yyvsp[0])); }
#line 5579 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 506:
#line 2267 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_unary_minus); mto((yyval), (yyvsp[0])); }
#line 5585 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 507:
#line 2269 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_mult); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5591 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 508:
#line 2271 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_div); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5597 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 509:
#line 2273 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_mod); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5603 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 510:
#line 2275 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_equal); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5609 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 511:
#line 2277 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_notequal); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5615 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 512:
#line 2279 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_verilog_case_equality); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5621 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 513:
#line 2281 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_verilog_case_inequality); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5627 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 514:
#line 2283 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_and); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5633 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 515:
#line 2285 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_or); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5639 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 516:
#line 2287 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_lt); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5645 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 517:
#line 2289 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_le); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5651 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 518:
#line 2291 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_gt); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5657 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 519:
#line 2293 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_ge); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5663 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 520:
#line 2295 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_bitand); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5669 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 521:
#line 2297 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_bitor); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5675 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 522:
#line 2299 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_bitxor); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5681 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 523:
#line 2301 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_bitxnor); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5687 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 524:
#line 2303 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_shl); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5693 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 525:
#line 2305 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_shl); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5699 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 526:
#line 2307 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_lshr); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5705 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 527:
#line 2312 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_shr); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5711 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 528:
#line 2314 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_if); mto((yyval), (yyvsp[-4])); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5717 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 529:
#line 2316 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_constant); stack((yyval)).type()=typet(ID_string); addswap((yyval), ID_value, (yyvsp[0])); }
#line 5723 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 531:
#line 2322 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_not); mto((yyval), (yyvsp[0])); }
#line 5729 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 532:
#line 2323 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_or); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5735 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 533:
#line 2324 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_and); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5741 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 534:
#line 2325 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_overlapped_implication); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5747 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 535:
#line 2326 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_non_overlapped_implication); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5753 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 536:
#line 2328 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); }
#line 5759 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 537:
#line 2329 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_always"); mto((yyval), (yyvsp[0])); }
#line 5765 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 538:
#line 2330 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_eventually"); mto((yyval), (yyvsp[0])); }
#line 5771 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 539:
#line 2331 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_nexttime"); mto((yyval), (yyvsp[0])); }
#line 5777 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 540:
#line 2332 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_s_always"); mto((yyval), (yyvsp[0])); }
#line 5783 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 541:
#line 2333 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_s_eventually"); mto((yyval), (yyvsp[0])); }
#line 5789 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 542:
#line 2334 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_s_nexttime"); mto((yyval), (yyvsp[0])); }
#line 5795 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 543:
#line 2335 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_s_until"); mto((yyval), (yyvsp[0])); }
#line 5801 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 544:
#line 2336 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_s_until_with"); mto((yyval), (yyvsp[0])); }
#line 5807 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 545:
#line 2337 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_until"); mto((yyval), (yyvsp[0])); }
#line 5813 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 546:
#line 2338 "parser.y" /* yacc.c:1646  */
    { init((yyval), "SV_until_with"); mto((yyval), (yyvsp[0])); }
#line 5819 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 548:
#line 2344 "parser.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[-1]); mto((yyval), (yyvsp[0])); }
#line 5825 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 549:
#line 2346 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_sva_sequence_concatenation); mto((yyval), (yyvsp[-2])); mto((yyvsp[-1]), (yyvsp[0])); mto((yyval), (yyvsp[-1])); }
#line 5831 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 550:
#line 2348 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_sva_sequence_first_match); mto((yyval), (yyvsp[-1])); }
#line 5837 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 551:
#line 2350 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_sva_sequence_throughout); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[0])); }
#line 5843 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 552:
#line 2355 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_sva_cycle_delay); mto((yyval), (yyvsp[0])); stack((yyval)).operands().push_back(nil_exprt()); }
#line 5849 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 553:
#line 2357 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_sva_cycle_delay); mto((yyval), (yyvsp[-3])); mto((yyval), (yyvsp[-1])); }
#line 5855 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 554:
#line 2359 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_sva_cycle_delay); mto((yyval), (yyvsp[-3])); stack((yyval)).copy_to_operands(exprt(ID_infinity)); }
#line 5861 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 555:
#line 2363 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_bitnot); }
#line 5867 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 556:
#line 2364 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_not); }
#line 5873 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 557:
#line 2365 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_reduction_and); }
#line 5879 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 558:
#line 2366 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_reduction_nand); }
#line 5885 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 559:
#line 2367 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_reduction_or); }
#line 5891 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 560:
#line 2368 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_reduction_nor); }
#line 5897 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 561:
#line 2369 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_reduction_xor); }
#line 5903 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 562:
#line 2370 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_reduction_xnor); }
#line 5909 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 563:
#line 2371 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_reduction_xnor); }
#line 5915 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 564:
#line 2376 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_preincrement); mto((yyval), (yyvsp[0])); }
#line 5921 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 565:
#line 2378 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_predecrement); mto((yyval), (yyvsp[0])); }
#line 5927 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 566:
#line 2380 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_postincrement); mto((yyval), (yyvsp[-2])); }
#line 5933 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 567:
#line 2382 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_postdecrement); mto((yyval), (yyvsp[-2])); }
#line 5939 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 570:
#line 2388 "parser.y" /* yacc.c:1646  */
    { extractbits((yyval), (yyvsp[-1]), (yyvsp[0])); }
#line 5945 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 571:
#line 2390 "parser.y" /* yacc.c:1646  */
    { extractbits((yyval), (yyvsp[-1]), (yyvsp[0])); }
#line 5951 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 575:
#line 2395 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 5957 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 576:
#line 2396 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_NULL); }
#line 5963 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 578:
#line 2404 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_constant); addswap((yyval), ID_value, (yyvsp[0])); }
#line 5969 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 579:
#line 2408 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_concatenation); swapop((yyval), (yyvsp[-1])); }
#line 5975 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 580:
#line 2413 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_replication); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[-1])); }
#line 5981 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 581:
#line 2415 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_replication); mto((yyval), (yyvsp[-2])); mto((yyval), (yyvsp[-1])); }
#line 5987 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 586:
#line 2441 "parser.y" /* yacc.c:1646  */
    { init((yyval), ID_hierarchical_identifier);
		  stack((yyval)).reserve_operands(2);
		  mto((yyval), (yyvsp[-2]));
		  mto((yyval), (yyvsp[0]));
		}
#line 5997 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 587:
#line 2449 "parser.y" /* yacc.c:1646  */
    { new_symbol((yyval), (yyvsp[0])); }
#line 6003 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 588:
#line 2453 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 6009 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 589:
#line 2466 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 6015 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;

  case 590:
#line 2479 "parser.y" /* yacc.c:1646  */
    { make_nil((yyval)); }
#line 6021 "verilog_y.tab.cpp" /* yacc.c:1646  */
    break;


#line 6025 "verilog_y.tab.cpp" /* yacc.c:1646  */
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
#line 2611 "parser.y" /* yacc.c:1906  */

