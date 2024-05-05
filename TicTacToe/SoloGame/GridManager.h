#pragma once
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
#include "Team.h"
#include "Tile.h"
class GridManager
{
private:
	int gridSize = 300;
	int gridLineThickness = 20;
	int startX = 100;
	int startY = 100;	
	const sf::Color gridLineColor = sf::Color(0, 0, 0, 255);
	sf::RectangleShape backgroundLines[8];
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
	void display(sf::RenderWindow& window);
	void clearGrid();
	bool TryChangeTileStatus(sf::Vector2f position, Team team);
};

