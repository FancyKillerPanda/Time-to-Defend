#include "pch.h"

#include "Arrow.h"

#include <cmath>

#include "Game.h"
#include "Settings.h"
#include "utils/Maths.h"


Game* Arrow::s_Game = nullptr;
Texture* Arrow::s_Texture = nullptr;
int Arrow::s_InstanceCount = 0;


Arrow::Arrow(Game* const game, float pixXPos, float pixYPos, unsigned int direction)
	: m_Direction((direction + 270) % 360), m_PixXPos(pixYPos), m_PixYPos(pixYPos)
{
	s_Game = game;

	if (s_InstanceCount == 0)
	{
		s_Texture = new Texture("res/txrs/Arrow.png", s_Game->getRenderer());
	}

	s_InstanceCount += 1;

	LOG_INFO("Created arrow.");
}

Arrow::~Arrow()
{
	LOG_INFO("Destroyed arrow.");

	s_InstanceCount -= 1;

	if (s_InstanceCount == 0)
	{
		delete s_Texture;
		s_Texture = nullptr;
	}
}


void Arrow::draw()
{
	s_Texture->setRect((unsigned int) m_PixYPos, (unsigned int) m_PixXPos);

	SDL_RenderCopy(s_Game->getRenderer(), s_Texture->getTexture(), nullptr, &s_Texture->getRect());
}

bool Arrow::update()
{
	move();

	return !(
		m_PixXPos < 0 ||
		m_PixYPos < 0 ||
		m_PixXPos > NUM_OF_CELLS_X * CELL_SIZE ||
		m_PixYPos > NUM_OF_CELLS_Y * CELL_SIZE
	);
}

void Arrow::move()
{
	m_PixXPos += ARROW_SPEED * (float) std::sin(getRadians(m_Direction));
	m_PixYPos += ARROW_SPEED * (float) std::cos(getRadians(m_Direction));
}
