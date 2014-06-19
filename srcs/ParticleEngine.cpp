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

bool  ParticleEngine::canDraw(std::pair<float, float> playerpos, std::pair<float, float> botpos)
{
  std::pair<float, float> pos;

  if (playerpos.first > botpos.first)
  {
    if (playerpos.second > botpos.second)
    {
      if ((playerpos.first - botpos.first > 30) && (playerpos.second - botpos.second > 30))
        return (false);
    }
    else
    {
      if ((playerpos.first - botpos.first > 30) && (botpos.second - playerpos.second > 30))
        return (false);
    }
  }
  else
  {
    if (playerpos.second > botpos.second)
    {
      if ((botpos.first - playerpos.first > 30 ) && (playerpos.second - botpos.second > 30))
        return (false);
    }
    else
    {
      if ((botpos.first - playerpos.first > 30) && (botpos.second - playerpos.second > 30))
        return (false);
    }
  }
  return (true);
}

void 	ParticleEngine::draw(gdl::AShader &shader, const gdl::Clock &clock, AObject *player)
{
  std::vector<Particles*>::iterator it;
  _loader->bindTexture(BLOCKD);
  for (it = _exploList.begin(); it != _exploList.end(); ++it)
  {
    if (canDraw(player->getPos(), (*it)->getPos()))
      (*it)->draw(shader);
  }
}

void  ParticleEngine::spawnParticles(glm::vec3 &vec)
{
  Particles *part = new Particles(_loader, vec);
  _exploList.push_back(part);
}

void 	ParticleEngine::update()
{
  std::vector<Particles*>::iterator it;
  for (it = _exploList.begin(); it != _exploList.end();)
  {
    if ((*it)->getFuel() > 0)
      (*it++)->update();
    else
      it = _exploList.erase(it);
  }
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
