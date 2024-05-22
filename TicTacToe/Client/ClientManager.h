#pragma once
#include "GameManager.h"
#include "ClientNetwork.h"


class ClientManager
{
public:
	ClientManager();
	 int Init();
private:
	GameManager gameManager;
	ClientNetwork clientNetwork;
	
};

