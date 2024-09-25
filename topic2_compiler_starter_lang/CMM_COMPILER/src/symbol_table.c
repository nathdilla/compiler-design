#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
    Create a new symbol table with a given size
*/
symbol_table* create_symbol_table(int size) {
    symbol_table* new_table = (symbol_table*)malloc(sizeof(symbol_table));
    if (!new_table) return 0;

    new_table->size = size;
    new_table->table = (symbol**)malloc(sizeof(symbol*) * size);
    if (!new_table->table) {
        free(new_table);
        return 0;
    }

    for (int i = 0; i < size; i++) {
        new_table->table[i] = 0;
    }

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
}

/*
    Lookup a symbol in the symbol table by name

    Returns a pointer to the symbol if found, NULL otherwise
*/
symbol* lookup(symbol_table* table, char* name) {
    printf("Looking up %s\n", name);
    unsigned int hashval = hash(table, name);
    #include <stddef.h> // Include the header file for NULL macro

    // Search the linked list at table->table[hashval]
    // Check if the entry at hashval is null

    if (table->table[hashval] == NULL) {
        printf("No symbol found at hash value %u\n", hashval);
        return NULL;
    } else {
            printf("Symbol found at hash value %u\n", hashval);
            for (symbol* sym = table->table[hashval]; sym != 0; sym = sym->next) {
                printf("Symbol name: %s\n", sym->name);
                if (strcmp(name, sym->name) == 0) return sym;
            }
      }   
    
    return NULL;
}

/*
    Free the symbol table and all symbols in it
*/
void free_table(symbol_table* table) {
    for (int i = 0; i < table->size; i++) {
        symbol* sym = table->table[i];
        while (sym != 0) {
            symbol* next_symbol = sym->next;
            free(sym->name);
            free(sym->type);
            // Free other dynamically allocated fields of Symbol
            free(sym);
            sym = next_symbol;
        }
    }
    free(table->table);
    free(table);
}

void print_table(symbol_table* table) {
    printf("----- SYMBOL TABLE -----\n");
    for (int i = 0; i < table->size; i++) {
        symbol* sym = table->table[i];
        while (sym != 0) {
            printf("Name: %s, Type: %s\n", sym->name, sym->type);
            // Print other fields of Symbol
            sym = sym->next;
        }
    }
    printf("------------------------\n");
}  // For debugging