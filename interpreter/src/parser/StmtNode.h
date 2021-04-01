#pragma once

#include "parser/Token.h"
#include "parser/ExprNode.h"

#include <vector>

enum StmtNodeType {
    STMT_PRINT,
    STMT_PRINTLN,
    STMT_STRINGDECL,
    STMT_NUMDECL,
    STMT_CONDITIONAL,
    STMT_WHILE,
    STMT_EXPR
};

struct StmtNode {
    StmtNodeType type;

    ExprNode* val;

    std::vector<StmtNode*> body;
    std::vector<StmtNode*> elsebody;
};