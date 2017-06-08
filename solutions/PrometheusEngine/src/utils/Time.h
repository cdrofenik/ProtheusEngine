#pragma once

#include <chrono>

#define SECOND 1000000000.0

class Time
{
public:
	static void setDelta(double value);
	static double getDelta();

	static std::chrono::time_point<std::chrono::steady_clock> GetTime();

private:
	static double m_delta;
};

