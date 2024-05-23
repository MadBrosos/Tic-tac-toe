#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include <vector>

constexpr auto WIDTH = (1920*0.5f);;
constexpr auto HEIGHT = (1080*0.5f);
constexpr auto CELL_SIZE = 100.0f;
constexpr auto CELL_SPACING = 0.0f;
constexpr auto CELL_THICKNESS = 2.0f;
constexpr auto CIRCLE_RADIUS = CELL_SIZE * 0.40f;
constexpr auto CIRCLE_THICKNESS = 8.0f;
constexpr auto CROSS_LENGTH = CELL_SIZE * 0.8f;
constexpr auto CROSS_THICKNESS = 8.0f;


class Display
{
public:
	Display();
	~Display();
	
protected:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text* firstPlayerNameText;
	sf::Text* secondPlayerNameText;
	sf::Text* winnerText;
	sf::Text* currentTurnText;

	sf::FloatRect cellBounds[9];

	void DisplayGrid();
	void DisplayCircle(int x, int y, int radius);
	void DisplayCross(int x, int y, int length);
	void SetCurrentPlayerText(GameData* data);
	void SetCurrentTurnText(GameData* data);

public:
	sf::RenderWindow* GetWindow();
	void UpdateScreen(GameData* data);
	int IsInCell(int x, int y);
};

