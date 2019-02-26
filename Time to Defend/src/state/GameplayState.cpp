#include "pch.h"

#include "GameplayState.h"

#include "Game.h"
#include "utils/Random.h"
#include "utils/Position.h"


void GameplayState::onEnter()
{
	m_CurrentMap.load("res/maps/Level_1.txt");

	m_Towers.emplace_back(new Tower(s_Game, Position { 12,  9 }));
	m_Towers.emplace_back(new Tower(s_Game, Position { 12, 37 }));

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
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_TowerRotationVelocity = -TOWER_ROTATION_SPEED;
			break;

		case SDLK_RIGHT:
			m_TowerRotationVelocity = TOWER_ROTATION_SPEED;
			break;

		case SDLK_t:
			m_CurrentTowerIndex = (m_CurrentTowerIndex + 1) % m_Towers.size();
			break;

		case SDLK_SPACE:
			m_Arrows.emplace_back(m_Towers[m_CurrentTowerIndex]->shoot());
			break;
		}

		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_TowerRotationVelocity = 0;
			break;

		case SDLK_RIGHT:
			m_TowerRotationVelocity = 0;
			break;
		}

		break;
	}
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

	m_Towers[m_CurrentTowerIndex]->rotate(m_TowerRotationVelocity);

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

	for (unsigned int arrowIndex = 0; arrowIndex < m_Arrows.size(); arrowIndex++)
	{
		Arrow* arrow = m_Arrows[arrowIndex];

		for (unsigned int enemyIndex = 0; enemyIndex < m_Arrows.size(); enemyIndex++)
		{
			Enemy* enemy = m_Enemies[enemyIndex];

			if (arrow->collidesWithEnemy(enemy))
			{
				delete arrow;
				arrow = nullptr;

				m_Arrows.erase(m_Arrows.begin() + arrowIndex);

				delete enemy;
				enemy = nullptr;

				m_Enemies.erase(m_Enemies.begin() + enemyIndex);
			}
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

	for (Arrow* arrow : m_Arrows)
	{
		arrow->draw();
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
