#include "pch.h"

#include "GameplayState.h"

#include "Game.h"
#include "utils/Random.h"
#include "utils/Position.h"


void GameplayState::onEnter()
{
	m_CurrentMap.load("res/maps/Level_1.txt");

	m_Towers.emplace_back(new Tower(s_Game, Position { 12, 9 }));

	spawnEnemy();
}

void GameplayState::onExit()
{
	for (Enemy* enemy : m_Enemies)
	{
		delete enemy;
		enemy = nullptr;
	}

	for (Tower* tower : m_Towers)
	{
		delete tower;
		tower = nullptr;
	}
}

void GameplayState::handleEvent(SDL_Event& event)
{
}

void GameplayState::update()
{
	if (m_EnemyMoveTimer.getElapsed() >= 500)
	{
		for (unsigned int i = 0; i < m_Enemies.size(); i++)
		{
			Enemy* enemy = m_Enemies[i];

			if (!enemy->move())
			{
				delete enemy;
				enemy = nullptr;

				m_Enemies.erase(m_Enemies.begin() + i);
			}
		}

		m_EnemyMoveTimer.reset();
	}
}

void GameplayState::draw()
{
	m_CurrentMap.draw(s_Game->getRenderer());

	for (Enemy* enemy : m_Enemies)
	{
		enemy->draw();
	}

	for (Tower* tower : m_Towers)
	{
		tower->draw();
	}
}


void GameplayState::spawnEnemy()
{
#pragma warning(suppress: 4267)
	Position spawnPos = m_CurrentMap.getSpawnCoords()[Random::randint(0, m_CurrentMap.getSpawnCoords().size() - 1)];
	m_Enemies.emplace_back(new Enemy(s_Game, &m_CurrentMap, spawnPos));
}
