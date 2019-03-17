#include "pch.h"

#include "LevelPassedState.h"

#include "Game.h"


void LevelPassedState::onEnter()
{
	// Creates the text
	m_LevelPassedText.load("res/fonts/arial.ttf", "Level Passed!", 48, SDL_Color { 70, 255, 0, 255 }, s_Game->getRenderer());
	m_InfoText.load("res/fonts/arial.ttf", "Press <Enter> to continue or <Escape> to exit!", 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());

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
	}
}

void LevelPassedState::draw()
{
	m_LevelPassedText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
	m_InfoText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 11 / 20);
}
