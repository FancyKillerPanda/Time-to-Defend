#include "pch.h"

#include "Texture.h"

#include "utils/Log.h"


Texture::Texture(const char* filepath, SDL_Renderer* const renderer)
{
	load(filepath, renderer);
}

Texture::~Texture()
{
	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;

		LOG_INFO("Destroyed texture (filepath: {0}).", m_Filepath);
	}
}


void Texture::load(const char* filepath, SDL_Renderer* const renderer)
{
#ifdef _DEBUG
	m_Filepath = filepath;
#endif

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

	m_Loaded = true;

	LOG_INFO("Created texture.");
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
