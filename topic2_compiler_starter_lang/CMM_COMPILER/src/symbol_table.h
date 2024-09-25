#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include <string.h>

// Symbol structure

// Define the Symbol struct
typedef struct symbol {
    char* name;
    char* type;
    struct symbol* next;
    // Add other fields of Symbol
} symbol;

// Define the SymbolTable struct
typedef struct symbol_table {
    int size;
    struct symbol** table;
} symbol_table;

// Function declarations
symbol_table* create_symbol_table(int size);
void add_symbol(symbol_table* table, char* name, char* type);
symbol* lookup(symbol_table* table, char* name);
void free_table(symbol_table* table);
void print_table(symbol_table* table);  // For debugging

#endif // SYMBOL_TABLE_H