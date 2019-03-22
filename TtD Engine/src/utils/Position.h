#pragma once


class Position
{
public:
	int row = 0;
	int col = 0;

public:
	Position(int row, int col)
		: row(row), col(col)
	{
	}


	// Returns a new position with each element added together
	inline Position operator+(const Position& other)
	{
		return Position(row + other.row, col + other.col);
	}

	// Adds the other position to the current one
	inline void operator+=(const Position& other)
	{
		row += other.row;
		col += other.col;
	}

	// Returns a new position which is equal to the current position minus the other
	inline Position operator-(const Position& other)
	{
		return Position(row - other.row, col - other.col);
	}

	// Subtracts the other position from the current one
	inline void operator-=(const Position& other)
	{
		row -= other.row;
		col -= other.col;
	}

	inline bool operator==(const Position& other) const
	{
		return (row == other.row) && (col == other.col);
	}

	inline bool operator!=(const Position& other) const
	{
		return !(*this == other);
	}
};
