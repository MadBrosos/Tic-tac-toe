#pragma once
#include "Team.h"
#include <SFML/Graphics.hpp>
class Tile
{
	
private:
	Team status;
	sf::Sprite* sprite;
public:
	Tile();
	Tile(float positionX, float positionY, float size);
	~Tile();
	void display(sf::RenderWindow& window);
	void changeStatus(sf::Texture& newTexture, Team status);
	
	bool checkTileClosestIsNeutral(sf::Vector2f& position);
};

