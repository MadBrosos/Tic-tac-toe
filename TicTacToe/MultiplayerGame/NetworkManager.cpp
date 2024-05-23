#include "NetworkManager.h"
HANDLE hMutex;
HANDLE restartHdl;
DWORD restartThreadId;
HANDLE changedTileHdl;
DWORD changeTileThreadId;
NetworkManager::NetworkManager()
{
    gameManager = new GameManager(std::bind(&NetworkManager::beginTurn, this, std::placeholders::_1));
    hMutex = CreateMutex(NULL, false, LPCWSTR(mutexName));
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
        update();
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
        if (isServer) {
            if (currentPlayerController->handleInputEndGame(event)) {
                if (currentPlayerController->handleInputEndGame(event)) {
               
                    //    ReleaseMutex(hMutex);
                    gameManager->restartGame();
                    restartGame = true;
                    beginTurn(false);
                    std::cout << send(*currentSocket, (char*)&restartGame, sizeof(bool), 0) << std::endl;

                }
            }
        }
       
      
       
    }
}

void NetworkManager::display(sf::RenderWindow& window)
{
    gameManager->display(window);
}

DWORD  WINAPI NetworkManager::receivedRestartGameThread(LPVOID param)
{
    std::cout << "changed restart  " << std::endl;
     WaitForSingleObject(hMutex, INFINITE);
     NetworkManager* networkManager = (NetworkManager*)param;
   
    std::cout << "Launch restart  " << std::endl;
    try {
        networkManager->receivedRestartGame();
    }

    catch (int error) {
        std::cout << "Error restart  receveid  " << std::endl;
    }
 
    ReleaseMutex(hMutex);
    try {
        CloseHandle(restartHdl);
    }
    catch (int error) {
        std::cout << "cannot close by error restart" << error << std::endl;
    }
    std::cout << "Release restart mutex  " << std::endl;
    return 0;
}

DWORD WINAPI NetworkManager::receivedChangedGridTileThread(LPVOID param)
{
    std::cout << "changed grid tile thread  " << std::endl;
     WaitForSingleObject(hMutex, INFINITE);

     NetworkManager* networkManager = (NetworkManager*)param;
   
    std::cout << "launch grid tile thread  " << std::endl;
    try {
      
    networkManager->receivedChangedGridTile();
    }
    
    catch(int error){
        std::cout << "Error tile receveid  " << std::endl;
    }
    ReleaseMutex(hMutex);
    try {
        CloseHandle(changedTileHdl);
    }
    catch (int error) {
        std::cout << "cannot close by error changed tile " << error << std::endl;
    }
    std::cout << "Release change tile thread mutex  " << std::endl;
    return 0;
}

void NetworkManager::receivedRestartGame()
{
  //  std::cout << "restart try " << std::endl;
    int bytesCount = recv(*currentSocket, (char*)&restartGame, sizeof(bool), 0);

    if (bytesCount < 0) {
        std::cout << "Ca bug les tiles" << std::endl;
    }
    else {
        std::cout << "restart received " << std::endl;
        needUpdateRestart = true; 
    
    }
}

void NetworkManager::receivedChangedGridTile()
{
   
    int bytesCount = recv(*currentSocket, (char*)&changeTile, sizeof(ChangeTileStatus), 0);
    if (bytesCount < 0) {
        std::cout<< "Ca bug les tiles" << std::endl;
    }
    else {
        std::cout << "change tile received " << std::endl;
       
        needUpdateTile = true;
    
    }
    

  // check si le thread n'est pas lancé
    // au moment du changement de nos tiles
    // try catch
    // condition 
    // sleep 


  
}

void NetworkManager::beginTurn(bool isWin)
{
    if (isWin) {
        if(!isServer)
 
            restartHdl = CreateThread(NULL, 0, receivedRestartGameThread, this, 0, &restartThreadId);
    }
    else {
        if (gameManager->isFirstPlayerTurn != isServer) {
            changedTileHdl = CreateThread(NULL, 0, receivedChangedGridTileThread, this, 0, &changeTileThreadId);
        }
    }
}

void NetworkManager::update()
{
    if (needUpdateRestart) {

        gameManager->restartGame();
        beginTurn(false);
        needUpdateRestart = false; 

    }
    if (needUpdateTile) {

        needUpdateTile = false; 
        gameManager->grid->changeTileStatus(changeTile);
    }
}
