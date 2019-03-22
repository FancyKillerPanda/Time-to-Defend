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

void Menu::addItems(std::initializer_list<const char*> texts)
{
	for (const char* text : texts)
	{
		if (text == "")
		{
			m_Texts.emplace_back(nullptr);
		}

		else
		{
			m_Texts.emplace_back(new Text(DEFAULT_FONT_PATH, text, 28, SDL_Color { 90, 160, 30 , 255 }, s_Game->getRenderer()));
		}
	}
}
