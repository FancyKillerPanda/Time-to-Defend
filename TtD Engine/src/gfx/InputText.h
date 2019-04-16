#pragma once

#include <pch.h>

#include "Text.h"


class Application;


class InputText
{
private:
	static Application* s_Game;

	// The current text being displayed
	Text m_CurrentText;

	// What to set the text to when there is nothing typed
	std::string m_ZeroCharDefault;

	// Whether the text only accepts numbers
	bool m_NumbersOnly = false;

public:
	InputText(Application* const game, std::string defaultText, bool numbersOnly = false);

	void handleKeyEvent(SDL_Event& event);
	void handleInputEvent(SDL_Event& event);

	inline Text& get() { return m_CurrentText; }
};
