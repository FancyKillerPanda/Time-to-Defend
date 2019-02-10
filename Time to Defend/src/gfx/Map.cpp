#include "Map.h"

#include <iostream>
#include <fstream>

#include "utils/Log.h"


Map::Map()
{
}

Map::Map(const char *filepath)
{
	load(filepath);
}


void Map::load(const char *filepath)
{
	unsigned int row = 0;
	unsigned int col = 0;

	std::ifstream mapFile(filepath);

	if (!mapFile)
	{
		LOG_FATAL("Failed to load map (filepath: {0}).", filepath);
		return;
	}

	char c;

	mapFile >> std::noskipws;

	while (mapFile >> c)
	{
		switch (c)
		{
		case '\n':
			row += 1;
			col = 0;

			break;

		default:
			m_Data[row][col] = c;
			col += 1;

			break;
		}
	}

	LOG_INFO("Created map (filepath: {0}).", filepath);

	for (unsigned int ro = 0; ro < NUM_OF_CELLS_Y; ro++)
	{
		for (unsigned int co = 0; co < NUM_OF_CELLS_X; co++)
		{
			std::cout << m_Data[ro][co];
		}

		std::cout << std::endl;
	}
}
