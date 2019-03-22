#pragma once

#include "pch.h"

#include "gfx/Texture.h"


class Game;
class Enemy;


class Arrow
{
private:
	static Game* s_Game;

	// Texture
	Texture* m_Texture;

	// Direction the arrow is travelling, in degrees
	unsigned int m_Direction = 0;

	// Current position (in pixels)
	float m_PixXPos = 0.0f;
	float m_PixYPos = 0.0f;

public:
	Arrow() = default;
	Arrow(Game* const game, float xPos, float yPos, unsigned int direction);
	~Arrow();

	void draw();
	bool update();
	void move();

	// Checks if the arrow is colliding with an enemy
	bool collidesWithEnemy(Enemy* enemy);
};
