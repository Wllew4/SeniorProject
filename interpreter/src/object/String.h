#pragma once
#include "object/Object.h"

class String : public Object {
    protected:
        const char* m_value;
    public:
        inline const char* getValue() { return m_value; }
        inline void setValue(const char* x){ m_value = x; }
        String(const char* name, const char* value) : Object(name), m_value(value) {}
        std::string getString();
};