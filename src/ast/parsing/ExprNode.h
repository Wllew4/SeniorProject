#pragma once

#include "ast/lexing/Token.h"

#include <variant>

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
        ExprNode* left;
        ExprNode* right;
        char op_type;
    };

    struct unop
    {
        ExprNode* left;
        char op_type;
    };

    ExprNodeType type;

    std::variant<double, std::string, std::string, binop, unop> val;
    
    void operator=(const ExprNode& r)
    {
        val = r.val;
    }

    /*union val{
        double num;

        std::string string;

        std::string id;

        struct {
            ExprNode* left;
            ExprNode* right;
            char op_type;
        } binop;

        struct {
            ExprNode* left;
            char op_type;
        } unop;

        val() { id = ""; }
        ~val(){}
        val(const val& r){ id = ""; }
    } val;*/
};