#pragma once

#include "pch.h"

#include "BaseGameState.h"

#include "gfx/Text.h"


class GameOverState : public GameState
{
private:
	Text* m_GameOverText;

public:
	void onEnter() override;
	void onExit() override;

	void draw() override;
};
