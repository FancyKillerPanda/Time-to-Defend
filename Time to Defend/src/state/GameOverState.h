#pragma once

#include "pch.h"

#include "BaseGameState.h"

#include "gfx/Text.h"


class GameOverState : public GameState
{
private:
	Text m_GameOverText;
	Text m_RestartText;
	Text m_ExitText;

	// Whether currently highlighting text
	bool m_HighlightingRestartText = false;
	bool m_HighlightingExitText = false;

	// Whether the game was won
	bool m_Won;

public:
	GameOverState(bool won);

	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
