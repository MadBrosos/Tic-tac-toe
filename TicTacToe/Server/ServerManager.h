#pragma once
#include "GameManager.h"
#include "ServerNetwork.h"

class ServerManager
{
public:
	ServerManager();
	ServerNetwork serverNetwork;
	GameManager* gameManager;
	int Init();
	
};

