#pragma once

#define WIN32_LEAN_AND_MEAN
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
	SOCKET socketAccepted;
private:
	void setupDLL();
	void createServerSocket();
	void bindSocket();
	void listen();
	void acceptSocket();
	void sendToClient();
	void receiveFromClient();
	
	SOCKET serverSocket;
	WSADATA wsaData;
	int wsaerr;
	int bytesCount;
	
};

