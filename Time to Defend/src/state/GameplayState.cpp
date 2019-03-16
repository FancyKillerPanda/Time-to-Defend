#include "pch.h"

#include "GameplayState.h"

#include "Game.h"
#include "utils/Random.h"
#include "utils/Position.h"
#include "GameOverState.h"
#include "LevelPassedState.h"


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
	// Does not handle events until level is loaded
	if (m_NeedToLoadLevel)
	{
		return;
	}

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
			// Stops highlighting the current tower
			m_Towers[m_CurrentTowerIndex]->setHighlight(false);

			// Changes the current tower
			m_CurrentTowerIndex = (m_CurrentTowerIndex + 1) % m_Towers.size();

			// Highlights the current tower
			m_Towers[m_CurrentTowerIndex]->setHighlight(true);

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
	if (m_NeedToLoadLevel)
	{
		loadLevel();
		m_NeedToLoadLevel = false;

		return;
	}

	if (m_NumberOfWavesToSpawn > 0 && m_WaveTimer.getElapsed() >= WAVE_SPAWN_TIME)
	{
		// Spawns the next wave
		spawnEnemies();

		// Reduces the number of waves still left to spawn
		m_NumberOfWavesToSpawn -= 1;

		m_WaveTimer.reset();
		return;
	}

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

	// Level passed
	if (m_Enemies.size() == 0)
	{
		switch (m_GameLevel)
		{
		case GameLevel::_1:
			m_GameLevel = GameLevel::_2;
			break;

		case GameLevel::_2:
			m_GameLevel = GameLevel::_3;
			break;
		}

		m_NeedToLoadLevel = true;

		// Pushes the first state onto the stack
		std::unique_ptr<GameState> gameOverState = std::make_unique<LevelPassedState>();
		s_Game->pushState(std::move(gameOverState));

		return;
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


void GameplayState::loadLevel()
{
	// Makes sure no towers, enemies, or arrows remain
	onExit();

	// Makes sure tower isn't spinning after level creation
	m_TowerRotationVelocity = 0;

	// Clears the vectors
	m_Enemies.clear();
	m_Arrows.clear();
	m_Towers.clear();

	switch (m_GameLevel)
	{
	case GameLevel::_1:
		// Loads the first map
		m_CurrentMap.load(s_Game, "res/maps/Level_1.txt");

		// Creates two towers
		m_Towers.emplace_back(new Tower(s_Game, Position { 12,  9 }));
		m_Towers.emplace_back(new Tower(s_Game, Position { 12, 37 }));

		m_NumberOfWavesToSpawn = 1;

		break;

	case GameLevel::_2:
		// Loads the second map
		m_CurrentMap = Map(s_Game, "res/maps/Level_2.txt");

		// Creates two towers
		m_Towers.emplace_back(new Tower(s_Game, Position { 19, 12 }));
		m_Towers.emplace_back(new Tower(s_Game, Position {  6, 33 }));

		m_NumberOfWavesToSpawn = 3;

		break;

	case GameLevel::_3:
		// Loads the third map
		m_CurrentMap = Map(s_Game, "res/maps/Level_3.txt");

		// Creates four towers
		m_Towers.emplace_back(new Tower(s_Game, Position { 12, 10 }));
		m_Towers.emplace_back(new Tower(s_Game, Position {  4, 23 }));
		m_Towers.emplace_back(new Tower(s_Game, Position { 13, 36 }));
		m_Towers.emplace_back(new Tower(s_Game, Position { 22, 23 }));

		m_NumberOfWavesToSpawn = 4;

		break;
	}

	// Highlights the first tower the user controls
	m_Towers[m_CurrentTowerIndex]->setHighlight(true);

	// Spawns the first wave
	spawnEnemies();
	m_WaveTimer.reset();
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
