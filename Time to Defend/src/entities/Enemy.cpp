#include "Enemy.h"

#include "Game.h"
#include "Settings.h"


Game* Enemy::s_Game = nullptr;
Texture Enemy::s_Texture;


Enemy::Enemy(Game* const game, unsigned int row, unsigned int col)
	: m_Row(row), m_Col(col)
{
	s_Game = game;

	if (!s_Texture.getLoaded())
	{
		s_Texture.load("res/txrs/Enemy.png", s_Game->getRenderer());
	}
}


void Enemy::draw()
{
	s_Texture.setRect(m_Col * CELL_SIZE, m_Row * CELL_SIZE);

	SDL_RenderCopy(s_Game->getRenderer(), s_Texture.getTexture(), nullptr, &s_Texture.getRect());
}
