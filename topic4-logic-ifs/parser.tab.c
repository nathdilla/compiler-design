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
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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
     EQ = 269,
     PLUS = 270,
     MINUS = 271,
     STAR = 272,
     BSLASH = 273,
     BOOL = 274,
     NUMBER = 275,
     FLOAT = 276,
     WRITE = 277,
     RETURN = 278,
     FUNC = 279,
     ARRAY = 280,
     IF = 281
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
#define EQ 269
#define PLUS 270
#define MINUS 271
#define STAR 272
#define BSLASH 273
#define BOOL 274
#define NUMBER 275
#define FLOAT 276
#define WRITE 277
#define RETURN 278
#define FUNC 279
#define ARRAY 280
#define IF 281




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

	
/*
 * File:        parser.y
 * Author:      Nathan Dilla, Eli Streitmatter, Isac Artzi
 * Date:        October 11, 2024
 * Description: Bison grammar for the C-Minus Minus language.
 * Version:     3.0
 * 
 * This current yacc file can parse the following grammar:
 * 1. Function calls
 * 2. Variable declarations
 * 3. Assignment statements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "symbol_table.h"
#include "semantic.h"
#include "optimizer.h"
#include "code_generator.h"


extern int yylex();
extern int yyparse();
extern FILE* yyin;    // Declare yyin, the file pointer for the input file
extern int yylineno;  // Declare yylineno, the line number counter
extern TAC* tac_head;  // Declare the head of the linked list of TAC entries

void yyerror(const char* s);

#define TABLE_SIZE 100

ASTNode* root = NULL; 
symbol_table* previous_scope = NULL;
symbol_table* current_scope = NULL;


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
typedef union YYSTYPE
#line 41 "parser.y"
{
	int number;
	float fval;
	char character;
	char* string;
	char* operator;
	struct ASTNode* ast;
}
/* Line 193 of yacc.c.  */
#line 197 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 210 "parser.tab.c"

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   81

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  43
/* YYNRULES -- Number of states.  */
#define YYNSTATES  87

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     7,    10,    11,    14,    22,    23,    26,
      30,    31,    34,    38,    39,    46,    47,    49,    53,    56,
      57,    59,    63,    65,    67,    74,    78,    79,    82,    87,
      89,    95,   103,   107,   109,   111,   113,   115,   120,   125,
     127,   129,   131,   133
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      28,     0,    -1,    31,    33,    43,    -1,    31,    43,    -1,
      -1,    30,    29,    -1,    25,     3,     4,     6,    20,     7,
       5,    -1,    -1,    32,    31,    -1,     3,     4,     5,    -1,
      -1,    35,    33,    -1,    24,     3,     4,    -1,    -1,    34,
      36,    10,    37,    11,    41,    -1,    -1,    38,    -1,    38,
      12,    37,    -1,     3,     4,    -1,    -1,    40,    -1,    40,
      12,    39,    -1,     4,    -1,    20,    -1,     8,    31,    29,
      43,    42,     9,    -1,    23,    45,     5,    -1,    -1,    44,
      43,    -1,     4,    14,    45,     5,    -1,    47,    -1,     4,
      10,    39,    11,     5,    -1,     4,     6,    20,     7,    14,
      45,     5,    -1,    45,    46,    45,    -1,     4,    -1,    21,
      -1,    19,    -1,    20,    -1,     4,    10,    39,    11,    -1,
       4,     6,    20,     7,    -1,    15,    -1,    16,    -1,    17,
      -1,    18,    -1,    22,     4,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    87,    87,    95,   105,   106,   116,   133,   134,   145,
     164,   165,   176,   186,   185,   212,   213,   219,   229,   241,
     242,   249,   259,   265,   276,   290,   298,   299,   308,   322,
     325,   332,   345,   353,   359,   369,   375,   383,   390,   401,
     408,   415,   422,   431
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "ID", "SEMICOLON", "LBRACK",
  "RBRACK", "LCURBRACK", "RCURBRACK", "LPAREN", "RPAREN", "COMMA", "DOT",
  "EQ", "PLUS", "MINUS", "STAR", "BSLASH", "BOOL", "NUMBER", "FLOAT",
  "WRITE", "RETURN", "FUNC", "ARRAY", "IF", "$accept", "Program",
  "ArrayDeclList", "ArrayDecl", "VarDeclList", "VarDecl", "FuncDeclList",
  "FuncSignature", "FuncDecl", "@1", "ParamList", "Param",
  "InputParamList", "InputParam", "Block", "ReturnStmt", "StmtList",
  "Stmt", "Expr", "BinOp", "WriteStmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    27,    28,    28,    29,    29,    30,    31,    31,    32,
      33,    33,    34,    36,    35,    37,    37,    37,    38,    39,
      39,    39,    40,    40,    41,    42,    43,    43,    44,    44,
      44,    44,    45,    45,    45,    45,    45,    45,    45,    46,
      46,    46,    46,    47
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,     7,     0,     2,     3,
       0,     2,     3,     0,     6,     0,     1,     3,     2,     0,
       1,     3,     1,     1,     6,     3,     0,     2,     4,     1,
       5,     7,     3,     1,     1,     1,     1,     4,     4,     1,
       1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,     0,     0,    10,     7,     0,     1,     0,     0,     0,
      26,    13,    10,     3,    26,    29,     8,     9,     0,    19,
       0,     0,     0,     2,     0,    11,    27,     0,    22,    23,
       0,    20,    33,    35,    36,    34,     0,    43,    12,    15,
       0,     0,    19,     0,    19,    28,    39,    40,    41,    42,
       0,     0,     0,    16,     0,    30,    21,     0,     0,    32,
      18,     0,    15,     0,    38,    37,     7,    14,    17,    31,
       4,     0,    26,     4,     0,     0,     5,     0,     0,     0,
       0,     0,    24,     0,    25,     0,     6
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    72,    73,     3,     4,    10,    11,    12,    24,
      52,    53,    30,    31,    67,    79,    13,    14,    36,    50,
      15
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -49
static const yytype_int8 yypact[] =
{
       6,     9,    14,    -1,     6,    15,   -49,    37,    27,    16,
       3,   -49,    12,   -49,     3,   -49,   -49,   -49,    18,     4,
       7,    32,    41,   -49,    36,   -49,   -49,    42,   -49,   -49,
      47,    40,    38,   -49,   -49,   -49,     0,   -49,   -49,    50,
      45,    55,     4,    30,     4,   -49,   -49,   -49,   -49,   -49,
       7,    57,    53,    54,     7,   -49,   -49,    58,    56,    39,
     -49,    60,    50,    17,   -49,   -49,     6,   -49,   -49,   -49,
      44,    67,     3,    44,    68,    48,   -49,    69,     7,    64,
      59,    24,   -49,    70,   -49,    71,   -49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -49,   -49,     1,   -49,    -3,   -49,    66,   -49,   -49,   -49,
      19,   -49,   -32,   -49,   -49,   -49,   -10,   -49,   -48,   -49,
     -49
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      23,    16,    59,     7,    26,    45,    63,     7,    28,     1,
      56,    32,    58,     5,     6,    46,    47,    48,    49,    22,
      17,     8,    69,     9,    29,     8,    33,    34,    35,    84,
      81,    21,    46,    47,    48,    49,     9,    37,    27,    46,
      47,    48,    49,    18,    43,    38,    39,    19,    44,    40,
      57,    20,    42,    51,    46,    47,    48,    49,    41,    54,
      55,    60,    75,    70,    61,    64,    62,    65,    66,    71,
      74,    78,    77,    82,    76,    80,    86,    85,    25,    83,
       0,    68
};

static const yytype_int8 yycheck[] =
{
      10,     4,    50,     4,    14,     5,    54,     4,     4,     3,
      42,     4,    44,     4,     0,    15,    16,    17,    18,     3,
       5,    22,     5,    24,    20,    22,    19,    20,    21,     5,
      78,     4,    15,    16,    17,    18,    24,     5,    20,    15,
      16,    17,    18,     6,     6,     4,    10,    10,    10,     7,
      20,    14,    12,     3,    15,    16,    17,    18,    11,    14,
       5,     4,    72,    66,    11,     7,    12,    11,     8,    25,
       3,    23,     4,     9,    73,     6,     5,     7,    12,    20,
      -1,    62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    31,    32,     4,     0,     4,    22,    24,
      33,    34,    35,    43,    44,    47,    31,     5,     6,    10,
      14,     4,     3,    43,    36,    33,    43,    20,     4,    20,
      39,    40,     4,    19,    20,    21,    45,     5,     4,    10,
       7,    11,    12,     6,    10,     5,    15,    16,    17,    18,
      46,     3,    37,    38,    14,     5,    39,    20,    39,    45,
       4,    11,    12,    45,     7,    11,     8,    41,    37,     5,
      31,    25,    29,    30,     3,    43,    29,     4,    23,    42,
       6,    45,     9,    20,     5,     7,     5
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
      yyerror (YY_("syntax error: cannot back up")); \
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
      case 4: /* "ID" */
#line 76 "parser.y"
	{ fprintf(yyoutput, "%s", (yyvaluep->string)); };
#line 806 "parser.tab.c"
	break;
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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


/* Prevent warnings from -Wmissing-prototypes.  */

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
#line 87 "parser.y"
    { 
									printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = (yyvsp[(1) - (3)].ast);
									root->program.funcDeclList = (yyvsp[(2) - (3)].ast);
									root->program.stmtList = (yyvsp[(3) - (3)].ast);
									;}
    break;

  case 3:
#line 95 "parser.y"
    { 
									printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = (yyvsp[(1) - (2)].ast);
									root->program.stmtList = (yyvsp[(2) - (2)].ast);
									;}
    break;

  case 4:
#line 105 "parser.y"
    {/*empty, i.e. it is possible not to declare an array*/;}
    break;

  case 5:
#line 106 "parser.y"
    {  
									printf("PARSER: Recognized array declaration list\n"); 
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_ArrayDeclList;
									(yyval.ast)->arrayDeclList.arrayDecl = (yyvsp[(1) - (2)].ast);
									(yyval.ast)->arrayDeclList.arrayDeclList = (yyvsp[(2) - (2)].ast);
									printASTNode((yyval.ast));
									;}
    break;

  case 6:
#line 116 "parser.y"
    { 
									printf("PARSER: Recognized array declaration: %s\n", (yyvsp[(3) - (7)].string));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_ArrayDecl;
									(yyval.ast)->arrayDecl.varType = strdup((yyvsp[(2) - (7)].string));
									(yyval.ast)->arrayDecl.varName = strdup((yyvsp[(3) - (7)].string));
									char buffer[20];
									snprintf(buffer, sizeof(buffer), "%d", (yyvsp[(5) - (7)].number));
									(yyval.ast)->arrayDecl.size = strdup(buffer);

									printf("\nAdding array symbol: {%s} to table {%s}\n", (yyvsp[(3) - (7)].string), current_scope->scope_name);
									add_symbol(current_scope, (yyvsp[(3) - (7)].string), (yyvsp[(2) - (7)].string));
									print_table(current_scope);
								;}
    break;

  case 7:
#line 133 "parser.y"
    {/*empty, i.e. it is possible not to declare a variable*/;}
    break;

  case 8:
#line 134 "parser.y"
    {  
									printf("PARSER: Recognized variable declaration list\n"); 
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_VarDeclList;
									(yyval.ast)->varDeclList.varDecl = (yyvsp[(1) - (2)].ast);
									(yyval.ast)->varDeclList.varDeclList = (yyvsp[(2) - (2)].ast);
									printASTNode((yyval.ast));
									;}
    break;

  case 9:
#line 145 "parser.y"
    { 
									symbol *entry = lookup(current_scope, (yyvsp[(2) - (3)].string));
									if (entry != NULL) {
										yyerror("Variable already declared");
									} else {
										printf("PARSER: Recognized variable declaration: %s\n", (yyvsp[(2) - (3)].string));
										(yyval.ast) = malloc(sizeof(ASTNode));
										(yyval.ast)->type = NodeType_VarDecl;
										(yyval.ast)->varDecl.varType = strdup((yyvsp[(1) - (3)].string));
										(yyval.ast)->varDecl.varName = strdup((yyvsp[(2) - (3)].string));

										printf("\nAdding symbol: {%s} to table {%s}\n", (yyvsp[(2) - (3)].string), current_scope->scope_name);
										add_symbol(current_scope, (yyvsp[(2) - (3)].string), (yyvsp[(1) - (3)].string));
										print_table(current_scope);
									}
								;}
    break;

  case 10:
#line 164 "parser.y"
    {/*empty, i.e. it is possible not to declare a variable*/;}
    break;

  case 11:
#line 165 "parser.y"
    {  
										printf("PARSER: Recognized function declaration list\n"); 
										(yyval.ast) = malloc(sizeof(ASTNode));
										(yyval.ast)->type = NodeType_FuncDeclList;
										(yyval.ast)->funcDeclList.funcDecl = (yyvsp[(1) - (2)].ast);
										(yyval.ast)->funcDeclList.funcDeclList = (yyvsp[(2) - (2)].ast);
										printASTNode((yyval.ast));
										;}
    break;

  case 12:
#line 176 "parser.y"
    { 
								printf("PARSER: Recognized function signature\n");
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_FuncSignature;
								(yyval.ast)->funcSignature.funcType = strdup((yyvsp[(2) - (3)].string));
								(yyval.ast)->funcSignature.funcName = strdup((yyvsp[(3) - (3)].string));
								;}
    break;

  case 13:
#line 186 "parser.y"
    {
					printf("PARSER: Entering function scope\n");
					symbol_table* local_table = create_symbol_table(TABLE_SIZE, (yyvsp[(1) - (1)].ast)->funcSignature.funcName); 
					(yyvsp[(1) - (1)].ast)->funcSignature.scope = local_table;
					local_table->parent = current_scope;
					previous_scope = current_scope;
					current_scope = local_table; 
				;}
    break;

  case 14:
#line 195 "parser.y"
    { 
					// Scopes will be made compile-time. runtime scopes will be dealt with in the future.
					printf("PARSER: Recognized function declaration\n");
					(yyval.ast) = malloc(sizeof(ASTNode));
					(yyval.ast)->type = NodeType_FuncDecl;
					(yyval.ast)->funcDecl.funcType = strdup((yyvsp[(1) - (6)].ast)->funcSignature.funcType);
					(yyval.ast)->funcDecl.funcName = strdup((yyvsp[(1) - (6)].ast)->funcSignature.funcName);
					(yyval.ast)->funcDecl.funcSignature = (yyvsp[(1) - (6)].ast);
					(yyval.ast)->funcDecl.paramList = (yyvsp[(4) - (6)].ast);
					(yyval.ast)->funcDecl.block = (yyvsp[(6) - (6)].ast);
					(yyval.ast)->funcDecl.scope = current_scope;
					printf("PARSER: Exiting function scope\n");
					current_scope = previous_scope;
				;}
    break;

  case 15:
#line 212 "parser.y"
    {/*empty, i.e. it is possible not to have any parameters*/;}
    break;

  case 16:
#line 213 "parser.y"
    { printf("PARSER: Recognized single parameter\n");
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_ParamList;
								(yyval.ast)->paramList.param = (yyvsp[(1) - (1)].ast);
								(yyval.ast)->paramList.paramList = NULL;
								;}
    break;

  case 17:
#line 219 "parser.y"
    { 
									printf("PARSER: Recognized parameter list with comma\n");
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_ParamList;
									(yyval.ast)->paramList.param = (yyvsp[(1) - (3)].ast);
									(yyval.ast)->paramList.paramList = (yyvsp[(3) - (3)].ast);
									;}
    break;

  case 18:
#line 229 "parser.y"
    {
									printf("PARSER: Recognized parameter: %s\n", (yyvsp[(2) - (2)].string));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_Param;
									(yyval.ast)->param.varType = strdup((yyvsp[(1) - (2)].string));
									(yyval.ast)->param.varName = strdup((yyvsp[(2) - (2)].string));
									printf("\nAdding PARAMETER symbol: {%s} to table {%s}\n", (yyvsp[(2) - (2)].string), current_scope->scope_name);
									add_symbol(current_scope, (yyvsp[(2) - (2)].string), (yyvsp[(1) - (2)].string));
									print_table(current_scope);
									;}
    break;

  case 19:
#line 241 "parser.y"
    {/*empty, i.e. it is possible not to have any input parameters*/;}
    break;

  case 20:
#line 242 "parser.y"
    { 
								printf("PARSER: Recognized single input parameter\n");
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_InputParamList;
								(yyval.ast)->inputParamList.inputParam = (yyvsp[(1) - (1)].ast);
								(yyval.ast)->inputParamList.inputParamList = NULL;
								;}
    break;

  case 21:
#line 249 "parser.y"
    { 
											printf("PARSER: Recognized input parameter list with comma\n");
											(yyval.ast) = malloc(sizeof(ASTNode));
											(yyval.ast)->type = NodeType_InputParamList;
											(yyval.ast)->inputParamList.inputParam = (yyvsp[(1) - (3)].ast);
											(yyval.ast)->inputParamList.inputParamList = (yyvsp[(3) - (3)].ast);
											;}
    break;

  case 22:
#line 259 "parser.y"
    {
							printf("PARSER: Recognized input parameter ID: %s\n", (yyvsp[(1) - (1)].string));
							(yyval.ast) = malloc(sizeof(ASTNode));
							(yyval.ast)->type = NodeType_InputParam;
							(yyval.ast)->inputParam.value = strdup((yyvsp[(1) - (1)].string));
							;}
    break;

  case 23:
#line 265 "parser.y"
    {
							printf("PARSER: Recognized input parameter number: %d\n", (yyvsp[(1) - (1)].number));
							(yyval.ast) = malloc(sizeof(ASTNode));
							(yyval.ast)->type = NodeType_InputParam;
							char buffer[20];
							snprintf(buffer, sizeof(buffer), "%d", (yyvsp[(1) - (1)].number));
							(yyval.ast)->inputParam.value = strdup(buffer);
							;}
    break;

  case 24:
#line 277 "parser.y"
    { 
				printf("PARSER: Recognized block\n"); 
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_Block;
				(yyval.ast)->block.varDeclList = (yyvsp[(2) - (6)].ast);
				(yyval.ast)->block.arrayDeclList = (yyvsp[(3) - (6)].ast);
				(yyval.ast)->block.stmtList = (yyvsp[(4) - (6)].ast);
				(yyval.ast)->block.returnStmt = (yyvsp[(5) - (6)].ast);
			;}
    break;

  case 25:
#line 290 "parser.y"
    { 
										printf("PARSER: Recognized return statement\n");
										(yyval.ast) = malloc(sizeof(ASTNode));
										(yyval.ast)->type = NodeType_ReturnStmt;
										(yyval.ast)->returnStmt.expr = (yyvsp[(2) - (3)].ast);
										;}
    break;

  case 26:
#line 298 "parser.y"
    {/*empty, i.e. it is possible not to have any statement*/;}
    break;

  case 27:
#line 299 "parser.y"
    { printf("PARSER: Recognized statement list\n");
							(yyval.ast) = malloc(sizeof(ASTNode));
							(yyval.ast)->type = NodeType_StmtList;
							(yyval.ast)->stmtList.stmt = (yyvsp[(1) - (2)].ast);
							(yyval.ast)->stmtList.stmtList = (yyvsp[(2) - (2)].ast);
							;}
    break;

  case 28:
#line 308 "parser.y"
    {
									printf("Parsed Assignment Statement: %s = ...\n", (yyvsp[(1) - (4)].string));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_AssignStmt;
									(yyval.ast)->assignStmt.varName = strdup((yyvsp[(1) - (4)].string));
									(yyval.ast)->assignStmt.expr = (yyvsp[(3) - (4)].ast);
									symbol *entry = lookup(current_scope, (yyvsp[(1) - (4)].string));
									if (entry == NULL) {
										yyerror("Variable not declared");
									} else if ((yyvsp[(3) - (4)].ast)->type == NodeType_SimpleExpr) {
										entry->value = (yyvsp[(3) - (4)].ast)->simpleExpr.number;
										print_table(current_scope);
									}
 								;}
    break;

  case 29:
#line 322 "parser.y"
    {
									(yyval.ast) = (yyvsp[(1) - (1)].ast);
								;}
    break;

  case 30:
#line 325 "parser.y"
    {
									printf("Parsed Function Call: %s()\n", (yyvsp[(1) - (5)].string));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_FuncCall;
									(yyval.ast)->funcCall.funcName = strdup((yyvsp[(1) - (5)].string));
									// $$->funcCall.paramList = NULL;
								;}
    break;

  case 31:
#line 332 "parser.y"
    {
									printf("Parsed Array Assignment: %s[%d] = ...\n", (yyvsp[(1) - (7)].string), (yyvsp[(3) - (7)].number));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_ArrayAssignStmt;
									(yyval.ast)->arrayAssignStmt.varName = strdup((yyvsp[(1) - (7)].string));
									char buffer[20];
									snprintf(buffer, sizeof(buffer), "%d", (yyvsp[(3) - (7)].number));
									(yyval.ast)->arrayAssignStmt.index = strdup(buffer);
									(yyval.ast)->arrayAssignStmt.expr = (yyvsp[(6) - (7)].ast);
								;}
    break;

  case 32:
#line 345 "parser.y"
    { 
						printf("PARSER: Recognized binary operation\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_Expr;
						(yyval.ast)->expr.left = (yyvsp[(1) - (3)].ast);
						(yyval.ast)->expr.right = (yyvsp[(3) - (3)].ast);
						(yyval.ast)->expr.operator = (yyvsp[(2) - (3)].ast)->binOp.operator;
 						;}
    break;

  case 33:
#line 353 "parser.y"
    { 
						printf("ASSIGNMENT statement \n"); 
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_SimpleID;
						(yyval.ast)->simpleID.name = (yyvsp[(1) - (1)].string);
						;}
    break;

  case 34:
#line 359 "parser.y"
    {
						printf("PARSER: Recognized float\n");
						printf("FLOAT: %f\n", (yyvsp[(1) - (1)].fval));
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_SimpleExpr;
						char buffer[20];
						snprintf(buffer, sizeof(buffer), "%f", (yyvsp[(1) - (1)].fval));
						(yyval.ast)->simpleExpr.number = strdup(buffer);
						printf("FLOAT: %s\n", (yyval.ast)->simpleExpr.number);
					;}
    break;

  case 35:
#line 369 "parser.y"
    {
						printf("PARSER: Recognized boolean\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_SimpleExpr;
						(yyval.ast)->simpleExpr.number = strdup((yyvsp[(1) - (1)].string));
						;}
    break;

  case 36:
#line 375 "parser.y"
    { 
						printf("PARSER: Recognized number\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_SimpleExpr;
						char buffer[20];
						snprintf(buffer, sizeof(buffer), "%d", (yyvsp[(1) - (1)].number));
						(yyval.ast)->simpleExpr.number = strdup(buffer);
						;}
    break;

  case 37:
#line 383 "parser.y"
    {
						printf("PARSER: Recognized function call\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_FuncCall;
						(yyval.ast)->funcCall.funcName = strdup((yyvsp[(1) - (4)].string));
						(yyval.ast)->funcCall.inputParamList = (yyvsp[(3) - (4)].ast);
						;}
    break;

  case 38:
#line 390 "parser.y"
    {
						printf("PARSER: Recognized array access\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_ArrayAccess;
						(yyval.ast)->arrayAccess.varName = strdup((yyvsp[(1) - (4)].string));
						char buffer[20];
						snprintf(buffer, sizeof(buffer), "%d", (yyvsp[(3) - (4)].number));
						(yyval.ast)->arrayAccess.index = strdup(buffer);
						;}
    break;

  case 39:
#line 401 "parser.y"
    {
			printf("PARSER: Recognized binary operation (addition)\n");	
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_BinOp;
			(yyval.ast)->binOp.operator = *(yyvsp[(1) - (1)].operator);
;}
    break;

  case 40:
#line 408 "parser.y"
    {
				printf("PARSER: Recognized binary operation (subtraction)\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[(1) - (1)].operator);
;}
    break;

  case 41:
#line 415 "parser.y"
    {
				printf("PARSER: Recognized binary operation (multiplication)\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[(1) - (1)].operator);
;}
    break;

  case 42:
#line 422 "parser.y"
    {
				printf("PARSER: Recognized binary operation (division)\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[(1) - (1)].operator);
				// Note: Division by zero check should be implemented in the semantic analysis or code generation phase
				printf("WARNING: Remember to check for division by zero during semantic analysis or code generation\n");
;}
    break;

  case 43:
#line 431 "parser.y"
    {
									printf("PARSER: Recognized write statement\n");
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_WriteStmt;
									(yyval.ast)->writeStmt.varName = strdup((yyvsp[(2) - (3)].string));
								;}
    break;


/* Line 1267 of yacc.c.  */
#line 1942 "parser.tab.c"
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
      yyerror (YY_("syntax error"));
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
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
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
		      yytoken, &yylval);
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
		  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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


#line 439 "parser.y"


int main() {
    // Initialize file or input source
    yyin = fopen("testProg.cmm", "r");
	printf("Creating scope stack..\n");
	create_scope_stack();
	printf("Creating global symbol table..\n");
	symbol_table* global_sym_table = create_symbol_table(TABLE_SIZE, "global");
	current_scope = global_sym_table;
	push_scope(global_sym_table);
	
    if (yyparse() == 0) {
		printf("\n\n\nParsing successful!\n");
        traverseAST(root, 0);
		printf("\n\n");
		printf("\n=== SEMANTIC ANALYSIS ===\n\n");
		semantic_analysis(root, global_sym_table);
		printf("\n");
		printf("\n=== TAC GENERATION ===\n");
		print_TAC_to_file("TAC.ir", tac_head);
		printf("\n");
		print_all_TAC(tac_head); 
		printf("\n=== TAC OPTIMIZATION ===\n");
		optimize_TAC(&tac_head);
		print_optimized_TAC("optimized_TAC.ir", tac_head);
		printf("\n");
		print_all_TAC(tac_head);

		// Code generation
		printf("\n=== CODE GENERATION ===\n");
		init_code_generator("output.s");
		generate_MIPS(tac_head);
		finalize_code_generator("output.s");
		
        freeAST(root);
    } else {
        fprintf(stderr, "Parsing failed\n");
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
