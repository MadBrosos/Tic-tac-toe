#pragma once
#include "GameManager.h"
#include "ClientNetwork.h"
#include "ChangeTileStatus.h"
#include <windows.h>
class ClientManager
{
public:
	ClientManager();
	 int init();
	 void handleInput(sf::Event event, sf::RenderWindow& window);
	 void display(sf::RenderWindow& window);
	 DWORD WINAPI receivedRestartGame(LPVOID param);
	 DWORD WINAPI receivedChangedGridTile(LPVOID param);

private:
	sf::Vector2f mousePosition;
	GameManager* gameManager;
	ClientNetwork* clientNetwork;
	ChangeTileStatus changeTile;
	bool restartGame = false;
	HANDLE hdl;
	DWORD threadId;
};

