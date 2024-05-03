#pragma once
#include "Team.h"
#include <SFML/Graphics.hpp>
#include "GridManager.h"

class PlayerController
{
public :
	PlayerController(Team newTeam, GridManager* grid);
	~PlayerController();
	void handleInput(sf::Event event, sf::RenderWindow& window);
private:
	Team team;
	GridManager* grid;

};

