#pragma once

#include "pch.h"

#include "BaseGameState.h"
#include "gfx/Map.h"
#include "entities/Enemy.h"
#include "entities/Tower.h"
#include "entities/Arrow.h"
#include "utils/Timer.h"


// Possible levels for the game
enum class GameLevel
{
	_1,
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

	// Tracks time since last enemy move
	Timer m_EnemyMoveTimer;

	// Current tower
	int m_CurrentTowerIndex = 0;
	// Whether the tower is rotating
	int m_TowerRotationVelocity = 0;

private:
	// Spawns a new enemy
	void spawnEnemy();

public:
	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
