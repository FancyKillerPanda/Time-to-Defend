#pragma once

#include "pch.h"

#include "utils/Log.h"


class Game;


class GameState
{
public:
	// Allows access to the Game's data
	static Game* s_Game;

public:
	// Initialises the game state
	static void init(Game* const game);

	// Initialises the state
	virtual void onEnter() { LOG_INFO("Created base game state."); }
	// Cleans up the state
	virtual void onExit() { LOG_INFO("Destroyed base game state."); }

	virtual void handleEvent(SDL_Event& event) {}
	virtual void update() {}
	virtual void draw() {}
};
