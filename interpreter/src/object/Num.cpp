#include "object/Num.h"
#include <string>
#include "object/ObjectBuffer.h"

extern ObjectBuffer ProgramBuffer;

std::string Num::getString(){
    return std::to_string(*this->getValue());
}

void Num::setValue(double* x){
    delete m_value;
    m_value = x;
}

void Num::setRvalue(ExprNode* node){
    setValue(parseRvalue(node));
}

double* Num::parseRvalue(ExprNode* node){
    double* result = new double;
    if(node->type == ExprNodeType::EXPR_BINOP){
        if(node->val.binop.left->type == ExprNodeType::EXPR_ID){
            node->val.binop.left->type = ExprNodeType::EXPR_NUM;
            node->val.binop.left->val.num.value = *ProgramBuffer.GetNumByName(node->val.binop.left->val.id.name)->getValue();
        }
        if(node->val.binop.right->type == ExprNodeType::EXPR_ID){
            node->val.binop.right->type = ExprNodeType::EXPR_NUM;
            node->val.binop.right->val.num.value = *ProgramBuffer.GetNumByName(node->val.binop.right->val.id.name)->getValue();
        }
        switch(node->val.binop.op_type){
            case '+':
                *result = *parseRvalue(node->val.binop.left) + *parseRvalue(node->val.binop.right);

                break;
            case '-':
                *result = *parseRvalue(node->val.binop.left) - *parseRvalue(node->val.binop.right);
                break;
        }
    }
    else if(node->type == ExprNodeType::EXPR_UNOP){
        node->type = ExprNodeType::EXPR_NUM;
        node->val.num.value = -*ProgramBuffer.GetNumByName(node->val.unop.left->val.id.name)->getValue();
        *result = node->val.num.value;
    }
    else {
        if(node->type == ExprNodeType::EXPR_ID){
            node->type = ExprNodeType::EXPR_NUM;
            node->val.num.value = *ProgramBuffer.GetNumByName(node->val.id.name)->getValue();
        }
        *result = node->val.num.value;
    }

    return result;
}