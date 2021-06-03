#pragma once

//  Still needs name restandardization

#include "ast/lexing/Token.h"

#include <variant>
#include <memory>
#include <iostream>

enum class ExprNodeType
{
    EXPR_NUM    = 0,
    EXPR_STRING = 1,
    EXPR_ID     = 2,
    EXPR_BINOP  = 3,
    EXPR_UNOP   = 4
};

struct ExprNode
{
    struct binop
    {
        std::shared_ptr<ExprNode> left;
        std::shared_ptr<ExprNode> right;
        char op_type;

        /*~binop()
        {
            delete right;
            delete left;
        }*/
    };

    struct unop
    {
        std::shared_ptr<ExprNode> left;
        char op_type;
    };

    ExprNodeType type;

    //  Num, String, Id, binop, unop
    std::variant<double, std::string, std::string, binop, unop> val;
    
    void operator=(const ExprNode& r)
    {
        val = r.val;
    }
};