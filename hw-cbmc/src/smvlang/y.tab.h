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

#ifndef YY_YYSMV_Y_TAB_HPP_INCLUDED
# define YY_YYSMV_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yysmvdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    AG_Token = 258,
    AX_Token = 259,
    AF_Token = 260,
    INIT_Token = 261,
    TRANS_Token = 262,
    SPEC_Token = 263,
    VAR_Token = 264,
    DEFINE_Token = 265,
    ASSIGN_Token = 266,
    INVAR_Token = 267,
    FAIRNESS_Token = 268,
    MODULE_Token = 269,
    ARRAY_Token = 270,
    OF_Token = 271,
    DOTDOT_Token = 272,
    BOOLEAN_Token = 273,
    EXTERN_Token = 274,
    NEXT_Token = 275,
    INC_Token = 276,
    DEC_Token = 277,
    CASE_Token = 278,
    ESAC_Token = 279,
    BECOMES_Token = 280,
    ADD_Token = 281,
    SUB_Token = 282,
    SWITCH_Token = 283,
    init_Token = 284,
    PLUS_Token = 285,
    STRING_Token = 286,
    QSTRING_Token = 287,
    QUOTE_Token = 288,
    NUMBER_Token = 289,
    IMPLIES_Token = 290,
    UNION_Token = 291,
    EQUIV_Token = 292,
    XOR_Token = 293,
    OR_Token = 294,
    AND_Token = 295,
    NOT_Token = 296,
    EX_Token = 297,
    EF_Token = 298,
    EG_Token = 299,
    E_Token = 300,
    A_Token = 301,
    UNTIL_Token = 302,
    EQUAL_Token = 303,
    NOTEQUAL_Token = 304,
    LT_Token = 305,
    GT_Token = 306,
    LE_Token = 307,
    GE_Token = 308,
    MINUS_Token = 309,
    TIMES_Token = 310,
    DIVIDE_Token = 311,
    UMINUS = 312,
    DOT_Token = 313
  };
#endif
/* Tokens.  */
#define AG_Token 258
#define AX_Token 259
#define AF_Token 260
#define INIT_Token 261
#define TRANS_Token 262
#define SPEC_Token 263
#define VAR_Token 264
#define DEFINE_Token 265
#define ASSIGN_Token 266
#define INVAR_Token 267
#define FAIRNESS_Token 268
#define MODULE_Token 269
#define ARRAY_Token 270
#define OF_Token 271
#define DOTDOT_Token 272
#define BOOLEAN_Token 273
#define EXTERN_Token 274
#define NEXT_Token 275
#define INC_Token 276
#define DEC_Token 277
#define CASE_Token 278
#define ESAC_Token 279
#define BECOMES_Token 280
#define ADD_Token 281
#define SUB_Token 282
#define SWITCH_Token 283
#define init_Token 284
#define PLUS_Token 285
#define STRING_Token 286
#define QSTRING_Token 287
#define QUOTE_Token 288
#define NUMBER_Token 289
#define IMPLIES_Token 290
#define UNION_Token 291
#define EQUIV_Token 292
#define XOR_Token 293
#define OR_Token 294
#define AND_Token 295
#define NOT_Token 296
#define EX_Token 297
#define EF_Token 298
#define EG_Token 299
#define E_Token 300
#define A_Token 301
#define UNTIL_Token 302
#define EQUAL_Token 303
#define NOTEQUAL_Token 304
#define LT_Token 305
#define GT_Token 306
#define LE_Token 307
#define GE_Token 308
#define MINUS_Token 309
#define TIMES_Token 310
#define DIVIDE_Token 311
#define UMINUS 312
#define DOT_Token 313

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yysmvlval;

int yysmvparse (void);

#endif /* !YY_YYSMV_Y_TAB_HPP_INCLUDED  */
