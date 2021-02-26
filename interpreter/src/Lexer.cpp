#include <string.h>
#include <ctype.h>

#include "Lexer.h"
#include "Token.h"

void Lexer::Init(char* file){
    m_line = 1;
    m_position = file;
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
                m_line++;
                break;
            case '/':
                if(*m_position + 1 == '/') while(*m_position != '\n') m_position++;
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
                    m_position++;
                    char* value;
                    while(isalpha(*m_position)){
                        m_position++;
                    }
                    size_t length = sizeof(char) * (m_position - start);
                    memcpy(value, start, length);
                    value[length] = '\0';
                    if(strcmp(value, "println") == 0){
                        return { TokenType::T_PRINTLN, value };
                    }
                    if(strcmp(value, "print") == 0){
                        return { TokenType::T_PRINT, value };
                    }
                }
        }
    }
}