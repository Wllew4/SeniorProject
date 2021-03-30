#pragma once

#include "parser/Token.h"
#include "parser/StmtNode.h"

namespace Parser {
    namespace {
        Token m_next;
        Token m_current;
    }
    
    void parseNext();

    void printToken();

    void parse(char* file);

    ExprNode* parseAtomicExpr();
    ExprNode* parseUnopExpr();
    ExprNode* parseBinopExpr();

    ExprNode* parseBooleanExpr();

    ExprNode* parseExpr();

    StmtNode* parseNode();
}