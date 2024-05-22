#pragma once

#define WIN32_LEAN_AND_MEAN
#include "GameManager.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_PORT 5555

class ServerNetwork
{
public:
	ServerNetwork();
	~ServerNetwork();
private:
	void SetupDLL();
	void CreateServerSocket();
	void BindSocket();
	void Listen();
	void AcceptSocket();
	void SendToClient();
	void ReceiveFromClient();
	SOCKET acceptSocket;
	SOCKET serverSocket;
	WSADATA wsaData;
	int wsaerr;
	int bytesCount;
};

