#pragma once

#include "object/Primitive.h"

namespace Log {
    void Error(int size, ...);
    void Print(int size, ...);

    void PrintToken(int type, const char* val);
    void PrintStatement(int type);
    
    void UnexpectedToken(const char* value);
    void MissingToken(int x);
    void UnrecognizedIdentifier(const char* value);
    void RedefinedIdentifier(const char* value);
    void CannotImplicitlyConvert(const TYPE_PRIMITIVE& l, const TYPE_PRIMITIVE& r);
}