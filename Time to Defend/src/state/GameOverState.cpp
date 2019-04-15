#include "pch.h"

#include "GameOverState.h"

#include "Game.h"
#include "Settings.h"
#include "GameplayState.h"


GameOverState::GameOverState(bool won, std::string customMapName)
	: m_Won(won), m_CustomMapName(customMapName)
{
}


void GameOverState::onEnter()
{
	// Sets the text based upon the result of the game
	const char* text;
	SDL_Color colour;

	if (m_Won)
	{
		if (m_CustomMapName == "")
		{
			text = "Congratulations! You Won!";
		}

		else
		{
			m_GameOverTextString = "Congratulations! You Won (Map: ";
			m_GameOverTextString += m_CustomMapName;
			m_GameOverTextString += ")!";

			text = m_GameOverTextString.c_str();
		}

		colour = SDL_Color { 70, 255, 0, 255 };
	}

	else
	{
		if (m_CustomMapName == "")
		{
			text = "Game Over! You Lost!";
		}

		else
		{
			m_GameOverTextString = "Game Over! You Lost (Map: ";
			m_GameOverTextString += m_CustomMapName;
			m_GameOverTextString += ")!";

			text = m_GameOverTextString.c_str();
		}

		colour = SDL_Color { 255, 35, 0, 255 };
	}

	int textSize;

	// Text size is smaller to display entire map name
	if (m_CustomMapName == "")
	{
		textSize = 48;
	}

	else
	{
		textSize = 36;
	}

	// Creates the text
	m_GameOverText.load("res/fonts/arial.ttf", text, textSize, colour, s_Game->getRenderer());

	// Makes the text bold
	m_GameOverText.setStyle(TTF_STYLE_BOLD);

	m_OptionsMenu = new Menu(s_Game, {
		"Restart",
		"Exit"
	});

	SDL_SetRenderDrawColor(s_Game->getRenderer(), 0, 0, 0, 255);
}

void GameOverState::onExit()
{
	delete m_OptionsMenu;
	m_OptionsMenu = nullptr;
}

void GameOverState::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_r:
			std::unique_ptr<GameplayState> gameplayState;

			if (m_CustomMapName == "")
			{
				gameplayState = std::make_unique<GameplayState>();
			}

			else
			{
				std::string mapFilepath = "res/maps/custom/";
				mapFilepath += m_CustomMapName;
				mapFilepath += ".txt";

				gameplayState = std::make_unique<GameplayState>(m_CustomMapName, mapFilepath);
			}

			// Pops this state off the Game's stack
			s_Game->popState();

			// Pushes the gameplay state onto the stack
			s_Game->pushState(std::move(gameplayState));

			break;
		}

		break;

	case SDL_MOUSEBUTTONDOWN:
	{
		// Clicked "Restart"
		if (m_OptionsMenu->itemClicked() == 0)
		{
			std::unique_ptr<GameplayState> gameplayState;

			if (m_CustomMapName == "")
			{
				gameplayState = std::make_unique<GameplayState>();
			}

			else
			{
				std::string mapFilepath = "res/maps/custom/";
				mapFilepath += m_CustomMapName;
				mapFilepath += ".txt";

				gameplayState = std::make_unique<GameplayState>(m_CustomMapName, mapFilepath);
			}

			// Pops this state off the Game's stack
			s_Game->popState();

			// Pushes the gameplay state onto the stack
			s_Game->pushState(std::move(gameplayState));
		}

		// Clicked "Exit"
		else if (m_OptionsMenu->itemClicked() == 1)
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
	m_OptionsMenu->update();
}

void GameOverState::draw()
{
	// Draws text
	m_GameOverText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
	m_OptionsMenu->drawHorizontal(s_Game->getWindowWidth() * 8 / 20, s_Game->getWindowHeight() * 11 / 20, s_Game->getWindowWidth() * 4 / 20);
}
