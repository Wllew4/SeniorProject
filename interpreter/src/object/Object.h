#pragma once
#include <vector>
#include <iostream>

class Object {
    protected:
        const char* m_name;
    public:
        inline const char* getName() { return m_name; }
        Object(const char* name) : m_name(name) {}
        virtual std::string getString() = 0;
};

class Num : public Object {
    protected:
        double* m_value;
    public:
        inline double* getValue() { return m_value; }
        inline void setValue(double* x){ m_value = x; }
        Num(const char* name, double* value) : Object(name), m_value(value) {}
        std::string getString();
};

class String : public Object {
    protected:
        const char* m_value;
    public:
        inline const char* getValue() { return m_value; }
        inline void setValue(const char* x){ m_value = x; }
        String(const char* name, const char* value) : Object(name), m_value(value) {}
        std::string getString();
};

class ObjectBuffer {
    private:
        std::vector<Num*>       numbuffer;
        std::vector<String*>    stringbuffer;
        std::vector<Object*>    objbuffer;

    public:
        Object* GetObjectByName(const char* name);
        Num* GetNumByName(const char* name);
        String* GetStringByName(const char* name);
        void AddNum(const char* name, double* value);
        void AddString(const char* name, const char* value);
};

extern ObjectBuffer ProgramBuffer;