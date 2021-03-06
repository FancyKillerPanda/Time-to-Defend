#pragma once

#include "pch.h"

#include "Application.h"

#include "Settings.h"
#include "utils/Position.h"
#include "gfx/Texture.h"
#include "entities/Tower.h"


class Map
{
private:
	static Application* s_Game;

	// The cell data
	std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y> m_Data = {};

	// A vector of where possible spawn coordinates are
	std::vector<Position> m_SpawnCoords = {};
	// A vector of where path coordinates are
	std::vector<Position> m_PathCoords = {};
	// A vector of the coordinates of the top left cell of each tower
	std::vector<Position> m_TowerCoords = {};

	// The texture for the grass
	Texture m_GrassTexture;
	Texture m_TrackTexture;

	// Whether the map is loaded
	bool m_Loaded = false;

	// The number of waves to spawn in the map
	unsigned int m_NumberOfWavesToSpawn;

	Tower* m_TowerToDraw = nullptr;

	const char* m_Filepath;

public:
	Map() = default;
	Map(Application* const game, const char* filepath, bool editing = false);
	~Map();

	void load(Application* const game, const char* filepath, bool editing = false);
	void draw(bool drawTowers = false);

	// Adds necessary information such as enemy spawn points
	void convertToPlayableFormat();

	// Checks if the map is empty
	bool isEmpty();

	inline const std::vector<Position>& getSpawnCoords() const { return m_SpawnCoords; }
	inline std::vector<Position>& getPathCoords() { return m_PathCoords; }
	inline std::vector<Position>& getTowerCoords() { return m_TowerCoords; }
	inline const std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y>& getCoords() const { return m_Data; }
	inline std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y>& getCoords() { return m_Data; }
	inline bool getLoaded() { return m_Loaded; }
	inline unsigned int getNumberOfWavesToSpawn() { return m_NumberOfWavesToSpawn; }
};
