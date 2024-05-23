#pragma once
#include "GameData.h"
#include "Display.h"

class Controller
{

public:
	Controller();
	~Controller();

protected:
	static int totalPlayers;
	int id = 0;

public:	
	void HandleInput(int x, int y, GameData* data, Display* display);
};

