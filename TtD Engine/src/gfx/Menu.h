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
};
