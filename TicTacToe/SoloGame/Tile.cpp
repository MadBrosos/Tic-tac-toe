#include "Tile.h"
#include <iostream>
Tile::Tile()
{
	sprite = new sf::Sprite();
}

Tile::Tile(float positionX, float positionY, float scale)
{
	sprite = new sf::Sprite();
	sprite->setPosition(sf::Vector2f(positionX, positionY));
	sprite->setScale(sf::Vector2f(scale, scale));
	
}



Tile::~Tile()
{

}

void Tile::display(sf::RenderWindow& window)
{
	window.draw(*sprite);
}

void Tile::changeStatus(sf::Texture& newTexture, Team newStatus)
{
	sprite->setTexture(newTexture);
	status = newStatus;
	
}



bool Tile::checkTileClosestIsNeutral(sf::Vector2f& position)
{

	if (sprite->getGlobalBounds().contains(position)) {
		
		if (status == Team::Neutral) {
		
			return true;
		}
	}
	return false;
}





