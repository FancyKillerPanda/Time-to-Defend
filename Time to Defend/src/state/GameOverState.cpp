#include "pch.h"

#include "GameOverState.h"

#include "Game.h"
#include "Settings.h"
#include "GameplayState.h"


void GameOverState::onEnter()
{
	// Creates the text
	m_GameOverText.load("res/fonts/arial.ttf", "Game Over!", 48, SDL_Color { 255, 35, 0, 255 }, s_Game->getRenderer());
	m_InfoText.load("res/fonts/arial.ttf", "Press <Escape> to exit or <R> to restart!", 28, SDL_Color { 90, 160, 0, 255 }, s_Game->getRenderer());

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
			std::unique_ptr<GameState> gameOverState = std::make_unique<GameplayState>();
			s_Game->pushState(std::move(gameOverState));

			break;
		}

		break;
	}
}

void GameOverState::draw()
{
	// Draws text
	m_GameOverText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
	m_InfoText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 11 / 20);
}
