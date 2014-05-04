/*
** AObject.cpp for AObject in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 16:54:46 2014 Antonin Ribeaud
// Last update Sun May  4 03:23:40 2014 Mehdi Chouag
*/

#include "AObject.hpp"

AObject::AObject() : 
	_position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{

}

AObject::~AObject()
{

}

void		AObject::setPos(std::pair<float, float> &pos)
{
  translate(glm::vec3(pos.first, 0, pos.second));
  _pos = pos;
}

std::pair<float, float>	AObject::getPos() const
{
  return (_pos);
}

void 		AObject::translate(glm::vec3 const &v)
{
  _position += v;
}

void		AObject::rotate(glm::vec3 const& axis, float angle)
{
  _rotation += axis * angle;
}

void 		AObject::scale(glm::vec3 const& scale)
{
  _scale *= scale;
}

void		AObject::setType(type Type)
{
  _type = Type;
}

type		AObject::getType() const
{
  return (_type);
}

glm::mat4 	AObject::getTransformation()
{
  glm::mat4 transform(1);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::translate(transform, _position);
  transform = glm::scale(transform, _scale);
  return (transform);
}

float		AObject::getTrans() const
{
  return (_trans);
}

void	AObject::setPlayer(int player)
{
  _players = player; 
}

void	AObject::setScreen(int screen)
{
  _screen = screen;
}

void	AObject::setSpeed(float speed)
{
  _speed = speed;
}

void	AObject::setMap(std::map< std::pair<float, float>, AObject *> &map)
{
  _map = map;
}
