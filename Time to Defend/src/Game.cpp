#include "Game.h"

#include "utils/Log.h"


Game::Game()
{
	Log::init();

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
	{
		LOG_FATAL("Could not initialise SDL.");
		m_Running = false;
	}

	LOG_INFO("SDL initialised.");

	m_Window = SDL_CreateWindow(m_WindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN);

	if (m_Window == nullptr)
	{
		LOG_FATAL("Could not create SDL window.");
		m_Running = false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_Renderer == nullptr)
	{
		LOG_FATAL("Could not create SDL renderer.");
		m_Running = false;
	}
}

Game::~Game()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;

		LOG_INFO("Destroyed SDL renderer.");
	}

	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;

		LOG_INFO("Destroyed SDL window.");
	}

	SDL_Quit();

	LOG_INFO("Destroyed Game.");
}

void Game::run()
{
	while (m_Running)
	{
		handleEvents();
		update();
		draw();
	}
}


void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_Running = false;
		}
	}
}

void Game::update()
{
}

void Game::draw()
{
	SDL_RenderClear(m_Renderer);

	SDL_RenderPresent(m_Renderer);
}
