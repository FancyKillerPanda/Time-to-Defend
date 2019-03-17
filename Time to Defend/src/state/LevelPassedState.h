#pragma once

#include "pch.h"

#include "BaseGameState.h"

#include "gfx/Text.h"


class LevelPassedState : public GameState
{
private:
	Text m_LevelPassedText;
	Text m_InfoText;

	unsigned int m_Level;

public:
	LevelPassedState(unsigned int level);

	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void draw() override;
};
