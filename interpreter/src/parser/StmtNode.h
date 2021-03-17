#pragma once
#include <vector>

#include "Token.h"
#include "ExprNode.h"

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

    void exec (){
        switch(type){

        }
    }
};