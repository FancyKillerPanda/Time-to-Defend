#pragma once

#include "pch.h"


// Converts degrees to radians
inline constexpr double getRadians(double degrees)
{
	return degrees * (M_PI / 180);
}

// Converts radians to degrees
inline constexpr double getDegrees(double radians)
{
	return radians * (180 / M_PI);
}
