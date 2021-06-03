#pragma once

#include "ast/lexing/Token.h"
#include "debug/Debug.h"

class Debug::Callback
{
public:
	static void LoadFile(const char* _fileContents);
	static void NewToken(Token& _token);
};