#pragma once

#include "parser/Token.h"
#include <string>

enum ExprNodeType {
    EXPR_NUM,
    EXPR_STRING,
    EXPR_ID,
    EXPR_BINOP,
    EXPR_UNOP
};

struct ExprNode {
    ExprNodeType type;

    union val{
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

        val(){}
        ~val(){}
        val(const val& r){}
    } val;

    void operator=(const ExprNode& r){
        switch(r.type){
            case ExprNodeType::EXPR_NUM:
                val.num = r.val.num;
                break;
            case ExprNodeType::EXPR_STRING:
                val.string = r.val.string;
                break;
            case ExprNodeType::EXPR_ID:
                val.id = r.val.id;
                break;
            case ExprNodeType::EXPR_BINOP:
                val.binop = r.val.binop;
                break;
            case ExprNodeType::EXPR_UNOP:
                val.unop = r.val.unop;
                break;
        }
    }
};