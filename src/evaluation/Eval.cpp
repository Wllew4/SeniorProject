#include "evaluation/Eval.h"
#include "evaluation/Math.h"
#include "debug/Log.h"
#include <string>
#include <string.h>

#include <iostream>

double Eval::EvalNumExpr(ExprNode* node)
{
    
    double result = 0;
    ExprNode left = ExprNode();
    ExprNode right = ExprNode();
    if(node->type == ExprNodeType::EXPR_BINOP)
    {
        if(std::get<3>(node->val).left->type == ExprNodeType::EXPR_ID)
        {
            left.type = ExprNodeType::EXPR_NUM;
            left.val.emplace<0>(buffer->GetByName(std::get<2>(std::get<3>(node->val).left->val))->asNum());
        }
        else left = *std::get<3>(node->val).left;

        if(std::get<3>(node->val).right->type == ExprNodeType::EXPR_ID)
        {
            right.type = ExprNodeType::EXPR_NUM;
            right.val.emplace<0>(buffer->GetByName(std::get<2>(std::get<3>(node->val).right->val))->asNum());
        }
        else right = *std::get<3>(node->val).right;
        
        switch(std::get<3>(node->val).op_type)
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
                //std::cout << "ranmodulus";
                result = modulus(EvalNumExpr(&left), EvalNumExpr(&right));
                //std::cout << *result << std::endl;
                break;
        }
    }
    else if(node->type == ExprNodeType::EXPR_UNOP)
    {
        left.type = ExprNodeType::EXPR_NUM;
        left.val.emplace<0>(-buffer->GetByName(std::get<2>(node->val))->asNum());
        result = std::get<0>(left.val);
    }
    else if(node->type == ExprNodeType::EXPR_ID)
    {
        left.type = ExprNodeType::EXPR_NUM;
        left.val.emplace<0>(buffer->GetByName(std::get<2>(node->val))->asNum());
        result = std::get<0>(left.val);
    }
    else
    {
        result = std::get<0>(node->val);
    }
    return result;
}

std::string Eval::EvalStringExpr(ExprNode* node)
{
    std::string result;
    if(node->type == ExprNodeType::EXPR_BINOP)
    {
        if(std::get<3>(node->val).left->type == ExprNodeType::EXPR_ID)
        {
            std::get<3>(node->val).left->type = ExprNodeType::EXPR_STRING;
            std::get<1>(std::get<3>(node->val).left->val) = buffer->GetByName(std::get<2>(std::get<3>(node->val).left->val))->asString();
        }
        if(std::get<3>(node->val).right->type == ExprNodeType::EXPR_ID)
        {
            std::get<3>(node->val).right->type = ExprNodeType::EXPR_STRING;
            std::get<1>(std::get<3>(node->val).right->val) = buffer->GetByName(std::get<2>(std::get<3>(node->val).right->val))->asString();
        }
        if(std::get<3>(node->val).op_type == '+')
        {
            std::string* concat = new std::string(std::string(EvalStringExpr(std::get<3>(node->val).left)) + std::string(EvalStringExpr(std::get<3>(node->val).right)));
            result = (*concat).c_str();
        }
        else
        {
            Log::UnexpectedToken(&std::get<3>(node->val).op_type);
        }
    }
    else
    {
        if(node->type == ExprNodeType::EXPR_ID)
        {
            node->type = ExprNodeType::EXPR_STRING;
            std::get<1>(node->val) = buffer->GetByName(std::get<1>(node->val))->asString();
        }
        result = std::get<1>(node->val);
    }

    return result;
}

// TYPE_PRIMITIVE getExprType()
// {

// }

// uhhhhh
bool Eval::EvalBoolExpr(ExprNode* node)
{
    // bool* result;
    // TYPE_PRIMITIVE exprtype = getExprType();
    // Primitive left (new TYPE_PRIMITIVE(TYPE_STRING), new Data(), "left");
    // Primitive right (new TYPE_PRIMITIVE(TYPE_STRING), new Data(), "right");

    // if(node->type == ExprNodeType::EXPR_BINOP){

    // }
    switch(std::get<3>(node->val).op_type){
        case '=':
            if(Eval::EvalNumExpr(std::get<3>(node->val).left) == Eval::EvalNumExpr(std::get<3>(node->val).right)){
                return true;
            }
            else {
                return false;
            }
            break;
        case '<':
            if(Eval::EvalNumExpr(std::get<3>(node->val).left) < Eval::EvalNumExpr(std::get<3>(node->val).right)){
                return true;
            }
            else {
                return false;
            }
            break;
        case '>':
            if(Eval::EvalNumExpr(std::get<3>(node->val).left) > Eval::EvalNumExpr(std::get<3>(node->val).right)){
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
std::string Eval::toString(Primitive* val)
{
    switch(*val->getType()){
        case TYPE_PRIMITIVE::TYPE_STRING:
            return val->getData().string;
        case TYPE_PRIMITIVE::TYPE_NUM:
            return std::to_string(val->getData().num);
        case TYPE_PRIMITIVE::TYPE_BOOL:
            if(val->getData().boolean) return "true";
            else return "false";
    }
    return "";
}

bool Eval::toBool(Primitive* val)
{
    switch(*val->getType()){
        case TYPE_PRIMITIVE::TYPE_STRING:
            if(strcmp(val->getData().string.c_str(), "") == 0) return false;
            else return true;
        case TYPE_PRIMITIVE::TYPE_NUM:
            if(val->getData().num) return true;
            else return false;
        case TYPE_PRIMITIVE::TYPE_BOOL:
            return val->getData().boolean;
    }
    return false;
}