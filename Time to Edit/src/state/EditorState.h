#pragma once

#include "pch.h"

#include "state/BaseGameState.h"

#include "gfx/Map.h"
#include "gfx/Menu.h"
#include "gfx/InputText.h"


class EditorState : public GameState
{
	enum class ScreenState
	{
		Editor,
		SaveScreen,
		ChangeWavesToSpawnScreen,
	};

private:
	// Map currently being edited
	Map m_MapEditing;

	bool m_MouseButtonDown = false;
	bool m_TurnToTrack = true;

	bool m_ShowGrid = false;

	// Whether the user is currently in the process of placing a tower
	bool m_CurrentlyPlacingTower = false;

	// The current location of the "hovering" tower
	Position m_HoveringTowerLocation = { -1, -1 };

	// The tower drawn when the user is deciding where to place it
	Tower* m_TowerToDraw;

	// Whether the tower is currently conflicting with an object
	bool m_TowerConflictingWithObject = false;

	// The name of the project
	std::string m_ProjectName;

	// The current state of the screen
	ScreenState m_ScreenState;

	// The options (Yes, No, Cancel)
	Menu* m_OptionsMenu;

	// The text asking if the user wants to save
	Text m_SaveQuestion;

	// The number of waves that need to be spawned
	unsigned int m_NumberOfWavesToSpawn;

	// Whether the map is being loaded from file
	bool m_Load = false;

	// The filepath for the map
	std::string m_MapFilepath;

	// The number of waves to spawn (user input)
	InputText* m_NumberOfWavesToSpawnText;
	Text m_NumberOfWavesLabel;

private:
	// Handles when a cell is clicked
	void clickCell();

	// Gets the position of the cell under the mouse
	Position getCellUnderMouse();

	// Saves the map
	void saveMap();

	// Checks if the 2x2 area of the tower conflicts with an object
	bool towerConflicts(Tower* tower);

	// Checks if the map currently needs saving
	bool needToSave();

public:
	EditorState(std::string projectName);
	EditorState(std::string projectName, unsigned int numberOfWavesToSpawn);

	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;

	bool actionsOnExit() override;
};
