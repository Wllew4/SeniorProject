#pragma once

#include "Token.h"
#include "StmtNode.h"

namespace Parser {
    namespace {
        Token m_next;
        Token m_current;
    }
    
    void parseNext();

    void printToken();

    void parse();

    ExprNode* parseAtomicExpr();
    ExprNode* parseUnopExpr();
    ExprNode* parseBinopExpr();

    ExprNode* parseExpr();

    StmtNode* parseNode();
}