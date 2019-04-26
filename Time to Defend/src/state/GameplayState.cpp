#include "pch.h"

#include "GameplayState.h"

#include "Game.h"
#include "utils/Random.h"
#include "utils/Position.h"
#include "GameOverState.h"
#include "LevelPassedState.h"


#define CHANGE_TOWER(key, num) case key:\
	changeToTower(num);\
	break;


const std::array<std::string, 6> GameplayState::s_GameLevelStrings = {
	"_1",
	"_2",
	"_3",
	"_4",
	"_5",
	"_6",
};


GameplayState::GameplayState(std::string customMapName, std::string customMapFilepath)
	: m_CustomMapName(customMapName), m_CustomMapFilepath(customMapFilepath)
{
	m_GameLevel = GameLevel::Custom;
}


void GameplayState::onEnter()
{
	m_PausedText.load(DEFAULT_FONT_PATH, "Paused!", 48, SDL_Color { 255, 255, 255, 255 }, s_Game->getRenderer());
	m_PausedText.setStyle(TTF_STYLE_BOLD);
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

		case SDLK_p:
			// Pauses/unpauses the game
			m_Paused = !m_Paused;
			break;

		case SDLK_RETURN:
			// Unpauses the game
			m_Paused = false;
			break;

		case SDLK_t:
			// Changes the tower
			changeToTower((m_CurrentTowerIndex + 1) % m_Towers.size());
			break;

		case SDLK_SPACE:
			if (s_Game->settings->spaceToShoot && m_TowerShootTimer.getElapsed() >= TOWER_SHOOT_COOLDOWN_TIME)
			{
				// Shoots an arrow
				m_Arrows.emplace_back(m_Towers[m_CurrentTowerIndex]->shoot());
				m_TowerShootTimer.reset();

				break;
			}

		CHANGE_TOWER(SDLK_1, 0);
		CHANGE_TOWER(SDLK_2, 1);
		CHANGE_TOWER(SDLK_3, 2);
		CHANGE_TOWER(SDLK_4, 3);
		CHANGE_TOWER(SDLK_5, 4);
		CHANGE_TOWER(SDLK_6, 5);
		CHANGE_TOWER(SDLK_7, 6);
		CHANGE_TOWER(SDLK_8, 7);
		CHANGE_TOWER(SDLK_9, 8);
		CHANGE_TOWER(SDLK_0, 9);

		#ifdef _DEBUG
		case SDLK_k:
			// Kills all enemies
			for (unsigned int i = 0; i < m_Enemies.size(); i++)
			{
				// Gets the enemy
				Enemy* enemy = m_Enemies[i];

				// Deletes the enemy
				delete enemy;
				enemy = nullptr;
			}

			// Removes the (now destroyed) enemies from the vector
			m_Enemies.clear();

			break;
		#endif // _DEBUG
		}

		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			if (s_Game->settings->arrowKeysToRotateTower)
			{
				// Will stop the tower from moving
				m_TowerRotationVelocity = 0;
				break;
			}

		case SDLK_RIGHT:
			if (s_Game->settings->arrowKeysToRotateTower)
			{
				// Will stop the tower from moving
				m_TowerRotationVelocity = 0;
				break;
			}
		}

		break;

	case SDL_MOUSEBUTTONDOWN:
		if (!s_Game->settings->spaceToShoot && m_TowerShootTimer.getElapsed() >= TOWER_SHOOT_COOLDOWN_TIME)
		{
			// Shoots an arrow
			m_Arrows.emplace_back(m_Towers[m_CurrentTowerIndex]->shoot());
			m_TowerShootTimer.reset();

			break;
		}
	}
}

void GameplayState::update()
{
	if (m_Paused)
	{
		return;
	}

	if (m_NeedToLoadLevel)
	{
		loadLevel();
		m_NeedToLoadLevel = false;

		return;
	}

	if (m_NumberOfWavesToSpawn > 0 && m_WaveTimer.getElapsed() >= WAVE_SPAWN_TIME)
	{
		// Spawns the next wave and resets the timer
		spawnEnemies();
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
			s_Game->replaceTopState<GameOverState>(false, m_GameLevel == GameLevel::Custom ? m_CustomMapName : "");

			return;
		}
	}

	if (s_Game->settings->arrowKeysToRotateTower)
	{
		// Rotates the tower if needed
		m_Towers[m_CurrentTowerIndex]->rotate((double) m_TowerRotationVelocity);
	}

	else
	{
		// Rotates the tower to face the mouse
		m_Towers[m_CurrentTowerIndex]->update();
	}

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
		case GameLevel::_2:
		case GameLevel::_3:
		case GameLevel::_4:
		case GameLevel::_5:
			m_GameLevel = GameLevel((int) m_GameLevel + 1);
			break;

		case GameLevel::_6:
			// Ends the game with a win
			s_Game->replaceTopState<GameOverState>(true, "");
			return;

		case GameLevel::Custom:
			s_Game->replaceTopState<GameOverState>(true, m_CustomMapName);
			return;
		}

		m_NeedToLoadLevel = true;

		// Pushes the level passed state onto the stack
		s_Game->pushState<LevelPassedState>((int) m_GameLevel);

		return;
	}
}

void GameplayState::draw()
{
	// Draws the map
	m_CurrentMap.draw();

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

	if (m_Paused)
	{
		// Dims the screen
		SDL_SetRenderDrawColor(s_Game->getRenderer(), 0, 0, 0, 150);
		SDL_RenderFillRect(s_Game->getRenderer(), nullptr);

		// Draws the paused text
		m_PausedText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() / 2);
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

	if (m_GameLevel == GameLevel::Custom)
	{
		// Loads the custom map
		m_CurrentMap.load(s_Game, m_CustomMapFilepath.c_str());

		// Couldn't load map
		if (!m_CurrentMap.getLoaded())
		{
			LOG_WARNING("Could not load custom map. Starting level 1.");
			m_GameLevel = GameLevel::_1;
		}
	}

	switch (m_GameLevel)
	{
	case GameLevel::Custom:
		break;

	case GameLevel::_1:
		// I don't know why level 1 doesn't like to load properly
		m_CurrentMap.load(s_Game, "res/maps/Level_1.txt");
		break;

	default:
		// Calculates the map's filepath
		m_CurrentMapFilepath = "res/maps/Level";
		m_CurrentMapFilepath += s_GameLevelStrings[(unsigned int) m_GameLevel];
		m_CurrentMapFilepath += ".txt";

		// Creates the map
		m_CurrentMap = Map(s_Game, m_CurrentMapFilepath.c_str());

		break;
	}

	// Sets the number of waves to spawn
	m_NumberOfWavesToSpawn = m_CurrentMap.getNumberOfWavesToSpawn();
	// Resets number of waves already spawned
	m_NumberOfWavesAlreadySpawned = 0;

	// Creates the towers
	for (const Position& position : m_CurrentMap.getTowerCoords())
	{
		m_Towers.emplace_back(new Tower(s_Game, position));
	}

	// Highlights the first tower the user controls
	m_Towers[m_CurrentTowerIndex]->setHighlight(true);

	// Spawns the first wave
	spawnEnemies();
	m_WaveTimer.reset();
}

void GameplayState::spawnEnemies()
{
	// Calculates the colour
	unsigned int colourIndex = (unsigned int) std::floor((double) m_NumberOfWavesAlreadySpawned / 2.0);

	if (colourIndex >= (unsigned int) EnemyColour::COUNT)
	{
		colourIndex = (unsigned int) EnemyColour::COUNT - 1;
	}

	EnemyColour colour = EnemyColour(colourIndex);

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
		m_Enemies.emplace_back(new Enemy(s_Game, &m_CurrentMap, m_CurrentMap.getSpawnCoords()[index], colour));
		usedIndices.push_back(index);
	}

	// Adjusts the wave spawn counters
	m_NumberOfWavesToSpawn -= 1;
	m_NumberOfWavesAlreadySpawned += 1;
}

void GameplayState::changeToTower(int towerNumber)
{
	if (towerNumber < m_Towers.size())
	{
		// Stops highlighting the current tower
		m_Towers[m_CurrentTowerIndex]->setHighlight(false);

		// Changes the current tower
		m_CurrentTowerIndex = towerNumber;

		// Highlights the current tower
		m_Towers[m_CurrentTowerIndex]->setHighlight(true);
	}

	m_TowerShootTimer.reset();
}
