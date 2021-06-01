#pragma once

#include "object/Primitive.h"
#include <iostream>
#define Print (logInstance << logInstance.getPrefix())

namespace Debug
{
	class Log
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
			
			inline std::string& getPrefix()
			{
				return prefix;
			}
			
			static Log& UnhandledException(int code);
	};
}

extern Debug::Log logInstance;

// namespace Log {
//     void Error(int size, ...);
//     void Print(int size, ...);

//     void PrintToken(int type, const char* val);
//     void PrintStatement(int type);
    
//     void UnexpectedToken(const char* value);
//     void MissingToken(int x);
//     void UnrecognizedIdentifier(const char* value);
//     void RedefinedIdentifier(const char* value);
//     void CannotImplicitlyConvert(const TYPE_PRIMITIVE& l, const TYPE_PRIMITIVE& r);
// } 