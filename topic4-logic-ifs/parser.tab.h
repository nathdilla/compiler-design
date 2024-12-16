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
     TYPE = 258,
     ID = 259,
     SEMICOLON = 260,
     LBRACK = 261,
     RBRACK = 262,
     LCURBRACK = 263,
     RCURBRACK = 264,
     LPAREN = 265,
     RPAREN = 266,
     COMMA = 267,
     DOT = 268,
     EQEQ = 269,
     NEQ = 270,
     LT = 271,
     GT = 272,
     LTEQ = 273,
     GTEQ = 274,
     AND = 275,
     OR = 276,
     NOT = 277,
     MOD = 278,
     EQ = 279,
     PLUS = 280,
     MINUS = 281,
     STAR = 282,
     BSLASH = 283,
     BOOL = 284,
     NUMBER = 285,
     FLOAT = 286,
     WRITE = 287,
     RETURN = 288,
     FUNC = 289,
     ARRAY = 290,
     IF = 291,
     ELSE = 292,
     WHILE = 293,
     BREAK = 294
   };
#endif
/* Tokens.  */
#define TYPE 258
#define ID 259
#define SEMICOLON 260
#define LBRACK 261
#define RBRACK 262
#define LCURBRACK 263
#define RCURBRACK 264
#define LPAREN 265
#define RPAREN 266
#define COMMA 267
#define DOT 268
#define EQEQ 269
#define NEQ 270
#define LT 271
#define GT 272
#define LTEQ 273
#define GTEQ 274
#define AND 275
#define OR 276
#define NOT 277
#define MOD 278
#define EQ 279
#define PLUS 280
#define MINUS 281
#define STAR 282
#define BSLASH 283
#define BOOL 284
#define NUMBER 285
#define FLOAT 286
#define WRITE 287
#define RETURN 288
#define FUNC 289
#define ARRAY 290
#define IF 291
#define ELSE 292
#define WHILE 293
#define BREAK 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 42 "parser.y"
{
	int number;
	float fval;
	char character;
	char* string;
	char* operator;
	struct ASTNode* ast;
}
/* Line 1529 of yacc.c.  */
#line 136 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

