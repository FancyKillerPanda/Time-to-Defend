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
	Paragraph(Application* const game, std::initializer_list<const char*> texts);
	~Paragraph();

	// Loads the paragraph text
	void load(Application* const game, std::initializer_list<const char*> texts);

	// Draws the paragraph
	void draw(unsigned int yTop);
};
