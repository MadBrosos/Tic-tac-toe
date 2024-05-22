#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
    gameManager = new GameManager(std::bind(&NetworkManager::beginTurn, this, std::placeholders::_1));
   
}


int NetworkManager::init(SOCKET &inSocket, bool inIsServer)
{
    currentSocket = &inSocket;
    gameManager->grid->currentSocket = currentSocket;
    std::string windowName = "Tic Tac Toe - The Game - " ;
    windowName.append(inIsServer ? "Server" : "Client");
    sf::RenderWindow window(sf::VideoMode(gameManager->windowSize, gameManager->windowSize), windowName);
    currentPlayerController = inIsServer ? gameManager->firstPlayer : gameManager->secondPlayer;
    isServer = inIsServer;
    beginTurn(false);
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
    }
    else
    {
        if (currentPlayerController->handleInputEndGame(event)) {
            gameManager->restartGame();
            restartGame = true;
            beginTurn(false);
          std::cout<< send(*currentSocket, (char*)&restartGame, sizeof(bool), 0) << std::endl;
          CloseHandle(restartHdl);
        }
       
    }
}

void NetworkManager::display(sf::RenderWindow& window)
{
    gameManager->display(window);
}

DWORD _stdcall NetworkManager::receivedRestartGameThread(LPVOID param)
{
    NetworkManager* networkManager = (NetworkManager*)param;
    networkManager->receivedRestartGame();
    return 0;
}

DWORD _stdcall NetworkManager::receivedChangedGridTileThread(LPVOID param)
{
    std::cout << "changed grid tile thread  " << std::endl;
    NetworkManager* networkManager = (NetworkManager*)param;

    networkManager->receivedChangedGridTile();
    return 0;
}

void NetworkManager::receivedRestartGame()
{
    std::cout << "restart try " << std::endl;
    recv(*currentSocket, (char*)&restartGame, sizeof(bool), 0);
    std::cout << "restart received " << std::endl;
    gameManager->restartGame();
    beginTurn(false);
    try {
    CloseHandle(restartHdl);
    }
    catch (int error) {
        std::cout << "cannot close by error restart" << error << std::endl;
    }
}

void NetworkManager::receivedChangedGridTile()
{
   
    int bytesCount = recv(*currentSocket, (char*)&changeTile, sizeof(ChangeTileStatus), 0);

  // check si le thread n'est pas lancé
    // au moment du changement de nos tiles
    // try catch
    // condition 
    // sleep 

    gameManager->grid->changeTileStatus(changeTile);
    try {
     CloseHandle(changedTileHdl);
    }
    catch(int error){
        std::cout<<"cannot close by error changed tile "  << error <<std::endl;
    }
  
}

void NetworkManager::beginTurn(bool isWin)
{
    if (isWin) {
        restartHdl = CreateThread(NULL, 0, receivedRestartGameThread, this, 0, &restartThreadId);
    }
    else {
        if (gameManager->isFirstPlayerTurn != isServer) {
            changedTileHdl = CreateThread(NULL, 0, receivedChangedGridTileThread, this, 0, &changeTileThreadId);
        }
    }
}
