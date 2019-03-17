#pragma once

#include "pch.h"

#include "BaseGameState.h"
#include "gfx/Map.h"
#include "entities/Enemy.h"
#include "entities/Tower.h"
#include "entities/Arrow.h"


// Possible levels for the game
enum class GameLevel
{
	_1,
	_2,
	_3,
};


class GameplayState : public GameState
{
private:
	// Current game level
	GameLevel m_GameLevel;

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

	// Timer for when to spawn the next wave
	Timer m_WaveTimer;

private:
	// Loads a level
	void loadLevel();

	// Spawns a set of enemies
	void spawnEnemies();

	// Ends the game
	void endGame(bool won);

public:
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
