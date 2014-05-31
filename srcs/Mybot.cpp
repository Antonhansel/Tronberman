#include "Mybot.hpp"

Mybot::Mybot()
{
  _x_obj = 0;
  _y_obj = 0;
  _seerange = 5;
  _rec = 3;
  _modelpath = "./ressources/assets/anim/bomberman_white_run.FBX";
}

Mybot::~Mybot()
{}

PlayerType Mybot::getType() const
{
    return (IA);
}

bool      Mybot::lineSafe(int x, int y, int m_x, int m_y) const
{
  AObject *tmp;

  for (int i = 1; i <= _seerange; i++)
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

bool      Mybot::isSafe(int x, int y) const
{
  if (!lineSafe(x, y, 0, 1))
      return false;
  if (!lineSafe(x, y, 0, -1))
      return false;
  if (!lineSafe(x, y, 1, 0))
      return false;
  if (!lineSafe(x, y, -1, 0))
      return false;
  if (!lineSafe(x, y, 0, 0))
     return false;
  return true;
}

void      Mybot::moveTo(int x, int y, int move_x, int move_y)
{
  if (_checkMove2(x + move_x, y + move_y))
  {
    _x_obj = x + move_x;
    _y_obj = y + move_y;
  }
}

bool     Mybot::setObjDef(int x, int y, int rec, dir last)
{
  int     inc;

 srand(time(NULL));
  inc = (rand() + _id) % 4;
  if (isSafe(x, y))
    return true;
  if (rec > 3)
    return false;
  for (int i = 0; i < 4; i++)
  {
    if (_checkMove2(x + 1, y) && inc % 4 == 0 && last != LEFT)
    {
      if (setObjDef(x + 1, y, rec + 1, RIGHT))
        return true;
    }
    else if (_checkMove2(x - 1, y) && inc % 4 == 1 && last != RIGHT)
    {
      if (setObjDef(x - 1, y, rec + 1, LEFT))
        return true;
    }
    else if (_checkMove2(x, y + 1) && inc % 4 == 2 && last != UP)
    {
      if (setObjDef(x, y + 1, rec + 1, DOWN))
        return true;
    }
    else if (_checkMove2(x, y - 1) && inc % 4 == 3 && last != DOWN)
    {
      if (setObjDef(x, y - 1, rec + 1, UP))
        return true;
    }
    inc++;
  }
  return false;
}

void     Mybot::setObjDef(int x, int y)
{
  int     inc;

  srand(time(NULL));
  inc = (rand() + _id) % 4;
  for (int i = 0; i < 4; i++)
  {
    if (setObjDef(x + 1, y, 0, RIGHT) && inc % 4 == 0)
      moveTo(x, y, 1, 0);
    else if (setObjDef(x - 1, y, 0, LEFT) && inc % 4 == 1)
      moveTo(x, y, -1, 0);
    else if (setObjDef(x, y + 1, 0, DOWN) && inc % 4 == 2)
      moveTo(x, y, 0, 1);
    else if (setObjDef(x, y - 1, 0, UP) && inc % 4 == 3)
      moveTo(x, y, 0, -1);
    inc++;
  }
}

void     Mybot::setObjOff(int x, int y)
{
  int     inc;

  srand(time(NULL));
  inc = rand() % 4;
  for (int i = 0; i < 4; i++)
  {
    if (isSafe(x + 1, y) && _checkMove2(x + 1, y) && inc % 4 == 0)
      moveTo(x, y, 1, 0);
    else if (isSafe(x - 1, y) && _checkMove2(x - 1, y) && inc % 4 == 1)
      moveTo(x, y, -1, 0);
    else if (isSafe(x, y + 1) && _checkMove2(x, y + 1) && inc % 4 == 2)
      moveTo(x, y, 0, 1);
    else if (isSafe(x, y - 1) && _checkMove2(x, y - 1) && inc % 4 == 3)
      moveTo(x, y, 0, -1);
      if (_checkMove2(x, y) && rand() % (10+_id) < _id)
          spawnBomb();
    inc++;
  }
}

void    Mybot::update(gdl::Clock const &clock, gdl::Input &input)
{
  float trans = static_cast<float>(clock.getElapsed()) * _speed / 2;
  glm::vec3                               rotation = glm::vec3(0);
  //float trans = 1;
  int     x;
  int     y;

   x = realPos(getPos()).first;
   y = realPos(getPos()).second;
  if ((x == _x_obj && y == _y_obj) || (_x_obj == 0 && _y_obj == 0))
  {
      if (isSafe(x, y))
       setObjOff(x, y);
      else
        setObjDef(x, y);
  }
  else
  {
    translate(glm::vec3(trans * (_x_obj - x), 0, trans * (_y_obj - y)));
    _pos.first += trans * (_x_obj - x);
    _pos.second +=  trans * (_y_obj - y);
      if ((rotation.y = (_x_obj - x) * 90) == 0)
        rotation.y = (_y_obj - y + 1) * 90 + 180;
      rotate(rotation);
  }
}

void    Mybot::setSeeRange(int seerange)
{
  _seerange = seerange;
}

void    Mybot::setRec(int rec)
{
  _rec = rec;
}
