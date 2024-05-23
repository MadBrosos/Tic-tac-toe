#include "Model.h"

Model::Model()
{
    for (int i = 0; i < 9; i++)
    {
		grid[i] = 0;
	}
	currentPlayer = '1';
	winner = 3;
	version = 0;
	canPlay = false;
}

Model::~Model()
{

}

char Model::GetVersion()
{
	return version;
}

bool Model::GetCanPlay()
{
	return canPlay;
}

void Model::SetCanPlay(bool value)
{
	canPlay = value;
}

void Model::SetValues(std::string state)
{
    for (int i = 0; i < 9; i++)
    {
		grid[i] = state[i];
	}
	currentPlayer = state[9];

	std::cout << "Model updated" << std::endl;
	
	version++;
	//reinterpret_cast<void(*)()> (callback) ();
}

char Model::GetCell(int index)
{
    if(index < 0 || index > 8) return -1;
    return grid[index] - '0';
}

bool Model::IsCellEmpty(int index)
{
    return GetCell(index) == 0;
}

int Model::GetCurrentPlayer()
{
    return currentPlayer;
}

char Model::GetWinner()
{
    return winner;
}

void Model::SetWinner(char value)
{
	std::cout << " Normally Player " << value << " wins!" << std::endl;
	winner = value;
}

int Model::GetCurrentTurn()
{
	return version;
}

void Model::Reset()
{
	for (int i = 0; i < 9; i++)
	{
		grid[i] = 0;
	}
	currentPlayer = '1';
	version = 0;
	canPlay = false;
	winner = 3;
}
