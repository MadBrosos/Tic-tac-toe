#pragma once
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
#include "Team.h"
#include "Tile.h"
#include "ChangeTileStatus.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

class GridManager
{
private:
	int gridSize = 300;
	int gridLineThickness = 20;
	int startX = 100;
	int startY = 100;	
	const sf::Color gridLineColor = sf::Color(0, 0, 0, 255);
	sf::RectangleShape* backgroundLines[8];
	Tile* tiles[9];

	sf::Texture circleTexture;
	sf::Texture crossTexture;
	sf::Texture blankTexture;
	bool loadGridAssets();
	bool isFull() const;
	void createGridBackground();
	void createTiles();
	void updateGridState(Tile* checkTile);
	std::function<void(bool, Team)> onChangeStatus;
public:
	GridManager(std::function<void(bool, Team)> newChangeStatus);
	~GridManager();
	void display(sf::RenderWindow& window);
	SOCKET* currentSocket;
	void clearGrid();
	bool tryChangeTileStatus(sf::Vector2f position, Team team);
	void changeTileStatus(ChangeTileStatus change);
};

