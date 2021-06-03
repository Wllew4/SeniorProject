#include "ast/parsing/Parser.h"
#include "ast/lexing/Lexer.h"

#include "debug/Callback.h"
#include "debug/Log.h"

void Parser::ParseNext(){
    m_current = m_next;
    m_next = m_lexer.GetNextToken();
    Debug::Callback::NewToken(m_next);
}

void Parser::Init(char* _file){
    m_lexer.Init(_file);
    ParseNext();
}

bool Parser::IsDone()
{
    return m_next.type == TokenType::T_EOF;
}

ExprNode* Parser::ParseAtomicExpr(){
    ParseNext();
    switch(m_current.type){
        case TokenType::T_ID: {
            ExprNode* idexpr = new ExprNode();
            idexpr->type = ExprNodeType::EXPR_ID;
            //std::cout << m_current.value;
            idexpr->val.emplace<2>(m_current.value);
            //std::cout << idexpr->val.id;
            return idexpr;
        }
        case TokenType::T_NUM: {
            ExprNode* numexpr = new ExprNode();
            numexpr->type = ExprNodeType::EXPR_NUM;
            numexpr->val.emplace<0>(std::stod(m_current.value));
            return numexpr;
        }
        case TokenType::T_STRING: {
            ExprNode* stringexpr = new ExprNode();
            stringexpr->type = ExprNodeType::EXPR_STRING;
            stringexpr->val.emplace<1>(m_current.value);
            return stringexpr;
        }
        default:
            Debug::Log::UnhandledException(201) << "Unexpected token: " << m_current.value << '\n';
            exit(0);
    }
}

ExprNode* Parser::ParseUnopExpr(){
    ExprNode* expr = NULL;
    while(m_next.type == T_MINUS){
        ParseNext();
        ExprNode* oldexpr = expr;
        expr = new ExprNode();
        expr->type = ExprNodeType::EXPR_UNOP;
        expr->val.emplace<4>(ExprNode::unop({ std::unique_ptr<ExprNode>(oldexpr), '-'}));
    }
    if(expr == NULL) expr = ParseAtomicExpr();
    else {
        ExprNode* traversal = expr;
        while(std::get<4>(traversal->val).left != NULL){
            traversal = std::get<4>(traversal->val).left.get();
        }
        //definitely breaks. need more abstraction.
        //std::get<4>(traversal->val).left = ParseAtomicExpr();
    }
    return expr;
}

ExprNode* Parser::ParseBinopExpr(){
    ExprNode* expr = ParseUnopExpr();
    while(m_next.type == T_PLUS || m_next.type == T_MINUS || m_next.type == T_MULT || m_next.type == T_DIV || m_next.type == T_MODULUS){
        char type;
        switch(m_next.type){
            case T_PLUS: type = '+'; break;
            case T_MINUS: type = '-'; break;
            case T_MULT: type = '*'; break;
            case T_DIV: type = '/'; break;
            case T_MODULUS: type = '%'; break;
        }
        ParseNext();
        ExprNode* left = expr;
        ExprNode* right = ParseUnopExpr();
        expr = new ExprNode();
        expr->type = ExprNodeType::EXPR_BINOP;
        expr->val.emplace<3>(ExprNode::binop({std::shared_ptr<ExprNode>(left), std::shared_ptr<ExprNode>(right), type}));
    }
    return expr;
}

ExprNode* Parser::ParseExpr(){
    ExprNode* expr = ParseBinopExpr();
    if(m_next.type == T_EQ || m_next.type == T_LESSTHAN || m_next.type == T_GREATERTHAN){
        char type;
        switch(m_next.type){
            case T_EQ: type = '='; break;
            case T_LESSTHAN: type = '<'; break;
            case T_GREATERTHAN: type = '>'; break;
        }
        ParseNext();
        ExprNode* left = expr;
        ExprNode* right = ParseExpr();
        expr = new ExprNode();
        expr->type = ExprNodeType::EXPR_BINOP;
        expr->val.emplace<3>(ExprNode::binop({ std::shared_ptr<ExprNode>(left), std::shared_ptr<ExprNode>(right), type }));
    }
    return expr;
}

std::unique_ptr<StmtNode> Parser::ParseNode()
{

    StmtNodeType t = TokenTypeToStmtType(m_next.type);
    
    if (t == StmtNodeType::STMT_EXPR)
    {
        return std::unique_ptr<StmtNode>(new StmtNode(t, ParseExpr()));
    }
    if (t <= StmtNodeType::STMT_NUMDECL)
    {
        ParseNext();
        return std::unique_ptr<StmtNode>(new StmtNode(t, ParseExpr()));
    }
    if (t == StmtNodeType::STMT_WHILE)
    {
        ParseNext();
        return std::unique_ptr<StmtNode>(new StmtNode(t, ParseExpr(), std::shared_ptr<StmtNode>(ParseNode()) ));
    }
    if (t <= StmtNodeType::STMT_CONDITIONAL)
    {
        ParseNext();
        auto expr = ParseExpr();
        auto stmt = std::shared_ptr<StmtNode>(ParseNode());
        ParseNext();
        auto elsestmt = std::shared_ptr<StmtNode>(ParseNode());
        return std::unique_ptr<StmtNode>(new StmtNode(t, expr, stmt, elsestmt ));
    }
    if (t == StmtNodeType::STMT_ELSE)
    {
        ParseNext();
        return std::unique_ptr<StmtNode>(new StmtNode(t, std::shared_ptr<StmtNode>(ParseNode())));
    }
    if (t == StmtNodeType::STMT_SCOPE)
    {
        ParseNext();
        std::vector<std::shared_ptr<StmtNode>> stmts;
        while (m_next.type != TokenType::T_CLOSEBRACE)
        {
            stmts.push_back(ParseNode());
            ParseNext();
        }
        //ParseNext();
        return std::unique_ptr<StmtNode>(new StmtNode(t, stmts));
    }

    return nullptr;
}

StmtNodeType Parser::TokenTypeToStmtType(TokenType& _tokenType)
{
    switch (_tokenType)
    {
        case TokenType::T_PRINT:
            return StmtNodeType::STMT_PRINT;
        case TokenType::T_PRINTLN:
            return StmtNodeType::STMT_PRINTLN;
        case TokenType::T_STRINGDECL:
            return StmtNodeType::STMT_STRINGDECL;
        case TokenType::T_NUMDECL:
            return StmtNodeType::STMT_NUMDECL;
        case TokenType::T_IF:
            return StmtNodeType::STMT_CONDITIONAL;
        case TokenType::T_ELSE:
            return StmtNodeType::STMT_ELSE;
        case TokenType::T_WHILE:
            return StmtNodeType::STMT_WHILE;
        case TokenType::T_OPENBRACE:
            return StmtNodeType::STMT_SCOPE;
        default:
            return StmtNodeType::STMT_EXPR;
    }
    return StmtNodeType();
}