#pragma once

#include "pch.h"

#include "BaseGameState.h"
#include "gfx/Map.h"
#include "entities/Enemy.h"
#include "entities/Tower.h"
#include "utils/Timer.h"


enum class GameLevel
{
	_1,
};


class GameplayState : public GameState
{
private:
	GameLevel m_GameLevel;

	Map m_CurrentMap;
	std::vector<Enemy*> m_Enemies;
	std::vector<Tower*> m_Towers;

	Timer m_EnemyMoveTimer;

private:
	void spawnEnemy();

public:
	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
