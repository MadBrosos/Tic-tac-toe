#include "GridManager.h"
#include <iostream>
bool GridManager::loadGridAssets()
{
    if (!this->crossTexture.loadFromFile("Assets/cross.png"))
        return false;
    if (!this->circleTexture.loadFromFile("Assets/circle.png"))
        return false;    
    if (!this->blankTexture.loadFromFile("Assets/blank.png"))
        return false;
    return true;
}

void GridManager::createGridBackground()
{
    for (unsigned int i = 0; i < 4; i++)
    {
        backgroundLines[i] = sf::RectangleShape(sf::Vector2f(gridSize + gridLineThickness, gridLineThickness));
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

void GridManager::createTiles()
{
    for (unsigned int y = 0; y < 3; y++)
    {
        for (unsigned int x = 0; x < 3; x++)
        {
            int index = y * 3 + x;
            tiles[index] = new Tile(startX+gridLineThickness+x*gridSize/3, startY+ gridLineThickness + y * gridSize / 3, (100.0f-gridLineThickness)/100.0f);
            tiles[index]->changeStatus(blankTexture,Team::Neutral);
        }
    }
}

bool GridManager::TryChangeTileStatus(sf::Vector2f position, Team team)
{
    for (unsigned int i = 0; i < 9; i++)
    {
      
        if (tiles[i]->checkTileClosestIsNeutral(position)) {

            tiles[i]->changeStatus(team == Team::Circle ? circleTexture : crossTexture, team);
            
            return true;
        }
    }
    return false;
}

  

GridManager::GridManager()
{
    createGridBackground();
   
    loadGridAssets();
    createTiles();
}


void GridManager::display(sf::RenderWindow& window)
{


    for (unsigned int i = 0; i < 9; i++)
    {
        tiles[i]->display(window);
    }
    for (unsigned int i = 0; i < 8; i++)
    {
        window.draw(backgroundLines[i]);

    }
}
