#include "pch.h"

#include "Game.h"

#include "utils/Log.h"
#include "utils/Random.h"
#include "state/BaseGameState.h"
#include "state/GameplayState.h"


Game::Game()
{
	// Initialises other parts of the game
	Log::init();
	Random::init();
	GameState::init(this);

	// Initialises SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
	{
		LOG_FATAL("Could not initialise SDL.");
		m_Running = false;
		return;
	}

	LOG_INFO("SDL initialised.");

	// Initialises IMG
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		LOG_FATAL("Could not initialise IMG.");
		m_Running = false;
		return;
	}

	LOG_INFO("IMG initialised.");

	// Initialises TTF
	if (TTF_Init() != 0)
	{
		LOG_FATAL("Could not initialise TTF.");
		m_Running = false;
		return;
	}

	LOG_INFO("TTF initialised.");

	// Creates the window
	m_Window = SDL_CreateWindow(m_WindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN);

	// Error checking for window creation
	if (m_Window == nullptr)
	{
		LOG_FATAL("Could not create SDL window.");
		m_Running = false;
		return;
	}

	LOG_INFO("Created SDL window.");

	// Creates the renderer
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Error checking for renderer creation
	if (m_Renderer == nullptr)
	{
		LOG_FATAL("Could not create SDL renderer.");
		m_Running = false;
		return;
	}

	LOG_INFO("Created SDL renderer.");

	// Sets the clear colour
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);

	// Pushes the first state onto the stack
	std::unique_ptr<GameState> gameplayState = std::make_unique<GameplayState>();
	pushState(std::move(gameplayState));
}

Game::~Game()
{
	// Empties the state stack
	for (unsigned int i = 0; i < m_GameStates.size(); i++)
	{
		popState();
	}

	// Destroys the renderer
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;

		LOG_INFO("Destroyed SDL renderer.");
	}

	// Destroys the window
	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;

		LOG_INFO("Destroyed SDL window.");
	}

	// Terminates SDL
	SDL_Quit();

	LOG_INFO("Destroyed Game.");
}

void Game::run()
{
	// Main game-loop
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
			// Makes sure there is a state in the stack
			if (m_GameStates.empty())
			{
				LOG_WARNING("Could not handle events for game state (empty stack).");
			}

			else
			{
				// Lets the state handle the event
				m_GameStates.back()->handleEvent(event);
			}

			break;
		}
	}
}

void Game::update()
{
	// Makes sure there is a state in the stack
	if (m_GameStates.empty())
	{
		LOG_WARNING("Could not update game state (empty stack).");
	}

	else
	{
		// Updates the state
		m_GameStates.back()->update();
	}
}

void Game::draw()
{
	// Clears the screen
	SDL_RenderClear(m_Renderer);

	// Makes sure there is a state in the stack
	if (m_GameStates.empty())
	{
		LOG_WARNING("Could not draw game state (empty stack).");
	}

	else
	{
		// Lets the state draw what it needs to
		m_GameStates.back()->draw();
	}

	SDL_RenderPresent(m_Renderer);
}


void Game::pushState(std::unique_ptr<GameState> state)
{
	m_GameStates.emplace_back(std::move(state));
	// Sets up the state
	m_GameStates.back()->onEnter();
}

void Game::popState()
{
	// Makes sure there is a state in the stack
	if (m_GameStates.empty())
	{
		LOG_WARNING("Tried to pop GameState off empty stack.");
	}

	else
	{
		// Cleans up the state before popping
		m_GameStates.back()->onExit();
		m_GameStates.pop_back();
	}
}
