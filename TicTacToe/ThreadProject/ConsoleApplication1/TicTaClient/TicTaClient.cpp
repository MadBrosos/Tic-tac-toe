#include <iostream>
#include "View.h"
#include "Controller.h"
#include "processthreadsapi.h"


void RunView(View* view)
{
	view->Run();
}

int main()
{
    auto controller = new Controller();
    controller->InitConnection();
    controller->InitReceiveThread();

    auto view = new View();
    view->SetController(controller);

    RunView(view);

    // TODO - add restart mechanic
}