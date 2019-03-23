#pragma once

#include "pch.h"

#include "state/BaseGameState.h"

#include "gfx/Map.h"


class EditorState : public GameState
{
private:
	// Map currently being edited
	Map m_MapEditing;

private:
	// Handles when a cell is clicked
	void clickCell();

public:
	void onEnter() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
