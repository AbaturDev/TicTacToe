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

	sf::Texture crossTexture;
	sf::Texture backgroundTexture;
	sf::Texture circleTexture;
	sf::Texture aiWin;
	sf::Texture playerWin;
	sf::Texture tie;
	sf::Texture emptyTexture;

	sf::Sprite background;
	sf::Sprite result;

	bool playerTurn;	//1->player(true), 0->ai

public:
	Game(bool playerTurn = true);
	void run();

private:
	void update();
	void proccesEvents();
	void render();

	void playerMove(sf::Vector2f mousePosition);
	void aiMove();
	bool checkTie();
	int evaluate();
	int minmax(int depth, bool isMax, int alpha, int beta);
};

