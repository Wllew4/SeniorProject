#pragma once

#include "ast/lexing/Token.h"
#include "ast/parsing/ExprNode.h"

#include <vector>

enum StmtNodeType {
    STMT_PRINT,
    STMT_PRINTLN,
    STMT_STRINGDECL,
    STMT_NUMDECL,
    STMT_CONDITIONAL,
    STMT_WHILE,
    STMT_EXPR,
    STMT_SCOPE
};

struct StmtNode {
    StmtNodeType type;

    ExprNode* val;

    StmtNode* body;
    StmtNode* elsebody;

    std::vector<StmtNode*> scope;
};