#include "GameData.h"
#include <iostream>

GameData::GameData()
{
	currentPlayer = 0;
	currentTurn = 0;
	winner = -1;
	for (size_t i = 0; i < 9; i++)
	{
		grid[i] = -1;
	}
}

GameData::~GameData()
{
}

void GameData::SetCell(int index, int value)
{
	grid[index] = value;
}

void GameData::SetCell(int x, int y, int value)
{
}

void GameData::SetCurrentTurn(int value)
{
	currentTurn = value;
	currentPlayer = currentTurn % 2;
}

int GameData::GetCurrentPlayer()
{
	return currentPlayer;
}

int GameData::GetWinner()
{
	return winner;
}

int GameData::GetCurrentTurn()
{
	return currentTurn;
}

void GameData::RefreshWinner()
{
	if (currentTurn < 4)
	{
		winner = -1;
		return;
	}

	auto check = [&](int a, int b, int c)
		{
			return (grid[a] == grid[b] && grid[b] == grid[c] && grid[a] != -1) ? grid[a] : -1;
		};

	auto checkRow = [&](int a, int size, int* values)
		{
			if (grid[a] == -1) return -1;

			for (size_t i = 0; i < size; i += 3)
			{
				auto result = check(values[i], values[i + 1], values[i + 2]);
				if (result != -1)
				{
					return result;
				}
			}
			return -1;
		};

	int row1 = checkRow(0, 9, new int[9] {0, 1, 2, 0, 3, 6, 0, 4, 8});
	if (row1 != -1)
	{
		winner = row1;
		return;
	}
	int row2 = checkRow(4, 9, new int[9] {3, 4, 5, 1, 4, 7, 2, 4, 6});
	if (row2 != -1)
	{
		winner = row2;
		return;
	}
	int row3 = checkRow(8, 6, new int[6] {6, 7, 8, 2, 5, 8});
	winner = row3;
}

void GameData::Reset()
{
	currentPlayer = 0;
	currentTurn = 0;
	winner = -1;
	for (size_t i = 0; i < 9; i++)
	{
		grid[i] = -1;
	}
}

void GameData::CheckDraw()
{
	if (winner != -1) return;
	bool draw = true;
	for (size_t i = 0; i < 9; i++)
	{
		if (grid[i] == -1)
		{
			draw = false;
			break;
		}
	}
	if (draw)
	{
		winner = 3;
	}
}

int GameData::GetCell(int index)
{
	return grid[index];
}

bool GameData::IsCellEmpty(int index)
{
	return GetCell(index) == -1;
}
