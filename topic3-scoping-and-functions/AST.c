#include "AST.h"
int indentValue = 2;

void printIndent(int level) {
    for (int i = 0; i < level; i++) {
        printf("--");
    }
}

void traverseAST(ASTNode* node, int level) {
    if (!node) {
        printf ("Nothing to traverse\n");
        return;
    }

    printIndent(level);
    //printf("Traversing node of type %d\n", node->type);
    switch (node->type) {
        case NodeType_Program:
            printIndent(level);
            printf("Program\n");
            traverseAST(node->program.varDeclList, level + indentValue);
            traverseAST(node->program.stmtList, level + indentValue);
            printf("|");
            break;
        case NodeType_VarDeclList:
            printIndent(level);
            printf("Variable Declaration List\n");
            traverseAST(node->varDeclList.varDecl, level + indentValue);
            traverseAST(node->varDeclList.varDeclList, level + indentValue);
            break;
        case NodeType_VarDecl:
            printIndent(level);
            printf("Variable Declaration: %s %s\n", node->varDecl.varType, node->varDecl.varName);
            break;
        case NodeType_SimpleExpr:
            printIndent(level);
            printf("Simple Expression: %d\n", node->simpleExpr.number);
            break;
        case NodeType_SimpleID:
            printIndent(level);
            printf("Simple Identifier: %s\n", node->simpleID.name);
            break;
        case NodeType_WriteStmt:
            printIndent(level);
            printf("Write: %s\n", node->writeStmt.varName);
            break;
        case NodeType_Expr:
            printIndent(level);
            printf("Expression: %c\n", node->expr.operator);
            traverseAST(node->expr.left, level + indentValue);
            traverseAST(node->expr.right, level + indentValue);
            break;
        case NodeType_StmtList:
            printIndent(level);
            printf("Statement List\n");
            traverseAST(node->stmtList.stmt, level + indentValue);
            traverseAST(node->stmtList.stmtList, level + indentValue);
            break;
        case NodeType_Stmt:
            printIndent(level);
            printf("Statement: %s %s\n", node->stmt.varName, node->stmt.operator);
            traverseAST(node->stmt.expr, level + indentValue);
            break;
        case NodeType_AssignStmt:
            printIndent(level);
            printf("Assignment: %s = %s\n", node->assignStmt.varName, "node->assignStmt.expr");
            traverseAST(node->assignStmt.expr, level + indentValue);
            break;
        case NodeType_BinOp:
            printIndent(level);
            printf("BinOp: %c\n", node->binOp.operator);
            traverseAST(node->binOp.left, level + indentValue);
            traverseAST(node->binOp.right, level + indentValue);
            break;
        case NodeType_FuncDeclList:
            printIndent(level);
            printf("Function Declaration List\n");
            traverseAST(node->funcDeclList.funcDecl, level + indentValue);
            traverseAST(node->funcDeclList.funcDeclList, level + indentValue);
            break;
        case NodeType_FuncDecl:
            printIndent(level);
            printf("Function Declaration: %s\n", node->funcDecl.funcName);
            traverseAST(node->funcDecl.paramList, level + indentValue);
            traverseAST(node->funcDecl.block, level + indentValue);
            break;
        case NodeType_Block:
            printIndent(level);
            printf("Block\n");
            traverseAST(node->block.varDeclList, level + indentValue);
            traverseAST(node->block.stmtList, level + indentValue);
            break;
        case NodeType_ParamList:
            printIndent(level);
            printf("Parameter List\n");
            traverseAST(node->paramList.param, level + indentValue);
            traverseAST(node->paramList.paramList, level + indentValue);
            break;
        case NodeType_Param:
            printIndent(level);
            printf("Parameter: %s %s\n", node->param.varName, node->param.varType);
            break;
    }
}

// print one node
void printASTNode(ASTNode* node) {
    if (!node) {
        printf ("Nothing to print\n");
        return;
    }
    //printf("Traversing node of type %d\n", node->type);
    switch (node->type) {
        case NodeType_Program:
            printf("Program\n");
            break;
        case NodeType_VarDeclList:
            printf("Variable Declaration List\n");
            break;
        case NodeType_VarDecl:
            printf("Variable Declaration: %s %s\n", node->varDecl.varType, node->varDecl.varName);
            break;
        case NodeType_SimpleExpr:
            printf("Simple Expression:\n");
            break;
        case NodeType_SimpleID:
            printf("Simple Identifier: %s\n", node->simpleID.name);
        case NodeType_Expr:
            printf("Expression\n");
            break;
        case NodeType_StmtList:
            printf("Statement List\n");
            break;
        case NodeType_Stmt:
            printf("Statement: %s %s\n", node->stmt.varName, node->stmt.operator);
            break;
        case NodeType_AssignStmt:
            printf("Assignment: %s = %s\n", node->assignStmt.varName, "node->assignStmt.expr");
            break;
        case NodeType_BinOp:
            printf("BinOp: %c\n", node->binOp.operator);
            break;
        case NodeType_WriteStmt:
            printf("Write: %s\n", node->writeStmt.varName);
            break;
        case NodeType_FuncDeclList:
            printf("Function Declaration List\n");
            break;
        case NodeType_FuncDecl:
            printf("Function Declaration: %s\n", node->funcDecl.funcName);
            break;
        case NodeType_Block:
            printf("Block\n");
            break;
        case NodeType_ParamList:
            printf("Parameter List\n");
            break;
        case NodeType_Param:
            printf("Parameter: %s %s\n", node->param.varName, node->param.varType);
            break;
    }
} 

void freeAST(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NodeType_Program:
            free(node->program.varDeclList);
            free(node->program.stmtList);
            break;
        case NodeType_VarDeclList:
            free(node->varDeclList.varDecl);
            free(node->varDeclList.varDeclList);
            break;
        case NodeType_VarDecl:
            free(node->varDecl.varType);
            free(node->varDecl.varName);
            break;
        case NodeType_SimpleExpr:
            // free(node->simpleExpr.number);
            break;
        case NodeType_SimpleID:
            // free(node->simpleID.name);
            break;
        case NodeType_Expr:
            free(node->expr.left);
            free(node->expr.right);
            // free(node->expr.operator);
            break;
        case NodeType_StmtList:
            free(node->stmtList.stmt);
            free(node->stmtList.stmtList);
            break;
        case NodeType_Stmt:
            free(node->stmt.varName);
            free(node->stmt.operator);
            free(node->stmt.expr);
            break;
        case NodeType_AssignStmt:
            free(node->assignStmt.varName);
            free(node->assignStmt.expr);
            break;
        case NodeType_WriteStmt:
            free(node->writeStmt.varName);
            break;
        case NodeType_BinOp:
            free(node->binOp.left);
            free(node->binOp.right);
            // free(node->binOp.operator);
            break;  
        case NodeType_FuncDeclList:
            free(node->funcDeclList.funcDecl);
            free(node->funcDeclList.funcDeclList);
            break;
        case NodeType_FuncDecl:
            free(node->funcDecl.funcName);
            free(node->funcDecl.paramList);
            free(node->funcDecl.block);
            break;
        case NodeType_Block:
            free(node->block.varDeclList);
            free(node->block.stmtList);
            break;
        case NodeType_ParamList:
            free(node->paramList.param);
            free(node->paramList.paramList);
            break;
        case NodeType_Param:
            free(node->param.varName);
            free(node->param.varType);
            break;
    }

    free(node);
}

ASTNode* createNode(NodeType type) {
    ASTNode* newNode = (ASTNode*)malloc(sizeof(ASTNode));
    if (newNode == NULL) {
        // Handle memory allocation failure if needed
        return NULL;
    }

    newNode->type = type;

    // Initialize the node based on its type
    switch (type) {
        case NodeType_Program:
            newNode->program.varDeclList = NULL;
            newNode->program.stmtList = NULL;
            break;
        case NodeType_VarDeclList:
            newNode->varDeclList.varDecl = NULL;
            newNode->varDeclList.varDeclList = NULL;
            break;
        case NodeType_VarDecl:
            newNode->varDecl.varType = NULL;
            newNode->varDecl.varName = NULL;
            break;
        case NodeType_SimpleExpr:
            // newNode->simpleExpr.number = NULL;
            break;
        case NodeType_SimpleID:
            // newNode->simpleID.name = NULL;
            break;
        case NodeType_Expr:
            newNode->expr.operator = '\0';  // Placeholder value
            newNode->expr.left = NULL;
            newNode->expr.right = NULL;
            break;
        case NodeType_StmtList:
            newNode->stmtList.stmt = NULL;  // Example initialization
            newNode->stmtList.stmtList = NULL;
            break;
        case NodeType_Stmt:
            newNode->stmt.operator = NULL;  // Example initialization
            newNode->stmt.varName = NULL;
            newNode->stmt.expr = NULL;
            break;
        case NodeType_AssignStmt:
            newNode->assignStmt.varName = NULL;
            newNode->assignStmt.expr = NULL;
            break;
        case NodeType_WriteStmt:
            newNode->writeStmt.varName = NULL;
            break;
        case NodeType_BinOp:
            newNode->binOp.operator = '\0';  // Placeholder value
            newNode->binOp.left = NULL;
            newNode->binOp.right = NULL;
            break;
        // Add more cases as necessary for other node types
        case NodeType_FuncDeclList:
            newNode->funcDeclList.funcDecl = NULL;
            newNode->funcDeclList.funcDeclList = NULL;
            break;
        case NodeType_FuncDecl:
            newNode->funcDecl.funcName = NULL;
            newNode->funcDecl.paramList = NULL;
            newNode->funcDecl.block = NULL;
            break;
        case NodeType_Block:
            newNode->block.varDeclList = NULL;
            newNode->block.stmtList = NULL;
            break;
        case NodeType_ParamList:
            newNode->paramList.param = NULL;
            newNode->paramList.paramList = NULL;
            break;
        case NodeType_Param:
            newNode->param.varName = NULL;
            newNode->param.varType = NULL;
            break;
    }

    return newNode;
}
