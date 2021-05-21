#pragma once

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
    std::unique_ptr<ExprNode> boolean;
    std::shared_ptr<StmtNode> body;

    /*~FlowControl()
    {
        delete boolean;
    }*/
};
#include <iostream>
struct FlowControlWithElse
{
    std::unique_ptr<ExprNode> boolean;
    std::shared_ptr<StmtNode> body;
    std::shared_ptr<StmtNode> elsebody;

    /*~FlowControlWithElse()
    {
        if (boolean != NULL)
        {
            std::cout << boolean;
            delete boolean;
        }  
    }*/
};

struct StmtNode {
    StmtNodeType type;

    std::variant <
        std::unique_ptr<ExprNode>,
        FlowControl,
        std::vector<std::shared_ptr<StmtNode>>,
        FlowControlWithElse,
        std::shared_ptr<StmtNode>> data;

    StmtNode(StmtNodeType t, ExprNode* v)
    {
        type = t;
        data.emplace<0>(v);
    }

    StmtNode(StmtNodeType t, ExprNode* _b, std::shared_ptr<StmtNode> b)
    {
        type = t;
        data.emplace<1>(FlowControl({ std::unique_ptr<ExprNode>(_b), b }));
    }

    StmtNode(StmtNodeType t, std::vector<std::shared_ptr<StmtNode>> d)
    {
        type = t;
        data.emplace<2>(d);
    }

    StmtNode(StmtNodeType t, ExprNode* _b, std::shared_ptr<StmtNode> b, std::shared_ptr<StmtNode> eb)
    {
        type = t;
        data.emplace<3>(FlowControlWithElse({ std::unique_ptr<ExprNode>(_b), b, eb }));
    }

    StmtNode(StmtNodeType t, std::shared_ptr<StmtNode> d)
    {
        type = t;
        data.emplace<4>(d);
    }

    StmtNode(const StmtNode& o)
    {
        type = o.type;
        //data = o.data;
    }

    ~StmtNode()
    {
        /*if (data.index() == 0)
        {
            delete std::get<ExprNode*>(data);
        }*/
    }
};