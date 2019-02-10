#include "Map.h"

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
}
