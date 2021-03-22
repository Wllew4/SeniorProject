#pragma once
#include <iostream>

class Object {
    protected:
        const char* m_name;
    public:
        inline const char* getName() { return m_name; }
        Object(const char* name) : m_name(name) {}
        virtual std::string getString() = 0;
};