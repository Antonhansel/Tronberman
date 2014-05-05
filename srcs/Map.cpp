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
}

Map::Map(const std::string& name)
{

}

Map::~Map()
{}

void    Map::outline()
{
  std::pair<float, float> pos;

  for (int y = -size_y; y <= size_y; y++)
  {
    for (int x = -size_x; x <= size_x; x++)
    {
      if (x == -size_x || x == size_x ||
          y == -size_y || y == size_y)
      {
        pos = std::make_pair(y, x);
        cases[pos] = create<Cube>();
        cases[pos]->setType(BORDER);
        cases[pos]->setPos(pos);
        cases[pos]->initialize();
      }
    }

  }
}

std::map< std::pair<float, float>, AObject *> &Map::getMap()
{
  return (cases);
}

void    Map::drawWall()
{
  int   min;
  int   max;
  std::pair<float, float> pos;

  min = 0;
  max = 100;
  srand(time(NULL));
  for (int y = -size_y; y <= size_y; y++)
    {
      for (int x = -size_x; x <= size_x; x++)
      {
        if (x != -size_x && x != size_x &&
            y != -size_y && y != size_y && 
            x != 0 && x != 1 && y != 0 && y != 1)
        {
          pos = std::make_pair(y, x);
          if ((rand()%(max - min) + min) > 90)
            {
              cases[pos] = create<Cube>();
              cases[pos]->setType(BLOCKD);
              cases[pos]->setPos(pos);
              cases[pos]->initialize();
            }
        }
      }
    } 
}