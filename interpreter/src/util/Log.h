#pragma once

namespace Log {
    void Error(int size, ...);
    void Print(int size, ...);

    void PrintToken(int type, const char* val);
    void PrintStatement(int type);
    
    void UnexpectedToken(const char* value);
    void MissingSemicolon();
    void UnrecognizedIdentifier(const char* value);
}