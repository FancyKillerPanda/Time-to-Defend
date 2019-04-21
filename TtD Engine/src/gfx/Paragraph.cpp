#include "pch.h"

#include "Paragraph.h"

#include "Settings.h"
#include "Application.h"


Application* Paragraph::s_Game = nullptr;


Paragraph::Paragraph(Application* const game, std::initializer_list<const char*> texts, unsigned int fontSize, SDL_Color textColour)
{
	load(game, texts, fontSize, textColour);
}

Paragraph::~Paragraph()
{
	for (Text* text : m_Texts)
	{
		if (text != nullptr)
		{
			delete text;
			text = nullptr;
		}
	}
}


void Paragraph::load(Application* const game, std::initializer_list<const char*> texts, unsigned int fontSize, SDL_Color textColour)
{
	s_Game = game;

	for (const char* text : texts)
	{
		if (std::strcmp(text, "") == 0)
		{
			m_Texts.emplace_back(nullptr);
		}

		else
		{
			m_Texts.emplace_back(new Text(DEFAULT_FONT_PATH, text, fontSize, textColour, s_Game->getRenderer()));
		}
	}
}

void Paragraph::draw(unsigned int yTop)
{
	unsigned int currentY = yTop;

	// Draws the paragraph
	for (Text* text : m_Texts)
	{
		if (text != nullptr)
		{
			text->draw(s_Game->getWindowWidth() / 2, currentY);
		}

		// Still adds to currentY to end paragraph
		currentY += s_Game->getWindowHeight() * 1 / 20;
	}
}
