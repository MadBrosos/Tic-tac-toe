
#include "ClientManager.h"

int main()
{
	
	/*
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
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Socket Invalid" << WSAGetLastError() << endl;
		closesocket(clientSocket);
		WSACleanup();
		return 0;
	}

	cout << "Connected Sockets" << endl;
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(DEFAULT_PORT);
	if (connect(clientSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		cout << "Connect failed" << WSAGetLastError() << endl;
		closesocket(clientSocket);
		WSACleanup();
		return 0;
	}
	else {
		cout << "Connect Success" << endl;
	}

	cout << "Send server" << endl;
	char buffer[200] = "Je suis là";
	int bytesCount = send(clientSocket, buffer, 200, 0);
	if (bytesCount > 0) {
		cout << "message sent" << buffer<< endl;
	}
	else {
		cout << "message failed" << buffer << endl;
		closesocket(clientSocket);
		WSACleanup();
	}

	
	 bytesCount = recv(clientSocket, buffer, 200, 0);
	if (bytesCount > 0) {
		cout << "message received" << buffer << endl;
	}
	else {
		cout << "message failed" << buffer << endl;
		closesocket(clientSocket);
		WSACleanup();
	}

	cout << "Set up Client Socket" << endl;
	sockaddr_in address;
	address.sin_family = AF_INET;

	InetPton(AF_INET, _T("127.0.0.1"), &address.sin_addr.s_addr);
	address.sin_port = htons(DEFAULT_PORT);
	cout << "Send" << endl;
	char buffer[200] = "send this to server";
	int bytesSent = sendto(clientSocket, (const char*)buffer, strlen(buffer), 0, (struct sockaddr*)&address, sizeof(address));
	if (bytesSent == -1) {

		cout << "Error transmitting data" << endl;
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
		*/
}