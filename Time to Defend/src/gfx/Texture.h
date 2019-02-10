#pragma once

#include <SDL/SDL.h>


class Texture
{
private:
	SDL_Texture* m_Texture = nullptr;
	SDL_Rect m_Rect = {};

	bool m_Loaded = false;

public:
	Texture() = default;
	Texture(const char* filepath, SDL_Renderer* const renderer);
	~Texture();

	void load(const char* filepath, SDL_Renderer* const renderer);

	void setRect(unsigned int x, unsigned int y);
	void setRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	inline SDL_Texture* const getTexture() { return m_Texture; }
	inline const SDL_Rect& getRect() { return m_Rect; }
	inline bool getLoaded() { return m_Loaded; }
};
