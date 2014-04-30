/*
** Floor.hpp for Floor in /home/apollo/rendu/bestbomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 18:53:14 2014 Antonin Ribeaud
** Last update Tue Apr  29 18:53:14 2014 Antonin Ribeaud
*/

#ifndef _FLOOR_HPP_
# define _FLOOR_HPP_

#include "AObject.hpp"

class Floor : public AObject
{
public:
	Floor(float width, float height, float speed);
	~Floor();
	bool		initialize();
	void		update(gdl::Clock const &clock, gdl::Input &input);
	void		draw(gdl::AShader &shader, gdl::Clock const &clock);
private:
	gdl::Geometry	_geometry;
	gdl::Texture	_texture;
	float			_speed;
	float			_width;
	float			_height;
};

#endif /*!_FLOOR_HPP_*/