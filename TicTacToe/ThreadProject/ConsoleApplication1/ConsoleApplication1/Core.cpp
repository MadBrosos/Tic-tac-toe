#include "Core.h"

#include "Display.h"
#include "GameData.h"
#include "Controller.h"

#include <iostream>

Core::Core()
	: display()
	, gameData()
	, player1()
	, player2()
{
	window = display.GetWindow();
}

Core::~Core()
{
}

void Core::Init()
{
	auto window = display.GetWindow();

	display.UpdateScreen(&gameData);
}

void Core::Run()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gameData.GetWinner() == -1)
			{
				auto player = gameData.GetCurrentPlayer() == 1 ? player2 : player1;
				auto mousePos = sf::Mouse::getPosition(*window);
				player.HandleInput(mousePos.x, mousePos.y, &gameData, &display);
				gameData.RefreshWinner();
				gameData.CheckDraw();
				display.UpdateScreen(&gameData);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				gameData.Reset();
				display.UpdateScreen(&gameData);
			}
		}
	}

	std::cout << "Oof" << std::endl;
}
