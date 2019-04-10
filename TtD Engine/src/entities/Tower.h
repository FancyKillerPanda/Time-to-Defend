#pragma once

#include "pch.h"

#include "Application.h"

#include "utils/Position.h"
#include "gfx/Texture.h"
#include "Arrow.h"


class Tower
{
private:
	static Application* s_Game;

	Texture* m_Texture;
	Texture* m_HighlightedTexture;
	Position m_Position = { 0, 0 };
	double m_Direction = 0;

	bool m_Highlighted = false;

public:
	Tower() = default;
	Tower(Application* const game, Position position);
	~Tower();

	void update();
	void draw();

	// Rotates the tower by an amount
	void rotate(double amountDeg);

	// Creates a new arrow and returns it
	Arrow* shoot();

	// Sets whether the tower is highlighted
	void setHighlight(bool value) { m_Highlighted = value; }
};
