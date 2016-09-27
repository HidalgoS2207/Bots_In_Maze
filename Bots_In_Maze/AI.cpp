#include "AI.h"

AI::AI()
	:
	ai_move(up)
{
	srand(time(NULL));
}

AI::~AI()
{}

AI::AI_Moves AI::compute_movement(const std::string & visual)
{
	//check for exit at sight
	int index;
	for (index = 0; index < 9; index++)
	{
		if (visual[index] == 'e')
		{
			break;
		}
	}

	if (index != 9)
	{
		if (index == 1 || index == 3 || index == 5 || index == 7)
		{
			switch (index)
			{
			case 1:
				return up;
			case 3:
				return left;
			case 5:
				return right;
			case 7:
				return down;
			}
		}
		else
		{
			switch (index)
			{
			case 0:
				if (visual[3] == '#')
				{
					return up;
				}
				else
				{
					return left;
				}
			case 2:
				if (visual[5] == '#')
				{
					return up;
				}
				else
				{
					return right;
				}
			case 6:
				if (visual[3] == '#')
				{
					return down;
				}
				else
				{
					return left;
				}
			case 8:
				if (visual[5] == '#')
				{
					return down;
				}
				else
				{
					return right;
				}
			}
		}
	}

	//if no exit at sight compute some valid movement and return the result
	bool possible = false;

	if (visual[1] == '#')
	{
		while (!possible)
		{
			switch (rand() % 3)
			{
			case 0:
				ai_move = right;
				if (visual[5] == '-')
				{
					possible = true;
				}
				break;
			case 1:
				ai_move = left;
				if (visual[3] == '-')
				{
					possible = true;
				}
				break;
			case 2:
				ai_move = down;
				if (visual[7] == '-')
				{
					possible = true;
				}
				break;
			}
		}
	}
	else
	{
		ai_move = up;
	}

	return ai_move;
}
