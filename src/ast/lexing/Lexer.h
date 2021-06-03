#pragma once

#include "ast/lexing/Token.h"

class Lexer
{
public:
	void Init(char* _file);
	Token GetNextToken();
	static std::string GetLine();

private:
	char* m_position;
};