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
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 5555
/*
int main()
{
	cout << "Client" << endl;

	cout << "Set up DLL" << endl;
	SOCKET clientSocket;
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
	cout << "Create Client Socket" << endl;
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Socket Invalid" << WSAGetLastError() << endl;
		closesocket(clientSocket);
		WSACleanup();
		return 0;
	}
	cout << "Set up Client Socket" << endl;
	sockaddr_in address;
	address.sin_family = AF_INET;
	
	InetPton(AF_INET, _T("127.0.0.1"), &address.sin_addr.s_addr);
	address.sin_port = htons(DEFAULT_PORT);
	cout << "Send" << endl;
	char buffer[200] = "send this to server";
	int bytesSent = sendto(clientSocket, (const char*)buffer, strlen(buffer), 0, (struct sockaddr*) &address, sizeof(address));
	if (bytesSent == -1) {

		cout << "Error transmitting data"  << endl;
			closesocket(clientSocket);
		WSACleanup();
		return 0;
	}
	else {
		cout << "Data send :" << buffer << endl;
	}
	system("pause");
	closesocket(clientSocket);
	WSACleanup();
	
	return 0;
}*/