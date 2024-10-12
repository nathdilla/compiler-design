#ifndef AST_H
#define AST_H

// Include standard libraries as needed, e.g., stdlib 
// for memory management functions
#include <stdlib.h>
#include <stdio.h>

// NodeType enum to differentiate between different 
// kinds of AST nodes
typedef enum { 
    NodeType_Program,
    NodeType_VarDeclList, 
    NodeType_VarDecl, 
    NodeType_SimpleExpr,
    NodeType_SimpleID,
    NodeType_Expr, 
    NodeType_FuncDecl,
    NodeType_FuncDeclList,
    NodeType_ParamList,
    NodeType_Param,
    NodeType_Block,
    NodeType_StmtList,
    NodeType_Stmt,
    NodeType_AssignStmt,
    NodeType_BinOp,
    NodeType_WriteStmt,
} NodeType;

// Structure for AST nodes
typedef struct ASTNode {
    NodeType type;
    union {
        struct{
            struct ASTNode* varDeclList;
            struct ASTNode* stmtList;
        } program;

        struct {
            struct ASTNode* varDecl;
            struct ASTNode* varDeclList;
        } varDeclList;

        struct {
            char* varType;
            char* varName;
        } varDecl;

        struct {
            int number;
            char* temp;
        } simpleExpr;

        struct {
            char* name;
            char* temp;
        } simpleID;

        struct {
            // Expression-specific fields
            char operator;  // Example for an operator field
            struct ASTNode* left;  // Left operand
            struct ASTNode* right; // Right operand
            char* temp; // Temporary variable for TAC
        } expr;

        struct {
            struct ASTNode* funcDecl;
            struct ASTNode* funcDeclList;
        } funcDeclList;

        struct {
            char* funcName;
            char* funcType;
            struct ASTNode* paramList;
            struct ASTNode* block;
        } funcDecl;

        struct {
            struct ASTNode* param;
            struct ASTNode* paramList;
        } paramList;

        struct {
            char* varType;
            char* varName;
        } param;

        struct {
            struct ASTNode* varDeclList;
            struct ASTNode* stmtList;
        } block;

        struct {
            // StatementList-specific fields
            struct ASTNode* stmt;
            struct ASTNode* stmtList; 
            // Example for linking statements in a list
        } stmtList;

        struct {
            char* operator; // e.g., '='
            char* varName;
            struct ASTNode* expr;
        } stmt;

        struct {
            char* varName;
            struct ASTNode* expr;
        } assignStmt;

        struct {
            char* varName;
        } writeStmt;

        struct {
            char operator;
            struct ASTNode* left;
            struct ASTNode* right;
        } binOp;
    };
} ASTNode;

// Function prototypes for AST handling
ASTNode* createNode(NodeType type);
void freeAST(ASTNode* node);
void traverseAST(ASTNode* node, int level);
void printASTNode(ASTNode* node);

#endif // AST1_H