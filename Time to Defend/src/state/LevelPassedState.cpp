#include "pch.h"

#include "LevelPassedState.h"

#include "Game.h"
#include "GameplayState.h"


LevelPassedState::LevelPassedState(unsigned int level)
	: m_Level(level)
{
}


void LevelPassedState::onEnter()
{
	std::string text = "Level ";
	text += std::to_string(m_Level);
	text += " Passed!";

	// Creates the text
	m_LevelPassedText.load("res/fonts/arial.ttf", text.c_str(), 48, SDL_Color { 70, 255, 0, 255 }, s_Game->getRenderer());

	// Makes the text bold
	m_LevelPassedText.setStyle(TTF_STYLE_BOLD);

	m_OptionsMenu = new Menu(s_Game, {
		"Continue",
		"Restart",
		"Exit"
	});


	SDL_SetRenderDrawColor(s_Game->getRenderer(), 0, 0, 0, 255);
}

void LevelPassedState::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RETURN:
			s_Game->popState();
		}

		break;

	case SDL_MOUSEBUTTONDOWN:
	{
		// Clicked "Continue"
		if (m_OptionsMenu->itemClicked() == 0)
		{
			// Pops this state off the Game's stack
			s_Game->popState();
		}

		// Clicked "Restart"
		else if (m_OptionsMenu->itemClicked() == 1)
		{
			// Pops both this state off the stack
			s_Game->popState();

			// Replaces the top state (GameplayState) with a new copy
			s_Game->replaceTopState<GameplayState>();
		}

		// Clicked "Exit"
		else if (m_OptionsMenu->itemClicked() == 2)
		{
			// Stops the game from running
			s_Game->setRunning(false);
		}

		break;
	}
	}
}

void LevelPassedState::update()
{
	m_OptionsMenu->update();
}

void LevelPassedState::draw()
{
	m_LevelPassedText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
	m_OptionsMenu->drawHorizontal(s_Game->getWindowWidth() * 6 / 20, s_Game->getWindowHeight() * 11 / 20, s_Game->getWindowWidth() * 4 / 20);
}
