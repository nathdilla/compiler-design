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
%token <operator> BSLASH
%token <number> NUMBER
%token <string> WRITE
%token <string> RETURN
%token <string> FUNC


%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <ast> Program VarDecl VarDeclList FuncDecl FuncDeclList ParamList Param Block Stmt StmtList Expr BinOp WriteStmt
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
									root->program.stmtList = $2;
									}
		| VarDeclList StmtList { 
									printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = $1;
									root->program.stmtList = $2;
									}
;

VarDeclList
		  	: 						{/*empty, i.e. it is possible not to declare a variable*/}
		  	| 	VarDecl VarDeclList {  
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

FuncDecl
	  	:    	FUNC TYPE ID LPAREN ParamList RPAREN Block
									{ 
									// Scopes will be made compile-time. runtime scopes will be dealt with in the future.
									printf("PARSER: Recognized function declaration\n");
									$$ = malloc(sizeof(ASTNode));
									$$->type = NodeType_FuncDecl;
									$$->funcDecl.funcType = strdup($2);
									$$->funcDecl.funcName = strdup($3);
									$$->funcDecl.paramList = $5;
									$$->funcDecl.block = $7;
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
									}

Block
	  	:    	LBRACK 
			{ 
				printf("PARSER: Entering block\n");
				symbol_table* local_table = create_symbol_table(TABLE_SIZE, "local"); 
				local_table->parent = current_scope;
				previous_scope = current_scope;
				current_scope = local_table; 
			} 	VarDeclList StmtList 
			{
				printf("PARSER: Exiting block\n");
				current_scope = previous_scope;
			}
				RBRACK 	
			{ 
				printf("PARSER: Recognized block\n"); 
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_Block;
				$$->block.varDeclList = $3;
				$$->block.stmtList = $4;
			}

;

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
	| 	NUMBER 			{ 
						printf("PARSER: Recognized number\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_SimpleExpr;
						char buffer[20];
						snprintf(buffer, sizeof(buffer), "%d", $1);
						$$->simpleExpr.number = strdup(buffer);
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
		printf("\n=== TAC OPTIMIZATION ===\n");
		optimize_TAC(&tac_head);
		print_optimized_TAC("optimized_TAC.ir", tac_head);

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