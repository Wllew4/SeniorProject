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

    ExprNode* val;
};