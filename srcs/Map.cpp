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

int     Map::getSide(float x, float y)
{
  std::pair<float, float>   spawn;
  int     check;

  check = 0;
  spawn = std::make_pair((float)x + 1, (float)y);
  if (cases.find(spawn) == cases.end())
    check++;
  spawn.first -= 2;
  if (cases.find(spawn) == cases.end())
    check++;
  spawn.first -= 1;;
  spawn.second += 1;;
  if (cases.find(spawn) == cases.end())
    check++;
  spawn.second -= 1;
  if (cases.find(spawn) == cases.end())
    check++;
  return (check);
}

bool    Map::deleteSide(float x, float y)
{
  std::pair<float, float>   spawn;
  std::map< std::pair<float, float>, AObject * >::iterator it;

  spawn = std::make_pair((float)x + 1, (float)y);
  if ((it = cases.find(spawn)) != cases.end())
    if ((*it).second->getType() == BLOCKD)
    {
      cases.erase(it);
      return (true);
    }
  spawn.first -= 2;
  if ((it = cases.find(spawn)) != cases.end())
    if ((*it).second->getType() == BLOCKD)
    {
      cases.erase(it);
      return (true);
    }
  spawn.first += 1;
  spawn.second -= 1;
  if ((it = cases.find(spawn)) != cases.end())
    if ((*it).second->getType() == BLOCKD)
    {
      cases.erase(it);
      return (true);
    }
  spawn.first += 2;
  if ((it = cases.find(spawn)) != cases.end())
    if ((*it).second->getType() == BLOCKD)
    {
      cases.erase(it);
      return (true);
    }
  return (false);
}

std::vector<std::pair <float, float> >   Map::setSpawn(int nb)
{
  std::map< std::pair<float, float>, AObject * >::iterator it;
  std::vector<std::pair <float, float> > spawns;
  std::pair <float, float>   spawn;
  int   x;
  int   y;

  srand(time(NULL));
  for (int i = 0; i < nb; i++)
  {
    if ((x = rand() %(size_x * 2) -size_x) %2 == 0)
      x++;
    if ((y = rand() %(size_y * 2) -size_y) %2 == 0)
      y++;
    spawn = std::make_pair((float)x, (float)y);
    if ((it = cases.find(spawn)) != cases.end())
      if ((*it).second->getType() == BLOCKD)
        cases.erase(it);
    while (getSide(x, y) < 2)
      deleteSide(x, y);
    spawns.push_back(std::make_pair((float)x, (float)y));
  }
  return (spawns);
}
