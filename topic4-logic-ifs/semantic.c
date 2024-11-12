#include "semantic.h"
#include <stdio.h>
#include "temp.h"

// Perform semantic analysis on the AST
TAC* tac_head = NULL;
TACStack* tac_buffer_head = NULL;

int temp_vars[10] = {0}; // Definition and initialization
int arg_regs[10] = {0}; // Definition and initialization
int arg_reg_index = 0;
int allocated_arg_regs = -1;
symbol_table* scope = NULL;

bool buffering_tac = false;

/*
Recursively traverse the AST and perform semantic analysis
*/

void semantic_analysis(ASTNode* node, symbol_table* sym_table) {
    scope = sym_table;
    printf("%s  :   ", scope->scope_name);
    if (node == NULL) return;

    switch (node->type) {
        case NodeType_Program:
            printf("Performing semantic analysis on program\n");
            semantic_analysis(node->program.varDeclList, sym_table);
            semantic_analysis(node->program.funcDeclList, sym_table);
            semantic_analysis(node->program.stmtList, sym_table);
            break;
        case NodeType_VarDeclList:
            printf("Performing semantic analysis on variable declaration list\n");
            semantic_analysis(node->varDeclList.varDecl, sym_table);
            semantic_analysis(node->varDeclList.varDeclList, sym_table);
            break;
        case NodeType_VarDecl:
            printf("Performing semantic analysis on variable declaration\n");   
            // if (lookup(sym_table, node->varDecl.varName) != NULL) {
            //     fprintf(stderr, "Error: Variable '%s' redeclared.\n", node->varDecl.varName);
            // } else {
            //     add_symbol(sym_table, node->varDecl.varName, node->varDecl.varType); // Assuming 0 as initial value
            // }
            
            break;
        case NodeType_StmtList:
            printf("Performing semantic analysis on statement list\n");
            semantic_analysis(node->stmtList.stmt, sym_table);
            semantic_analysis(node->stmtList.stmtList, sym_table);
            break;
        case NodeType_Stmt:
            printf("Performing semantic analysis on statement\n");
            semantic_analysis(node->stmt.expr, sym_table);
            break;  
        case NodeType_AssignStmt:
            printf("Performing semantic analysis on assignment statement\n");
            semantic_analysis(node->assignStmt.expr, sym_table);
            symbol* sym = lookup(sym_table, node->assignStmt.varName);
            // check if symbol type matches expression type
            char* expr_type = "none";
            if (node->assignStmt.expr->type == NodeType_SimpleExpr) {
                expr_type = node->assignStmt.expr->simpleExpr.type;
                printf("simple type found: %s\n", expr_type);
            } else if (node->assignStmt.expr->type == NodeType_Expr) {
                expr_type = node->assignStmt.expr->expr.expr_type;
                printf("expr type found: %s\n", expr_type);
            } else {
                printf("type not found\n");
            }
            if (sym != NULL) {
                if (strcmp(expr_type, sym->type) != 0) {
                    fprintf(stderr, "Semantic error: Type mismatch in assignment to variable '%s'. Expected: %s, Found: %s\n", node->assignStmt.varName, sym->type, expr_type);
                } else {
                    printf("Type match: %s\n", expr_type);
                }
            }
            break;
        case NodeType_Expr:
            printf("Performing semantic analysis on expression\n");
            // Check if types match
            semantic_analysis(node->expr.left, sym_table);
            semantic_analysis(node->expr.right, sym_table);
            
            char* left_type = "none";
            char* right_type = "none";

            if (node->expr.left->type == NodeType_SimpleExpr) {
                left_type = node->expr.left->simpleExpr.type;
            } else if (node->expr.left->type == NodeType_Expr) {
                left_type = node->expr.left->expr.expr_type;
            }

            if (node->expr.right->type == NodeType_SimpleExpr) {
                right_type = node->expr.right->simpleExpr.type;
            } else if (node->expr.right->type == NodeType_Expr) {
                right_type = node->expr.right->expr.expr_type;
            }

            if (strcmp(left_type, right_type) != 0) {
                fprintf(stderr, "Semantic error: Type mismatch in expression. Left: %s, Right: %s\n", left_type, right_type);
            }

            node->expr.expr_type = left_type;
            break;
        // default:
        //     fprintf(stderr, "Unknown Node Type\n");
        case NodeType_BinOp:
            printf("Performing semantic analysis on binary operation\n");
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
            printf("Performing semantic analysis on simple ID\n");
            // Check for declaration of variable
            if (lookup(sym_table, node->simpleID.name) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->simpleID.name);
            }
            break;
        case NodeType_SimpleExpr:
            printf("Performing semantic analysis on simple expression\n");
            // no checks necessary for number
            break;
        case NodeType_WriteStmt:
            printf("Performing semantic analysis on write statement\n");
            // no checks necessary... for now
            if (lookup(sym_table, node->writeStmt.varName) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->simpleID.name);
            }
            break;
        case NodeType_FuncDeclList:
            printf("Performing semantic analysis on function declaration list\n");
            semantic_analysis(node->funcDeclList.funcDecl, sym_table);
            semantic_analysis(node->funcDeclList.funcDeclList, sym_table);
            break;
        case NodeType_FuncDecl:
            printf("Performing semantic analysis on function declaration\n");
            semantic_analysis(node->funcDecl.funcSignature, node->funcDecl.scope);
            semantic_analysis(node->funcDecl.paramList, node->funcDecl.scope);
            semantic_analysis(node->funcDecl.block, node->funcDecl.scope);
            // buffering_tac = false;
            break;
        case NodeType_FuncSignature:
            printf("Performing semantic analysis on function signature\n");
            // no checks necessary... for now
            break;
        case NodeType_Block:
            printf("Performing semantic analysis on block\n");
            semantic_analysis(node->block.varDeclList, sym_table);
            semantic_analysis(node->block.arrayDeclList, sym_table);
            semantic_analysis(node->block.stmtList, sym_table);
            semantic_analysis(node->block.returnStmt, sym_table);
            break;
        case NodeType_ReturnStmt:
            printf("Performing semantic analysis on return statement====================================\n");
            semantic_analysis(node->returnStmt.expr, sym_table);
            buffering_tac = true;
            allocated_arg_regs = -1;
            break;
        case NodeType_ParamList:
            printf("Performing semantic analysis on parameter list\n");
            semantic_analysis(node->paramList.param, sym_table);
            semantic_analysis(node->paramList.paramList, sym_table);
            break;
        case NodeType_Param:
            printf("Performing semantic analysis on parameter\n");
            break;
        case NodeType_FuncCall:
            printf("Performing semantic analysis on function call\n");
            semantic_analysis(node->funcCall.inputParamList, sym_table);
            // no checks necessary... for now
            break;
        case NodeType_InputParamList:
            printf("Performing semantic analysis on input parameter list\n");
            semantic_analysis(node->inputParamList.inputParam, sym_table);
            semantic_analysis(node->inputParamList.inputParamList, sym_table);
            break;
        case NodeType_InputParam:
            printf("Performing semantic analysis on input parameter\n");
            // no checks necessary... for now
            break;
        case NodeType_ArrayDeclList:
            printf("Performing semantic analysis on array declaration list\n");
            semantic_analysis(node->arrayDeclList.arrayDecl, sym_table);
            semantic_analysis(node->arrayDeclList.arrayDeclList, sym_table);
            break;
        case NodeType_ArrayDecl:
            printf("Performing semantic analysis on array declaration\n");
            // no checks necessary... for now
            break;
        case NodeType_ArrayAssignStmt:
            printf("Performing semantic analysis on array assignment statement\n");
            semantic_analysis(node->arrayAssignStmt.expr, sym_table);
            break;
        case NodeType_ArrayAccess:
            printf("Performing semantic analysis on array access\n");
            // no checks necessary... for now
            break;
        case NodeType_TypeCast:
            printf("Performing semantic analysis on type cast\n");
            // no checks necessary... for now
            break;
        // ... handle other node types ...
        default:
            fprintf(stderr, "Unknown Node Type\n");
    }

    // ... other code ...

    TAC* tac = tac_expr(node, sym_table);
    print_TAC(tac);

    if (node->type == NodeType_SimpleID)
    {
        symbol *sym = lookup(sym_table, node->simpleID.name);
        if (sym)
        {
            node->simpleID.temp = sym->temp_var;
        }
    }

    // if (node->type == NodeType_Block) {
    //     printf("Block scope: %s\n", node->block.scope->scope_name);
    //     scope = node->block.scope;
    // }

    // ... other code ...
}

// You can add more functions related to semantic analysis here
// Implement functions to generate TAC expressions

bool is_temp_var(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return false;
    }
    if (str[0] == 't')
    {
        return true;
    }
    return false;
}

TAC *tac_expr(ASTNode *expr, symbol_table *sym_table)
{

    // Depending on your AST structure, generate the appropriate TAC
    // If the TAC is generated successfully, append it to the global TAC list
    // Return the generated TAC, so that it can be used by the caller, e.g. for printing
    if (!expr)
        return NULL;

    TAC *instruction = (TAC *)malloc(sizeof(TAC));
    if (!instruction)
        return NULL;

    instruction->scope = sym_table;
    printf("Generating TAC in the scope %s\n", sym_table->scope_name);
    switch (expr->type)
    {
        case NodeType_Expr:
        {
            printf("Generating TAC for expression\n");
            instruction->arg1 = create_operand(expr->expr.left);
            instruction->arg2 = create_operand(expr->expr.right);
            char op_str[2] = {expr->expr.operator, '\0' };
            instruction->op = strdup(op_str);
            instruction->result = create_temp_var();
            expr->expr.temp = instruction->result;
            break;
        }

        case NodeType_VarDecl:
        {
            printf("Generating TAC for variable declaration\n");
            instruction->op = strdup("declare");
            instruction->result = strdup(expr->varDecl.varName);
            break;
        }

        case NodeType_AssignStmt:
        {
            printf("Generating TAC for assignment statement\n");
            instruction->arg1 = create_operand(expr->assignStmt.expr);
            instruction->op = strdup("assign");
            instruction->result = expr->assignStmt.varName;
            symbol *sym = lookup(scope, instruction->result);
            if (sym->temp_var != NULL && is_temp_var(instruction->arg1))
            {
                sym->temp_var = instruction->arg1;
            }
            break;
        }

        case NodeType_WriteStmt:
        {
            printf("Generating TAC for write statement\n");
            instruction->arg1 = "";
            instruction->arg2 = "";
            instruction->op = strdup("write");
            instruction->result = strdup(expr->writeStmt.varName);
            break;
        }

        case NodeType_FuncSignature: {
            printf("Generating TAC for function declaration\n");
            instruction->op = strdup("func");
            instruction->result = strdup(expr->funcDecl.funcName);
            instruction->scope = expr->funcSignature.scope;
            buffering_tac = false;
            allocated_arg_regs = -1;
            break;
        }

        case NodeType_ReturnStmt: {
            printf("Generating TAC for return statement\n");
            instruction->arg1 = create_operand(expr->returnStmt.expr);
            instruction->op = strdup("return");
            instruction->result = "";
            break;
        }

        case NodeType_Param: {
            printf("Generating TAC for parameter\n");
            instruction->op = strdup("param");
            instruction->result = create_arg_register();
            instruction->arg1 = strdup(expr->param.varName);
            instruction->arg2 = create_temp_var();
            symbol* sym = lookup(scope, instruction->arg1);
            sym->temp_var = instruction->arg2;
            sym->is_param = true;
            printf("Setting param %s to %s\n", instruction->arg1, instruction->arg2);
            break;
        }

        case NodeType_InputParam: {
            printf("Generating TAC for input parameter\n");
            instruction->op = strdup("param_in");
            instruction->result = create_arg_register();
            instruction->arg1 = strdup(expr->inputParam.value);
            break;
        }

        case NodeType_FuncCall: {
            printf("Generating TAC for function call\n");
            instruction->op = strdup("call");
            instruction->arg1 = strdup(expr->funcCall.funcName);
            instruction->result = create_temp_var();
            expr->funcCall.temp = instruction->result;
            break;
        }

        case NodeType_ArrayDecl: {
            printf("Generating TAC for array declaration\n");
            instruction->op = strdup("array");
            instruction->result = strdup(expr->arrayDecl.varName);
            instruction->arg1 = strdup(expr->arrayDecl.size);
            break;
        }

        case NodeType_ArrayAssignStmt: {
            printf("Generating TAC for array assignment\n");
            instruction->arg1 = create_operand(expr->arrayAssignStmt.expr);
            instruction->arg2 = expr->arrayAssignStmt.index;
            instruction->op = strdup("assign_array");
            instruction->result = expr->arrayAssignStmt.varName;
            break;
        }

        case NodeType_ArrayAccess: {
            printf("Generating TAC for array access\n");
            instruction->arg1 = strdup(expr->arrayAccess.varName);
            instruction->arg2 = strdup(expr->arrayAccess.index);
            instruction->op = strdup("array_access");
            instruction->result = create_temp_var();
            expr->arrayAccess.temp = instruction->result;
            symbol* sym = lookup(scope, instruction->arg1);
            sym->temp_var = instruction->result;
            // printf("Setting param %s to %s\n", instruction->arg1, instruction->arg2);
            break;
        }

        default:
            free(instruction);
            return NULL;
    }
    
    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    append_TAC(&tac_head, instruction);

    // if (buffering_tac) {
    //     push_TAC(&tac_buffer_head, instruction);
    // }

    return instruction;
}
// Function to create a new temporary variable for TAC
char *create_temp_var()
{
    static int count = 0;
    char *tempVar = malloc(10); // Enough space for "t" + number
    if (!tempVar)
        return NULL;
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
        case NodeType_Param: {
            symbol* sym = lookup(scope, node->param.varName);
            if (sym != NULL && sym->temp_var != NULL) {
                return sym->temp_var;
            }
            return node->simpleID.name;
        }
        case NodeType_ArrayAccess: {
            symbol* sym = lookup(scope, node->arrayAccess.varName);
            if (sym != NULL && sym->temp_var != NULL) {
                return sym->temp_var;
            }
            return node->arrayAccess.varName;
        }
        case NodeType_SimpleExpr:
            // return  node->simpleExpr.number in string format
            snprintf(buffer, 20, "%s", node->simpleExpr.number);
            return strdup(buffer);
            // return node->simpleExpr.temp;
        case NodeType_Expr:
            return node->expr.temp;
        case NodeType_FuncCall:
            return node->funcCall.temp;
        case NodeType_AssignStmt:
            return "t9";
        default:
            // return node->expr.temp;
            return NULL;
    }
}

// Print the TAC list to a file
// This function is provided for reference, you can modify it as needed

void print_TAC_to_file(const char *filename, TAC *tac)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Failed to open file");
        return;
    }
    TAC *current = tac;
    while (current != NULL)
    {
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
            fprintf(file, "%s load %s\n", current->result, current->arg1);
        }
        else if (strcmp(current->op, "+") == 0 ||
                 strcmp(current->op, "-") == 0 ||
                 strcmp(current->op, "*") == 0 ||
                 strcmp(current->op, "/") == 0)
        {
            fprintf(file, "%s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
        }
        else if (strcmp(current->op, "write") == 0)
        {
            fprintf(file, "write %s\n", current->result);
        } else if (strcmp(current->op, "func") == 0) {
            fprintf(file, "\n");
            fprintf(file, "func %s\n", current->result);
        } else if (strcmp(current->op, "return") == 0) {
            fprintf(file, "return %s\n", current->arg1);
            fprintf(file, "\n");
        } else if (strcmp(current->op, "param") == 0) {
            fprintf(file, "%s param %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "param_in") == 0) {
            fprintf(file, "%s param_in %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "call") == 0) {
            fprintf(file, "%s call %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "array") == 0) {
            fprintf(file, "%s array, size %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "assign_array") == 0) {
            fprintf(file, "%s[%s] = %s\n", current->result, current->arg2, current->arg1);
        } else if (strcmp(current->op, "array_access") == 0) {
            fprintf(file, "%s = %s[%s]\n", current->result, current->arg1, current->arg2);
        }
        current = current->next;
    }
    fclose(file);
    printf("TAC written to %s\n", filename);
}

// Temporary variable allocation and deallocation functions //

void initialize_temp_vars()
{
    for (int i = 0; i < 20; i++)
    {
        temp_vars[i] = 0;
    }
    temp_vars[9] = 1; // Reserve the last temp var for temporary calculations
    temp_vars[8] = 1; // I need another one too for the same reason
}

int allocate_temp_var(int temp_vars[])
{
    // implement the temp var allocation logic
    // use the tempVars array to keep track of allocated temp vars

    // search for the next available temp var
    for (int i = 0; i < 20; i++)
    {
        if (temp_vars[i] == 0)
        {
            temp_vars[i] = 1;
            return i;
        }
    }
    return -1; // No available temp var
}

void deallocate_temp_var(int temp_vars[], int index)
{
    // implement the temp var deallocation logic
    // use the tempVars array to keep track of allocated temp vars
    if (index >= 0 && index < 20)
    {
        temp_vars[index] = 0;
    }
}

void append_TAC(TAC **head, TAC *new_instruction)
{
    if (!*head)
    {
        *head = new_instruction;
    }
    else
    {
        TAC *current = *head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = new_instruction;
    }
}

void print_TAC(TAC* tac) {
    if (!tac) return;
    if (strcmp(tac->op, "declare") == 0) {
            printf("%s declare\n", tac->result);
        } else if (strcmp(tac->op, "assign") == 0) {
            printf("%s = %s\n", tac->result, tac->arg1);
        } else if (strcmp(tac->op, "load") == 0) {
            printf("%s load %s\n", tac->result, tac->arg1);
        } else if (strcmp(tac->op, "+") == 0) {
            printf("%s = %s + %s\n", tac->result, tac->arg1, tac->arg2);
        } else if (strcmp(tac->op, "write") == 0) {
            printf("write %s\n", tac->result);
        } else if (strcmp(tac->op, "func") == 0) {
            printf("\n");
            printf("func %s\n", tac->result);
        } else if (strcmp(tac->op, "return") == 0) {
            printf("return %s\n", tac->arg1);
            printf("\n");
        } else if (strcmp(tac->op, "param") == 0) {
            printf("%s param %s\n", tac->result, tac->arg2);
        } else if (strcmp(tac->op, "param_in") == 0) {
            printf("%s param_in %s\n", tac->result, tac->arg1);
        } else if (strcmp(tac->op, "call") == 0) {
            printf("%s = call %s\n", tac->result, tac->arg1);
        } else if (strcmp(tac->op, "li") == 0) {
            printf("%s li %s\n", tac->result, tac->arg1);
        } else if (strcmp(tac->op, "array") == 0) {
            printf("%s array, size %s\n", tac->result, tac->arg1);
        } else if (strcmp(tac->op, "assign_array") == 0) {
            printf("%s[%s] = %s\n", tac->result, tac->arg2, tac->arg1);
        } else if (strcmp(tac->op, "array_access") == 0) {
            printf("%s = %s[%s]\n", tac->result, tac->arg1, tac->arg2);
        }
}

void print_all_TAC(TAC* tac) {
    TAC* current = tac;
    while (current != NULL) {
        print_TAC(current);
        current = current->next;
    }
}

// Function declarations for TAC stack operations
void push_TAC(TACStack** stack, TAC* tac) {
    TACStack* new_node = (TACStack*)malloc(sizeof(TACStack));
    if (!new_node) return;
    new_node->tac = tac;
    new_node->next = *stack;
    *stack = new_node;
    printf("Pushed TAC onto stack\n");
}

// TAC* pop_TAC(TACStack** stack) {
//     if (is_TAC_stack_empty(*stack)) return NULL;
//     TACStack* top = *stack;
//     TAC* tac = top->tac;
//     *stack = top->next;
//     free(top);
//     return tac;
// }

// bool is_TAC_stack_empty(TACStack* stack) {
//     return stack == NULL;
// }

// Function to allocate argument registers for parameters
int allocate_arg_register(int arg_regs[], int num_args) {
    for (int i = 0; i < num_args; i++) {
        if (arg_regs[i] == 0) { // Check if the register is free
            arg_regs[i] = 1; // Mark the register as used
            return i; // Return the register index
        }
    }
    return -1; // No free register found
}

// Function to check if a given string is an argument register
bool is_arg_register(const char* str) {
    return str != NULL && str[0] == 'a' && str[1] >= '0' && str[1] <= '9' && str[2] == '\0';
}

// Function to deallocate argument registers
void deallocate_arg_register(int arg_regs[], int index) {
    allocated_arg_regs -= 1;
}

// Function to create a new argument register name using allocate_arg_register
char* create_arg_register() {
    allocated_arg_regs += 1;
    char* arg_reg = (char*)malloc(10); // Enough space for "a" + number
    if (!arg_reg) return NULL;
    snprintf(arg_reg, 10, "a%d", allocated_arg_regs);
    return arg_reg;
}

char* get_arg_register(int index) {
    char* arg_reg = (char*)malloc(10); // Enough space for "a" + number
    if (!arg_reg) return NULL;
    snprintf(arg_reg, 10, "a%d", index);
    return arg_reg;
}