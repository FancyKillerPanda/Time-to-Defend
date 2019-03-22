#pragma once

#include "pch.h"

#include "BaseApplication.h"

#include "gfx/Texture.h"
#include "gfx/Map.h"
#include "utils/Position.h"
#include "utils/Timer.h"


class Enemy
{
private:
	// Game and Map are same for all enemies
	static Application* s_Game;
	static const Map* s_Map;

	// Texture
	Texture* m_Texture;

	// Position and previous position
	Position m_Position = { 0, 0 };
	Position m_LastPosition = { 0, 0 };

	bool hasMoved = false;

	// Tracks time since last enemy move
	Timer m_MoveTimer;
	// Time it takes for enemy to update
	unsigned int m_MoveTime;

public:
	Enemy() = default;
	Enemy(Application* const game, const Map* map, Position position);
	~Enemy();

	void draw();

	// Gets the next available position
	Position getNextPosition();
	// Moves the enemy
	bool move();

	inline Texture* const getTexture() { return m_Texture; }
	inline unsigned int getMoveTime() { return m_MoveTime; }
};
