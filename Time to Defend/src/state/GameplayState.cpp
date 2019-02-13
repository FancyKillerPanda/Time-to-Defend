#include "pch.h"

#include "GameplayState.h"

#include "Game.h"
#include "utils/Random.h"
#include "utils/Position.h"


void GameplayState::onEnter()
{
	m_CurrentMap.load("res/maps/Level_1.txt");

	spawnEnemy();
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
	if (m_EnemyMoveTimer.getElapsed() >= 500)
	{
		for (Enemy* enemy : m_Enemies)
		{
			enemy->move();
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
}


void GameplayState::spawnEnemy()
{
#pragma warning(suppress: 4267)
	Position spawnPos = m_CurrentMap.getSpawnCoords()[Random::randint(0, m_CurrentMap.getSpawnCoords().size() - 1)];
	m_Enemies.emplace_back(new Enemy(s_Game, &m_CurrentMap, spawnPos));
}
