#include "pch.h"

#include "EditorState.h"
#include "GameSettings.h"


EditorState::EditorState(std::string projectName, unsigned int numberOfWavesToSpawn)
	: m_ProjectName(projectName), m_NumberOfWavesToSpawn(numberOfWavesToSpawn)
{
}


void EditorState::onEnter()
{
	m_MapEditing.load(s_Game, nullptr);

	// Creates the tower
	m_TowerToDraw = new Tower(s_Game, m_HoveringTowerLocation);

	// The save question
	m_SaveQuestion.load(DEFAULT_FONT_PATH, "Do you want to save?", 48, SDL_Color { 0, 200, 200, 255 }, s_Game->getRenderer());

	// Creates the options
	m_OptionsMenu = new Menu(s_Game, {
		"Yes",
		"No",
		"Cancel"
	});

	// Sets the colours for the text
	for (Text* optionText : m_OptionsMenu->getItems())
	{
		optionText->setColour(SDL_Color { 0, 0, 0, 255 });
	}
}

void EditorState::handleEvent(SDL_Event& event)
{
	if (m_ScreenState == ScreenState::SaveScreen)
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			// Clicked "Yes"
			if (m_OptionsMenu->itemClicked() == 0)
			{
				saveMap();
				s_Game->end();
			}

			// Clicked "No"
			else if (m_OptionsMenu->itemClicked() == 1)
			{
				s_Game->end();
			}

			// Clicked "Cancel"
			else if (m_OptionsMenu->itemClicked() == 2)
			{
				m_ScreenState = ScreenState::Editor;
			}
		}

		return;
	}

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
			m_HoveringTowerLocation = getCellUnderMouse();

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
	if (m_ScreenState == ScreenState::SaveScreen)
	{
		m_OptionsMenu->update();

		// Sets the colours for the text
		for (Text* optionText : m_OptionsMenu->getItems())
		{
			optionText->setColour(SDL_Color { 0, 0, 0, 255 });
		}

		return;
	}

	m_TowerConflictingWithObject = towerConflicts(m_TowerToDraw);

	if (m_MouseButtonDown)
	{
		if (m_CurrentlyPlacingTower)
		{
			if (!m_TowerConflictingWithObject)
			{
				Position cell = getCellUnderMouse();
				m_MapEditing.getCoords()[cell.row][cell.col] = 'T';
				m_MapEditing.getTowerCoords().push_back(cell);

				m_CurrentlyPlacingTower = false;

				// Needs to happen otherwise clickCell() will
				// be called on the next frame
				m_MouseButtonDown = false;
			}
		}

		else
		{
			clickCell();
		}
	}
}

void EditorState::draw()
{
	// Draws the map even on the save screen
	m_MapEditing.draw(true);

	if (m_ScreenState == ScreenState::SaveScreen)
	{
		m_SaveQuestion.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 9 / 20);
		m_OptionsMenu->drawHorizontal(s_Game->getWindowWidth() * 5 / 20, s_Game->getWindowHeight() * 11 / 20, s_Game->getWindowWidth() * 5 / 20);

		return;
	}

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

		if (m_TowerConflictingWithObject)
		{
			SDL_SetRenderDrawColor(s_Game->getRenderer(), 170, 0, 0, 100);
		}

		else
		{
			SDL_SetRenderDrawColor(s_Game->getRenderer(), 0, 170, 0, 100);
		}

		// Adds a dim over the tower
		SDL_RenderFillRect(s_Game->getRenderer(), &m_TowerToDraw->getTexture()->getRect());
	}
}

bool EditorState::actionsOnExit()
{
	if (m_ScreenState == ScreenState::SaveScreen)
	{
		s_Game->end();
	}

	m_ScreenState = ScreenState::SaveScreen;

	return true;
}


void EditorState::clickCell()
{
	Position cell = getCellUnderMouse();

	if (m_TurnToTrack)
	{
		m_MapEditing.getCoords()[cell.row][cell.col] = 'P';
		m_MapEditing.getPathCoords().push_back(cell);
	}

	else
	{
		m_MapEditing.getCoords()[cell.row][cell.col] = '.';
		m_MapEditing.getPathCoords().push_back(cell);
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

	// Puts the number of waves to spawn at the top of the map data
	file << m_NumberOfWavesToSpawn << '\n';

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

bool EditorState::towerConflicts(Tower* tower)
{
	// Creates a rectangle for the tower
	SDL_Rect towerRect = { tower->getPosition().col * (int) CELL_SIZE, tower->getPosition().row * (int) CELL_SIZE, (int) CELL_SIZE * 2, (int) CELL_SIZE * 2 };

	// Checks if tower conflicts with path
	for (const Position& pathCell : m_MapEditing.getPathCoords())
	{
		// Creates a rectangle for the path cell
		SDL_Rect pathRect = { pathCell.col * (int) CELL_SIZE, pathCell.row * (int) CELL_SIZE, (int) CELL_SIZE, (int) CELL_SIZE };

		// Checks for an intersection
		if (SDL_HasIntersection(&towerRect, &pathRect))
		{
			return true;
		}
	}

	for (const Position& otherTowerPos : m_MapEditing.getTowerCoords())
	{
		// Creates a rectangle for the other tower
		SDL_Rect otherTowerRect = { otherTowerPos.col * (int) CELL_SIZE, otherTowerPos.row * (int) CELL_SIZE, (int) CELL_SIZE * 2, (int) CELL_SIZE * 2 };

		// Checks for an intersection
		if (SDL_HasIntersection(&towerRect, &otherTowerRect))
		{
			return true;
		}
	}

	return false;
}
