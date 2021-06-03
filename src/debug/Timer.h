#pragma once

#include "debug/Log.h"

#include <chrono>

class Debug::Timer
{
public:
	Timer(std::string _id);
	~Timer();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_endTimePoint;

	std::string m_Id;
};