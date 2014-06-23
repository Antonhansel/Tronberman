#include "Mybot.hpp"

Mybot::Mybot()
{
  _x_obj = 0;
  _y_obj = 0;
  _dep = 1;
  _modelpath = "./ressources/assets/anim/bomberman_white_run.FBX";
  _seerange = 8;
  _freq_bombs = 10;
  _action = 4;
  _rec = 6;
}

Mybot::~Mybot()
{}

PlayerType Mybot::getType() const
{
    return (IA);
}

bool      Mybot::lineSafe(const int x, const int y, const int m_x, const int m_y) const
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

bool      Mybot::isSafe(const int x, const int y) const
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

void      Mybot::moveTo(const int x, const int y, const int move_x, const int move_y)
{
  if (_checkMove2(x + move_x, y + move_y))
  {
    _x_obj = x + move_x;
    _y_obj = y + move_y;
  }
}

bool     Mybot::setObjDef(const int x, const int y, const int rec, enum dir last)
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

int     Mybot::setObjDef(const int x, const int y)
{
  int     inc;
  int     ret;

  ret = 4;
  srand(time(NULL));
  inc = (rand() + _id) % 4;
  for (int i = 0; i < 4; i++)
  {
    if (setObjDef(x + 1, y, 0, RIGHT) && inc % 4 == 0 && _checkMove2(x + 1, y))
    {
      moveTo(x, y, 1, 0);
      ret = LEFT;
    }
    else if (setObjDef(x - 1, y, 0, LEFT) && inc % 4 == 1 && _checkMove2(x - 1, y))
    {
      moveTo(x, y, -1, 0);
      ret = RIGHT;
    }
    else if (setObjDef(x, y + 1, 0, DOWN) && inc % 4 == 2 && _checkMove2(x, y + 1))
    {
      moveTo(x, y, 0, 1);
      ret = UP;
    }
    else if (setObjDef(x, y - 1, 0, UP) && inc % 4 == 3 && _checkMove2(x, y - 1))
    {
      moveTo(x, y, 0, -1);
      ret = DOWN;
    }
    inc++;
  }
  return ret;
}

int     Mybot::setObjOff(const int x, const int y)
{
  int     inc;
  int     ret;

  ret = 4;
  srand(time(NULL));
  inc = rand() % _action;
  for (int i = 0; i < 4; i++)
  {
     if (_checkMove2(x, y) && rand() % (_freq_bombs+_id) < _id)
       spawnBomb();
    if (isSafe(x + 1, y) && _checkMove2(x + 1, y) && inc % _action == 0)
    {
      moveTo(x, y, 1, 0);
      ret = LEFT;
    }
    else if (isSafe(x - 1, y) && _checkMove2(x - 1, y) && inc % _action == 1)
    {
      moveTo(x, y, -1, 0);
      ret = RIGHT;
    }
    else if (isSafe(x, y + 1) && _checkMove2(x, y + 1) && inc % _action == 2)
    {
      moveTo(x, y, 0, 1);
      ret = UP;
    }
    else if (isSafe(x, y - 1) && _checkMove2(x, y - 1) && inc % _action == 3)
    {
      moveTo(x, y, 0, -1);
      ret = DOWN;
    }
    inc++;
  }
  return (ret);
}

void    Mybot::update(gdl::Clock const &clock, gdl::Input &input)
{
  float trans = static_cast<float>(clock.getElapsed()) * _speed /4;
  AObject                                 *tmp;
  int     x;
  int     y;

  x = realPos(getPos()).first;
  y = realPos(getPos()).second;
  _shield += clock.getElapsed();
  if ((_dep >= 0.9 && (_x_obj - x == 0 && _y_obj - y == 0)) || (_x_obj == 0 && _y_obj == 0))
  {
    if (isSafe(x, y))
      _move = setObjOff(x, y);
    else
      _move =setObjDef(x, y);
    if (_move < 4)
      _dep = 0;
  }
  else if (_isAlive)
  {
    if (_move == LEFT)
    {
      translate(glm::vec3(trans, 0, 0));
      _pos.first += trans;
      _dep += trans;
    }
    else if (_move == RIGHT)
    {
      translate(glm::vec3(-trans, 0, 0));
      _pos.first -= trans;
      _dep += trans;
    }
    else if (_move == UP)
    {
      translate(glm::vec3(0, 0, trans));
      _pos.second +=  trans;
      _dep += trans;
    }
    else if (_move == DOWN)
    {
      translate(glm::vec3(0, 0, -trans));
      _pos.second -=  trans;
      _dep += trans;
    }
    tmp = _map->getCase(_pos.first, _pos.second);
    if (tmp && (tmp->getType() < 12 && tmp->getType() >= 9))
    {
      static_cast<Bonus*>(tmp)->addToPlayer(this);
      _sound->playSound(BONUS_S, 30);
      _map->deleteCube(_pos.first, _pos.second);
    }
  }
}

void    Mybot::setSeeRange(const int seerange)
{
  _seerange = seerange;
}

void    Mybot::setRec(const int rec)
{
  _rec = rec;
}

void    Mybot::setAction(const int action)
{
  _action = action;
}

void    Mybot::setFreqBombs(const int freq_bombs)
{
  _freq_bombs = freq_bombs;
}