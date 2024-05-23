#include "ServerController.h"
#include "winsock2.h"
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

ServerController::ServerController()
{
	serverData = new ServerData();
}

ServerController::~ServerController()
{
	delete serverData;
}

char ServerController::InitServer()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        std::cerr << "socket creation failed" << std::endl;
        return -2;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (const sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "bind failed" << std::endl;
        return -3;
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR)
    {
        std::cerr << "listen failed" << std::endl;
        return -4;
    };
    std::cout << "Server initialized. Waiting for clients..." << std::endl;

    int* len = new int(sizeof(sockaddr));
    firstClientSocket = accept(serverSocket, &firstClientAddr, len);
    if (firstClientSocket == INVALID_SOCKET)
    {
        std::cerr << "accept 1 failed " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -5;
    }

    std::cout << "Accept 1 connection " << std::endl;

    len = new int(sizeof(sockaddr));
    secondClientSocket = accept(serverSocket, &secondClientAddr, len);
    if (secondClientSocket == INVALID_SOCKET)
    {
        std::cerr << "accept 2 failed " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -6;
    }

    std::cout << "Accept 2 connection " << std::endl;

    return 0;
}

void ServerController::Send(const char* message, SOCKET socket)
{
    if (send(socket, message, strlen(message), 0) == -1)
    {
        std::cout << "send failed" << WSAGetLastError() << std::endl;
    }
}

void ServerController::Receive(char* buffer, sockaddr_in& clientAddr, SOCKET clientSocket)
{
    int len = sizeof(clientAddr);
    memset(buffer, 0, BUFFER_SIZE);
    if (recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, (sockaddr*)&clientAddr, &len) == INVALID_SOCKET)
    {
        std::cout << "recvfrom failed" << std::endl;
    }
}

void ServerController::ProcessRequest(char* buffer, sockaddr_in& clientAddr)
{
    std::cout << "Received: " << buffer << std::endl;
    char currentPlayer = serverData->GetCurrentPlayer();
    if (std::string(buffer).find("reset") != std::string::npos)
    {
		ResetBoard();
	}
    else
    {
        int position = buffer[0] - '0';

        // TODO: Check if the position is valid
        if (serverData->GetCell(position) != 0)
        {
            std::cout << "Invalid move" << std::endl;
            return;
        }
        serverData->SetCell(position, currentPlayer);
        serverData->RefreshWinner();
    }

    currentPlayer = serverData->GetCurrentPlayer();
    std::cout << "Current player: " << currentPlayer << std::endl;


    serverData->SetCurrentTurn(serverData->GetCurrentTurn() + 1);

    std::string message = "board:";

    for (int i = 0; i < 9; i++)
    {
        message += serverData->GetCell(i) + '0';
    }

    currentPlayer = serverData->GetCurrentPlayer();

    message += currentPlayer + '0';

    std::cout << message << std::endl;
    Send(message.c_str(), firstClientSocket);
    Send(message.c_str(), secondClientSocket);

    if (serverData->GetWinner() != 0 || serverData->GetCurrentTurn() == 9)
    {
        char winner = serverData->GetWinner() + '0';

        std::string msgWin = "win:";
        msgWin = msgWin.append(1, winner);

        std::cout << "Player " << winner << " wins!" << std::endl;
        std::cout << "sending: " << msgWin << std::endl;
        Send(msgWin.c_str(), firstClientSocket);
        Send(msgWin.c_str(), secondClientSocket);
	}
}

void ServerController::ResetBoard()
{
    delete serverData;
    serverData = new ServerData();
}

void ServerController::StartGame()
{
    std::cout << "Game started" << std::endl;

    ResetBoard();

    Send(READY_MESSAGE, firstClientSocket);
    Send(READY_MESSAGE, secondClientSocket);
}

void ServerController::CloseServer()
{
    closesocket(serverSocket);
	WSACleanup();
}

void ServerController::Run()
{
    char buffer[BUFFER_SIZE] = { 0 };
    sockaddr_in clientAddr = { 0 };
    StartGame();
    serverData->SetShouldRestart(false);
    serverData->RefreshWinner();
    while(!serverData->GetShouldRestart())
    {
        auto clientSocket = (serverData->GetCurrentPlayer() == 1) ? firstClientSocket : secondClientSocket;

        if(serverData->GetWinner() == 0) Send(PLAY_MESSAGE, clientSocket);

        Receive(buffer, clientAddr, clientSocket);

        ProcessRequest(buffer, clientAddr);
    }


    Run();
}