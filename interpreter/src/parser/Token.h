#pragma once

enum TokenType {
    T_STRINGDECL,
    T_NUMDECL,
    T_STRING,
    T_NUM,
    T_ID,
    T_PRINT,
    T_PRINTLN,
    T_EQ,
    T_PLUS,
    T_MINUS,
    T_MULT,
    T_DIV,
    T_MODULUS,
    T_IF,
    T_ELSE,
    T_WHILE,
    T_LESSTHAN,
    T_GREATERTHAN,
    T_OPENBRACE,
    T_CLOSEBRACE,
    T_SEMICOLON,
    T_EOF
};

struct Token {
    TokenType type;
    const char* value;
};