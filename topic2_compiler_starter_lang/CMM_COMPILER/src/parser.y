%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "symbol_table.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);

#define TABLE_SIZE 100

ASTNode* root = NULL; 
symbol_table* sym_table = NULL;
symbol* sym = NULL;
%}

%union {
	int number;
	char character;
	char* string;
	char* operator;
	struct ASTNode* ast;
}

%token <string> TYPE
%token <string> ID
%token <char> SEMICOLON
%token <operator> EQ
%token <char> PLUS
%token <number> NUMBER
%token <string> WRITE

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <ast> Program VarDecl VarDeclList Stmt StmtList Expr BinOp
%start Program

%%

Program
	  	: VarDeclList StmtList  { printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = $1;
									root->program.stmtList = $2;
									// Set other fields as necessary
								}
;

VarDeclList
		  	: 						{/*empty, i.e. it is possible not to declare a variable*/}
		  	| 	VarDecl VarDeclList {  printf("PARSER: Recognized variable declaration list\n"); 
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_VarDeclList;
									$$->varDeclList.varDecl = $1;
									$$->varDeclList.varDeclList = $2;
									printASTNode($$);
									// Set other fields as necessary
									}
;

VarDecl
	  	:    	TYPE ID SEMICOLON   { printf("PARSER: Recognized variable declaration: %s\n", $2);
									symbol *entry = lookup(sym_table, $2);
									if (entry != NULL) {
										yyerror("Variable already declared");
									} else {
										$$ = malloc(sizeof(ASTNode));
										$$->type = NodeType_VarDecl;
										$$->varDecl.varType = strdup($1);
										$$->varDecl.varName = strdup($2);
										// Set other fields as necessary

										add_symbol(sym_table, $2, $1);
										print_table(sym_table);
									}
									}
	  	|   	TYPE ID 			{ 
									yyerror("Missing semicolon after declaring variable");
									printf ("Missing semicolon after declaring variable: %s\n", $2);
									}
;

StmtList
	   	:   				{/*empty, i.e. it is possible not to have any statement*/}
	   	| 	Stmt StmtList 	{ printf("PARSER: Recognized statement list\n");
							$$ = malloc(sizeof(ASTNode));
							$$->type = NodeType_StmtList;
							$$->stmtList.stmt = $1;
							$$->stmtList.stmtList = $2;
							// Set other fields as necessary
							}
;

Stmt
  	: 	ID EQ Expr SEMICOLON 	{ /* code TBD */
								printf("PARSER: Recognized assignment statement\n");
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_Stmt;
								$$->stmt.varName = strdup($1);
								$$->stmt.operator = $2;
								$$->stmt.expr = $3;
								// Set other fields as necessary
 								}
   	| 	WRITE ID SEMICOLON 		{ printf("PARSER: Recognized write statement\n"); }
;

Expr
   	: 	ID BinOp ID		{ 
						printf("PARSER: Recognized binary operation\n");
						/*
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_Expr;
						$$->expr.left = $1;
						$$->expr.right = $3;
						$$->expr.operator = $2;
						*/
						// Set other fields as necessary
 						}
	| 	ID 				{ printf("ASSIGNMENT statement \n"); }
	| 	NUMBER 			{ 
						printf("PARSER: Recognized number\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_SimpleExpr;
						$$->simpleExpr.number = ($1);
						// Set other fields as necessary
						}
;

BinOp: PLUS { /* code TBD */ }
;

%%

int main() {
    // Initialize file or input source
    yyin = fopen("testProg.cmm", "r");

    // Start parsing
	// create an empty symbol table
	sym_table = create_symbol_table(TABLE_SIZE);
	if (sym_table == NULL) {
        // Handle error
        return EXIT_FAILURE;
    }
	// sym = malloc(sizeof(Symbol));
	// initializeTempVars();
    if (yyparse() == 0) {
        // Successfully parsed
		printf("Parsing successful!\n");
        traverseAST(root, 0);
		print_table(sym_table);
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
