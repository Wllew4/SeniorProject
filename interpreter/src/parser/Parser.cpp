#include "parser/Parser.h"
#include "parser/Lexer.h"
#include "util/Log.h"
#include "util/File.h"
#include "config.h"
#include "Exec.h"

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
            numexpr->val.num.value = atof(m_current.value);
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
    while(m_next.type == T_PLUS || m_next.type == T_MINUS){
        char type = m_next.type == T_PLUS ? '+' : '-';
        parseNext();
        ExprNode* left = expr;
        ExprNode* right = parseUnopExpr();
        expr->type = ExprNodeType::EXPR_BINOP;
        expr->val.binop = {left, right, type};
    }
    return expr;
}

ExprNode* Parser::parseExpr(){
    ExprNode* expr = parseBinopExpr();
    if(m_next.type == T_EQ){
        parseNext();
        ExprNode* left = expr;
        ExprNode* right = parseExpr();
        expr = new ExprNode;
        expr->type = ExprNodeType::EXPR_BINOP;
        expr->val.binop = {left, right, '='};
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
                node->val.print.expr_string = expr;
            }
            else Log::MissingSemicolon();
            return node;
        }
        case TokenType::T_PRINT: {
            node->type = StmtNodeType::STMT_PRINT;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_SEMICOLON){
                node->val.print.expr_string = expr;
            }
            else Log::MissingSemicolon();
            return node;
        }
        case TokenType::T_NUMDECL: {
            node->type = StmtNodeType::STMT_NUMDECL;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_SEMICOLON){
                node->val.numassign.expr = expr;
            }
            else Log::MissingSemicolon();
            return node;
        }
        case TokenType::T_STRINGDECL: {
            node->type = StmtNodeType::STMT_STRINGDECL;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_SEMICOLON){
                node->val.stringassign.expr = expr;
            }
            else Log::MissingSemicolon();
            return node;
        }
        default: {
            ExprNode* expr = parseExpr();
            node->type = StmtNodeType::STMT_EXPR;
            node->val.exprstmt.expr = expr;
            return node;
        }
    }
    return node;
}