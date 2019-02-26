#pragma once

#include "gfx/Texture.h"
#include "gfx/Map.h"
#include "utils/Position.h"


class Game;


class Enemy
{
private:
	// Game and Map are same for all enemies
	static Game* s_Game;
	static const Map* s_Map;

	// Texture
	Texture* m_Texture;

	// Position and previous position
	Position m_Position = { 0, 0 };
	Position m_LastPosition = { 0, 0 };

	bool hasMoved = false;

public:
	Enemy() = default;
	Enemy(Game* const game, const Map* map, Position position);
	~Enemy();

	void draw();

	// Gets the next available position
	Position getNextPosition();
	// Moves the enemy
	bool move();

	Texture* const getTexture() { return m_Texture; }
};
