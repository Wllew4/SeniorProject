#pragma once

#include "ast/lexing/Token.h"

class Lexer
{
	private:
		char* m_position;

	public:
		void Init(char* file);
	    Token getNextToken();
	    static std::string getLine();
};