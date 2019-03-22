#include "pch.h"

#include "Arrow.h"
#include "Enemy.h"

#include <cmath>

#include "Game.h"
#include "Settings.h"
#include "utils/Maths.h"


Game* Arrow::s_Game = nullptr;


Arrow::Arrow(Game* const game, float pixXPos, float pixYPos, unsigned int direction)
	: m_Direction((direction + 270) % 360), m_PixXPos(pixXPos), m_PixYPos(pixYPos)
{
	s_Game = game;

	// Creates the texture
	m_Texture = new Texture("res/txrs/Arrow.png", s_Game->getRenderer());
}

Arrow::~Arrow()
{
	delete m_Texture;
	m_Texture = nullptr;
}


void Arrow::draw()
{
	// Draws the texture at the current position
	SDL_RenderCopy(s_Game->getRenderer(), m_Texture->getTexture(), nullptr, &m_Texture->getRect());
}

bool Arrow::update()
{
	// Moves the arrow
	move();

	// Returns false if the piece is out of bounds
	return !(
		m_PixXPos < 0 ||
		m_PixYPos < 0 ||
		m_PixXPos > NUM_OF_CELLS_X * CELL_SIZE ||
		m_PixYPos > NUM_OF_CELLS_Y * CELL_SIZE
	);
}

void Arrow::move()
{
	// Moves in the current direction
	m_PixYPos += ARROW_SPEED * (float) std::sin(getRadians(m_Direction));
	m_PixXPos += ARROW_SPEED * (float) std::cos(getRadians(m_Direction));

	// Re-sets the texture's rect
	m_Texture->setRect((unsigned int) m_PixXPos, (unsigned int) m_PixYPos);
}

bool Arrow::collidesWithEnemy(Enemy* enemy)
{
	return SDL_HasIntersection(&m_Texture->getRect(), &enemy->getTexture()->getRect());
}
