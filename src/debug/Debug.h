#pragma once

#include "ast/lexing/Token.h"
#include "debug/Log.h"
#include <chrono>

extern bool options[4];


namespace Debug
{
	
	void parseArgs(int argc, char** argv);

	void callbackNewToken(Token& t);
	
	//Move into separate file
	class Timer
	{
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_endTimePoint;
			
			bool b_Print;
			std::string m_Id;
		
		public:
			Timer(std::string id = "", bool print = true) : m_Id(id), b_Print(print)
			{
				m_startTimePoint = std::chrono::high_resolution_clock::now();
			}
			
			~Timer()
			{
				m_endTimePoint = std::chrono::high_resolution_clock::now();
				
				auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_startTimePoint).time_since_epoch().count();
				auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(m_endTimePoint).time_since_epoch().count();
				
				double duration = end - start;
				
				Print << "Timer " << m_Id << " completed in " << duration << "ms\n";
			}
	};
}