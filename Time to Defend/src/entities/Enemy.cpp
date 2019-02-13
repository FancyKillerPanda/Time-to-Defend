#include "pch.h"

#include "Enemy.h"

#include "Game.h"
#include "Settings.h"
#include "utils/Random.h"


Game* Enemy::s_Game = nullptr;
Texture* Enemy::s_Texture = nullptr;
int Enemy::s_InstanceCount = 0;
const Map* Enemy::s_Map = nullptr;


Enemy::Enemy(Game* const game, const Map* map, Position position)
	: m_Position(position)
{
	s_Game = game;
	s_Map = map;

	if (s_InstanceCount == 0)
	{
		s_Texture = new Texture("res/txrs/Enemy.png", s_Game->getRenderer());
	}

	s_InstanceCount += 1;

	LOG_INFO("Created enemy.");
}

Enemy::~Enemy()
{
	LOG_INFO("Destroyed enemy.");

	s_InstanceCount -= 1;

	if (s_InstanceCount == 0)
	{
		delete s_Texture;
		s_Texture = nullptr;
	}
}


void Enemy::draw()
{
	s_Texture->setRect(m_Position.col * CELL_SIZE, m_Position.row * CELL_SIZE);

	SDL_RenderCopy(s_Game->getRenderer(), s_Texture->getTexture(), nullptr, &s_Texture->getRect());
}

void Enemy::move()
{
	const Position& nextPos = getNextPosition();

	m_LastPosition = m_Position;
	m_Position = nextPos;
}

Position Enemy::getNextPosition()
{
	std::vector<Position> possibleMoves;

	for (int rowDiff = -1; rowDiff <= 1; rowDiff++)
	{
		for (int colDiff = -1; colDiff <= 1; colDiff++)
		{
			if (rowDiff == 0 && colDiff == 0)
			{
				continue;
			}

			if (m_Position.row + rowDiff == m_LastPosition.row &&
				m_Position.col + colDiff == m_LastPosition.col)
			{
				continue;
			}

			if (m_Position.row + rowDiff >= 0 &&
				m_Position.col + colDiff >= 0 &&
				m_Position.row + rowDiff < NUM_OF_CELLS_Y &&
				m_Position.col + colDiff < NUM_OF_CELLS_X &&
				(s_Map->getCoords()[m_Position.row + rowDiff][m_Position.col + colDiff] == 'P' || s_Map->getCoords()[m_Position.row + rowDiff][m_Position.col + colDiff] == 'S'))
			{
				possibleMoves.emplace_back(m_Position.row + rowDiff, m_Position.col + colDiff);
			}
		}
	}

	bool shouldRemove = false;

	for (const Position& pos : possibleMoves)
	{
		if (pos.row - m_Position.row == 0 ||
			pos.col - m_Position.col == 0)
		{
			shouldRemove = true;
		}
	}

	if (shouldRemove)
	{
		for (unsigned int i = 0; i < possibleMoves.size(); i++)
		{
			const Position& pos = possibleMoves[i];

			if (pos.row - m_Position.row != 0 &&
				pos.col - m_Position.col != 0)
			{
				possibleMoves.erase(possibleMoves.begin() + i);
			}
		}
	}

	return possibleMoves[Random::randint(0, (int) possibleMoves.size() - 1)];
}
