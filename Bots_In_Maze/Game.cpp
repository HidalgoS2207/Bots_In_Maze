#include "Game.h"

Game::Game(int bots_num)
	:
	maze(bots_num),
	messages(),
	bots_number(bots_num),
	generator((int)time(NULL))
{
	for (int i = 0; i < bots_number; i++)
	{
		bots.push_back(new Bot());
	}

	for (int i = 0; i < maze.get_map_size().second; i++)
	{
		for (int j = 0; j <= maze.get_map_size().first; j++)
		{
			if (maze.get_single_block(j + (i*(maze.get_map_size().first + 1))) == '#' || maze.get_single_block(j + (i*(maze.get_map_size().first + 1))) == 'e' || maze.get_single_block(j + (i*(maze.get_map_size().first + 1))) == '\n')
			{
				valid_grid.push_back(false);
			}
			else
			{
				valid_points_index.push_back({ j,i });
				valid_grid.push_back(true);
			}
		}
	}

	set_bots_initial_positions();

	transfer_bots_info();
	transfer_maze_info();
}

Game::~Game()
{
	for (int i = 0; i < bots_number; i++)
	{
		delete bots[i];
	}
}

void Game::transfer_maze_info()
{
	for (int i = 0; i < bots_number; i++)
	{
		bots[i]->save_maze_data(maze.get_visual(i) , maze.check_exit_position(i));
	}
}

void Game::transfer_bots_info()
{
	for (int i = 0; i < bots_number; i++)
	{
		maze.save_bots_data(bots[i]->get_bot_pos(), bots[i]->get_facing(), i);
	}
}

void Game::set_bots_initial_positions()
{
	std::uniform_int_distribution<int> distribution_position(0,valid_points_index.size() - 1);
	std::uniform_int_distribution<int> distribution_orientation(0, 3);

	for (int i = 0; i < bots_number; i++)
	{
		bots[i]->set_initial_position(valid_points_index[distribution_position(generator)]);
		bots[i]->set_initial_orientation(distribution_orientation(generator));
	}
}

void Game::Update()
{
	switch (messages.get_message())
	{
	case 0x00: //messages doesn't match with the current command, returns 0 and waits for commands input
		printf("\nNot a valid command - Type 'Help' for commands list\n");
		break;
	case 0x01: //exit command
		throw 0x09;
	case 0x02: //Make single move command
		timer.start_watch();
		
		for (int i = 0; i < bots_number; i++)
		{
			bots[i]->bot_next_move();
		}

		transfer_bots_info();
		transfer_maze_info();

		timer.stop_watch();

		std::cout << "Movements done in " << timer.get_time() << " millisecons\n";
		break;
	case 0x03:
		std::cout << "\nSet the number of steps:";
		while (std::cin >> steps && (steps < 1 || steps > 1000)) {}
		timer.start_watch();
		for (int i = 0; i < steps; i++)
		{
			for (int i = 0; i < bots_number; i++)
			{
				bots[i]->bot_next_move();
			}

			transfer_bots_info();
			transfer_maze_info();

			if (winner())
			{
				break;
			}
		}
		timer.stop_watch();

		std::cout << "Movements done in " << timer.get_time() << " millisecons\n";
		break;
	case 0x04:
		maze.print_maze();
		break;
	case 0x05: //Draw the choosen bot current visual
		index = 0;
		std::cout << "Select bot: ";
		std::cin >> index;
		while ((index > bots_number || index < 1))
		{
			std::cin >> index;
		}
		bots[index - 1]->draw_visual();
		break;
	case 0x06: //help command -> print commands table
		printf("\nCommands Table: \n");
		for (int i = 0; i < messages.get_command_list_size(); i++)
		{
			std::cout << "\n" << i + 1 << " " << messages.get_command_string(i);
		}
		std::cout << "\n";
		break;
	case 0x07:
		break;
	case 0x08:
		break;
	case 0x09: //print to screen bot info (position and orientation)
		index = 0;
		std::cout << "Select bot number: ";
		std::cin >> index;
		while ((index > bots_number || index < 1))
		{
			std::cin >> index;
		}
		std::cout << "Bot number " << index << "\nPosition = {" << bots[index - 1]->get_bot_pos().first << ";" << bots[index - 1]->get_bot_pos().second << "}\n";
		std::cout << "Orientation = ";
		switch (bots[index - 1]->get_facing())
		{
		case 0:
			std::cout << "North\n";
			break;
		case 1:
			std::cout << "East\n";
			break;
		case 2:
			std::cout << "South\n";
			break;
		case 3:
			std::cout << "West\n";
			break;
		}
		break;
	case 0x0a:
		for (int i = 0; i < bots_number; i++)
		{
			std::cout << "Bot number " << i + 1 << "\nPosition = {" << bots[i]->get_bot_pos().first << ";" << bots[i]->get_bot_pos().second << "}\n";
			std::cout << "Orientation = ";
			switch (bots[i]->get_facing())
			{
			case 0:
				std::cout << "North\n";
				break;
			case 1:
				std::cout << "East\n";
				break;
			case 2:
				std::cout << "South\n";
				break;
			case 3:
				std::cout << "West\n";
				break;
			}
			std::cout << "\n";
		}
		break;
	case 0xFF:
		std::cout << "\n'help' command for complete commands list\n";
		break;
	default:
		break;
	}

	if (!winner())
	{
		printf("\n> ");
		messages.wait_for_message();
	}
	else
	{
		index = 0;

		while (!bots[index]->bot_win())
		{
			index++;
		}

		printf("\n-- The Winner is Bot Number %d --\n\n", index + 1);
	}
}

bool Game::winner()
{
	index = 0;

	while ((!bots[index]->bot_win()))
	{
		index++;

		if (index == bots_number)
		{
			return false;
		}
	}

	return true;
}
