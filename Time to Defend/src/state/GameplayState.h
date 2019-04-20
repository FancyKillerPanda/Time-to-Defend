#pragma once

#include "pch.h"

#include "state/BaseGameState.h"
#include "gfx/Map.h"
#include "gfx/Text.h"
#include "entities/Enemy.h"
#include "entities/Tower.h"
#include "entities/Arrow.h"


// Possible levels for the game
enum class GameLevel
{
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	Custom,
};


class GameplayState : public GameState
{
private:
	static const std::array<std::string, 6> s_GameLevelStrings;

	// Current game level
	GameLevel m_GameLevel;

	// Filepath for the current map
	std::string m_CurrentMapFilepath;
	// Current map being used
	Map m_CurrentMap;

	// Containers for sprites
	std::vector<Enemy*> m_Enemies;
	std::vector<Tower*> m_Towers;
	std::vector<Arrow*> m_Arrows;

	// Current tower
	int m_CurrentTowerIndex = 0;
	// Whether the tower is rotating
	int m_TowerRotationVelocity = 0;

	// Whether the game is over
	bool m_GameOver = false;

	// Whether the level needs to be loaded
	bool m_NeedToLoadLevel = true;

	// The number of waves of enemies still to spawn
	unsigned int m_NumberOfWavesToSpawn = 0;
	// The number of waves of enemies already spawned
	unsigned int m_NumberOfWavesAlreadySpawned = 0;

	// Timer for when to spawn the next wave
	Timer m_WaveTimer;
	// Timer for how long since tower has shot
	Timer m_TowerShootTimer;

	// Whether the game is paused
	bool m_Paused = false;

	// Text that appears when game is paused
	Text m_PausedText;

	// Custom map filepath
	std::string m_CustomMapFilepath = "";

	// Custom map name
	std::string m_CustomMapName = "";

private:
	// Loads a level
	void loadLevel();

	// Spawns a set of enemies
	void spawnEnemies();

	// Changes the tower if possible
	void changeToTower(int towerNumber);

public:
	GameplayState() = default;
	GameplayState(std::string customMapName, std::string customMapFilepath);

	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
