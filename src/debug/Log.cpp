#include "debug/Log.h"
#include "ast/lexing/Lexer.h"

const char* primitivetypes[] = {
    "num",
    "string",
    "bool"
};

Debug::Log logInstance;

std::string& Debug::Log::getPrefix()
{
    return prefix;
}

Debug::Log& Debug::Log::UnhandledException(int code)
{
	return Print << "Unhandled Exception " << code << " on line " << Lexer::getLine() << ": ";
}

Debug::Log& Debug::Log::Crash(int code)
{
    return Print << "Crash " << code << " on line " << Lexer::getLine() << ": ";
}