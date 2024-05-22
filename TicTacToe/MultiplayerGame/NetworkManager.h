#pragma once
#include "GameManager.h"
#include "ClientNetwork.h"
#include "ChangeTileStatus.h"
#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#include "PlayerController.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
class NetworkManager
{
public:
	NetworkManager();

	int init(SOCKET& socket, bool isServer);
	void handleInput(sf::Event event, sf::RenderWindow& window);
	void display(sf::RenderWindow& window);
	static DWORD WINAPI receivedRestartGameThread(LPVOID param);
	static DWORD WINAPI receivedChangedGridTileThread(LPVOID param);
	void  receivedRestartGame();
	void receivedChangedGridTile();
	void beginTurn(bool isWin);
	private:
		SOCKET* currentSocket;
	sf::Vector2f mousePosition;
	GameManager* gameManager;
	ChangeTileStatus changeTile;
	PlayerController* currentPlayerController;
	bool restartGame = false;
	bool isServer = true;
	HANDLE restartHdl;
	DWORD restartThreadId;

	HANDLE changedTileHdl;
	DWORD changeTileThreadId;

};

