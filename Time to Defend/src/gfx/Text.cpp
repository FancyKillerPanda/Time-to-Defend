#include "pch.h"

#include "Text.h"

#include "utils/Log.h"


Text::Text(const char* fontPath, const char* text, unsigned int size, SDL_Color colour, SDL_Renderer* renderer)
{
	load(fontPath, text, size, colour, renderer);
}

Text::~Text()
{
	// Destroys the texture
	SDL_DestroyTexture(m_TextTexture);
	m_TextTexture = nullptr;

	// Closes the font
	TTF_CloseFont(m_Font);
	m_Font = nullptr;

	LOG_INFO("Destroyed text (text: \"{0}\").", m_Text);
}

void Text::load(const char* fontPath, const char* text, unsigned int size, SDL_Color colour, SDL_Renderer* renderer)
{
	// Sets attributes on load
	m_FontPath = fontPath;
	m_Text = text;
	m_Size = size;
	m_Colour = colour;
	m_Renderer = renderer;

	// Loads the font
	m_Font = TTF_OpenFont(m_FontPath, size);

	// Error checking for font
	if (m_Font == nullptr)
	{
		LOG_FATAL("Could not load font (filepath: {0}).\nSDLError: {1}.", m_FontPath, SDL_GetError());
		return;
	}

	updateTexture();

	LOG_INFO("Text loaded (text: \"{0}\").", m_Text);

	m_Loaded = true;
}


void Text::updateTexture()
{
	// Destroys the last texture
	SDL_DestroyTexture(m_TextTexture);
	m_TextTexture = nullptr;

	// Creates a surface for the font
	//SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, m_Text, m_Colour);
	SDL_Surface* textSurface = TTF_RenderUTF8_Solid(m_Font, m_Text, m_Colour);

	// Error checking for text surface
	if (textSurface == nullptr)
	{
		LOG_FATAL("Could not create text surface (filepath: {0}).\nSDLError: {1}.", m_FontPath, SDL_GetError());
		return;
	}

	// Creates a texture from the surface
	m_TextTexture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);

	if (m_TextTexture == nullptr)
	{
		LOG_FATAL("Could not create texture from surface for font (filepath: {0}).\nSDLError: {1}.", m_FontPath, SDL_GetError());
		return;
	}

	// Frees the temporary surface
	SDL_FreeSurface(textSurface);

	// Gets the dimensions of the texture
	SDL_QueryTexture(m_TextTexture, nullptr, nullptr, &m_TextRect.w, &m_TextRect.h);

	LOG_INFO("Created texture (filepath: {0}).", m_FontPath);
}

void Text::setText(const char* text)
{
	if (!m_Loaded)
	{
		LOG_WARNING("Tried to set text before loading.");
		return;
	}

	m_Text = text;
	updateTexture();
}

void Text::setColour(const SDL_Color& colour)
{
	if (!m_Loaded)
	{
		LOG_WARNING("Tried to set text colour before loading.");
		return;
	}

	m_Colour = colour;
	updateTexture();
}

void Text::setSize(unsigned int size)
{
	if (!m_Loaded)
	{
		LOG_WARNING("Tried to set text size before loading.");
		return;
	}

	m_Size = size;
	updateTexture();
}

void Text::draw(unsigned int x, unsigned int y)
{
	if (!m_Loaded)
	{
		LOG_ERROR("Tried to draw text before loading.");
		return;
	}

	// Sets the text position (aligned center)
	m_TextRect.x = x - (m_TextRect.w / 2);
	m_TextRect.y = y - (m_TextRect.h / 2);

	SDL_RenderCopy(m_Renderer, m_TextTexture, nullptr, &m_TextRect);
}

void Text::setStyle(int style)
{
	TTF_SetFontStyle(m_Font, style);
}
