#include "object/ObjectBuffer.h"
#include "util/Log.h"
#include <string.h>

Object* ObjectBuffer::GetObjectByName(const char* name){
    for(Num* obj : numbuffer){
        if(strcmp(obj->getName(), name) == 0){
            return obj;
        }
    }
    for(String* obj : stringbuffer){
        if(strcmp(obj->getName(), name) == 0){
            return obj;
        }
    }
    for(Object* obj : objbuffer){
        if(strcmp(obj->getName(), name) == 0){
            return obj;
        }
    }
    Log::UnrecognizedIdentifier(name);
    exit(0);
}

Num* ObjectBuffer::GetNumByName(const char* name){
    for(Num* obj : numbuffer){
        if(strcmp(obj->getName(), name) == 0){
            return obj;
        }
    }
    Log::UnrecognizedIdentifier(name);
    exit(0);
}

String* ObjectBuffer::GetStringByName(const char* name){
    for(String* obj : stringbuffer){
        if(strcmp(obj->getName(), name) == 0){
            return obj;
        }
    }
    Log::UnrecognizedIdentifier(name);
    exit(0);
}

ObjectType ObjectBuffer::GetObjectType(const char* name){
    for(Num* obj : numbuffer){
        if(strcmp(obj->getName(), name) == 0){
            return ObjectType::OBJ_NUM;
        }
    }
    for(String* obj : stringbuffer){
        if(strcmp(obj->getName(), name) == 0){
            return ObjectType::OBJ_STRING;
        }
    }
    Log::UnrecognizedIdentifier(name);
    exit(0);
}

void ObjectBuffer::AddNum(const char* name, double* value){
    numbuffer.push_back(new Num(name, value));
}

void ObjectBuffer::AddString(const char* name, const char* value){
    stringbuffer.push_back(new String(name, value));
}