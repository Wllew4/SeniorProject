#include "object/String.h"
#include "object/ObjectBuffer.h"
#include "util/Log.h"

extern ObjectBuffer ProgramBuffer;

std::string String::getString(){
    return this->getValue();
}

void String::setValue(const char* x){
    delete m_value;
    m_value = x;
}

void String::setRvalue(ExprNode* node){
    setValue(parseRvalue(node));
}

const char* String::parseRvalue(ExprNode* node){
    const char* result;
    if(node->type == ExprNodeType::EXPR_BINOP){
        if(node->val.binop.left->type == ExprNodeType::EXPR_ID){
            node->val.binop.left->type = ExprNodeType::EXPR_STRING;
            node->val.binop.left->val.string.value = ProgramBuffer.GetStringByName(node->val.binop.left->val.id.name)->getValue();
        }
        if(node->val.binop.right->type == ExprNodeType::EXPR_ID){
            node->val.binop.right->type = ExprNodeType::EXPR_STRING;
            node->val.binop.right->val.string.value = ProgramBuffer.GetStringByName(node->val.binop.right->val.id.name)->getValue();
        }
        if(node->val.binop.op_type == '+'){
            std::string* concat = new std::string(std::string(parseRvalue(node->val.binop.left)) + std::string(parseRvalue(node->val.binop.right)));
            result = (*concat).c_str();
        }
        else {
            Log::UnexpectedToken(&node->val.binop.op_type);
        }
    }
    else {
        if(node->type == ExprNodeType::EXPR_ID){
            node->type = ExprNodeType::EXPR_STRING;
            node->val.string.value = ProgramBuffer.GetStringByName(node->val.string.value)->getValue();
        }
        result = node->val.string.value;
    }

    return result;
}