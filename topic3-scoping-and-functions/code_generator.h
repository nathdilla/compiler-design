// codeGenerator.h

#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "AST.h" // Include your AST definition
#include "semantic.h" // Include your TAC definition
#include <stdbool.h>

#define NUM_TEMP_REGISTERS 10

// typedef struct {
//     TAC* head;
//     function_heads* next;
// } function_heads;

// Initializes code generation, setting up any necessary structures
void init_code_generator(const char* outputFilename);

// Generates MIPS assembly code from the provided TAC
void generate_MIPS(TAC* tac_instructions);

// Finalizes code generation, closing files and cleaning up
void finalize_code_generator(const char* output_filename);

// Allocate a register
int allocate_register();

// Deallocate a register
void deallocate_register(int regIndex);

#endif // CODE_GENERATOR_H
