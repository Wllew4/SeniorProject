#pragma once
#include <vector>

#include "parser/Token.h"
#include "parser/ExprNode.h"

enum StmtNodeType {
    STMT_PRINT,
    STMT_PRINTLN,
    EXPR_STMT
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
    } val;
};