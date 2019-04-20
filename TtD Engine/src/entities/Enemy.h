#pragma once

#include "pch.h"

#include "Application.h"

#include "gfx/Texture.h"
#include "gfx/Map.h"
#include "utils/Position.h"
#include "utils/Timer.h"


enum class EnemyColour
{
	Red,
	Blue,
	Lime,
	Yellow,
	Black,
};


class Enemy
{
private:
	// Game and Map are same for all enemies
	static Application* s_Game;
	static const Map* s_Map;

	// The names of the colours
	static const std::array<std::string, 5> s_ColourStrings;

	// The filepath of the texture
	std::string m_TextureFilepath;
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

	// The colour of the enemy
	EnemyColour m_Colour;

public:
	Enemy(Application* const game, const Map* map, Position position, EnemyColour colour);
	~Enemy();

	void draw();

	// Gets the next available position
	Position getNextPosition();
	// Moves the enemy
	bool move();

	inline Texture* const getTexture() { return m_Texture; }
	inline unsigned int getMoveTime() { return m_MoveTime; }
};
