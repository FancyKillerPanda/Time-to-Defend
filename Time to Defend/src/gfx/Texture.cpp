#include "pch.h"

#include "Texture.h"

#include "utils/Log.h"


std::unordered_map<const char*, std::pair<SDL_Texture*, unsigned int>> Texture::s_TextureCache = {};


Texture::Texture(const char* filepath, SDL_Renderer* const renderer)
{
	load(filepath, renderer);
}

Texture::~Texture()
{
	// Decreases the reference count
	s_TextureCache.find(m_Filepath)->second.second -= 1;

	// Checks if this is the last texture
	if (s_TextureCache.find(m_Filepath)->second.second == 0)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;

		s_TextureCache.erase(m_Filepath);

		LOG_INFO("Destroyed texture (filepath: {0}).", m_Filepath);
	}
}


void Texture::load(const char* filepath, SDL_Renderer* const renderer)
{
	m_Filepath = filepath;

	// Texture of this filepath already exists
	if (s_TextureCache.find(m_Filepath) != s_TextureCache.end())
	{
		m_Texture = s_TextureCache.find(m_Filepath)->second.first;

		// Sets the dimensions in the rect
		SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_Rect.w, &m_Rect.h);

		// Increases the reference count
		s_TextureCache.find(m_Filepath)->second.second += 1;
	}

	else
	{
		// Loads the texture
		m_Texture = IMG_LoadTexture(renderer, filepath);

		// Error checking for texture
		if (m_Texture == nullptr)
		{
			LOG_FATAL("Could not load texture (filepath: {0}).\nSDLError: {1}.", filepath, SDL_GetError());
			return;
		}

		// Checks for valid texture dimensions
		if (SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_Rect.w, &m_Rect.h) == -1)
		{
			LOG_FATAL("Texture is invalid (filepath: {0}).\nSDLError: {1}.", filepath, SDL_GetError());
			return;
		}

		// Adds the texture into the cache
		s_TextureCache.insert(std::pair<const char*, std::pair<SDL_Texture*, unsigned int>>(
			m_Filepath, std::pair<SDL_Texture*, unsigned int>(m_Texture, 1)
		));

		LOG_INFO("Created texture (filepath: {0}).", m_Filepath);
	}

	m_Loaded = true;
}

void Texture::setRect(unsigned int x, unsigned int y)
{
	m_Rect.x = x;
	m_Rect.y = y;
}

void Texture::setRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	m_Rect.x = x;
	m_Rect.y = y;
	m_Rect.w = width;
	m_Rect.h = height;
}
