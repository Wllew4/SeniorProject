#pragma once

#include "Token.h"
#include "Node.h"

namespace Parser {
    namespace {
        Token m_next;
        Token m_current;
    }
    
    void parseNext();

    void printToken();

    void parse();

    void parseExpression();

    void parseCurrentToken();
}