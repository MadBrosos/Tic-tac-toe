
#include "ServerManager.h"


int  main()
{
	ServerManager serverManager;
	return serverManager.init();
	/*

	std::cout << "SERVER" << std::endl;

	std::cout << "Set up DLL" << std::endl;
	SOCKET serverSocket;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		std::cout << "DLL not found" << std::endl;
		return 0;
	}
	else {
		std::cout << "Dll found " << wsaData.szSystemStatus << std::endl;
	}

	std::cout << "Create Server Socket" << std::endl;
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Socket Invalid" << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "Socket Valid" << std::endl;
	}
	std::cout << "Bind Sockets" << std::endl;
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(DEFAULT_PORT);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		std::cout << "Bind failed" << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "Bind Success" << std::endl;
	}

	std::cout << "Listen" << std::endl;
	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		std::cout << "Listen failed" << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "Listen is Ok waiting for connection..." << std::endl;
	}
	std::cout << "Accept connection" << std::endl;
	SOCKET acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET) {
		std::cout << "Accepted failed" << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "Accepted connection" << std::endl;
	}

	std::cout << "receive" << std::endl;
	char buffer[200];
	int bytesCount = recv(acceptSocket, buffer, 200, 0);
	if (bytesCount > 0) {
		std::cout << "message received" << buffer << std::endl;
	}
	else {
		std::cout << "message failed" << buffer << std::endl;
		closesocket(acceptSocket);
		WSACleanup();
	}
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
	system("pause");	
	closesocket(serverSocket);
	WSACleanup();
	/*
	cout << "Receive" << endl;
	char buffer[200] = "";
	sockaddr_in clientAdress;
	int clientAdress_length = (int)sizeof(clientAdress);
	int bytes_received = recvfrom(serverSocket, buffer, 200, 0, (struct sockaddr*)&clientAdress, &clientAdress_length);
	if (bytes_received < 0) {
		cout << "Could not receive datagram" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		cout << "Data received :" << buffer << endl;
	}
	

	*/
	return 0;
}