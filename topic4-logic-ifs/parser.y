%{
	
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
%}

%union {
	int number;
	float fval;
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
%token <char> LCURBRACK
%token <char> RCURBRACK
%token <char> LPAREN
%token <char> RPAREN
%token <char> COMMA
%token <char> DOT
%token <char> EQEQ
%token <char> NEQ
%token <char> LT
%token <char> GT
%token <char> LTEQ
%token <char> GTEQ
%token <char> AND
%token <char> OR
%token <char> NOT
%token <operator> EQ
%token <operator> PLUS
%token <operator> MINUS
%token <operator> STAR 
%token <operator> BSLASH
%token <string> BOOL
%token <number> NUMBER
%token <fval> FLOAT
%token <string> WRITE
%token <string> RETURN
%token <string> FUNC
%token <string> ARRAY
%token <string> IF


%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <ast> Program VarDecl VarDeclList FuncDecl FuncDeclList ParamList Param Block Stmt StmtList Expr BinOp WriteStmt ReturnStmt FuncSignature InputParamList InputParam ArrayDecl ArrayDeclList LogicExpr IfBlock IfStmt
%start Program

%left PLUS MINUS
%left STAR BSLASH

%%

Program
	  	: VarDeclList FuncDeclList StmtList { 
									printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = $1;
									root->program.funcDeclList = $2;
									root->program.stmtList = $3;
									}
		| VarDeclList StmtList { 
									printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = $1;
									root->program.stmtList = $2;
									}
;

ArrayDeclList
		  	: 						{/*empty, i.e. it is possible not to declare an array*/}
		  	| 	ArrayDecl ArrayDeclList {  
									printf("PARSER: Recognized array declaration list\n"); 
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_ArrayDeclList;
									$$->arrayDeclList.arrayDecl = $1;
									$$->arrayDeclList.arrayDeclList = $2;
									printASTNode($$);
									}
								
ArrayDecl
		:    ARRAY TYPE ID LBRACK NUMBER RBRACK SEMICOLON { 
									printf("PARSER: Recognized array declaration: %s\n", $3);
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_ArrayDecl;
									$$->arrayDecl.varType = strdup($2);
									$$->arrayDecl.varName = strdup($3);
									char buffer[20];
									snprintf(buffer, sizeof(buffer), "%d", $5);
									$$->arrayDecl.size = strdup(buffer);

									printf("\nAdding array symbol: {%s} to table {%s}\n", $3, current_scope->scope_name);
									add_symbol(current_scope, $3, $2);
									print_table(current_scope);
								}
;

VarDeclList
		  	: 						{/*empty, i.e. it is possible not to declare a variable*/}
		  	| 	VarDeclList VarDecl {  
									printf("PARSER: Recognized variable declaration list\n"); 
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_VarDeclList;
									$$->varDeclList.varDecl = $1;
									$$->varDeclList.varDeclList = $2;
									printASTNode($$);
									}
;

VarDecl
	  	:    TYPE ID SEMICOLON   { 
									symbol *entry = lookup(current_scope, $2);
									if (entry != NULL) {
										yyerror("Variable already declared");
									} else {
										printf("PARSER: Recognized variable declaration: %s\n", $2);
										$$ = malloc(sizeof(ASTNode));
										$$->type = NodeType_VarDecl;
										$$->varDecl.varType = strdup($1);
										$$->varDecl.varName = strdup($2);

										printf("\nAdding symbol: {%s} to table {%s}\n", $2, current_scope->scope_name);
										add_symbol(current_scope, $2, $1);
										print_table(current_scope);
									}
								}
;

FuncDeclList
		  	: 							{/*empty, i.e. it is possible not to declare a variable*/}
		  	| 	FuncDecl FuncDeclList 	{  
										printf("PARSER: Recognized function declaration list\n"); 
										$$ = malloc(sizeof(ASTNode));
										$$->type = NodeType_FuncDeclList;
										$$->funcDeclList.funcDecl = $1;
										$$->funcDeclList.funcDeclList = $2;
										printASTNode($$);
										}
;

FuncSignature
	  	:    	FUNC TYPE ID 	{ 
								printf("PARSER: Recognized function signature\n");
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_FuncSignature;
								$$->funcSignature.funcType = strdup($2);
								$$->funcSignature.funcName = strdup($3);
								}

FuncDecl
	  	:    	FuncSignature 
				{
					printf("PARSER: Entering function scope\n");
					symbol_table* local_table = create_symbol_table(TABLE_SIZE, $1->funcSignature.funcName); 
					$1->funcSignature.scope = local_table;
					local_table->parent = current_scope;
					previous_scope = current_scope;
					current_scope = local_table; 
				} 
				LPAREN ParamList RPAREN Block
				{ 
					// Scopes will be made compile-time. runtime scopes will be dealt with in the future.
					printf("PARSER: Recognized function declaration\n");
					$$ = malloc(sizeof(ASTNode));
					$$->type = NodeType_FuncDecl;
					$$->funcDecl.funcType = strdup($1->funcSignature.funcType);
					$$->funcDecl.funcName = strdup($1->funcSignature.funcName);
					$$->funcDecl.funcSignature = $1;
					$$->funcDecl.paramList = $4;
					$$->funcDecl.block = $6;
					$$->funcDecl.scope = current_scope;
					printf("PARSER: Exiting function scope\n");
					current_scope = previous_scope;
				}
;

ParamList
		: 						{/*empty, i.e. it is possible not to have any parameters*/}
		| 	Param 				{ printf("PARSER: Recognized single parameter\n");
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_ParamList;
								$$->paramList.param = $1;
								$$->paramList.paramList = NULL;
								}
		| 	Param COMMA ParamList 	{ 
									printf("PARSER: Recognized parameter list with comma\n");
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_ParamList;
									$$->paramList.param = $1;
									$$->paramList.paramList = $3;
									}
;

Param
	  	:    	TYPE ID 			{
									printf("PARSER: Recognized parameter: %s\n", $2);
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_Param;
									$$->param.varType = strdup($1);
									$$->param.varName = strdup($2);
									printf("\nAdding PARAMETER symbol: {%s} to table {%s}\n", $2, current_scope->scope_name);
									add_symbol(current_scope, $2, $1);
									print_table(current_scope);
									}

InputParamList
		: 						{/*empty, i.e. it is possible not to have any input parameters*/}
		| 	InputParam 			{ 
								printf("PARSER: Recognized single input parameter\n");
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_InputParamList;
								$$->inputParamList.inputParam = $1;
								$$->inputParamList.inputParamList = NULL;
								}
		| 	InputParam COMMA InputParamList 	{ 
											printf("PARSER: Recognized input parameter list with comma\n");
											$$ = malloc(sizeof(ASTNode));
											$$->type = NodeType_InputParamList;
											$$->inputParamList.inputParam = $1;
											$$->inputParamList.inputParamList = $3;
											}
;

InputParam
		:    	ID 			{
							printf("PARSER: Recognized input parameter ID: %s\n", $1);
							$$ = malloc(sizeof(ASTNode));
							$$->type = NodeType_InputParam;
							$$->inputParam.value = strdup($1);
							}
		| 	NUMBER 		{
							printf("PARSER: Recognized input parameter number: %d\n", $1);
							$$ = malloc(sizeof(ASTNode));
							$$->type = NodeType_InputParam;
							char buffer[20];
							snprintf(buffer, sizeof(buffer), "%d", $1);
							$$->inputParam.value = strdup(buffer);
							}
;

Block
	  	:    	LCURBRACK ArrayDeclList VarDeclList StmtList ReturnStmt RCURBRACK 					
			{ 
				printf("PARSER: Recognized block\n"); 
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_Block;
				$$->block.varDeclList = $3;
				$$->block.arrayDeclList = $2;
				$$->block.stmtList = $4;
				$$->block.returnStmt = $5;
			}

;

ReturnStmt
	  	:    	RETURN Expr SEMICOLON 	{ 
										printf("PARSER: Recognized return statement\n");
										$$ = malloc(sizeof(ASTNode));
										$$->type = NodeType_ReturnStmt;
										$$->returnStmt.expr = $2;
										}

StmtList
	   	:   				{/*empty, i.e. it is possible not to have any statement*/}
	   	| 	Stmt StmtList 	{ printf("PARSER: Recognized statement list\n");
							$$ = malloc(sizeof(ASTNode));
							$$->type = NodeType_StmtList;
							$$->stmtList.stmt = $1;
							$$->stmtList.stmtList = $2;
							}
;

Stmt
  	: 	ID EQ Expr SEMICOLON 	{
									printf("Parsed Assignment Statement: %s = ...\n", $1);
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_AssignStmt;
									$$->assignStmt.varName = strdup($1);
									$$->assignStmt.expr = $3;
									symbol *entry = lookup(current_scope, $1);
									if (entry == NULL) {
										yyerror("Variable not declared");
									} else if ($3->type == NodeType_SimpleExpr) {
										entry->value = $3->simpleExpr.number;
										print_table(current_scope);
									}
 								}
   	| 	WriteStmt 				{
									$$ = $1;
								}
	|   ID LPAREN InputParamList RPAREN SEMICOLON {
									printf("Parsed Function Call: %s()\n", $1);
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_FuncCall;
									$$->funcCall.funcName = strdup($1);
									// $$->funcCall.paramList = NULL;
								}
	|   ID LBRACK NUMBER RBRACK EQ Expr SEMICOLON {
									printf("Parsed Array Assignment: %s[%d] = ...\n", $1, $3);
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_ArrayAssignStmt;
									$$->arrayAssignStmt.varName = strdup($1);
									char buffer[20];
									snprintf(buffer, sizeof(buffer), "%d", $3);
									$$->arrayAssignStmt.index = strdup(buffer);
									$$->arrayAssignStmt.expr = $6;
								}
	| 	IfStmt 				{
									$$ = $1;
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
 						}
	| 	ID 				{ 
						printf("ASSIGNMENT statement \n"); 
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_SimpleID;
						$$->simpleID.name = $1;
						}
	| 	LPAREN TYPE RPAREN Expr 	{ 
						printf("PARSER: Recognized type cast\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_TypeCast;
						$$->typeCast.type = strdup($2);
						$$->typeCast.expr = $4;
						}
	| 	FLOAT {
						printf("PARSER: Recognized float\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_SimpleExpr;
						char buffer[20];
						snprintf(buffer, sizeof(buffer), "%f", $1);
						$$->simpleExpr.number = strdup(buffer);
						$$->simpleExpr.type = "float";
					}
	| 	BOOL {
						printf("PARSER: Recognized boolean\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_SimpleExpr;
						$$->simpleExpr.number = strdup($1);
						$$->simpleExpr.type = "bool";
						}
	| 	NUMBER 			{ 
						printf("PARSER: Recognized number\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_SimpleExpr;
						char buffer[20];
						snprintf(buffer, sizeof(buffer), "%d", $1);
						$$->simpleExpr.number = strdup(buffer);
						$$->simpleExpr.type = "int";
						}
	|   ID LPAREN InputParamList RPAREN 	{
						printf("PARSER: Recognized function call\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_FuncCall;
						$$->funcCall.funcName = strdup($1);
						$$->funcCall.inputParamList = $3;
						}
	|   ID LBRACK NUMBER RBRACK 	{
						printf("PARSER: Recognized array access\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_ArrayAccess;
						$$->arrayAccess.varName = strdup($1);
						char buffer[20];
						snprintf(buffer, sizeof(buffer), "%d", $3);
						$$->arrayAccess.index = strdup(buffer);
						}
;

BinOp: PLUS {
			printf("PARSER: Recognized binary operation (addition)\n");	
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_BinOp;
			$$->binOp.operator = *$1;
}

BinOp: MINUS {
				printf("PARSER: Recognized binary operation (subtraction)\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = *$1;
}

BinOp: STAR {
				printf("PARSER: Recognized binary operation (multiplication)\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = *$1;
}

BinOp: BSLASH {
				printf("PARSER: Recognized binary operation (division)\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = *$1;
				// Note: Division by zero check should be implemented in the semantic analysis or code generation phase
				printf("WARNING: Remember to check for division by zero during semantic analysis or code generation\n");
}

WriteStmt : WRITE ID SEMICOLON {
									printf("PARSER: Recognized write statement\n");
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_WriteStmt;
									$$->writeStmt.varName = strdup($2);
								}
;

LogicExpr
		: Expr EQEQ Expr {
							printf("PARSER: Recognized equality expression\n");
							$$ = malloc(sizeof(ASTNode));
							$$->type = NodeType_LogicExpr;
							$$->logicExpr.left = $1;
							$$->logicExpr.right = $3;
							$$->logicExpr.operator = "==";
						}

IfStmt
		: IF LPAREN LogicExpr RPAREN IfBlock {
									printf("PARSER: Recognized if statement\n");
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_IfStmt;
									$$->ifStmt.condition = $3;
									$$->ifStmt.block = $5;
								}

// IfStmtSignature
// 		: IF LPAREN LogicExpr RPAREN {
// 									printf("PARSER: Recognized if statement signature\n");
// 									$$ = malloc(sizeof(ASTNode));
// 									$$->type = NodeType_IfStmtSignature;
// 									$$->ifStmtSignature.condition = $3;
// 								}

IfBlock
		: LCURBRACK StmtList RCURBRACK {
									printf("PARSER: Recognized if block\n");
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_IfBlock;
									$$->ifBlock.stmtList = $2;
								}
%%

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