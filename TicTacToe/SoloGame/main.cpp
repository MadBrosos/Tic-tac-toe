#include <iostream>
#include <windows.h>
using namespace std;
int test2 = 5;
HANDLE hdl;
void test() {
	cout << "je fais le test" << endl;
	test2 = 50;
}

DWORD WINAPI BasicThread(LPVOID param) {
	cout << "Thread start" << endl;
	Sleep(2000);
	cout << "Thread end" << endl;
	test();
	cout << test2 << endl;
	test2 = 10;
	cout << test2 << endl;
	//ResumeThread(hdl);
	//SuspendThread(hdl);
	return 0;
}

int main()
{ 
	DWORD threadId;
	//CloseHandle(hdl);
//	hdl = CreateThread(NULL, 0, BasicThread, NULL, 0, &threadId);
//	std::cout << "test" << std::endl;
	//system("pause");
	return 0;
//	std::cout << "test" <<std::endl;
 // GameManager gameManager;
   //return gameManager.initWindow();
}