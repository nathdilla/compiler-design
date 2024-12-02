#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "AST.h"            // definition of ASTNode
#include "symbol_table.h"   // definition of symbol_table

#include "temp.h"
#include <stdbool.h>

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
    char* type;
    struct TAC* next; // Next instruction
    symbol_table* scope; // Scope of the instruction
    bool dead; // Add this field
} TAC;
// Stack to hold TAC instructions for backpatching
typedef struct TACStack {
    TAC* tac;
    struct TACStack* next;
} TACStack;

// Function declarations for TAC stack operations
void push_TAC(TACStack** stack, TAC* tac);
TAC* pop_TAC(TACStack** stack);
bool is_TAC_stack_empty(TACStack* stack);

extern int temp_vars[10]; // Declaration only
extern int float_temp_vars[30]; // Declaration only
extern TAC* tac_head; // Global head of the TAC instructions list

// Function to allocate argument registers for parameters
int allocate_arg_register(int arg_regs[], int num_args);
// Function to deallocate argument registers
void deallocate_arg_register(int arg_regs[], int index);
// Function to check if a given string is an argument register
char* get_arg_register(int index);
bool is_arg_register(const char* str);
int allocate_temp_var(int temp_vars[]);
int allocate_float_temp_var(int float_temp_vars[]);
char* create_arg_register();
bool is_temp_var(const char* str);
void semantic_analysis(ASTNode* node, symbol_table* symTab);
TAC* tac_expr(ASTNode* expr, symbol_table* sym_table); //returns the TAC for the expression to print on console
TAC* tac_if_block_header(ASTNode* expr, symbol_table* sym_table);
TAC* tac_condition(ASTNode* expr, symbol_table* sym_table);
TAC* tac_header(ASTNode* expr, symbol_table* sym_table);
char* create_temp_var();
char* create_float_temp_var();
char* create_if_label();
char* create_operand(ASTNode* node);
void print_TAC(TAC* tac);
void initialize_temp_vars();
void deallocate_temp_var(int tempVars[], int index);
void append_TAC(TAC** head, TAC* newInstruction);
void print_TAC_to_file(const char* filename, TAC* tac);
void print_all_TAC(TAC* tac);
// You can add more function declarations related to semantic analysis here

#endif // SEMANTIC_H
