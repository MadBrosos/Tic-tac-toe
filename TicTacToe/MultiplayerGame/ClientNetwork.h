#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

using namespace std;
#define DEFAULT_PORT 5555

class ClientNetwork
{
public:
	ClientNetwork();
	~ClientNetwork();	
	SOCKET clientSocket;
private:
	void setupDLL();
	void createClientSocket();
	void connectSocket();
	void sendToServer();
	void receiveFromServer();

	WSADATA wsaData;
	int wsaerr;
	int bytesCount;
	char buffer[200] = "";
};

