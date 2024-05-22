#include <iostream>>
#include "GridManager.h"
#include "ChangeTileStatus.h"

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

bool GridManager::isFull() const
{
    for (unsigned int i = 0; i < 9; i++)
    {
        if(tiles[i]->getStatus() == Team::Neutral)
        {
            return false;
        }
    }
    return true;
}

void GridManager::createGridBackground()
{
    for (unsigned int i = 0; i < 4; i++)
    {
        backgroundLines[i] = new sf::RectangleShape(sf::Vector2f(gridSize + gridLineThickness, gridLineThickness));
        backgroundLines[i]->setPosition(sf::Vector2f(startX, startY + i * gridSize / 3));
    }
    for (unsigned int i = 4; i < 8; i++)
    {
        backgroundLines[i] = new sf::RectangleShape(sf::Vector2f(gridLineThickness, gridSize));
        backgroundLines[i]->setPosition(sf::Vector2f(startX + (i - 4) * gridSize / 3, startY));
    }
    for (unsigned int i = 0; i < 8; i++)
    {
        backgroundLines[i]->setFillColor(gridLineColor);
    }
}

void GridManager::createTiles()
{
   
    for (unsigned int y = 0; y < 3; y++)
    {
        for (unsigned int x = 0; x < 3; x++)
        {
            int index = y * 3 + x;
            tiles[index] = new Tile(startX+gridLineThickness+x*gridSize/3, startY+ gridLineThickness + y * gridSize / 3, (100.0f-gridLineThickness)/100.0f, index);
            tiles[index]->changeStatus(blankTexture,Team::Neutral);
        }
    }
}

void GridManager::updateGridState(Tile* checkTile)
{
    unsigned int row = (checkTile->getIndex() / 3) * 3;
    unsigned int column= checkTile->getIndex() % 3;
    const Team currentStatus = checkTile->getStatus();

    //Rows
    if(tiles[row]->getStatus() == currentStatus
        && tiles[row+1]->getStatus() == currentStatus
        && tiles[row+2]->getStatus() == currentStatus)
    {
        onChangeStatus(true, currentStatus);
    }
    //Column
    else if (tiles[column]->getStatus() == currentStatus
        && tiles[column + 3]->getStatus() == currentStatus
        && tiles[column + 6]->getStatus() == currentStatus)
    {
        onChangeStatus(true, currentStatus);
    }
    //Diagonal Left
    else if (tiles[0]->getStatus() == currentStatus
        && tiles[4]->getStatus() == currentStatus
        && tiles[8]->getStatus() == currentStatus)
    {
        onChangeStatus(true, currentStatus);
    }
	//Diagonal Right
    else if (tiles[2]->getStatus() == currentStatus
        && tiles[4]->getStatus() == currentStatus
        && tiles[6]->getStatus() == currentStatus)
    {
        onChangeStatus(true, currentStatus);
    }
    else if(isFull())
    {
        onChangeStatus(true, Team::Neutral);
    }
    else
    {
        onChangeStatus(false, Team::Neutral);
    }
}

void GridManager::clearGrid()
{
    for (unsigned int i = 0; i < 9; i++)
    {
    	tiles[i]->changeStatus(blankTexture, Team::Neutral);
    }
}

bool GridManager::tryChangeTileStatus(sf::Vector2f position, Team team)
{

    for (unsigned int i = 0; i < 9; i++)
    {
        if (tiles[i]->checkTileClosestIsNeutral(position)) {
            ChangeTileStatus change;
            change.team = team;
            change.tileIndex = i;
            changeTileStatus(change);
           std::cout << send(*currentSocket, (char*) &change, sizeof(ChangeTileStatus),0 ) << std::endl;
        	return true;
        }
    }
    return false;
}

void GridManager::changeTileStatus(ChangeTileStatus change)
{
    tiles[change.tileIndex]->changeStatus(change.team == Team::Circle ? circleTexture : crossTexture, change.team);
    updateGridState(tiles[change.tileIndex]);
}


  

GridManager::GridManager(std::function<void(bool, Team)> newChangeStatus)
{
    createGridBackground();
   
    loadGridAssets();
    createTiles();
    onChangeStatus = newChangeStatus;
   
}

GridManager::~GridManager()
{
    for (int i = 8; i >= 0; i--)
    {
        delete tiles[i];
    }
    for (int i = 7; i >= 0; i--)
    {
        delete backgroundLines[i];
    }
}


void GridManager::display(sf::RenderWindow& window)
{
    for (unsigned int i = 0; i < 9; i++)
    {
        tiles[i]->display(window);
    }
    for (unsigned int i = 0; i < 8; i++)
    {
        window.draw(*backgroundLines[i]);

    }
}
