#include "debug/Timer.h"

Debug::Timer::Timer(std::string id = "", bool print = true)
	: m_Id(id), b_Print(print)
{
	m_startTimePoint = std::chrono::high_resolution_clock::now();
}

Debug::Timer::~Timer()
{
	m_endTimePoint = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_endTimePoint).time_since_epoch().count();

	long long duration = end - start;

	Print << "Timer " << m_Id << " completed in " << duration << "ms\n";
}