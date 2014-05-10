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

Player::Player()
{
  _stock = 3;
  _range = 2;
}

Player::~Player()
{}

bool    Player::initialize()
{
  _speed = 7.0f;
  //_model.load( "./ressources/assets/marvin.fbx");
  _model.load( "./ressources/assets/bomberman_white_run.FBX");
  scale(glm::vec3(1,2,1));
  //scale(glm::vec3(0.002,0.002,0.002));
  return (true);
}

void	Player::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  glPushMatrix();
  _model.setCurrentAnim(_anim);
  _model.gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
  glPopMatrix();
}

void    Player::setPlayer(int player)
{
  _players = player; 
}

void    Player::setScreen(int screen)
{
  _screen = screen;
}

void    Player::setSpeed(float speed)
{
  _speed = speed;
}

float   Player::getTrans()
{
  return (_trans);
}

bool	Player::checkMove(float y, float x)
{
  float temp1;
  float temp2;

  std::pair<float, float> pos;
  pos.first = y;
  pos.second = x;
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
  if (_map->find(pos) == (_map->end()))
    return (true);
  else
    return (false);
}


void	Player::update(gdl::Clock const &clock, gdl::Input &input)
{
 _trans = static_cast<float>(clock.getElapsed()) * _speed;
 if (_players == 1)
   {
     if (input.getKey(SDLK_UP) && checkMove(_posy, _posx + (_trans -0.2)) == true)
       {
  	 _anim = 2;
  	 _posx += 1 * _trans;
  	 translate(glm::vec3(0, 0, 1) * _trans);
       }
     if (input.getKey(SDLK_DOWN) && checkMove(_posy, _posx + (-1 * (_trans+0.3))) == true)
       {
  	 _anim = 2;
  	 _posx += -1 * _trans;
  	 translate(glm::vec3(0, 0, -1) * _trans);
       }
     if (input.getKey(SDLK_LEFT) && checkMove(_posy + (_trans +0.2), _posx) == true)
       {
  	 _anim = 2;
  	 _posy += 1 * _trans;
  	 translate(glm::vec3(1, 0, 0) * _trans);
       }
     if (input.getKey(SDLK_RIGHT) && checkMove(_posy + (-1 * (_trans - 0.2)), _posx) == true)
       {
  	 _anim = 2;
  	 _posy += -1 * _trans;
  	 translate(glm::vec3(-1, 0, 0) * _trans);
       }
   }
 else
   {
     if (input.getKey(SDLK_z) && checkMove(_posy, _posx + (1 * _trans)) == true)
       {
	   _anim = 2;
	   _posx += 1 * _trans;
	   translate(glm::vec3(0, 0, 1) * _trans);
       }
     if (input.getKey(SDLK_s) && checkMove(_posy, _posx + (-1 * _trans)) == true)
       {
	 _anim = 2;
	 _posx += -1 * _trans;
	 translate(glm::vec3(0, 0, -1) * _trans);
       }
     if (input.getKey(SDLK_q) && checkMove(_posy + (1 * _trans), _posx) == true)
       {
	 _anim = 2;
	 _posy += 1 * _trans;
	 translate(glm::vec3(1, 0, 0) * _trans);
       }
     if (input.getKey(SDLK_d) && checkMove(_posy + (-1 * _trans), _posx) == true)
       {
	 _anim = 2;
	 _posy += -1 * _trans;
	 translate(glm::vec3(-1, 0, 0) * _trans);
       }
   }
  if (_anim == 2)
    _anim = 1;
  else
    _anim = 0;
  _pos.first = _posy;
  _pos.second = _posx;
}

int  Player::getStock() const
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