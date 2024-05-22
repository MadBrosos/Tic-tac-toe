#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerController.h"
#include "GridManager.h"

class GameManager
{
public:
	PlayerController* firstPlayer;
	PlayerController* secondPlayer;
	GridManager* grid;
	GameManager();
	~GameManager();
	int initWindow();
	void endPlayerTurn(bool isWin, Team teamSelected);
private:
	const sf::Color backgroundColor = sf::Color(122, 122, 122, 255);
	const int windowSize = 500;
	bool isFirstPlayerTurn = true;
	bool isGameFinish = false;
	sf::Text gameText;
	sf::Text restartText;
	sf::Font font;
	void handleInput(sf::Event event, sf::RenderWindow& window);
	void display(sf::RenderWindow& window);
	void setStringText(sf::Text& text, float posY, std::string name);
	void createAndLoadText();
	void changeRestartTextStatus(bool isShow);
	void restartGame();
};

