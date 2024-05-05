#pragma once
#include "Team.h"
#include <functional>
#include <SFML/Graphics.hpp>
#include "GridManager.h"

class PlayerController
{
public :
	PlayerController(Team newTeam, GridManager* newGrid, std::function<void()> newRestartCallback);
	~PlayerController();
	void handleInputGame(sf::Event event, sf::RenderWindow& window);
	void handleInputEndGame(sf::Event event);
private:
	Team team;
	GridManager* grid;
	std::function<void()> restartCallback;
};

