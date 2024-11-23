// codeGenerator.c

#include "code_generator.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static FILE* output_file;

symbol_table* current_scope_code_gen = NULL;

typedef struct {
    char* name; // Name of the register, e.g., "$t0"
    bool inUse; // Whether the register is currently in use
} MIPSRegister;

// typedef struct {
//     char* instruction;
//     MIPSinstruction* next;
// } MIPSinstruction;

// MIPSinstruction* global_head = NULL;
// MIPSinstruction* local_head = NULL;
bool in_function = false;

// void add_MIPS_instruction(MIPSinstruction** head, char* instruction) {
//     MIPSinstruction* new_instruction = (MIPSinstruction*)malloc(sizeof(MIPSinstruction));
//     if (!new_instruction) {
//         perror("Failed to allocate memory for MIPS instruction");
//         exit(EXIT_FAILURE);
//     }
//     new_instruction->instruction = instruction;
//     new_instruction->next = NULL;

//     if (!*head) {
//         *head = new_instruction;
//     } else {
//         MIPSinstruction* current = *head;
//         while (current->next) {
//             current = current->next;
//         }
//         current->next = new_instruction;
//     }
// }

// void print_MIPS_to_file(FILE* file, MIPSinstruction* head) {
//     MIPSinstruction* current = head;
//     while (current != NULL) {
//         fprintf(file, "%s", current->instruction);
//         current = current->next;
//     }
// }



// Array of temporary registers, used for register allocation
// and tracking which registers are currently in use

MIPSRegister temp_registers[NUM_TEMP_REGISTERS] = {
    {"$t0", false}, {"$t1", false}, {"$t2", false}, {"$t3", false},
    {"$t4", false}, {"$t5", false}, {"$t6", false}, {"$t7", false},
    {"$t8", false}, {"$t9", false},
};

// Array of register names
const char* register_names[40] = {
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9",
    "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9",
    "f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19",
    "f20", "f21", "f22", "f23", "f24", "f25", "f26", "f27", "f28", "f29",
};

// function to check if input is a register_name
bool is_register_name(const char* str) {
    for (int i = 0; i < 40; i++) {
        if (strcmp(str, register_names[i]) == 0) {
            return true;
        }
    }
    return false;
}

void init_code_generator(const char* output_filename) {
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }
    // Write the data section header
    fprintf(output_file, ".data\n");
}

// Function to handle storing the value
void store_value(FILE* output_file, const char* register_name, const char* result, symbol* sym) {
    fprintf(output_file, "\t# store value of %s\n", result);
    if (sym != NULL && sym->is_local) {
        printf("stack offset: %d\n", sym->stack_offset);
        if (register_name[1] == 'f' && is_register_name(register_name+1)) {
            fprintf(output_file, "\ts.s %s, %d($fp)\n", register_name, sym->stack_offset);
        } else if (register_name[1] == 't' && is_register_name(register_name+1)) {
            fprintf(output_file, "\tsw %s, %d($fp)\n", register_name, sym->stack_offset);
        }
    } else {
        fprintf(output_file, "\tsw %s, var_%s\n", register_name, result);
    }
}

void evaluate_operations(TAC* current, int stack_offset) {
// if (strcmp(current->op, "const") == 0) {
    //     fprintf(output_file, "\tli $%s, %s\n", current->result, current->arg1);
    // }
    if (strcmp(current->op, "assign") == 0) {
        fprintf(output_file, "\t# assignment of %s\n", current->result);
        int tempRegIndex = allocate_register();
        if (tempRegIndex == -1) {
        // Handle register allocation failure
        return;
        }
        // Lookup the symbol for the current result in the current scope
        // printf("%s",current->op);
        symbol* sym = lookup(current_scope_code_gen, current->result);

        if (is_register_name(current->arg1)) {
            // If arg1 is already a temp register, directly store it into the variable
            char tempRegName[10];
            snprintf(tempRegName, sizeof(tempRegName), "$%s", current->arg1);
            store_value(output_file, tempRegName, current->result, sym);
        } else {
            // Load the immediate value into a temp register
            const char* tempRegName = temp_registers[tempRegIndex].name;
            fprintf(output_file, "\tli %s, %s\n", tempRegName, current->arg1);
            
            // Store the temp register value
            store_value(output_file, tempRegName, current->result, sym);
        }
        deallocate_register(tempRegIndex);
    } else if (strcmp(current->op, "li") == 0) {
        if (strcmp(current->type, "int") == 0) {
            fprintf(output_file, "\tli $%s, %s\n", current->result, current->arg1);
        } else if (strcmp(current->type, "float") == 0) {
            // Convert the float value to its hexadecimal bit representation
            float float_val = atof(current->arg1);
            unsigned int hex_val;
            memcpy(&hex_val, &float_val, sizeof(float_val));
            fprintf(output_file, "\tli %s, 0x%08X\n", "$t9", hex_val);
            fprintf(output_file, "\tmtc1 $t9, $%s\n", current->result);
        }
    }
    else if (strcmp(current->op, "write") == 0) {
        symbol* sym = lookup(current_scope_code_gen, current->result);
        printf("writing %s\n", current->result);
        fprintf(output_file, "\t# write %s\n", current->result);
        if (sym && sym->is_param) {
            fprintf(output_file, "\tmove $a0, $%s\n", sym->temp_var);
            fprintf(output_file, "\tli $v0, 1\n\tsyscall\n");
        } else if (sym && sym->is_local) {
            if (strcmp(sym->type, "int") == 0) {
                fprintf(output_file, "\tlw $a0, %d($fp)\n", sym->stack_offset);
                fprintf(output_file, "\tli $v0, 1\n\tsyscall\n");
            } else if (strcmp(sym->type, "float") == 0) {
                fprintf(output_file, "\tl.s $f12, %d($fp)\n", sym->stack_offset);
                fprintf(output_file, "\tli $v0, 2\n\tsyscall\n");
            }
        } else if (current->result[0] == 't') {
            fprintf(output_file, "\tmove $a0, $%s\n", current->result);
            fprintf(output_file, "\tli $v0, 1\n\tsyscall\n");
        } else {
            fprintf(output_file, "\tlw $t9, var_%s\n", current->result);
            fprintf(output_file, "\tmove $a0, $t9\n");
            fprintf(output_file, "\tli $v0, 1\n\tsyscall\n");
        }
    }
    else if (strcmp(current->op, "+") == 0) {
        // Modify the command below, to properly allocate registers for the operands
        char arg1_reg[10];
        char arg2_reg[10];

        // Use t9 and t8 for temporary operations
        char* temp_reg1 = "$t9"; // Designated temp register for arg1 if not a temp
        char* temp_reg2 = "$t8"; // Designated temp register for arg2 if not a temp

        if (is_register_name(current->arg1)) {
            // arg1 is a temporary, so add $ in front
            snprintf(arg1_reg, sizeof(arg1_reg), "$%s", current->arg1);
        } else if (isdigit(current->arg1[0]) || (current->arg1[0] == '-' && isdigit(current->arg1[1]))) {
            // arg1 is a constant, so load it into the designated temp register (t9)
            fprintf(output_file, "\tli %s, %s\n", temp_reg1, current->arg1);
            strcpy(arg1_reg, temp_reg1);
        } else {
            // arg1 is not a temporary, so load it into the designated temp register (t9)
            symbol* sym = lookup(current_scope_code_gen, current->arg1);
            if (sym && sym->is_local) {
                fprintf(output_file, "\tlw %s, %d($fp)\n", temp_reg1, sym->stack_offset);
            } else {
                fprintf(output_file, "\tlw %s, var_%s\n", temp_reg1, current->arg1);
            }
            strcpy(arg1_reg, temp_reg1);
        }

        if (is_register_name(current->arg2)) {
            // arg1 is a temporary, so add $ in front
            snprintf(arg2_reg, sizeof(arg2_reg), "$%s", current->arg2);
        } else if (isdigit(current->arg2[0]) || (current->arg2[0] == '-' && isdigit(current->arg2[1]))) {
            // arg1 is a constant, so load it into the designated temp register (t9)
            fprintf(output_file, "\tli %s, %s\n", temp_reg2, current->arg2);
            strcpy(arg2_reg, temp_reg2);
        } else {
            // arg1 is not a temporary, so load it into the designated temp register (t9)
            symbol* sym = lookup(current_scope_code_gen, current->arg2);
            if (sym && sym->is_local) {
                fprintf(output_file, "\tlw %s, %d($fp)\n", temp_reg2, sym->stack_offset);
            } else {
                fprintf(output_file, "\tlw %s, var_%s\n", temp_reg2, current->arg2);
            }
        }

        // Perform the addition with the appropriate registers
        fprintf(output_file, "\tadd $%s, %s, %s\n", current->result, arg1_reg, arg2_reg);
    } else if (strcmp(current->op, "func") == 0) {
        in_function = true;
        current_scope_code_gen = current->scope;
        printf("scope variables:");
        print_table(current_scope_code_gen);
        fprintf(output_file, "\n%s:\n", current->result);
        // Function prologue
        fprintf(output_file, "\taddi $sp, $sp, -12\n");
        fprintf(output_file, "\tsw $ra, 8($sp)\n"); // save return address
        fprintf(output_file, "\tsw $fp, 4($sp)\n"); // save frame pointer
        fprintf(output_file, "\tmove $fp, $sp\n"); // set up new frame pointer
        fprintf(output_file, "\n"); // save argument
        // allocate memory for variables in current symbol table
        stack_offset = -12;
        for (int i = 0; i < current_scope_code_gen->size; i++) {
            symbol* sym = current_scope_code_gen->table[i];
            while (sym != 0) {
                fprintf(output_file, "\t# allocate memory for %s\n", sym->name);
                fprintf(output_file, "\taddi $sp, $sp, -4\n"); // Allocate space on stack
                fprintf(output_file, "\tsw $zero, 0($sp)\n"); // Initialize allocated space to 0
                sym->stack_offset = stack_offset; // Keep track of stack position
                stack_offset -= 4; // Update stack offset for next variable
                fprintf(output_file, "\n");
                printf("stack offset: %d of variable %s\n", sym->stack_offset, sym->name);
                // Print other fields of Symbol
                sym = sym->next;
            }
        }

    } else if (strcmp(current->op, "param") == 0) {
        // int tempRegIndex = allocate_register();
        fprintf(output_file, "\tmove $%s, $%s\n", current->arg2, current->result);
    } else if (strcmp(current->op, "return") == 0) {
        // look up the symbol for the return value in the current scope
        printf("processing return\n");
        fprintf(output_file, "\n");   
        fprintf(output_file, "\t# return %s\n", current->arg1);
        symbol* sym = lookup(current_scope_code_gen, current->arg1);
        if (sym && sym->is_param) {
            fprintf(output_file, "\tmove $v0, $%s\n", sym->temp_var);
        } else if (sym && sym->is_local) {
            fprintf(output_file, "\tlw $v0, %d($fp)\n", sym->stack_offset);
        } else if (is_register_name(current->arg1)) {
            fprintf(output_file, "\tmove $v0, $%s\n", current->arg1);
        } else if (isdigit(current->arg1[0]) || (current->arg1[0] == '-' && isdigit(current->arg1[1]))) {
            fprintf(output_file, "\tli $v0, %s\n", current->arg1); // Load constant directly
        } else {
            fprintf(output_file, "\tlw $v0, var_%s\n", current->arg1);
        }
        
        fprintf(output_file, "\n");
        fprintf(output_file, "\t# restore return address\n");
        fprintf(output_file, "\tlw $ra, 8($fp)\n"); // restore return address
        fprintf(output_file, "\t# restore frame pointer\n");
        fprintf(output_file, "\tlw $fp, 4($fp)\n"); // restore frame pointer
        fprintf(output_file, "\t# deallocate stack space\n");
        fprintf(output_file, "\taddi $sp, $sp, %d\n", stack_offset * -1); // deallocate stack space
        fprintf(output_file, "\tjr $ra\n"); // return
        current_scope_code_gen = current_scope_code_gen->parent;
        in_function = false;
    } else if (strcmp(current->op, "param_in") == 0) {
        fprintf(output_file, "\tli $%s, %s\n", current->result, current->arg1);
    } else if (strcmp(current->op, "call") == 0) {
        fprintf(output_file, "\tjal %s\n", current->arg1);
        
        fprintf(output_file, "\n");
        fprintf(output_file, "\tmove $%s, $v0\n", current->result);
    } else if (strcmp(current->op, "array") == 0) {
        // allocate memory for array on stack according to size
        fprintf(output_file, "\t# allocate memory for array %s\n", current->result);
        symbol* sym = lookup(current_scope_code_gen, current->result);
        int array_offset = 4 * atoi(current->arg1);
        sym->stack_offset = array_offset;
        stack_offset -= array_offset;
        fprintf(output_file, "\taddi $sp, $sp, -%d\n", array_offset);
        fprintf(output_file, "\n");
    } else if (strcmp(current->op, "assign_array") == 0) {
        int tempRegIndex = allocate_register();
        if (tempRegIndex == -1) {
        // Handle register allocation failure
        return;
        }
        // Lookup the symbol for the current result in the current scope
        // printf("%s",current->op);
        symbol* sym = lookup(current_scope_code_gen, current->result);

        if (is_register_name(current->arg1)) {
            // If arg1 is already a temp register, directly store it into the variable
            char tempRegName[10];
            snprintf(tempRegName, sizeof(tempRegName), "$%s", current->arg1);
            // store value in array
            fprintf(output_file, "\t# store value in array %s\n", current->result);
            int offset = 4 * atoi(current->arg2) + sym->stack_offset;
            char offset_str[10];
            snprintf(offset_str, sizeof(offset_str), "%d", offset);
            fprintf(output_file, "\tsw %s, -%s($sp)\n", tempRegName, offset_str);
        } else {
            // Load the immediate value into a temp register
            const char* tempRegName = temp_registers[tempRegIndex].name;
            fprintf(output_file, "\tli %s, %s\n", tempRegName, current->arg1);
            // store value in array
            fprintf(output_file, "\t# store value in array %s\n", current->result);
            int offset = 4 * atoi(current->arg2) + sym->stack_offset;
            char offset_str[10];
            snprintf(offset_str, sizeof(offset_str), "%d", offset);
            fprintf(output_file, "\tsw %s, -%s($sp)\n", tempRegName, offset_str);
        }
        deallocate_register(tempRegIndex);        
    } else if (strcmp(current->op, "array_access") == 0) {
        fprintf(output_file, "\t# array access of %s\n", current->arg1);
        symbol* sym = lookup(current_scope_code_gen, current->arg1);
        int offset = 4 * atoi(current->arg2) + sym->stack_offset;
        char offset_str[10];
        snprintf(offset_str, sizeof(offset_str), "%d", offset);
        fprintf(output_file, "\tlw $%s, -%s($sp)\n", current->result, offset_str);
    } else if (strcmp(current->op, "==" ) == 0) {
        // Modify the command below, to properly allocate registers for the operands
        char arg1_reg[10];
        char arg2_reg[10];

        // Use t9 and t8 for temporary operations
        char* temp_reg1 = "$t9"; // Designated temp register for arg1 if not a temp
        char* temp_reg2 = "$t8"; // Designated temp register for arg2 if not a temp

        if (is_register_name(current->arg1)) {
            // arg1 is a temporary, so add $ in front
            snprintf(arg1_reg, sizeof(arg1_reg), "$%s", current->arg1);
        } else if (isdigit(current->arg1[0]) || (current->arg1[0] == '-' && isdigit(current->arg1[1]))) {
            // arg1 is a constant, so load it into the designated temp register (t9)
            fprintf(output_file, "\tli %s, %s\n", temp_reg1, current->arg1);
            strcpy(arg1_reg, temp_reg1);
        } else {
            // arg1 is not a temporary, so load it into the designated temp register (t9)
            symbol* sym = lookup(current_scope_code_gen, current->arg1);
            if (sym && sym->is_local) {
                fprintf(output_file, "\tlw %s, %d($fp)\n", temp_reg1, sym->stack_offset);
            } else {
                fprintf(output_file, "\tlw %s, var_%s\n", temp_reg1, current->arg1);
            }
            strcpy(arg1_reg, temp_reg1);
        }

        if (is_register_name(current->arg2)) {
            // arg1 is a temporary, so add $ in front
            snprintf(arg2_reg, sizeof(arg2_reg), "$%s", current->arg2);
        } else if (isdigit(current->arg2[0]) || (current->arg2[0] == '-' && isdigit(current->arg2[1]))) {
            // arg1 is a constant, so load it into the designated temp register (t9)
            fprintf(output_file, "\tli %s, %s\n", temp_reg2, current->arg2);
            strcpy(arg2_reg, temp_reg2);
        } else {
            // arg1 is not a temporary, so load it into the designated temp register (t9)
            symbol* sym = lookup(current_scope_code_gen, current->arg2);
            if (sym && sym->is_local) {
                fprintf(output_file, "\tlw %s, %d($fp)\n", temp_reg2, sym->stack_offset);
            } else {
                fprintf(output_file, "\tlw %s, var_%s\n", temp_reg2, current->arg2);
            }
        }

        fprintf(output_file, "\tseq $%s, %s, %s\n", current->result, arg1_reg, arg2_reg);
        // fprintf(output_file, "\tseq %s, %s, %s\n", current->arg1, current->arg2, current->result);
    } else if (strcmp(current->op, "if" ) == 0) {
        fprintf(output_file, "\tbeq $%s, $%s, %s\n", current->arg1, current->arg2, current->result);
    } else if (strcmp(current->op, "if_block") == 0) {
        fprintf(output_file, "\tj %s\n", current->result);
    } else if (strcmp(current->op, "if_end") == 0) {
        fprintf(output_file, "# IF STMT END\n");
        fprintf(output_file, "%s:\n", current->result);
    } else if (strcmp(current->op, "if_start") == 0) {
        fprintf(output_file, "# IF STMT START\n");
        fprintf(output_file, "%s:\n", current->result);
    } else if (strcmp(current->op, "if_block_head") == 0) {
        fprintf(output_file, "# IF BLOCK START\n");
        fprintf(output_file, "%s:\n", current->result);
    }
}

void generate_MIPS(TAC* tac_instructions) {
    /*
    NOTE: This is a simple code generation function that generates MIPS assembly code
    from the provided TAC instructions. It assumes that the TAC is already optimized

    The generated code is written to the output file specified during initialization.
    The register allocation strategy used here is a simple linear scan of the temporary
    registers, without considering more advanced techniques such as liveness analysis.

    You can modify this function to implement more advanced register allocation
    and other optimizations as needed for your compiler.

    Not all generated MIPS uses the allocated registers, so you may need to modify
    the code to properly allocate registers for each operation.
    
    */
    TAC* current = tac_instructions;
    // allocate memory for variables
    while (current != NULL) {
        if (strcmp(current->op, "declare") == 0 && current->scope->parent == NULL) {
            fprintf(output_file, "var_%s: .word %s\n", current->result, "0");
        }
        current = current->next;
    }
    fprintf(output_file, ".text\n.globl main\n");

    int regIndex = allocate_register(); // Allocate a register, e.g., $t0
    if (regIndex == -1) {
        // Handle register allocation failure
        return;
    }
    current = tac_instructions;
    int stack_offset = -12;
    while (current != NULL) { // local instructions
        evaluate_operations(current, stack_offset);
        current = current->next;
    }

    // Exit program
    fprintf(output_file, "# Exit program\n");
    fprintf(output_file, "\tli $v0, 10\n\tsyscall\n");
}

void finalize_code_generator(const char* outputFilename) {
    if (output_file) {
        fclose(output_file);
        printf("MIPS code generated and saved to file %s\n", outputFilename);
        output_file = NULL;
    }
}


/*

Implementing register allocation in your MIPS code generation phase is a crucial step 
for optimizing the use of CPU resources. The goal is to map your temporary variables (from TAC) 
to a limited set of MIPS registers, ideally minimizing memory access by keeping 
frequently used values in registers.

MIPS architecture provides a set of general-purpose registers, 
$t0 to $t9 for temporary values, and $s0 to $s7 for saved values. 
For simplicity, let's focus on using the temporary registers.

Strategy for Register Allocation:
--------------------------------

A simple strategy for register allocation could involve:

Register Pool: Keep track of which registers are currently available.
Allocation and Deallocation: Allocate registers when needed for operations and 
                             deallocate them when they are no longer needed.
Spilling: If all registers are in use and another one is needed,
          "spill" a register's value to memory and reuse the register.

*/

// Allocate a register
int allocate_register() {
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        if (!temp_registers[i].inUse) {
            temp_registers[i].inUse = true;
            return i; // Return the register index
        }
    }
    // No available register, implement spilling if necessary
    return -1; // Indicate failure
}

// Deallocate a register
void deallocate_register(int regIndex) {
    if (regIndex >= 0 && regIndex < NUM_TEMP_REGISTERS) {
        temp_registers[regIndex].inUse = false;
    }
}
