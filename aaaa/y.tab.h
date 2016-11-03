/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KW_INT = 258,
     KW_FLOAT = 259,
     KW_BOOL = 260,
     KW_CHAR = 261,
     KW_IF = 262,
     KW_THEN = 263,
     KW_ELSE = 264,
     KW_FOR = 265,
     KW_TO = 266,
     KW_READ = 267,
     KW_RETURN = 268,
     KW_PRINT = 269,
     OPERATOR_LE = 270,
     OPERATOR_GE = 271,
     OPERATOR_EQ = 272,
     OPERATOR_NE = 273,
     OPERATOR_AND = 274,
     OPERATOR_OR = 275,
     OPERATOR_L = 276,
     OPERATOR_G = 277,
     OPERATOR_ATTR = 278,
     OPERATOR_MUL = 279,
     OPERATOR_DIV = 280,
     OPERATOR_SUB = 281,
     OPERATOR_ADD = 282,
     TK_IDENTIFIER = 283,
     LIT_INTEGER = 284,
     LIT_FALSE = 285,
     LIT_TRUE = 286,
     LIT_CHAR = 287,
     LIT_STRING = 288,
     TOKEN_ERROR = 289,
     IF_SIMPLE = 290,
     EXPRESSION = 291
   };
#endif
/* Tokens.  */
#define KW_INT 258
#define KW_FLOAT 259
#define KW_BOOL 260
#define KW_CHAR 261
#define KW_IF 262
#define KW_THEN 263
#define KW_ELSE 264
#define KW_FOR 265
#define KW_TO 266
#define KW_READ 267
#define KW_RETURN 268
#define KW_PRINT 269
#define OPERATOR_LE 270
#define OPERATOR_GE 271
#define OPERATOR_EQ 272
#define OPERATOR_NE 273
#define OPERATOR_AND 274
#define OPERATOR_OR 275
#define OPERATOR_L 276
#define OPERATOR_G 277
#define OPERATOR_ATTR 278
#define OPERATOR_MUL 279
#define OPERATOR_DIV 280
#define OPERATOR_SUB 281
#define OPERATOR_ADD 282
#define TK_IDENTIFIER 283
#define LIT_INTEGER 284
#define LIT_FALSE 285
#define LIT_TRUE 286
#define LIT_CHAR 287
#define LIT_STRING 288
#define TOKEN_ERROR 289
#define IF_SIMPLE 290
#define EXPRESSION 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 66 "parser.y"
{
    HASHCELL* symbol;
    TREENODE* node;
}
/* Line 1529 of yacc.c.  */
#line 126 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

