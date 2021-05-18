#pragma once

#include "ast/lexing/Token.h"
#include "ast/parsing/StmtNode.h"

#include <memory>

namespace Parser {
    namespace {
        Token m_next;
        Token m_current;
    }
    
    void parseNext();

    void Init(char* file);

    bool IsDone();

    ExprNode* parseAtomicExpr();
    ExprNode* parseUnopExpr();
    ExprNode* parseBinopExpr();

    //ExprNode* parseBooleanExpr();

    ExprNode* parseExpr();

    std::unique_ptr<StmtNode> parseNode();

    StmtNodeType TokenTypeToStmtType(TokenType& t);
}