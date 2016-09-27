//Bots in the maze

#include <cstdio>
#include <stdio.h>
#include <iostream>

#include "Game.h"

int main()
{
	try
	{
		int num_bots = 0;
		std::cout << "Set the number of bots: ";
		std::cin >> num_bots;

		Game game(num_bots);

		while (!game.winner())
		{
			game.Update();
		}
	}
	catch(int e)
	{
		switch (e)
		{
		case 0x01:
			printf("\nERROR -> 'Maze.txt' file missing\n\n");
			system("PAUSE");
			return 0;
		case 0x02:
			printf("\nERROR -> 'Maze.txt' file corrupted\n\n");
			system("PAUSE");
			return 0;
		case 0x03:
			printf("\nERROR -> Mismatch map size signature with actual map size\n\n");
			system("PAUSE");
			return 0;
		case 0x04:
			printf("\nERROR -> Invalid Map Size\n\n");
			system("PAUSE");
			return 0;
		case 0x05:
			printf("\nERROR -> Bad Map Character\n\n");
			system("PAUSE");
			return 0;
		case 0x06:
			printf("\nERROR -> No Exit or the Exit is in {0,0} position\n\n");
			system("PAUSE");
			return 0;
		case 0x07:
			printf("\nERROR -> Bad Exit Coordinates\n\n");
			system("PAUSE");
			return 0;
		case 0x08:
			printf("\nERROR -> Two or more exits\n\n");
			system("PAUSE");
			return 0;
		case 0x09:
			printf("\n-- Game Finished by User --\n\n");
			system("PAUSE");
			return 0;
		default:
			printf("\nERROR -> Unhandled\n\n");
			system("PAUSE");
			return 0;
		}
	}

	system("PAUSE");
	return 0;
}