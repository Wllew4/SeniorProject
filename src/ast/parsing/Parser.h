#pragma once

#include "ast/lexing/Lexer.h"
#include "ast/lexing/Token.h"
#include "ast/parsing/StmtNode.h"

#include <memory>

class Parser {
public:
    void ParseNext();

    void Init(char* _file);

    bool IsDone();

    ExprNode* ParseAtomicExpr();
    ExprNode* ParseUnopExpr();
    ExprNode* ParseBinopExpr();

    ExprNode* ParseExpr();

    std::unique_ptr<StmtNode> ParseNode();

    StmtNodeType TokenTypeToStmtType(TokenType& _tokenType);
    
private:
      Token m_next;
      Token m_current;
      Lexer m_lexer;
};