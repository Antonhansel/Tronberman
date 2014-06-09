//
// Player.cpp for Player in /home/chouag_m/rendu/bitbucker
//
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
//
// Started on  Sat May 10 00:23:31 2014 Mehdi Chouag
// Last update Sat May 10 00:58:19 2014 Mehdi Chouag
//

#include "Bombs.hpp"
#include "Map.hpp"
#include "Bonus.hpp"

Player::Player()
{
  _stock = 1;
  _range = 2;
  _x = 0;
  _life = 1;
  _begin = false;
  _input = NULL;
  _key[PUP] = &Player::up;
  _key[PDOWN] = &Player::down;
  _key[PRIGHT] = &Player::right;
  _key[PLEFT] = &Player::left;
  _shield = 1;
  _isAlive = true;
  _score = 0;
  _dir = NORTH;
  _modelpath = "./ressources/assets/anim/bomberman_gold_run.FBX";
}

Player::~Player()
{}

PlayerType Player::getType() const
{
  return (HUMAN);
}


bool    Player::initialize()
{
  _speed = 7;
  _pos.second += 0.3;
  if (_model.load(_modelpath) == false)
  {
    std::cout << "Error on loading model" << std::endl;
    return (false);
  }
  scale(glm::vec3(1,2,1));
  translate(glm::vec3(-0.5, 0, 0));
  return (true);
}

void  Player::spawnBomb()
{
  std::pair<float, float> pos;

  pos = realPos(getPos());
  if (_bombs->find(pos) == _bombs->end())
  {
    _sound->playSound(PBOMB_S, 30);
    Bombs *b = new Bombs();
    b->setObjects(_map, _sound, _bombs);
    b->setPlayerTab(_playermap);
    b->makeBomb((Player*)this);
    (*_bombs)[pos] = b;
  }
}

void    Player::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  if (_dir == WEST)
    translate(glm::vec3(0.25, 0, 0.25));
  else if (_dir == EAST)
    translate(glm::vec3(-0.25, 0, -0.25));
  else if (_dir == SOUTH)
    translate(glm::vec3(0.25, 0, -0.25));
  else
  {
    translate(glm::vec3(-0.25, 0, 0.25));
  }
  _model.setCurrentAnim(_anim);
  _model.gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
  if (_dir == WEST)
    translate(glm::vec3(-0.25, 0, -0.25));
  else if (_dir == EAST)
    translate(glm::vec3(0.25, 0, 0.25));
  else if (_dir == SOUTH)
    translate(glm::vec3(-0.25, 0, 0.25));
  else
    translate(glm::vec3(0.25, 0, -0.25));
}

void    Player::setMap(Map *map)
{
  _map = map;
}

void    Player::setPlayer(int player)
{
  _player = player;
}

void    Player::setSpeed(float speed)
{
  _speed = speed;
  _speedActiv = 10;
}

bool    Player::_checkMove2(float x, float y)
{
  AObject *cas = _map->getCase(x, y);
  if (!cas || cas->getType() == BONUSV || cas->getType() == BONUSB || cas->getType() == BONUSR)
    return (true);
  else
    return (false);
}

AObject    *Player::_checkMove(float x, float y)
{
  AObject *tmp;
  tmp = NULL;
  std::pair<float, float> pos;
  if (x != 0)
  {
    if (x > 0)
    {
      pos.first = floor(_pos.first + x + 0.2);
      pos.second = floor(_pos.second + y + 0.2);
    }
    else
    {
      pos.first = floor(_pos.first + x - 0.2);
      pos.second = floor(_pos.second + y + 0.2);
    }
    tmp = _map->getCase(pos.first, pos.second);
    if (!tmp)
    {
      if (x > 0)
      {
        pos.first = floor(_pos.first + x + 0.2);
        pos.second = floor(_pos.second + y - 0.2);
      }
      else
      {
        pos.first = floor(_pos.first + x - 0.2);
        pos.second = floor(_pos.second + y - 0.2);
      }
      tmp = _map->getCase(pos.first, pos.second);
    }
  }
  else if (y != 0)
  {
    if (y > 0)
    {
      pos.first = floor(_pos.first + x + 0.2);
      pos.second = floor(_pos.second + y + 0.2);
    }
    else
    {
      pos.first = floor(_pos.first + x + 0.2);
      pos.second = floor(_pos.second + y - 0.2);
    }
    tmp = _map->getCase(pos.first, pos.second);
    if (!tmp)
    {
      if (y > 0)
      {
        pos.first = floor(_pos.first + x - 0.2);
        pos.second = floor(_pos.second + y + 0.2);
      }
      else
      {
        pos.first = floor(_pos.first + x - 0.2);
        pos.second = floor(_pos.second + y - 0.2);
      }
      tmp = _map->getCase(pos.first, pos.second);
    }
  }
  return (tmp);
}

bool    Player::_onBomb(float x, float y)
{
  std::pair<float, float>   pos;
  AObject *tmp;
  AObject *cur = _map->getCase(_pos.first, _pos.second);
  if (cur != NULL && (cur->getType() == BOMB || cur->getType() == LASER))
  {
    if ((tmp = _checkMove(x, y)) == NULL || (tmp && (tmp->getType() <= 12 && tmp->getType() >= 9)) || (tmp && tmp->getType() == BOMB))
      return (true);
  }
  return (false);
}

void    Player::update(const gdl::Clock &clock, gdl::Input &input)
{
  std::vector<key> k;

  if (_isAlive == true)
  {
    if (_speedActiv > 0)
    {
      _speedActiv -= clock.getElapsed();
      if (_speedActiv <= 0)
        _speed = 7;
    }
    float trans = static_cast<float>(clock.getElapsed()) *  _speed;
    std::map<int, std::pair<float, float> >                 keymap;
    std::pair<float, float> i;
    glm::vec3                               rotation = glm::vec3(0);
    AObject                                 *tmp;
    int                                     numHumans = 0;
    std::pair<float,float> (Player::*moveFct)(float &);

    _shield += clock.getElapsed();
    for (std::vector<Player *>::iterator i = _playermap->begin(); i != _playermap->end(); ++i)
    {
      if ((*i)->getType() == HUMAN)
        ++numHumans;
    }
    if (_input == NULL && _id == 1)
    {
      _input = new AInput(input, KEY1);
      if (numHumans >= 2)
        _input->setMode(true);
    }
    else if (_input == NULL && _id == 2)
      _input = new AInput(input, KEY2);
    _input->setInput(input);
    k = _input->getInput();
    for (std::vector<key>::iterator it = k.begin(); it != k.end(); ++it)
    {
      if (_input && !AInput::getKey(k, NONE))
      {
        if (_input && AInput::getKey(k, PBOMB))
          this->spawnBomb();
        moveFct = this->_key[(*it)];
        if (!moveFct)
          continue;
        i = (this->*_key[(*it)])(trans);
        _anim = 2;
        rotation.y += (i.second) ? (SIGN(i.second) * 90 - 90) : (0);
        rotation.y += (i.first) ? (SIGN(i.first) * -90 + 180) : (0);
        switch ((int)(rotation.y))
        {
          case 0:
          _dir = NORTH;
          break;
          case -180:
          _dir = SOUTH;
          break;
          case 270:
          _dir = EAST;
          break;
          case 90:
          _dir = WEST;
        }
        rotate(rotation);
        tmp = _checkMove(i.first, i.second);
        if (!tmp || (tmp && (tmp->getType() <= 12 && tmp->getType() >= 9)) || _onBomb(i.first, i.second)/*|| _checkMove2(i.first, i.second)*/)
        {
          if (tmp && (tmp->getType() <= 12 && tmp->getType() >= 9))
          {
            static_cast<Bonus*>(tmp)->addToPlayer(this);
            _sound->playSound(BONUS_S, 30);
            _map->deleteCube(tmp->getPos().first, tmp->getPos().second);
          }
          _pos.first += i.first;
          _pos.second += i.second;
          translate(glm::vec3(i.first, 0, i.second));
        }
      }
      else if (_input && AInput::getKey(k, PBOMB))
        this->spawnBomb();
    }
    if (_anim == 2)
      _anim = 1;
    else
      _anim = 0;
  }
}


std::pair<float, float>    Player::up(float &trans)
{
  std::pair<float, float> i(0, trans);

  return (i);
}

std::pair<float, float>    Player::down(float &trans)
{
  std::pair<float, float> i(0, -trans);

  return (i);
}

std::pair<float, float>    Player::right(float &trans)
{
  std::pair<float, float> i(-trans, 0);

  return (i);
}

std::pair<float, float>    Player::left(float &trans)
{
  std::pair<float, float> i(trans, 0);

  return (i);
}

std::pair<float, float>     &Player::realPos(std::pair<float, float> pos)
{
  float temp1;
  float temp2;
  temp1 = floor(pos.first);
  temp2 = ceil(pos.first);
  if (temp1 - pos.first > pos.first - temp2)
    pos.first = temp1;
  else
    pos.first = temp2;
  temp1 = floor(pos.second);
  temp2 = ceil(pos.second);
  if (temp1 - pos.second > pos.second - temp2)
    pos.second = temp1;
  else
    pos.second = temp2;
  return (pos);
}

int     Player::getStock() const
{
  return (_stock);
}

void  Player::setStock(int stock)
{
  _stock = stock;
}

void  Player::setId(int id)
{
  _id = id;
  if (_id == 1 || _id == 0)
    _modelpath = "./ressources/assets/anim/bomberman_black_run.FBX";
  else if (_id == 2)
    _modelpath = "./ressources/assets/anim/bomberman_blue_run.FBX";
}

int   Player::getId() const
{
  return (_id);
}

int   Player::getRange() const
{
  return (_range);
}

void  Player::setBombs(std::map<std::pair<float, float>, Bombs *>  *bombs)
{
  _bombs = bombs;
}

void  Player::setRange(int range)
{
  _range = range;
}

void    Player::setLife(int newLife)
{
  _life = newLife;
  _shield = 0;
}

int     Player::getLife() const
{
  return (_life);
}

bool    Player::getBegin() const
{
  return (_begin);
}

void    Player::setBegin(bool begin)
{
  _begin = begin;
}

float    Player::getShield() const
{
  return (_shield);
}

void    Player::setShield(float s)
{
  _shield = s;
}

bool    Player::isAlive() const
{
  return (_isAlive);
}

void    Player::setIsAlive()
{
  _isAlive = false;
}

void    Player::setScore(int newScore)
{
  _score = newScore;
}

int     Player::getScore() const
{
  return (_score);
}

void    Player::setPlayerTab(std::vector<Player*> *playermap)
{
  _playermap = playermap;
}

void    Player::setSound(Sound *sound)
{
  _sound = sound;
}

float   Player::getSpeed() const
{
  return (_speed);
}

void    Player::dir(dirr dir)
{
  glm::vec3  rotation = glm::vec3(0);
  switch (dir)
  {
    case NORTH:
    rotation.y = 0;
    break;
    case SOUTH:
    rotation.y = 180;
    break;
    case WEST:
    rotation.y = 90;
    break;
    case EAST:
    rotation.y = 270;
    break;
  }
  rotate(rotation);
  _dir = dir;
}
dirr    Player::dir() const
{
  return (_dir);
}

