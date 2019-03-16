#include "pch.h"

#include "StartScreenState.h"

#include "Game.h"
#include "Settings.h"
#include "GameplayState.h"


void StartScreenState::onEnter()
{
	// Creates the text
	m_TtDText.load("res/fonts/arial.ttf", "Time to Defend!", 48, SDL_Color { 255, 70, 0, 255 }, s_Game->getRenderer());
	m_InfoText.load("res/fonts/arial.ttf", "Press <H> for instructions or <Enter> to start.", 28, SDL_Color { 70, 255, 0, 255 }, s_Game->getRenderer());

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
			// Pops this state off the Game's stack
			s_Game->popState();

			// Pushes the gameplay state onto the stack
			std::unique_ptr<GameState> gameplayState = std::make_unique<GameplayState>();
			s_Game->pushState(std::move(gameplayState));

			break;
		}

		break;
	}
}

void StartScreenState::draw()
{
	// Draws text
	m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
	m_InfoText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 11 / 20);
}
