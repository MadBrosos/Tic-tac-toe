#include "ModelDisplayer.h"
#include <iostream>
#include <string>

ModelDisplayer::ModelDisplayer()
{
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
	playerTurnText = new sf::Text();
	currentTurnText = new sf::Text();
	winnerText = new sf::Text();

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return;
	}

	auto setupText = [&](sf::Text* text, const char* str, int x, int y, int size)
		{
			text->setFont(font);
			text->setString(str);
			text->setCharacterSize(size);
			text->setPosition(x, y);
			text->setFillColor(sf::Color::White);
		};

	setupText(playerTurnText, "Player 1's turn", 0, 0, 24);
	setupText(currentTurnText, "Current Turn: 0", 0, 24, 24);
	setupText(winnerText, "", 0, 48, 24);
}

ModelDisplayer::~ModelDisplayer()
{
	delete window;
	delete playerTurnText;
}

void ModelDisplayer::DisplayGrid()
{
	int centerWidth = WIDTH / 2;
	int centerHeight = HEIGHT / 2;

	float cellSpacing = 10.0f;

	for (size_t i = 0; i < 9; i++)
	{
		auto x = (i % 3) * (CELL_SIZE + CELL_SPACING) + centerWidth - (1.5f * CELL_SIZE + CELL_SPACING);
		auto y = (i / 3) * (CELL_SIZE + CELL_SPACING) + centerHeight - (1.5f * CELL_SIZE + CELL_SPACING);

		sf::RectangleShape rectangle(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		rectangle.setPosition(x, y);
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setOutlineColor(sf::Color::White);
		rectangle.setOutlineThickness(CELL_THICKNESS);

		cellBounds[i] = rectangle.getGlobalBounds();

		window->draw(rectangle);
	}
}

void ModelDisplayer::DisplayCircle(int x, int y, int radius)
{
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color::Black);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(CIRCLE_THICKNESS);
	circle.setPosition(x - radius, y - radius);
	window->draw(circle);
}

void ModelDisplayer::DisplayCross(int x, int y, int length)
{
	int x_corner = x - (CELL_SIZE / 2.0f);
	int y_corner = y - (CELL_SIZE / 2.0f);
	int y_corner2 = y_corner + CELL_SIZE - CROSS_THICKNESS;

	sf::RectangleShape line1(sf::Vector2f(CELL_SIZE, CROSS_THICKNESS));
	line1.setPosition(x_corner + 19, y_corner + 14); // use length instead of magic numbers
	line1.rotate(45);
	line1.setFillColor(sf::Color::White);
	window->draw(line1);

	sf::RectangleShape line2(sf::Vector2f(CELL_SIZE, CROSS_THICKNESS));
	line2.setPosition(x_corner + 12, y_corner2 - 8); // use length instead of magic numbers
	line2.rotate(-45);
	line2.setFillColor(sf::Color::White);
	window->draw(line2);
}

void ModelDisplayer::SetCurrentPlayerText(Model* model)
{
	std::string str = "Player ";
	str = str.append(model->GetCurrentPlayer() == '1' ? "1" : "2");
	str = str.append("'s turn");

	if (model->GetCanPlay()) str = str.append(" (YOU)");

	playerTurnText->setString(str);
	window->draw(*playerTurnText);
}

void ModelDisplayer::SetCurrentTurnText(Model* model)
{
	std::string str = "Current Turn: ";
	str += std::to_string(model->GetCurrentTurn());

	currentTurnText->setString(str);
	//
	// window->draw(*currentTurnText);
}

void ModelDisplayer::SetWinnerText(Model* model)
{
	if (model->GetWinner() == 3) return;
	if (model->GetWinner() == '0')
	{
		std::cout << "It's a draw!" << std::endl;
		winnerText->setString("It's a draw!");
		window->draw(*winnerText);
		return;
	}
	std::string str = "Player ";
	str = str.append(model->GetWinner() == '1' ? "1" : "2");
	str = str.append(" wins!");
	std::cout << "so it's " << str << std::endl;
	winnerText->setString(str);
	window->draw(*winnerText);
}

sf::RenderWindow* ModelDisplayer::GetWindow()
{
	return window;
}

void ModelDisplayer::UpdateScreen(Model* model)
{
	std::cout << "UpdateScreen" << std::endl;

	window->clear();


	DisplayGrid();

	for (size_t i = 0; i < 9; i++)
	{
		int x = (i % 3) * (CELL_SIZE + CELL_SPACING) + WIDTH / 2 - (1.5f * CELL_SIZE + CELL_SPACING) + CELL_SIZE / 2;
		int y = (i / 3) * (CELL_SIZE + CELL_SPACING) + HEIGHT / 2 - (1.5f * CELL_SIZE + CELL_SPACING) + CELL_SIZE / 2;

		if (model->GetCell(i) == 1)
		{
			DisplayCircle(x, y, CIRCLE_RADIUS);
		}
		else if (model->GetCell(i) == 2)
		{
			DisplayCross(x, y, CROSS_LENGTH);
		}
	}

	SetCurrentPlayerText(model);
	SetCurrentTurnText(model);
	SetWinnerText(model);

	window->display();
}

int ModelDisplayer::IsInCell(int x, int y)
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
