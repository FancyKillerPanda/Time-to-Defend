#include "pch.h"

#include "Map.h"

#include "utils/Log.h"


Map::Map()
{
	m_CellRect.w = CELL_SIZE;
	m_CellRect.h = CELL_SIZE;
}

Map::Map(const char* filepath)
{
	m_CellRect.w = CELL_SIZE;
	m_CellRect.h = CELL_SIZE;
	load(filepath);
}

Map::~Map()
{
	LOG_INFO("Destroyed map (filepath: {0}).", m_Filepath);
}


void Map::load(const char* filepath)
{
#ifdef _DEBUG
	m_Filepath = filepath;
#endif

	int row = 0;
	int col = 0;

	// Opens the file to read it
	std::ifstream mapFile(filepath);

	// Could not open file
	if (!mapFile)
	{
		LOG_FATAL("Failed to load map (filepath: {0}).", filepath);
		return;
	}

	char c;

	// Does not skip whitespace
	mapFile >> std::noskipws;

	// Runs through each character
	while (mapFile >> c)
	{
		switch (c)
		{
		case '\n':
			row += 1;
			col = 0;

			break;

		case 'S':
			m_SpawnCoords.emplace_back(row, col);
			// No break here, spawn coordinates are always also path coordinates

		case 'P':
			m_PathCoords.emplace_back(row, col);
			// No break here, path coordinates also need to be in the final data

		default:
			m_Data[row][col] = c;
			col += 1;

			break;
		}
	}

	LOG_INFO("Created map (filepath: {0}).", filepath);
}

void Map::draw(SDL_Renderer* renderer)
{
	for (int row = 0; row < NUM_OF_CELLS_Y; row++)
	{
		for (int col = 0; col < NUM_OF_CELLS_X; col++)
		{
			// Sets the position of the cell
			m_CellRect.x = col * CELL_SIZE;
			m_CellRect.y = row * CELL_SIZE;

			// Sets the appropriate drawing colour
			if (m_Data[row][col] == '.')
			{
				SDL_SetRenderDrawColor(renderer, 0, 127, 0, 255);
			}

			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			}

			// Draws the rectangle
			SDL_RenderFillRect(renderer, &m_CellRect);
		}
	}
}
