#pragma once
#include <SFML/Graphics.hpp>
class GridManager
{
public:
	int gridSize = 300;
	int gridLineThickness = 20;
	const sf::Color gridLineColor = sf::Color(0, 0, 0, 255);
	GridManager();
	sf::RectangleShape backgroundLines[8];
	void display(sf::RenderWindow& window);
};

