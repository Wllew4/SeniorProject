#pragma once
#include <string>

namespace Log {
    void Error(int size, ...);
    void Print(int size, ...);
    
    void UnexpectedToken(int line, const char* value);
}