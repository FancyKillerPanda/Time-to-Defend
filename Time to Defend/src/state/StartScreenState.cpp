#include "pch.h"

#include "StartScreenState.h"

#include "Game.h"
#include "Settings.h"
#include "GameplayState.h"


void StartScreenState::onEnter()
{
	//*
	// The instructions
	const char* instructionText =
"Welcome to Time to Defend! Your goal is\n\
to try to defeat all the enemies that will\n\
be trying to invade your land.\n\n\
To rotate your tower, press <Left> or <Right>\n\
To shoot, press <Space>.\n\
To switch which tower you are controlling,\n\
press <T>.";
	//*/

	// Creates the text
	m_TtDText.load("res/fonts/arial.ttf", "Time to Defend!", 48, SDL_Color { 255, 70, 0, 255 }, s_Game->getRenderer());
	m_InfoText.load("res/fonts/arial.ttf", "Press <H> for instructions or <Enter> to start.", 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText.load("res/fonts/arial.ttf", instructionText, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());

	// Makes the background render black
	SDL_SetRenderDrawColor(s_Game->getRenderer(), 0, 0, 0, 255);
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
	}
}

void StartScreenState::draw()
{
	switch (m_ScreenState)
	{
	case ScreenState::MainScreen:
		// Draws text
		m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
		m_InfoText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 11 / 20);

		break;

	case ScreenState::Instructions:
		// Draws text
		m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 4 / 20);
		m_InstructionsText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 6 / 20);

		break;
	}
}
