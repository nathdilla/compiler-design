// codeGenerator.c

#include "code_generator.h"
#include <stdio.h>
#include <stdlib.h>

static FILE* output_file;

typedef struct {
    char* name; // Name of the register, e.g., "$t0"
    bool inUse; // Whether the register is currently in use
} MIPSRegister;

// Array of temporary registers, used for register allocation
// and tracking which registers are currently in use

MIPSRegister temp_registers[NUM_TEMP_REGISTERS] = {
    {"$t0", false}, {"$t1", false}, {"$t2", false}, {"$t3", false},
    {"$t4", false}, {"$t5", false}, {"$t6", false}, {"$t7", false},
    {"$t8", false}, {"$t9", false},
};

void init_code_generator(const char* output_filename) {
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }
    // Write the data section header
    fprintf(output_file, ".data\n");
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
        if (strcmp(current->op, "declare") == 0) {
            fprintf(output_file, "var_%s: .word %s\n", current->result, "0");
        }
        current = current->next;
    }
    fprintf(output_file, ".text\n.globl main\nmain:\n");

    int regIndex = allocate_register(); // Allocate a register, e.g., $t0
    if (regIndex == -1) {
        // Handle register allocation failure
        return;
    }
    current = tac_instructions;
    while (current != NULL) {
        // if (strcmp(current->op, "const") == 0) {
        //     fprintf(output_file, "\tli $%s, %s\n", current->result, current->arg1);
        // }
        if (strcmp(current->op, "assign") == 0) {
            int tempRegIndex = allocate_register();
            if (tempRegIndex == -1) {
            // Handle register allocation failure
            return;
            }
            if (current->arg1[0] == 't') {
                // If arg1 is already a temp register, directly store it into the variable
                fprintf(output_file, "\tsw $%s, var_%s\n", current->arg1, current->result);
            } else {
                // Otherwise, load the immediate value into a temp register and store it
                fprintf(output_file, "\tli %s, %s\n", temp_registers[tempRegIndex].name, current->arg1);
                fprintf(output_file, "\tsw %s, var_%s\n", temp_registers[tempRegIndex].name, current->result);
            }
            deallocate_register(tempRegIndex);
        } else if (strcmp(current->op, "li") == 0) {
            fprintf(output_file, "\tli $%s, %s\n", current->result, current->arg1);
        }
        else if (strcmp(current->op, "write") == 0) {
            fprintf(output_file, "\tlw $t9, var_%s\n", current->result);
            fprintf(output_file, "\tmove $a0, $t9\n");
            fprintf(output_file, "\tli $v0, 1\n\tsyscall\n");
        }
        else if (strcmp(current->op, "+") == 0) {
            // Modify the command below, to properly allocate registers for the operands
            char arg1_reg[10];
            char arg2_reg[10];

            // Use t9 and t8 for temporary operations
            char* temp_reg1 = "$t9"; // Designated temp register for arg1 if not a temp
            char* temp_reg2 = "$t8"; // Designated temp register for arg2 if not a temp

            if (current->arg1[0] == 't' || current->arg1[0] == 'a') {
            // arg1 is a temporary, so add $ in front
            snprintf(arg1_reg, sizeof(arg1_reg), "$%s", current->arg1);
            } else {
            // arg1 is not a temporary, so load it into the designated temp register (t9)
            fprintf(output_file, "\tli %s, %s\n", temp_reg1, current->arg1);
            strcpy(arg1_reg, temp_reg1);
            }

            if (current->arg2[0] == 't' || current->arg2[0] == 'a') {
            // arg2 is a temporary, so add $ in front
            snprintf(arg2_reg, sizeof(arg2_reg), "$%s", current->arg2);
            } else {
            // arg2 is not a temporary, so load it into the designated temp register (t8)
            fprintf(output_file, "\tli %s, %s\n", temp_reg2, current->arg2);
            strcpy(arg2_reg, temp_reg2);
            }

            // Perform the addition with the appropriate registers
            fprintf(output_file, "\tadd %s, %s, %s\n", temp_registers[regIndex].name, arg1_reg, arg2_reg);
        } else if (strcmp(current->op, "func") == 0) {
            fprintf(output_file, "\n%s:\n", current->result);
            // Function prologue
            fprintf(output_file, "\taddi $sp, $sp, -12\n");
            fprintf(output_file, "\tsw $ra, 8($sp)\n"); // save return address
            fprintf(output_file, "\tsw $fp, 4($sp)\n"); // save frame pointer
            fprintf(output_file, "\tmove $fp, $sp\n"); // set up new frame pointer
        } else if (strcmp(current->op, "param") == 0) {
            // int tempRegIndex = allocate_register();
            fprintf(output_file, "\tmove $%s, $%s\n", current->arg2, current->result);
        }
        // Add more operations here (subtraction, multiplication, etc.)

        current = current->next;
    }

    // Exit program
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
