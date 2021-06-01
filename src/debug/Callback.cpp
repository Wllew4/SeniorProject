#include "debug/Callback.h"
#include "debug/Log.h"

void Debug::Callback::LoadFile(const char* fileContents)
{
	if (Debug::GetOption(0))
		Print << "Debug: Echo file:\n" << fileContents << '\n';
}

void Debug::Callback::NewToken(Token& t)
{
	if (Debug::GetOption(3))
		Print << t.toString() << '\n';
}