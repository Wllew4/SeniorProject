#include "debug/Log.h"

#include "ast/lexing/Lexer.h"

Debug::Log& Debug::Log::GetInstance()
{
    static Log instance;
    return instance;
}

std::string& Debug::Log::GetPrefix()
{
    return m_prefix;
}

Debug::Log& Debug::Log::Print()
{
    return GetInstance() << GetInstance().GetPrefix();
}

Debug::Log& Debug::Log::UnhandledException(int _errorCode)
{
	return Print() << "Unhandled Exception " << _errorCode << " on line " << Lexer::GetLine() << ": ";
}

Debug::Log& Debug::Log::Crash(int _errorCode)
{
    return Print() << "Crash " << _errorCode << " on line " << Lexer::GetLine() << ": ";
}