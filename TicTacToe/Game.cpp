#include "Game.h"
#include <algorithm>
#include <limits>

Game::Game(bool playerTurn) : window(sf::VideoMode(512, 512), "TicTacToe", sf::Style::Default)
{
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

	if (circleTexture.getSize() != crossTexture.getSize())
	{
		throw std::runtime_error("Difrent sizes of cross and circle textures");
	}
	sf::Vector2f desiredSize(100.0f, 100.0f);
	sf::Vector2u tempSize = crossTexture.getSize();		// cross size == circle size

	float scaleX = desiredSize.x / tempSize.x;
	float scaleY = desiredSize.y / tempSize.y;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j].setScale(scaleX, scaleY);
		}
	}

	emptyTexture.create(1, 1);
	sf::Uint8 transparentPixel[4] = { 0, 0, 0, 0 };
	emptyTexture.update(transparentPixel);

	this->playerTurn = playerTurn;
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

		if (event.type == sf::Event::MouseButtonPressed && playerTurn == true)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			playerMove(static_cast<sf::Vector2f>(mousePosition));
		}
	}
}

void Game::update()
{
	if (evaluate() == -10)
	{
		std::cout << "Player wins";
		window.close();
	}
	if (checkTie())
	{
		std::cout << "TIE";
		window.close();
	}
	if (playerTurn == false)
	{
		aiMove();
	}
	if (evaluate() == 10)
	{
		std::cout << "AI wins";
		window.close();
	}
	if (checkTie())
	{
		std::cout << "TIE";
		window.close();
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
	window.display();
}

void Game::playerMove(sf::Vector2f mousePosition)
{
	int gridSize = 170;
	sf::Vector2f position;

	// Check which cell was clicked
	if ((mousePosition.x >= 0 && mousePosition.x < gridSize && mousePosition.y >= 0 && mousePosition.y < gridSize) && board[0][0].getTexture() == nullptr)
	{
		// 1st
		board[0][0].setTexture(crossTexture);
		position = sf::Vector2f((gridSize / 2.0f) - board[0][0].getGlobalBounds().width / 2.0f, (gridSize / 2.0f) - board[0][0].getGlobalBounds().height / 2.0f);
		board[0][0].setPosition(position);
		playerTurn = false;
	}
	else if ((mousePosition.x >= gridSize && mousePosition.x < 2 * gridSize && mousePosition.y >= 0 && mousePosition.y < gridSize) && board[0][1].getTexture() == nullptr)
	{
		// 2nd
		board[0][1].setTexture(crossTexture);
		position = sf::Vector2f(1.5f * gridSize - board[0][1].getGlobalBounds().width / 2.0f, gridSize / 2.0f - board[0][1].getGlobalBounds().height / 2.0f);
		board[0][1].setPosition(position);
		playerTurn = false;
	}
	else if ((mousePosition.x >= 2 * gridSize && mousePosition.x < 3 * gridSize && mousePosition.y >= 0 && mousePosition.y < gridSize) && board[0][2].getTexture() == nullptr)
	{
		// 3rd
		board[0][2].setTexture(crossTexture);
		position = sf::Vector2f(2.5f * gridSize - board[0][2].getGlobalBounds().width / 2.0f, gridSize / 2.0f - board[0][2].getGlobalBounds().height / 2.0f);
		board[0][2].setPosition(position);
		playerTurn = false;
	}
	else if ((mousePosition.x >= 0 && mousePosition.x < gridSize && mousePosition.y >= gridSize && mousePosition.y < 2 * gridSize) && board[1][0].getTexture() == nullptr)
	{
		// 4th
		board[1][0].setTexture(crossTexture);
		position = sf::Vector2f(gridSize / 2.0f - board[1][0].getGlobalBounds().width / 2.0f, 1.5f * gridSize - board[1][0].getGlobalBounds().height / 2.0f);
		board[1][0].setPosition(position);
		playerTurn = false;
	}
	else if ((mousePosition.x >= gridSize && mousePosition.x < 2 * gridSize && mousePosition.y >= gridSize && mousePosition.y < 2 * gridSize) && board[1][1].getTexture() == nullptr)
	{
		// 5th
		board[1][1].setTexture(crossTexture);
		position = sf::Vector2f(1.5f * gridSize - board[1][1].getGlobalBounds().width / 2.0f, 1.5f * gridSize - board[1][1].getGlobalBounds().height / 2.0f);
		board[1][1].setPosition(position);
		playerTurn = false;
	}
	else if ((mousePosition.x >= 2 * gridSize && mousePosition.x < 3 * gridSize && mousePosition.y >= gridSize && mousePosition.y < 2 * gridSize) && board[1][2].getTexture() == nullptr)
	{
		// 6th
		board[1][2].setTexture(crossTexture);
		position = sf::Vector2f(2.5f * gridSize - board[1][2].getGlobalBounds().width / 2.0f, 1.5f * gridSize - board[1][2].getGlobalBounds().height / 2.0f);
		board[1][2].setPosition(position);
		playerTurn = false;
	}
	else if ((mousePosition.x >= 0 && mousePosition.x < gridSize && mousePosition.y >= 2 * gridSize && mousePosition.y < 3 * gridSize) && board[2][0].getTexture() == nullptr)
	{
		// 7th
		board[2][0].setTexture(crossTexture);
		position = sf::Vector2f(gridSize / 2.0f - board[2][0].getGlobalBounds().width / 2.0f, 2.5f * gridSize - board[2][0].getGlobalBounds().height / 2.0f);
		board[2][0].setPosition(position);
		playerTurn = false;
	}
	else if ((mousePosition.x >= gridSize && mousePosition.x < 2 * gridSize && mousePosition.y >= 2 * gridSize && mousePosition.y < 3 * gridSize) && board[2][1].getTexture() == nullptr)
	{
		// 8th
		board[2][1].setTexture(crossTexture);
		position = sf::Vector2f(1.5f * gridSize - board[2][1].getGlobalBounds().width / 2.0f, 2.5f * gridSize - board[2][1].getGlobalBounds().height / 2.0f);
		board[2][1].setPosition(position);
		playerTurn = false;
	}
	else if ((mousePosition.x >= 2 * gridSize && mousePosition.x < 3 * gridSize && mousePosition.y >= 2 * gridSize && mousePosition.y < 3 * gridSize) && board[2][2].getTexture() == nullptr)
	{
		// 9th
		board[2][2].setTexture(crossTexture);
		position = sf::Vector2f(2.5f * gridSize - board[2][2].getGlobalBounds().width / 2.0f, 2.5f * gridSize - board[2][2].getGlobalBounds().height / 2.0f);
		board[2][2].setPosition(position);
		playerTurn = false;
	}
}

bool Game::checkTie()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j].getTexture() == nullptr || board[i][j].getTexture() == &emptyTexture)
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
		if (board[i][0].getTexture() == board[i][1].getTexture() && board[i][1].getTexture() == board[i][2].getTexture())
		{
			if (board[i][0].getTexture() == &circleTexture)
			{
				return +10;
			}
			else if (board[i][0].getTexture() == &crossTexture)
			{
				return -10;
			}
		}

		if (board[0][i].getTexture() == board[1][i].getTexture() && board[1][i].getTexture() == board[2][i].getTexture() && board[0][i].getTexture() != nullptr)
		{
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

	if (board[0][0].getTexture() == board[1][1].getTexture() && board[1][1].getTexture() == board[2][2].getTexture() && board[0][0].getTexture() != nullptr)
	{
		if (board[0][0].getTexture() == &circleTexture)
		{
			return +10;
		}
		else if (board[0][0].getTexture() == &crossTexture)
		{
			return -10;
		}
	}
	else if (board[0][2].getTexture() == board[1][1].getTexture() && board[1][1].getTexture() == board[2][0].getTexture() && board[0][2].getTexture() != nullptr)
	{
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
			if (board[i][j].getTexture() == nullptr)
			{
				board[i][j].setTexture(circleTexture);

				int move = minmax(0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

				board[i][j].setTexture(emptyTexture);
				
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
		board[x][y].setTexture(circleTexture);
		board[x][y].setPosition((x * gridSize + gridSize / 2.0f) - circleTexture.getSize().x / 2.0f, (y * gridSize + gridSize / 2.0f) - circleTexture.getSize().y / 2.0f);
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
				if (board[i][j].getTexture() == nullptr)
				{
					board[i][j].setTexture(circleTexture);

					best = std::max(best, minmax(depth + 1, !isMax, alpha, beta));

					board[i][j].setTexture(emptyTexture);
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
				if (board[i][j].getTexture() == nullptr)
				{
					board[i][j].setTexture(crossTexture);
					
					best = std::min(best, minmax(depth + 1, !isMax, alpha, beta));

					board[i][j].setTexture(emptyTexture);
					beta = std::min(beta, best);
					if (beta <= alpha) break;
				}
			}
		}
		return best;
	}
}