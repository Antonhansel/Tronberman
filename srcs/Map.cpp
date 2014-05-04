//
// Map.cpp for Map in /home/apollo/rendu/cpp_bomberman
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Thu May  1 16:48:07 2014 ribeaud antonin
// Last update Sun May  4 03:21:00 2014 Mehdi Chouag
//

#include "Map.hpp"

Map::Map(const int& x, const int& y, std::map< std::pair<float, float>, AObject * > &map) : 
  size_x(x), size_y(y), cases(map)
{
  outline();
  drawWall();
  // spawnBot();
}

Map::Map(const std::string& name)
{

}

Map::~Map()
{}

void		Map::outline()
{
  std::pair<float, float>	pos;

  for (int i = -size_x; i <= size_x; i++)
    {
      pos = std::make_pair(-size_y, i);
      cases[pos] = create<Cube>();
      cases[pos]->setType(BORDER);
      cases[pos]->setPos(pos);
      cases[pos]->initialize();
    }
  for (int i = -size_x; i <= size_x; i++)
    {
      pos = std::make_pair(size_y, i);
      cases[pos] = create<Cube>();
      cases[pos]->setType(BORDER);
      cases[pos]->setPos(pos);
      cases[pos]->initialize();
    }
  for (int i = (-size_y + 1); i <= size_y; i++)
    {
      pos = std::make_pair(i, -size_y);
      cases[pos] = create<Cube>();
      cases[pos]->setType(BORDER);
      cases[pos]->setPos(pos);
      cases[pos]->initialize();
    }
  for (int i = (-size_y + 1); i <= size_y; i++)
    {
      pos = std::make_pair(i, size_y);
      cases[pos] = create<Cube>();
      cases[pos]->setType(BORDER);
      cases[pos]->setPos(pos);
      cases[pos]->initialize();
    }
}

// bool		Map::spawnBotChecking(const int& x, const int& y)
// {
//   int		x_max;
//   int		y_max;

//   x_max = x;
//   y_max = y;
//   while (y_max < y + 3)
//     {
//       x_max = x;
//       while (x_max < x + 3)
// 	{
// 	  isEmpty(x_max, y_max);
// 	  x_max++;
// 	}
//       y_max++;
//     }
//   return (true);
// }

// void		Map::spawnBot()
// {
//   type		blocktype;
//   std::pair<float, float>	pos;

//   blocktype = BOT;
//   for (int y = (-size_y + 16); y < size_y; y += 15)
//     {
//       for (int x = (-size_x + 16); x < size_x; x += 15)
// 	{
// 	  if (spawnBotChecking(x - 1, y - 1) == true)
// 	    {
// 	      pos = std::make_pair(x, y);
// 	      cases[pos] = create<Cube>();
// 	      cases[pos]->setType(BORDER);
// 	      cases[pos]->setPos(x, y);      
// 	    }
// 	}
//     }
// }

std::map< std::pair<float, float>, AObject *> &Map::getMap()
{
  return (cases);
}

void		Map::drawWall()
{
  int		min;
  int		max;
  std::pair<float, float>	pos;

  min = 0;
  max = 100;
  srand(time(NULL));
  for (int y = (-size_y + 1); y < size_y; y++)
    {
      for (int x = (-size_x + 1); x < size_x; x++)
	{
	  pos = std::make_pair(x, y);
	  if ((rand()%(max - min) + min) > 80)
	    {
	      cases[pos] = create<Cube>();
	      cases[pos]->setType(BLOCKD);
	      cases[pos]->setPos(pos);
	      cases[pos]->initialize();
	    }
	}
    }
}
