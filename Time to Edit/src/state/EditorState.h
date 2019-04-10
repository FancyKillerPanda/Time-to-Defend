#pragma once

#include "pch.h"

#include "state/BaseGameState.h"

#include "gfx/Map.h"


class EditorState : public GameState
{
private:
	// Map currently being edited
	Map m_MapEditing;

	bool m_MouseButtonDown = false;
	bool m_TurnToTrack = true;

	bool m_ShowGrid = false;
	bool m_CtrlClickRemoveTrack = true;

private:
	// Handles when a cell is clicked
	void clickCell();

	// Gets the position of the cell under the mouse
	Position getCellUnderMouse();

	// Saves the map
	void saveMap();

public:
	EditorState(bool ctrlClickRemoveTrack);

	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
