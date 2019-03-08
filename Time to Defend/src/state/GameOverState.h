#pragma once

#include "pch.h"

#include "BaseGameState.h"

#include "gfx/Text.h"


class GameOverState : public GameState
{
private:
	Text* m_GameOverText;
	Text* m_InfoText;

public:
	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void draw() override;
};
