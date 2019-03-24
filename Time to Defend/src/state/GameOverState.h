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

	// Whether the game was won
	bool m_Won;

public:
	GameOverState(bool won);

	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
