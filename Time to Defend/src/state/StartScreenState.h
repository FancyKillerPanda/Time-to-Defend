#pragma once

#include "pch.h"

#include "BaseGameState.h"

#include "gfx/Text.h"


class StartScreenState : public GameState
{
	enum class ScreenState
	{
		MainScreen,
		Instructions,
	};

private:
	// The "Time to Defend!" header text
	Text m_TtDText;
	// Information about what actions the user can take
	Text m_InfoText;

	// The instructions on how to play
	Text m_InstructionsText_0;
	Text m_InstructionsText_1;
	Text m_InstructionsText_2;
	Text m_InstructionsText_3;
	Text m_InstructionsText_4;
	Text m_InstructionsText_5;

	// The current screen
	ScreenState m_ScreenState = ScreenState::MainScreen;

private:
	void loadInstructionText();

public:
	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void draw() override;
};

