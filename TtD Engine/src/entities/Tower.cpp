#include "pch.h"

#include "Tower.h"

#include "utils/Log.h"
#include "utils/Maths.h"
#include "Settings.h"


Application* Tower::s_Game = nullptr;


Tower::Tower(Application* const game, Position position)
	: m_Position(position)
{
	s_Game = game;

	// Creates the textures and sets their starting rects
	m_Texture = new Texture("res/txrs/Tower.png", s_Game->getRenderer());
	m_Texture->setRect(m_Position.col * CELL_SIZE, m_Position.row * CELL_SIZE);
	m_HighlightedTexture = new Texture("res/txrs/Tower Highlighted.png", s_Game->getRenderer());
	m_HighlightedTexture->setRect(m_Position.col * CELL_SIZE, m_Position.row * CELL_SIZE);

	LOG_INFO("Created tower.");
}

Tower::~Tower()
{
	LOG_INFO("Destroyed tower.");

	delete m_Texture;
	m_Texture = nullptr;
}


void Tower::update()
{
	// Gets the mouse position
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	m_Direction = getDegrees(std::atan2(m_Texture->getRect().y - mouseY, m_Texture->getRect().x - mouseX)) - 90;
}

void Tower::draw()
{
	SDL_Texture* texture;

	if (m_Highlighted)
	{
		texture = m_HighlightedTexture->getTexture();
	}

	else
	{
		texture = m_Texture->getTexture();
	}

	// Renders the tower, rotating by the current direction
	SDL_RenderCopyEx(s_Game->getRenderer(), texture, nullptr, &m_Texture->getRect(), m_Direction, nullptr, SDL_FLIP_NONE);
}

Arrow* Tower::shoot()
{
	// Creates an arrow at the center of the tower
	return new Arrow(
		s_Game,
		(float) ((m_Position.col + 1) * CELL_SIZE),
		(float) ((m_Position.row + 1) * CELL_SIZE),
		m_Direction
	);
}