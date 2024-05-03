#pragma once
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
	void createGridBackground();
	void createTiles();
	
public:

	GridManager();
	void display(sf::RenderWindow& window);
	bool TryChangeTileStatus(sf::Vector2f position, Team team);
};

