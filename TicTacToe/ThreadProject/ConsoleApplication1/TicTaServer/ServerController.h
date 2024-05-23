#pragma once
#include "ServerData.h"
#include <winsock2.h>
#include <iostream>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 1024
#define READY_MESSAGE "start"
#define PLAY_MESSAGE "canPlay"
#define END_MESSAGE "end"

class ServerController
{
public:
	ServerController();
	~ServerController();

protected:
	ServerData* serverData;

	SOCKET serverSocket;
	SOCKET firstClientSocket;
	SOCKET secondClientSocket;
	sockaddr firstClientAddr;
	sockaddr secondClientAddr;
	sockaddr_in serverAddr = { 0 };

	void Send(const char* message, SOCKET socket);
	void Receive(char* buffer, sockaddr_in& clientAddr,SOCKET clientSocket);
	void ProcessRequest(char* buffer, sockaddr_in& clientAddr);
	void ResetBoard();
	void StartGame();
	void CloseServer();

public:
	char InitServer();
	void Run();
};

