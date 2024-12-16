#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
    Create a new symbol table with a given size
*/
symbol_table* create_symbol_table(int size, char* scope_name) {
    symbol_table* new_table = (symbol_table*)malloc(sizeof(symbol_table));
    if (!new_table) return 0;

    new_table->size = size;
    new_table->table = (symbol**)malloc(sizeof(symbol*) * size);
    new_table->scope_name = strdup(scope_name);
    if (!new_table->table) {
        free(new_table);
        return 0;
    }

    for (int i = 0; i < size; i++) {
        new_table->table[i] = 0;
    }

    // push_scope(new_table);

    return new_table;
}

/*
    Hash helper function to calculate the hash value of a string, used to index into the table
*/
unsigned int hash(symbol_table* table, char* name) {
    unsigned int hashval = 0;
    for (; *name != '\0'; name++) hashval = *name + (hashval << 5) - hashval;
    return hashval % table->size;
}

/*
    Add a new symbol to the symbol table by hashing the name and adding it to the appropriate index
*/
void add_symbol(symbol_table* table, char* name, char* type) {
    symbol* new_symbol = (symbol*)malloc(sizeof(symbol));
    if (!new_symbol) return;
    new_symbol->name = strdup(name);
    new_symbol->type = strdup(type);
    // Initialize other fields of Symbol

    if (table == NULL || table->table == NULL) {
        fprintf(stderr, "Symbol table or table array not initialized\n");
        // Handle the error, possibly free newSymbol and return
    }

    unsigned int hashval = hash(table, name);
    new_symbol->next = table->table[hashval];  
    table->table[hashval] = new_symbol;

    // Set is_local to true if the table is not global
    if (strcmp(table->scope_name, "global") != 0) {
        new_symbol->is_local = true;
    } else {
        new_symbol->is_local = false;
    }
}

/*
    Lookup a symbol in the symbol table by name

    Returns a pointer to the symbol if found, NULL otherwise
*/
symbol* lookup(symbol_table* table, char* name) {
    // Traverse through the scope chain (table and its parents)
    while (table != NULL) {
        printf("Looking up %s in scope, %s\n", name, table->scope_name);
        
        unsigned int hashval = hash(table, name);
        
        // Check the symbol table at the hash value
        if (table->table[hashval] == NULL) {
            printf("No symbol found at hash value %u in this scope (%s)\n", hashval, table->scope_name);
        } else {
            printf("Symbol found at hash value %u in this scope\n", hashval);
            for (symbol* sym = table->table[hashval]; sym != NULL; sym = sym->next) {
                printf("Symbol name: %s\n", sym->name);
                if (strcmp(name, sym->name) == 0) {
                    // Symbol found, return it
                    return sym;
                }
            }
        }
        
        // Move to the parent scope if the symbol wasn't found in the current scope
        table = table->parent;
    }
    
    // If no symbol is found in any scope, return NULL
    printf("Symbol %s not found in any scope\n", name);
    return NULL;
}

/*
    Free the symbol table and all symbols in it
*/
void free_table(symbol_table* symbolTable)
{
    if (symbolTable == NULL) {
        printf("Symbol table is NULL. Nothing to free.\n");
        return;
    }

    printf("Starting to free symbol table of size %d\n", symbolTable->size);

    for (int i = 0; i < symbolTable->size; i++) {
        symbol* current = symbolTable->table[i];
        
        // Print current bucket being processed
        //printf("Processing bucket %d\n", i);

        while (current != NULL) {
            //printf("Freeing symbol: %s\n", current->name ? current->name : "NULL");

            symbol* next = current->next;

            // Safely free the symbol's name if it exists
            if (current->name != NULL) {
                //printf("Freeing symbol name: %s\n", current->name);
                free(current->name);
                current->name = NULL; // Avoid double free
            }

            // Free the symbol itself
            //printf("Freeing symbol structure\n");
            free(current);
            current = next;

            // Print status of next symbol to process
            if (current != NULL) {
                //printf("Next symbol in bucket: %s\n", current->name ? current->name : "NULL");
            } else {
                //printf("No more symbols in this bucket.\n");
            }
        }
    }

    // Free the table array and the symbol table itself
    //printf("Freeing the symbol table array.\n");
    free(symbolTable->table);
    symbolTable->table = NULL; // Avoid double free

    //printf("Freeing the symbol table structure itself.\n");
    free(symbolTable);

    //printf("Symbol table freed successfully.\n");
}
void print_table(symbol_table* table) {
    printf("\n\n\n----- SYMBOL TABLE: %s -----\n", table->scope_name);
    for (int i = 0; i < table->size; i++) {
        symbol* sym = table->table[i];
        while (sym != 0) {
            printf("Name: %s, Type: %s, Value: %s\n", sym->name, sym->type, sym->value);
            // Print other fields of Symbol
            sym = sym->next;
        }
    }
    printf("------------------------\n\n\n");
}  // For debugging

scope_stack* create_scope_stack() { 
    scope_stack* new_stack = (scope_stack*)malloc(sizeof(scope_stack));
    if (!new_stack) return NULL;
    new_stack->top = NULL;
    scopes = new_stack;
    return new_stack;
}

void push_scope(symbol_table* table) {
    if (scopes->top == NULL) {
        printf("SYMBOL TABLE: Pushing first scope\n");
        scopes->top = table;
        return;
    } else {
        perror("SYMBOL TABLE: Pushing new scope\n");
        table->parent = scopes->top;
        scopes->top = table;
    }
}

void pop_scope(scope_stack* stack) {

}

symbol_table* top_scope(scope_stack* stack) {
    return NULL;
}

void free_scope_stack(scope_stack* stack) {
    while (stack->top != NULL) {
        pop_scope(stack);
    }
    free(stack);
}