#include "ClientNetwork.h"
#include <iostream>
using namespace std;
ClientNetwork::ClientNetwork()
{
	cout << "Client" << endl;
	setupDLL();
	createClientSocket();
	connectSocket();
	receiveFromServer();
}

ClientNetwork::~ClientNetwork()
{
	system("pause");
	closesocket(clientSocket);
	WSACleanup();
}

void ClientNetwork::setupDLL()
{
	cout << "Set up DLL" << endl;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "DLL not found" << endl;
	}
	else {
		cout << "Dll found " << wsaData.szSystemStatus << endl;
	}
}

void ClientNetwork::createClientSocket()
{
	cout << "Create Client Socket" << endl;
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		closesocket(clientSocket);
		WSACleanup();
		cout << "Socket Invalid" << WSAGetLastError()<< endl;
	}
}

void ClientNetwork::connectSocket()
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
		cout << "Connect failed" << WSAGetLastError() << endl;
	}
	else {
		cout << "Connect Success" << endl;
	}
}

void ClientNetwork::sendToServer()
{
	bytesCount = send(clientSocket, buffer, 200, 0);
	if (bytesCount > 0) {
		cout << "message sent" << buffer << endl;
	}
	else {
	
		closesocket(clientSocket);
		WSACleanup();
		cout << "Message failed" <<buffer << endl;
	}
}

void ClientNetwork::receiveFromServer()
{
	bytesCount = recv(clientSocket, buffer, 200, 0);
	if (bytesCount > 0) {
		cout << "message received" << buffer << endl;
	}
	else {
	
		cout << "Message failed" << buffer << endl;
		closesocket(clientSocket);
		WSACleanup();
		
	}
}
