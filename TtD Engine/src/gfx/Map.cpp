#include "pch.h"

#include "Map.h"

#include "utils/Log.h"
#include "Settings.h"


Application* Map::s_Game = nullptr;


Map::Map(Application* const game, const char* filepath, bool editing)
{
	load(game, filepath, editing);
}

Map::~Map()
{
	delete m_TowerToDraw;
	m_TowerToDraw = nullptr;

	LOG_INFO("Destroyed map (filepath: {0}).", m_Filepath);
}


void Map::load(Application* const game, const char* filepath, bool editing)
{
	m_Filepath = filepath;

	// Sets the game instance
	s_Game = game;

	// Loads the textures
	m_GrassTexture.load("res/txrs/Grass.jpg", s_Game->getRenderer());
	m_TrackTexture.load("res/txrs/Track.jpg", s_Game->getRenderer());

	// Creates the tower that will be drawn
	m_TowerToDraw = new Tower(s_Game, Position { 0, 0 });

	// Sets the width and height to the cell size
	m_GrassTexture.setRect(0, 0, CELL_SIZE, CELL_SIZE);
	m_TrackTexture.setRect(0, 0, CELL_SIZE, CELL_SIZE);

	// Empty map
	if (m_Filepath == nullptr)
	{
		// Fills map with '.'
		for (int row = 0; row < NUM_OF_CELLS_Y; row++)
		{
			for (int col = 0; col < NUM_OF_CELLS_X; col++)
			{
				m_Data[row][col] = '.';
			}
		}

		LOG_INFO("Created empty map.");
		return;
	}

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
	std::string numOfWaves;

	// Does not skip whitespace
	mapFile >> std::noskipws;

	// Reads the number of waves to spawn
	if (std::getline(mapFile, numOfWaves))
	{
		try
		{
			m_NumberOfWavesToSpawn = std::stoi(numOfWaves);
		}

		catch (const std::exception&)
		{
			LOG_WARNING("No number of waves to spawn. Defaulting to 2.");
			m_NumberOfWavesToSpawn = 2;

			// Returns to beginning of file
			mapFile.seekg(0, std::ios::beg);
		}
	}

	else
	{
		LOG_ERROR("No map data.");
		return;
	}

	// Runs through each character
	while (mapFile >> c)
	{
		switch (c)
		{
		case '\n':
			row += 1;
			col = 0;

			break;

		case 'T':
			// Top-left tower cell
			m_TowerCoords.emplace_back(row, col);

			// Default case
			m_Data[row][col] = c;
			col += 1;

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

	if (m_TowerCoords.empty() && !editing)
	{
		// Makes sure at least one tower
		m_TowerCoords.emplace_back(0, 0);
	}

	m_Loaded = true;
	LOG_INFO("Created map (filepath: {0}).", filepath);
}

void Map::draw(bool drawTowers)
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

	if (drawTowers)
	{
		for (const Position& position : m_TowerCoords)
		{
			// Sets the position of the tower
			m_TowerToDraw->setPosition(position);

			// Draws the tower
			m_TowerToDraw->draw();
		}
	}
}

void Map::convertToPlayableFormat()
{
	for (int row = 0; row < NUM_OF_CELLS_Y; row++)
	{
		for (int col = 0; col < NUM_OF_CELLS_X; col++)
		{
			char& cell = m_Data[row][col];

			if (cell == 'P')
			{
				int numOfNeighbors = 0;

				for (int rowDiff = -1; rowDiff <= 1; rowDiff++)
				{
					for (int colDiff = -1; colDiff <= 1; colDiff++)
					{
						if (rowDiff == 0 && colDiff == 0)
						{
							continue;
						}

						int newRow = row + rowDiff;
						int newCol = col + colDiff;

						if (newRow < 0 || newRow >= NUM_OF_CELLS_Y || newCol < 0 || newCol >= NUM_OF_CELLS_X)
						{
							continue;
						}

						if (m_Data[newRow][newCol] == 'P' || m_Data[newRow][newCol] == 'S')
						{
							numOfNeighbors += 1;
						}
					}
				}

				if (row == 0 || col == 0 || row == NUM_OF_CELLS_Y - 1 || col == NUM_OF_CELLS_X - 1 || numOfNeighbors == 1)
				{
					cell = 'S';
				}
			}
		}
	}
}

bool Map::isEmpty()
{
	for (int row = 0; row < NUM_OF_CELLS_Y; row++)
	{
		for (int col = 0; col < NUM_OF_CELLS_X; col++)
		{
			if (m_Data[row][col] != '.')
			{
				return false;
			}
		}
	}

	return true;
}
