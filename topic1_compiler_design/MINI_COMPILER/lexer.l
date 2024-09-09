%option noyywrap

%{
/* C code section */
#include <stdio.h>
#include <string.h>

/* Define the yylex function declaration */
#define YY_DECL int yylex()

/* Global variables for counting */
int words = 0;
int chars = 0;
int lines = 0;
%}

/* Definitions section */
letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
delim       [ \t\n]
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?(digit)+)?
ws          {delim}+

%%
/* Rules section */

/* Handle multi-line comments */
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

/* Keywords */
"if"	{words++; printf("%s : IF\n", yytext);}
"else"	{words++; printf("%s : ELSE\n", yytext);}
"return"	{words++; printf("%s : RETURN\n", yytext);}
						
/* Data types */
"int"	{words++; chars += strlen(yytext); printf("%s : TYPE\n", yytext);}
"char"	{words++; chars += strlen(yytext); printf("%s : TYPE\n", yytext);}
		
/* Other keywords */
"write"	{words++; chars += strlen(yytext); printf("%s : KEYWORD\n", yytext);}
		
/* Identifiers */
{ID}	{words++; chars += strlen(yytext); printf("%s : IDENTIFIER\n",yytext);}
			
/* Numbers */
{NUMBER}	{words++; chars += strlen(yytext); printf("%s : NUMBER\n",yytext);}
			
/* Punctuation and operators */
";"		{chars++; printf("%s : SEMICOLON\n", yytext);}
"="		{chars++; printf("%s : EQ\n", yytext);}
"+"		{chars++; printf("%s : PLUS\n", yytext);}
"-"		{chars++; printf("%s : MINUS\n", yytext);}
"*"		{chars++; printf("%s : MULT\n", yytext);}
"/"		{chars++; printf("%s : DIV\n", yytext);}
"{"     {chars++; printf("%s : LBRACE\n", yytext);}
"}"     {chars++; printf("%s : RBRACE\n", yytext);}
"("     {chars++; printf("%s : LPAREN\n", yytext);}
")"     {chars++; printf("%s : RPAREN\n", yytext);}
"["     {chars++; printf("%s : LBRACK\n", yytext);}
"]"     {chars++; printf("%s : RBRACK\n", yytext);}
		
/* Newline, whitespace, and unrecognized symbols */
\n		{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++; printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);}
		
%%
/* User code section */

int main(int argc, char**argv)
{
	#ifdef YYDEBUG
		yydebug = 1;
	#endif
	printf("Compiler started. \n\n");
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yylex();
}
