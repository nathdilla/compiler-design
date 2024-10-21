#include "semantic.h"
#include <stdio.h>
#include "temp.h"

// Perform semantic analysis on the AST
TAC* tac_head = NULL;

int temp_vars[10] = {0}; // Definition and initialization
symbol_table* scope = NULL;

/*
Recursively traverse the AST and perform semantic analysis
*/
void semantic_analysis(ASTNode* node, symbol_table* sym_table) {
    scope = sym_table;
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
            // if (lookup(sym_table, node->varDecl.varName) != NULL) {
            //     fprintf(stderr, "Error: Variable '%s' redeclared.\n", node->varDecl.varName);
            // } else {
            //     add_symbol(sym_table, node->varDecl.varName, node->varDecl.varType); // Assuming 0 as initial value
            // }
            
            break;
        case NodeType_StmtList:
            semantic_analysis(node->stmtList.stmt, sym_table);
            semantic_analysis(node->stmtList.stmtList, sym_table);
            break;
        case NodeType_Stmt:
            semantic_analysis(node->stmt.expr, sym_table);
            break;  
        case NodeType_AssignStmt:
            semantic_analysis(node->assignStmt.expr, sym_table);
            break;
        case NodeType_Expr:
            semantic_analysis(node->expr.left, sym_table);
            semantic_analysis(node->expr.right, sym_table);
            break;
        // default:
        //     fprintf(stderr, "Unknown Node Type\n");
        case NodeType_BinOp:
            // Check for declaration of variables
            if (lookup(sym_table, node->binOp.left->varDecl.varName) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->varDecl.varName);
            }
            if (lookup(sym_table, node->binOp.right->varDecl.varName) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->varDecl.varName);
            }
            semantic_analysis(node->binOp.left, sym_table);
            break;
        case NodeType_SimpleID:
            // Check for declaration of variable
            if (lookup(sym_table, node->simpleID.name) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->simpleID.name);
            }
            break;
        case NodeType_SimpleExpr:
            // no checks necessary for number
            break;
        case NodeType_WriteStmt:
            // no checks necessary... for now
            if (lookup(sym_table, node->writeStmt.varName) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->simpleID.name);
            }
            break;
        // ... handle other node types ...
        default:
            fprintf(stderr, "Unknown Node Type\n");
    }

       // ... other code ...

    if (node->type == NodeType_VarDecl || node->type == NodeType_SimpleExpr || 
        node->type == NodeType_SimpleID || node->type == NodeType_AssignStmt || 
        node->type == NodeType_Expr || node->type == NodeType_WriteStmt ||
        node->type == NodeType_BinOp) {
        TAC* tac = tac_expr(node, sym_table);
        print_TAC(tac);
    }

    if (node->type == NodeType_SimpleID) {
        symbol* sym = lookup(sym_table, node->simpleID.name);
        if (sym) {
            node->simpleID.temp = sym->temp_var;
        }
    }

    // ... other code ...

}

// You can add more functions related to semantic analysis here
// Implement functions to generate TAC expressions

bool is_temp_var(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    if (str[0] == 't') {
        return true;
    }
    return false;
}

TAC* tac_expr(ASTNode* expr, symbol_table* sym_table) {

    // Depending on your AST structure, generate the appropriate TAC
    // If the TAC is generated successfully, append it to the global TAC list
    // Return the generated TAC, so that it can be used by the caller, e.g. for printing
    if (!expr) return NULL;

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    instruction->scope = sym_table;
    printf("Generating TAC in the scope %s\n", sym_table->scope_name);
    switch (expr->type) {
        case NodeType_Expr: {
            printf("Generating TAC for expression\n");
            instruction->arg1 = create_operand(expr->expr.left);
            instruction->arg2 = create_operand(expr->expr.right);
            instruction->op = strdup("+"); //strdup(expr->expr.operator);
            instruction->result = create_temp_var(); // temp calculations
            expr->expr.temp = instruction->result;
            break;
        }

        // case NodeType_BinOp: {
        //     printf("Generating TAC for binary operation\n");
        //     instruction->arg1 = create_operand(expr->binOp.left);
        //     instruction->arg2 = create_operand(expr->binOp.right);
        //     instruction->op = strdup("+"); //strdup(expr->binOp.operator);
        //     instruction->result = create_temp_var();
        //     // expr->binOp.temp = instruction->result;
        //     break;
        // }

        case NodeType_SimpleID: {
            symbol* sym = lookup(scope, expr->simpleID.name);
            if (sym != NULL && sym->temp_var == NULL) {
                printf("Generating TAC for simple ID\n");
                instruction->arg1 = create_operand(expr);
                instruction->op = strdup("load");
                instruction->result = create_temp_var();
                expr->simpleID.temp = instruction->result;
                
                sym->temp_var = instruction->result;
            } else {
                instruction->arg1 = sym->name;
                instruction->op = strdup("load");
                instruction->result = sym->temp_var;
            }
            break;
        }

        case NodeType_VarDecl: {
            printf("Generating TAC for variable declaration\n");
            instruction->op = strdup("declare");
            instruction->result = strdup(expr->varDecl.varName);
            break;
        }

        case NodeType_AssignStmt: {
            printf("Generating TAC for assignment statement\n");
            instruction->arg1 = create_operand(expr->assignStmt.expr);
            instruction->op = strdup("assign");
            instruction->result = expr->assignStmt.varName;
            symbol* sym = lookup(scope, instruction->result);
            if (sym->temp_var != NULL && is_temp_var(instruction->arg1)) {
                sym->temp_var = instruction->arg1;
            }
            break;
        }

        case NodeType_WriteStmt: {
            printf("Generating TAC for write statement\n");
            instruction->arg1 = "";
            instruction->arg2 = "";
            instruction->op = strdup("write");
            instruction->result = strdup(expr->writeStmt.varName);
            break;
        }
        // Add cases for other expression types...

        default:
            free(instruction);
            return NULL;
    }

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    append_TAC(&tac_head, instruction);

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
    char buffer[20]; // Declare buffer here
    switch (node->type) {   
        case NodeType_SimpleID: {
            symbol* sym = lookup(scope, node->simpleID.name);
            if (sym != NULL && sym->temp_var != NULL) {
                return sym->temp_var;
            }
            return node->simpleID.name;
        }
        case NodeType_SimpleExpr:
            // return  node->simpleExpr.number in string format
            snprintf(buffer, 20, "%s", node->simpleExpr.number);
            return strdup(buffer);
            // return node->simpleExpr.temp;
        case NodeType_Expr:
            return node->expr.temp;
        case NodeType_AssignStmt:
            return "t9";
        default:
            // return node->expr.temp;
            return NULL;
    }
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
        // fprintf(file, "%s : ", current->op);
        if (strcmp(current->op, "declare") == 0) {
            fprintf(file, "%s declare\n", current->result);
        } else if (strcmp(current->op, "assign") == 0) {
            fprintf(file, "%s = %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "load") == 0) {
            fprintf(file, "%s = %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "+") == 0) {
            fprintf(file, "%s = %s + %s\n", current->result, current->arg1, current->arg2);
        } else if (strcmp(current->op, "write") == 0) {
            fprintf(file, "write %s\n", current->result);
        }
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
    temp_vars[9] = 1; // Reserve the last temp var for temporary calculations
    temp_vars[8] = 1; // I need another one too for the same reason
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

void print_TAC(TAC* tac) {
    if (!tac) return;
    if (strcmp(tac->op, "declare") == 0) {
        printf("%s = 0\n", tac->result);
    } else {
        printf("%s = %s %s %s\n", tac->result, tac->arg1, tac->op, tac->arg2);
    }
}
