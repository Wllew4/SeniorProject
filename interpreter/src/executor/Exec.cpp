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
                std::cout << statement->val->val.string.value;
            }
            else if(statement->val->type == ExprNodeType::EXPR_NUM){
                std::cout << *statement->val->val.num.value;
            }
            else if(statement->val->type == ExprNodeType::EXPR_ID){
                std::cout << buffer->GetByName(statement->val->val.id.name)->asString();
            }

            if(statement->type == StmtNodeType::STMT_PRINTLN){ std::cout << std::endl; }
            return;
        
        //Number Declaration
        case StmtNodeType::STMT_NUMDECL:
            if(buffer->GetByName(statement->val->val.id.name) != nullptr){
                Log::RedefinedIdentifier(statement->val->val.id.name);
                exit(0);
            }
            if(statement->val->type == ExprNodeType::EXPR_ID){
                buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_NUM), new double (0), statement->val->val.id.name);
                break;
            }
            buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_NUM), Eval::EvalNumExpr(statement->val->val.binop.right), statement->val->val.binop.left->val.id.name);
            break;

        //String Declaration
        case StmtNodeType::STMT_STRINGDECL:
            if(buffer->GetByName(statement->val->val.id.name) != nullptr){
                Log::RedefinedIdentifier(statement->val->val.id.name);
                exit(0);
            }
            if(statement->val->type == ExprNodeType::EXPR_ID){
                buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_STRING), new char(0), statement->val->val.id.name);
                break;
            }
            buffer->AddPrimitive(new TYPE_PRIMITIVE (TYPE_STRING), new char(0), statement->val->val.binop.left->val.id.name);
            buffer->GetByName(statement->val->val.binop.left->val.id.name)->setValue(Eval::EvalStringExpr(statement->val->val.binop.right));
            break;

        case StmtNodeType::STMT_CONDITIONAL:
            if(*Eval::EvalBoolExpr(statement->val)){
                for(StmtNode* conditionals : statement->body){
                    Exec(conditionals);
                }
            }
            else {
                for(StmtNode* conditionals : statement->elsebody){
                    Exec(conditionals);
                }
            }
            break;

        case StmtNodeType::STMT_WHILE:
            while(*Eval::EvalBoolExpr(statement->val)){
                for(StmtNode* conditionals : statement->body){
                    Exec(conditionals);
                }
            }
            break;

        //Expression Statements
        case StmtNodeType::STMT_EXPR:
            switch(*buffer->GetByName(statement->val->val.binop.left->val.id.name)->getType()){
                case TYPE_PRIMITIVE::TYPE_NUM:
                    buffer->GetByName(statement->val->val.binop.left->val.id.name)->setValue(Eval::EvalNumExpr(statement->val->val.binop.right));
                    break;
                case TYPE_PRIMITIVE::TYPE_STRING:
                    buffer->GetByName(statement->val->val.binop.left->val.id.name)->setValue(statement->val->val.binop.right->val.string.value);
                    break;
            }
            break;

        case StmtNodeType::STMT_SCOPE:
            for(StmtNode* node : statement->body){
                Exec(node);
            }
            break;
    }
}