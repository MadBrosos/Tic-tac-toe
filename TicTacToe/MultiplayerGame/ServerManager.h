#pragma once
#include "GameManager.h"
#include "ServerNetwork.h"
#include "ChangeTileStatus.h"
#include <windows.h>
class ServerManager
{
public:
	ServerManager();
	ServerNetwork* serverNetwork;
	GameManager* gameManager;
	int init();
	
	void handleInput(sf::Event event, sf::RenderWindow& window);
	void display(sf::RenderWindow& window);
	DWORD WINAPI receivedRestartGame(LPVOID param);
	DWORD WINAPI receivedChangedGridTile(LPVOID param);

private:
	sf::Vector2f mousePosition;

	ChangeTileStatus changeTile;
	bool restartGame = false;
	HANDLE hdl;
	DWORD threadId;
};

