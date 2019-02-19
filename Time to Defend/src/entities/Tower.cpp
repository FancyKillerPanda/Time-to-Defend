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

	SDL_RenderCopy(s_Game->getRenderer(), s_Texture->getTexture(), nullptr, &s_Texture->getRect());
}
