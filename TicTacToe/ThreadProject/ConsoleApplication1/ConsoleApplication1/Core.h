#pragma once

#include <SFML/Graphics.hpp>
#include "Display.h"
#include "GameData.h"
#include "Controller.h"

class Core
{
public:
	Core();
	~Core();

protected:
	Display display;
	GameData gameData;
	Controller player1;
	Controller player2;
	sf::RenderWindow* window;

public:
	void Init();
	void Run();
};

