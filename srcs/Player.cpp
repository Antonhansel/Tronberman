//
// Player.cpp for Player in /home/chouag_m/rendu/bitbucker
//
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
//
// Started on  Sat May 10 00:23:31 2014 Mehdi Chouag
// Last update Sat May 10 00:58:19 2014 Mehdi Chouag
//

#include "Player.hpp"
#include "Map.hpp"

Player::Player()
{
    _stock = 3;
    _range = 2;
    _x = 0;
    _life = 3;
    _begin = false;
    _input = NULL;
    _key[PUP] = &Player::up;
    _key[PDOWN] = &Player::down;
    _key[PRIGHT] = &Player::right;
    _key[PLEFT] = &Player::left;
    _shield = 1;
    _isAlive = true;
}

Player::~Player()
{}

bool    Player::initialize()
{
    _speed = 7;
    _model.load( "./ressources/assets/bomberman_white_run.FBX");
    scale(glm::vec3(1,2,1));
    translate(glm::vec3(-0.5, 0, 0));
    return (true);
}

void    Player::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
    glPushMatrix();
    _model.setCurrentAnim(_anim);
    _model.gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
    glPopMatrix();
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
}

bool    Player::_checkMove(float x, float y)
{
    AObject *cas = _map->getCase(floor(_pos.first + x), floor(_pos.second + y));
    if (!cas || cas->getType() == BONUS)
        return (true);
    else
        return (false);
}

bool    Player::_onBomb()
{
    AObject     *tmp;

    return (((tmp = _map->getCase(floor(_pos.first), floor(_pos.second)))
        && tmp->getType() == BOMB)
        || ((tmp = _map->getCase(floor(_pos.first + 0.4), floor(_pos.second + 0.4)))
        && tmp->getType() == BOMB));
}

void    Player::update(gdl::Clock const &clock, gdl::Input &input)
{
    if (_isAlive == true)
    {
    float trans = static_cast<float>(clock.getElapsed()) * _speed;
    std::map<int, std::pair<float, float> > keymap;
    std::pair<float, float> i;
    glm::vec3                               rotation = glm::vec3(0);
    key                                      key;
    AObject                                 *tmp;

    _shield += clock.getElapsed();
    if (_input == NULL && _player == 1)
        _input = new AInput(input, KEY1);
    else if (_input == NULL && _player == 2)
        _input = new AInput(input, KEY2);
    else if (_id < 3)
        _input->setInput(input);
    if (_input && (key = _input->getInput()) != NONE)
    {
        i = (this->*_key[key])(trans);
        _anim = 2;
        rotation.y += (i.second) ? (SIGN(i.second) * 90 - 90) : (0);
        rotation.y += (i.first) ? (SIGN(i.first) * -90 + 180) : (0);
        rotate(rotation);
    }
    if (_onBomb() ||
                (_checkMove(
                    i.first,
                    i.second)
                && _checkMove(
                    i.first + 0.4,
                    i.second + 0.4)
                && _checkMove(
                    i.first,
                    i.second + 0.4)
                && _checkMove(
                    i.first + 0.4,
                    i.second)
                ))
            {
                _pos.first += i.first;
                _pos.second += i.second;
                translate(glm::vec3(i.first, 0, i.second));
            }
    if (_anim == 2)
        _anim = 1;
    else
        _anim = 0;
    tmp = _map->getCase(_pos.first, _pos.second);
    if (tmp && tmp->getType() == BONUS)
    {
        static_cast<Bonus*>(tmp)->addToPlayer(this);
        _map->deleteCube(_pos.first, _pos.second);
    }
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

std::pair<float, float>     Player::realPos(std::pair<float, float> pos)
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
}

int   Player::getId() const
{
    return (_id);
}

int   Player::getRange() const
{
    return (_range);
}

void  Player::setRange(int range)
{
    _range = range;
}

void    Player::setLife(int newLife)
{
    _life = newLife;
    if (_life <= 0)
      _isAlive = false;
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

bool    Player::isAlive() const
{
  return (_isAlive);
}