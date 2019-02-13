#pragma once

#include "pch.h"

#include "Settings.h"
#include "utils/Position.h"


class Map
{
private:
	std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y> m_Data = {};
	std::vector<Position> m_SpawnCoords = {};
	std::vector<Position> m_PathCoords = {};
	SDL_Rect m_CellRect;

#ifdef _DEBUG
	const char* m_Filepath;
#endif

public:
	Map();
	Map(const char* filepath);
	~Map();

	void load(const char* filepath);
	void draw(SDL_Renderer* renderer);
	inline const std::vector<Position>& getSpawnCoords() const { return m_SpawnCoords; }
	inline const std::vector<Position>& getPathCoords() const { return m_PathCoords; }
	inline const std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y>& getCoords() const { return m_Data; }
};
