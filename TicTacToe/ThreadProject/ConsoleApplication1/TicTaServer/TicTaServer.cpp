#include "ServerController.h"

int main()
{
    ServerController serverController;
    if(serverController.InitServer()==0) serverController.Run();
    return 0;
}
