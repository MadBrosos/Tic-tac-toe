#include "ServerData.h"
#include <iostream>

ServerData::ServerData()
{
	currentTurn = 0;
	winner = 0;
}

ServerData::~ServerData()
{
}

void ServerData::SetValues(char cells[9], char turn, char player)
{
	for (int i = 0; i < 9; i++)
	{
		board[i] = cells[i];
	}
	currentTurn = turn;
	winner = player;
}

void ServerData::SetCell(int index, char value)
{
	if (index < 0 || index > 8) {
		std::cout  << "Invalid index" << std::endl;
		return;
	}
	board[index] = value;
}

void ServerData::SetCurrentTurn(char turn)
{
	currentTurn = turn;
}

void ServerData::RefreshWinner()
{
	if (currentTurn < 4)
	{
		winner = 0;
		return;
	}

	auto check = [&](char a, char b, char c)
		{
			return (board[a] == board[b] && board[b] == board[c] && board[a] != 0) ? board[a] : 0;
		};

	auto checkRow = [&](char a, char size, char* values)
		{
			if (board[a] == 0) return 0;

			for (size_t i = 0; i < size; i += 3)
			{
				auto result = check(values[i], values[i + 1], values[i + 2]);
				if (result != 0)
				{
					return result;
				}
			}
			return 0;
		};

	char row1 = checkRow(0, 9, new char[9] {0, 1, 2, 0, 3, 6, 0, 4, 8});
	if (row1 != 0)
	{
		winner = row1;
		return;
	}
	char row2 = checkRow(4, 9, new char[9] {3, 4, 5, 1, 4, 7, 2, 4, 6});
	if (row2 != 0)
	{
		winner = row2;
		return;
	}
	char row3 = checkRow(8, 6, new char[6] {6, 7, 8, 2, 5, 8});
	winner = row3;
}

char ServerData::GetCell(char index)
{
	if (index < 0 || index > 8) return -1;
	return board[index];
}

bool ServerData::IsCellEmpty(char index)
{
	return GetCell(index) == 0;
}

char ServerData::GetCurrentPlayer()
{
	return (currentTurn % 2) + 1;
}

char ServerData::GetWinner()
{
	//std::cout << "Winner is " << winner + '0' << std::endl;
	return winner;
}

char ServerData::GetCurrentTurn()
{
	return currentTurn;
}

void ServerData::SetShouldRestart(bool value)
{
	shouldRestart = value;
}

bool ServerData::GetShouldRestart()
{
	return shouldRestart;
}


