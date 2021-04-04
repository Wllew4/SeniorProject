#pragma once

#include "parser/Token.h"

enum ExprNodeType {
    EXPR_NUM,
    EXPR_STRING,
    EXPR_ID,
    EXPR_BINOP,
    EXPR_UNOP
};

struct ExprNode {
    ExprNodeType type;

    union {
        struct {
            double* value;
        } num;

        struct {
            const char* value;
        } string;

        struct {
            const char* name;
        } id;

        struct {
            ExprNode* left;
            ExprNode* right;
            char op_type;
        } binop;

        struct {
            ExprNode* left;
            char op_type;
        } unop;
    } val;
};