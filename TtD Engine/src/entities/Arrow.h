#pragma once

#include "pch.h"

#include "Application.h"
#include "gfx/Texture.h"


class Enemy;


class Arrow
{
private:
	static Application* s_Game;

	// Texture
	Texture* m_Texture;

	// Direction the arrow is travelling, in degrees
	double m_Direction = 0;

	// Current position (in pixels)
	float m_PixXPos = 0.0f;
	float m_PixYPos = 0.0f;

public:
	Arrow() = default;
	Arrow(Application* const game, float xPos, float yPos, double direction);
	~Arrow();

	void draw();
	bool update();
	void move();

	// Checks if the arrow is colliding with an enemy
	bool collidesWithEnemy(Enemy* enemy);
};
