#include "NetworkManager.h"
#include "ServerNetwork.h"
#include "ClientNetwork.h"

#include <string>

#include <assert.h>



int test2 = 5;
HANDLE hdl;
DWORD threadId;
void test() {
	cout << "je fais le test" << endl;
	test2 = 50;
}
/*
DWORD WINAPI BasicThread(LPVOID param) {
	cout << "Thread start" << endl;
	Sleep(2000);
	cout << "Thread end" << endl;
	test();
	cout << test2 << endl;
	test2 = 10;
	cout << test2 << endl;
	CloseHandle(hdl);
	//ResumeThread(hdl);
	//SuspendThread(hdl);
	return 0;
}*/

int main()
{ 

	std::string nameApplication;
	std::cout << "Enter your name: " << std::endl;
	std::getline(cin, nameApplication); // Using getline to capture the entire line
	std::cout << "your name " << nameApplication << std::endl;
	NetworkManager networkManager;
	if (nameApplication == "server") {
		ServerNetwork serverNetwork; 
		return networkManager.init(serverNetwork.socketAccepted, true);
	}
	else if(nameApplication == "client") {
		ClientNetwork clientNetwork;
		return networkManager.init(clientNetwork.clientSocket, false);
	
	}
	
	//CloseHandle(hdl);
	//hdl = CreateThread(NULL, 0, BasicThread, NULL, 0, &threadId);
	//std::cout << "test" << std::endl;


}