#include "pch.h"

#include "InputText.h"
#include "Settings.h"
#include "Application.h"


Application* InputText::s_Game = nullptr;


InputText::InputText(Application* const game, std::string defaultText, bool numbersOnly)
	: m_ZeroCharDefault(defaultText), m_NumbersOnly(numbersOnly)
{
	s_Game = game;

	// Loads the text to a default value
	m_CurrentText.load(DEFAULT_FONT_PATH, defaultText, 28, SDL_Color { 160, 160, 160, 255 }, s_Game->getRenderer());
}


void InputText::handleKeyEvent(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_BACKSPACE:
		std::size_t length = m_CurrentText.getText().length();

		if (length == 0 || m_CurrentText.getText() == "Untitled")
		{
			break;
		}

		if (SDL_GetModState() & KMOD_CTRL)
		{
			// Removes characters until a space
			while (m_CurrentText.getText().length() > 0 && m_CurrentText.getText().back() != ' ')
			{
				m_CurrentText.getText().pop_back();
			}

			if (m_CurrentText.getText().length() > 0)
			{
				// Removes the space
				m_CurrentText.getText().pop_back();
			}
		}

		else
		{
			// Removes a character
			m_CurrentText.getText().pop_back();
		}

		// Sets empty text to default
		if (m_CurrentText.getText().length() == 0)
		{
			m_CurrentText.setText(m_ZeroCharDefault, false);
		}

		// Updates the text
		m_CurrentText.setText(m_CurrentText.getText());

		break;
	}
}

void InputText::handleInputEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_TEXTINPUT:
		if (std::regex_match(event.text.text, s_Game->s_NonFilenameCharacters))
		{
			break;
		}

		if (m_NumbersOnly && !std::isdigit(event.text.text[0]))
		{
			break;
		}

		if (m_CurrentText.getText() == m_ZeroCharDefault)
		{
			m_CurrentText.setText("", false);
		}

		m_CurrentText.setText(m_CurrentText.getText() + event.text.text);

		break;
	}
}
