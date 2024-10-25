#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Symbol structure

// Define the Symbol struct
typedef struct symbol {
    char* name;
    char* type;
    struct symbol* next;
    char* temp_var; // Temporary variable for code generation
    char* value; // Constant value for constant folding
    int stack_offset; // Stack offset for local variables
    bool is_local;
    bool is_param;
    // Add other fields of Symbol
} symbol;

// Define the SymbolTable struct
typedef struct symbol_table {
    char* scope_name;
    int size;
    struct symbol** table;
    struct symbol_table* parent;
} symbol_table;

// Define the ScopeStack struct
typedef struct scope_stack {
    struct symbol_table* top;
} scope_stack;

// Scope stack functions
scope_stack* create_scope_stack();
void push_scope(symbol_table* table);
void pop_scope(scope_stack* stack);
symbol_table* top_scope(scope_stack* stack);
void free_scope_stack(scope_stack* stack);

// Function declarations
symbol_table* create_symbol_table(int size, char* scope_name);
void add_symbol(symbol_table* table, char* name, char* type);
symbol* lookup(symbol_table* table, char* name);
void free_table(symbol_table* table);
void print_table(symbol_table* table);  // For debugging

static scope_stack* scopes;

#endif // SYMBOL_TABLE_H