#include "pch.h"

#include "BaseGameState.h"


Application* GameState::s_Game;

void GameState::init(Application* const game)
{
	s_Game = game;
	LOG_INFO("Game state initialised.");
}
