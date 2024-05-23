#include "GameManager.h"
#include <iostream>



void GameManager::display(sf::RenderWindow& window)
{
    grid->display(window);
    window.draw(gameText);
    window.draw(restartText);
}

void GameManager::createAndLoadText()
{
    //Game Text
    this->font.loadFromFile("Assets/Pinky Love.ttf");
    this->gameText.setFont(font);
    this->gameText.setCharacterSize(25);
    setStringText(gameText, 0, "Server - It's time to play !");

    //Restart Text
    this->restartText.setFont(font);
    this->restartText.setCharacterSize(25);
}

void GameManager::changeRestartTextStatus(bool isShow)
{
    if(isShow)
    {
        setStringText(restartText, windowSize - 50.0f , "Server Press Space to restart game");
    }
    else
    {
        setStringText(restartText, windowSize - 50.0f, "");
    }
}

void GameManager::restartGame()
{
    grid->clearGrid();
    isFirstPlayerTurn = true;
    isGameFinish = false;
    changeRestartTextStatus(isGameFinish);
    setStringText(gameText, 0, "Server - It's time to play !");
   
}

void GameManager::setStringText(sf::Text &text,float posY,  std::string name)
{
	text.setString(name);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setPosition(windowSize * 0.5f - bounds.width * 0.5f, posY);
}


GameManager::GameManager(std::function<void(bool)> newOnEndTurn) : isFirstPlayerTurn(true), isGameFinish(false)
{
    grid = new GridManager(std::bind(&GameManager::endPlayerTurn, this, std::placeholders::_1, std::placeholders::_2));
    firstPlayer = new PlayerController(Team::Circle, grid);
	secondPlayer = new PlayerController(Team::Cross, grid );
    onEndTurn = newOnEndTurn;

    createAndLoadText();
}

GameManager::~GameManager()
{
	delete firstPlayer;
	delete secondPlayer;
	delete grid;
}



void GameManager::endPlayerTurn(bool isWin, Team teamSelected)
{
    if(!isWin)
    {
        isFirstPlayerTurn = !isFirstPlayerTurn;
        if(isFirstPlayerTurn)
        {
            setStringText(gameText, 0, "Server - It's time to play !");
        }
        else
        {
            setStringText(gameText, 0, "Client - It's time to play !");
        }
    }
    else
    {
        isGameFinish = true;
        changeRestartTextStatus(isGameFinish);
	    if(teamSelected == Team::Neutral)
	    {
            setStringText(gameText, 0, "It's a Draw !");
	    }
        else
        {
	        if(isFirstPlayerTurn)
	        {
                setStringText(gameText, 0, "Congrats you win Server");
	        }
	        else
	        {
                setStringText(gameText, 0, "Congrats you win Client");
            }
        }
    }
    onEndTurn(isWin);
}
