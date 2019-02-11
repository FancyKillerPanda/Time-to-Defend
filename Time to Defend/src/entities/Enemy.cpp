#include "Enemy.h"

#include "Game.h"
#include "Settings.h"


Game* Enemy::s_Game = nullptr;
Texture* Enemy::s_Texture = nullptr;
int Enemy::s_InstanceCount = 0;


Enemy::Enemy(Game* const game, unsigned int row, unsigned int col)
	: m_Row(row), m_Col(col)
{
	s_Game = game;

	if (s_InstanceCount == 0)
	{
		s_Texture = new Texture("res/txrs/Enemy.png", s_Game->getRenderer());
	}

	s_InstanceCount += 1;

	LOG_INFO("Created enemy.");
}

Enemy::~Enemy()
{
	LOG_INFO("Destroyed enemy.");

	s_InstanceCount -= 1;

	if (s_InstanceCount == 0)
	{
		delete s_Texture;
		s_Texture = nullptr;
	}
}


void Enemy::draw()
{
	s_Texture->setRect(m_Col * CELL_SIZE, m_Row * CELL_SIZE);

	SDL_RenderCopy(s_Game->getRenderer(), s_Texture->getTexture(), nullptr, &s_Texture->getRect());
}
