#include "pch.h"

#include "StartScreenState.h"

#include "Game.h"
#include "Settings.h"
#include "GameplayState.h"


void StartScreenState::onEnter()
{
	// Creates the text
	m_TtDText.load("res/fonts/arial.ttf", "Time to Defend!", 48, SDL_Color { 255, 70, 0, 255 }, s_Game->getRenderer());
	m_InfoText.load("res/fonts/arial.ttf", "Press <H> for instructions or <Enter> to start.", 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());

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
				loadInstructionText();
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
		m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 5 / 20);
		m_InstructionsText_0.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 8 / 20);
		m_InstructionsText_1.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
		m_InstructionsText_2.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 10 / 20);
		m_InstructionsText_3.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 12 / 20);
		m_InstructionsText_4.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 13 / 20);
		m_InstructionsText_5.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 14 / 20);

		break;
	}
}

void StartScreenState::loadInstructionText()
{
	// The instructions
	const char* instructionText_0 = "Welcome to Time to Defend! Your goal is to try";
	const char* instructionText_1 = "to defeat all the enemies that will be trying";
	const char* instructionText_2 = "to invade your land.";
	const char* instructionText_3 = "To rotate your tower, press <Left> or <Right>.";
	const char* instructionText_4 = "To shoot, press <Space>. To switch which";
	const char* instructionText_5 = "tower you are controlling, press <T>.";

	m_InstructionsText_0.load("res/fonts/arial.ttf", instructionText_0, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_1.load("res/fonts/arial.ttf", instructionText_1, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_2.load("res/fonts/arial.ttf", instructionText_2, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_3.load("res/fonts/arial.ttf", instructionText_3, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_4.load("res/fonts/arial.ttf", instructionText_4, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_InstructionsText_5.load("res/fonts/arial.ttf", instructionText_5, 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
}
