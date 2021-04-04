#include "parser/Parser.h"
#include "parser/Lexer.h"
#include "executor/Exec.h"
#include "util/Log.h"
#include "util/File.h"
#include "util/Debug.h"

#include <iostream>

void Parser::parseNext(){
    m_current = m_next;
    m_next = Lexer::getNextToken();
    if(options[1]){
        Log::PrintToken(m_next.type, m_next.value);
    }
}

void Parser::parse(char* file){
    Lexer::Init(File::readFile(file));
    parseNext();
    while(m_next.type != TokenType::T_EOF){
        StmtNode* statement = parseNode();
        Exec(statement);
        parseNext();
    }
    exit(0);
}

ExprNode* Parser::parseAtomicExpr(){
    parseNext();
    switch(m_current.type){
        case TokenType::T_ID: {
            ExprNode* idexpr = new ExprNode;
            idexpr->type = ExprNodeType::EXPR_ID;
            idexpr->val.id.name = m_current.value;
            return idexpr;
        }
        case TokenType::T_NUM: {
            ExprNode* numexpr = new ExprNode;
            numexpr->type = ExprNodeType::EXPR_NUM;
            numexpr->val.num.value = new double(atof(m_current.value));
            return numexpr;
        }
        case TokenType::T_STRING: {
            ExprNode* stringexpr = new ExprNode;
            stringexpr->type = ExprNodeType::EXPR_STRING;
            stringexpr->val.string.value = m_current.value;
            return stringexpr;
        }
        default:
            Log::UnexpectedToken(m_next.value);
            exit(0);
    }
}

ExprNode* Parser::parseUnopExpr(){
    ExprNode* expr = NULL;
    while(m_next.type == T_MINUS){
        parseNext();
        ExprNode* oldexpr = expr;
        expr = new ExprNode;
        expr->type = ExprNodeType::EXPR_UNOP;
        expr->val.unop = {oldexpr, '-'};
    }
    if(expr == NULL) expr = parseAtomicExpr();
    else {
        ExprNode* traversal = expr;
        while(traversal->val.unop.left != NULL){
            traversal = traversal->val.unop.left;
        }
        traversal->val.unop.left = parseAtomicExpr();
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
        expr = new ExprNode;
        expr->type = ExprNodeType::EXPR_BINOP;
        expr->val.binop = {left, right, type};
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
        expr = new ExprNode;
        expr->type = ExprNodeType::EXPR_BINOP;
        expr->val.binop = {left, right, type};
    }
    return expr;
}

StmtNode* Parser::parseNode(){
    StmtNode* node = new StmtNode;

    switch (m_next.type){
        case TokenType::T_PRINTLN: {
            node->type = StmtNodeType::STMT_PRINTLN;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_SEMICOLON){
                node->val = expr;
            }
            else Log::MissingToken(TokenType::T_SEMICOLON);
            return node;
        }
        case TokenType::T_PRINT: {
            node->type = StmtNodeType::STMT_PRINT;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_SEMICOLON){
                node->val = expr;
            }
            else Log::MissingToken(TokenType::T_SEMICOLON);
            return node;
        }
        case TokenType::T_NUMDECL: {
            node->type = StmtNodeType::STMT_NUMDECL;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_SEMICOLON){
                node->val = expr;
            }
            else Log::MissingToken(TokenType::T_SEMICOLON);
            return node;
        }
        case TokenType::T_STRINGDECL: {
            node->type = StmtNodeType::STMT_STRINGDECL;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_SEMICOLON){
                node->val = expr;
            }
            else Log::MissingToken(TokenType::T_SEMICOLON);
            return node;
        }
        case TokenType::T_IF: {
            node->type = StmtNodeType::STMT_CONDITIONAL;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_OPENBRACE){
                node->val = expr;
            }
            else Log::MissingToken(TokenType::T_OPENBRACE);
            parseNext();
            while(m_next.type != T_CLOSEBRACE){
                node->body.push_back(parseNode());
                parseNext();
            }
            parseNext();
            if(m_next.type == T_ELSE){
                parseNext();
                parseNext();
                while(m_next.type != T_CLOSEBRACE){
                    node->elsebody.push_back(parseNode());
                    parseNext();
                }
            }
            return node;
        }
        case TokenType::T_WHILE: {
            node->type = StmtNodeType::STMT_WHILE;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_OPENBRACE){
                node->val = expr;
            }
            else Log::MissingToken(TokenType::T_OPENBRACE);
            parseNext();
            while(m_next.type != T_CLOSEBRACE){
                node->body.push_back(parseNode());
                parseNext();
            }
            return node;
        }
        default: {
            ExprNode* expr = parseExpr();
            node->type = StmtNodeType::STMT_EXPR;
            node->val = expr;
            return node;
        }
    }
    return node;
}