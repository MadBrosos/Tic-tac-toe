#include "PlayerController.h"
#include <iostream>
PlayerController::PlayerController(Team newTeam, GridManager* newGrid)
{
	team = newTeam;
	grid = newGrid;
}

PlayerController::~PlayerController()
{

}

void PlayerController::handleInputGame(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Button::Left) {
	
			grid->tryChangeTileStatus(window.mapPixelToCoords(sf::Mouse::getPosition(window)), team);
		}
	}
}

bool PlayerController::handleInputEndGame(sf::Event event)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		return true;
	}
	return false;
}

