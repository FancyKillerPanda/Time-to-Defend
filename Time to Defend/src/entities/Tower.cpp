#include "pch.h"

#include "Tower.h"

#include "utils/Log.h"
#include "Game.h"
#include "Settings.h"


Game* Tower::s_Game = nullptr;
Texture* Tower::s_Texture = nullptr;
int Tower::s_InstanceCount = 0;


Tower::Tower(Game* const game, Position position)
	: m_Position(position)
{
	s_Game = game;

	if (s_InstanceCount == 0)
	{
		s_Texture = new Texture("res/txrs/Tower.png", s_Game->getRenderer());
	}

	s_InstanceCount += 1;

	LOG_INFO("Created tower.");
}

Tower::~Tower()
{
	LOG_INFO("Destroyed tower.");

	s_InstanceCount -= 1;

	if (s_InstanceCount == 0)
	{
		delete s_Texture;
		s_Texture = nullptr;
	}
}


void Tower::draw()
{
	s_Texture->setRect(m_Position.col * CELL_SIZE, m_Position.row * CELL_SIZE);

	SDL_RenderCopyEx(s_Game->getRenderer(), s_Texture->getTexture(), nullptr, &s_Texture->getRect(), m_Direction, nullptr, SDL_FLIP_NONE);
}

void Tower::rotate(int amountDeg)
{
	m_Direction += 360;
	m_Direction += amountDeg;
	m_Direction %= 360;
}

Arrow* Tower::shoot()
{
	return new Arrow(
		s_Game,
		(m_Position.col + 1) * CELL_SIZE,
		(m_Position.row + 1) * CELL_SIZE,
		m_Direction
	);
}
