/*
** Cube.hpp for Cube in /home/apollo/rendu/bestbomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 16:47:20 2014 Antonin Ribeaud
// Last update Sat May  3 22:56:31 2014 Mehdi Chouag
*/

#ifndef _CUBE_HPP_
# define _CUBE_HPP_

# include "AObject.hpp"

class Cube : public AObject
{
private:
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  float		_speed;
  type		_type;
public:
	Cube();
	~Cube();
	void update(gdl::Clock const &clock, gdl::Input &input);
	bool initialize();
	void draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif /*!CUBE_HPP_*/
