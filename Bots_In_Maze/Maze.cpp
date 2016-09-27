#include "Maze.h"

Maze::Maze(int bots_number_)
	:
	bots_number(bots_number_),
	im(),
	exit_coord({0,0})
{
	map_size = im.set_map_size();
	maze_map = im.fill_string(map_size);

	for (int i = 0; i < bots_number; i++)
	{
		bots_positions.push_back({ { 0,0 }, 0 });
		bot_pos_index.push_back(0);
	}

	check_map();
}

Maze::~Maze()
{}

void Maze::print_maze()
{
	for (int i = 0; i < maze_map.size(); i++)
	{
		bool is_a_bot = false;

		for (int j = 0; j < bots_number; j++)
		{
			if (i == bot_pos_index[j])
			{
				is_a_bot = true;
			}
		}

		if (is_a_bot)
		{
			printf("%c", 0x40);
		}
		else
		{
			printf("%c", maze_map[i]);
		}
	}
}

std::pair<int, int> Maze::get_map_size()
{
	return map_size;
}

char Maze::get_single_block(int pos)
{
	return maze_map[pos];
}

void Maze::check_map()
{
	bool exit_found = false;
	//general characters checking

	for (int i = 0; i < map_size.second ; i++)
	{
		for (int j = 0; j <= map_size.first; j++)
		{
			if (j == map_size.first && maze_map[j + (i * (map_size.first+1))] != 0x0a)
			{
				throw 0x05;
			}
			else if (j != map_size.first && maze_map[j + (i*(map_size.first + 1))] != 0x23 && maze_map[j + (i*(map_size.first + 1))] != 0x65 && maze_map[j + (i*(map_size.first + 1))] != 0x2d)
			{
				throw 0x05;
			}

			if (maze_map[j + (i*(map_size.first + 1))] == 0x65)
			{
				if (exit_found)
				{
					throw 0x08;
				}
				exit_coord.first = j;
				exit_coord.second = i;

				exit_found = true;
			}
		}
	}

	//check corners

	if (maze_map[0] != 0x23 || maze_map[map_size.first - 1] != 0x23 || maze_map[(map_size.first + 1) * (map_size.second - 1)] != 0x23 || maze_map[((map_size.first + 1) * (map_size.second - 1)) + map_size.first - 1] != 0x23)
	{
		throw 0x05;
	}

	//check walls

	for (int i = 1; i < map_size.first; i++)
	{
		if ((maze_map[i] != 0x23 && maze_map[i] != 0x65) || ((maze_map[((map_size.first + 1) * (map_size.second - 1)) +i] != 0x23 && maze_map[((map_size.first + 1) * (map_size.second - 1)) + i] != 0x65)))
		{
			throw 0x05; 
		}
	}

	for (int i = 1; i < map_size.second - 1; i++)
	{
		if ((maze_map[i*(map_size.first+1)] != 0x23 && maze_map[i*(map_size.first + 1)] != 0x65) || ((maze_map[(i*(map_size.first + 1)) + map_size.first - 1] != 0x23 && maze_map[(i*(map_size.first + 1)) + map_size.first - 1] != 0x65)))
		{
			throw 0x05;
		}
	}

	//check exit coordinates

	if (exit_coord.first == 0 && exit_coord.second == 0)
	{
		throw 0x06;
	}
	

	if (exit_coord.first != 0 && exit_coord.first != map_size.first - 1)
	{
		if (exit_coord.second != 0 && exit_coord.second != map_size.second - 1)
		{
			throw 0x07;
		}
	}
}

void Maze::save_bots_data(std::pair<int, int> coords, int orientation , int index)
{
	if (index < bots_positions.size())
	{
		bots_positions[index].first = coords;
		bots_positions[index].second = orientation;

		bot_pos_index[index] = coords.first + (coords.second * (map_size.first + 1));
	}
}

std::string Maze::get_visual(int index)
{
	std::string visual;

	int pos = bots_positions[index].first.first - 1 + ((bots_positions[index].first.second - 1) * (map_size.first + 1));

	switch (bots_positions[index].second)
	{
	case 0:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				visual.push_back(maze_map[j + (i*(map_size.first + 1)) + pos]);
			}
		}
		break;
	case 1:
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < 3; j++)
			{
				visual.push_back(maze_map[i + (j*(map_size.first + 1)) + pos]);
			}
		}
		break;
	case 2:
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 2; j >= 0; j--)
			{
				visual.push_back(maze_map[j + (i*(map_size.first + 1)) + pos]);
			}
		}
		break;
	case 3:
		for (int i = 0; i < 2; i++)
		{
			for (int j = 2; j >= 0; j--)
			{
				visual.push_back(maze_map[i + (j*(map_size.first + 1)) + pos]);
			}
		}
		break;
	}

	return visual;
}

bool Maze::check_exit_position(int index)
{
	return (exit_coord == bots_positions[index].first);
}
