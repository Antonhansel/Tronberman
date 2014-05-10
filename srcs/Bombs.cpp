/*
** Bombs.cpp for Bombs in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Sat May  10 02:44:49 2014 Antonin Ribeaud
** Last update Sat May  10 02:44:49 2014 Antonin Ribeaud
*/

#include "Bombs.hpp"

Bombs::Bombs()
{
  initialize();
}

Bombs::~Bombs()
{}

void Bombs::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void  Bombs::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
}

bool	Bombs::initialize()
{
  scale(glm::vec3(0.9, 0.9, 0.9));
  _speed = 10.0f;
  return (true);
}