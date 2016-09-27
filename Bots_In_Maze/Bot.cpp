#pragma once

#include "Bot.h"

Bot::Bot()
	:
	bot_AI(),
	is_in_exit(false)
{}

Bot::~Bot()
{}

void Bot::bot_next_move()
{
	if (!is_in_exit)
	{
		Moves next_move;
		next_move = (Moves)bot_AI.compute_movement(visual);
		translate_move(next_move);
	}
}

bool Bot::bot_win()
{
	return is_in_exit;
}

void Bot::set_initial_position(std::pair<int, int> position)
{
	cur_pos = position;
}

void Bot::set_initial_orientation(int or )
{
	orientation = (Facing)or;
}

void Bot::draw_visual()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << visual[j + (i*3)];
		}
		std::cout << "\n";
	}
}

void Bot::translate_move(Moves next_move)
{
	bot_path.push_back({ cur_pos.first,cur_pos.second });

	switch (orientation)
	{
	case north:
		if (Moves::up == next_move)
		{
			cur_pos.second--;
		}
		else if (Moves::right == next_move)
		{
			cur_pos.first++;
			orientation = east;
		}
		else if (Moves::down == next_move)
		{
			cur_pos.second++;
			orientation = south;
		}
		else if (Moves::left == next_move)
		{
			cur_pos.first--;
			orientation = west;
		}
		break;
	case east:
		if (Moves::up == next_move)
		{
			cur_pos.first++;
		}
		else if (Moves::right == next_move)
		{
			cur_pos.second++;
			orientation = south;
		}
		else if (Moves::down == next_move)
		{
			cur_pos.first--;
			orientation = west;
		}
		else if (Moves::left == next_move)
		{
			cur_pos.second--;
			orientation = north;
		}
		break;
	case south:
		if (Moves::up == next_move)
		{
			cur_pos.second++;
		}
		else if (Moves::right == next_move)
		{
			cur_pos.first--;
			orientation = west;
		}
		else if (Moves::down == next_move)
		{
			cur_pos.second--;
			orientation = north;
		}
		else if (Moves::left == next_move)
		{
			cur_pos.first++;
			orientation = east;
		}
		break;
	case west:
		if (Moves::up == next_move)
		{
			cur_pos.first--;
		}
		else if (Moves::right == next_move)
		{
			cur_pos.second--;
			orientation = north;
		}
		else if (Moves::down == next_move)
		{
			cur_pos.first++;
			orientation = east;
		}
		else if (Moves::left == next_move)
		{
			cur_pos.second++;
			orientation = south;
		}
		break;
	}
}

//data transference methods

void Bot::save_maze_data(std::string visual_, bool is_in_exit_)
{
	visual.insert(0,visual_);
	visual[4] = '@';
	is_in_exit = is_in_exit_;
}

std::pair<int, int> Bot::get_bot_pos()
{
	return cur_pos;
}

int Bot::get_facing()
{
	return orientation;
}
