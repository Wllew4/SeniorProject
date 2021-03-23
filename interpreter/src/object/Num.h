#pragma once
#include "object/Object.h"
#include "parser/ExprNode.h"

class Num : public Object {
    protected:
        double* m_value;
        double* parseRvalue(ExprNode* node);
    public:
        inline double* getValue() { return m_value; }
        void setValue(double* x);
        void setRvalue(ExprNode* node);
        Num(const char* name, double* value) : Object(name), m_value(value) {}
        std::string getString();
};