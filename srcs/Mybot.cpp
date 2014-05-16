#include "Mybot.hpp"

Mybot::Mybot()
{}

Mybot::~Mybot()
{}

bool      Mybot::lineSave(int x, int y, int m_x, int m_y)
{
  AObject *tmp;

  for (int i = 1; i <= 5; i++)
  {
      tmp = _map->getCase(x + (i * m_x), y + (i * m_y));
      if (tmp)
      {
          if (tmp->getType() == BOMB)
              return false;
          else if (tmp->getType() == BLOCKD || tmp->getType() == BLOCK)
              return true;
      }
  }
  return true;
}

bool      Mybot::isSafe(int x, int y)
{
  if (!lineSave(x, y, 0, 1))
      return false;
  if (!lineSave(x, y, 0, -1))
      return false;
  if (!lineSave(x, y, 1, 0))
      return false;
  if (!lineSave(x, y, -1, 0))
      return false;
  if (!lineSave(x, y, 0, 0))
     return false;
  return true;
}