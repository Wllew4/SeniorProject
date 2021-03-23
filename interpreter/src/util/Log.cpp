#include "Log.h"
#include "parser/Lexer.h"
#include <stdarg.h>
#include <iostream>
#include <string>

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
    static const char* tokentypes[] = {
        "StringDecl\t",   "NumDecl\t\t",
        "String\t\t",       "Number\t\t",
        "ID\t\t",           "Print\t\t",
        "Printline\t\t",    "EQ\t\t",
        "Plus\t\t",         "Minus\t\t",
        "Semicolon\t\t",    "EOF\t\t"};
    Log::Print(5,"TOKEN:\t", "Type: ", tokentypes[type], val, "\n");
}

void Log::PrintStatement(int type){
    Log::Print(4,"STATEMENT:\t", "Type: ", std::to_string(type).c_str(), "\n");
}

void Log::UnexpectedToken(const char* value){
    std::string linebuf = std::to_string(Lexer::m_line);
    Log::Error(4, "Unexpected token on line ", linebuf, ": ", value);
}

void Log::MissingSemicolon(){
    std::string linebuf = std::to_string(Lexer::m_line);
    Log::Error(3, "Missing semicolon on line ", linebuf, "\n");
}

void Log::UnrecognizedIdentifier(const char* value){
    std::string linebuf = std::to_string(Lexer::m_line);
    Log::Error(4, "Unrecognized Identifier on line ", linebuf, ": ", value);
}