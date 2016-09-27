#pragma once

#include "Maze.h"
#include "Bot.h"
#include "Timer.h"


#include <iostream>
#include <vector>
#include <random>
#include <time.h>

class Game
{
private:
	class Messages_Processor
	{
	public:
		Messages_Processor()
			:
			current_message(0xFF)
		{
			load_messages_list();
		}
		~Messages_Processor() {}

		int get_message()
		{
			return current_message;
		}

		void wait_for_message()
		{
			message_string.clear();

			std::cin >> message_string;

			current_message = process_message();
		}

		std::string get_command_string(int index)
		{
			return messages_list[index];
		}

		int get_command_list_size()
		{
			return messages_list.size();
		}
	private:
		int current_message;
		std::string message_string;
		std::vector< std::string > messages_list;

		void load_messages_list()
		{
			//main messages
			messages_list.push_back("exit"); //0x01
			messages_list.push_back("move"); //0x02
			messages_list.push_back("move_steps"); //0x03 
			messages_list.push_back("draw_maze"); //0x04
			messages_list.push_back("draw_bot_visual"); //0x05
			messages_list.push_back("help"); //0x06
			messages_list.push_back("list_bot_movements"); //0x07
			messages_list.push_back("generate_file"); //0x08
			messages_list.push_back("get_bot_info"); //0x09
			messages_list.push_back("print_all_bots_info"); //0x0a
		}

		void case_sensitive_correction()
		{
			int index = 0;

			for (auto i : message_string)
			{
				if ((int)i < 91)
				{
					message_string[index] += 32;
				}
				index++;
			}
		}

		int process_message()
		{
			case_sensitive_correction();

			int index = 0;

			for (auto i : messages_list)
			{
				index++;

				if (i.compare(message_string) == 0)
				{
					return index;
				}
			}

			return 0x00;
		}
	};
public:
	Game(int bots_num);
	~Game();
private:
	Maze maze;
	Messages_Processor messages;

	void transfer_maze_info();
	void transfer_bots_info();

	int bots_number;
	std::vector< Bot* > bots;

	std::vector<bool> valid_grid;
	std::vector< std::pair<int,int> > valid_points_index;

	std::default_random_engine generator;

	void set_bots_initial_positions();

	int index;
	int steps;

	Timer timer;
public:
	void Update();
	bool winner();
};