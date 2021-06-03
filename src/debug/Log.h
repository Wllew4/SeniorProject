#pragma once

#include "object/Primitive.h"
#include "debug/Debug.h"

#include <iostream>

class Debug::Log
{
public:
	Log(const Log&) = delete;
	static Log& GetInstance();

	template<typename T>
	inline Log& operator<<(T _t)
	{
		std::cout << _t << std::flush;
		return *this;
	}

	static Log& Print();
	static Log& UnhandledException(int _errorCode);
	static Log& Crash(int _errorCode);

private:
	Log() {}
	std::string m_prefix = "JANELLE:\t";
	std::string& GetPrefix();
};