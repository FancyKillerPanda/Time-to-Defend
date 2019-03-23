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
	{
		m_MouseButtonDown = true;
		Position cell = getCellUnderMouse();

		if (m_MapEditing.getCoords()[cell.row][cell.col] == '.')
		{
			m_TurnToTrack = true;
		}

		else
		{
			m_TurnToTrack = false;
		}

		break;
	}

	case SDL_MOUSEBUTTONUP:
		m_MouseButtonDown = false;
		break;
	}
}

void EditorState::update()
{
	if (m_MouseButtonDown)
	{
		clickCell();
	}
}

void EditorState::draw()
{
	m_MapEditing.draw();
}


void EditorState::clickCell()
{
	Position cell = getCellUnderMouse();

	if (m_TurnToTrack)
	{
		m_MapEditing.getCoords()[cell.row][cell.col] = 'P';
	}

	else
	{
		m_MapEditing.getCoords()[cell.row][cell.col] = '.';
	}
};

Position EditorState::getCellUnderMouse()
{
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	return Position { (int) std::floor(mouseY / CELL_SIZE), (int) std::floor(mouseX / CELL_SIZE) };
}
