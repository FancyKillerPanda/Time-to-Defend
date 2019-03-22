#include "pch.h"

#include "Application.h"

#include "state/BaseGameState.h"


Application::Application(unsigned int windowWidth, unsigned int windowHeight, const char* windowTitle)
	: m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_WindowTitle(windowTitle)
{
}

Application::~Application()
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


void Application::run()
{
	// Main game-loop
	while (m_Running)
	{
		handleEvents();
		update();
		draw();
	}
}

void Application::pushState(std::unique_ptr<GameState> state)
{
	m_GameStates.emplace_back(std::move(state));
	// Sets up the state
	m_GameStates.back()->onEnter();
}

void Application::popState()
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


bool Application::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
	{
		LOG_FATAL("Could not initialise SDL.\nSDLError: {0}.", SDL_GetError());
		m_Running = false;
		return false;
	}

	LOG_INFO("SDL initialised.");

	return true;
}

bool Application::initIMG()
{
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		LOG_FATAL("Could not initialise IMG.\nSDLError: {0}.", SDL_GetError());
		m_Running = false;
		return false;
	}

	LOG_INFO("IMG initialised.");

	return true;
}

bool Application::initTTF()
{
	if (TTF_Init() != 0)
	{
		LOG_FATAL("Could not initialise TTF.\nSDLError: {0}.", SDL_GetError());
		m_Running = false;
		return false;
	}

	LOG_INFO("TTF initialised.");

	return true;
}

bool Application::createWindow()
{
	m_Window = SDL_CreateWindow(m_WindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN);

	// Error checking for window creation
	if (m_Window == nullptr)
	{
		LOG_FATAL("Could not create SDL window.\nSDLError: {0}.", SDL_GetError());
		m_Running = false;
		return false;
	}

	LOG_INFO("Created SDL window.");

	return true;
}

bool Application::createRenderer()
{
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Error checking for renderer creation
	if (m_Renderer == nullptr)
	{
		LOG_FATAL("Could not create SDL renderer.\nSDLError: {0}.", SDL_GetError());
		m_Running = false;
		return false;
	}

	LOG_INFO("Created SDL renderer.");

	return true;
}
