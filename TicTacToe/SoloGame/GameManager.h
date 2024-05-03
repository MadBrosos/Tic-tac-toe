#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerController.h"
#include "GridManager.h"
class GameManager
{
public:
	PlayerController* firstPlayer;
	PlayerController* secondPlayer;
	GridManager* grid;
	
	

	GameManager();
	~GameManager();
	int initWindow();
private:
	const sf::Color backgroundColor = sf::Color(122, 122, 122, 255);
	const int windowSize = 500;
	void handleInput(sf::Event event);
	void display(sf::RenderWindow& window);


	
};

