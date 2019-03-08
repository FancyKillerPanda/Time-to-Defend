#pragma once

#include "pch.h"

#include "BaseGameState.h"

#include "gfx/Text.h"


class LevelPassedState : public GameState
{
private:
	Text m_LevelPassedText;
	Text m_InfoText;

public:
	void onEnter() override;

	void draw() override;
};
