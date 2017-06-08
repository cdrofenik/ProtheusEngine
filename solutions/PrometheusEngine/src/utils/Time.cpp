#include "Time.h"

double Time::m_delta = 0;

void Time::setDelta(double value)
{
	m_delta = value;
}

double Time::getDelta()
{
	return m_delta;
}

std::chrono::time_point<std::chrono::steady_clock> Time::GetTime()
{
	return std::chrono::high_resolution_clock::now();
}


