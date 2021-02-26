#pragma once

enum Type {
    T_VAR,
    T_STRING,
    T_NUM,
    T_PRINT,
    T_PRINTLN,
    T_EOF
};

struct Token {
    Type type;
    const char* value;
};