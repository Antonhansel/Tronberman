/*
** AObject.cpp for AObject in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 16:54:46 2014 Antonin Ribeaud
** Last update Tue Apr  29 16:54:46 2014 Antonin Ribeaud
*/

#include "AObject.hpp"

AObject::AObject() : 
	_position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{

}

AObject::~AObject()
{

}

bool		AObject::initialize()
{}

void		AObject::update(gdl::Clock const &clock, gdl::Input &input)
{
	(void)clock;
	(void)input;
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