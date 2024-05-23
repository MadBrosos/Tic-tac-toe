#pragma once
#include "Model.h"
#include "ModelDisplayer.h"
#include "winsock2.h"
#include <ws2tcpip.h>

#define PORT 8080
#define BUFFER_SIZE 1024

class Controller
{
public:
	Controller();
	~Controller();

protected:
	Model* model;
	ModelDisplayer* modelDisplayer;
	SOCKET clientSocket;
	HANDLE receiveThread;

	bool isReady = false;
	bool isEndGame = false;

	int Connect();
	void Send(std::string message, int len);
	void Disconnect();

public:
	void Receive();
	void OnEndGame();
	int InitConnection();
	void InitReceiveThread();
	void SetModelDisplayer(ModelDisplayer*);
	void RequestCellClick(int);
	void RequestReset();
	Model* GetModel();
};

