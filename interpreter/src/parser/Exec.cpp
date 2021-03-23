#include "parser/Exec.h"
#include "object/ObjectBuffer.h"
#include "util/Log.h"
#include "util/Debug.h"
#include <iostream>

ObjectBuffer ProgramBuffer;

void Exec(StmtNode* statement){

    if(options[2]){
        Log::PrintStatement(statement->type);
    }

    switch(statement->type){
        //  Printing
        case StmtNodeType::STMT_PRINT:
        case StmtNodeType::STMT_PRINTLN:
            if(statement->val->type == ExprNodeType::EXPR_STRING){
                std::cout << statement->val->val.string.value;
            }
            else if(statement->val->type == ExprNodeType::EXPR_NUM){
                std::cout << statement->val->val.num.value;
            }
            else if(statement->val->type == ExprNodeType::EXPR_ID){
                std::cout << ProgramBuffer.GetObjectByName(statement->val->val.id.name)->getString();
            }

            if(statement->type == StmtNodeType::STMT_PRINTLN){ std::cout << std::endl; }
            return;
        
        //Number Declaration
        case StmtNodeType::STMT_NUMDECL:
            if(ProgramBuffer.GetObjectByName(statement->val->val.id.name) != nullptr){
                Log::RedefinedIdentifier(statement->val->val.id.name);
                exit(0);
            }
            if(statement->val->type == ExprNodeType::EXPR_ID){
                ProgramBuffer.AddNum(statement->val->val.id.name, new double(0));
                break;
            }
            ProgramBuffer.AddNum(statement->val->val.binop.left->val.id.name, nullptr);
            ProgramBuffer.GetNumByName(statement->val->val.binop.left->val.id.name)->setRvalue(statement->val->val.binop.right);
            break;

        //String Declaration
        case StmtNodeType::STMT_STRINGDECL:
        if(ProgramBuffer.GetObjectByName(statement->val->val.id.name) != nullptr){
                Log::RedefinedIdentifier(statement->val->val.id.name);
                exit(0);
            }
            if(statement->val->type == ExprNodeType::EXPR_ID){
                ProgramBuffer.AddString(statement->val->val.id.name, new char(0));
                break;
            }
            ProgramBuffer.AddString(statement->val->val.binop.left->val.id.name, 0);
            ProgramBuffer.GetStringByName(statement->val->val.binop.left->val.id.name)->setRvalue(statement->val->val.binop.right);
            break;

        //Expression Statements
        case StmtNodeType::STMT_EXPR:
            switch(ProgramBuffer.GetObjectType(statement->val->val.binop.left->val.id.name)){
                case ObjectType::OBJ_NUM:
                    ProgramBuffer.GetNumByName(statement->val->val.binop.left->val.id.name)->setRvalue(statement->val->val.binop.right);
                    break;
                case ObjectType::OBJ_STRING:
                    ProgramBuffer.GetStringByName(statement->val->val.binop.left->val.id.name)->setValue(statement->val->val.binop.right->val.string.value);
                    break;
            }
    }
}