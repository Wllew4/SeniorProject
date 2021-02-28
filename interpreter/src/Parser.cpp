#include "Parser.h"
#include "Lexer.h"
#include "util/Log.h"
#include "config.h"

void Parser::parseNext(){
    m_current = m_next;
    m_next = Lexer::getNextToken();
    if(options[1]){
        printToken();
    }
}

void Parser::printToken(){
    static const char* tokentypes[] = {"Var", "String", "Number", "Print", "Printline", "Semicolon", "EOF"};
    Log::Print(6,"TOKEN:\t", "Type: ", tokentypes[m_next.type], "\t\t", m_next.value, "\n");
}

void Parser::parse(){
    while(m_next.type != TokenType::T_EOF){
        parseCurrentToken();
        parseNext();
    }
    exit(0);
}

void Parser::parseExpression(){
    while(m_next.type != TokenType::T_SEMICOLON){
        // parseCurrentToken();
        parseNext();
    }
}

void Parser::parseCurrentToken(){
    switch (m_current.type){
        case TokenType::T_PRINTLN:
            if(m_next.type == TokenType::T_STRING || m_next.type == TokenType::T_NUM){
                printf("%s\n", m_next.value);
            }
            else {
                Log::UnexpectedToken(Lexer::m_line, m_next.value);
            }
            break;
        case TokenType::T_PRINT:
            if(m_next.type == TokenType::T_STRING || m_next.type == TokenType::T_NUM){
                printf("%s", m_next.value);
            }
            else {
                Log::UnexpectedToken(Lexer::m_line, m_next.value);
            }
            break;
    }
}