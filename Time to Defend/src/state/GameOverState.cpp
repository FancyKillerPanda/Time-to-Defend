#include "pch.h"

#include "GameOverState.h"

#include "Game.h"
#include "Settings.h"
#include "GameplayState.h"


GameOverState::GameOverState(bool won)
	: m_Won(won)
{
}


void GameOverState::onEnter()
{
	// Sets the text based upon the result of the game
	const char* text;
	SDL_Color colour;

	if (m_Won)
	{
		text = "Congratulations! You Won!";
		colour = SDL_Color { 70, 255, 0, 255 };
	}

	else
	{
		text = "Game Over! You Lost!";
		colour = SDL_Color { 255, 35, 0, 255 };
	}

	// Creates the text
	m_GameOverText.load("res/fonts/arial.ttf", text, 48, colour, s_Game->getRenderer());
	m_RestartText.load("res/fonts/arial.ttf", "Restart", 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());
	m_ExitText.load("res/fonts/arial.ttf", "Exit", 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());

	// Makes the text bold
	m_GameOverText.setStyle(TTF_STYLE_BOLD);
	m_RestartText.setStyle(TTF_STYLE_BOLD);
	m_ExitText.setStyle(TTF_STYLE_BOLD);

	SDL_SetRenderDrawColor(s_Game->getRenderer(), 0, 0, 0, 255);
}

void GameOverState::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_r:
			// Pops this state off the Game's stack
			s_Game->popState();

			// Pushes the gameplay state onto the stack
			std::unique_ptr<GameState> gameplayState = std::make_unique<GameplayState>();
			s_Game->pushState(std::move(gameplayState));

			break;
		}

		break;

	case SDL_MOUSEBUTTONDOWN:
	{
		int mouseX;
		int mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		if (m_RestartText.rectCollides(mouseX, mouseY))
		{
			// Pops this state off the Game's stack
			s_Game->popState();

			// Pushes the gameplay state onto the stack
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

void GameOverState::update()
{
	// Gets the mouse position
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	// Highlights the restart text
	if (m_RestartText.rectCollides(mouseX, mouseY))
	{
		if (!m_HighlightingRestartText)
		{
			m_RestartText.setColour(SDL_Color { 255, 255, 0, 255 });
			m_HighlightingRestartText = true;
		}
	}

	// Highlights the exit text
	else if (m_ExitText.rectCollides(mouseX, mouseY))
	{
		if (!m_HighlightingExitText)
		{
			m_ExitText.setColour(SDL_Color { 255, 255, 0, 255 });
			m_HighlightingExitText = true;
		}
	}

	// Stops highlighting both text
	else
	{
		if (m_HighlightingRestartText || m_HighlightingExitText)
		{
			m_HighlightingRestartText = false;
			m_HighlightingExitText = false;

			m_RestartText.setColour(SDL_Color { 90, 160, 30, 255 });
			m_ExitText.setColour(SDL_Color { 90, 160, 30, 255 });
		}
	}
}

void GameOverState::draw()
{
	// Draws text
	m_GameOverText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
	m_RestartText.draw(s_Game->getWindowWidth() * 8 / 20, s_Game->getWindowHeight() * 11 / 20);
	m_ExitText.draw(s_Game->getWindowWidth() * 12 / 20, s_Game->getWindowHeight() * 11 / 20);
}
