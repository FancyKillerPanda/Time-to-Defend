#include "pch.h"

#include "GameOverState.h"

#include "Game.h"
#include "Settings.h"


void GameOverState::onEnter()
{
	// Creates the text
	m_GameOverText = new Text("res/fonts/arial.ttf", "Game Over!", 48, SDL_Color { 0, 0, 0, 255 }, s_Game->getRenderer());
	m_InfoText = new Text("res/fonts/arial.ttf", "Press <Escape> to exit or <R> to restart!", 28, SDL_Color { 0, 0, 0, 255 }, s_Game->getRenderer());
}

void GameOverState::onExit()
{
	// Destroys text objects
	delete m_GameOverText;
	m_GameOverText = nullptr;
	delete m_InfoText;
	m_InfoText = nullptr;
}

void GameOverState::draw()
{
	// Draws text
	m_GameOverText->draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
	m_InfoText->draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 11 / 20);
}
