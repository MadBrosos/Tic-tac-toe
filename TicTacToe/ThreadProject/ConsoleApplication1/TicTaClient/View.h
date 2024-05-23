#pragma once
#include <SFML/Graphics.hpp>
#include "ModelDisplayer.h"
#include "Controller.h"

class View
{
public:
	View();
	~View();

protected:
	Controller* controller;
	sf::RenderWindow* window;
	ModelDisplayer* modelDisplayer;

public:
	void SetController(Controller* controller);
	void Run();
};

