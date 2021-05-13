#pragma once

#include "ast/lexing/Token.h"

namespace Lexer
{
    void Init(char* file);
    Token getNextToken();
    std::string getLine();
}