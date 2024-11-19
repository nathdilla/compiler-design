#include "optimizer.h"
#include "symbol_table.h"
#include <stdbool.h>
#include <ctype.h>

TAC *live_definitions[MAX_TAC];

void optimize_TAC(TAC **head)
{
    constant_propagation(head);
    constant_folding(head);
    // copy_Propagation(head);
    dead_code_elimination(head);
}

int live_definitions_count = 0;

void add_live_definition(TAC *tac)
{
    char *existing_definition = lookup_live_definition(tac->result);
    if (existing_definition != NULL)
    {
        // printf("Removed live definition: %s = %s\n", tac->result, existing_definition);
        remove_live_definition(tac->result);
    }
    if (live_definitions_count < MAX_TAC)
    {
        live_definitions[live_definitions_count++] = tac;
        printf("Added live definition: %s = %s\n", tac->result, tac->arg1);
    }
}

void remove_live_definition(const char *var)
{
    for (int i = 0; i < live_definitions_count; ++i)
    {
        if (strcmp(live_definitions[i]->result, var) == 0)
        {
            for (int j = i; j < live_definitions_count - 1; ++j)
            {
                live_definitions[j] = live_definitions[j + 1];
            }
            --live_definitions_count;
            printf("Removed live definition: %s\n", var);
            break;
        }
    }
}

char *lookup_live_definition(const char *var)
{
    for (int i = 0; i < live_definitions_count; ++i)
    {
        if (strcmp(live_definitions[i]->result, var) == 0)
        {
            return live_definitions[i]->arg1;
        }
    }
    return NULL;
}

bool is_constant(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return false;
    }
    if (str[0] == '-' || str[0] == '+')
    {
        str++;
    }
    bool has_dot = false;
    while (*str)
    {
        if (!isdigit(*str))
        {
            if (*str == '.' && !has_dot)
            {
                has_dot = true;
            }
            else
            {
                return false;
            }
        }
        str++;
    }
    return true;
}

bool is_variable(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return false;
    }
    // Exclude numbers and temporary variables
    if (isdigit(*str) || (str[0] == '-' && isdigit(str[1])))
    {
        return false;
    }
    if (str[0] == 't' && isdigit(str[1]))
    {
        return false; // Exclude temporaries
    }
    // Check for valid variable names
    while (*str)
    {
        if (!isalnum(*str) && *str != '_')
        {
            return false;
        }
        str++;
    }
    return true;
}

void constant_propagation(TAC **head)
{
    printf("\n**Constant Propagation**\n\n");
    TAC *current = *head;
    while (current != NULL)
    {
        if (strcmp(current->op, "assign") == 0 && is_variable(current->result) && is_constant(current->arg1))
        {
            add_live_definition(current);
        }
        if (strcmp(current->op, "load") == 0 && is_variable(current->arg1))
        {
            add_live_definition(current);
        }
        if (is_variable(current->arg1) && lookup_live_definition(current->arg1) && strcmp(current->op, "return") != 0) { // change it only if this is the most recent definition
            printf("Replacing %s with %s\n", current->arg1, lookup_live_definition(current->arg1));
            current->arg1 = lookup_live_definition(current->arg1);
        }
        if (is_temp_var(current->arg1) && lookup_live_definition(current->arg1)) {
            char* definition = lookup_live_definition(current->arg1);
            if (is_constant(lookup_live_definition(definition))) {
                if (definition != NULL) {
                    printf("Replacing %s with %s\n", current->arg1, definition);
                    current->arg1 = definition;
                };
            }
        }
        if (is_variable(current->arg2) && lookup_live_definition(current->arg2) && strcmp(current->op, "return") != 0) { // change it only if this is the most recent definition
            printf("Replacing %s with %s\n", current->arg2, lookup_live_definition(current->arg2));
            current->arg2 = lookup_live_definition(current->arg2);
        }
        if (is_temp_var(current->arg2) && lookup_live_definition(current->arg2)) {
            char* definition = lookup_live_definition(current->arg2);
            if (is_constant(lookup_live_definition(definition))) {
                if (definition != NULL) {
                    printf("Replacing %s with %s\n", current->arg2, definition);
                    current->arg2 = definition;
                };
            }
        }
        current = current->next;
    }
}

void constant_folding(TAC **head)
{
    printf("\n**Constant Folding**\n\n");
    TAC *current = *head;
    while (current != NULL)
    {
        if (is_constant(current->arg1) && is_constant(current->arg2) && (strcmp(current->op, "+") == 0 || strcmp(current->op, "-") == 0 || strcmp(current->op, "*") == 0 || strcmp(current->op, "/") == 0))
        {
            printf("consts");
            char *result_str = (char *)malloc(20);
            if (strcmp(current->type, "int") == 0) {
                printf("int\n");
                int result;
                int arg1 = atoi(current->arg1);
                int arg2 = atoi(current->arg2);
                if (strcmp(current->op, "+") == 0)
                    result = arg1 + arg2;
                else if (strcmp(current->op, "-") == 0)
                    result = arg1 - arg2;
                else if (strcmp(current->op, "*") == 0)
                    result = arg1 * arg2;
                else if (strcmp(current->op, "/") == 0 && arg2 != 0)
                    result = arg1 / arg2;
                else
                {
                    current = current->next;
                    continue;
                }
                sprintf(result_str, "%d", result);
                printf("Folded constant operation: %s = %d\n", current->result, result);
            } else if (strcmp(current->type, "float") == 0) {
                printf("float\n");
                float result;
                float arg1 = atof(current->arg1);
                float arg2 = atof(current->arg2);
                if (strcmp(current->op, "+") == 0)
                    result = arg1 + arg2;
                else if (strcmp(current->op, "-") == 0)
                    result = arg1 - arg2;
                else if (strcmp(current->op, "*") == 0)
                    result = arg1 * arg2;
                else if (strcmp(current->op, "/") == 0 && arg2 != 0)
                    result = arg1 / arg2;
                else
                {
                    current = current->next;
                    continue;
                }
                sprintf(result_str, "%f", result);
                printf("Folded constant operation: %s = %f\n", current->result, result);
            }
            
            current->op = "li";
            current->arg1 = result_str;
            current->arg2 = NULL;
        }
        current = current->next;
    }
}
void print_optimized_TAC(const char *filename, TAC *head)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    TAC *current = head;
    while (current != NULL)
    {
        if (current->dead)
        {
            current = current->next;
            continue;
        }
        // fprintf(file, "%s : ", current->op);
        if (strcmp(current->op, "declare") == 0)
        {
            fprintf(file, "%s declare\n", current->result);
        }
        else if (strcmp(current->op, "assign") == 0)
        {
            fprintf(file, "%s = %s\n", current->result, current->arg1);
        }
        else if (strcmp(current->op, "load") == 0)
        {
            fprintf(file, "%s = %s\n", current->result, current->arg1);
        }
        else if (strcmp(current->op, "li") == 0)
        {
            fprintf(file, "%s li %s\n", current->result, current->arg1);
        }
        else if (strcmp(current->op, "+") == 0)
        {
            fprintf(file, "%s = %s + %s\n", current->result, current->arg1, current->arg2);
        }
        else if (strcmp(current->op, "write") == 0)
        {
            fprintf(file, "write %s\n", current->result);
        }
        current = current->next;
    }
    printf("Optimized TAC written to %s\n", filename);
    fclose(file);
}

bool is_live_var(const char *var, char *live_vars[], int live_vars_count)
{
    for (int i = 0; i < live_vars_count; ++i)
    {
        if (strcmp(live_vars[i], var) == 0)
        {
            return true;
        }
    }
    return false;
}

void remove_var(const char *var, char *live_vars[], int *live_vars_count)
{
    for (int i = 0; i < *live_vars_count; ++i)
    {
        if (strcmp(live_vars[i], var) == 0)
        {
            // Shift the remaining variables
            for (int j = i; j < *live_vars_count - 1; ++j)
            {
                live_vars[j] = live_vars[j + 1];
            }
            --(*live_vars_count);
            break;
        }
    }
}

void dead_code_elimination(TAC **tac)
{
    printf("\n**Dead Code Elimination**\n\n");
    TAC *tac_list[MAX_TAC];
    int tac_count = 0;
    TAC *current = *tac;

    // Read TAC into an array
    while (current != NULL)
    {
        tac_list[tac_count++] = current;
        current->dead = false; // Initialize all instructions as alive
        current = current->next;
    }

    char *live_vars[MAX_TAC];
    int live_vars_count = 0;

    // Traverse TAC instructions backward
    for (int i = tac_count - 1; i >= 0; --i)
    {
        TAC *instr = tac_list[i];

        // Always keep declare statements and write statements
        if (strcmp(instr->op, "declare") == 0 || strcmp(instr->op, "write") == 0)
        {
            continue;
        }

        // Update live variables
        // Add variables used in the instruction
        if (instr->arg1 && (is_variable(instr->arg1) || is_temp_var(instr->arg1)))
        {
            if (!is_live_var(instr->arg1, live_vars, live_vars_count))
            {
                live_vars[live_vars_count++] = instr->arg1;
            }
        }
        if (instr->arg2 && (is_variable(instr->arg2) || is_temp_var(instr->arg2)))
        {
            if (!is_live_var(instr->arg2, live_vars, live_vars_count))
            {
                live_vars[live_vars_count++] = instr->arg2;
            }
        }

        // Determine if the instruction is dead
        bool is_dead = false;

        if (instr->result)
        {
            if (is_temp_var(instr->result))
            {
                // For temporaries, check if they are used later
                if (!is_live_var(instr->result, live_vars, live_vars_count))
                {
                    is_dead = true;
                }
                else
                {
                    // Remove the temporary from live_vars since it's now defined
                    remove_var(instr->result, live_vars, &live_vars_count);
                }
            }
            else if (is_variable(instr->result))
            {
                // For variables, keep all assignments and arithmetic operations
                if (strcmp(instr->op, "+") == 0 || strcmp(instr->op, "-") == 0 ||
                    strcmp(instr->op, "*") == 0 || strcmp(instr->op, "/") == 0 ||
                    strcmp(instr->op, "assign") == 0)
                {
                    is_dead = false;
                }
                // Remove the variable from live_vars if it's there
                if (is_live_var(instr->result, live_vars, live_vars_count))
                {
                    remove_var(instr->result, live_vars, &live_vars_count);
                }
            }
        }

        if (is_dead)
        {
            // Mark instruction as dead
            printf("Removing dead code: %s\n", instr->result);
            instr->dead = true;
        }
    }

    // Reconstruct the TAC linked list, skipping dead instructions
    TAC *new_head = NULL;
    TAC *new_tail = NULL;
    for (int i = 0; i < tac_count; ++i)
    {
        TAC *instr = tac_list[i];
        if (!instr->dead)
        {
            if (new_head == NULL)
            {
                new_head = instr;
                new_tail = instr;
                instr->next = NULL;
            }
            else
            {
                new_tail->next = instr;
                new_tail = instr;
                instr->next = NULL;
            }
        }
    }
    *tac = new_head;
}