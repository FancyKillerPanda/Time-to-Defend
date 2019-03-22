#pragma once

#include "pch.h"

#include "state/BaseGameState.h"

#include "gfx/Text.h"


class LevelPassedState : public GameState
{
private:
	Text m_LevelPassedText;
	Text m_ContinueText;
	Text m_RestartText;
	Text m_ExitText;

	// Whether currently highlighting text
	bool m_HighlightingContinueText = false;
	bool m_HighlightingRestartText = false;
	bool m_HighlightingExitText = false;

	unsigned int m_Level;

public:
	LevelPassedState(unsigned int level);

	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
