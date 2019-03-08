#include "pch.h"

#include "GameOverState.h"

#include "Game.h"
#include "Settings.h"


void GameOverState::onEnter()
{
	// Creates the text
	m_GameOverText = new Text("res/fonts/arial.ttf", "Game Over!", 48, SDL_Color { 0, 0, 0, 255 }, s_Game->getRenderer());
}

void GameOverState::onExit()
{
	// Destroys the text
	delete m_GameOverText;
	m_GameOverText = nullptr;
}

void GameOverState::draw()
{
	// Draws text
	m_GameOverText->draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() / 2);
}
