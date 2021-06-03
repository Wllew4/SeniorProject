#include "debug/Callback.h"

#include "debug/Log.h"

void Debug::Callback::LoadFile(const char* _fileContents)
{
	if (Debug::GetOption(0))
		Debug::Log::Print() << "Debug: Echo file:\n" << _fileContents << '\n';
}

void Debug::Callback::NewToken(Token& _token)
{
	if (Debug::GetOption(1))
		Debug::Log::Print() << _token.ToString() << '\n';
}