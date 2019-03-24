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
				m_ScreenState = ScreenState::MainScreen;
				break;
			}

			break;

		case SDLK_h:
			// Goes to the instructions screen
			if (m_ScreenState == ScreenState::MainScreen)
			{
				m_ScreenState = ScreenState::Instructions;
				loadInstructionPage();
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
				loadInstructionPage();
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
		m_TtEText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 6 / 20);
		m_MainMenu->draw(s_Game->getWindowHeight() * 9 / 20);

		break;

	case ScreenState::Instructions:
		// Draws text
		m_TtEText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 5 / 20);
		m_InstructionsText_0.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 8 / 20);
		m_InstructionsText_1.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
		m_InstructionsText_2.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 11 / 20);
		m_InstructionsText_3.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 12 / 20);
		m_InstructionsText_4.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 13 / 20);
		m_InstructionsText_5.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 14 / 20);

		m_BackMenu->draw(s_Game->getWindowHeight() * 18 / 20);

		break;
	}
}

void StartScreenState::loadInstructionPage()
{
	if (m_InstructionPageLoaded)
	{
		return;
	}

	// The instructions
	const char* instructionText_0 = "Welcome to Time to Edit! This is a level editor";
	const char* instructionText_1 = "for Time to Defend!";
	const char* instructionText_2 = "To change a tile between grass and track,";
	const char* instructionText_3 = "simply click on it (or click and drag for";
	const char* instructionText_4 = "multiple tiles). If you want to see grid";
	const char* instructionText_5 = "lines, press <G>.";

	m_InstructionsText_0.load("res/fonts/arial.ttf", instructionText_0, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_1.load("res/fonts/arial.ttf", instructionText_1, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_2.load("res/fonts/arial.ttf", instructionText_2, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_3.load("res/fonts/arial.ttf", instructionText_3, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_4.load("res/fonts/arial.ttf", instructionText_4, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_5.load("res/fonts/arial.ttf", instructionText_5, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());

	m_InstructionPageLoaded = true;
}
