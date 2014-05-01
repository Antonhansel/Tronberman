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
	draw_wall();
	spawn_bot();
}

Map::Map(const std::string& name)
{

}

Map::~Map()
{}

std::list<Case *>	Map::getCases()
{
	return (cases);
}

void		Map::outline()
{
	Case_type type;

	type = Outline;
	for (int i = -size_x; i <= size_x; i++)
	{
		cases.push_front(new Case(-size_y, i, type));
	}
	for (int i = -size_x; i <= size_x; i++)
	{
		cases.push_front(new Case(size_y, i, type));
	}

	for (int i = (-size_y + 1); i <= size_y; i++)
	{
		cases.push_front(new Case(i, -size_y, type));
	}

	for (int i = (-size_y + 1); i <= size_y; i++)
	{
		cases.push_front(new Case(i, size_y, type));
	}
}

bool		Map::isEmpty(const int& x, const int& y)
{
	std::list<Case *> map = getCases();

	for (std::list<Case *>::iterator it = map.begin(); it != map.end(); it++)
	{	
		if ((*it)->getPosx() == x && (*it)->getPosy() == y)
		{
			map.remove(*it);
			return (true);
		}
	}
	return (false);
}

bool		Map::spawn_bot_checking(const int& x, const int& y)
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

void		Map::spawn_bot()
{
	Case_type type;

	type = Bot;
	for (int y = (-size_y + 16); y < size_y; y += 15)
	{
		for (int x = (-size_x + 16); x < size_x; x += 15)
		{
			if (spawn_bot_checking(x - 1, y - 1) == true)
				cases.push_front(new Case(x, y, type));
		}
	}
}

void		Map::draw_wall()
{
	int		min;
	int		max;
	Case_type type;

	min = 0;
	max = 100;
	type = Block;
	srand(time(NULL));


	for (int y = (-size_y + 1); y < size_y; y++)
	{
		for (int x = (-size_x + 1); x < size_x; x++)
		{
			if ((rand()%(max - min) + min) > 70)
				cases.push_front(new Case(x, y, type));
		}
	}
}
