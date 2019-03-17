#pragma once

#include "pch.h"

#include "state/BaseGameState.h"
#include "utils/Timer.h"
#include "gfx/Text.h"


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

#ifdef _DEBUG
	// Frame rate timer
	Timer m_FrameTimer;
	// Counter of number of frames since timer reset
	unsigned int m_FrameCount;

	// Text containing debug information
	Text m_InfoText;
#endif // _DEBUG


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
	inline unsigned int getWindowWidth() { return m_WindowWidth; }
	inline unsigned int getWindowHeight() { return m_WindowHeight; }
};
