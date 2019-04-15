#pragma once

#include "pch.h"

#include "state/BaseGameState.h"

#include "gfx/Map.h"
#include "gfx/Menu.h"


class EditorState : public GameState
{
	enum class ScreenState
	{
		Editor,
		SaveScreen,
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

private:
	// Handles when a cell is clicked
	void clickCell();

	// Gets the position of the cell under the mouse
	Position getCellUnderMouse();

	// Saves the map
	void saveMap();

	// Checks if the 2x2 area of the tower conflicts with an object
	bool towerConflicts(Tower* tower);

public:
	EditorState(std::string projectName);

	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;

	void actionsOnExit() override;
};
