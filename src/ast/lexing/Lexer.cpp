#include "ast/lexing/Lexer.h"
#include "ast/lexing/Token.h"

#include <string.h>
#include <ctype.h>
#include <iostream>
#include <string>

int g_line = 1;

void Lexer::Init(char* _file)
{
    g_line = 1;
    m_position = _file;
}

std::string Lexer::GetLine()
{
    return std::to_string(g_line);
}

Token Lexer::GetNextToken()
{
    while(true)
    {
        switch(*m_position)
        {
            case ' ':
            case '\r':
            case '\t':
                m_position++;
                break;
            case '\n':
                m_position++;
                g_line++;
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
            case '<':
                m_position++;
                return { TokenType::T_LESSTHAN, "<" };
            case '>':
                m_position++;
                return { TokenType::T_GREATERTHAN, ">" };
            case '/':
                if(*(m_position + 1) == '/'){
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
                m_position++;
                return { TokenType::T_STRING, std::string(start, start + length) };
                }
            
            default:

                if(isalpha(*m_position))
                {
                    char* start = m_position;
                    int length = 0;
                    m_position++;
                    while(isalpha(*m_position))
                    {
                        length++;
                        m_position++;
                    }
                    length++;
                    std::string value = std::string(start, start + length);
                    if(value == "println")
                        return { TokenType::T_PRINTLN, value };
                    if(value == "print")
                        return { TokenType::T_PRINT, value };
                    if(value == "num")
                        return { TokenType::T_NUMDECL, value };
                    if(value == "string")
                        return { TokenType::T_STRINGDECL, value };
                    if(value == "if")
                        return { TokenType::T_IF, value };
                    if(value == "else")
                        return { TokenType::T_ELSE, value };
                    if(value == "while")
                        return { TokenType::T_WHILE, value };
                    else
                        return { TokenType::T_ID, value };
                }
                if(isdigit(*m_position))
                {
                    char* start = m_position;
                    int length = 0;
                    m_position++;
                    while(isdigit(*m_position))
                    {
                        length++;
                        m_position++;
                    }
                    length++;
                    return { TokenType::T_NUM, std::string(start, start + length) };
                }
        }
    }
}