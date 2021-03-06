#pragma once

#include "pch.h"

#include "Application.h"

#include "utils/Log.h"


class GameState
{
public:
	// Allows access to the Game's data
	static Application* s_Game;

public:
	// Initialises the game state
	static void init(Application* const game);

	// Initialises the state
	virtual void onEnter() { LOG_INFO("Created base game state."); }
	// Cleans up the state
	virtual void onExit() { LOG_INFO("Destroyed base game state."); }

	virtual void handleEvent(SDL_Event&) {}
	virtual void update() {}
	virtual void draw() {}

	// Actions when user tries to exit the application
	// Returns false if no action needs to be taken
	virtual bool actionsOnExit() { return false; }
};
