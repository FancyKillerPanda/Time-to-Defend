#include "pch.h"

#include "Menu.h"

#include "Application.h"
#include "Settings.h"


Application* Menu::s_Game = nullptr;


Menu::Menu(Application* const game, std::initializer_list<const char*> texts)
{
	s_Game = game;
	addItems(texts);
}

Menu::~Menu()
{
	// Deletes all the text
	for (Text* text : m_Texts)
	{
		if (text != nullptr)
		{
			delete text;
			text = nullptr;
		}
	}
}


void Menu::draw(unsigned int yTop)
{
	unsigned int currentY = yTop;

	for (Text* text : m_Texts)
	{
		if (text != nullptr)
		{
			text->draw(s_Game->getWindowWidth() / 2, currentY);
		}

		currentY += s_Game->getWindowHeight() * 2 / 20;
	}
}

void Menu::drawHorizontal(unsigned int xLeft, unsigned int y, unsigned int increment)
{
	unsigned int currentX = xLeft;

	for (Text* text : m_Texts)
	{
		if (text != nullptr)
		{
			text->draw(currentX, y);
		}

		currentX += increment;
	}
}

void Menu::update()
{
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	for (unsigned int i = 0; i < m_Texts.size(); i++)
	{
		Text* text = m_Texts[i];

		if (text->rectCollides(mouseX, mouseY))
		{
			if (m_CurrentlyHighlighting != (int) i)
			{
				if (m_CurrentlyHighlighting != -1)
				{
					// Resets the old menu item highlighting
					m_Texts[m_CurrentlyHighlighting]->setStyle(TTF_STYLE_NORMAL, false);
					m_Texts[m_CurrentlyHighlighting]->setColour(m_DefaultTextColour);
				}

				m_CurrentlyHighlighting = i;

				// Sets the new item to highlight
				text->setStyle(TTF_STYLE_BOLD, false);
				text->setColour(m_HighlightedTextColour);
			}

			break;
		}
	}

	if (m_CurrentlyHighlighting != -1)
	{
		// Resets the old menu item highlighting
		if (!m_Texts[m_CurrentlyHighlighting]->rectCollides(mouseX, mouseY))
		{
			m_Texts[m_CurrentlyHighlighting]->setStyle(TTF_STYLE_NORMAL, false);
			m_Texts[m_CurrentlyHighlighting]->setColour(m_DefaultTextColour);

			m_CurrentlyHighlighting = -1;
		}
	}
}

void Menu::addItems(std::initializer_list<const char*> texts)
{
	for (const char* text : texts)
	{
		if (std::strcmp(text, "") == 0)
		{
			m_Texts.emplace_back(nullptr);
		}

		else
		{
			m_Texts.emplace_back(new Text(DEFAULT_FONT_PATH, text, 28, m_DefaultTextColour, s_Game->getRenderer()));
		}
	}
}

int Menu::itemClicked()
{
	// Gets the mouse posiiton
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	for (unsigned int i = 0; i < m_Texts.size(); i++)
	{
		Text* text = m_Texts[i];

		if (text != nullptr && text->rectCollides(mouseX, mouseY))
		{
			return i;
		}
	}

	return -1;
}
