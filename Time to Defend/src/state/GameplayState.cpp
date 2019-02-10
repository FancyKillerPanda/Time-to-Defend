#include "GameplayState.h"

#include "Game.h"


void GameplayState::onEnter()
{
	m_CurrentMap.load("res/maps/Level_1.txt");
	m_TestTexture.load("res/txrs/Test.png", s_Game->getRenderer());
}

void GameplayState::onExit()
{
}

void GameplayState::handleEvent(SDL_Event& event)
{
}

void GameplayState::update()
{
}

void GameplayState::draw()
{
	m_CurrentMap.draw(s_Game->getRenderer());
	SDL_RenderCopy(s_Game->getRenderer(), m_TestTexture.getTexture(), nullptr, &m_TestTexture.getRect());
}
