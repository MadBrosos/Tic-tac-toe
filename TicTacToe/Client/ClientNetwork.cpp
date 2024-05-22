#include "ClientNetwork.h"
#include <iostream>
using namespace std;
#include <assert.h>
ClientNetwork::ClientNetwork()
{
	cout << "Client" << endl;
	SetupDLL();
	CreateClientSocket();
	ConnectSocket();
}

ClientNetwork::~ClientNetwork()
{
	system("pause");
	closesocket(clientSocket);
	WSACleanup();
}

void ClientNetwork::SetupDLL()
{
	cout << "Set up DLL" << endl;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		assert("DLL not found");
	}
	else {
		cout << "Dll found " << wsaData.szSystemStatus << endl;
	}
}

void ClientNetwork::CreateClientSocket()
{
	cout << "Create Client Socket" << endl;
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		closesocket(clientSocket);
		WSACleanup();
		assert("Socket Invalid" + WSAGetLastError());
	}
}

void ClientNetwork::ConnectSocket()
{
	cout << "Connected Sockets" << endl;
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(DEFAULT_PORT);
	if (connect(clientSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		closesocket(clientSocket);
		WSACleanup();
		assert("Connect failed" + WSAGetLastError());
	}
	else {
		cout << "Connect Success" << endl;
	}
}

void ClientNetwork::SendToServer()
{
	bytesCount = send(clientSocket, buffer, 200, 0);
	if (bytesCount > 0) {
		cout << "message sent" << buffer << endl;
	}
	else {
		cout << "message failed" << buffer << endl;
		closesocket(clientSocket);
		WSACleanup();
	}
}

void ClientNetwork::ReceiveFromServer()
{
	bytesCount = recv(clientSocket, buffer, 200, 0);
	if (bytesCount > 0) {
		cout << "message received" << buffer << endl;
	}
	else {
		cout << "message failed" << buffer << endl;
		closesocket(clientSocket);
		WSACleanup();
	}
}
