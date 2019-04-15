#pragma once

#include "pch.h"

#include "Application.h"

#include "Settings.h"
#include "utils/Position.h"
#include "gfx/Texture.h"


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

#ifdef _DEBUG
	const char* m_Filepath;
#endif

public:
	Map() = default;
	Map(Application* const game, const char* filepath);
	~Map();

	void load(Application* const game, const char* filepath);
	void draw();

	// Adds necessary information such as enemy spawn points
	void convertToPlayableFormat();

	inline const std::vector<Position>& getSpawnCoords() const { return m_SpawnCoords; }
	inline const std::vector<Position>& getPathCoords() const { return m_PathCoords; }
	inline const std::vector<Position>& getTowerCoords() const { return m_TowerCoords; }
	inline const std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y>& getCoords() const { return m_Data; }
	inline std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y>& getCoords() { return m_Data; }
	inline bool getLoaded() { return m_Loaded; }
};
