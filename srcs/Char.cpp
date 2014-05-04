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

void	Char::setMap(std::map< std::pair<float, float>, AObject *> &map)
{
  _map = map;
}

float	Char::getTrans()
{
  return (_trans);
}

void Char::update(gdl::Clock const &clock, gdl::Input &input)
{
  _trans = static_cast<float>(clock.getElapsed()) * _speed;
  if (_screen == 1)
    {
      if (input.getKey(SDLK_UP))
	translate(glm::vec3(0, 0, 1) * _trans);
      if (input.getKey(SDLK_DOWN))
	translate(glm::vec3(0, 0, -1) * _trans);
      if (input.getKey(SDLK_LEFT))
	translate(glm::vec3(1, 0, 0) * _trans);
      if (input.getKey(SDLK_RIGHT))
	translate(glm::vec3(-1, 0, 0) * _trans);
    }
  else
    {
      if (input.getKey(SDLK_z))
	translate(glm::vec3(0, 0, 1) * _trans);
      if (input.getKey(SDLK_s))
	    translate(glm::vec3(0, 0, -1) * _trans);
      if (input.getKey(SDLK_q))
	translate(glm::vec3(1, 0, 0) * _trans);
      if (input.getKey(SDLK_d))
	translate(glm::vec3(-1, 0, 0) * _trans);		
    }
  //_model->gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
  //_model->gdl::Model::update(clock.getElapsed());
}

void Char::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
  //gdl::Model::Begin();
  //glPushMatrix();
  //_model->gdl::Model::play("Take 001");
  //glTranslatef(this->position_->x, 0.0f, this->position_->y);
  //glRotatef(this->rotation_->x, 0.0f, 0.0f, 0.0f);
  //_model->gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
  //glPopMatrix();
  // 	gdl::Model::End();
}

bool	Char::initialize()
{
  _speed = 10.0f;
  if (_texture.load("./ressources/assets/char.tga") == false)
    {
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  //_geometry.setColor(glm::vec4(1, 1, 0, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  //_geometry.setColor(glm::vec4(0, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  //_geometry.setColor(glm::vec4(1, 0, 1, 1));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  //_geometry.setColor(glm::vec4(0, 1, 0, 1));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  //_geometry.setColor(glm::vec4(0, 0, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
  return (true);
}
