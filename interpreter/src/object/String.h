#pragma once
#include "object/Object.h"
#include "parser/ExprNode.h"

class String : public Object {
    protected:
        const char* m_value;
        const char* parseRvalue(ExprNode* node);
    public:
        inline const char* getValue() { return m_value; }
        void setValue(const char* x);
        void setRvalue(ExprNode* node);
        String(const char* name, const char* value) : Object(name), m_value(value) {}
        std::string getString();
};