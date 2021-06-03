#include "execution/Execution.h"

#include "evaluation/Eval.h"
#include "debug/Log.h"
#include "ast/parsing/Parser.h"

#include <iostream>

Exec::Exec(PrimitiveBuffer& _program)
    : m_eval(_program) {}

void Exec::Init(char* _file)
{
    m_parser.Init(_file);

    while (!m_parser.IsDone()) {
        std::shared_ptr<StmtNode> stmt = m_parser.ParseNode();
        Execute(stmt);
        m_parser.ParseNext();
    }
}

void Exec::Execute(std::shared_ptr<StmtNode> _statement)
{
    switch(_statement->type){
        //  Printing
        case StmtNodeType::STMT_PRINT:
        case StmtNodeType::STMT_PRINTLN:
            if(std::get<0>(_statement->data)->type == ExprNodeType::EXPR_STRING)
            {
                std::cout << m_eval.EvalStringExpr(std::get<0>(_statement->data).get());
            }
            else if(std::get<0>(_statement->data)->type == ExprNodeType::EXPR_NUM)
            {
                std::cout << m_eval.EvalNumExpr(std::get<0>(_statement->data).get());
            }
            else if(std::get<0>(_statement->data)->type == ExprNodeType::EXPR_ID)
            {
                std::cout << m_eval.GetBuffer().GetByName(std::get<2>(std::get<0>(_statement->data)->val)).AsString();
            }

            if(_statement->type == StmtNodeType::STMT_PRINTLN){ std::cout << std::endl; }
            break;
        
        //Number Declaration
        case StmtNodeType::STMT_NUMDECL:
        {
            ExprNode* expression = std::get<0>(_statement->data).get();

            if (std::get<0>(_statement->data)->type == ExprNodeType::EXPR_ID)
            {
                m_eval.GetBuffer().AddPrimitive(PrimitiveType::Num, 0.0, std::get<2>(expression->val));
                break;
            }
            m_eval.GetBuffer().AddPrimitive(PrimitiveType::Num, m_eval.EvalNumExpr(std::get<3>(expression->val).right.get()), std::get<2>(std::get<3>(expression->val).left->val));
            break;
        }
        
        //String Declaration
        case StmtNodeType::STMT_STRINGDECL:
        {
            ExprNode* expression = std::get<0>(_statement->data).get();

            if (std::get<0>(_statement->data)->type == ExprNodeType::EXPR_ID)
            {
                m_eval.GetBuffer().AddPrimitive(PrimitiveType::String, std::string(), std::get<2>(expression->val));
                break;
            }
            m_eval.GetBuffer().AddPrimitive(PrimitiveType::String, m_eval.EvalStringExpr(std::get<3>(expression->val).right.get()), std::get<2>(std::get<3>(expression->val).left->val));
            break;
        }

        //If _statements
        case StmtNodeType::STMT_CONDITIONAL:
        {
            bool bContainsElse = std::get<FlowControlWithElse>(_statement->data).elsebody.get()->type == StmtNodeType::STMT_ELSE;
            bool bIsTrue = m_eval.EvalBoolExpr(std::get<FlowControlWithElse>(_statement->data).boolean.get());
            if (bContainsElse && bIsTrue)
            {
                Execute(std::get<FlowControlWithElse>(_statement->data).body);
            }
            else if(bIsTrue)
            {
                Execute(std::get<FlowControlWithElse>(_statement->data).body);
                Execute(std::get<FlowControlWithElse>(_statement->data).elsebody);
            }
            else if (bContainsElse)
            {
                Execute(std::get<4>(std::get<FlowControlWithElse>(_statement->data).elsebody.get()->data));
            }
            else
            {
                Execute(std::get<FlowControlWithElse>(_statement->data).elsebody);
            }
            break;
        }

        //While loops
        case StmtNodeType::STMT_WHILE:
            while(m_eval.EvalBoolExpr(std::get<FlowControl>(_statement->data).boolean.get())){
                Execute(std::get<FlowControl>(_statement->data).body);
            }
            break;

        //Expression _statements
        case StmtNodeType::STMT_EXPR:
            switch(m_eval.GetBuffer().GetByName(std::get<2>(std::get<3>(std::get<0>(_statement->data)->val).left->val)).GetType()){
                case PrimitiveType::Num:
                    m_eval.GetBuffer().GetByName(std::get<2>(std::get<3>(std::get<0>(_statement->data)->val).left->val)).SetValue(m_eval.EvalNumExpr(std::get<3>(std::get<0>(_statement->data)->val).right.get()));
                    break;
                case PrimitiveType::String:
                    m_eval.GetBuffer().GetByName(std::get<2>(std::get<3>(std::get<0>(_statement->data)->val).left->val)).SetValue(m_eval.EvalStringExpr(std::get<3>(std::get<0>(_statement->data)->val).right.get()));
                    break;
            }
            break;

        //Scopes
        case StmtNodeType::STMT_SCOPE:
            m_eval.GetBuffer().IncreaseScope();
            for(auto i : std::get<2>(_statement->data)) Execute(i);
            m_eval.GetBuffer().DescreaseScope();
            break;
    }
}