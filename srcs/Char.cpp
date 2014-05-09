/*
** Char.cpp for char in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 21:11:55 2014 Antonin Ribeaud
// Last update Wed May  7 19:13:50 2014 ribeaud antonin
*/

#include "Char.hpp"
#include <iostream>

#include "Core.hpp"

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

//   inputmap1[SDLK_UP] = &Core::moveUp;
//   inputmap1[SDLK_DOWN] = &Core::moveDown;
//   inputmap1[SDLK_LEFT] = &Core::moveLeft;
//   inputmap1[SDLK_RIGHT] = &Core::moveUp;
//   inputmap2[SDLK_z] = &Core::moveUp;
//   inputmap2[SDLK_s] = &Core::moveDown;
//   inputmap2[SDLK_q] = &Core::moveLeft;
//   inputmap2[SDLK_d] = &Core::moveRight;
// }

// void  Core::changeFocus2(AObject *cur_char)
// {
//   cur_char->update(_clock, _input);
//   if (_input.getKey(SDLK_z))
//     _posx2 += cur_char->getTrans();
//   if (_input.getKey(SDLK_s))
//     _posx2 -= cur_char->getTrans();
//   if (_input.getKey(SDLK_q))
//     _posy2 += cur_char->getTrans();
//   if (_input.getKey(SDLK_d))
//     _posy2 -= cur_char->getTrans();
//   _cam->moveCamera(glm::vec3(_posy2, 13, -10 + _posx2), 
//          glm::vec3(_posy2, 0, _posx2), glm::vec3(0, 1, 0), 2);
// }

// void  Core::changeFocus(AObject *cur_char)
// {
  
// }

// void  Core::moveUp(AObject *cur_char, int &posx, int &posy, int screen)
// {
//   cur_char->update(_clock, _input);
//   posx += cur_char->getTrans();
//   _cam->moveCamera(glm::vec3(posy, 13, -10 + posx), 
//          glm::vec3(posy, 0, posx), glm::vec3(0, 1, 0), screen);
// }

// void  Core::moveDown(AObject *cur_char, int &posx, int &posy, int screen)
// {
//   cur_char->update(_clock, _input);
//   posx -= cur_char->getTrans();
//   _cam->moveCamera(glm::vec3(posy, 13, -10 + posx), 
//          glm::vec3(posy, 0, posx), glm::vec3(0, 1, 0), screen);
// }

// void  Core::moveLeft(AObject *cur_char, int &posx, int &posy, int screen)
// {
//   cur_char->update(_clock, _input);
//   posy += cur_char->getTrans();
//   _cam->moveCamera(glm::vec3(posy, 13, -10 + posx), 
//          glm::vec3(posy, 0, posx), glm::vec3(0, 1, 0), screen);
// }

// void  Core::moveRight(AObject *cur_char, int &posx, int &posy, int screen)
// {
//   cur_char->update(_clock, _input);
//   posy -= cur_char->getTrans();
//   _cam->moveCamera(glm::vec3(posy, 13, -10 + posx), 
//          glm::vec3(posy, 0, posx), glm::vec3(0, 1, 0), screen);
// }

