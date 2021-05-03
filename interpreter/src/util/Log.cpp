#include "Log.h"
#include "parser/Lexer.h"
#include <stdarg.h>
#include <iostream>
#include <string>
#include <cstring>

const char* tokentypes[] = {
    "StringDecl",   "NumDecl",
    "String",       "Number",
    "ID",           "Print",
    "Printline",    "EQ",
    "Plus",         "Minus",
    "Mult",         "Div",
    "Modulus",      "If",
    "Else",         "While",
    "LThan",        "GThan",
    "OpenBrace",    "CloseBrace",
    "Semicolon",    "EOF"
};

const char* primitivetypes[] = {
    "num",
    "string",
    "bool"
};

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
    Log::Print(6,"TOKEN:\t", "Type: ", tokentypes[type], strlen(tokentypes[type]) < 10 ? "\t\t" : "\t", val, "\n");
}

void Log::PrintStatement(int type){
    Log::Print(4,"STATEMENT:\t", "Type: ", std::to_string(type).c_str(), "\n");
}

void Log::UnexpectedToken(const char* value){
    Log::Error(4, "Unexpected token on line ", Lexer::getLine(), ": ", value);
}

void Log::MissingToken(int x){
    Log::Error(5, "Missing token of type ", tokentypes[x], " on line ", Lexer::getLine(), "\n");
}

void Log::UnrecognizedIdentifier(const char* value){
    Log::Error(4, "Unrecognized Identifier on line ", Lexer::getLine(), ": ", value);
}

void Log::RedefinedIdentifier(const char* value){
    Log::Error(4, "Redefined Identifier on line ", Lexer::getLine(), ": ", value);
}

void Log::CannotImplicitlyConvert(const TYPE_PRIMITIVE& l, const TYPE_PRIMITIVE& r)
{
    Log::Error(5, "Cannot implicitly convert object of type ", primitivetypes[l], " to ", primitivetypes[r], ".");
}