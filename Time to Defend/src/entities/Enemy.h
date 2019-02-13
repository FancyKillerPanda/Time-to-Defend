#pragma once

#include "gfx/Texture.h"
#include "gfx/Map.h"


class Game;


class Enemy
{
private:
	static Game* s_Game;
	static Texture* s_Texture;
	static int s_InstanceCount;
	static const Map* s_Map;

	unsigned int m_Row = 0;
	unsigned int m_Col = 0;

	unsigned int m_LastRow = 0;
	unsigned int m_LastCol = 0;

public:
	Enemy() = default;
	Enemy(Game* const game, const Map* map, unsigned int row, unsigned int col);
	~Enemy();

	void draw();

	std::pair<unsigned int, unsigned int> getNextPosition();
	void move();
};
