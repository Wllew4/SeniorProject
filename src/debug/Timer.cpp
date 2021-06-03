#include "debug/Timer.h"

Debug::Timer::Timer(std::string _id = "")
	: m_Id(_id)
{
	m_startTimePoint = std::chrono::high_resolution_clock::now();
}

Debug::Timer::~Timer()
{
	m_endTimePoint = std::chrono::high_resolution_clock::now();

	long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_startTimePoint).time_since_epoch().count();
	long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(m_endTimePoint).time_since_epoch().count();

	long long duration = end - start;

	Debug::Log::Print() << "Timer \"" << m_Id << "\" completed in " << duration << "ms\n";
}