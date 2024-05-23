#pragma once
#include "GameManager.h"
#include "ServerNetwork.h"
#include "ChangeTileStatus.h"

class ServerManager
{
public:
	ServerManager();
	ServerNetwork* serverNetwork;
	GameManager* gameManager;
	int init();
	
	void handleInput(sf::Event event, sf::RenderWindow& window);
	void display(sf::RenderWindow& window);

private:
	sf::Vector2f mousePosition;
	GameManager* gameManager;
	ChangeTileStatus changeTile;
	bool restartGame = false;
};

