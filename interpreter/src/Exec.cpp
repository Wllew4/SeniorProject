#include "Exec.h"
#include <iostream>

void Exec(StmtNode* statement){
    switch(statement->type){
        case StmtNodeType::STMT_PRINT:
            if(statement->val.print.expr_string->type == ExprNodeType::EXPR_STRING) std::cout << statement->val.print.expr_string->val.string.value;
            else {
                std::cout << statement->val.print.expr_string->val.num.value;
            }
            return;
        case StmtNodeType::STMT_PRINTLN:
            if(statement->val.print.expr_string->type == ExprNodeType::EXPR_STRING) std::cout << statement->val.print.expr_string->val.string.value << std::endl;
            else {
                std::cout << statement->val.print.expr_string->val.num.value << std::endl;
            }
            return;
        case StmtNodeType::STMT_NUMDECL:
            if(statement->val.numassign.expr->type == ExprNodeType::EXPR_BINOP){
                std::cout << statement->val.numassign.expr->val.binop.left->val.id.name << std::endl;
                std::cout << statement->val.numassign.expr->val.binop.right->val.num.value;
            }
            break;
        case StmtNodeType::STMT_EXPR:
            std::cout << statement->val.exprstmt.expr->val.binop.left->val.id.name << std::endl;
            std::cout << statement->val.exprstmt.expr->val.binop.right->val.num.value;
            break;
    }
}