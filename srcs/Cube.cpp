/*
** Cube.cpp for Cube in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 16:48:25 2014 Antonin Ribeaud
// Last update Sun May  4 03:21:07 2014 Mehdi Chouag
*/

#include "Cube.hpp"

Cube::Cube()
{
	_particles = NULL;
}

Cube::~Cube()
{
	if (_particles != NULL)
		_particles->spawnParticles(_position);
}

void Cube::update(gdl::Clock const &clock, gdl::Input &input)
{

}

void Cube::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
}

bool	Cube::initialize()
{
  return (true);
}
