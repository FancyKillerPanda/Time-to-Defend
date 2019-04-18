#pragma once

#include "pch.h"

#include "Text.h"


class Application;


class Menu
{
private:
	static Application* s_Game;

	// The items currently in the menu
	std::vector<Text*> m_Texts;

	// The item currently being highlighted
	int m_CurrentlyHighlighting = -1;

	// The default and highlighted colour of the text
	SDL_Color m_DefaultTextColour = { 90, 160, 30, 255 };
	SDL_Color m_HighlightedTextColour = { 255, 255, 0, 255 };

public:
	Menu(Application* const game, std::initializer_list<const char*> texts);
	~Menu();

	// Updates the menu
	void update();

	// Draws the menu
	void draw(unsigned int yTop);

	// Draws the menu horizontally
	void drawHorizontal(unsigned int xLeft, unsigned int y, unsigned int increment);

	// Adds one or more items to the menu
	void addItems(std::initializer_list<const char*> texts);

	// Returns the menu text that was clicked, if any
	int itemClicked();

	// Gets the items in the menu
	std::vector<Text*>& getItems() { return m_Texts; }

	// Sets the default colour of the text
	void setTextColour(SDL_Color colour) { m_DefaultTextColour = colour; }
	// Sets the highlight colour of the text
	void setHighlightedTextColour(SDL_Color colour) { m_HighlightedTextColour = colour; }
};
