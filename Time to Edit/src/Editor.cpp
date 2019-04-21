#include "pch.h"

#include "Editor.h"

#include "utils/Log.h"
#include "utils/Random.h"
#include "Settings.h"
#include "state/BaseGameState.h"
#include "state/StartScreenState.h"
#include "GameSettings.h"


Editor::Editor()
	: Application(960, 540, "Time to Edit")
{
	// Initialises other parts of the editor
	Log::init("TTELOG");
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

	// Sets the clear colour, the blend mode, and starts keyboard text input
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
	SDL_StartTextInput();

	// Sets the window icon
	SDL_Surface* iconSurface = IMG_Load("res/txrs/TtE Icon.png");

	if (iconSurface)
	{
		SDL_SetWindowIcon(m_Window, iconSurface);
		LOG_INFO("Set window icon.");
	}

	else
	{
		LOG_ERROR("Could not set window icon.");
	}

	// Initialises the settings
	readSettings();

	// Pushes the first state onto the stack
	pushState<StartScreenState>();

#ifdef _DEBUG
	// Loads the information text
	m_InfoText.load(DEFAULT_FONT_PATH, "Time to Edit V0.1.0 | 0 FPS", 10, SDL_Color { 180, 180, 180, 255 }, m_Renderer);
#endif // _DEBUG
}

Editor::~Editor()
{
	// Saves settings to a file
	saveSettings();

	delete settings;
	settings = nullptr;
}


void Editor::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			// Makes sure there is a state in the stack
			if (m_GameStates.empty())
			{
				LOG_WARNING("Could not handle actions on exit for game state (empty stack).");
			}

			else
			{
				// Lets the state take its actions
				if (!m_GameStates.back()->actionsOnExit())
				{
					m_Running = false;
				}
			}

			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				// Makes sure there is a state in the stack
				if (m_GameStates.empty())
				{
					LOG_WARNING("Could not handle actions on exit for game state (empty stack).");
				}

				else
				{
					// Lets the state take its actions
					if (!m_GameStates.back()->actionsOnExit())
					{
						m_Running = false;
					}
				}

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

void Editor::update()
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
		std::string text = "Time to Edit V0.1.0 | ";
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

void Editor::draw()
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

	// Displays the screen
	SDL_RenderPresent(m_Renderer);
}


void Editor::saveSettings()
{
	// Opens the file to write in
	std::fstream settingsFile;
	settingsFile.open("res/TtESettings.txt", std::fstream::out | std::fstream::trunc);

	// Error checking
	if (!settingsFile)
	{
		LOG_ERROR("Could not open file to save settings to.");
		return;
	}

	// Puts the settings into the file
	settingsFile << (int) settings->ctrlClickToRemoveTrack << '\n';

	// Closes the file
	settingsFile.close();
}

void Editor::readSettings()
{
	// Sets the settings to their default value
	settings = new GameSettings();

	// Opens the file to read from
	std::fstream settingsFile;
	settingsFile.open("res/TtESettings.txt", std::fstream::in);

	// Error checking
	if (!settingsFile)
	{
		LOG_WARNING("Could not open file to read settings from.");
		return;
	}

	std::string nextVal;

	// Assigns values to the settings
	try
	{
		if (std::getline(settingsFile, nextVal))
		{
			settings->ctrlClickToRemoveTrack = (bool) std::stoi(nextVal);
		}
	}

	catch (const std::exception&)
	{
		LOG_WARNING("Failed to set editor settings. File most likely contains non-integers.");
	}

	// Closes the file
	settingsFile.close();
}
