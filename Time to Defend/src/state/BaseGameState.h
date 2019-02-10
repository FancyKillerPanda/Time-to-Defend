#pragma once

#include <SDL/SDL.h>

#include "utils/Log.h"


class GameState
{
public:
	virtual void onEnter() { LOG_INFO("Created base game state."); }
	virtual void onExit() { LOG_INFO("Destroyed base game state."); }

	virtual void handleEvent(SDL_Event &event) {}
	virtual void update() {}
	virtual void draw() {}
};
