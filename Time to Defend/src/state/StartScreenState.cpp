#include "pch.h"

#include "StartScreenState.h"

#include "Game.h"
#include "Settings.h"
#include "GameplayState.h"


void StartScreenState::onEnter()
{
	// Creates the text
	m_TtDText.load("res/fonts/arial.ttf", "Time to Defend!", 48, SDL_Color { 255, 70, 0, 255 }, s_Game->getRenderer());

	// Makes the text bold
	m_TtDText.setStyle(TTF_STYLE_BOLD);

	// Creates the main menu
	m_MainMenu = new Menu(s_Game, {
		"Play",
		"Instructions",
		"Level Editor",
		"Settings (Coming Soon...)"
	});

	// The instructions
	m_Instructions = new Paragraph(s_Game, {
		"Welcome to Time to Defend! Your goal is to try",
		"to defeat all the enemies that will be trying",
		"to invade your land.",
		"",
		"To rotate your tower, press <Left> or <Right>.",
		"To shoot, press <Space>. To switch which",
		"tower you are controlling, press <T>."
	});

	// Creates the back button
	m_BackMenu = new Menu(s_Game, {
		"<-- Back"
	});

	// Makes the background render black
	SDL_SetRenderDrawColor(s_Game->getRenderer(), 0, 0, 0, 255);
}

void StartScreenState::onExit()
{
	delete m_MainMenu;
	m_MainMenu = nullptr;

	delete m_Instructions;
	m_Instructions = nullptr;

	delete m_BackMenu;
	m_BackMenu = nullptr;
}

void StartScreenState::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RETURN:
			switch (m_ScreenState)
			{
			case ScreenState::MainScreen:
			{
				// Pops this state off the Game's stack
				s_Game->popState();

				// Pushes the gameplay state onto the stack
				std::unique_ptr<GameState> gameplayState = std::make_unique<GameplayState>();
				s_Game->pushState(std::move(gameplayState));

				break;
			}

			// Goes back to the main screen
			case ScreenState::Instructions:
				m_ScreenState = ScreenState::MainScreen;
				break;
			}

			break;

		case SDLK_h:
			// Goes to the instructions screen
			if (m_ScreenState == ScreenState::MainScreen)
			{
				m_ScreenState = ScreenState::Instructions;
			}

			break;
		}

		break;

	case SDL_MOUSEBUTTONDOWN:
		switch (m_ScreenState)
		{
		case ScreenState::MainScreen:
		{
			// Clicked "Play"
			if (m_MainMenu->itemClicked() == 0)
			{
				// Pops this state off the Game's stack
				s_Game->popState();

				// Pushes the gameplay state onto the stack
				std::unique_ptr<GameState> gameplayState = std::make_unique<GameplayState>();
				s_Game->pushState(std::move(gameplayState));
			}

			// Clicked "Instructions"
			else if (m_MainMenu->itemClicked() == 1)
			{
				m_ScreenState = ScreenState::Instructions;
			}

			// Clicked "Level Editor"
			else if (m_MainMenu->itemClicked() == 2)
			{
			#ifdef _WIN32

				if (ShellExecute(NULL, "open", "Time to Edit.exe", "", "", SW_SHOW))
				{
					LOG_INFO("Successfully started editor process.");
				}
				else
				{
					LOG_ERROR("Could not start editor process.");
				}

			#endif
			}

			// Clicked "Settings"
			else if (m_MainMenu->itemClicked() == 3)
			{
				// TODO: Switch to settings page once it's created
			}

			break;
		}

		case ScreenState::Instructions:
		{
			if (m_BackMenu->itemClicked() == 0)
			{
				m_ScreenState = ScreenState::MainScreen;
			}

			break;
		}
		}

		break;
	}
}

void StartScreenState::update()
{
	switch (m_ScreenState)
	{
	case ScreenState::MainScreen:
	{
		m_MainMenu->update();
		break;
	}

	case ScreenState::Instructions:
		m_BackMenu->update();
		break;
	}
}

void StartScreenState::draw()
{
	switch (m_ScreenState)
	{
	case ScreenState::MainScreen:
		// Draws text
		m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 5 / 20);
		m_MainMenu->draw(s_Game->getWindowHeight() * 8 / 20);

		break;

	case ScreenState::Instructions:
		// Draws text
		m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 5 / 20);
		m_Instructions->draw(s_Game->getWindowHeight() * 8 / 20);
		m_BackMenu->draw(s_Game->getWindowHeight() * 18 / 20);

		break;
	}
}
