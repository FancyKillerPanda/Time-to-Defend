#pragma once

#include "pch.h"

#include "Settings.h"
#include "utils/Position.h"
#include "gfx/Texture.h"


class Game;


class Map
{
private:
	static Game* s_Game;

	// The cell data
	std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y> m_Data = {};

	// A vector of where possible spawn coordinates are
	std::vector<Position> m_SpawnCoords = {};
	// A vector of where path coordinates are
	std::vector<Position> m_PathCoords = {};

	// The texture for the grass
	Texture m_GrassTexture;
	Texture m_TrackTexture;

#ifdef _DEBUG
	const char* m_Filepath;
#endif

public:
	Map();
	Map(Game* const game, const char* filepath);
	~Map();

	void load(Game* const game, const char* filepath);
	void draw(SDL_Renderer* renderer);
	inline const std::vector<Position>& getSpawnCoords() const { return m_SpawnCoords; }
	inline const std::vector<Position>& getPathCoords() const { return m_PathCoords; }
	inline const std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y>& getCoords() const { return m_Data; }
};
