#pragma once
#include "Team.h"
#include <SFML/Graphics.hpp>
class Tile
{
	
private:
	unsigned int tileIndex;
	Team status;
	sf::Sprite* sprite;
public:
	Tile();
	Tile(float positionX, float positionY, float size, unsigned int index);
	~Tile();
	bool checkTileClosestIsNeutral(sf::Vector2f& position);
	void display(sf::RenderWindow& window);
	void changeStatus(sf::Texture& newTexture, Team status);
	unsigned int getIndex() const;
	Team getStatus() const;
};

