#pragma once

#include "gfx/Texture.h"


class Game;


class Enemy
{
private:
	static Game* s_Game;
	static Texture s_Texture;

	unsigned int m_Row = 0;
	unsigned int m_Col = 0;

public:
	Enemy() = default;
	Enemy(Game* const game, unsigned int row, unsigned int col);

	void draw();
};
