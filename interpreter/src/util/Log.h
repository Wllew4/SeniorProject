#pragma once

namespace Log {
    void Error(int size, ...);
    void Print(int size, ...);

    void PrintToken(int type, const char* val);
    
    void UnexpectedToken(int line, const char* value);
    void MissingSemicolon(int line);
}