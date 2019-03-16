#include "pch.h"

#include "Map.h"

#include "utils/Log.h"
#include "Game.h"
#include "Settings.h"


Game* Map::s_Game = nullptr;


Map::Map()
{
}

Map::Map(Game* const game, const char* filepath)
{
	load(game, filepath);
}

Map::~Map()
{
	LOG_INFO("Destroyed map (filepath: {0}).", m_Filepath);
}


void Map::load(Game* const game, const char* filepath)
{
#ifdef _DEBUG
	m_Filepath = filepath;
#endif

	// Sets the game instance
	s_Game = game;

	// Loads the textures
	m_GrassTexture.load("res/txrs/Grass.png", s_Game->getRenderer());
	m_TrackTexture.load("res/txrs/Track.jpg", s_Game->getRenderer());

	// Sets the width and height to the cell size
	m_GrassTexture.setRect(0, 0, CELL_SIZE, CELL_SIZE);
	m_TrackTexture.setRect(0, 0, CELL_SIZE, CELL_SIZE);

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
			if (m_Data[row][col] == 'P' || m_Data[row][col] == 'S')
			{
				// Sets the position of the cell
				m_TrackTexture.setRect(col * CELL_SIZE, row * CELL_SIZE);

				// Draws the texture
				SDL_RenderCopy(s_Game->getRenderer(), m_TrackTexture.getTexture(), nullptr, &m_TrackTexture.getRect());
			}

			else
			{
				// Sets the position of the cell
				m_GrassTexture.setRect(col * CELL_SIZE, row * CELL_SIZE);

				// Draws the texture
				SDL_RenderCopy(s_Game->getRenderer(), m_GrassTexture.getTexture(), nullptr, &m_GrassTexture.getRect());
			}
		}
	}
}
