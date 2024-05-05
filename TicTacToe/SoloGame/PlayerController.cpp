#include "PlayerController.h"
#include <iostream>
PlayerController::PlayerController(Team newTeam, GridManager* newGrid, std::function<void()> newRestartCallback)
{
	team = newTeam;
	grid = newGrid;
	restartCallback = newRestartCallback;
}

PlayerController::~PlayerController()
{

}

void PlayerController::handleInputGame(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		
		if (event.mouseButton.button == sf::Mouse::Button::Left) {
	
			grid->TryChangeTileStatus(window.mapPixelToCoords(sf::Mouse::getPosition(window)), team);
		}
	}
}

void PlayerController::handleInputEndGame(sf::Event event)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		restartCallback();
	}
}

