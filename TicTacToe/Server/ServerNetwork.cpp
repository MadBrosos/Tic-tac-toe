#include "ServerNetwork.h"
#include <assert.h>

ServerNetwork::ServerNetwork()
{
	std::cout << "SERVER" << std::endl;
	setupDLL();
	createServerSocket();
	bindSocket();
	listen();
	acceptSocket();
}

ServerNetwork::~ServerNetwork()
{
}

void ServerNetwork::setupDLL()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		assert("DLL not found");
	}
	else {
		std::cout << "Dll found " << wsaData.szSystemStatus << std::endl;
	}
}

void ServerNetwork::createServerSocket()
{
	std::cout << "Create Server Socket" << std::endl;
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		WSACleanup();
		assert("Socket Invalid" + WSAGetLastError());
	}
	else {
		std::cout << "Socket Valid" << std::endl;
	}
}

void ServerNetwork::bindSocket()
{
	std::cout << "Bind Sockets" << std::endl;
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(DEFAULT_PORT);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		assert("Bind failed" + WSAGetLastError());
		closesocket(serverSocket);
		WSACleanup();
		
	}
	else {
		std::cout << "Bind Success" << std::endl;
	}
}

void ServerNetwork::listen()
{
	std::cout << "Listen" << std::endl;
	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		std::cout << "Listen failed" << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "Listen is Ok waiting for connection..." << std::endl;
	}
}

void ServerNetwork::acceptSocket()
{
	std::cout << "Accept connection" << std::endl;
	 acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET) {
		assert("Accepted failed" + WSAGetLastError());		
		closesocket(serverSocket);
		WSACleanup();
	}
	else {
		std::cout << "Accepted connection" << std::endl;
	}
}

void ServerNetwork::receiveFromClient()
{
	std::cout << "receive" << std::endl;
	char buffer[200];
	bytesCount = recv(acceptSocket, buffer, 200, 0);
	if (bytesCount > 0) {
		std::cout << "message received" << buffer << std::endl;
	}
	else {
		std::cout << "message failed" << buffer << std::endl;
		closesocket(acceptSocket);
		WSACleanup();
	}
}

void ServerNetwork::sendToClient()
{
	char confirmationBuffer[200] = "Message Received";
	bytesCount = send(acceptSocket, confirmationBuffer, 200, 0);
	if (bytesCount > 0) {
		std::cout << "message sent" << confirmationBuffer << std::endl;
	}
	else {
		std::cout << "message sent" << confirmationBuffer << std::endl;
		closesocket(acceptSocket);
		WSACleanup();
	}
}


