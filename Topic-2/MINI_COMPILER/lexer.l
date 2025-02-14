%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include "mini_parser1.tab.h"

#define YY_DECL int yylex()

int words = 0;
int chars = 0;
int lines = 0;

%}

letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
delim       [ \t\n]
NUMBER         {digit}+(\.{digit}+)?(E[+\-]?(digit)+)?
ws          {delim}+

%%
"/*"    				{
							int c;
							while((c = input()) != 0) {
								if(c == '*') {
									if((c = input()) == '/')
										break;
									else
										unput(c);
								}
							}
						}

"if"	{words++;
		 printf("%s : IF\n", yytext);
		}

"else"	{words++;
		 printf("%s : ELSE\n", yytext);
		}

"return"	{words++;
		 printf("%s : RETURN\n", yytext);
		}

"int"	{words++; chars += strlen(yytext);
		 printf("%s : TYPE\n", yytext);
		}

"char"	{words++; chars += strlen(yytext);
		 printf("%s : TYPE\n", yytext);
		}
		
"write"	{words++; 
		 chars += strlen(yytext);
		 printf("%s : KEYWORD\n", yytext);
		}
		
{ID}	{words++; chars += strlen(yytext);
		 printf("%s : IDENTIFIER\n",yytext);
		}
			
{NUMBER}	{words++; chars += strlen(yytext);
			  printf("%s : NUMBER\n",yytext);
			}
			
";"		{chars++;
		 printf("%s : SEMICOLON\n", yytext);
		}
		
"="		{chars++;
		 printf("%s : EQ\n", yytext);
		}

"+"		{chars++;
		 printf("%s : PLUS\n", yytext);
		}

"-"		{chars++;
		 printf("%s : MINUS\n", yytext);
		}

"*"		{chars++;
		 printf("%s : MULT\n", yytext);
		}

"/"		{chars++;
		 printf("%s : DIV\n", yytext);
		}

"{"     {chars++;
         printf("%s : LBRACE\n", yytext);
        }

"}"     {chars++;
         printf("%s : RBRACE\n", yytext);
        }

"("     {chars++;
         printf("%s : LPAREN\n", yytext);
        }

")"     {chars++;
         printf("%s : RPAREN\n", yytext);
        }

"["     {chars++;
         printf("%s : LBRACK\n", yytext);
        }

"]"     {chars++;
         printf("%s : RBRACK\n", yytext);
        }

\n		{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
		


%%
