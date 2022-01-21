// ticTacToe.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Header.h"


int main()
{
	ticTacToe game;
	getUserName(&game.userName);
	startPlayer(&game.firstPlayer, &game.player1Sign, &game.player2Sign);
	printInfo(&game);
	short int i = game.firstPlayer;
	while (game.progress == inProgress)
	{
			if (i == 0)
			{
				gamerPlay(&game);
				endGameCheck(&game);
				printInfo(&game);
				i = 1;
			}
			else
			{
				computerPlay(&game);
				endGameCheck(&game);
				printInfo(&game);
				i = 0;
			}
	}
	system("pause");
	return 0;
}

