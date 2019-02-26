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
	s_TextureCache.find(m_Filepath)->second.second -= 1;

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

	if (s_TextureCache.find(m_Filepath) != s_TextureCache.end())
	{
		m_Texture = s_TextureCache.find(m_Filepath)->second.first;
		s_TextureCache.find(m_Filepath)->second.second += 1;
	}

	else
	{
		m_Texture = IMG_LoadTexture(renderer, filepath);

		if (m_Texture == nullptr)
		{
			LOG_FATAL("Could not load texture (filepath: {0}).\nSDLError: {1}", filepath, SDL_GetError());
			return;
		}

		if (SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_Rect.w, &m_Rect.h) == -1)
		{
			LOG_FATAL("Texture is invalid (filepath: {0}).\nSDLError: {1}", filepath, SDL_GetError());
			return;
		}

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
