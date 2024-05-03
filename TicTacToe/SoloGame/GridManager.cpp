#include "GridManager.h"

GridManager::GridManager(float startX, float startY)
{
    for (unsigned int i = 0; i < 4; i++)
    {
        backgroundLines[i] = sf::RectangleShape(sf::Vector2f(gridSize, gridLineThickness));
        backgroundLines[i].setPosition(sf::Vector2f(startX, startY + i * gridSize / 3));
    }
    for (unsigned int i = 4; i < 8; i++)
    {
        backgroundLines[i] = sf::RectangleShape(sf::Vector2f(gridLineThickness, gridSize));
        backgroundLines[i].setPosition(sf::Vector2f(startX + (i - 4) * gridSize / 3, startY));
    }
    for (unsigned int i = 0; i < 8; i++)
    {
        backgroundLines[i].setFillColor(gridLineColor);
    }
}


void GridManager::display(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < 8; i++)
	{
		window.draw(backgroundLines[i]);
	}
}
