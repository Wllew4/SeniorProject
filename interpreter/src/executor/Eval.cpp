#include "executor/Eval.h"
#include "object/ObjectBuffer.h"
#include "util/Math.h"

extern ObjectBuffer ProgramBuffer;

double Eval::EvalNum(ExprNode* node){
    double result = 0;
    ExprNode* left;
    if(node->type == ExprNodeType::EXPR_BINOP){
        ExprNode* right;
        if(node->val.binop.left->type == ExprNodeType::EXPR_ID){
            left = new ExprNode;
            left->type = ExprNodeType::EXPR_NUM;
            left->val.num.value = ProgramBuffer.GetNumByName(node->val.binop.left->val.id.name)->getValue();
        } else left = node->val.binop.left;
        if(node->val.binop.right->type == ExprNodeType::EXPR_ID){
            right = new ExprNode;
            right->type = ExprNodeType::EXPR_NUM;
            right->val.num.value = ProgramBuffer.GetNumByName(node->val.binop.right->val.id.name)->getValue();
        } else right = node->val.binop.right;
        switch(node->val.binop.op_type){
            case '+':
                result = EvalNum(left) + EvalNum(right);
                break;
            case '-':
                result = EvalNum(left) - EvalNum(right);
                break;
            case '*':
                result = EvalNum(left) * EvalNum(right);
                break;
            case '/':
                result = EvalNum(left) / EvalNum(right);
                break;
            case '%':
                result = modulus(EvalNum(left), EvalNum(right));
                break;
        }
    }
    else if(node->type == ExprNodeType::EXPR_UNOP){
        left = new ExprNode;
        left->type = ExprNodeType::EXPR_NUM;
        left->val.num.value = -ProgramBuffer.GetNumByName(node->val.id.name)->getValue();
        result = left->val.num.value;
    }
    else if(node->type == ExprNodeType::EXPR_ID){
        left = new ExprNode;
        left->type = ExprNodeType::EXPR_NUM;
        left->val.num.value = ProgramBuffer.GetNumByName(node->val.id.name)->getValue();
        result = left->val.num.value;
    }
    else {
        result = node->val.num.value;
    }
    return result;
}