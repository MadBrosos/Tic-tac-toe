#include "ServerManager.h"

ServerManager::ServerManager()
{
	serverNetwork = new ServerNetwork();
	gameManager = new GameManager();
}

int ServerManager::init()
{
    std::cout << "test" << std::endl;
    std::cout << gameManager->windowSize << std::endl;
    sf::RenderWindow window(sf::VideoMode(gameManager->windowSize, gameManager->windowSize), "Tic Tac Toe - Server Manager - The Game");

    //Set Frame Rate
    window.setFramerateLimit(60);

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
        window.clear(gameManager->backgroundColor);

        display(window);
        window.display();
    }
    return 0;
}

void ServerManager::handleInput(sf::Event event, sf::RenderWindow& window)
{
    if (!gameManager->isGameFinish)
    {
        // send
        if (gameManager->isFirstPlayerTurn) {
            gameManager->firstPlayer->handleInputGame(event, window);

        }
        else {
            recv(serverNetwork->socketAccepted, (char*)&changeTile, sizeof(ChangeTileStatus), 0);
            gameManager->grid->changeTileStatus(changeTile);
        }
    }
    else
    {
        if (gameManager->firstPlayer->handleInputEndGame(event)) {
            gameManager->restartGame();
            restartGame = true;
            send(serverNetwork->socketAccepted, (char*)&restartGame, sizeof(bool), 0);
        }
        recv(serverNetwork->socketAccepted, (char*)&restartGame, sizeof(bool), 0);
        gameManager->restartGame();
    }
}

void ServerManager::display(sf::RenderWindow& window)
{
    gameManager->display(window);
   
}
