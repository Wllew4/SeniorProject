#include "Parser.h"
#include "Lexer.h"
#include "util/Log.h"
#include "config.h"

#include <iostream>

void Parser::parseNext(){
    m_current = m_next;
    m_next = Lexer::getNextToken();
    if(options[1]){
        printToken();
        fflush(stdout);
    }
}

void Parser::printToken(){
    static const char* tokentypes[] = {"Var", "String", "Number", "Print", "Printline", "EQ", "Plus", "Minus", "Semicolon", "EOF"};
    Log::Print(6,"TOKEN:\t", "Type: ", tokentypes[m_next.type], "\t\t", m_next.value, "\n");
}

void Parser::parse(){
    while(m_next.type != TokenType::T_EOF){
        parseNext();
        parseNode();
    }
    exit(0);
}

ExprNode* Parser::parseAtomicExpr(){
    parseNext();
    switch(m_current.type){
        
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
            //std::cout << "returns here\n";
            Log::UnexpectedToken(Lexer::m_line, m_next.value);
            exit(0);
    }
}

ExprNode* Parser::parseUnopExpr(){
    ExprNode* expr = NULL;
    // while(m_next.type == T_MINUS){
    //     parseNext();
    //     ExprNode* oldexpr = expr;
    //     expr->type = ExprNodeType::EXPR_UNOP;
    //     expr->val.unop = {oldexpr, '-'};
    // }
    if(expr == NULL) expr = parseAtomicExpr();
    else {
        ExprNode* traversal = expr;
        while(traversal->val.unop.left != NULL){
            traversal = traversal->val.unop.left;
        }
        //traversal->val.unop.left = parseAtomicExpr();
    }
    //std::cout << "returns here";
    return expr;
}

ExprNode* Parser::parseBinopExpr(){
    ExprNode* expr = parseUnopExpr();
    while(m_next.type == T_PLUS || T_MINUS){
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
        expr->type = ExprNodeType::EXPR_BINOP;
        expr->val.binop = {left, right, '='};
    }
    return expr;
}

StmtNode* Parser::parseNode(){
    StmtNode* node;

    switch (m_next.type){
        case TokenType::T_PRINTLN: {
            node->type = StmtNodeType::STMT_PRINTLN;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_next.type == TokenType::T_SEMICOLON){
                node->type = StmtNodeType::STMT_PRINTLN;
                node->val.print.expr_string = expr;
            }
            else Log::Error(1, "nope!");

            return node;
        }
            
            // if(m_next.type == TokenType::T_STRING || m_next.type == TokenType::T_NUM){
            //     // printf("%s\n", m_next.value);
            // }
            // else {
            //     Log::UnexpectedToken(Lexer::m_line, m_next.value);
            // }
        case TokenType::T_PRINT: {
            node->type = StmtNodeType::STMT_PRINT;
            parseNext();
            ExprNode* expr = parseExpr();
            if(m_current.type == TokenType::T_SEMICOLON){
                std::cout << "yeah!";
                node->type = StmtNodeType::STMT_PRINT;
                node->val.print.expr_string = expr;
            }
            else Log::Error(1, "nope!");

            return node;
        }
            // if(m_next.type == TokenType::T_STRING || m_next.type == TokenType::T_NUM){
            //     // printf("%s", m_next.value);
            // }
            // else {
            //     Log::UnexpectedToken(Lexer::m_line, m_next.value);
            // }
            break;
        default: {
            ExprNode* expr = parseExpr();
            node->type = StmtNodeType::EXPR_STMT;
            node->val.exprstmt.expr = expr;
            return node;
        }
            
    }
    return node;
}