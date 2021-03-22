#include "Exec.h"
#include "object/ObjectBuffer.h"
#include <iostream>

ObjectBuffer ProgramBuffer;

void Exec(StmtNode* statement){
    switch(statement->type){
        case StmtNodeType::STMT_PRINT:
        case StmtNodeType::STMT_PRINTLN:
            if(statement->val.print.expr_string->type == ExprNodeType::EXPR_STRING){
                std::cout << statement->val.print.expr_string->val.string.value;
            }
            else if(statement->val.print.expr_string->type == ExprNodeType::EXPR_NUM){
                std::cout << statement->val.print.expr_string->val.num.value;
            }
            else if(statement->val.print.expr_string->type == ExprNodeType::EXPR_ID){
                std::cout << ProgramBuffer.GetObjectByName(statement->val.print.expr_string->val.id.name)->getString();
            }

            if(statement->type == StmtNodeType::STMT_PRINTLN){ std::cout << std::endl; }
            return;
        case StmtNodeType::STMT_NUMDECL:
            if(statement->val.numassign.expr->type == ExprNodeType::EXPR_ID){
                ProgramBuffer.AddNum(statement->val.numassign.expr->val.id.name, new double(0));
                break;
            }
            ProgramBuffer.AddNum(statement->val.exprstmt.expr->val.binop.left->val.id.name, 0);
            ProgramBuffer.GetNumByName(statement->val.exprstmt.expr->val.binop.left->val.id.name)->setValue(&statement->val.exprstmt.expr->val.binop.right->val.num.value);
						
            break;

        case StmtNodeType::STMT_STRINGDECL:
            if(statement->val.stringassign.expr->type == ExprNodeType::EXPR_ID){
                ProgramBuffer.AddString(statement->val.stringassign.expr->val.id.name, new char(0));
                break;
            }
            ProgramBuffer.AddString(statement->val.exprstmt.expr->val.binop.left->val.id.name, 0);
            ProgramBuffer.GetStringByName(statement->val.exprstmt.expr->val.binop.left->val.id.name)->setValue(statement->val.exprstmt.expr->val.binop.right->val.string.value);
            break;

        case StmtNodeType::STMT_EXPR:
            if(statement->val.exprstmt.expr->val.binop.right->type == ExprNodeType::EXPR_NUM){
                ProgramBuffer.GetNumByName(statement->val.exprstmt.expr->val.binop.left->val.id.name)->setValue(&statement->val.exprstmt.expr->val.binop.right->val.num.value);
                break;
            }
            if(statement->val.exprstmt.expr->val.binop.right->type == ExprNodeType::EXPR_STRING){
                ProgramBuffer.GetStringByName(statement->val.exprstmt.expr->val.binop.left->val.id.name)->setValue(statement->val.exprstmt.expr->val.binop.right->val.string.value);
                break;
            }
    }
}