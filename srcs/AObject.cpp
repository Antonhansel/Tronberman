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
# include "ParticleEngine.hpp"


AObject::AObject() :
	_position(), _rotation(), _scale(1, 1, 1)
{
  _transformationDirty = true;
  _particles = NULL;
}

AObject::~AObject()
{}

void    AObject::setPos(const std::pair<float, float> &pos)
{
  _position += glm::vec3(pos.first, 0, pos.second);
  _pos.first += pos.first;
  _pos.second += pos.second;
  _transformationDirty = true;
}

void    AObject::setAbsPos(const std::pair<float, float> &pos)
{
  _position = glm::vec3(pos.first, 0, pos.second);
  _pos.first = pos.first;
  _pos.second = pos.second;
  _transformationDirty = true;
}

void    AObject::setAbsPos(float x, float y)
{
  _position = glm::vec3(x, 0, y);
  _pos.first = x;
  _pos.second = y;
  _transformationDirty = true;
}

std::pair<float, float>	AObject::getPos() const
{
  return (std::make_pair<float, float>(_position.x, _position.z));
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

void  AObject::setParticle(ParticleEngine *particles)
{
    _particles = particles;
}

glm::mat4 	AObject::getTransformation()
{
  if (_transformationDirty)
  {
    _transformation = glm::translate(glm::mat4(), _position);
    _transformation = glm::scale(_transformation, _scale);
    if (_rotation.x)
      _transformation = glm::rotate(_transformation, _rotation.x, glm::vec3(1, 0, 0));
    if (_rotation.y)
      _transformation = glm::rotate(_transformation, _rotation.y, glm::vec3(0, 1, 0));
    if (_rotation.z)
      _transformation = glm::rotate(_transformation, _rotation.z, glm::vec3(0, 0, 1));
    _transformationDirty = false;
  }
  return (_transformation);
}

void    AObject::setTexture(gdl::Texture *texture)
{
  _texture = texture;
}
