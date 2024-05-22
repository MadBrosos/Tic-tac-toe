#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
    gameManager = new GameManager();
}


int NetworkManager::init(SOCKET &inSocket, bool inIsServer)
{
    currentSocket = &inSocket;
    std::string windowName = "Tic Tac Toe - The Game - " ;
    windowName.append(inIsServer ? "Server" : "Client");
    sf::RenderWindow window(sf::VideoMode(gameManager->windowSize, gameManager->windowSize), windowName);
    currentPlayerController = inIsServer ? gameManager->firstPlayer : gameManager->secondPlayer;
    isServer = inIsServer;
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

void NetworkManager::handleInput(sf::Event event, sf::RenderWindow& window)
{
    if (!gameManager->isGameFinish)
    {
        // send
        if (gameManager->isFirstPlayerTurn == isServer) {
            currentPlayerController->handleInputGame(event, window);

        }
        else {
            recv(*currentSocket, (char*)&changeTile, sizeof(ChangeTileStatus), 0);
            gameManager->grid->changeTileStatus(changeTile);
        }
    }
    else
    {
        if (currentPlayerController->handleInputEndGame(event)) {
            gameManager->restartGame();
            restartGame = true;
            send(*currentSocket, (char*)&restartGame, sizeof(bool), 0);
        }
        recv(*currentSocket, (char*)&restartGame, sizeof(bool), 0);
        gameManager->restartGame();
    }
}

void NetworkManager::display(sf::RenderWindow& window)
{
    gameManager->display(window);
}

DWORD __stdcall NetworkManager::receivedRestartGame(LPVOID param)
{
    return 0;
}

DWORD __stdcall NetworkManager::receivedChangedGridTile(LPVOID param)
{
    return 0;
}
