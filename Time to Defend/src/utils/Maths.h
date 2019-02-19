#pragma once

#define _USE_MATH_DEFINES
#include <cmath>


inline constexpr double getRadians(double degrees)
{
	return degrees * (M_PI / 180);
}
