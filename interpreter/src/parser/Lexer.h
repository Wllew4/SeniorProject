#pragma once

#include "parser/Token.h"

namespace Lexer {

    void Init(char* file);
    Token getNextToken();
    const char* getLine();
}