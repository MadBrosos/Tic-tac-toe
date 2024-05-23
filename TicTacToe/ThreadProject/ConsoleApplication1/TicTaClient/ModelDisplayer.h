#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Model.h"

constexpr auto WIDTH = (1920 * 0.5f);;
constexpr auto HEIGHT = (1080 * 0.5f);
constexpr auto CELL_SIZE = 100.0f;
constexpr auto CELL_SPACING = 0.0f;
constexpr auto CELL_THICKNESS = 2.0f;
constexpr auto CIRCLE_RADIUS = CELL_SIZE * 0.40f;
constexpr auto CIRCLE_THICKNESS = 8.0f;
constexpr auto CROSS_LENGTH = CELL_SIZE * 0.8f;
constexpr auto CROSS_THICKNESS = 8.0f;

class ModelDisplayer
{
public:
	ModelDisplayer();
	~ModelDisplayer();

protected:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text* playerTurnText;
	sf::Text* currentTurnText;
	sf::Text* winnerText;

	sf::FloatRect cellBounds[9];

	

	void DisplayGrid();
	void DisplayCircle(int x, int y, int radius);
	void DisplayCross(int x, int y, int length);
	void SetCurrentPlayerText(Model* model);
	void SetCurrentTurnText(Model* model);
	void SetWinnerText(Model* model);

public:
	sf::RenderWindow* GetWindow();
	void UpdateScreen(Model* model);
	int IsInCell(int x, int y);
};

