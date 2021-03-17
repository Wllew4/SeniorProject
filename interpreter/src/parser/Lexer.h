#pragma once

#include "Token.h"

namespace Lexer {
    namespace {
        char* m_position;
        int m_line = 1;
    }
    void Init(char* file);
    Token getNextToken();
}