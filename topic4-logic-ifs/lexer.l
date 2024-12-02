%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()
#include "parser.tab.h"

int words = 0;
int chars = 0;
int lines = 0;

%}

letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
delim       [ \t\n]
NUMBER         [+-]?{digit}+
FLOAT          [+-]?{digit}+"."{digit}+(E[+\-]?{digit}+)?
ws             {delim}+

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
						
"int"	{words++; chars += strlen(yytext);
		 printf("%s : TYPE\n", yytext);
		 yylval.string = strdup(yytext); 
		 return TYPE;
		}

"float"	{words++; chars += strlen(yytext);
		 printf("%s : TYPE\n", yytext);
		 yylval.string = strdup(yytext); 
		 return TYPE;
		}

"bool"	{words++; chars += strlen(yytext);
		 printf("%s : TYPE\n", yytext);
		 yylval.string = strdup(yytext); 
		 return TYPE;
		}

"void"	{words++; chars += strlen(yytext);
		 printf("%s : TYPE\n", yytext);
		 yylval.string = strdup(yytext); 
		 return TYPE;
		}

"TRUE"	{words++; chars += strlen(yytext);
		 printf("%s : BOOL\n", yytext);
		 yylval.string = strdup(yytext); 
		 return BOOL;
		}

"FALSE"	{words++; chars += strlen(yytext);
		 printf("%s : BOOL\n", yytext);
		 yylval.string = strdup(yytext); 
		 return BOOL;
		}
		
"write"	{words++; 
		 chars += strlen(yytext);
		 printf("%s : WRITE\n", yytext);
		 yylval.string = strdup(yytext);
		 return WRITE;
		}

"return"	{words++; 
		 chars += strlen(yytext);
		 printf("%s : RETURN\n", yytext);
		 yylval.string = strdup(yytext);
		 return RETURN;
		}

"function" {words++; chars += strlen(yytext);
		 printf("%s : FUNC\n", yytext);
		 yylval.string = strdup(yytext); 
		 return FUNC;
		}

"table" {words++; chars += strlen(yytext);
		 printf("%s : ARRAY\n", yytext);
		 yylval.string = strdup(yytext); 
		 return ARRAY;
		}

"if"	{words++; chars += strlen(yytext);
		 printf("%s : IF\n", yytext);
		 yylval.string = strdup(yytext); 
		 return IF;
		}

"else"	{words++; chars += strlen(yytext);
		 printf("%s : ELSE\n", yytext);
		 yylval.string = strdup(yytext); 
		 return ELSE;
		}

"while" {
		 words++; chars += strlen(yytext);
		 printf("%s : WHILE\n", yytext);
		 yylval.string = strdup(yytext); 
		 return WHILE;
		}
			
"="		{chars++;
		 printf("%s : EQ\n", yytext);
		 yylval.operator = strdup(yytext);
		 return EQ;
		}

"+"		{chars++;
		 printf("%s : PLUS\n", yytext);
		 yylval.operator = strdup(yytext);
		 return PLUS;
		}

"-"		{chars++;
		 printf("%s : MINUS\n", yytext);
		 yylval.operator = strdup(yytext);
		 return MINUS;
		}

"*"		{chars++;
		 printf("%s : STAR\n", yytext);
		 yylval.operator = strdup(yytext);
		 return STAR;
		}

"/"		{chars++;
		 printf("%s : BSLASH\n", yytext);
		 yylval.operator = strdup(yytext);
		 return BSLASH;
		}

{ID}	{words++; chars += strlen(yytext);
			  printf("%s : IDENTIFIER\n",yytext);
			  yylval.string = strdup(yytext); 
			  return ID;
		}
			
{NUMBER}	{words++; chars += strlen(yytext);
			  printf("%s : NUMBER\n",yytext);
			  yylval.number = atoi(yytext);
			  return NUMBER;
			}

{FLOAT}	{words++; chars += strlen(yytext);
			  printf("%s : FLOAT\n",yytext);
			  yylval.fval = atof(yytext);
			  return FLOAT;
			}

";"		{chars++;	
		  printf("%s : SEMICOLON\n", yytext);
		  yylval.string = strdup(yytext); 
		  return SEMICOLON;
		}

"{"		{chars++;
		  printf("%s : LCURBRACK\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LCURBRACK;
		}

"}"		{chars++;
		  printf("%s : RCURBRACK\n", yytext);
		  yylval.string = strdup(yytext); 
		  return RCURBRACK;
		}

"["		{chars++;
			printf("%s : LBRACK\n", yytext);
			yylval.string = strdup(yytext); 
			return LBRACK;
		}

"]"		{chars++;
			printf("%s : RBRACK\n", yytext);
			yylval.string = strdup(yytext); 
			return RBRACK;
		}

"("		{chars++;
		  printf("%s : LPAREN\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LPAREN;
		}

")"		{chars++;
		  printf("%s : RPAREN\n", yytext);
		  yylval.string = strdup(yytext); 
		  return RPAREN;
		}

","		{chars++;
		  printf("%s : COMMA\n", yytext);
		  yylval.string = strdup(yytext); 
		  return COMMA;
		}

"."		{chars++;
		  printf("%s : DOT\n", yytext);
		  yylval.string = strdup(yytext); 
		  return DOT;
		}

"=="	{chars += 2;
		  printf("%s : EQEQ\n", yytext);
		  yylval.string = strdup(yytext); 
		  return EQEQ;
		}

"!="	{chars += 2;
		  printf("%s : NEQ\n", yytext);
		  yylval.string = strdup(yytext); 
		  return NEQ;
		}

"<"		{chars++;
		  printf("%s : LT\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LT;
		}

"<="	{chars += 2;
		  printf("%s : LTEQ\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LTEQ;
		}

">"		{chars++;
		  printf("%s : GT\n", yytext);
		  yylval.string = strdup(yytext); 
		  return GT;
		}

">="	{chars += 2;
		  printf("%s : GTEQ\n", yytext);
		  yylval.string = strdup(yytext); 
		  return GTEQ;
		}

"&&"	{chars += 2;
		  printf("%s : AND\n", yytext);
		  yylval.string = strdup(yytext); 
		  return AND;
		}

"||"	{chars += 2;
		  printf("%s : OR\n", yytext);
		  yylval.string = strdup(yytext); 
		  return OR;
		}

		

\n		{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
		


%%