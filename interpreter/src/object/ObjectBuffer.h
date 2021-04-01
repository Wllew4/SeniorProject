#pragma once
#include "object/Object.h"
#include "object/Num.h"
#include "object/String.h"
#include <vector>

enum ObjectType {
    OBJ_NUM,
    OBJ_STRING
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
        ObjectType GetObjectType(const char* name);
        void AddNum(const char* name, double value);
        void AddString(const char* name, const char* value);
};