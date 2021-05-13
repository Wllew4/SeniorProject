#include "execution/Exec.h"
#include "evaluation/Eval.h"
#include "debug/Log.h"
#include "debug/Debug.h"
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
                std::cout << std::get<1>(statement->val->val);
            }
            else if(statement->val->type == ExprNodeType::EXPR_NUM){
                std::cout << std::get<0>(statement->val->val);
            }
            else if(statement->val->type == ExprNodeType::EXPR_ID){
                std::cout << buffer->GetByName(std::get<2>(statement->val->val))->asString();
            }

            if(statement->type == StmtNodeType::STMT_PRINTLN){ std::cout << std::endl; }
            return;
        
        //Number Declaration
        case StmtNodeType::STMT_NUMDECL:
            //if(buffer->GetByName(std::get<2>(statement->val->val)) != nullptr){
                //Log::RedefinedIdentifier(std::get<2>(statement->val->val).c_str());
                //exit(0);
            //}
            if(statement->val->type == ExprNodeType::EXPR_ID){
                buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_NUM), new double (0), std::get<2>(statement->val->val));
                break;
            }
            buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_NUM), Eval::EvalNumExpr(std::get<3>(statement->val->val).right), std::get<2>(std::get<3>(statement->val->val).left->val));
            break;

        //String Declaration
        case StmtNodeType::STMT_STRINGDECL:
            if(buffer->GetByName(std::get<2>(statement->val->val)) != nullptr){
                Log::RedefinedIdentifier(std::get<2>(statement->val->val).c_str());
                exit(0);
            }
            if(statement->val->type == ExprNodeType::EXPR_ID){
                buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_STRING), new char(0), std::get<2>(statement->val->val));
                break;
            }
            buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_STRING), new char(0), std::get<2>(std::get<3>(statement->val->val).left->val));
            buffer->GetByName(std::get<2>(std::get<3>(statement->val->val).left->val))->setValue(Eval::EvalStringExpr(std::get<3>(statement->val->val).right));
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
            switch(*buffer->GetByName(std::get<2>(std::get<3>(statement->val->val).left->val))->getType()){
                case TYPE_PRIMITIVE::TYPE_NUM:
                    buffer->GetByName(std::get<2>(std::get<3>(statement->val->val).left->val))->setValue(Eval::EvalNumExpr(std::get<3>(statement->val->val).right));
                    break;
                case TYPE_PRIMITIVE::TYPE_STRING:
                    buffer->GetByName(std::get<2>(std::get<3>(statement->val->val).left->val))->setValue(std::get<1>(std::get<3>(statement->val->val).right->val));
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