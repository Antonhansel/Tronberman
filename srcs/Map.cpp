//
// Map.cpp for Map in /home/apollo/rendu/cpp_bomberman
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Thu May  1 16:48:07 2014 ribeaud antonin
// Last update Thu May  1 16:48:08 2014 ribeaud antonin
//

#include "Map.hpp"
#include "Case.hpp"

Map::Map(const int& x, const int& y) : 
	size_x(x), size_y(y)
{
	outline();
	drawWall();
	spawnBot();
}

Map::Map(const std::string& name)
{

}

Map::~Map()
{}

std::map< std::pair<int, int>, Case *>	Map::getCases()
{
	return (cases);
}

void		Map::outline()
{
	std::pair<int, int>	pos;
	Case_type type;

	type = Outline;
	for (int i = -size_x; i <= size_x; i++)
	{
		pos = std::make_pair(-size_y, i);
		cases[pos] = new Case(-size_y, i, type);
	}
	for (int i = -size_x; i <= size_x; i++)
	{
		pos = std::make_pair(size_y, i);
		cases[pos] = new Case(size_y, i, type);
	}
	for (int i = (-size_y + 1); i <= size_y; i++)
	{
		pos = std::make_pair(i, -size_y);
		cases[pos] = new Case(i, -size_y, type);
	}
	for (int i = (-size_y + 1); i <= size_y; i++)
	{
		pos = std::make_pair(i, size_y);
		cases[pos] = new Case(i, size_y, type);
	}
}

bool		Map::isEmpty(const int& x, const int& y)
{
	std::map< std::pair<int, int>, Case *> map = getCases();
	std::pair<int, int>	pos;

	pos = std::make_pair(x, y);
	cases[pos] = NULL;
	return (true);
}

bool		Map::spawnBotChecking(const int& x, const int& y)
{
	int		x_max;
	int		y_max;

	x_max = x;
	y_max = y;
	while (y_max < y + 3)
	{
		x_max = x;
		while (x_max < x + 3)
		{
			isEmpty(x_max, y_max);
			x_max++;
		}
		y_max++;
	}
	return (true);
}

void		Map::spawnBot()
{
	Case_type type;
	std::pair<int, int>	pos;

	type = Bot;
	for (int y = (-size_y + 16); y < size_y; y += 15)
	{
		for (int x = (-size_x + 16); x < size_x; x += 15)
		{
			if (spawnBotChecking(x - 1, y - 1) == true)
			{
				pos = std::make_pair(x, y);
				cases[pos] = new Case(x, y, type);
			}
		}
	}
}

void		Map::drawWall()
{
	int		min;
	int		max;
	Case_type type;
	std::pair<int, int>	pos;

	min = 0;
	max = 100;
	type = Block;
	srand(time(NULL));
	for (int y = (-size_y + 1); y < size_y; y++)
	{
		for (int x = (-size_x + 1); x < size_x; x++)
		{
			pos = std::make_pair(x, y);
			if ((rand()%(max - min) + min) > 80)
				cases[pos] = new Case(x, y, type);
			else
				cases[pos] = NULL;
		}
	}
}
