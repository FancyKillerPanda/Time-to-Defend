#include "pch.h"

#include "Game.h"

#include "utils/Log.h"
#include "utils/Random.h"
#include "state/BaseGameState.h"
#include "state/StartScreenState.h"


Game::Game()
	: Application(960, 540, "Time to Defend!")
{
	// Initialises other parts of the game
	Log::init("TTDLOG");
	Random::init();
	GameState::init(this);

	if (!(
		initSDL() &&
		initIMG() &&
		initTTF() &&
		createWindow() &&
		createRenderer()
		))
	{
		return;
	}

	// Sets the clear colour
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);

	// Pushes the first state onto the stack
	std::unique_ptr<GameState> startScreenState = std::make_unique<StartScreenState>();
	pushState(std::move(startScreenState));

#ifdef _DEBUG
	// Loads the information text
	m_InfoText.load("res/fonts/arial.ttf", "Time to Defend V0.1.0 | 0 FPS", 10, SDL_Color { 180, 180, 180, 255 }, m_Renderer);
#endif // _DEBUG

	// Resets the frame timer
	m_FrameTimer.reset();
	m_FrameCount = 0;
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

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				m_Running = false;
				break;
			}

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

#ifdef _DEBUG
	m_FrameCount += 1;

	if (m_FrameTimer.getElapsed() >= 1000.0)
	{
		// Creates the text
		std::string text = "Time to Defend V0.1.0 | ";
		text += std::to_string(m_FrameCount);
		text += " FPS";

		// Sets the text
		m_InfoText.setText(text.c_str());

		// Resets the timer
		m_FrameTimer.reset();
		m_FrameCount = 0;
	}
#endif // _DEBUG
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

#ifdef _DEBUG
	// Draws the information text
	m_InfoText.draw(m_WindowWidth - m_InfoText.getRect().w / 2 - 10, m_WindowHeight - m_InfoText.getRect().h / 2 - 10);
#endif // _DEBUG


	SDL_RenderPresent(m_Renderer);
}
