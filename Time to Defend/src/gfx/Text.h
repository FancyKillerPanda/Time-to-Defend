#pragma once

#include "pch.h"


class Text
{
private:
	// Whether the data and texture has been loaded
	bool m_Loaded = false;

	// Text data
	const char* m_FontPath;
	const char* m_Text;
	unsigned int m_Size;
	SDL_Color m_Colour;
	SDL_Renderer* m_Renderer;

	// The font that will be used
	TTF_Font* m_Font;

	// SDL texture and it's rectangle
	SDL_Texture* m_TextTexture;
	SDL_Rect m_TextRect;

private:
	// Updates the texture to after data changes
	void updateTexture();

public:
	Text() = default;
	Text(const char* fontPath, const char* text, unsigned int size, SDL_Color colour, SDL_Renderer* renderer);
	~Text();

	// Loads the text
	void load(const char* fontPath, const char* text, unsigned int size, SDL_Color colour, SDL_Renderer* renderer);

	// Sets the text
	void setText(const char* text);
	// Sets the colour of the text
	void setColour(const SDL_Color& colour);
	// Sets the font size
	void setSize(unsigned int size);

	// Draws the text to the renderer
	void draw(unsigned int x, unsigned int y);
};
