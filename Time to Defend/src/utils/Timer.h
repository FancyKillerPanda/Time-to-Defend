#pragma once

#include "pch.h"


class Timer
{
	using Clock = std::chrono::high_resolution_clock;

private:
	Clock::time_point m_Start;

public:
	Timer()
	{
		m_Start = Clock::now();
	}

	void reset()
	{
		m_Start = Clock::now();
	}

	double getElapsed()
	{
		std::chrono::duration<double, std::milli> diff = Clock::now() - m_Start;
		return diff.count();
	}
};
