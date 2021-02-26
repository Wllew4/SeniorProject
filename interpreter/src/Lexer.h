#pragma once

#include "Token.h"

namespace Lexer {
    namespace {
        char* m_position;
        int m_line;
    }
    void Init(char* file);
    Token getNextToken();
}