#include "pch.h"

#include "Enemy.h"

#include "Game.h"
#include "Settings.h"
#include "utils/Random.h"


Game* Enemy::s_Game = nullptr;
Texture* Enemy::s_Texture = nullptr;
int Enemy::s_InstanceCount = 0;
const Map* Enemy::s_Map = nullptr;


Enemy::Enemy(Game* const game, const Map* map, unsigned int row, unsigned int col)
	: m_Row(row), m_Col(col)
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
	s_Texture->setRect(m_Col * CELL_SIZE, m_Row * CELL_SIZE);

	SDL_RenderCopy(s_Game->getRenderer(), s_Texture->getTexture(), nullptr, &s_Texture->getRect());
}

void Enemy::move()
{
	const std::pair<unsigned int, unsigned int> nextPos = getNextPosition();

	m_LastRow = m_Row;
	m_LastCol = m_Col;

	m_Row = nextPos.first;
	m_Col = nextPos.second;
}

std::pair<unsigned int, unsigned int> Enemy::getNextPosition()
{
	std::vector<std::pair<unsigned int, unsigned int>> possibleMoves;

	for (int rowDiff = -1; rowDiff <= 1; rowDiff++)
	{
		for (int colDiff = -1; colDiff <= 1; colDiff++)
		{
			if (rowDiff == 0 && colDiff == 0)
			{
				continue;
			}

			if (m_Row + rowDiff == m_LastRow &&
				m_Col + colDiff == m_LastCol)
			{
				continue;
			}

			if (m_Row + rowDiff >= 0 &&
				m_Col + colDiff >= 0 &&
				m_Row + rowDiff < NUM_OF_CELLS_Y &&
				m_Col + colDiff < NUM_OF_CELLS_X &&
				(s_Map->getCoords()[m_Row + rowDiff][m_Col + colDiff] == 'P' || s_Map->getCoords()[m_Row + rowDiff][m_Col + colDiff] == 'S'))
			{
				possibleMoves.emplace_back(m_Row + rowDiff, m_Col + colDiff);
			}
		}
	}

	return possibleMoves[Random::randint(0, possibleMoves.size() - 1)];
}
