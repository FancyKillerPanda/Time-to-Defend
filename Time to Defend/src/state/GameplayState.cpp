#include "pch.h"

#include "GameplayState.h"

#include "Game.h"
#include "utils/Random.h"
#include "utils/Position.h"


void GameplayState::onEnter()
{
	m_CurrentMap.load("res/maps/Level_1.txt");

	m_Towers.emplace_back(new Tower(s_Game, Position { 12, 9 }));
	m_Arrows.emplace_back(new Arrow(s_Game, 100.0f, 100.0f, 45));

	m_Towers[0]->rotate(45);

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

	for (Arrow* arrow : m_Arrows)
	{
		delete arrow;
		arrow = nullptr;
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

	for (unsigned int i = 0; i < m_Arrows.size(); i++)
	{
		Arrow* arrow = m_Arrows[i];

		if (!arrow->update())
		{
			delete arrow;
			arrow = nullptr;

			m_Arrows.erase(m_Arrows.begin() + i);
		}
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

	for (Arrow* arrow : m_Arrows)
	{
		arrow->draw();
	}
}


void GameplayState::spawnEnemy()
{
#pragma warning(suppress: 4267)
	Position spawnPos = m_CurrentMap.getSpawnCoords()[Random::randint(0, m_CurrentMap.getSpawnCoords().size() - 1)];
	m_Enemies.emplace_back(new Enemy(s_Game, &m_CurrentMap, spawnPos));
}
