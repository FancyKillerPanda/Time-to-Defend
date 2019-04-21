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
		NewProject,
		LoadProject,
	};

private:
	// The "Time to Edit!" header text
	Text m_TtEText;

	// The main menu
	Menu* m_MainMenu = nullptr;

	// The settings menu
	Menu* m_SettingsMenu;

	// Whether the instruction page has already loaded
	bool m_InstructionPageLoaded = false;

	// The instructions on how to use the editor
	Paragraph* m_Instructions;

	// The back button
	Menu* m_BackMenu;

	// The next button
	Menu* m_ContinueMenu;

	// The current screen
	ScreenState m_ScreenState = ScreenState::MainScreen;

	// The currently inputted project name and its labels
	InputText* m_ProjectName;
	Text m_NewProjectLabel;
	Text m_LoadProjectLabel;

	// The number of waves to spawn (user input)
	InputText* m_NumberOfWavesToSpawn;
	Text m_NumberOfWavesLabel;

	// The input text currently taking input
	InputText* m_InputCurrentlyHandling = nullptr;

private:
	void loadInstructions();

public:
	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};

