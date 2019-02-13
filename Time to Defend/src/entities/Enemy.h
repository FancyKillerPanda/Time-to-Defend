#pragma once

#include "gfx/Texture.h"
#include "gfx/Map.h"
#include "utils/Position.h"


class Game;


class Enemy
{
private:
	static Game* s_Game;
	static Texture* s_Texture;
	static int s_InstanceCount;
	static const Map* s_Map;

	Position m_Position = { 0, 0 };
	Position m_LastPosition = { 0, 0 };

public:
	Enemy() = default;
	Enemy(Game* const game, const Map* map, Position position);
	~Enemy();

	void draw();

	Position getNextPosition();
	void move();
};
