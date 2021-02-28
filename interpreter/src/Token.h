#pragma once

enum TokenType {
    T_VAR,
    T_STRING,
    T_NUM,
    T_PRINT,
    T_PRINTLN,
    T_SEMICOLON,
    T_EOF
};

struct Token {
    TokenType type;
    const char* value;
};