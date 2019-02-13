#pragma once

#include "pch.h"

#include "Settings.h"


class Map
{
private:
	std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y> m_Data = {};
	std::vector<std::pair<unsigned int, unsigned int>> m_SpawnCoords = {};
	std::vector<std::pair<unsigned int, unsigned int>> m_PathCoords = {};
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
	inline const std::vector<std::pair<unsigned int, unsigned int>>& getSpawnCoords() const { return m_SpawnCoords; }
	inline const std::vector<std::pair<unsigned int, unsigned int>>& getPathCoords() const { return m_PathCoords; }
	inline const std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y>& getCoords() const { return m_Data; }
};
