

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
// #pragma comment (lib, "Mswsock.lib")
using namespace std;
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 5555
/*
int  main()
{
	cout << "SERVER" << endl;

	cout << "Set up DLL" << endl;
	SOCKET serverSocket;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "DLL not found" << endl;
		return 0;
	}
	else {
		cout << "Dll found " << wsaData.szSystemStatus << endl;
	}

	cout << "Create Server Socket" << endl;
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serverSocket == INVALID_SOCKET) {
		cout << "Socket Invalid" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "Socket Valid" << endl;
	}
	cout << "Bind Sockets" << endl;
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(DEFAULT_PORT);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		cout << "Bind failed" << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		cout << "Bind Success" << endl;
	}
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
	system("pause");
	closesocket(serverSocket);
	WSACleanup();
	
	return 0;
}*/