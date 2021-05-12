#pragma once

#include "ast/lexing/Token.h"
#include "ast/parsing/StmtNode.h"

namespace Parser {
    namespace {
        Token m_next;
        Token m_current;
    }
    
    void parseNext();

    void parse(char* file);

    ExprNode* parseAtomicExpr();
    ExprNode* parseUnopExpr();
    ExprNode* parseBinopExpr();

    //ExprNode* parseBooleanExpr();

    ExprNode* parseExpr();

    StmtNode* parseNode();
}