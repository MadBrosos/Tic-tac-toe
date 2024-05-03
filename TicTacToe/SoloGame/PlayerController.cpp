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

void PlayerController::handleInput(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed)
		if (event.mouseButton.button == sf::Mouse::Button::Left) {
	
			grid->TryChangeTileStatus(window.mapPixelToCoords(sf::Mouse::getPosition(window)), team);
		}
			
}

