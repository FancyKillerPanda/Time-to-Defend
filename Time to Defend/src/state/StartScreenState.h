#pragma once

#include "pch.h"

#include "state/BaseGameState.h"

#include "gfx/Text.h"
#include "gfx/Menu.h"


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

	// The main menu
	Menu* m_MainMenu = nullptr;

	// Whether the instruction page has already loaded
	bool m_InstructionPageLoaded = false;

	// The instructions on how to play
	Text m_InstructionsText_0;
	Text m_InstructionsText_1;
	Text m_InstructionsText_2;
	Text m_InstructionsText_3;
	Text m_InstructionsText_4;
	Text m_InstructionsText_5;

	Menu* m_BackMenu;

	// The current screen
	ScreenState m_ScreenState = ScreenState::MainScreen;

private:
	void loadInstructionPage();

public:
	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};

