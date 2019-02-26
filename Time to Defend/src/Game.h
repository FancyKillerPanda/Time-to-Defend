#pragma once

#include "pch.h"

#include "state/BaseGameState.h"


class Game
{
private:
	bool m_Running = true;

	// Window properties
	unsigned int m_WindowWidth = 960;
	unsigned int m_WindowHeight = 540;
	const char* m_WindowTitle = "Time to Defend!";

	// SDL window and renderer
	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	// Stack of the current game states
	std::vector<std::unique_ptr<GameState>> m_GameStates;

private:
	void handleEvents();
	void update();
	void draw();

public:
	Game();
	~Game();

	// Runs the main game-loop
	void run();

	// Pushes a state onto the stack
	void pushState(std::unique_ptr<GameState> state);
	// Pops a state from the stack
	void popState();

	inline SDL_Renderer* const getRenderer() { return m_Renderer; }
};
