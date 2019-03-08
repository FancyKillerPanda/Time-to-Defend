#include "pch.h"

#include "LevelPassedState.h"

#include "Game.h"


void LevelPassedState::onEnter()
{
	// Creates the text
	m_LevelPassedText.load("res/fonts/arial.ttf", "Level Passed!", 48, SDL_Color { 0, 0, 0, 255 }, s_Game->getRenderer());
	m_InfoText.load("res/fonts/arial.ttf", "Press <Enter> to continue or <Escape> to exit!", 28, SDL_Color { 0, 0, 0, 255 }, s_Game->getRenderer());
}

void LevelPassedState::draw()
{
	m_LevelPassedText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
	m_InfoText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 11 / 20);
}
