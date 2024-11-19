#ifndef AST_H
#define AST_H

// Include standard libraries as needed, e.g., stdlib 
// for memory management functions
#include <stdlib.h>
#include <stdio.h>

#include "symbol_table.h"

// NodeType enum to differentiate between different 
// kinds of AST nodes
typedef enum { 
    NodeType_Program,
    NodeType_VarDeclList, 
    NodeType_VarDecl, 
    NodeType_SimpleExpr,
    NodeType_SimpleID,
    NodeType_Expr, 
    NodeType_FuncSignature,
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
    NodeType_ReturnStmt,
    NodeType_FuncCall,
    NodeType_InputParam,
    NodeType_InputParamList,
    NodeType_ArrayDeclList,
    NodeType_ArrayDecl,
    NodeType_ArrayAssignStmt,
    NodeType_ArrayAccess,
    NodeType_TypeCast,
    NodeType_IfStmt,
    NodeType_IfStmtSignature,   
    NodeType_LogicExpr,
    NodeType_IfBlock,
} NodeType;

// Structure for AST nodes
typedef struct ASTNode {
    NodeType type;
    union {
        struct{
            struct ASTNode* varDeclList;
            struct ASTNode* stmtList;
            struct ASTNode* funcDeclList;
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
            char* number;
            char* temp;
            char* type;
        } simpleExpr;

        struct {
            char* name;
            char* temp;
        } simpleID;

        struct {
            // Expression-speci fic fields
            char operator;  // Example for an operator field
            struct ASTNode* left;  // Left operand
            struct ASTNode* right; // Right operand
            char* expr_type; // Type of the expression
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
            struct ASTNode* funcSignature;
            symbol_table* scope;    
        } funcDecl;

        struct {
            char* funcName;
            char* funcType;
            symbol_table* scope;
        } funcSignature;

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
            struct ASTNode* returnStmt;
            struct ASTNode* arrayDeclList;
            symbol_table* scope;
        } block;

        struct {
            struct ASTNode* expr;
        } returnStmt;

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

        struct {
            char* funcName;
            struct ASTNode* inputParamList;
            char* temp;
        } funcCall;

        struct {
            char* value;
        } inputParam;

        struct {
            struct ASTNode* inputParam;
            struct ASTNode* inputParamList;
        } inputParamList;

        struct ArrayDeclList {
            struct ASTNode* arrayDecl;
            struct ASTNode* arrayDeclList;
        } arrayDeclList;
        
        struct ArrayDecl {
            char* varType;
            char* varName;
            char* size;
        } arrayDecl;
        
        struct ArrayAssignStmt {
            char* varName;
            char* index;
            struct ASTNode* expr;
        } arrayAssignStmt;

        struct ArrayAccess {
            char* varName;
            char* index;
            char* temp;
        } arrayAccess;

        struct TypeCast {
            char* name;
            char* type;
            struct ASTNode* expr;
        } typeCast;

        struct LogicExpr {
            char* operator;
            struct ASTNode* left;
            struct ASTNode* right;
            char* temp;
        } logicExpr;

        struct IfStmt {
            struct ASTNode* IfStmtSignature;
            struct ASTNode* block;
            char* false_label;
        } ifStmt;

        struct IfStmtSignature {
            struct ASTNode* condition;
            char* false_label;
        } ifStmtSignature;
        
        struct IfBlock {
            struct ASTNode* stmtList;
            char* false_label;
        } ifBlock;
    };
} ASTNode;

// Function prototypes for AST handling
ASTNode* createNode(NodeType type);
void freeAST(ASTNode* node);
void traverseAST(ASTNode* node, int level);
void printASTNode(ASTNode* node);

#endif // AST1_H