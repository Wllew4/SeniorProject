#include "Log.h"
#include <stdio.h>

void Log::Error(const char* msg){
    printf("\u001b[31mJANELLE:\t\u001b[36m%s\033[0m", msg);
}

void Log::Print(const char* msg){
    printf("\u001b[36mJANELLE:\t%s\033[0m", msg);
}

void Log::AddOn(const char* msg){
    printf("\u001b[36m%s\033[0m", msg);
}