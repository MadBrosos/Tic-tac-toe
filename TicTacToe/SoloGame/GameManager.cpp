#include "GameManager.h"
#include <iostream>

void GameManager::handleInput(sf::Event event, sf::RenderWindow& window)
{
    if (isFirstPlayerTurn) {
        firstPlayer->handleInput(event, window);
    }
    else {
        secondPlayer->handleInput(event, window);
    }
}

void GameManager::display(sf::RenderWindow& window)
{
    grid->display(window);
}





GameManager::GameManager()
{
    grid = new GridManager();
	firstPlayer = new PlayerController(Team::Circle, grid);
	secondPlayer = new PlayerController(Team::Cross, grid);
	
}

GameManager::~GameManager()
{
	delete firstPlayer;
	delete secondPlayer;
	delete grid;
}

int GameManager::initWindow()
{
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Tic Tac Toe - The Game");

    //game manager
    // player
    
	//Set Icon for the window



	//Set Frame Rate
	window.setFramerateLimit(60);

	//game loop
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            handleInput(event, window);
            
        }
        //test
        window.clear(backgroundColor);
     
        display(window);
        window.display();
    }
    return 0; 
}
