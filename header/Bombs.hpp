/*
** Bombs.hpp for Bombs in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Sat May  10 02:45:01 2014 Antonin Ribeaud
** Last update Sat May  10 02:45:01 2014 Antonin Ribeaud
*/

#ifndef BOMBS_HPP_
# define BOMBS_HPP_

# include "AObject.hpp"

class Bombs : public AObject
{
private:
  	float		_speed;
  	gdl::Model 	_model;
  	type		_type;
  	int			_anim;
public:
	Bombs();
	~Bombs();

	/* data */
	bool 	exploded(gdl::Clock const &clock, gdl::Input &input);
	bool	initialize();
	void	draw(gdl::AShader &shader, gdl::Clock const &clock);
	void	update(gdl::Clock const &clock, gdl::Input &input);
};

#endif