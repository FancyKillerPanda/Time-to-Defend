#pragma once

#include "pch.h"

#include "state/BaseGameState.h"

#include "gfx/Text.h"
#include "gfx/Menu.h"


class LevelPassedState : public GameState
{
private:
	Text m_LevelPassedText;
	Menu* m_OptionsMenu;

	unsigned int m_Level;

public:
	LevelPassedState(unsigned int level);

	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
