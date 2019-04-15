#pragma once

#include "pch.h"

#include "state/BaseGameState.h"

#include "gfx/Text.h"
#include "gfx/Menu.h"


class GameOverState : public GameState
{
private:
	Text m_GameOverText;
	Menu* m_OptionsMenu;
	std::string m_GameOverTextString;

	// Whether the game was won
	bool m_Won;

	// The custom map's name (empty if not custom)
	std::string m_CustomMapName = "";

public:
	GameOverState(bool won, std::string customMapName);

	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
