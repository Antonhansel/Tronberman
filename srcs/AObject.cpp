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
  _isAlive = true;
  _transformationDirty = true;
}

AObject::~AObject()
{

}

void		AObject::setPos(std::pair<float, float> &pos)
{
  if (pos.first != 0 || pos.second != 0)
    translate(glm::vec3(pos.first, 0, pos.second));
  _pos = pos;
  _posy = pos.first;
  _posx = pos.second;
}

std::pair<float, float>	AObject::getPos() const
{
  return (_pos);
}

void 		AObject::translate(glm::vec3 const &v)
{
  _transformationDirty = true;
  _position += v;
}

void		AObject::rotate(glm::vec3 const& rotation)
{
  if (rotation == _rotation)
    return;
  _transformationDirty = true;
  _rotation = rotation;
}

void 		AObject::scale(glm::vec3 const& scale)
{
  _transformationDirty = true;
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
  if (_transformationDirty)
  {
    _transformation = glm::translate(glm::mat4(1), _position);
    _transformation = glm::scale(_transformation, _scale);
    _transformation = glm::translate(_transformation, glm::vec3(0.3, 0, -0.3));
    if (_rotation.x)
      _transformation = glm::rotate(_transformation, _rotation.x, glm::vec3(1, 0, 0));
    if (_rotation.y)
      _transformation = glm::rotate(_transformation, _rotation.y, glm::vec3(0, 1, 0));
    if (_rotation.z)
      _transformation = glm::rotate(_transformation, _rotation.z, glm::vec3(0, 0, 1));
    _transformation = glm::translate(_transformation, glm::vec3(-0.3, 0, 0.3));
    _transformationDirty = false;
  }
  return (_transformation);
}

float		AObject::getTrans() const
{
  return (_trans);
}

void	AObject::setPlayer(int player)
{
  _players = player;
}

void	AObject::setSpeed(float speed)
{
  _speed = speed;
}

void	AObject::setMap(Map *map)
{
  _map = map;
}

void  AObject::setBombs(std::map< std::pair<float, float>, AObject* > &bombs)
{
  _bombs = bombs;
}

const std::map< std::pair<float, float>, AObject* >&  AObject::getBombs()
{
  return (_bombs);
}

void AObject::setTexture(gdl::Texture *texture)
{
  _texture = texture;
}


void  AObject::setIsAlive(bool isAlive)
{
  _isAlive = isAlive;
}

bool  AObject::getIsAlive() const
{
  return (_isAlive);
}
