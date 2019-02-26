#pragma once

#include "pch.h"

#include "gfx/Texture.h"


class Game;


class Arrow
{
private:
	static Game* s_Game;

	Texture* m_Texture;
	unsigned int m_Direction = 0;
	float m_PixXPos = 0.0f;
	float m_PixYPos = 0.0f;

public:
	Arrow() = default;
	Arrow(Game* const game, float xPos, float yPos, unsigned int direction);
	~Arrow();

	void draw();
	bool update();
	void move();
};
