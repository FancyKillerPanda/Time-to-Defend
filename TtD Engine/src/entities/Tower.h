#pragma once

#include "pch.h"

#include "utils/Position.h"
#include "gfx/Texture.h"
#include "Arrow.h"


class Game;


class Tower
{
private:
	static Game* s_Game;

	Texture* m_Texture;
	Texture* m_HighlightedTexture;
	Position m_Position = { 0, 0 };
	unsigned int m_Direction = 0;

	bool m_Highlighted = false;

public:
	Tower() = default;
	Tower(Game* const game, Position position);
	~Tower();

	void draw();

	// Rotates the tower, input in degrees
	void rotate(int amountDeg);

	// Creates a new arrow and returns it
	Arrow* shoot();

	// Sets whether the tower is highlighted
	void setHighlight(bool value) { m_Highlighted = value; }
};
