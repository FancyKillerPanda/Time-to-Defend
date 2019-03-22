#pragma once

#include "pch.h"


class GameState;

class Application
{
public:
	// Pushes a state onto the stack
	virtual void pushState(std::unique_ptr<GameState> state) = 0;
	// Pops a state from the stack
	virtual void popState() = 0;

	virtual inline SDL_Renderer* const getRenderer() = 0;
	virtual inline unsigned int getWindowWidth() = 0;
	virtual inline unsigned int getWindowHeight() = 0;

	virtual void setRunning(bool value) = 0;
};
