/*
** Char.cpp for char in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 21:11:55 2014 Antonin Ribeaud
// Last update Sun May  4 02:55:08 2014 Mehdi Chouag
*/

#include "Char.hpp"
#include <iostream>

Char::Char()
{
  _speed = 10.0f;
  _map = NULL;
  _anim = 0;
}

Char::~Char()
{}

void	Char::setPlayer(int player)
{
  _players = player; 
}

void	Char::setScreen(int screen)
{
  _screen = screen;
}

void	Char::setSpeed(float speed)
{
  _speed = speed;
}

void	Char::setMap(std::map< std::pair<float, float>, AObject *> *map)
{
  _map = map;
}

void  Char::setBombs(std::map< std::pair<float, float>, AObject* > &bombs)
{
  _bombs = bombs;
}

float	Char::getTrans()
{
  return (_trans);
}

bool  Char::checkMove(float y, float x)
{
  std::pair<float, float>   pos1;
  std::pair<float, float>   pos2;
  std::pair<float, float>   pos3;
  std::pair<float, float>   pos4;
  AObject                   *obj1 = NULL;
  AObject                   *obj2 = NULL;
  AObject                   *obj3 = NULL;
  AObject                   *obj4 = NULL;
  bool                      error = true;

if (y < 0) 
  y -= 1;
if (x < 0)
  x -= 1;

  pos1 = std::make_pair((float)((int)(y + 0.4)), (float)((int)(x)));
  pos2 = std::make_pair((float)((int)(y + 0.9)), (float)((int)(x)));
  pos3 = std::make_pair((float)((int)(y + 0.4)), (float)((int)(x + 0.9)));
  pos4 = std::make_pair((float)((int)(y + 0.9)), (float)((int)(x + 0.9)));

  if ((*_map).find(pos1) != (*_map).end())
    obj1 = (*_map).find(pos1)->second;
  if ((*_map).find(pos2) != (*_map).end())
    obj2 = (*_map).find(pos2)->second;
  if ((*_map).find(pos3) != (*_map).end())
    obj3 = (*_map).find(pos3)->second;
  if ((*_map).find(pos4) != (*_map).end())
    obj4 = (*_map).find(pos4)->second;

  if (obj1 != NULL && (obj1->getType() == BLOCKD || obj1->getType() == BORDER || obj1->getType() == BOT))
    error = false;
  if (obj2 != NULL && (obj2->getType() == BLOCKD || obj2->getType() == BORDER || obj2->getType() == BOT))
    error = false;
  if (obj3 != NULL && (obj3->getType() == BLOCKD || obj3->getType() == BORDER || obj3->getType() == BOT))
    error = false;
  if (obj4 != NULL && (obj4->getType() == BLOCKD || obj4->getType() == BORDER || obj4->getType() == BOT))
      error = false;
  if (error == false)
    _trans = 0;
  return (error);
}

void  Char::checkBombs()
{
  std::pair<float, float> bpos(_posy, _posx);
        //pos = std::make_pair(_posy, _posx);
  _bombs[bpos] = new Bombs();
  _bombs[bpos]->translate(glm::vec3(_posy, 0, _posx + 1) * _trans);
  //std::cout << "posY : " << _bombs[bpos]->_posy << " && posX : " << _bombs[bpos]->_posx << std::endl;
}

void Char::update(gdl::Clock const &clock, gdl::Input &input)
{
 _trans = static_cast<float>(clock.getElapsed()) * _speed;
  if ((input.getKey(SDLK_UP) || input.getKey(SDLK_z)) && checkMove(_posy, _posx + (1 * _trans)) == true)
  {
      _anim = 2;
    _posx += 1 * _trans;
    translate(glm::vec3(0, 0, 1) * _trans);
  }
  if ((input.getKey(SDLK_DOWN) || input.getKey(SDLK_s)) && checkMove(_posy, _posx + (-1 * _trans)) == true)
  {
      _anim = 2;
    _posx += -1 * _trans;
    translate(glm::vec3(0, 0, -1) * _trans);
  }
  if ((input.getKey(SDLK_LEFT) || input.getKey(SDLK_q)) && checkMove(_posy + (1 * _trans), _posx) == true)
  {
      _anim = 2;
    _posy += 1 * _trans;
    translate(glm::vec3(1, 0, 0) * _trans);
  }
  if ((input.getKey(SDLK_RIGHT) || input.getKey(SDLK_d)) && checkMove(_posy + (-1 * _trans), _posx) == true)
  {
      _anim = 2;
    _posy += -1 * _trans;
     translate(glm::vec3(-1, 0, 0) * _trans);
  }
  if (_anim == 2)
    _anim = 1;
  else
    _anim = 0;
}

void Char::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  // (void)clock;
  // _texture.bind();
  // _geometry.draw(shader, getTransformation(), GL_QUADS);
  glPushMatrix();
  _model.setCurrentAnim(_anim);
  // glTranslatef(this->position_->z, 0.0f, this->position_->x);
  //glRotatef(_rotation.y, 0.0f, 0.0f, 10.0f);
  _model.gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
  glPopMatrix();
}

bool	Char::initialize()
{
  _speed = 10.0f;
  _model.load( "./ressources/assets/bomberman_white_run.FBX");
  scale(glm::vec3(1,2,1));
  return (true);
}
