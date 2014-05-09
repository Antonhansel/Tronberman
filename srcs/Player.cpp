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
{}

Player::~Player()
{}

bool    Player::initialize()
{
  _speed = 10.0f;
  _model.load( "./ressources/assets/bomberman_white_run.FBX");
  scale(glm::vec3(1,2,1));
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
  // std::pair<float, float>   pos;
  // AObject                   *obj = NULL;
  
  // if (y < 0)
  //   y -= 1;
  // if (x < 0)
  //   x -= 1;

  // for (int i = 0; i < 4; i++)
  // {
  //   if (i == 0)
  //     pos = std::make_pair((float)((int)(y + 0.6)), (float)((int)(x)));
  //   else if (i == 1)
  //    pos = std::make_pair((float)((int)(y + 0.9)), (float)((int)(x)));
  //   else if (i == 2)
  //     pos = std::make_pair((float)((int)(y + 0.6)), (float)((int)(x + 0.9)));
  //   else if (i == 3)
  //     pos = std::make_pair((float)((int)(y + 0.9)), (float)((int)(x + 0.9)));

  //   if ((*_map).find(pos) != (*_map).end())
  //     obj = (*_map).find(pos)->second;
  //   if (obj != NULL && (obj->getType() == BLOCKD || obj->getType() == BORDER ||
  //       obj->getType() == BOT || obj->getType() == BLOCK))
  //     return (false);
  // }
  return (true);
}


void	Player::update(gdl::Clock const &clock, gdl::Input &input)
{
 _trans = static_cast<float>(clock.getElapsed()) * _speed;
 if (_players == 1)
   {
     if (input.getKey(SDLK_UP) && checkMove(_posy, _posx + (1 * _trans)) == true)
       {
	 _anim = 2;
	 _posx += 1 * _trans;
	 translate(glm::vec3(0, 0, 1) * _trans);
       }
     if (input.getKey(SDLK_DOWN) && checkMove(_posy, _posx + (-1 * _trans)) == true)
       {
	 _anim = 2;
	 _posx += -1 * _trans;
	 translate(glm::vec3(0, 0, -1) * _trans);
       }
     if (input.getKey(SDLK_LEFT) && checkMove(_posy + (1 * _trans), _posx) == true)
       {
	 _anim = 2;
	 _posy += 1 * _trans;
	 translate(glm::vec3(1, 0, 0) * _trans);
       }
     if (input.getKey(SDLK_RIGHT) && checkMove(_posy + (-1 * _trans), _posx) == true)
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
