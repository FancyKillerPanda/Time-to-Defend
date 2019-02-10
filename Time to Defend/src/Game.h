#pragma once

#include <memory>
#include <vector>

#include <SDL/SDL.h>

#include "state/BaseGameState.h"


class Game
{
private:
	bool m_Running = true;

	unsigned int m_WindowWidth = 960;
	unsigned int m_WindowHeight = 540;
	const char* m_WindowTitle = "Time to Defend!";

	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	std::vector<std::unique_ptr<GameState>> m_GameStates;

private:
	void handleEvents();
	void update();
	void draw();

public:
	Game();
	~Game();

	void run();

	void pushState(std::unique_ptr<GameState> state);
	void popState();

	inline SDL_Renderer* const getRenderer() { return m_Renderer; }
};
