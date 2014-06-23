/*
** Background.hpp for background in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 11:53:12 2014 Antonin Ribeaud
** Last update Thu May  01 11:53:12 2014 Antonin Ribeaud
*/

#ifndef _BACKGROUND_HPP_
# define _BACKGROUND_HPP_

#include "AObject.hpp"

class Background : public AObject
{
public:
	Background(const float, const float, const float);
	~Background();
	bool		initialize();
	void		update(gdl::Clock const &clock, gdl::Input &input);
	void		draw(gdl::AShader &shader, gdl::Clock const &clock);
private:
	gdl::Geometry	_geometry;
	gdl::Texture	_texture;
	float			_speed;
	float			_width;
	float			_height;
	bool 			_dir;
	float 			_spin;
	float 			_x;
	float 			_z;
};

#endif /*!_BACKGROUND_HPP_*/