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
    static const char* tokentypes[] = {"Var", "String", "Number", "Print", "Printline", "EOF"};
    Log::Print(6,"TOKEN:\t", "Type: ", tokentypes[m_next.type], "\t\t", m_next.value, "\n");
}

void Parser::parse(){
    while(m_next.type != Type::T_EOF){
        parseNext();
    }
}