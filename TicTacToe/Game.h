#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <iostream>

class Game
{
private:
	sf::RenderWindow window;
	sf::Sprite board[3][3];
	sf::Sprite background;

	sf::Texture crossTexture;
	sf::Texture backgroundTexture;
	sf::Texture circleTexture;
	sf::Texture blank;
	sf::RectangleShape line;
	sf::Text result;
	sf::Text info;
	sf::Font font;


	bool playerTurn;	//1->player(true), 0->ai
	bool isFinished;

public:
	Game(bool playerTurn = true);
	void run();

private:
	void update();
	void proccesEvents();
	void render();

	void setResult(int score);
	void playerMove(sf::Vector2f mousePosition);
	void aiMove();
	bool checkTie();
	int evaluate();
	int minmax(int depth, bool isMax, int alpha, int beta);
	void restart();
	void setInfo();
	void setLine(int x, int y, float angle);
};

