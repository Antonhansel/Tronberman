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
}

Cube::~Cube()
{

}

void Cube::update(gdl::Clock const &clock, gdl::Input &input)
{
	// if (input.getKey(SDLK_UP))
	// 	translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
	// if (input.getKey(SDLK_DOWN))
	// 	translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
	// if (input.getKey(SDLK_LEFT))
	// 	translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
	// if (input.getKey(SDLK_RIGHT))
	// 	translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}

void Cube::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
}

bool	Cube::initialize()
{
  _speed = 10.0f;
  return (true);
}
