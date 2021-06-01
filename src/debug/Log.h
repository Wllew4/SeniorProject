#pragma once

#include "object/Primitive.h"
#include "debug/Debug.h"
#include <iostream>
#define Print (logInstance << logInstance.getPrefix())

class Debug::Log
{
	private:
		std::string prefix = "JANELLE:\t";
		
	public:
		template<typename T>
		inline Log& operator<<(T t)
		{
			std::cout << t << std::flush;
			return *this;
		}
			
		std::string& getPrefix();
			
		static Log& UnhandledException(int code);
		static Log& Crash(int code);
};

extern Debug::Log logInstance;