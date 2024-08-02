#include "Game.h"
#include <algorithm>
#include <limits>

Game::Game(bool playerTurn) : window(sf::VideoMode(512, 512), "TicTacToe", sf::Style::Close)
{
	if (!font.loadFromFile("images/Lato-Black.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}
	result.setFont(font);
	info.setFont(font);

	if (!backgroundTexture.loadFromFile("images/board.png"))
	{
		throw std::runtime_error("Failed to load background texture");
	}
	background.setTexture(backgroundTexture);

	if (!crossTexture.loadFromFile("images/cross.png"))
	{
		throw std::runtime_error("Failed to load cross texture");
	}

	if (!circleTexture.loadFromFile("images/circle.png"))
	{
		throw std::runtime_error("Failed to load circle texture");
	}

	if (!blank.loadFromFile("images/blank.png"))
	{
		throw std::runtime_error("Failed to load blank texture");
	}

	if (circleTexture.getSize() != crossTexture.getSize())
	{
		throw std::runtime_error("Difrent sizes of cross and circle textures");
	}
	sf::Vector2f desiredSize(100.0f, 100.0f);
	sf::Vector2u tempSize = crossTexture.getSize();		// cross size == circle size

	float scaleX = desiredSize.x / tempSize.x;
	float scaleY = desiredSize.y / tempSize.y;
	int gridSize = 170;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j].setScale(scaleX, scaleY);
			board[i][j].setTexture(blank);
			board[i][j].setPosition((i * gridSize + gridSize / 2.0f) - board[i][j].getGlobalBounds().width / 2.0f, (j * gridSize + gridSize / 2.0f) - board[i][j].getGlobalBounds().height / 2.0f);
		}
	}

	this->playerTurn = playerTurn;
	isFinished = false;
}

void Game::run()
{
	while (window.isOpen())
	{
		proccesEvents();
		update();
		render();
	}
}

void Game::proccesEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed && (playerTurn == true && isFinished == false))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			playerMove(static_cast<sf::Vector2f>(mousePosition));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			restart();
		}
	}
}

void Game::update()
{
	if (evaluate() == -10)
	{
		setResult(-10);
		setInfo();
		isFinished = true;
	}

	else if (checkTie())
	{
		setResult(0);
		setInfo();
		isFinished = true;
	}

	if (playerTurn == false && isFinished == false)
	{
		aiMove();
	}

	if (evaluate() == 10)
	{
		setResult(10);
		setInfo();
		isFinished = true;
	}

	else if (checkTie())
	{
		setResult(0);
		setInfo();
		isFinished = true;
	}

}

void Game::render()
{
	window.clear();
	window.draw(background);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			window.draw(board[i][j]);
		}
	}
	if (isFinished) {
		if(!checkTie()) window.draw(line);
		window.draw(info);
		window.draw(result);
	}
	window.display();
}

void Game::playerMove(sf::Vector2f mousePosition)
{
	int gridSize = 170;
	int x = mousePosition.x / gridSize;
	int y = mousePosition.y / gridSize;

	if (board[x][y].getTexture() == &blank)
	{
		board[x][y].setTexture(crossTexture, true);
		board[x][y].setPosition((x*gridSize+gridSize/2.0f)-board[x][y].getGlobalBounds().width/2.0f,(y*gridSize+gridSize/2.0f)-board[x][y].getGlobalBounds().height/2.0f);
		playerTurn = false;
	}
}

bool Game::checkTie()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j].getTexture() == &blank)
			{
				return false;
			}
		}
	}
	return true;
}

int Game::evaluate()
{
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0].getTexture() == board[i][1].getTexture() && board[i][1].getTexture() == board[i][2].getTexture() && board[i][0].getTexture() != &blank)
		{
			setLine(i, 0, 0);
			if (board[i][0].getTexture() == &circleTexture)
			{
				return +10;
			}
			else if (board[i][0].getTexture() == &crossTexture)
			{
				return -10;
			}
		}

		if (board[0][i].getTexture() == board[1][i].getTexture() && board[1][i].getTexture() == board[2][i].getTexture() && board[0][i].getTexture() != &blank)
		{
			setLine(0, i, 90);
			if (board[0][i].getTexture() == &circleTexture)
			{
				return +10;
			}
			else if (board[0][i].getTexture() == &crossTexture)
			{
				return -10;
			}
		}
	}

	if (board[0][0].getTexture() == board[1][1].getTexture() && board[1][1].getTexture() == board[2][2].getTexture() && board[0][0].getTexture() != &blank)
	{
		setLine(0, 0, 45);
		if (board[0][0].getTexture() == &circleTexture)
		{
			return +10;
		}
		else if (board[0][0].getTexture() == &crossTexture)
		{
			return -10;
		}
	}
	else if (board[0][2].getTexture() == board[1][1].getTexture() && board[1][1].getTexture() == board[2][0].getTexture() && board[0][2].getTexture() != &blank)
	{
		setLine(0, 2, 135);
		if (board[0][2].getTexture() == &circleTexture)
		{
			return +10;
		}
		else if (board[0][2].getTexture() == &crossTexture)
		{
			return -10;
		}
	}

	return 0;
}

void Game::aiMove()
{
	int gridSize = 170;
	int x = -1;
	int y = -1;

	int bestValue = std::numeric_limits<int>::min();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j].getTexture() == &blank)
			{
				board[i][j].setTexture(circleTexture);

				int move = minmax(0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

				board[i][j].setTexture(blank);

				if (move > bestValue)
				{
					x = i;
					y = j;
					bestValue = move;
				}
			}
		}
	}

	if (x != -1 && y != -1) {
		board[x][y].setTexture(circleTexture, true);
		board[x][y].setPosition((x * gridSize + gridSize / 2.0f) - board[x][y].getGlobalBounds().width / 2.0f, (y * gridSize + gridSize / 2.0f) - board[x][y].getGlobalBounds().height / 2.0f);
	}
	playerTurn = true;
}

int Game::minmax(int depth, bool isMax, int alpha, int beta)
{
	int score = evaluate();

	if (score == 10)
	{
		return score;
	}

	if (score == -10)
	{
		return score;
	}

	if (checkTie())
	{
		return 0;
	}

	if (isMax)
	{
		int best = std::numeric_limits<int>::min();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j].getTexture() == &blank)
				{
					board[i][j].setTexture(circleTexture);

					best = std::max(best, minmax(depth + 1, !isMax, alpha, beta));

					board[i][j].setTexture(blank);
					alpha = std::max(alpha, best);
					if (beta <= alpha) break;
				}
			}
		}
		return best;
	}
	else
	{
		int best = std::numeric_limits<int>::max();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j].getTexture() == &blank)
				{
					board[i][j].setTexture(crossTexture);

					best = std::min(best, minmax(depth + 1, !isMax, alpha, beta));

					board[i][j].setTexture(blank);
					beta = std::min(beta, best);
					if (beta <= alpha) break;
				}
			}
		}
		return best;
	}
}

void Game::setResult(int score)
{
	result.setCharacterSize(95);
	result.setOrigin(result.getLocalBounds().width / 2, result.getLocalBounds().height / 2);
	result.setPosition(256, 256-result.getLocalBounds().height/2.0f - 100);
	result.setFillColor(sf::Color::Red);

	if (score == -10)
	{
		result.setString("Player wins!");
	}
	else if (score == 10)
	{
		result.setString("Ai wins!");
	}
	else if (score == 0)
	{
		result.setString("It's a tie!");
	}
}

void Game::restart()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j].setTexture(blank, true);
		}
	}
	result.setString("");
	info.setString("");
	isFinished = false;
}

void Game::setInfo()
{
	info.setCharacterSize(28); 
	info.setOrigin(info.getLocalBounds().width / 2, info.getLocalBounds().height / 2);
	info.setPosition(256, 256 - info.getLocalBounds().height / 2.0f - 30);
	info.setFillColor(sf::Color::Blue);

	info.setString("Press ESC to quit or SPACE to restart");
}

void Game::setLine(int x, int y, float angle)
{


	int gridSize = 170;
	line.setFillColor(sf::Color::Black);
	
	line.setRotation(angle);

	if (angle == 0) {
		line.setSize(sf::Vector2f(5, gridSize * 3));
		line.setPosition(x * gridSize + gridSize / 2.0f - 2.5f, 0);
	}
	else if (angle == 90) {
		line.setSize(sf::Vector2f(gridSize * 3, 5));
		line.setPosition(x * gridSize, y * gridSize + gridSize / 2.0f - 2.5f);
		line.setRotation(0);
	}
	else if (angle == 45) {
		line.setSize(sf::Vector2f(std::sqrt(2) * gridSize * 3, 5));
		line.setPosition(0, 0);
	}
	else if (angle == 135) {
		line.setSize(sf::Vector2f(std::sqrt(2) * gridSize * 3, 5));
		line.setPosition(gridSize * 3, 0);
	}
}