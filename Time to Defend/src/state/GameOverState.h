#pragma once

#include "pch.h"

#include "BaseGameState.h"

#include "gfx/Text.h"


class GameOverState : public GameState
{
private:
	Text m_GameOverText;
	Text m_InfoText;

	// Whether the game was won
	bool m_Won;

public:
	GameOverState(bool won);

	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void draw() override;
};
