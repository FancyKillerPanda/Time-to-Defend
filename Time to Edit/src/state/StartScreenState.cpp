#include "pch.h"

#include "StartScreenState.h"

#include "Settings.h"
#include "EditorState.h"


void StartScreenState::onEnter()
{
	// Creates the text
	m_TtEText.load("res/fonts/arial.ttf", "Time to Edit!", 48, SDL_Color { 255, 70, 0, 255 }, s_Game->getRenderer());

	// Makes the text bold
	m_TtEText.setStyle(TTF_STYLE_BOLD);

	// Creates the main menu
	m_MainMenu = new Menu(s_Game, {
		"Start New",
		"Load (Coming Soon...)",
		"Instructions",
		"Settings"
	});

	// The settings
	m_SettingsMenu = new Menu(s_Game, {
		"Use <Ctrl-Click> to Remove Track: True"
	});

	// The instructions
	m_Instructions = new Paragraph(s_Game, {
		"Welcome to Time to Edit! This is a level editor",
		"for Time to Defend!",
		"",
		"To change a tile between grass and track,",
		"simply click on it (or click and drag for",
		"multiple tiles). If you want to see grid",
		"lines, press <G>."
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

				// Pushes the editor state onto the stack
				std::unique_ptr<GameState> editorState = std::make_unique<EditorState>();
				s_Game->pushState(std::move(editorState));

				break;
			}

			// Goes back to the main screen
			case ScreenState::Instructions:
			case ScreenState::Settings:
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
			// Clicked "Start New"
			if (m_MainMenu->itemClicked() == 0)
			{
				// Pops this state off the Game's stack
				s_Game->popState();

				// Pushes the editor state onto the stack
				std::unique_ptr<GameState> editorState = std::make_unique<EditorState>();
				s_Game->pushState(std::move(editorState));
			}

			// Clicked "Load"
			else if (m_MainMenu->itemClicked() == 1)
			{
				// TODO: Load previous map
			}

			// Clicked "Instructions"
			else if (m_MainMenu->itemClicked() == 2)
			{
				m_ScreenState = ScreenState::Instructions;
			}

			// Clicked "Settings
			else if (m_MainMenu->itemClicked() == 3)
			{
				m_ScreenState = ScreenState::Settings;
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

		case ScreenState::Settings:
		{
			if (m_SettingsMenu->itemClicked() == 0)
			{
				if (m_CtrlClickRemoveTrack)
				{
					m_SettingsMenu->getItems()[0]->setText("Use <Ctrl-Click> to Remove Track: False");
				}

				else
				{
					m_SettingsMenu->getItems()[0]->setText("Use <Ctrl-Click> to Remove Track: True");
				}

				m_CtrlClickRemoveTrack = !m_CtrlClickRemoveTrack;
			}
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

	case ScreenState::Settings:
		m_SettingsMenu->update();
		break;
	}
}

void StartScreenState::draw()
{
	switch (m_ScreenState)
	{
	case ScreenState::MainScreen:
		// Draws text
		m_TtEText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 5 / 20);
		m_MainMenu->draw(s_Game->getWindowHeight() * 8 / 20);

		break;

	case ScreenState::Instructions:
		// Draws text
		m_TtEText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 5 / 20);
		m_Instructions->draw(s_Game->getWindowHeight() * 8 / 20);
		m_BackMenu->draw(s_Game->getWindowHeight() * 18 / 20);

		break;

	case ScreenState::Settings:
		// Draws text
		m_TtEText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 8 / 20);
		m_SettingsMenu->draw(s_Game->getWindowHeight() * 11 / 20);
	}
}
