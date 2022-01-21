#pragma once

enum signs : char
{
	cross = 'X',
	empty = ' ',
	zero = 'O'
};

enum gameState
{
	inProgress,
	firstPlayerWin,
	secondPlayerWin,
	draw
};

enum firstMove
{
	player1,
	player2
};

struct ticTacToe
{
	static const size_t fieldSize = 3;
	signs field[fieldSize][fieldSize] = { empty, empty, empty, empty, empty, empty, empty, empty, empty };
	size_t x = 0;
	size_t y = 0;
	std::string userName;
	gameState progress = inProgress;
	firstMove firstPlayer = player1;
	signs player1Sign = cross;
	signs player2Sign = zero;
};

void getUserName(std::string* username);
void startPlayer(firstMove* firstPlayer, signs* player1Sign, signs* player2Sign);
void printInfo(ticTacToe* game);
void printField(ticTacToe* game);
void computerPlay(ticTacToe* game);
void gamerPlay(ticTacToe* game);
int endGameCheck(ticTacToe* game);
void clearSrc();
int32_t getRandomNum(int32_t min, int32_t max);
