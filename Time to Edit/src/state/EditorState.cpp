#include "pch.h"

#include "EditorState.h"
#include "GameSettings.h"


EditorState::EditorState(std::string projectName)
	: m_ProjectName(projectName)
{
}


void EditorState::onEnter()
{
	m_MapEditing.load(s_Game, nullptr);

	// Creates the tower
	m_TowerToDraw = new Tower(s_Game, m_HoveringTowerLocation);
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
			if (SDL_GetModState() & KMOD_CTRL)
			{
				saveMap();
			}

			break;

		case SDLK_t:
			m_CurrentlyPlacingTower = !m_CurrentlyPlacingTower;
			break;
		}

		break;

	case SDL_MOUSEBUTTONDOWN:
	{
		m_MouseButtonDown = true;

		if (!s_Game->settings->ctrlClickToRemoveTrack)
		{
			Position cell = getCellUnderMouse();

			if (m_MapEditing.getCoords()[cell.row][cell.col] == '.')
			{
				m_TurnToTrack = true;
			}

			else
			{
				m_TurnToTrack = false;
			}
		}

		else
		{
			if (SDL_GetModState() & KMOD_CTRL)
			{
				m_TurnToTrack = false;
			}

			else
			{
				m_TurnToTrack = true;
			}
		}

		break;
	}

	case SDL_MOUSEBUTTONUP:
		m_MouseButtonDown = false;
		break;

	case SDL_MOUSEMOTION:
		if (m_CurrentlyPlacingTower)
		{
			m_HoveringTowerLocation = getCellUnderMouse();
		}

		break;
	}
}

void EditorState::update()
{
	if (m_MouseButtonDown)
	{
		if (m_CurrentlyPlacingTower)
		{
			Position cell = getCellUnderMouse();
			m_MapEditing.getCoords()[cell.row][cell.col] = 'T';
			m_MapEditing.getTowerCoords().push_back(cell);

			m_CurrentlyPlacingTower = false;

			// Needs to happen otherwise clickCell() will
			// be called on the next frame
			m_MouseButtonDown = false;
		}

		else
		{
			clickCell();
		}
	}
}

void EditorState::draw()
{
	m_MapEditing.draw(true);

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

	if (m_CurrentlyPlacingTower)
	{
		// Draws the tower where the mouse is
		m_TowerToDraw->setPosition(m_HoveringTowerLocation);
		m_TowerToDraw->draw();
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
	// Windows only
#ifdef WIN32
	if (!(CreateDirectory("res\\maps\\custom\\", nullptr) || GetLastError() == ERROR_ALREADY_EXISTS))
	{
		LOG_ERROR("Could not create directory to save in.");
		return;
	}
#endif // WIN32

	std::string filename = "res/maps/custom/";
	filename += m_ProjectName;
	filename += ".txt";

	std::fstream file;
	file.open(filename.c_str(), std::fstream::out | std::fstream::trunc);

	if (!file)
	{
		LOG_ERROR("Could not open file to save map to.");
		return;
	}

	m_MapEditing.convertToPlayableFormat();

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
