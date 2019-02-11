#include "GameplayState.h"

#include "Game.h"


void GameplayState::onEnter()
{
	m_CurrentMap.load("res/maps/Level_1.txt");
	m_Enemies.emplace_back(new Enemy(s_Game, 4, 0));
}

void GameplayState::onExit()
{
	for (Enemy* enemy : m_Enemies)
	{
		delete enemy;
		enemy = nullptr;
	}
}

void GameplayState::handleEvent(SDL_Event& event)
{
}

void GameplayState::update()
{
}

void GameplayState::draw()
{
	m_CurrentMap.draw(s_Game->getRenderer());

	for (Enemy* enemy : m_Enemies)
	{
		enemy->draw();
	}
}
