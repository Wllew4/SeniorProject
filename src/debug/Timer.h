#pragma once
#include <chrono>
#include "debug/Log.h"

class Debug::Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_endTimePoint;

	bool b_Print;
	std::string m_Id;

public:
	Timer(std::string id, bool print);

	~Timer();
};