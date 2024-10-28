/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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

#line 111 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TYPE = 3,                       /* TYPE  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_SEMICOLON = 5,                  /* SEMICOLON  */
  YYSYMBOL_LBRACK = 6,                     /* LBRACK  */
  YYSYMBOL_RBRACK = 7,                     /* RBRACK  */
  YYSYMBOL_LCURBRACK = 8,                  /* LCURBRACK  */
  YYSYMBOL_RCURBRACK = 9,                  /* RCURBRACK  */
  YYSYMBOL_LPAREN = 10,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 11,                    /* RPAREN  */
  YYSYMBOL_COMMA = 12,                     /* COMMA  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_PLUS = 14,                      /* PLUS  */
  YYSYMBOL_MINUS = 15,                     /* MINUS  */
  YYSYMBOL_STAR = 16,                      /* STAR  */
  YYSYMBOL_BSLASH = 17,                    /* BSLASH  */
  YYSYMBOL_NUMBER = 18,                    /* NUMBER  */
  YYSYMBOL_BOOL_LITERAL = 19,              /* BOOL_LITERAL  */
  YYSYMBOL_WRITE = 20,                     /* WRITE  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_FUNC = 22,                      /* FUNC  */
  YYSYMBOL_ARRAY = 23,                     /* ARRAY  */
  YYSYMBOL_YYACCEPT = 24,                  /* $accept  */
  YYSYMBOL_Program = 25,                   /* Program  */
  YYSYMBOL_ArrayDeclList = 26,             /* ArrayDeclList  */
  YYSYMBOL_ArrayDecl = 27,                 /* ArrayDecl  */
  YYSYMBOL_VarDeclList = 28,               /* VarDeclList  */
  YYSYMBOL_VarDecl = 29,                   /* VarDecl  */
  YYSYMBOL_FuncDeclList = 30,              /* FuncDeclList  */
  YYSYMBOL_FuncSignature = 31,             /* FuncSignature  */
  YYSYMBOL_FuncDecl = 32,                  /* FuncDecl  */
  YYSYMBOL_33_1 = 33,                      /* $@1  */
  YYSYMBOL_ParamList = 34,                 /* ParamList  */
  YYSYMBOL_Param = 35,                     /* Param  */
  YYSYMBOL_InputParamList = 36,            /* InputParamList  */
  YYSYMBOL_InputParam = 37,                /* InputParam  */
  YYSYMBOL_Block = 38,                     /* Block  */
  YYSYMBOL_39_2 = 39,                      /* $@2  */
  YYSYMBOL_40_3 = 40,                      /* $@3  */
  YYSYMBOL_ReturnStmt = 41,                /* ReturnStmt  */
  YYSYMBOL_StmtList = 42,                  /* StmtList  */
  YYSYMBOL_Stmt = 43,                      /* Stmt  */
  YYSYMBOL_Expr = 44,                      /* Expr  */
  YYSYMBOL_BinOp = 45,                     /* BinOp  */
  YYSYMBOL_WriteStmt = 46                  /* WriteStmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   81

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  44
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  88

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    91,   101,   102,   112,   129,   130,   141,
     160,   161,   172,   182,   181,   208,   209,   215,   225,   237,
     238,   245,   255,   261,   273,   276,   272,   295,   303,   304,
     313,   327,   330,   337,   350,   358,   364,   372,   379,   388,
     397,   404,   411,   418,   427
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "ID",
  "SEMICOLON", "LBRACK", "RBRACK", "LCURBRACK", "RCURBRACK", "LPAREN",
  "RPAREN", "COMMA", "EQ", "PLUS", "MINUS", "STAR", "BSLASH", "NUMBER",
  "BOOL_LITERAL", "WRITE", "RETURN", "FUNC", "ARRAY", "$accept", "Program",
  "ArrayDeclList", "ArrayDecl", "VarDeclList", "VarDecl", "FuncDeclList",
  "FuncSignature", "FuncDecl", "$@1", "ParamList", "Param",
  "InputParamList", "InputParam", "Block", "$@2", "$@3", "ReturnStmt",
  "StmtList", "Stmt", "Expr", "BinOp", "WriteStmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-48)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       9,    14,    30,    -1,     9,    27,   -48,     1,    42,    44,
       0,   -48,    26,   -48,     0,   -48,   -48,   -48,    31,     6,
       4,    45,    47,   -48,    43,   -48,   -48,    48,   -48,   -48,
      41,    46,     3,   -48,   -48,    11,   -48,   -48,    51,    49,
      52,     6,    38,     6,   -48,   -48,   -48,   -48,   -48,     4,
      55,    50,    54,     4,   -48,   -48,    53,    56,    20,   -48,
      60,    51,    24,   -48,   -48,   -48,   -48,   -48,   -48,     9,
      57,    61,     0,    57,    65,    58,   -48,    64,     4,   -48,
      59,    28,    62,    66,   -48,   -48,    67,   -48
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       7,     0,     0,    10,     7,     0,     1,     0,     0,     0,
      28,    13,    10,     3,    28,    31,     8,     9,     0,    19,
       0,     0,     0,     2,     0,    11,    29,     0,    22,    23,
       0,    20,    35,    36,    39,     0,    44,    12,    15,     0,
       0,    19,     0,    19,    30,    40,    41,    42,    43,     0,
       0,     0,    16,     0,    32,    21,     0,     0,    34,    18,
       0,    15,     0,    38,    37,    24,    14,    17,    33,     7,
       4,     0,    28,     4,     0,     0,     5,     0,     0,    25,
       0,     0,     0,     0,    27,    26,     0,     6
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -48,   -48,     2,   -48,    -4,   -48,    69,   -48,   -48,   -48,
      13,   -48,   -26,   -48,   -48,   -48,   -48,   -48,    -9,   -48,
     -47,   -48,   -48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    72,    73,     3,     4,    10,    11,    12,    24,
      51,    52,    30,    31,    66,    69,    82,    79,    13,    14,
      35,    49,    15
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      16,    23,    58,     7,     7,    26,    62,    18,    32,    42,
      28,    19,     1,    43,    20,    55,    44,    57,     5,     8,
       8,     9,    33,    34,    29,    45,    46,    47,    48,    68,
       6,    81,    17,    84,    45,    46,    47,    48,    45,    46,
      47,    48,    45,    46,    47,    48,    21,    22,     9,    27,
      36,    37,    40,    38,    50,    39,    56,    54,    41,    59,
      63,    60,    53,    75,    74,    70,    61,    64,    65,    77,
      80,    85,    87,    86,    67,    76,     0,    83,     0,    78,
      71,    25
};

static const yytype_int8 yycheck[] =
{
       4,    10,    49,     4,     4,    14,    53,     6,     4,     6,
       4,    10,     3,    10,    13,    41,     5,    43,     4,    20,
      20,    22,    18,    19,    18,    14,    15,    16,    17,     5,
       0,    78,     5,     5,    14,    15,    16,    17,    14,    15,
      16,    17,    14,    15,    16,    17,     4,     3,    22,    18,
       5,     4,    11,    10,     3,     7,    18,     5,    12,     4,
       7,    11,    13,    72,     3,    69,    12,    11,     8,     4,
       6,     9,     5,     7,    61,    73,    -1,    18,    -1,    21,
      23,    12
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    25,    28,    29,     4,     0,     4,    20,    22,
      30,    31,    32,    42,    43,    46,    28,     5,     6,    10,
      13,     4,     3,    42,    33,    30,    42,    18,     4,    18,
      36,    37,     4,    18,    19,    44,     5,     4,    10,     7,
      11,    12,     6,    10,     5,    14,    15,    16,    17,    45,
       3,    34,    35,    13,     5,    36,    18,    36,    44,     4,
      11,    12,    44,     7,    11,     8,    38,    34,     5,    39,
      28,    23,    26,    27,     3,    42,    26,     4,    21,    41,
       6,    44,    40,    18,     5,     9,     7,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    24,    25,    25,    26,    26,    27,    28,    28,    29,
      30,    30,    31,    33,    32,    34,    34,    34,    35,    36,
      36,    36,    37,    37,    39,    40,    38,    41,    42,    42,
      43,    43,    43,    43,    44,    44,    44,    44,    44,    44,
      45,    45,    45,    45,    46
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,     7,     0,     2,     3,
       0,     2,     3,     0,     6,     0,     1,     3,     2,     0,
       1,     3,     1,     1,     0,     0,     8,     3,     0,     2,
       4,     1,     5,     7,     3,     1,     1,     4,     4,     1,
       1,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_ID: /* ID  */
#line 72 "parser.y"
         { fprintf(yyoutput, "%s", ((*yyvaluep).string)); }
#line 814 "parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* Program: VarDeclList FuncDeclList StmtList  */
#line 83 "parser.y"
                                                    { 
									printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = (yyvsp[-2].ast);
									root->program.funcDeclList = (yyvsp[-1].ast);
									root->program.stmtList = (yyvsp[0].ast);
									}
#line 1211 "parser.tab.c"
    break;

  case 3: /* Program: VarDeclList StmtList  */
#line 91 "parser.y"
                                       { 
									printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = (yyvsp[-1].ast);
									root->program.stmtList = (yyvsp[0].ast);
									}
#line 1223 "parser.tab.c"
    break;

  case 4: /* ArrayDeclList: %empty  */
#line 101 "parser.y"
                                                                        {/*empty, i.e. it is possible not to declare an array*/}
#line 1229 "parser.tab.c"
    break;

  case 5: /* ArrayDeclList: ArrayDecl ArrayDeclList  */
#line 102 "parser.y"
                                                        {  
									printf("PARSER: Recognized array declaration list\n"); 
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_ArrayDeclList;
									(yyval.ast)->arrayDeclList.arrayDecl = (yyvsp[-1].ast);
									(yyval.ast)->arrayDeclList.arrayDeclList = (yyvsp[0].ast);
									printASTNode((yyval.ast));
									}
#line 1242 "parser.tab.c"
    break;

  case 6: /* ArrayDecl: ARRAY TYPE ID LBRACK NUMBER RBRACK SEMICOLON  */
#line 112 "parser.y"
                                                                  { 
									printf("PARSER: Recognized array declaration: %s\n", (yyvsp[-4].string));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_ArrayDecl;
									(yyval.ast)->arrayDecl.varType = strdup((yyvsp[-5].string));
									(yyval.ast)->arrayDecl.varName = strdup((yyvsp[-4].string));
									char buffer[20];
									snprintf(buffer, sizeof(buffer), "%d", (yyvsp[-2].number));
									(yyval.ast)->arrayDecl.size = strdup(buffer);

									printf("\nAdding array symbol: {%s} to table {%s}\n", (yyvsp[-4].string), current_scope->scope_name);
									add_symbol(current_scope, (yyvsp[-4].string), (yyvsp[-5].string));
									print_table(current_scope);
								}
#line 1261 "parser.tab.c"
    break;

  case 7: /* VarDeclList: %empty  */
#line 129 "parser.y"
                                                                        {/*empty, i.e. it is possible not to declare a variable*/}
#line 1267 "parser.tab.c"
    break;

  case 8: /* VarDeclList: VarDecl VarDeclList  */
#line 130 "parser.y"
                                                    {  
									printf("PARSER: Recognized variable declaration list\n"); 
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_VarDeclList;
									(yyval.ast)->varDeclList.varDecl = (yyvsp[-1].ast);
									(yyval.ast)->varDeclList.varDeclList = (yyvsp[0].ast);
									printASTNode((yyval.ast));
									}
#line 1280 "parser.tab.c"
    break;

  case 9: /* VarDecl: TYPE ID SEMICOLON  */
#line 141 "parser.y"
                                         { 
									symbol *entry = lookup(current_scope, (yyvsp[-1].string));
									if (entry != NULL) {
										yyerror("Variable already declared");
									} else {
										printf("PARSER: Recognized variable declaration: %s\n", (yyvsp[-1].string));
										(yyval.ast) = malloc(sizeof(ASTNode));
										(yyval.ast)->type = NodeType_VarDecl;
										(yyval.ast)->varDecl.varType = strdup((yyvsp[-2].string));
										(yyval.ast)->varDecl.varName = strdup((yyvsp[-1].string));

										printf("\nAdding symbol: {%s} to table {%s}\n", (yyvsp[-1].string), current_scope->scope_name);
										add_symbol(current_scope, (yyvsp[-1].string), (yyvsp[-2].string));
										print_table(current_scope);
									}
								}
#line 1301 "parser.tab.c"
    break;

  case 10: /* FuncDeclList: %empty  */
#line 160 "parser.y"
                                                                                {/*empty, i.e. it is possible not to declare a variable*/}
#line 1307 "parser.tab.c"
    break;

  case 11: /* FuncDeclList: FuncDecl FuncDeclList  */
#line 161 "parser.y"
                                                        {  
										printf("PARSER: Recognized function declaration list\n"); 
										(yyval.ast) = malloc(sizeof(ASTNode));
										(yyval.ast)->type = NodeType_FuncDeclList;
										(yyval.ast)->funcDeclList.funcDecl = (yyvsp[-1].ast);
										(yyval.ast)->funcDeclList.funcDeclList = (yyvsp[0].ast);
										printASTNode((yyval.ast));
										}
#line 1320 "parser.tab.c"
    break;

  case 12: /* FuncSignature: FUNC TYPE ID  */
#line 172 "parser.y"
                                        { 
								printf("PARSER: Recognized function signature\n");
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_FuncSignature;
								(yyval.ast)->funcSignature.funcType = strdup((yyvsp[-1].string));
								(yyval.ast)->funcSignature.funcName = strdup((yyvsp[0].string));
								}
#line 1332 "parser.tab.c"
    break;

  case 13: /* $@1: %empty  */
#line 182 "parser.y"
                                {
					printf("PARSER: Entering function scope\n");
					symbol_table* local_table = create_symbol_table(TABLE_SIZE, (yyvsp[0].ast)->funcSignature.funcName); 
					(yyvsp[0].ast)->funcSignature.scope = local_table;
					local_table->parent = current_scope;
					previous_scope = current_scope;
					current_scope = local_table; 
				}
#line 1345 "parser.tab.c"
    break;

  case 14: /* FuncDecl: FuncSignature $@1 LPAREN ParamList RPAREN Block  */
#line 191 "parser.y"
                                { 
					// Scopes will be made compile-time. runtime scopes will be dealt with in the future.
					printf("PARSER: Recognized function declaration\n");
					(yyval.ast) = malloc(sizeof(ASTNode));
					(yyval.ast)->type = NodeType_FuncDecl;
					(yyval.ast)->funcDecl.funcType = strdup((yyvsp[-5].ast)->funcSignature.funcType);
					(yyval.ast)->funcDecl.funcName = strdup((yyvsp[-5].ast)->funcSignature.funcName);
					(yyval.ast)->funcDecl.funcSignature = (yyvsp[-5].ast);
					(yyval.ast)->funcDecl.paramList = (yyvsp[-2].ast);
					(yyval.ast)->funcDecl.block = (yyvsp[0].ast);
					(yyval.ast)->funcDecl.scope = current_scope;
					printf("PARSER: Exiting function scope\n");
					current_scope = previous_scope;
				}
#line 1364 "parser.tab.c"
    break;

  case 15: /* ParamList: %empty  */
#line 208 "parser.y"
                                                                {/*empty, i.e. it is possible not to have any parameters*/}
#line 1370 "parser.tab.c"
    break;

  case 16: /* ParamList: Param  */
#line 209 "parser.y"
                                                        { printf("PARSER: Recognized single parameter\n");
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_ParamList;
								(yyval.ast)->paramList.param = (yyvsp[0].ast);
								(yyval.ast)->paramList.paramList = NULL;
								}
#line 1381 "parser.tab.c"
    break;

  case 17: /* ParamList: Param COMMA ParamList  */
#line 215 "parser.y"
                                                { 
									printf("PARSER: Recognized parameter list with comma\n");
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_ParamList;
									(yyval.ast)->paramList.param = (yyvsp[-2].ast);
									(yyval.ast)->paramList.paramList = (yyvsp[0].ast);
									}
#line 1393 "parser.tab.c"
    break;

  case 18: /* Param: TYPE ID  */
#line 225 "parser.y"
                                                        {
									printf("PARSER: Recognized parameter: %s\n", (yyvsp[0].string));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_Param;
									(yyval.ast)->param.varType = strdup((yyvsp[-1].string));
									(yyval.ast)->param.varName = strdup((yyvsp[0].string));
									printf("\nAdding PARAMETER symbol: {%s} to table {%s}\n", (yyvsp[0].string), current_scope->scope_name);
									add_symbol(current_scope, (yyvsp[0].string), (yyvsp[-1].string));
									print_table(current_scope);
									}
#line 1408 "parser.tab.c"
    break;

  case 19: /* InputParamList: %empty  */
#line 237 "parser.y"
                                                                {/*empty, i.e. it is possible not to have any input parameters*/}
#line 1414 "parser.tab.c"
    break;

  case 20: /* InputParamList: InputParam  */
#line 238 "parser.y"
                                                        { 
								printf("PARSER: Recognized single input parameter\n");
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_InputParamList;
								(yyval.ast)->inputParamList.inputParam = (yyvsp[0].ast);
								(yyval.ast)->inputParamList.inputParamList = NULL;
								}
#line 1426 "parser.tab.c"
    break;

  case 21: /* InputParamList: InputParam COMMA InputParamList  */
#line 245 "parser.y"
                                                                { 
											printf("PARSER: Recognized input parameter list with comma\n");
											(yyval.ast) = malloc(sizeof(ASTNode));
											(yyval.ast)->type = NodeType_InputParamList;
											(yyval.ast)->inputParamList.inputParam = (yyvsp[-2].ast);
											(yyval.ast)->inputParamList.inputParamList = (yyvsp[0].ast);
											}
#line 1438 "parser.tab.c"
    break;

  case 22: /* InputParam: ID  */
#line 255 "parser.y"
                                                {
							printf("PARSER: Recognized input parameter ID: %s\n", (yyvsp[0].string));
							(yyval.ast) = malloc(sizeof(ASTNode));
							(yyval.ast)->type = NodeType_InputParam;
							(yyval.ast)->inputParam.value = strdup((yyvsp[0].string));
							}
#line 1449 "parser.tab.c"
    break;

  case 23: /* InputParam: NUMBER  */
#line 261 "parser.y"
                                        {
							printf("PARSER: Recognized input parameter number: %d\n", (yyvsp[0].number));
							(yyval.ast) = malloc(sizeof(ASTNode));
							(yyval.ast)->type = NodeType_InputParam;
							char buffer[20];
							snprintf(buffer, sizeof(buffer), "%d", (yyvsp[0].number));
							(yyval.ast)->inputParam.value = strdup(buffer);
							}
#line 1462 "parser.tab.c"
    break;

  case 24: /* $@2: %empty  */
#line 273 "parser.y"
                        { 
				
			}
#line 1470 "parser.tab.c"
    break;

  case 25: /* $@3: %empty  */
#line 276 "parser.y"
                        {
				
			}
#line 1478 "parser.tab.c"
    break;

  case 26: /* Block: LCURBRACK $@2 VarDeclList ArrayDeclList StmtList ReturnStmt $@3 RCURBRACK  */
#line 280 "parser.y"
                        { 
				printf("PARSER: Recognized block\n"); 
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_Block;
				(yyval.ast)->block.varDeclList = (yyvsp[-5].ast);
				(yyval.ast)->block.arrayDeclList = (yyvsp[-4].ast);
				(yyval.ast)->block.stmtList = (yyvsp[-3].ast);
				(yyval.ast)->block.returnStmt = (yyvsp[-2].ast);
				// $$->block.scope = current_scope;
				// printf("setting block scope to %s\n", current_scope->scope_name);
			}
#line 1494 "parser.tab.c"
    break;

  case 27: /* ReturnStmt: RETURN Expr SEMICOLON  */
#line 295 "parser.y"
                                                { 
										printf("PARSER: Recognized return statement\n");
										(yyval.ast) = malloc(sizeof(ASTNode));
										(yyval.ast)->type = NodeType_ReturnStmt;
										(yyval.ast)->returnStmt.expr = (yyvsp[-1].ast);
										}
#line 1505 "parser.tab.c"
    break;

  case 28: /* StmtList: %empty  */
#line 303 "parser.y"
                                                {/*empty, i.e. it is possible not to have any statement*/}
#line 1511 "parser.tab.c"
    break;

  case 29: /* StmtList: Stmt StmtList  */
#line 304 "parser.y"
                                        { printf("PARSER: Recognized statement list\n");
							(yyval.ast) = malloc(sizeof(ASTNode));
							(yyval.ast)->type = NodeType_StmtList;
							(yyval.ast)->stmtList.stmt = (yyvsp[-1].ast);
							(yyval.ast)->stmtList.stmtList = (yyvsp[0].ast);
							}
#line 1522 "parser.tab.c"
    break;

  case 30: /* Stmt: ID EQ Expr SEMICOLON  */
#line 313 "parser.y"
                                        {
									printf("Parsed Assignment Statement: %s = ...\n", (yyvsp[-3].string));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_AssignStmt;
									(yyval.ast)->assignStmt.varName = strdup((yyvsp[-3].string));
									(yyval.ast)->assignStmt.expr = (yyvsp[-1].ast);
									symbol *entry = lookup(current_scope, (yyvsp[-3].string));
									if (entry == NULL) {
										yyerror("Variable not declared");
									} else if ((yyvsp[-1].ast)->type == NodeType_SimpleExpr) {
										entry->value = (yyvsp[-1].ast)->simpleExpr.number;
										print_table(current_scope);
									}
 								}
#line 1541 "parser.tab.c"
    break;

  case 31: /* Stmt: WriteStmt  */
#line 327 "parser.y"
                                                        {
									(yyval.ast) = (yyvsp[0].ast);
								}
#line 1549 "parser.tab.c"
    break;

  case 32: /* Stmt: ID LPAREN InputParamList RPAREN SEMICOLON  */
#line 330 "parser.y"
                                                      {
									printf("Parsed Function Call: %s()\n", (yyvsp[-4].string));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_FuncCall;
									(yyval.ast)->funcCall.funcName = strdup((yyvsp[-4].string));
									// $$->funcCall.paramList = NULL;
								}
#line 1561 "parser.tab.c"
    break;

  case 33: /* Stmt: ID LBRACK NUMBER RBRACK EQ Expr SEMICOLON  */
#line 337 "parser.y"
                                                      {
									printf("Parsed Array Assignment: %s[%d] = ...\n", (yyvsp[-6].string), (yyvsp[-4].number));
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_ArrayAssignStmt;
									(yyval.ast)->arrayAssignStmt.varName = strdup((yyvsp[-6].string));
									char buffer[20];
									snprintf(buffer, sizeof(buffer), "%d", (yyvsp[-4].number));
									(yyval.ast)->arrayAssignStmt.index = strdup(buffer);
									(yyval.ast)->arrayAssignStmt.expr = (yyvsp[-1].ast);
								}
#line 1576 "parser.tab.c"
    break;

  case 34: /* Expr: Expr BinOp Expr  */
#line 350 "parser.y"
                                { 
						printf("PARSER: Recognized binary operation\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_Expr;
						(yyval.ast)->expr.left = (yyvsp[-2].ast);
						(yyval.ast)->expr.right = (yyvsp[0].ast);
						(yyval.ast)->expr.operator = (yyvsp[-1].ast)->binOp.operator;
 						}
#line 1589 "parser.tab.c"
    break;

  case 35: /* Expr: ID  */
#line 358 "parser.y"
                                                { 
						printf("ASSIGNMENT statement \n"); 
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_SimpleID;
						(yyval.ast)->simpleID.name = (yyvsp[0].string);
						}
#line 1600 "parser.tab.c"
    break;

  case 36: /* Expr: NUMBER  */
#line 364 "parser.y"
                                        { 
						printf("PARSER: Recognized number\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_SimpleExpr;
						char buffer[20];
						snprintf(buffer, sizeof(buffer), "%d", (yyvsp[0].number));
						(yyval.ast)->simpleExpr.number = strdup(buffer);
						}
#line 1613 "parser.tab.c"
    break;

  case 37: /* Expr: ID LPAREN InputParamList RPAREN  */
#line 372 "parser.y"
                                                {
						printf("PARSER: Recognized function call\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_FuncCall;
						(yyval.ast)->funcCall.funcName = strdup((yyvsp[-3].string));
						(yyval.ast)->funcCall.inputParamList = (yyvsp[-1].ast);
						}
#line 1625 "parser.tab.c"
    break;

  case 38: /* Expr: ID LBRACK NUMBER RBRACK  */
#line 379 "parser.y"
                                        {
						printf("PARSER: Recognized array access\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_ArrayAccess;
						(yyval.ast)->arrayAccess.varName = strdup((yyvsp[-3].string));
						char buffer[20];
						snprintf(buffer, sizeof(buffer), "%d", (yyvsp[-1].number));
						(yyval.ast)->arrayAccess.index = strdup(buffer);
						}
#line 1639 "parser.tab.c"
    break;

  case 39: /* Expr: BOOL_LITERAL  */
#line 388 "parser.y"
                     { 
                      printf("PARSER: Recognized boolean literal\n");
                      (yyval.ast) = malloc(sizeof(ASTNode));
                      (yyval.ast)->type = NodeType_SimpleExpr;
                      char buffer[20];
                      snprintf(buffer, sizeof(buffer), "%d", (yyvsp[0].number));
                      (yyval.ast)->simpleExpr.number = strdup(buffer);
                    }
#line 1652 "parser.tab.c"
    break;

  case 40: /* BinOp: PLUS  */
#line 397 "parser.y"
            {
			printf("PARSER: Recognized binary operation (addition)\n");	
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_BinOp;
			(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
}
#line 1663 "parser.tab.c"
    break;

  case 41: /* BinOp: MINUS  */
#line 404 "parser.y"
             {
				printf("PARSER: Recognized binary operation (subtraction)\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
}
#line 1674 "parser.tab.c"
    break;

  case 42: /* BinOp: STAR  */
#line 411 "parser.y"
            {
				printf("PARSER: Recognized binary operation (multiplication)\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
}
#line 1685 "parser.tab.c"
    break;

  case 43: /* BinOp: BSLASH  */
#line 418 "parser.y"
              {
				printf("PARSER: Recognized binary operation (division)\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
				// Note: Division by zero check should be implemented in the semantic analysis or code generation phase
				printf("WARNING: Remember to check for division by zero during semantic analysis or code generation\n");
}
#line 1698 "parser.tab.c"
    break;

  case 44: /* WriteStmt: WRITE ID SEMICOLON  */
#line 427 "parser.y"
                               {
									printf("PARSER: Recognized write statement\n");
									(yyval.ast) = malloc(sizeof(ASTNode));
									(yyval.ast)->type = NodeType_WriteStmt;
									(yyval.ast)->writeStmt.varName = strdup((yyvsp[-1].string));
								}
#line 1709 "parser.tab.c"
    break;


#line 1713 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 435 "parser.y"


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
