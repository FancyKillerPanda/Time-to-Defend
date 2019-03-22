#include "pch.h"

#include "Enemy.h"

#include "Settings.h"
#include "utils/Random.h"


Application* Enemy::s_Game = nullptr;
const Map* Enemy::s_Map = nullptr;


Enemy::Enemy(Application* const game, const Map* map, Position position)
	: m_Position(position), m_MoveTime((unsigned int) Random::randint(MIN_ENEMY_MOVE_TIME, MAX_ENEMY_MOVE_TIME))
{
	s_Game = game;
	s_Map = map;

	// Creates the texture and sets its rect
	m_Texture = new Texture("res/txrs/Enemy.png", s_Game->getRenderer());
	m_Texture->setRect(m_Position.col * CELL_SIZE, m_Position.row * CELL_SIZE);

	LOG_INFO("Created enemy.");
}

Enemy::~Enemy()
{
	LOG_INFO("Destroyed enemy.");

	delete m_Texture;
	m_Texture = nullptr;
}

void Enemy::draw()
{
	// Draws the enemy's texture to the screen
	SDL_RenderCopy(s_Game->getRenderer(), m_Texture->getTexture(), nullptr, &m_Texture->getRect());
}

bool Enemy::move()
{
	// Only moves if certain amount of time has passed
	if (m_MoveTimer.getElapsed() < m_MoveTime)
	{
		return true;
	}

	// Gets the next position to move to
	const Position& nextPos = getNextPosition();

	// Enemy has finished moving
	if (nextPos == Position(-1, -1))
	{
		return false;
	}

	// Last position and current position is updated
	m_LastPosition = m_Position;
	m_Position = nextPos;

	// Sets the texture rect
	m_Texture->setRect(m_Position.col * CELL_SIZE, m_Position.row * CELL_SIZE);

	hasMoved = true;
	m_MoveTimer.reset();

	return true;
}

Position Enemy::getNextPosition()
{
	// If the current position is a spawn point after the first move, stop moving
	if (hasMoved &&
		s_Map->getCoords()[m_Position.row][m_Position.col] == 'S')
	{
		return Position(-1, -1);
	}

	std::vector<Position> possibleMoves;

	for (int rowDiff = -1; rowDiff <= 1; rowDiff++)
	{
		for (int colDiff = -1; colDiff <= 1; colDiff++)
		{
			int newRow = m_Position.row + rowDiff;
			int newCol = m_Position.col + colDiff;

			// Would be same as current position
			if (rowDiff == 0 && colDiff == 0)
			{
				continue;
			}

			// Would be same as last position
			if (newRow == m_LastPosition.row &&
				newCol == m_LastPosition.col)
			{
				continue;
			}

			// If the position is in bounds
			if (newRow >= 0 &&
				newCol >= 0 &&
				newRow < NUM_OF_CELLS_Y &&
				newCol < NUM_OF_CELLS_X &&
				(s_Map->getCoords()[newRow][newCol] == 'P' || s_Map->getCoords()[newRow][newCol] == 'S'))
			{
				possibleMoves.emplace_back(newRow, newCol);
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

	// If there is a possible straight move, remove the diagonals
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

	// Returns a random move from the possible ones
	return possibleMoves[Random::randint(0, (int) possibleMoves.size() - 1)];
}
