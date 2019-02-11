#include "pch.h"

#include "Game.h"

#include "utils/Log.h"
#include "utils/Random.h"
#include "state/BaseGameState.h"
#include "state/GameplayState.h"


Game::Game()
{
	Log::init();
	Random::init();
	GameState::init(this);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
	{
		LOG_FATAL("Could not initialise SDL.");
		m_Running = false;
		return;
	}

	LOG_INFO("SDL initialised.");

	m_Window = SDL_CreateWindow(m_WindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN);

	if (m_Window == nullptr)
	{
		LOG_FATAL("Could not create SDL window.");
		m_Running = false;
		return;
	}

	LOG_INFO("Created SDL window.");

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_Renderer == nullptr)
	{
		LOG_FATAL("Could not create SDL renderer.");
		m_Running = false;
		return;
	}

	LOG_INFO("Created SDL renderer.");

	std::unique_ptr<GameState> gameplayState = std::make_unique<GameplayState>();
	pushState(std::move(gameplayState));
}

Game::~Game()
{
	for (unsigned int i = 0; i < m_GameStates.size(); i++)
	{
		popState();
	}

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
			break;

		default:
			if (m_GameStates.empty())
			{
				LOG_WARNING("Could not handle events for game state (empty stack).");
			}

			else
			{
				m_GameStates.back()->handleEvent(event);
			}

			break;
		}
	}
}

void Game::update()
{
	if (m_GameStates.empty())
	{
		LOG_WARNING("Could not update game state (empty stack).");
	}

	else
	{
		m_GameStates.back()->update();
	}
}

void Game::draw()
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);
	SDL_RenderClear(m_Renderer);

	if (m_GameStates.empty())
	{
		LOG_WARNING("Could not draw game state (empty stack).");
	}

	else
	{
		m_GameStates.back()->draw();
	}

	SDL_RenderPresent(m_Renderer);
}


void Game::pushState(std::unique_ptr<GameState> state)
{
	m_GameStates.emplace_back(std::move(state));
	m_GameStates.back()->onEnter();
}

void Game::popState()
{
	if (m_GameStates.empty())
	{
		LOG_WARNING("Tried to pop GameState off empty stack.");
	}

	else
	{
		m_GameStates.back()->onExit();
		m_GameStates.pop_back();
	}
}
