/*
** Char.hpp for char in /home/apollo/rendu/bestbomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 21:10:54 2014 Antonin Ribeaud
** Last update Tue Apr  29 21:10:54 2014 Antonin Ribeaud
*/

#ifndef _CHAR_HPP_
# define _CHAR_HPP_

# include "AObject.hpp"

class Char : public AObject
{
private:
	gdl::Texture	_texture;
	gdl::Geometry	_geometry;
	float			_speed;
public:
	Char();
	~Char();
	void update(gdl::Clock const &clock, gdl::Input &input);
	bool initialize();
	void draw(gdl::AShader &shader, gdl::Clock const &clock);	
	float			getTrans();
};

#endif /*!_CHAR_HPP_*/