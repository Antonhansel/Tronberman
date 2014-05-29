/*
** ParticleEngine.cpp for ParticleEngine in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon May  26 15:49:08 2014 Antonin Ribeaud
** Last update Mon May  26 15:49:08 2014 Antonin Ribeaud
*/

#include "ParticleEngine.hpp"
#include <sstream> 
#include <iostream>

ParticleEngine::ParticleEngine(Loader *loader)
{
  _loader = loader;
}

ParticleEngine::~ParticleEngine()
{}

void 	ParticleEngine::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  std::vector<Particles*>::iterator it;
  _loader->bindTexture(BLOCKD);
  for (it = _exploList.begin(); it != _exploList.end(); ++it)
  {
    (*it)->draw(shader);
  }
}

void  ParticleEngine::spawnParticles(glm::vec3 &vec)
{
  Particles *part = new Particles(_loader, vec);
  _exploList.push_back(part);
}

void 	ParticleEngine::update(gdl::Clock const &clock, gdl::Input &input)
{
  std::vector<Particles*>::iterator it;
  for (it = _exploList.begin(); it != _exploList.end(); ++it)
  {
    if ((*it)->getFuel() > 0)
      (*it)->update();
  }
  //cleanParticles();
}

void  ParticleEngine::cleanParticles()
{
  std::vector<Particles*>::iterator it;
  for (it = _exploList.begin(); it != _exploList.end(); ++it)
  {
    if ((*it)->getFuel() <= 0)
    {
      delete (*it);
      _exploList.erase(it);
    }
  }  
}
