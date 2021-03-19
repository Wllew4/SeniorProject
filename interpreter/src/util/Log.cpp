#include "Log.h"
#include <stdarg.h>
#include <iostream>

void Log::Error(int size, ...){
    va_list args;
    va_start(args, size);
    std::cout << "\u001b[31mJANELLE:\tError:\t\033[0m";
    for(int i = 0; i < size; i++){
        std::cout << va_arg(args, const char*);
    }
    va_end(args);

    fflush(stdout);

    exit(0);
}

void Log::Print(int size, ...){
    va_list args;
    va_start(args, size);
    std::cout << "\u001b[36mJANELLE:\t\033[0m";
    for(int i = 0; i < size; i++){
        std::cout << va_arg(args, const char*);
    }
    va_end(args);

    fflush(stdout);
}

void Log::PrintToken(int type, const char* val){
    static const char* tokentypes[] = {"StringDecl", "NumDecl", "String", "Number", "ID", "Print", "Printline", "EQ", "Plus", "Minus", "Semicolon", "EOF"};
    Log::Print(6,"TOKEN:\t", "Type: ", tokentypes[type], "\t\t", val, "\n");
}

void Log::UnexpectedToken(int line, const char* value){
    char* linebuf = new char[5];
    itoa(line, linebuf, 10);
    Log::Error(4, "Unexpected token on line ", linebuf, ": ", value);
    delete linebuf;
}

void Log::MissingSemicolon(int line){
    char* linebuf = new char[5];
    itoa(line, linebuf, 10);
    Log::Error(3, "Missing semicolon on line ", linebuf, "\n");
}