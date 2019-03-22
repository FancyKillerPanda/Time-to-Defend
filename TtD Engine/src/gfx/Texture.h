#pragma once

#include "pch.h"


class Texture
{
private:
	// Cache of texture
	// Maps a filepath to a pair of the texture-pointer and a reference count
	static std::unordered_map<const char*, std::pair<SDL_Texture*, unsigned int>> s_TextureCache;

	SDL_Texture* m_Texture = nullptr;
	SDL_Rect m_Rect = {};

	bool m_Loaded = false;
	const char* m_Filepath;

public:
	Texture() = default;
	Texture(const char* filepath, SDL_Renderer* const renderer);
	~Texture();

	// Loads the texture
	void load(const char* filepath, SDL_Renderer* const renderer);

	// Sets just the position of the rect
	void setRect(unsigned int x, unsigned int y);
	// Sets the position and dimensions of the rect
	void setRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	inline SDL_Texture* const getTexture() { return m_Texture; }
	inline const SDL_Rect& getRect() { return m_Rect; }
	inline bool getLoaded() { return m_Loaded; }
};
