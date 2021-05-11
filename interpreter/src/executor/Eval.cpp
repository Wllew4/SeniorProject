#include "executor/Eval.h"
#include "util/Math.h"
#include "util/Log.h"
#include <string>
#include <string.h>

double Eval::EvalNumExpr(ExprNode* node)
{
    
    double result;
    ExprNode left;
    ExprNode right;
    if(node->type == ExprNodeType::EXPR_BINOP)
    {
        if(node->val.binop.left->type == ExprNodeType::EXPR_ID)
        {
            left.type = ExprNodeType::EXPR_NUM;
            left.val.num.value = buffer->GetByName(node->val.binop.left->val.id.name)->asNum();
        } 
        else left = *node->val.binop.left;

        if(node->val.binop.right->type == ExprNodeType::EXPR_ID)
        {
            right.type = ExprNodeType::EXPR_NUM;
            right.val.num.value = buffer->GetByName(node->val.binop.right->val.id.name)->asNum();
        }
        else right = *node->val.binop.right;
        
        switch(node->val.binop.op_type)
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
        left.val.num.value = -buffer->GetByName(node->val.id.name)->asNum();
        result = left.val.num.value;
    }
    else if(node->type == ExprNodeType::EXPR_ID)
    {
        left.type = ExprNodeType::EXPR_NUM;
        left.val.num.value = buffer->GetByName(node->val.id.name)->asNum();
        result = left.val.num.value;
    }
    else
    {
        result = node->val.num.value;
    }
    return result;
}

const char* Eval::EvalStringExpr(ExprNode* node)
{
    const char* result;
    if(node->type == ExprNodeType::EXPR_BINOP)
    {
        if(node->val.binop.left->type == ExprNodeType::EXPR_ID)
        {
            node->val.binop.left->type = ExprNodeType::EXPR_STRING;
            node->val.binop.left->val.string.value = buffer->GetByName(node->val.binop.left->val.id.name)->asString();
        }
        if(node->val.binop.right->type == ExprNodeType::EXPR_ID)
        {
            node->val.binop.right->type = ExprNodeType::EXPR_STRING;
            node->val.binop.right->val.string.value = buffer->GetByName(node->val.binop.right->val.id.name)->asString();
        }
        if(node->val.binop.op_type == '+')
        {
            std::string* concat = new std::string(std::string(EvalStringExpr(node->val.binop.left)) + std::string(EvalStringExpr(node->val.binop.right)));
            result = (*concat).c_str();
        }
        else
        {
            Log::UnexpectedToken(&node->val.binop.op_type);
        }
    }
    else
    {
        if(node->type == ExprNodeType::EXPR_ID)
        {
            node->type = ExprNodeType::EXPR_STRING;
            node->val.string.value = buffer->GetByName(node->val.string.value)->asString();
        }
        result = node->val.string.value;
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

    switch(node->val.binop.op_type){
        case '=':
            if(Eval::EvalNumExpr(node->val.binop.left) == Eval::EvalNumExpr(node->val.binop.right)){
                return true;
            }
            else {
                return false;
            }
            break;
        case '<':
            if(Eval::EvalNumExpr(node->val.binop.left) < Eval::EvalNumExpr(node->val.binop.right)){
                return true;
            }
            else {
                return false;
            }
            break;
        case '>':
            if(Eval::EvalNumExpr(node->val.binop.left) > Eval::EvalNumExpr(node->val.binop.right)){
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
const char* Eval::toString(Primitive* val)
{
    switch(*val->getType()){
        case TYPE_PRIMITIVE::TYPE_STRING:
            return val->getData().string.c_str();
        case TYPE_PRIMITIVE::TYPE_NUM:
            return std::to_string(val->getData().num).c_str();
        case TYPE_PRIMITIVE::TYPE_BOOL:
            if(val->getData().boolean) return "true";
            else return "false";
    }
    return nullptr;
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