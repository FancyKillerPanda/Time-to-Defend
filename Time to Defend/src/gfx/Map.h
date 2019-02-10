#pragma once

#include <array>

#include <SDL/SDL.h>

#include "Settings.h"


class Map
{
private:
	std::array<std::array<char, NUM_OF_CELLS_X>, NUM_OF_CELLS_Y> m_Data = {};
	SDL_Rect m_CellRect;

public:
	Map();
	Map(const char *filepath);

	void load(const char *filepath);
	void draw(SDL_Renderer *renderer);
};
