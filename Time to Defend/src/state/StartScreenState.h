#pragma once

#include "pch.h"

#include "BaseGameState.h"

#include "gfx/Text.h"


class StartScreenState : public GameState
{
private:
	// The "Time to Defend!" header text
	Text m_TtDText;
	// Information about what actions the user can take
	Text m_InfoText;

public:
	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void draw() override;
};

