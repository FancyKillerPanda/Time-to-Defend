#pragma once

#include "pch.h"

#include "Text.h"


class Application;


class Paragraph
{
private:
	static Application* s_Game;

	// The lines of text
	std::vector<Text*> m_Texts;

public:
	Paragraph(Application* const game, std::initializer_list<const char*> texts, unsigned int fontSize = 28, SDL_Color textColour = { 90, 160, 30, 255 });
	~Paragraph();

	// Loads the paragraph text
	void load(Application* const game, std::initializer_list<const char*> texts, unsigned int fontSize = 28, SDL_Color textColour = { 90, 160, 30, 255 });

	// Draws the paragraph
	void draw(unsigned int yTop);
};
