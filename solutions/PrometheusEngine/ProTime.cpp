#include "ProTime.h"

double ProTime::m_delta = 0;

void ProTime::setDelta(double value)
{
	m_delta = value;
}

double ProTime::getDelta()
{
	return m_delta;
}

std::chrono::time_point<std::chrono::steady_clock> ProTime::GetTime()
{
	return std::chrono::high_resolution_clock::now();
}


