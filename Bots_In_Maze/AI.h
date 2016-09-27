#pragma once

#include <string>
#include <vector>
#include <time.h>

class AI
{
private:
	enum AI_Moves
	{
		up,
		right,
		down,
		left
	};
public:
	AI();
	~AI();

	AI_Moves compute_movement(const std::string & visual);
private:
	AI_Moves ai_move;
};
