#include "ClientManager.h"
#include <windows.h>
ClientManager::ClientManager()
{
    clientNetwork = new ClientNetwork();
	gameManager = new GameManager();
    gameManager->grid->currentSocket = &clientNetwork->clientSocket;
}

int ClientManager::init()
{
    sf::RenderWindow window(sf::VideoMode(gameManager->windowSize, gameManager->windowSize), "Tic Tac Toe - Client - The Game");

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
	//return gameManager.initWindow();
}

void ClientManager::handleInput(sf::Event event, sf::RenderWindow& window)
{
     // handle input va etre différent en fonction du client et du serveur
    if (!gameManager->isGameFinish)
    {
        // send
	    if (gameManager->isFirstPlayerTurn) {
            recv(clientNetwork->clientSocket,(char*) &changeTile, sizeof(ChangeTileStatus), 0 );
            gameManager->grid->changeTileStatus(changeTile);
	    }
	    else {
         
            gameManager->secondPlayer->handleInputGame(event, window);
	    }
    }
    else
    {
        if (gameManager->secondPlayer->handleInputEndGame(event)) {
            gameManager->restartGame();
            restartGame = true;
            send(clientNetwork->clientSocket, (char*)&restartGame, sizeof(bool), 0);
        }
        recv(clientNetwork->clientSocket, (char*)&restartGame, sizeof(bool), 0);
        gameManager->restartGame();
    }
}

void ClientManager::display(sf::RenderWindow& window)
{
    gameManager->display(window);
}


