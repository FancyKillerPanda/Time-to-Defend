#pragma once

#include "pch.h"


class Text
{
private:
	// Whether the data and texture has been loaded
	bool m_Loaded = false;

	// Text data
	const char* m_FontPath;
	std::string m_Text;
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
	Text(const char* fontPath, std::string text, unsigned int size, SDL_Color colour, SDL_Renderer* renderer);
	~Text();

	// Loads the text
	void load(const char* fontPath, std::string text, unsigned int size, SDL_Color colour, SDL_Renderer* renderer);

	// Whether the text has been clicked
	bool rectCollides(int x, int y);

	// Sets the text
	void setText(std::string text, bool update = true);
	// Sets the colour of the text
	void setColour(const SDL_Color& colour, bool update = true);
	// Sets the font size
	void setSize(unsigned int size, bool update = true);

	// Sets the style of the font
	void setStyle(int style, bool update = true);

	// Draws the text to the renderer
	void draw(unsigned int x, unsigned int y);

	// Gets the rect
	const SDL_Rect& getRect() { return m_TextRect; }

	// Gets the text
	const std::string& getText() { return m_Text; }
};
