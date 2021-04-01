#pragma once
#include "object/Object.h"
#include "parser/ExprNode.h"

class Num : public Object {
    protected:
        double m_value;
    public:
        double getValue();
        void setValue(double x);
        Num(const char* name, double value) : Object(name), m_value(value) {}
        std::string getString();
};