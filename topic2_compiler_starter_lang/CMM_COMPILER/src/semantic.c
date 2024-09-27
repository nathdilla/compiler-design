#include "semantic.h"
#include <stdio.h>

// Perform semantic analysis on the AST
TAC* tacHead = NULL;

/*
Recursively traverse the AST and perform semantic analysis
*/
void semantic_analysis(ASTNode* node, symbol_table* sym_table) {
    if (node == NULL) return;

    switch (node->type) {
        case NodeType_Program:
            printf("Performing semantic analysis on program\n");
            semantic_analysis(node->program.varDeclList, sym_table);
            semantic_analysis(node->program.stmtList, sym_table);
            break;
        case NodeType_VarDeclList:
            semantic_analysis(node->varDeclList.varDecl, sym_table);
            semantic_analysis(node->varDeclList.varDeclList, sym_table);
            break;
        case NodeType_VarDecl:
            
            // Check for redeclaration of variables
            break;
        case NodeType_StmtList:
            semantic_analysis(node->stmtList.stmt, sym_table);
            semantic_analysis(node->stmtList.stmtList, sym_table);
            break;
        // case NodeType_AssignStmt:
        //     semantic_analysis(node->assignStmt.expr, sym_table);
        //     break;  
        case NodeType_Expr:
            semantic_analysis(node->expr.left, sym_table);
            semantic_analysis(node->expr.right, sym_table);
            break;
        default:
            fprintf(stderr, "Unknown Node Type\n");
        // case NodeType_BinOp:
        //     // Check for declaration of variables
        //     if (lookupSymbol(symTab, node->binOp.left->varDecl.varName) == NULL) {
        //         fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->varDecl.varName);
        //     }
        //     if (lookupSymbol(symTab, node->binOp.right->varDecl.varName) == NULL) {
        //         fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->varDecl.varName);
        //     }
        //     semanticAnalysis(node->binOp.left, symTab);
        //     break;
        // case NodeType_SimpleID:
        //     // Check for declaration of variable
        //     if (lookupSymbol(symTab, node->simpleID.name) == NULL) {
        //         fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->simpleID.name);
            // }
        // case NodeType_SimpleExpr:
        //     // no checks necessary for number
        // // ... handle other node types ...
        // default:
        //     fprintf(stderr, "Unknown Node Type\n");
    }

       // ... other code ...

    if (node->type == NodeType_Expr || node->type == NodeType_SimpleExpr) {
        TAC* tac = tac_expr(node);
        // Process or store the generated TAC
        print_TAC(tac);
    }

    // ... other code ...

}

// You can add more functions related to semantic analysis here
// Implement functions to generate TAC expressions



TAC* tac_expr(ASTNode* expr) {

    // Depending on your AST structure, generate the appropriate TAC
    // If the TAC is generated successfully, append it to the global TAC list
    // Return the generated TAC, so that it can be used by the caller, e.g. for printing
    if (!expr) return NULL;

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    switch (expr->type) {
        case NodeType_Expr: {
            printf("Generating TAC for expression\n");
            instruction->arg1 = create_operand(expr->expr.left);
            instruction->arg2 = create_operand(expr->expr.right);
            instruction->op = strdup("+"); //strdup(expr->expr.operator);
            instruction->result = create_temp_var();
            break;
        }

        case NodeType_SimpleExpr: {
            printf("Generating TAC for simple expression\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->simpleExpr.number);
            instruction->arg1 = strdup(buffer);
            instruction->op = strdup("assign");
            instruction->result = create_temp_var();
            break;
        }

        // case NodeType_SimpleID: {
        //     printf("Generating TAC for simple ID\n");
        //     instruction->arg1 = strdup(expr->simpleID.name);
        //     instruction->op = strdup("assign");
        //     instruction->result = create_temp_var();
        //     break;
        // }

        // Add cases for other expression types...

        default:
            free(instruction);
            return NULL;
    }

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    append_TAC(&tacHead, instruction);

    return instruction;
}
// Function to create a new temporary variable for TAC
char* create_temp_var() {
    static int count = 0;
    char* tempVar = malloc(10); // Enough space for "t" + number
    if (!tempVar) return NULL;
    count = allocate_temp_var(temp_vars);
    sprintf(tempVar, "t%d", count++);
    return tempVar;
}

char* create_operand(ASTNode* node) {
    // Depending on your AST structure, return the appropriate string
    // representation of the operand. For example, if the operand is a simple
    // expression or an identifier, return its string representation.
    // This function needs to be implemented based on your AST structure.
    return NULL;
}

void print_TAC(TAC* tac) {
    if (!tac) return;
    printf("%s = %s %s %s\n", tac->result, tac->arg1, tac->op, tac->arg2);
}

// Print the TAC list to a file
// This function is provided for reference, you can modify it as needed

void print_TAC_to_file(const char* filename, TAC* tac) {
    FILE* file = fopen(filename , "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }   
    TAC* current = tac;
    while (current != NULL) {
        fprintf(file, "%s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
        current = current->next;
    }   
    fclose(file);
    printf("TAC written to %s\n", filename);
}


// Temporary variable allocation and deallocation functions //

void initialize_temp_vars() {
    for (int i = 0; i < 20; i++) {
        temp_vars[i] = 0;
    }
}

int allocate_temp_var(int temp_vars[]) {
   // implement the temp var allocation logic
   // use the tempVars array to keep track of allocated temp vars

    // search for the next available temp var
    for (int i = 0; i < 20; i++) {
        if (temp_vars[i] == 0) {
            temp_vars[i] = 1;
            return i;
        }
    }
    return -1; // No available temp var
}

void deallocate_temp_var(int temp_vars[], int index) {
    // implement the temp var deallocation logic
    // use the tempVars array to keep track of allocated temp vars
    if (index >= 0 && index < 20) {
        temp_vars[index] = 0;
    }
}   

void append_TAC(TAC** head, TAC* new_instruction) {
    if (!*head) {
        *head = new_instruction;
    } else {
        TAC* current = *head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_instruction;
    }
}
