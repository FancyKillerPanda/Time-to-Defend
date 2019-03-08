#include "pch.h"

#include "GameplayState.h"

#include "Game.h"
#include "utils/Random.h"
#include "utils/Position.h"
#include "GameOverState.h"


void GameplayState::onEnter()
{
	// Loads the first map
	m_CurrentMap.load("res/maps/Level_1.txt");

	// Creates two towers
	m_Towers.emplace_back(new Tower(s_Game, Position { 12,  9 }));
	m_Towers.emplace_back(new Tower(s_Game, Position { 12, 37 }));

	// Creates the first set of enemies
	spawnEnemies();
}

void GameplayState::onExit()
{
	// Destroys all enemies
	for (Enemy* enemy : m_Enemies)
	{
		delete enemy;
		enemy = nullptr;
	}

	// Destroys all towers
	for (Tower* tower : m_Towers)
	{
		delete tower;
		tower = nullptr;
	}

	// Destroys all arrows
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
			// Will rotate tower to the left
			m_TowerRotationVelocity = -TOWER_ROTATION_SPEED;
			break;

		case SDLK_RIGHT:
			// Will rotate tower to the right
			m_TowerRotationVelocity = TOWER_ROTATION_SPEED;
			break;

		case SDLK_t:
			// Changes the current tower
			m_CurrentTowerIndex = (m_CurrentTowerIndex + 1) % m_Towers.size();
			break;

		case SDLK_SPACE:
			// Shoots an arrow
			m_Arrows.emplace_back(m_Towers[m_CurrentTowerIndex]->shoot());
			break;
		}

		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			// Will stop the tower from moving
			m_TowerRotationVelocity = 0;
			break;

		case SDLK_RIGHT:
			// Will stop the tower from moving
			m_TowerRotationVelocity = 0;
			break;
		}

		break;
	}
}

void GameplayState::update()
{
	for (unsigned int i = 0; i < m_Enemies.size(); i++)
	{
		Enemy* enemy = m_Enemies[i];

		// Game over state is pushed if enemy has finished moving
		if (!enemy->move())
		{
			m_GameOver = true;

			endGame();
			return;
		}
	}

	// Rotates the tower if needed
	m_Towers[m_CurrentTowerIndex]->rotate(m_TowerRotationVelocity);

	// Moves each arrow
	for (unsigned int i = 0; i < m_Arrows.size(); i++)
	{
		Arrow* arrow = m_Arrows[i];

		// Destroys the arrow if it is out of bounds
		if (!arrow->update())
		{
			delete arrow;
			arrow = nullptr;

			m_Arrows.erase(m_Arrows.begin() + i);
		}
	}

	// Checks for arrow-enemy collisions
	for (unsigned int arrowIndex = 0; arrowIndex < m_Arrows.size(); arrowIndex++)
	{
		Arrow* arrow = m_Arrows[arrowIndex];

		for (unsigned int enemyIndex = 0; enemyIndex < m_Enemies.size(); enemyIndex++)
		{
			Enemy* enemy = m_Enemies[enemyIndex];

			// Destroys both objects if they collide
			if (arrow->collidesWithEnemy(enemy))
			{
				delete arrow;
				arrow = nullptr;

				m_Arrows.erase(m_Arrows.begin() + arrowIndex);

				delete enemy;
				enemy = nullptr;

				m_Enemies.erase(m_Enemies.begin() + enemyIndex);

				break;
			}
		}
	}
}

void GameplayState::draw()
{
	// Draws the map
	m_CurrentMap.draw(s_Game->getRenderer());

	// Draws each enemy
	for (Enemy* enemy : m_Enemies)
	{
		enemy->draw();
	}

	// Draws each arrow
	for (Arrow* arrow : m_Arrows)
	{
		arrow->draw();
	}

	// Draws each tower
	for (Tower* tower : m_Towers)
	{
		tower->draw();
	}
}


void GameplayState::spawnEnemies()
{
	// Stores which spawn positions have already been used
	std::vector<int> usedIndices;

	// Once for every spawn position
	for (unsigned int i = 0; i < m_CurrentMap.getSpawnCoords().size(); i++)
	{
		int index;

		while (true)
		{
			// Gets a spawn position index
			index = Random::randint(0, (int) m_CurrentMap.getSpawnCoords().size() - 1);

			// Index not already used
			if (std::find(usedIndices.begin(), usedIndices.end(), index) == usedIndices.end())
			{
				break;
			}
		}

		// Suppresses conversion warning
	#pragma warning(suppress: 4267)
		// Creates the enemy
		m_Enemies.emplace_back(new Enemy(s_Game, &m_CurrentMap, m_CurrentMap.getSpawnCoords()[index]));
		usedIndices.push_back(index);
	}
}

void GameplayState::endGame()
{
	// Pops this state off the Game's stack
	s_Game->popState();

	// Pushes the first state onto the stack
	std::unique_ptr<GameState> gameOverState = std::make_unique<GameOverState>();
	s_Game->pushState(std::move(gameOverState));
}
