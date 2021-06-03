#include "evaluation/Eval.h"

#include "debug/Log.h"
#include "evaluation/Math.h"

#include <iostream>
#include <string.h>

Eval::Eval(PrimitiveBuffer& _program)
    : m_buffer(_program) {}

PrimitiveBuffer& Eval::GetBuffer()
{
    return m_buffer;
}

double Eval::EvalNumExpr(ExprNode* _node)
{
    double result = 0;
    ExprNode left = ExprNode();
    ExprNode right = ExprNode();
    if(_node->type == ExprNodeType::EXPR_BINOP)
    {
        if(std::get<3>(_node->val).left->type == ExprNodeType::EXPR_ID)
        {
            left.type = ExprNodeType::EXPR_NUM;
            left.val.emplace<0>(m_buffer.GetByName(std::get<2>(std::get<3>(_node->val).left->val)).AsNum());
        }
        else left = *std::get<3>(_node->val).left;

        if(std::get<3>(_node->val).right->type == ExprNodeType::EXPR_ID)
        {
            right.type = ExprNodeType::EXPR_NUM;
            right.val.emplace<0>(m_buffer.GetByName(std::get<2>(std::get<3>(_node->val).right->val)).AsNum());
        }
        else right = *std::get<3>(_node->val).right;
        
        switch(std::get<3>(_node->val).op_type)
        {
            case '+':
                result = EvalNumExpr(&left) + EvalNumExpr(&right);
                break;
            case '-':
                result = EvalNumExpr(&left) - EvalNumExpr(&right);
                break;
            case '*':
                result = EvalNumExpr(&left) * EvalNumExpr(&right);
                break;
            case '/':
                result = EvalNumExpr(&left) / EvalNumExpr(&right);
                break;
            case '%':
                result = Math::Modulus(EvalNumExpr(&left), EvalNumExpr(&right));
                break;
        }
    }
    else if(_node->type == ExprNodeType::EXPR_UNOP)
    {
        left.type = ExprNodeType::EXPR_NUM;
        left.val.emplace<0>(-m_buffer.GetByName(std::get<2>(_node->val)).AsNum());
        result = std::get<0>(left.val);
    }
    else if(_node->type == ExprNodeType::EXPR_ID)
    {
        left.type = ExprNodeType::EXPR_NUM;
        left.val.emplace<0>(m_buffer.GetByName(std::get<2>(_node->val)).AsNum());
        result = std::get<0>(left.val);
    }
    else
    {
        result = std::get<0>(_node->val);
    }
    return result;
}

std::string Eval::EvalStringExpr(ExprNode* _node)
{
    std::string result;
    if(_node->type == ExprNodeType::EXPR_BINOP)
    {
        if(std::get<3>(_node->val).left->type == ExprNodeType::EXPR_ID)
        {
            std::get<3>(_node->val).left->type = ExprNodeType::EXPR_STRING;
            std::get<1>(std::get<3>(_node->val).left->val) = m_buffer.GetByName(std::get<2>(std::get<3>(_node->val).left->val)).AsString();
        }
        if(std::get<3>(_node->val).right->type == ExprNodeType::EXPR_ID)
        {
            std::get<3>(_node->val).right->type = ExprNodeType::EXPR_STRING;
            std::get<1>(std::get<3>(_node->val).right->val) = m_buffer.GetByName(std::get<2>(std::get<3>(_node->val).right->val)).AsString();
        }
        if(std::get<3>(_node->val).op_type == '+')
        {
            std::string* concat = new std::string(std::string(EvalStringExpr(std::get<3>(_node->val).left.get())) + std::string(EvalStringExpr(std::get<3>(_node->val).right.get())));
            result = (*concat).c_str();
        }
        else
        {
            //Log::UnexpectedToken(&std::get<3>(_node->val).op_type);
        }
    }
    else
    {
        if(_node->type == ExprNodeType::EXPR_ID)
        {
            _node->type = ExprNodeType::EXPR_STRING;
            std::get<1>(_node->val) = m_buffer.GetByName(std::get<1>(_node->val)).AsString();
        }
        result = std::get<1>(_node->val);
    }

    return result;
}

// TYPE_PRIMITIVE getExprType()
// {

// }

// uhhhhh
bool Eval::EvalBoolExpr(ExprNode* _node)
{
    // bool* result;
    // TYPE_PRIMITIVE exprtype = getExprType();
    // Primitive left (new TYPE_PRIMITIVE(TYPE_STRING), new Data(), "left");
    // Primitive right (new TYPE_PRIMITIVE(TYPE_STRING), new Data(), "right");

    // if(_node->type == ExprNodeType::EXPR_BINOP){

    // }
    switch(std::get<3>(_node->val).op_type){
        case '=':
            if(Eval::EvalNumExpr(std::get<3>(_node->val).left.get()) == Eval::EvalNumExpr(std::get<3>(_node->val).right.get())){
                return true;
            }
            else {
                return false;
            }
            break;
        case '<':
            if(Eval::EvalNumExpr(std::get<3>(_node->val).left.get()) < Eval::EvalNumExpr(std::get<3>(_node->val).right.get())){
                return true;
            }
            else {
                return false;
            }
            break;
        case '>':
            if(Eval::EvalNumExpr(std::get<3>(_node->val).left.get()) > Eval::EvalNumExpr(std::get<3>(_node->val).right.get())){
                return true;
            }
            else {
                return false;
            }
            break;
    }
    return false;
}

//  Save for later
std::string Eval::ToString(Primitive* _val)
{
    switch(_val->GetType()){
        case PrimitiveType::String:
            return _val->GetData().string;
        case PrimitiveType::Num:
            return std::to_string(_val->GetData().num);
        case PrimitiveType::Bool:
            if(_val->GetData().boolean) return "true";
            else return "false";
    }
    return "";
}

bool Eval::ToBool(Primitive* _val)
{
    switch(_val->GetType()){
        case PrimitiveType::String:
            if(strcmp(_val->GetData().string.c_str(), "") == 0) return false;
            else return true;
        case PrimitiveType::Num:
            if(_val->GetData().num) return true;
            else return false;
        case PrimitiveType::Bool:
            return _val->GetData().boolean;
    }
    return false;
}