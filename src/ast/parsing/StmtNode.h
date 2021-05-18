#pragma once

#include "ast/lexing/Token.h"
#include "ast/parsing/ExprNode.h"

#include <vector>
#include <variant>

#include <memory>

enum StmtNodeType {
    STMT_PRINT,
    STMT_PRINTLN,
    STMT_STRINGDECL,
    STMT_NUMDECL,
    STMT_EXPR,
    STMT_WHILE,
    STMT_CONDITIONAL,
    STMT_ELSE,
    STMT_SCOPE
};

struct StmtNode;

struct FlowControl
{
    ExprNode* boolean;
    std::shared_ptr<StmtNode> body;
};

struct StmtNode {
    StmtNodeType type;

    //ExprNode* val;

    std::variant <
        ExprNode*,
        FlowControl,
        std::vector<std::shared_ptr<StmtNode>>,
        std::shared_ptr<StmtNode>> data;

    StmtNode(StmtNodeType t, ExprNode* v)
    {
        type = t;
        data.emplace<0>(v);
    }

    StmtNode(StmtNodeType t, FlowControl v)
    {
        type = t;
        data.emplace<1>(v);
    }

    StmtNode(StmtNodeType t, std::vector<std::shared_ptr<StmtNode>> d)
    {
        type = t;
        data.emplace<2>(d);
    }

    StmtNode(StmtNodeType t, std::shared_ptr<StmtNode> d)
    {
        type = t;
        data.emplace<3>(d);
    }

    StmtNode(const StmtNode& o)
    {
        type = o.type;
        data = o.data;
    }

    /*StmtNode* body;
    StmtNode* elsebody;*/

    //std::vector<StmtNode*> scope;
};