/*
** Loading.hpp for Loading in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 11:53:12 2014 Antonin Ribeaud
** Last update Thu May  01 11:53:12 2014 Antonin Ribeaud
*/

#ifndef _Loading_HPP_
# define _Loading_HPP_

#include "AObject.hpp"

class Loading : public AObject
{
public:
	Loading(float width, float height, float speed);
	~Loading();
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

#endif /*!_Loading_HPP_*/