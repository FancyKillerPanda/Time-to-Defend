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

	int m_Row = 0;
	int m_Col = 0;

	int m_LastRow = 0;
	int m_LastCol = 0;

public:
	Enemy() = default;
	Enemy(Game* const game, const Map* map, int row, int col);
	~Enemy();

	void draw();

	std::pair<int, int> getNextPosition();
	void move();
};
