#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "AI.h"

class Bot
{
private:
	enum Facing
	{
		north,
		east,
		south,
		west
	};
	enum Moves
	{
		up,
		right,
		down,
		left
	};
public:
	Bot();
	~Bot();

	void bot_next_move();
	bool bot_win();

	void set_initial_position(std::pair<int,int> position);
	void set_initial_orientation(int or );

	void draw_visual();

public: //data transference methods
	void save_maze_data(std::string visual_, bool is_in_exit_);
	std::pair<int, int> get_bot_pos();
	int get_facing();

private: //maze info
	std::string visual;
	bool is_in_exit;

private:
	AI bot_AI;

	void translate_move(Moves next_move);

	std::vector< std::pair<int, int> > bot_path;
	std::pair<int, int> cur_pos;
	Facing orientation;
};
