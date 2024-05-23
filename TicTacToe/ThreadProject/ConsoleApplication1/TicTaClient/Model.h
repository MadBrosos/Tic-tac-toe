#pragma once
#include <iostream>
#include <string>

class ModelDisplayer;

class Model
{
public:
	Model();
	~Model();

protected:
	char grid[9];
	char currentPlayer = '1';
	char version = 0;
	char forceUpdate = 0;
	char winner = 3;

	bool canPlay = false;

public:
	char GetVersion();
	bool GetCanPlay();
	void SetCanPlay(bool value);
	char GetforceUpdate() { return forceUpdate; }
	void SetforceUpdate(char value) { forceUpdate = value; }

	void SetValues(std::string state);
	char GetCell(int index);
	bool IsCellEmpty(int index);
	int GetCurrentPlayer();
	void ResetCurrentPlayer() { currentPlayer = '1'; }
	char GetWinner();
	void SetWinner(char value);
	int GetCurrentTurn();
	void Reset();
};

