#pragma once

#include "pch.h"

#include "state/BaseGameState.h"

#include "gfx/Text.h"
#include "gfx/Menu.h"
#include "gfx/Paragraph.h"
#include "gfx/InputText.h"


class StartScreenState : public GameState
{
	enum class ScreenState
	{
		MainScreen,
		Instructions,
		Settings,
		LoadProject,
	};

private:
	// The "Time to Defend!" header text
	Text m_TtDText;

	// The main menu
	Menu* m_MainMenu = nullptr;

	// The load project next button
	Menu* m_LoadProjectMenu = nullptr;

	// Whether the instruction page has already loaded
	bool m_InstructionPageLoaded = false;

	// The instructions on how to play
	Paragraph* m_Instructions;

	// The settings menu
	Menu* m_SettingsMenu;

	// The back button
	Menu* m_BackMenu;

	// The current screen
	ScreenState m_ScreenState = ScreenState::MainScreen;

	// The currently inputted project name to load
	InputText* m_ProjectName;
	Text m_LoadProjectLabel;

private:
	void loadInstructions();

public:
	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};

