#include "pch.h"

#include "BaseGameState.h"

#include "Game.h"


Game *GameState::s_Game;

void GameState::init(Game* const game)
{
	s_Game = game;
	LOG_INFO("Game state initialised.");
}
