#include "ast/parsing/Parser.h"
#include "ast/lexing/Lexer.h"

#include "execution/Exec.h"

#include "debug/Debug.h"

void Parser::parseNext(){
    m_current = m_next;
    m_next = l.getNextToken();
    Debug::callbackNewToken(m_next);
    if(options[1]){
        //Log::PrintToken(m_next.type, m_next.value.c_str());
    }
}

void Parser::Init(char* file){
    l.Init(file);
    parseNext();
}

bool Parser::IsDone()
{
    return m_next.type == TokenType::T_EOF;
}

ExprNode* Parser::parseAtomicExpr(){
    parseNext();
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

ExprNode* Parser::parseUnopExpr(){
    ExprNode* expr = NULL;
    while(m_next.type == T_MINUS){
        parseNext();
        ExprNode* oldexpr = expr;
        expr = new ExprNode();
        expr->type = ExprNodeType::EXPR_UNOP;
        expr->val.emplace<4>(ExprNode::unop({ std::unique_ptr<ExprNode>(oldexpr), '-'}));
    }
    if(expr == NULL) expr = parseAtomicExpr();
    else {
        ExprNode* traversal = expr;
        while(std::get<4>(traversal->val).left != NULL){
            traversal = std::get<4>(traversal->val).left.get();
        }
        //definitely breaks. need more abstraction.
        //std::get<4>(traversal->val).left = parseAtomicExpr();
    }
    return expr;
}

ExprNode* Parser::parseBinopExpr(){
    ExprNode* expr = parseUnopExpr();
    while(m_next.type == T_PLUS || m_next.type == T_MINUS || m_next.type == T_MULT || m_next.type == T_DIV || m_next.type == T_MODULUS){
        char type;
        switch(m_next.type){
            case T_PLUS: type = '+'; break;
            case T_MINUS: type = '-'; break;
            case T_MULT: type = '*'; break;
            case T_DIV: type = '/'; break;
            case T_MODULUS: type = '%'; break;
        }
        parseNext();
        ExprNode* left = expr;
        ExprNode* right = parseUnopExpr();
        expr = new ExprNode();
        expr->type = ExprNodeType::EXPR_BINOP;
        expr->val.emplace<3>(ExprNode::binop({std::shared_ptr<ExprNode>(left), std::shared_ptr<ExprNode>(right), type}));
    }
    return expr;
}

ExprNode* Parser::parseExpr(){
    ExprNode* expr = parseBinopExpr();
    if(m_next.type == T_EQ || m_next.type == T_LESSTHAN || m_next.type == T_GREATERTHAN){
        char type;
        switch(m_next.type){
            case T_EQ: type = '='; break;
            case T_LESSTHAN: type = '<'; break;
            case T_GREATERTHAN: type = '>'; break;
        }
        parseNext();
        ExprNode* left = expr;
        ExprNode* right = parseExpr();
        expr = new ExprNode();
        expr->type = ExprNodeType::EXPR_BINOP;
        expr->val.emplace<3>(ExprNode::binop({ std::shared_ptr<ExprNode>(left), std::shared_ptr<ExprNode>(right), type }));
    }
    return expr;
}

std::unique_ptr<StmtNode> Parser::parseNode()
{

    StmtNodeType t = TokenTypeToStmtType(m_next.type);
    if (options[2]) {
        //Log::PrintStatement(t);
    }
    
    if (t == StmtNodeType::STMT_EXPR)
    {
        return std::unique_ptr<StmtNode>(new StmtNode(t, parseExpr()));
    }
    if (t <= StmtNodeType::STMT_NUMDECL)
    {
        parseNext();
        return std::unique_ptr<StmtNode>(new StmtNode(t, parseExpr()));
    }
    if (t == StmtNodeType::STMT_WHILE)
    {
        parseNext();
        return std::unique_ptr<StmtNode>(new StmtNode(t, parseExpr(), std::shared_ptr<StmtNode>(parseNode()) ));
    }
    if (t <= StmtNodeType::STMT_CONDITIONAL)
    {
        parseNext();
        auto expr = parseExpr();
        auto stmt = std::shared_ptr<StmtNode>(parseNode());
        parseNext();
        auto elsestmt = std::shared_ptr<StmtNode>(parseNode());
        return std::unique_ptr<StmtNode>(new StmtNode(t, expr, stmt, elsestmt ));
    }
    if (t == StmtNodeType::STMT_ELSE)
    {
        parseNext();
        return std::unique_ptr<StmtNode>(new StmtNode(t, std::shared_ptr<StmtNode>(parseNode())));
    }
    if (t == StmtNodeType::STMT_SCOPE)
    {
        parseNext();
        std::vector<std::shared_ptr<StmtNode>> stmts;
        while (m_next.type != TokenType::T_CLOSEBRACE)
        {
            stmts.push_back(parseNode());
            parseNext();
        }
        //parseNext();
        return std::unique_ptr<StmtNode>(new StmtNode(t, stmts));
    }

    if (options[2]) {
        //Log::PrintStatement(t);
    }

    return nullptr;

    //return std::make_unique<StmtNode>(new StmtNode(t, v));

    /*StmtNode* b = new StmtNode();
    StmtNode* eb = new StmtNode();
    std::vector<StmtNode*> s;*/

    //switch (m_next.type){
    //    case TokenType::T_PRINTLN: {
    //        t = StmtNodeType::STMT_PRINTLN;
    //        parseNext();
    //        ExprNode* expr = parseExpr();
    //        if(m_next.type == TokenType::T_SEMICOLON){
    //            v = expr;
    //        }
    //        else Log::MissingToken(TokenType::T_SEMICOLON);
    //        return std::make_unique<StmtNode>();
    //        //return node;
    //    }
    //    case TokenType::T_PRINT: {
    //        t = StmtNodeType::STMT_PRINT;
    //        parseNext();
    //        ExprNode* expr = parseExpr();
    //        if(m_next.type == TokenType::T_SEMICOLON){
    //            v = expr;
    //        }
    //        else Log::MissingToken(TokenType::T_SEMICOLON);
    //        //return node;
    //    }
    //    case TokenType::T_NUMDECL: {
    //        t = StmtNodeType::STMT_NUMDECL;
    //        parseNext();
    //        ExprNode* expr = parseExpr();
    //        if(m_next.type == TokenType::T_SEMICOLON){
    //            v = expr;
    //        }
    //        else Log::MissingToken(TokenType::T_SEMICOLON);
    //        //return node;
    //    }
    //    case TokenType::T_STRINGDECL: {
    //        t = StmtNodeType::STMT_STRINGDECL;
    //        parseNext();
    //        ExprNode* expr = parseExpr();
    //        if(m_next.type == TokenType::T_SEMICOLON){
    //            v = expr;
    //        }
    //        else Log::MissingToken(TokenType::T_SEMICOLON);
    //        //return node;
    //    }
    //    case TokenType::T_IF: {
    //        t = StmtNodeType::STMT_CONDITIONAL;
    //        parseNext();
    //        ExprNode* expr = parseExpr();
    //        v = expr;
    //        b = parseNode().get();
    //        parseNext();
    //        if(m_next.type == T_ELSE){
    //            parseNext();
    //            eb = parseNode().get();
    //        }
    //        //return node;
    //    }
    //    case TokenType::T_WHILE: {
    //        t = StmtNodeType::STMT_WHILE;
    //        parseNext();
    //        ExprNode* expr = parseExpr();
    //        v = expr;
    //        b = parseNode().get();
    //        parseNext();
    //        //return node;
    //    }
    //    case TokenType::T_OPENBRACE: {
    //        t = StmtNodeType::STMT_SCOPE;
    //        parseNext();
    //        while(m_next.type != T_CLOSEBRACE){
    //            s.push_back(parseNode().get());
    //            parseNext();
    //        }
    //        //return node;
    //    }
    //    default: {
    //        ExprNode* expr = parseExpr();
    //        t = StmtNodeType::STMT_EXPR;
    //        v = expr;
    //        //return node;
    //    }
    //}
    //return node;

    
}

StmtNodeType Parser::TokenTypeToStmtType(TokenType& t)
{
    switch (t)
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