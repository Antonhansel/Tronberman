//
// Map.cpp for Map in /home/apollo/rendu/cpp_bomberman
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Thu May  1 16:48:07 2014 ribeaud antonin
// Last update Sat May 10 01:34:58 2014 Mehdi Chouag
//

#include "Map.hpp"

Map::Map(const int& x, const int& y, std::map< std::pair<float, float>, AObject * > &map)
{
  size_x = x; 
  size_y = y; 
  cases = map;
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
  std::pair<float, float> pos;

  srand(time(NULL));
  for (int y = -size_y; y <= size_y; y++)
    {
      for (int x = -size_x; x <= size_x; x++)
      {
        if (x != -size_x && x != size_x &&
            y != -size_y && y != size_y)
        {
          pos = std::make_pair(y, x);
          if (x % 2 == 0 && y % 2 == 0 && !(x == 0 && y == 0))
            {
              cases[pos] = create<Cube>();
              cases[pos]->setType(BLOCK);
              cases[pos]->setPos(pos);
              cases[pos]->initialize();
            }
          else if ((rand() % 100) > 75 && cases[pos] == NULL)
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
