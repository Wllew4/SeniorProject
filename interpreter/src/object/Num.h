#pragma once
#include "object/Object.h"

class Num : public Object {
    protected:
        double* m_value;
    public:
        inline double* getValue() { return m_value; }
        inline void setValue(double* x){ m_value = x; }
        Num(const char* name, double* value) : Object(name), m_value(value) {}
        std::string getString();
};