#include "pch.h"

#include "StartScreenState.h"

#include "Game.h"
#include "Settings.h"
#include "GameplayState.h"


void StartScreenState::onEnter()
{
	// Creates the text
	m_TtDText.load("res/fonts/arial.ttf", "Time to Defend!", 48, SDL_Color { 255, 70, 0, 255 }, s_Game->getRenderer());

	// Makes the text bold
	m_TtDText.setStyle(TTF_STYLE_BOLD);

	// Creates the main menu
	m_MainMenu = new Menu(s_Game, {
		"Play",
		"Load Level",
		"Instructions",
		"Level Editor",
		"Settings"
	});

	// The load project page
	m_LoadProjectMenu = new Menu(s_Game, {
		"Continue -->"
	});

	// The settings
	m_SettingsMenu = new Menu(s_Game, {
		s_Game->settings->arrowKeysToRotateTower ? "Arrow Keys to Rotate Tower: True" : "Arrow Keys to Rotate Tower: False",
		s_Game->settings->spaceToShoot ? "Space to Shoot: True" : "Space to Shoot: False",
		s_Game->settings->towerShootCooldown ? "Tower Shoot Cooldown: True" : "Tower Shoot Cooldown: False"
	});

	// The instructions
	m_Instructions = new Paragraph(s_Game, {
		"Welcome to Time to Defend! Your goal is to try",
		"to defeat all the enemies that will be trying",
		"to invade your land.",
		"",
		"To rotate your tower, press <Left> or <Right>.",
		"To shoot, press <Space>. To switch which",
		"tower you are controlling, press <T>."
	});

	// Creates the back button
	m_BackMenu = new Menu(s_Game, {
		"<-- Back"
	});

	// Initialises the project name and its label
	m_ProjectName = new InputText(s_Game, "Untitled");
	m_LoadProjectLabel.load(DEFAULT_FONT_PATH, "Project Name:", 28, SDL_Color { 90, 160, 30, 255 }, s_Game->getRenderer());

	// Makes the background render black
	SDL_SetRenderDrawColor(s_Game->getRenderer(), 0, 0, 0, 255);
}

void StartScreenState::onExit()
{
	delete m_MainMenu;
	m_MainMenu = nullptr;

	delete m_LoadProjectMenu;
	m_LoadProjectMenu = nullptr;

	delete m_ProjectName;
	m_ProjectName = nullptr;

	delete m_Instructions;
	m_Instructions = nullptr;

	delete m_BackMenu;
	m_BackMenu = nullptr;
}

void StartScreenState::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RETURN:
			switch (m_ScreenState)
			{
			case ScreenState::MainScreen:
			{
				// Replaces this state with GameplayState
				s_Game->replaceTopState<GameplayState>();

				break;
			}

			case ScreenState::LoadProject:
			{
				// Creates the map filepath
				std::string mapFilepath = "res/maps/custom/";
				mapFilepath += m_ProjectName->get().getText() + ".txt";

				// Replaces this state with GameplayState
				s_Game->replaceTopState<GameplayState>(m_ProjectName->get().getText(), mapFilepath);

				break;
			}

			// Goes back to the main screen
			case ScreenState::Instructions:
			case ScreenState::Settings:
				m_ScreenState = ScreenState::MainScreen;
				break;
			}

			break;

		case SDLK_h:
			// Goes to the instructions screen
			if (m_ScreenState == ScreenState::MainScreen)
			{
				m_ScreenState = ScreenState::Instructions;
			}

			break;

		case SDLK_BACKSPACE:
			if (m_ScreenState == ScreenState::LoadProject)
			{
				m_ProjectName->handleKeyEvent(event);
			}

			break;
		}

		break;

	case SDL_MOUSEBUTTONDOWN:
		switch (m_ScreenState)
		{
		case ScreenState::MainScreen:
		{
			// Clicked "Play"
			if (m_MainMenu->itemClicked() == 0)
			{
				// Replaces this state with GameplayState
				s_Game->replaceTopState<GameplayState>();

				break;
			}

			// Clicked "Load Level"
			else if (m_MainMenu->itemClicked() == 1)
			{
				m_ScreenState = ScreenState::LoadProject;
			}

			// Clicked "Instructions"
			else if (m_MainMenu->itemClicked() == 1)
			{
				m_ScreenState = ScreenState::Instructions;
			}

			// Clicked "Level Editor"
			else if (m_MainMenu->itemClicked() == 2)
			{
			#ifdef _WIN32

				if (ShellExecute(NULL, "open", "Time to Edit.exe", "", "", SW_SHOW))
				{
					LOG_INFO("Successfully started editor process.");
				}
				else
				{
					LOG_ERROR("Could not start editor process.");
				}

			#endif
			}

			// Clicked "Settings"
			else if (m_MainMenu->itemClicked() == 3)
			{
				m_ScreenState = ScreenState::Settings;
			}

			break;
		}

		case ScreenState::LoadProject:
		{
			// Clicked "Next"
			if (m_LoadProjectMenu->itemClicked() == 0)
			{
				// Creates the map
				std::string mapFilepath = "res/maps/custom/";
				mapFilepath += m_ProjectName->get().getText() + ".txt";

				// Replaces this state with GameplayState
				s_Game->replaceTopState<GameplayState>(m_ProjectName->get().getText(), mapFilepath);

				break;
			}

			break;
		}

		case ScreenState::Instructions:
		{
			if (m_BackMenu->itemClicked() == 0)
			{
				m_ScreenState = ScreenState::MainScreen;
			}

			break;
		}

		case ScreenState::Settings:
			// Toggles arrow keys to rotate
			if (m_SettingsMenu->itemClicked() == 0)
			{
				if (s_Game->settings->arrowKeysToRotateTower)
				{
					m_SettingsMenu->getItems()[0]->setText("Arrow Keys to Rotate Tower: False");
				}

				else
				{
					m_SettingsMenu->getItems()[0]->setText("Arrow Keys to Rotate Tower: True");
				}

				s_Game->settings->arrowKeysToRotateTower = !s_Game->settings->arrowKeysToRotateTower;
			}

			// Toggles space to shoot
			else if (m_SettingsMenu->itemClicked() == 1)
			{
				if (s_Game->settings->spaceToShoot)
				{
					m_SettingsMenu->getItems()[1]->setText("Space to Shoot: False");
				}

				else
				{
					m_SettingsMenu->getItems()[1]->setText("Space to Shoot: True");
				}

				s_Game->settings->spaceToShoot = !s_Game->settings->spaceToShoot;
			}

			// Toggles tower shoot cooldown
			else if (m_SettingsMenu->itemClicked() == 2)
			{
				if (s_Game->settings->towerShootCooldown)
				{
					m_SettingsMenu->getItems()[2]->setText("Tower Shoot Cooldown: False");
				}

				else
				{
					m_SettingsMenu->getItems()[2]->setText("Tower Shoot Cooldown: True");
				}

				s_Game->settings->towerShootCooldown = !s_Game->settings->towerShootCooldown;
			}

			if (m_BackMenu->itemClicked() == 0)
			{
				m_ScreenState = ScreenState::MainScreen;
			}

			break;
		}

		break;

	case SDL_TEXTINPUT:
		if (m_ScreenState == ScreenState::LoadProject)
		{
			m_ProjectName->handleInputEvent(event);
		}

		break;
	}
}

void StartScreenState::update()
{
	switch (m_ScreenState)
	{
	case ScreenState::MainScreen:
	{
		m_MainMenu->update();
		break;
	}

	case ScreenState::LoadProject:
		m_LoadProjectMenu->update();
		m_BackMenu->update();
		break;

	case ScreenState::Instructions:
		m_BackMenu->update();
		break;

	case ScreenState::Settings:
		m_SettingsMenu->update();
		m_BackMenu->update();
		break;
	}
}

void StartScreenState::draw()
{
	switch (m_ScreenState)
	{
	case ScreenState::MainScreen:
		// Draws text
		m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 4 / 20);
		m_MainMenu->draw(s_Game->getWindowHeight() * 7 / 20);

		break;

	case ScreenState::LoadProject:
		// Draws text
		m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 5 / 20);
		m_LoadProjectLabel.draw(s_Game->getWindowWidth() * 1 / 3, s_Game->getWindowHeight() * 9 / 20);
		m_ProjectName->get().draw(s_Game->getWindowWidth() * 2 / 3, s_Game->getWindowHeight() * 9 / 20);
		m_LoadProjectMenu->draw(s_Game->getWindowHeight() * 16 / 20);
		m_BackMenu->draw(s_Game->getWindowHeight() * 18 / 20);

		break;

	case ScreenState::Instructions:
		// Draws text
		m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 5 / 20);
		m_Instructions->draw(s_Game->getWindowHeight() * 8 / 20);
		m_BackMenu->draw(s_Game->getWindowHeight() * 18 / 20);

		break;

	case ScreenState::Settings:
		// Draws text
		m_TtDText.draw(s_Game->getWindowWidth() / 2, s_Game->getWindowHeight() * 5 / 20);
		m_SettingsMenu->draw(s_Game->getWindowHeight() * 9 / 20);
		m_BackMenu->draw(s_Game->getWindowHeight() * 18 / 20);
	}
}
