#pragma once

#include "pch.h"

#include "Log.h"


class Random
{
private:
	static std::mt19937 m_Rng;

public:
	static void init();

	static int randint(int min, int max);
	static double randdouble(double min, double max);

};
