#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "semantic.h"
#include <stdbool.h>
#include <ctype.h>

#define MAX_TAC 1000

TAC* live_definitions[MAX_TAC];


void add_live_definition(TAC* tac);
void remove_live_definition(const char* var);
char* lookup_live_definition(const char* var);

void optimize_TAC(TAC** head);
bool is_constant(const char* str);
bool is_variable(const char* str);
// bool is_temp_var(const char* str);
void constant_folding(TAC** head);
void constant_propagation(TAC** head);
void copy_propagation(TAC** head);
void dead_code_elimination(TAC** head);
void print_optimized_TAC(const char* filename, TAC* head);

#endif // OPTIMIZER_H