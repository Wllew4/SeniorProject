#pragma once

#include "debug/Debug.h"
#include "ast/lexing/Token.h"

class Debug::Callback
{
public:
	static void LoadFile(const char* fileContents);
	static void NewToken(Token& t);
};