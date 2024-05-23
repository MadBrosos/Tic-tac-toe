#include "Controller.h"
#include "winsock2.h"
#include <ws2tcpip.h>
#include <iostream>
#include <string>
//#include "processthreadsapi.h"

#pragma comment(lib, "ws2_32.lib")

Controller::Controller()
{
	model = new Model();
}

Controller::~Controller()
{
	delete model;
}

int Controller::InitConnection()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "WSAStartup failed" << std::endl;
		return -1;
	}

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if ((clientSocket) == INVALID_SOCKET)
	{
		std::cout << "socket creation failed" << std::endl;
		return -2;
	}

	if (Connect() == INVALID_SOCKET) {
		return -3;
	};

	return 0;
}

void ReceiveThread(Controller* controller)
{
	while (true)
	{
		controller->Receive();
	}
}

void Controller::InitReceiveThread()
{
	receiveThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReceiveThread, this, 0, NULL);
}

int Controller::Connect()
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, L"127.0.0.1", &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(PORT);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		std::cerr << "connect failed with error: " << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return INVALID_SOCKET;
	}

	std::cout << "Connected to server" << std::endl;

	return 0;
}

void Controller::Receive()
{
	char buffer[BUFFER_SIZE];
	int bytecount = recv(clientSocket, buffer, 1024, 0);
	if (bytecount < 0)
	{
		std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
		return;
	}

	if (bytecount == 0)
	{
		return;
	}

	//std::cout << "Received " << bytecount << " bytes" << std::endl;

	bool changeReady = std::string(buffer).find("start") != std::string::npos;
	bool changePlay = std::string(buffer).find("canPlay") != std::string::npos;
	bool isBoardRefresh = std::string(buffer).find("board:") != std::string::npos;
	bool isEndGame = std::string(buffer).find("end") != std::string::npos;
	bool hasWinner = std::string(buffer).find("win:") != std::string::npos;

	std::cout << "Message:" << buffer /*<< (changePlay ? "' true" : "' false")*/ << std::endl;

	if (changeReady)
	{
		isReady = true;
		model->SetWinner(3);
	}
	if (changePlay)
	{
		model->SetCanPlay(true);
		model->SetforceUpdate(1);
	}
	if (isBoardRefresh)
	{
		auto state = std::string(buffer).substr(6);
		model->SetValues(state);
	}
	if (hasWinner)
	{
		std::cout << "receive winner" << std::endl;
		char winner = (std::string(buffer).substr(4)).c_str()[0];
		model->SetWinner(winner);
		OnEndGame();
		model->SetforceUpdate(1);
	}
}

void Controller::OnEndGame()
{
	std::cout << "End game" << std::endl;
	isEndGame = true;
	model->SetCanPlay(false);
}

void Controller::Send(std::string message, int len)
{
	int bytecount = send(clientSocket, message.c_str(), len, 0);
	if (bytecount <= 0)
	{
		std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
		return;
	}

	std::cout << "Sent " << bytecount << " bytes" << std::endl;
}

void Controller::Disconnect()
{
}

void Controller::SetModelDisplayer(ModelDisplayer* displayer)
{
	modelDisplayer = displayer;
}

void Controller::RequestCellClick(int index)
{
	bool canPlay = (model->GetCanPlay());

	std::cout << "Cell " << index << " click requested" << (canPlay ? " (canPlay)" : "") << std::endl;

	if (canPlay)
	{
		DWORD SuspendThread(HANDLE receiveThread);
		Send(std::to_string(index), 1);
		DWORD ResumeThread(HANDLE receiveThread);
	}
	model->SetCanPlay(false);
}

void Controller::RequestReset()
{
	std::cout << "Reset requested" << std::endl;
	if (isEndGame)
	{
		Send("reset", 5);
		isEndGame = false;
	}
}

Model* Controller::GetModel()
{
	return model;
}
