#include "execution/Exec.h"
#include "evaluation/Eval.h"
#include "debug/Log.h"
#include "ast/parsing/Parser.h"

#include <iostream>

PrimitiveBuffer& buffer = program.GetBuffer();

void Exec::Init(char* file)
{
    Parser::Init(file);

    while (!Parser::IsDone()) {
        std::shared_ptr<StmtNode> stmt = Parser::parseNode();
        Execute(stmt);
        Parser::parseNext();
    }
}

void Exec::Execute(std::shared_ptr<StmtNode> statement)
{
    switch(statement->type){
        //  Printing
        case StmtNodeType::STMT_PRINT:
        case StmtNodeType::STMT_PRINTLN:
            if(std::get<0>(statement->data)->type == ExprNodeType::EXPR_STRING)
            {
                std::cout << Eval::EvalStringExpr(std::get<0>(statement->data).get());
            }
            else if(std::get<0>(statement->data)->type == ExprNodeType::EXPR_NUM)
            {
                std::cout << Eval::EvalNumExpr(std::get<0>(statement->data).get());
            }
            else if(std::get<0>(statement->data)->type == ExprNodeType::EXPR_ID)
            {
                std::cout << buffer.GetByName(std::get<2>(std::get<0>(statement->data)->val))->asString();
            }

            if(statement->type == StmtNodeType::STMT_PRINTLN){ std::cout << std::endl; }
            break;
        
        //Number Declaration
        case StmtNodeType::STMT_NUMDECL:
        {
            ExprNode* expression = std::get<0>(statement->data).get();

            if (std::get<0>(statement->data)->type == ExprNodeType::EXPR_ID)
            {
                buffer.AddPrimitive(TYPE_PRIMITIVE::TYPE_NUM, 0.0, std::get<2>(expression->val));
                break;
            }
            buffer.AddPrimitive(TYPE_PRIMITIVE::TYPE_NUM, Eval::EvalNumExpr(std::get<3>(expression->val).right.get()), std::get<2>(std::get<3>(expression->val).left->val));
            break;
        }
        
        //String Declaration
        case StmtNodeType::STMT_STRINGDECL:
        {
            ExprNode* expression = std::get<0>(statement->data).get();

            if (std::get<0>(statement->data)->type == ExprNodeType::EXPR_ID)
            {
                buffer.AddPrimitive(TYPE_PRIMITIVE::TYPE_STRING, std::string(), std::get<2>(expression->val));
                break;
            }
            buffer.AddPrimitive(TYPE_PRIMITIVE::TYPE_STRING, Eval::EvalStringExpr(std::get<3>(expression->val).right.get()), std::get<2>(std::get<3>(expression->val).left->val));
            break;
        }

        //If statements
        case StmtNodeType::STMT_CONDITIONAL:
        {
            bool bContainsElse = std::get<FlowControlWithElse>(statement->data).elsebody.get()->type == StmtNodeType::STMT_ELSE;
            bool bIsTrue = Eval::EvalBoolExpr(std::get<FlowControlWithElse>(statement->data).boolean.get());
            if (bContainsElse && bIsTrue)
            {
                Execute(std::get<FlowControlWithElse>(statement->data).body);
            }
            else if(bIsTrue)
            {
                Execute(std::get<FlowControlWithElse>(statement->data).body);
                Execute(std::get<FlowControlWithElse>(statement->data).elsebody);
            }
            else if (bContainsElse)
            {
                Execute(std::get<4>(std::get<FlowControlWithElse>(statement->data).elsebody.get()->data));
            }
            else
            {
                Execute(std::get<FlowControlWithElse>(statement->data).elsebody);
            }
            break;
        }

        //While loops
        case StmtNodeType::STMT_WHILE:
            while(Eval::EvalBoolExpr(std::get<FlowControl>(statement->data).boolean.get())){
                Execute(std::get<FlowControl>(statement->data).body);
            }
            break;

        //Expression Statements
        case StmtNodeType::STMT_EXPR:
            switch(buffer.GetByName(std::get<2>(std::get<3>(std::get<0>(statement->data)->val).left->val))->getType()){
                case TYPE_PRIMITIVE::TYPE_NUM:
                    buffer.GetByName(std::get<2>(std::get<3>(std::get<0>(statement->data)->val).left->val))->setValue(Eval::EvalNumExpr(std::get<3>(std::get<0>(statement->data)->val).right.get()));
                    break;
                case TYPE_PRIMITIVE::TYPE_STRING:
                    buffer.GetByName(std::get<2>(std::get<3>(std::get<0>(statement->data)->val).left->val))->setValue(Eval::EvalStringExpr(std::get<3>(std::get<0>(statement->data)->val).right.get()));
                    break;
            }
            break;

        //Scopes
        case StmtNodeType::STMT_SCOPE:
            buffer.IncreaseScope();
            for(auto i : std::get<2>(statement->data)) Execute(i);
            buffer.DescreaseScope();
            break;
    }
}