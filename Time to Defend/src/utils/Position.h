#pragma once

#include "pch.h"


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


	inline Position operator+(const Position& other)
	{
		return Position(row + other.row, col + other.col);
	}

	inline void operator+=(const Position& other)
	{
		row += other.row;
		col += other.col;
	}

	inline Position operator-(const Position& other)
	{
		return Position(row - other.row, col - other.col);
	}

	inline void operator-=(const Position & other)
	{
		row -= other.row;
		col -= other.col;
	}
};
