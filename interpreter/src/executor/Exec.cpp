#include "executor/Exec.h"
#include "executor/Eval.h"
#include "util/Log.h"
#include "util/Debug.h"
#include "object/Primitive.h"

#include <iostream>

PrimitiveBuffer* buffer = program.GetBuffer();

void Exec(StmtNode* statement){

    if(options[2]){
        Log::PrintStatement(statement->type);
    }
    switch(statement->type){
        //  Printing
        case StmtNodeType::STMT_PRINT:
        case StmtNodeType::STMT_PRINTLN:
            if(statement->val->type == ExprNodeType::EXPR_STRING){
                std::cout << statement->val->val.string;
            }
            else if(statement->val->type == ExprNodeType::EXPR_NUM){
                std::cout << statement->val->val.num;
            }
            else if(statement->val->type == ExprNodeType::EXPR_ID){
                std::cout << buffer->GetByName(statement->val->val.id)->asString();
            }

            if(statement->type == StmtNodeType::STMT_PRINTLN){ std::cout << std::endl; }
            return;
        
        //Number Declaration
        case StmtNodeType::STMT_NUMDECL:
            if(buffer->GetByName(statement->val->val.id) != nullptr){
                Log::RedefinedIdentifier(statement->val->val.id.c_str());
                exit(0);
            }
            if(statement->val->type == ExprNodeType::EXPR_ID){
                buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_NUM), new double (0), statement->val->val.id);
                break;
            }
            buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_NUM), Eval::EvalNumExpr(statement->val->val.binop.right), statement->val->val.binop.left->val.id);
            break;

        //String Declaration
        case StmtNodeType::STMT_STRINGDECL:
            if(buffer->GetByName(statement->val->val.id) != nullptr){
                Log::RedefinedIdentifier(statement->val->val.id.c_str());
                exit(0);
            }
            if(statement->val->type == ExprNodeType::EXPR_ID){
                buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_STRING), new char(0), statement->val->val.id);
                break;
            }
            buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_STRING), new char(0), statement->val->val.binop.left->val.id);
            buffer->GetByName(statement->val->val.binop.left->val.id)->setValue(Eval::EvalStringExpr(statement->val->val.binop.right));
            break;

        case StmtNodeType::STMT_CONDITIONAL:
            if(Eval::EvalBoolExpr(statement->val)){
                Exec(statement->body);
            }
            else {
                Exec(statement->elsebody);
            }
            break;

        case StmtNodeType::STMT_WHILE:
            while(Eval::EvalBoolExpr(statement->val)){
                Exec(statement->body);
            }
            break;

        //Expression Statements
        case StmtNodeType::STMT_EXPR:
            switch(*buffer->GetByName(statement->val->val.binop.left->val.id)->getType()){
                case TYPE_PRIMITIVE::TYPE_NUM:
                    buffer->GetByName(statement->val->val.binop.left->val.id)->setValue(Eval::EvalNumExpr(statement->val->val.binop.right));
                    break;
                case TYPE_PRIMITIVE::TYPE_STRING:
                    buffer->GetByName(statement->val->val.binop.left->val.id)->setValue(statement->val->val.binop.right->val.string);
                    break;
            }
            break;

        case StmtNodeType::STMT_SCOPE:
            buffer->IncreaseScope();
            for(auto i : statement->scope) Exec(i);
            buffer->DescreaseScope();
            break;
    }
}