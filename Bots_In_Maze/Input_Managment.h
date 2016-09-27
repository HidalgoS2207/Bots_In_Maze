#pragma once

#include <fstream>
#include <math.h>

class Input_Managment
{
private:
	class String_Transformation
	{
	public:
		String_Transformation()
			:
			ret(0)
		{}
		~String_Transformation() {}

		int string_to_int(std::string st)
		{
			ret = 0;

			for (int i = 0; i < st.size(); i++)
			{
				ret += ((int)st[i] - 48)*(pow(10, (st.size() - 1 - i)));
			}

			return ret;
		}
	private:
		int ret;
	};
public:
	Input_Managment();
	~Input_Managment();

private:
	std::ifstream ifs;
	std::string map_size_string;

	const unsigned int max_map_width;
	const unsigned int max_map_height;
	const unsigned int min_map_height;
	const unsigned int min_map_width;

	String_Transformation st;

public:

	std::string fill_string(std::pair<int,int> map_size);
	std::pair<int,int> set_map_size();

	
};