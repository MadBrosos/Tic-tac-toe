#include "ServerManager.h"

ServerManager::ServerManager()
{
	serverNetwork;
	gameManager = new GameManager();
}

int ServerManager::Init()
{
	return 0;
	//return gameManager->initWindow();
	
}
