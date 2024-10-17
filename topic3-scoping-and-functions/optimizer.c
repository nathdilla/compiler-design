#include "optimizer.h"
#include "symbol_table.h"
#include <stdbool.h>
#include <ctype.h>

void optimize_TAC(TAC** head) {
    constant_propagation(head);
    constant_folding(head);
    // copy_Propagation(head);
    // dead_CodeElimination(head);
}

int live_definitions_count = 0;

void add_live_definition(TAC* tac) {
    char* existing_definition = lookup_live_definition(tac->result);
    if (existing_definition != NULL) {
        // printf("Removed live definition: %s = %s\n", tac->result, existing_definition);
        remove_live_definition(tac->result);
    }
    if (live_definitions_count < MAX_TAC) {
        live_definitions[live_definitions_count++] = tac;
        printf("Added live definition: %s = %s\n", tac->result, tac->arg1);
    }
}

void remove_live_definition(const char* var) {
    for (int i = 0; i < live_definitions_count; ++i) {
        if (strcmp(live_definitions[i]->result, var) == 0) {
            for (int j = i; j < live_definitions_count - 1; ++j) {
                live_definitions[j] = live_definitions[j + 1];
            }
            --live_definitions_count;
            printf("Removed live definition: %s\n", var);
            break;
        }
    }
}

char* lookup_live_definition(const char* var) {
    for (int i = 0; i < live_definitions_count; ++i) {
        if (strcmp(live_definitions[i]->result, var) == 0) {
            return live_definitions[i]->arg1;
        }
    }
    return NULL;
}

bool is_constant(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    if (str[0] == '-' || str[0] == '+') {
        str++;
    }
    bool has_dot = false;
    while (*str) {
        if (!isdigit(*str)) {
            if (*str == '.' && !has_dot) {
                has_dot = true;
            } else {
                return false;
            }
        }
        str++;
    }
    return true;
}

bool is_variable(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    if (isdigit(*str)) {
        return false;
    }
    if (str[0] == 't' && isdigit(str[1])) {
        return false;
    }
    while (*str) {
        if (!isalnum(*str) && *str != '_') {
            return false;
        }
        str++;
    }
    return true;
}

void constant_propagation(TAC** head) {
    TAC* current = *head;
    while (current != NULL) {
        if (strcmp(current->op, "assign") == 0 && is_variable(current->result) && is_constant(current->arg1)) {
            add_live_definition(current);
        }
        if (strcmp(current->op, "load") == 0 && is_variable(current->arg1)) {
            add_live_definition(current);
        }
        if (is_variable(current->arg1)) { // change it only if the this is the most recent definition
            printf("Replacing %s with %s\n", current->arg1, lookup_live_definition(current->arg1));
            current->arg1 = lookup_live_definition(current->arg1);
        }
        if (is_temp_var(current->arg1)) {
            char* definition = lookup_live_definition(current->arg1);
            if (definition != NULL) {
                printf("Replacing %s with %s\n", current->arg1, definition);
                current->arg1 = definition;
            };
        }
        current = current->next;
    }
}

void constant_folding(TAC** head) {
    TAC* current = *head;
    while (current != NULL) {
        if (strcmp(current->op, "+") == 0 && is_constant(current->arg1) && is_constant(current->arg2)) {
            int arg1 = atoi(current->arg1);
            int arg2 = atoi(current->arg2);
            int result = arg1 + arg2;
            char* result_str = (char*)malloc(20);
            sprintf(result_str, "%d", result);
            current->op = "assign";
            current->arg1 = result_str;
            current->arg2 = NULL;
        }
        current = current->next;
    }
}

// Print the optimized TAC list to a file
void print_optimized_TAC(const char* filename, TAC* head) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    TAC* current = head;
    while (current != NULL) {
        if (strcmp(current->op, "declare") == 0) {
            fprintf(file, "%s = 0\n", current->result);
        } else if (strcmp(current->op, "assign") == 0) {
            fprintf(file, "%s = %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "load") == 0) {
            fprintf(file, "%s = %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "+") == 0) {
            fprintf(file, "%s = %s + %s\n", current->result, current->arg1, current->arg2);
        }
        current = current->next;
    }   
    printf("Optimized TAC written to %s\n", filename);
    fclose(file);
}
