#include "Log.h"
#include <stdio.h>
#include <stdarg.h>

void Log::Error(int size, ...){
    va_list args;
    va_start(args, size);
    printf("\u001b[31mJANELLE:\tError:\t\033[0m");
    for(int i = 0; i < size; i++){
        printf(va_arg(args, const char*));
    }
    va_end(args);
}

void Log::Print(int size, ...){
    va_list args;
    va_start(args, size);
    printf("\u001b[36mJANELLE:\t\033[0m");
    for(int i = 0; i < size; i++){
        printf(va_arg(args, const char*));
    }
    va_end(args);
}

void Log::UnexpectedToken(int line, const char* value){
    char* linebuf = new char[5];
    itoa(line, linebuf, 10);
    Log::Error(4, "Unexpected token on line ", linebuf, ": ", value);
    delete linebuf;
}