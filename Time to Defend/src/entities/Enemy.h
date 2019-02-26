#pragma once

#include "gfx/Texture.h"
#include "gfx/Map.h"
#include "utils/Position.h"


class Game;


class Enemy
{
private:
	static Game* s_Game;
	static const Map* s_Map;

	Texture* m_Texture;
	Position m_Position = { 0, 0 };
	Position m_LastPosition = { 0, 0 };

	bool hasMoved = false;

public:
	Enemy() = default;
	Enemy(Game* const game, const Map* map, Position position);
	~Enemy();

	void draw();

	Position getNextPosition();
	bool move();

	Texture* const getTexture() { return m_Texture; }
};
