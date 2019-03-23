#include "pch.h"

#include "EditorState.h"


void EditorState::onEnter()
{
	m_MapEditing.load(s_Game, nullptr);
}

void EditorState::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		// Handles clicking on a cell
		clickCell();
		break;
	}
}

void EditorState::update()
{
}

void EditorState::draw()
{
	m_MapEditing.draw();
}


void EditorState::clickCell()
{
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int row = std::floor(mouseY / CELL_SIZE);
	int col = std::floor(mouseX / CELL_SIZE);

	m_MapEditing.getCoords()[row][col] = 'P';
};
