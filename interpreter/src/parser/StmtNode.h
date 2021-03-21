#pragma once

#include "parser/Token.h"
#include "parser/ExprNode.h"

enum StmtNodeType {
    STMT_PRINT,
    STMT_PRINTLN,
    STMT_STRINGDECL,
    STMT_NUMDECL,
    STMT_EXPR
};

struct StmtNode {
    StmtNodeType type;

    union {
        struct {
            ExprNode* expr_string;
        } print;
        
        struct {
            ExprNode* expr;
        } exprstmt;

        struct {
            ExprNode* expr;
        } numassign;

        struct {
            ExprNode* expr;
        } stringassign;
    } val;
};