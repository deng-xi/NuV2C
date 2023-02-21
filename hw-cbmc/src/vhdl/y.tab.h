/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
