#pragma once

#include "Token.h"

namespace Parser {
    namespace {
        Token m_next;
        Token m_current;
    }
    
    void parseNext();

    void printToken();

    void parse();
}