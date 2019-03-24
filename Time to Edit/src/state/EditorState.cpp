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
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_g:
			m_ShowGrid = !m_ShowGrid;
			break;

		case SDLK_s:
			saveMap();
			break;
		}

		break;

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

	if (m_ShowGrid)
	{
		// Vertical lines
		for (unsigned int x = CELL_SIZE * 3; x < CELL_SIZE * NUM_OF_CELLS_X; x += CELL_SIZE * 3)
		{
			SDL_RenderDrawLine(s_Game->getRenderer(), x, 0, x, CELL_SIZE * NUM_OF_CELLS_Y);
		}

		// Horizontal lines
		for (unsigned int y = CELL_SIZE * 3; y < CELL_SIZE * NUM_OF_CELLS_Y; y += CELL_SIZE * 3)
		{
			SDL_RenderDrawLine(s_Game->getRenderer(), 0, y, CELL_SIZE * NUM_OF_CELLS_X, y);
		}
	}
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

void EditorState::saveMap()
{
	std::fstream file;
	file.open("res/maps/custom/map1.txt", std::fstream::out | std::fstream::trunc);

	if (!file)
	{
		LOG_ERROR("Could not open file to save map to.");
		return;
	}

	for (int row = 0; row < NUM_OF_CELLS_Y; row++)
	{
		for (int col = 0; col < NUM_OF_CELLS_X; col++)
		{
			file << m_MapEditing.getCoords()[row][col];
		}

		file << '\n';
	}

	file.close();

	LOG_INFO("Saved map.");
}
