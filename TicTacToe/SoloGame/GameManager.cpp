#include "GameManager.h"
#include <iostream>

void GameManager::handleInput(sf::Event event)
{

}

void GameManager::display(sf::RenderWindow& window)
{
    grid->display(window);
}



GameManager::GameManager()
{
	firstPlayer = new PlayerController();
	secondPlayer = new PlayerController();
	grid = new GridManager(100,100);


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
	sf::Image icon;
    if (!icon.loadFromFile("Assets/ReadDead.png")) {
        std::cout << "Error loading icon" << std::endl;
    }
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


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

            handleInput(event);
        }
        //test
        window.clear(backgroundColor);
     
        display(window);
        window.display();
    }
    return 0; 
}
