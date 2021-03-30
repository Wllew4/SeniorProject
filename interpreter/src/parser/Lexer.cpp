#include <string.h>
#include <ctype.h>

#include "parser/Lexer.h"
#include "parser/Token.h"

#include <iostream>
#include <string>

char* m_position;
int m_line = 1;

void Lexer::Init(char* file){
    m_line = 1;
    m_position = file;
}

const char* Lexer::getLine(){
    return std::to_string(m_line).c_str();
}

Token Lexer::getNextToken(){
    while(true){
        switch(*m_position){
            case ' ':
            case '\r':
            case '\t':
                m_position++;
                break;
            case '\n':
                m_position++;
                m_line++;
                break;
            case '+':
                m_position++;
                return { TokenType::T_PLUS, "+" };
            case '-':
                m_position++;
                return { TokenType::T_MINUS, "-" };
            case '*':
                m_position++;
                return { TokenType::T_MULT, "*" };
            case '%':
                m_position++;
                return { TokenType::T_MODULUS, "%" };
            case '{':
                m_position++;
                return { TokenType::T_OPENBRACE, "{" };
            case '}':
                m_position++;
                return { TokenType::T_CLOSEBRACE, "}" };
            case ';':
                m_position++;
                return { TokenType::T_SEMICOLON, ";" };
            case '=':
                m_position++;
                return { TokenType::T_EQ, "=" };
            case '/':
                if(*m_position + 1 == '/'){
                    while(*m_position != '\n') m_position++;
                }
                else{
                    m_position++;
                    return { TokenType::T_DIV, "/" };
                }
                break;
            
            case '\0':
                return { TokenType::T_EOF, "End of file" };
            case '\"':
                {
                char* start = m_position + 1;
                int length = 0;
                m_position++;
                while(*m_position != '\"'){
                    length++;
                    m_position++;
                }
                char* value = new char[length];
                memcpy(value, start, length);
                value[length] = '\0';
                m_position++;
                return { TokenType::T_STRING, value };
                }
            
            default:

                if(isalpha(*m_position)){
                    char* start = m_position;
                    int length = 0;
                    m_position++;
                    while(isalpha(*m_position)){
                        length++;
                        m_position++;
                    }
                    length++;
                    char* value = new char[length];
                    memcpy(value, start, length);
                    value[length] = '\0';
                    if(strcmp(value, "println") == 0){
                        m_position++;
                        return { TokenType::T_PRINTLN, value };
                    }
                    if(strcmp(value, "print") == 0){
                        m_position++;
                        return { TokenType::T_PRINT, value };
                    }
                    if(strcmp(value, "num") == 0){
                        m_position++;
                        return { TokenType::T_NUMDECL, value };
                    }
                    if(strcmp(value, "string") == 0){
                        m_position++;
                        return { TokenType::T_STRINGDECL, value };
                    }
                    if(strcmp(value, "if") == 0){
                        m_position++;
                        return { TokenType::T_IF, value };
                    }
                    else {
                        return { TokenType::T_ID, value };
                    }
                }
                if(isdigit(*m_position)){
                    char* start = m_position;
                    int length = 0;
                    m_position++;
                    while(isdigit(*m_position)){
                        length++;
                        m_position++;
                    }
                    length++;
                    char* value = new char[length];
                    memcpy(value, start, length);
                    value[length] = '\0';
                    return { TokenType::T_NUM, value };
                }
        }
    }
}