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
	m_ContinueText.load("res/fonts/arial.ttf", "Continue", 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_RestartText.load("res/fonts/arial.ttf", "Restart", 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_ExitText.load("res/fonts/arial.ttf", "Exit", 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());

	// Makes the text bold
	m_LevelPassedText.setStyle(TTF_STYLE_BOLD);

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
		int mouseX;
		int mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		if (m_ContinueText.rectCollides(mouseX, mouseY))
		{
			// Pops this state off the Game's stack
			s_Game->popState();
		}

		else if (m_RestartText.rectCollides(mouseX, mouseY))
		{
			// Pops both this and the gameplay state off the stack
			s_Game->popState();
			s_Game->popState();

			// Pushes new gameplay state onto stack
			std::unique_ptr<GameState> gameplayState = std::make_unique<GameplayState>();
			s_Game->pushState(std::move(gameplayState));
		}

		else if (m_ExitText.rectCollides(mouseX, mouseY))
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
	// Gets the mouse position
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	// Highlights the continue text
	if (m_ContinueText.rectCollides(mouseX, mouseY))
	{
		if (!m_HighlightingContinueText)
		{
			m_ContinueText.setStyle(TTF_STYLE_BOLD, false);
			m_ContinueText.setColour(SDL_Color { 255, 255, 0, 255 });
			m_HighlightingContinueText = true;
		}
	}

	// Highlights the restart text
	else if (m_RestartText.rectCollides(mouseX, mouseY))
	{
		if (!m_HighlightingRestartText)
		{
			m_RestartText.setStyle(TTF_STYLE_BOLD, false);
			m_RestartText.setColour(SDL_Color { 255, 255, 0, 255 });
			m_HighlightingRestartText = true;
		}
	}

	// Highlights the exit text
	else if (m_ExitText.rectCollides(mouseX, mouseY))
	{
		if (!m_HighlightingExitText)
		{
			m_ExitText.setStyle(TTF_STYLE_BOLD, false);
			m_ExitText.setColour(SDL_Color { 255, 255, 0, 255 });
			m_HighlightingExitText = true;
		}
	}

	// Stops highlighting both text
	else
	{
		if (m_HighlightingContinueText || m_HighlightingRestartText || m_HighlightingExitText)
		{
			m_HighlightingContinueText = false;
			m_HighlightingRestartText = false;
			m_HighlightingExitText = false;

			m_ContinueText.setStyle(TTF_STYLE_NORMAL, false);
			m_ContinueText.setColour(SDL_Color { 90, 160, 30, 255 });

			m_RestartText.setStyle(TTF_STYLE_NORMAL, false);
			m_RestartText.setColour(SDL_Color { 90, 160, 30, 255 });

			m_ExitText.setStyle(TTF_STYLE_NORMAL, false);
			m_ExitText.setColour(SDL_Color { 90, 160, 30, 255 });
		}
	}
}

void LevelPassedState::draw()
{
	m_LevelPassedText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
	m_ContinueText.draw(s_Game->getWindowWidth() * 5 / 20, s_Game->getWindowHeight() * 11 / 20);
	m_RestartText.draw(s_Game->getWindowWidth() * 10 / 20, s_Game->getWindowHeight() * 11 / 20);
	m_ExitText.draw(s_Game->getWindowWidth() * 15 / 20, s_Game->getWindowHeight() * 11 / 20);
}
