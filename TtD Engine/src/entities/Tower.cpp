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

	// Creates the textures
	m_Texture = new Texture("res/txrs/Tower.png", s_Game->getRenderer());
	m_HighlightedTexture = new Texture("res/txrs/Tower Highlighted.png", s_Game->getRenderer());

	// Sets the texture's starting rects
	setPosition(m_Position);

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

void Tower::rotate(double amountDeg)
{
	// Makes sure direction is always in the range of [0, 360)
	m_Direction += 360.0;
	m_Direction += amountDeg;
	m_Direction = std::fmod(m_Direction, 360.0);
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

void Tower::setPosition(const Position& position)
{
	m_Position = position;
	m_Texture->setRect(position.col * CELL_SIZE, position.row * CELL_SIZE);
	m_HighlightedTexture->setRect(position.col * CELL_SIZE, position.row * CELL_SIZE);
}
