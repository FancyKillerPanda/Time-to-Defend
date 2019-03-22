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

public:
	Menu(Application* const game, std::initializer_list<const char*> texts);
	~Menu();

	// Draws the menu
	void draw(unsigned int yTop);

	// Adds one or more items to the menu
	void addItems(std::initializer_list<const char*> texts);
};
