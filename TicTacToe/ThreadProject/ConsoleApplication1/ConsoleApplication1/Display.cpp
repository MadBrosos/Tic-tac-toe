#include "Display.h"
#include "GameData.h"
#include <iostream>
#include <string>

Display::Display()
{
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
	firstPlayerNameText = new sf::Text();
	secondPlayerNameText = new sf::Text();
	winnerText = new sf::Text();
	currentTurnText = new sf::Text();

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return;
	}

	auto setupText = [&](sf::Text* text,const char* str,int x, int y, int size)
	{
		text->setFont(font);
		text->setString(str);
		text->setCharacterSize(size);
		text->setPosition(x, y);
		text->setFillColor(sf::Color::White);
	};

	setupText(firstPlayerNameText, "Player 1", 0, 0, 24);
	setupText(secondPlayerNameText, "Player 2", 0, 24, 24);
	setupText(winnerText, "Player 1's turn", 0, 72, 24);
	setupText(currentTurnText, "Current Turn: 0", 0, 48, 24);
}

Display::~Display()
{
	delete window;
	delete firstPlayerNameText;
	delete secondPlayerNameText;
	delete winnerText;
}

void Display::DisplayGrid()
{
	int centerWidth = WIDTH / 2;
	int centerHeight = HEIGHT / 2;

	float cellSpacing = 10.0f;

	for (size_t i = 0; i < 9; i++)
	{
		auto x = (i % 3) * (CELL_SIZE + CELL_SPACING) +centerWidth - (1.5f * CELL_SIZE + CELL_SPACING);
		auto y = (i / 3) * (CELL_SIZE + CELL_SPACING) +centerHeight - (1.5f * CELL_SIZE + CELL_SPACING);

		sf::RectangleShape rectangle(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		rectangle.setPosition(x, y);
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setOutlineColor(sf::Color::White);
		rectangle.setOutlineThickness(CELL_THICKNESS);

		rectangle.getLocalBounds();

		window->draw(rectangle);

		cellBounds[i] = rectangle.getGlobalBounds();

		auto pos = cellBounds[i].getPosition();

		//DisplayCircle(pos.x, pos.y,CIRCLE_RADIUS);
		//DisplayCross(pos.x, pos.y,CROSS_LENGTH);
	}
}

void Display::DisplayCircle(int x, int y, int radius)
{
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color::Black);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(CIRCLE_THICKNESS);
	circle.setPosition(x-radius, y-radius);
	window->draw(circle);
}

void Display::DisplayCross(int x, int y, int length)
{
	int x_corner = x - (CELL_SIZE / 2.0f);
	int y_corner = y - (CELL_SIZE / 2.0f);
	int y_corner2 = y_corner + CELL_SIZE - CROSS_THICKNESS;

	sf::RectangleShape line1(sf::Vector2f(CELL_SIZE, CROSS_THICKNESS));
	line1.setPosition(x_corner + 19, y_corner+ 14); // use length instead of magic numbers
	line1.rotate(45);
	line1.setFillColor(sf::Color::White);
	window->draw(line1);
	
	sf::RectangleShape line2(sf::Vector2f(CELL_SIZE, CROSS_THICKNESS));
	line2.setPosition(x_corner+ 12, y_corner2 - 8); // use length instead of magic numbers
	line2.rotate(-45);
	line2.setFillColor(sf::Color::White);
	window->draw(line2);
}

void Display::SetCurrentPlayerText(GameData* data)
{
	int winner = data->GetWinner();

	if (winner != -1)
	{
		winnerText->setString(winner == 3 ? "DRAW !!!" : winner == 2 ? "GG to player 2" : "GG to player 1");
		return;
	}

	winnerText->setString("");
}

void Display::SetCurrentTurnText(GameData* data)
{
	std::string turn = "Current Turn: ";
	turn.append(std::to_string(data->GetCurrentTurn()));

	if (data->GetWinner() == -1)
	{
		std::string player = " (";
		player.append(data->GetCurrentPlayer() == 0 ? "Player 1" : "Player 2");
		player.append("'s turn)");
		turn.append(player);
	}
	
	currentTurnText->setString(turn);
}

sf::RenderWindow* Display::GetWindow()
{
	return window;
}

void Display::UpdateScreen(GameData* data)
{
	std::cout << "Updating Screen" << std::endl;

	window->clear();

	window->draw(*firstPlayerNameText);
	window->draw(*secondPlayerNameText);
	SetCurrentPlayerText(data);
	window->draw(*winnerText);
	SetCurrentTurnText(data);
	window->draw(*currentTurnText);

	DisplayGrid();

	for (size_t i = 0; i < 9; i++)
	{
		auto cellcenter = cellBounds[i].getPosition();
		cellcenter.x += CELL_SIZE / 2;
		cellcenter.y += CELL_SIZE / 2;

		switch (data->GetCell(i))
		{
			case 1:
				DisplayCircle(cellcenter.x, cellcenter.y, CIRCLE_RADIUS);
				break;
			case 2:
				DisplayCross(cellcenter.x, cellcenter.y, CROSS_LENGTH);
				break;
			default:
				break;
		}
	}

	window->display();
}

int Display::IsInCell(int x, int y)
{
	for (size_t i = 0; i < 9; i++)
	{
		if (cellBounds[i].contains(x, y))
		{
			return i;
		}
	}
	return -1;
}
