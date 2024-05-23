#pragma once

class GameData
{
public:
	GameData();
	~GameData();

protected:
	int board[9];
	int currentPlayer;
	int currentTurn;
	int winner;
	
public:
	int GetCell(int index);
	bool IsCellEmpty(int index);
	void SetCell(int index, int value);
	void SetCell(int x,int y, int value);
	void SetCurrentTurn(int value);
	int GetCurrentPlayer();
	int GetWinner();
	int GetCurrentTurn();
	void RefreshWinner();
	void Reset();
	void CheckDraw();
};

