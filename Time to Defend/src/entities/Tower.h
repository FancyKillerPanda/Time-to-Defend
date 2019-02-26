#pragma once

#include "pch.h"

#include "utils/Position.h"
#include "gfx/Texture.h"
#include "Arrow.h"


class Game;


class Tower
{
private:
	static Game* s_Game;

	Texture* m_Texture;
	Position m_Position = { 0, 0 };
	unsigned int m_Direction = 0;

public:
	Tower() = default;
	Tower(Game* const game, Position position);
	~Tower();

	void draw();
	void rotate(int amountDeg);
	Arrow* shoot();
};
