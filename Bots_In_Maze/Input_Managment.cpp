#include "Input_Managment.h"

Input_Managment::Input_Managment()
	:
	max_map_width(30),
	max_map_height(30),
	min_map_width(5),
	min_map_height(5)
{
	ifs.open("Maze.txt", std::ios::in);

	if (!ifs.good())
	{
		throw 0x00000001;
	}
	else
	{
		if (ifs.get() != '{')
		{
			throw 0x00000002;
		}
	}
}

Input_Managment::~Input_Managment()
{
	ifs.close();
}

std::pair<int,int> Input_Managment::set_map_size()
{
	std::pair<int, int> map_size;

	ifs.seekg(1,ifs.beg);

	while (ifs.get() != ',' && map_size_string.size() <= 2)
	{
		ifs.seekg(-1 , ifs.cur);
		map_size_string.push_back(ifs.get());
	}

	if (map_size_string.size() > 2)
	{
		throw 0x00000002;
	}

	map_size.first = st.string_to_int(map_size_string);
	if (map_size.first > max_map_width || map_size.first < min_map_width)
	{
		throw 0x00000004;
	}

	map_size_string.clear();

	while (ifs.get() != '}' && map_size_string.size() <= 2)
	{
		ifs.seekg(-1,ifs.cur);
		map_size_string.push_back(ifs.get());
	}

	if (map_size_string.size() > 2)
	{
		throw 0x00000002;
	}

	map_size.second = st.string_to_int(map_size_string);
	if (map_size.second > max_map_height || map_size.second < min_map_height)
	{
		throw 0x00000004;
	}

	map_size_string.clear();

	return map_size;
}

std::string Input_Managment::fill_string(std::pair<int,int> map_size)
{
	std::string maze_map;

	int h_counter = 0;
	int w_counter = 0;
	ifs.seekg(0,ifs.beg);

	while (ifs.get() != '}') {}
	if (ifs.get() != 0x0a)
	{
		throw 0x00000002;
	}

	for (h_counter = 0 ; ; h_counter++)
	{
		if (h_counter > 0) { maze_map.push_back('\n'); }
		if (h_counter == map_size.second - 1) { break; }

		for (w_counter = 0 ; ifs.get() != 0x0a && h_counter != (map_size.second - 1); w_counter++)
		{
			ifs.seekg(-1 , ifs.cur);

			if (w_counter == map_size.first)
			{
				throw 0x03;
			}

			maze_map.push_back(ifs.get());
		}
	}

	for (w_counter = 0; ifs.get() != 0x7e; w_counter++)
	{
		ifs.seekg(-1,ifs.cur);

		if (w_counter == map_size.first)
		{
			throw 0x03;
		}

		maze_map.push_back(ifs.get());
	}

	maze_map.push_back('\n');

	return maze_map;
}


