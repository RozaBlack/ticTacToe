#include <iostream>
#include "Header.h"
#include <chrono>
#include <random>
#include <stdlib.h>

void getUserName(std::string* userName)
{
	std::cout << "Enter your name: ";
	std::cin >> *userName;
	clearSrc();
}

void startPlayer(firstMove* firstPlayer, signs* player1Sign, signs* player2Sign)
{
	//int32_t n = getRandomNum(1, 501);
	if (getRandomNum(1, 501) % 2 == 0)
	{
		*firstPlayer = player1;
		*player1Sign = cross;
		*player2Sign = zero;
	}
	else
	{
		*firstPlayer = player2;
		*player2Sign = cross;
		*player1Sign = zero;
	}
	//std::cout << n;
}

void printInfo(ticTacToe* const game)
{
	clearSrc();
	std::cout << std::endl << "     Hello " << game->userName << "!" << std::endl;
	std::cout << "     Let the game start!" << std::endl;
	std::cout << "     " << game->userName << " plays with " << game->player1Sign << ", computer" << " plays with " << game->player2Sign << std::endl;
	std::cout << "     Crosses go first" << std::endl << std::endl;

	printField(game);
	if (game->progress == firstPlayerWin)
	{
		std::cout << std::endl << "     Congratulations, " << game->userName << ", you are win! :)" << std::endl;
		
	}
	else if (game->progress == secondPlayerWin)
	{
		std::cout << std::endl << "     Sorry, " << game->userName << ", you are fail! :(" << std::endl;
	}
	else if (game->progress == draw)
	{
		std::cout << std::endl << "     It is draw! :|" << std::endl;
	}
}

void printField(ticTacToe* const game)
{

	std::cout << "        1   2   3 " << std::endl;
	std::cout << "       --- --- ---" << std::endl;
	for (size_t i = 0; i < game->fieldSize; i++)
	{
		std::cout << "    " << i + 1 << " |";
		for (size_t j = 0; j < game->fieldSize; j++)
		{
			std::cout << " " << game->field[j][i] << " |";
		}
		std::cout << std::endl;
		std::cout << "       --- --- ---" << std::endl;
	}

}

void computerPlay(ticTacToe* game)
{

	if (game->field[1][1] == empty)
	{
		game->field[1][1] = game->player2Sign;
	}
	else
	{
		for (size_t i = 0; i < game->fieldSize; i++)
		{
			for (size_t j = 0; j < game->fieldSize; j++)
			{
				if (game->field[j][i] == empty)
				{
					game->field[j][i] = game->player2Sign;
					endGameCheck(game);
					if (game->progress == secondPlayerWin || game->progress == draw)
					{
						goto endOfFunc;
					}
					else
					{
						game->field[j][i] = empty;
					}
				}
			}
		}

		for (size_t i = 0; i < game->fieldSize; i++)
		{
			for (size_t j = 0; j < game->fieldSize; j++)
			{
				if (game->field[j][i] == empty)
				{
					game->field[j][i] = game->player1Sign;
					endGameCheck(game);
					if (game->progress == firstPlayerWin)
					{
						game->field[j][i] = game->player2Sign;
						game->progress = inProgress;
						goto endOfFunc;
					}
					else
					{
						game->field[j][i] = empty;
					}
				}
			}
		}

		if (game->field[0][0] == empty)
		{
			game->field[0][0] = game->player2Sign;
		}
		else if (game->field[0][2] == empty)
		{
			game->field[0][2] = game->player2Sign;
		}
		else if (game->field[2][0] == empty)
		{
			game->field[2][0] = game->player2Sign;
		}
		else if (game->field[2][2] == empty)
		{
			game->field[2][2] = game->player2Sign;
		}
		else if (game->field[0][1] == empty)
		{
			game->field[0][1] = game->player2Sign;
		}
		else if (game->field[1][2] == empty)
		{
			game->field[1][2] = game->player2Sign;
		}
		else if (game->field[2][1] == empty)
		{
			game->field[2][1] = game->player2Sign;
		}
		else if (game->field[1][0] == empty)
		{
			game->field[1][0] = game->player2Sign;
		}
	}
endOfFunc:;
}

void gamerPlay(ticTacToe* game)
{
	do
	{
		std::cout << "      Enter y (1..3): ";
		std::cin >> game->y;
		while (game->y < 1 || game->y > 3)
		{
			std::cout << "      Uncorrect coordinate. Enter y(1..3): ";
			std::cin >> game->y;
		}

		std::cout << "      Enter x (1..3): ";
		std::cin >> game->x;
		while (game->x < 1 || game->x > 3)
		{
			std::cout << "      Uncorrect coordinate. Enter x(1..3): ";
			std::cin >> game->x;
		}
	} while (game->field[game->x - 1][game->y - 1] != empty);
	game->field[game->x-1][game->y-1] = game->player1Sign;

}

int endGameCheck(ticTacToe* game)
{
	size_t sum1[3] = { 0 };
	size_t sum2[3] = { 0 };
	size_t sum3 = 0;
	size_t sum4 = 0;
	size_t endValue1 = game->fieldSize * game->player1Sign;
	size_t endValue2 = game->fieldSize * game->player2Sign;
	size_t emptyElem = 0;
	for (size_t i = 0; i < game->fieldSize; i++)
	{
		sum3 += game->field[i][i];
		sum4 += game->field[game->fieldSize - 1 - i][i];

		for (size_t j = 0; j < game->fieldSize; j++)
		{
			sum1[i] += game->field[j][i]; // rows
			sum2[i] += game->field[i][j]; // columns
			if (game->field[j][i] == empty)
			{
				emptyElem++;
				
			}
		}
		if (sum1[i] == endValue1 || sum2[i] == endValue1)
		{
			game->progress = firstPlayerWin;
			return 0;
		}
		else if (sum1[i] == endValue2 || sum2[i] == endValue2)
		{
			game->progress = secondPlayerWin;
			return 0;
		}
		//sum1 = 0;
		//sum2 = 0;
	}
	if (sum3 == endValue1 || sum4 == endValue1)
	{
		game->progress = firstPlayerWin;
	}
	else if (sum3 == endValue2 || sum4 == endValue2)
	{
		game->progress = secondPlayerWin;
	}
	else if (emptyElem == 0)
	{
		game->progress = draw;
	}
	else if (emptyElem == 2)
	{
		int i1[2] = { 0 };
		int j1[2] = { 0 };
		int i0 = 0;
		for (size_t i = 0; i < game->fieldSize; i++) // y
		{
			for (size_t j = 0; j < game->fieldSize; j++) // x
			{
				if (game->field[j][i] == empty)
				{
					i1[i0] = i;
					j1[i0] = j;
					i0++;
					if (i0 == 2)
					{
						goto endCicle;
					}
				}
			}
		}
		endCicle:

		sum3 = 0;
		sum4 = 0;
		game->field[j1[0]][i1[0]] = game->player1Sign;
		game->field[j1[1]][i1[1]] = game->player2Sign;
		for (size_t i = 0; i < game->fieldSize; i++)
		{
			sum1[i] = 0;
			sum2[i] = 0;
			sum3 += game->field[i][i];
			sum4 += game->field[game->fieldSize - 1 - i][i];

			for (size_t j = 0; j < game->fieldSize; j++)
			{
				sum1[i] += game->field[j][i]; // rows
				sum2[i] += game->field[i][j]; // columns
			}
			if (sum1[i] == endValue1 || sum2[i] == endValue1)
			{
				game->field[j1[0]][i1[0]] = empty;
				game->field[j1[1]][i1[1]] = empty;
				return 0;
			}
			else if (sum1[i] == endValue2 || sum2[i] == endValue2)
			{
				game->field[j1[0]][i1[0]] = empty;
				game->field[j1[1]][i1[1]] = empty;
				return 0;
			}
		}
		if (sum3 == endValue1 || sum4 == endValue1)
		{
			game->field[j1[0]][i1[0]] = empty;
			game->field[j1[1]][i1[1]] = empty;
			return 0;
		}
		else if (sum3 == endValue2 || sum4 == endValue2)
		{
			game->field[j1[0]][i1[0]] = empty;
			game->field[j1[1]][i1[1]] = empty;
			return 0;
		}

		sum3 = 0;
		sum4 = 0;
		game->field[j1[0]][i1[0]] = game->player2Sign;
		game->field[j1[1]][i1[1]] = game->player1Sign;
		for (size_t i = 0; i < game->fieldSize; i++)
		{
			sum1[i] = 0;
			sum2[i] = 0;
			sum3 += game->field[i][i];
			sum4 += game->field[game->fieldSize - 1 - i][i];

			for (size_t j = 0; j < game->fieldSize; j++)
			{
				sum1[i] += game->field[j][i]; // rows
				sum2[i] += game->field[i][j]; // columns
			}
			if (sum1[i] == endValue1 || sum2[i] == endValue1)
			{
				game->field[j1[0]][i1[0]] = empty;
				game->field[j1[1]][i1[1]] = empty;
				return 0;
			}
			else if (sum1[i] == endValue2 || sum2[i] == endValue2)
			{
				game->field[j1[0]][i1[0]] = empty;
				game->field[j1[1]][i1[1]] = empty;
				return 0;
			}
		}
		if (sum3 == endValue1 || sum4 == endValue1)
		{
			game->field[j1[0]][i1[0]] = empty;
			game->field[j1[1]][i1[1]] = empty;
			return 0;
		}
		else if (sum3 == endValue2 || sum4 == endValue2)
		{
			game->field[j1[0]][i1[0]] = empty;
			game->field[j1[1]][i1[1]] = empty;
			return 0;
		}
		game->field[j1[0]][i1[0]] = empty;
		game->field[j1[1]][i1[1]] = empty;
		game->progress = draw;


	}
	else if (emptyElem == 1)
	{
	int i1 = 0;
	int j1 = 0;
	for (size_t i = 0; i < game->fieldSize; i++) // y
	{
		for (size_t j = 0; j < game->fieldSize; j++) // x
		{
			if (game->field[j][i] == empty)
			{
				i1 = i;
				j1 = j;
				goto endCicle1;
			}
		}
	}
endCicle1:

	sum3 = 0;
	sum4 = 0;
	if (game->firstPlayer == 0)
	{
		game->field[j1][i1] = game->player1Sign;
	}
	else
	{
		game->field[j1][i1] = game->player2Sign;
	}
	
	for (size_t i = 0; i < game->fieldSize; i++)
	{
		sum1[i] = 0;
		sum2[i] = 0;
		sum3 += game->field[i][i];
		sum4 += game->field[game->fieldSize - 1 - i][i];

		for (size_t j = 0; j < game->fieldSize; j++)
		{
			sum1[i] += game->field[j][i]; // rows
			sum2[i] += game->field[i][j]; // columns
		}
		if (sum1[i] == endValue1 || sum2[i] == endValue1)
		{
			game->field[j1][i1] = empty;
			game->field[j1][i1] = empty;
			return 0;
		}
		else if (sum1[i] == endValue2 || sum2[i] == endValue2)
		{
			game->field[j1][i1] = empty;
			game->field[j1][i1] = empty;
			return 0;
		}
	}
	if (sum3 == endValue1 || sum4 == endValue1)
	{
		game->field[j1][i1] = empty;
		game->field[j1][i1] = empty;
		return 0;
	}
	else if (sum3 == endValue2 || sum4 == endValue2)
	{
		game->field[j1][i1] = empty;
		game->field[j1][i1] = empty;
		return 0;
	}

	game->field[j1][i1] = empty;
	game->field[j1][i1] = empty;
	game->progress = draw;

	}

	return 0;
}

inline void clearSrc()
{
	system("cls");
}

int32_t __fastcall getRandomNum(int32_t min, int32_t max)
{
	const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937_64 generator(seed);
	std::uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
}