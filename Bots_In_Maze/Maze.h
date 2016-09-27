#pragma once

#include <string>

#include "Input_Managment.h"
#include <vector>

class Maze
{
public:

	Maze(int bots_number_);
	~Maze();

	void print_maze();

	std::pair<int, int> get_map_size();
	char get_single_block(int pos);
private:
	Input_Managment im;

	std::string maze_map;
	std::pair<int, int> map_size;

	std::pair<int, int> exit_coord;

	void check_map();

//Data transference methods and variables
private:
	std::vector< std::pair< std::pair<int,int>,int> > bots_positions;
	int bots_number;
	std::vector<int> bot_pos_index;
public:
	void save_bots_data(std::pair<int,int> coords , int orientation , int index);
	std::string get_visual(int index);
	bool check_exit_position(int index);
};