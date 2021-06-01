#pragma once

#include <string>
#include <string.h>

enum TokenType
{
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



struct Token
{
    TokenType type;
    std::string value;
    
    std::string toString()
    {
    	constexpr const char* tokentypes[] = {
		    "StrDecl",	    "NumDecl",
		    "StrLit",       "NumLit",
		    "ID",           "Print",
		    "Println",      "EQ",
		    "Plus",         "Minus",
		    "Mult",         "Div",
		    "Modulus",      "If",
		    "Else",         "While",
		    "LThan",        "GThan",
		    "OpBrace",      "ClBrace",
		    "Semicolon",    "EOF"
		};
		
    	std::string out = "TOKEN:\tType: ";
    	out += tokentypes[type];
    	out += strlen(tokentypes[type]) < 6 ?
    		"\t\t" : "\t";
    	out += "Value: ";
    	out += value;
    	  	
    	return out;
    }
};