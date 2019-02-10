#pragma once

#include <array>

#include "Settings.h"


class Map
{
private:
	std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y> m_Data = {};

public:
	Map();
	Map(const char *filepath);

	void load(const char *filepath);
};
