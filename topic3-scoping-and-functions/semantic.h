#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "AST.h"            // definition of ASTNode
#include "symbol_table.h"   // definition of symbol_table

#include "temp.h"

/*
    TAC stands for Three Address Code. It is a simple intermediate representation
    for code generation. Each TAC instruction has an operator and up to three operands.
    For example, an assignment statement x = y + z will be represented as:
    op = '+', arg1 = 'y', arg2 = 'z', result = 'x'
*/
typedef struct TAC {
    char* op;   // Operator
    char* arg1; // Argument 1
    char* arg2; // Argument 2
    char* result; // Result
    struct TAC* next; // Next instruction
} TAC;

/*
We are setting the maximum number of temporary variables to 20 because we are not
implementing register allocation in this project
*/
extern int temp_vars[10]; // Declaration only
extern TAC* tac_head; // Global head of the TAC instructions list

int allocate_temp_var(int temp_vars[]);
void semantic_analysis(ASTNode* node, symbol_table* symTab);
TAC* tac_expr(ASTNode* expr, symbol_table* sym_table); //returns the TAC for the expression to print on console
char* create_temp_var();
char* create_operand(ASTNode* node);
void print_TAC(TAC* tac);
void initialize_temp_vars();
void deallocate_temp_var(int tempVars[], int index);
void append_TAC(TAC** head, TAC* newInstruction);
void print_TAC_to_file(const char* filename, TAC* tac);
// You can add more function declarations related to semantic analysis here

#endif // SEMANTIC_H
