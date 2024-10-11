%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"


extern int yylex();
extern int yyparse();
extern FILE* yyin;    // Declare yyin, the file pointer for the input file


void yyerror(const char* s);

char* current_scope = "global";

#define TABLE_SIZE 100

ASTNode* root = NULL; 
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
%token <char> LBRACK
%token <char> RBRACK
%token <char> LPAREN
%token <char> RPAREN
%token <char> COMMA
%token <operator> EQ
%token <operator> PLUS
%token <operator> MINUS
%token <operator> STAR 
%token <operator> FSLASH
%token <number> NUMBER
%token <string> WRITE
%token <string> RETURN
%token <string> FUNC


%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <ast> Program VarDecl VarDeclList FuncDecl FuncDeclList ParamList Param Block Stmt StmtList Expr BinOp
%start Program

%%

Program
	  	: VarDeclList FuncDeclList  { printf("The PARSER has started\n"); 
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
									// symbol *entry = lookup(sym_table, $2);
									// if (entry != NULL) {
										// yyerror("Variable already declared");
									// } else {
										$$ = malloc(sizeof(ASTNode));
										$$->type = NodeType_VarDecl;
										$$->varDecl.varType = strdup($1);
										$$->varDecl.varName = strdup($2);
										// Set other fields as necessary

									// }
									}
	  	// |   	TYPE ID 			{ 
		// 							yyerror("Missing semicolon after declaring variable");
		// 							printf ("Missing semicolon after declaring variable: %s\n", $2);
		// 							}
;

FuncDeclList
		  	: 						{/*empty, i.e. it is possible not to declare a variable*/}
		  	| 	FuncDecl FuncDeclList {  printf("PARSER: Recognized function declaration list\n"); 
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_FuncDeclList;
									$$->funcDeclList.funcDecl = $1;
									$$->funcDeclList.funcDeclList = $2;
									printASTNode($$);
									// Set other fields as necessary
									}
;

FuncDecl
	  	:    	FUNC TYPE ID LPAREN {current_scope = strdup($3);} ParamList RPAREN Block  { printf("PARSER: Recognized function declaration: %s\n", $2);
									// symbol *entry = lookup(sym_table, $2);
									// if (entry != NULL) {
										// yyerror("Variable already declared");
									// } else {
										$$ = malloc(sizeof(ASTNode));
										$$->type = NodeType_FuncDecl;
										$$->funcDecl.funcType = strdup($2);
										$$->funcDecl.funcName = strdup($3);
										$$->funcDecl.paramList = $6;
										$$->funcDecl.block = $8;
										// Set other fields as necessary

									// }
									}
		// :    	FUNC TYPE ID  { printf("PARSER: Recognized function declaration: %s\n", $3);
		// 							// symbol *entry = lookup(sym_table, $2);
		// 							// if (entry != NULL) {
		// 								// yyerror("Variable already declared");
		// 							// } else {
		// 								$$ = malloc(sizeof(ASTNode));
		// 								$$->type = NodeType_FuncDecl;
		// 								$$->funcDecl.paramList = $6;
		// 								$$->funcDecl.block = $8;
		// 								// Set other fields as necessary

		// 							// }
		// 							}
;

ParamList
		: 						{/*empty, i.e. it is possible not to have any parameters*/}
		| 	Param 				{ printf("PARSER: Recognized single parameter\n");
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_ParamList;
								$$->paramList.param = $1;
								$$->paramList.paramList = NULL;
								// Set other fields as necessary
								}
		| 	Param COMMA ParamList { printf("PARSER: Recognized parameter list with comma\n");
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_ParamList;
								$$->paramList.param = $1;
								$$->paramList.paramList = $3;
								// Set other fields as necessary
								}
;

Param
	  	:    	TYPE ID 			{ printf("PARSER: Recognized parameter: %s\n", $2);
									// symbol *entry = lookup(sym_table, $2);
									// if (entry != NULL) {
										// yyerror("Variable already declared");
									// } else {
										$$ = malloc(sizeof(ASTNode));
										$$->type = NodeType_Param;
										$$->param.varType = strdup($1);
										$$->param.varName = strdup($2);
										// Set other fields as necessary

									// }
									}

Block
	  	:    	LBRACK VarDeclList StmtList RBRACK { printf("PARSER: Recognized block\n"); 
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_Block;
									$$->block.varDeclList = $2;
									$$->block.stmtList = $3;
									// Set other fields as necessary
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
								//symbol* existingSymbol = lookup(sym_table, $1);
								// if (existingSymbol != NULL) {
									printf("Parsed Assignment Statement: %s = ...\n", $1);
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_AssignStmt;
									$$->assignStmt.varName = strdup($1);
									$$->assignStmt.expr = $3;
								// } else {
									// printf("Error: Variable %s not declared\n", $1);
									// yyerror("Undeclared variable");
								// }
 								}
   	| 	WRITE ID SEMICOLON 		{
								//symbol* existingSymbol = lookup(sym_table, $2);
								// if (existingSymbol != NULL) {
									printf("Parsed Write Statement: %s\n", $2);
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_WriteStmt;
									$$->writeStmt.varName = strdup($2);
								// } else {
								// 	printf("Error: Variable %s not declared\n", $2);
								// 	yyerror("Undeclared variable");
								// }
								}
;

Expr
   	: 	Expr BinOp Expr { 
						printf("PARSER: Recognized binary operation\n");
						
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_Expr;
						$$->expr.left = $1;
						$$->expr.right = $3;
						$$->expr.operator = $2->binOp.operator;
						
						// Set other fields as necessary
 						}
	| 	ID 				{ printf("ASSIGNMENT statement \n"); 
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_SimpleID;
						$$->simpleID.name = $1;
						}
	| 	NUMBER 			{ 
						printf("PARSER: Recognized number\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_SimpleExpr;
						$$->simpleExpr.number = ($1);
						// Set other fields as necessary
						}
;

BinOp: PLUS {
				printf("PARSER: Recognized binary operation (addition)\n");	
				$ = malloc(sizeof(ASTNode));
				$->type = NodeType_BinOp;
				$->binOp.operator = *$1;
}

BinOp: MINUS {
				printf("PARSER: Recognized binary operation (subtraction)\n");
				$ = malloc(sizeof(ASTNode));
				$->type = NodeType_BinOp;
				$->binOp.operator = *$1;
}

BinOp: STAR {
				printf("PARSER: Recognized binary operation (multiplication)\n");
				$ = malloc(sizeof(ASTNode));
				$->type = NodeType_BinOp;
				$->binOp.operator = *$1;
}

BinOp: FSLASH {
				printf("PARSER: Recognized binary operation (division)\n");
				$ = malloc(sizeof(ASTNode));
				$->type = NodeType_BinOp;
				$->binOp.operator = *$1;
				// Note: Division by zero check should be implemented in the semantic analysis or code generation phase
				printf("WARNING: Remember to check for division by zero during semantic analysis or code generation\n");
}
;

%%

int main() {
    // Initialize file or input source
    yyin = fopen("testProg.cmm", "r");
    if (yyparse() == 0) {
        // Successfully parsed
		printf("Parsing successful!\n");
        traverseAST(root, 0);

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