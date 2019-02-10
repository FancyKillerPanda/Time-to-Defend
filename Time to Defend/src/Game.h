#pragma once

#include <SDL/SDL.h>


class Game
{
private:
	bool m_Running = true;

	unsigned int m_WindowWidth = 960;
	unsigned int m_WindowHeight = 540;
	const char *m_WindowTitle = "Time to Defend!";

	SDL_Window *m_Window = nullptr;
	SDL_Renderer *m_Renderer = nullptr;

private:
	void handleEvents();
	void update();
	void draw();

public:
	Game();
	~Game();

	void run();
};
