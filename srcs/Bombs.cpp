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
	_time = 0;
	initialize();
}

Bombs::~Bombs()
{}

void Bombs::update(gdl::Clock const &clock, gdl::Input &input)
{
	 _time += clock.getElapsed();
	 //std::cout << "MAJ\n";
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

bool  Bombs::makeBomb(Player *player)
{
  std::pair<float, float> pos;

  pos = player->getPos();
  pos.first = floor(pos.first);
  pos.second = floor(pos.second);
  if (_map->getCase(pos.first, pos.second) == NULL)
  {
    if (player != NULL && player->getStock() >= 1)
    {
      AObject *bomb = create<Bombs>();
      bomb->setType(BOMB);
      bomb->initialize();
      _map->addCube(pos.first, pos.second, bomb);
      //std::cout << "_bombs addr: " << _bombs << std::endl;
      _bombs.push_back(bomb);
      _player = player;
      _create = _time;
      //_bombs[_time] = std::make_pair(player->getId(), bomb);
      _player->setStock(_player->getStock() - 1);
    }
  }
  return (true);
}

void  Bombs::removeExplosion()
{
  std::vector< std::pair<double, AObject*> >::iterator it2;
  std::pair<float, float>     pos;

  for (it2 = _explosion.begin(); it2 != _explosion.end(); )
  {
    if (_time - (*it2).first > 0.5)
    {
      pos = (*it2).second->getPos();
      _map->deleteCube(pos.first, pos.second);
      it2 = _explosion.erase((it2));
    }
    else
      ++it2;
  }
}

void  Bombs::bombExplode()
{
  std::vector<AObject *>::iterator it2;
  std::pair<int, int> pos;
  //int                     playerId;

  for (it2 = _bombs.begin(); it2 != _bombs.end(); )
  {
    if (_time - _create > 2.0)
    {
      pos = (*it2)->getPos();
      _player->setStock(_player->getStock() + 1);
      pos = (*it2)->getPos();
      _map->deleteCube(pos.first, pos.second);
      it2 = _bombs.erase(it2);
      explosion(pos, _player->getId());
      _sound->playSound(BOMB_S, 100);
    }
    else
      ++it2;
  }
}

void		Bombs::newBomb(std::pair<float, float> &check)
{
  AObject	*bomb;

  bomb = create<Bombs>();
  bomb->setType(LASER);
  bomb->initialize();
  _map->addCube(check.first, check.second, bomb);
  _explosion.push_back(std::make_pair(_time, bomb));
}

void	Bombs::explosion(std::pair<float, float> pos, int playerId)
{
  AObject *tmp;
  std::map< std::pair<float, float>, AObject * >::iterator it;
  std::pair<float, float>	check;
  int 						range;

  range = _player->getRange();
  check.first = pos.first;
  check.second = pos.second - range;
  while (check.second - 1 < pos.second + range)
  {
    tmp = _map->getCase(check.first, check.second);
    if (tmp && tmp->getType() == BLOCKD)
    {
      _map->deleteCube(check.first, check.second);
      newBomb(check);
    }
    else if (!tmp)
      newBomb(check);
    check.second++;
  }
  check.first = pos.first - range;
  check.second = pos.second;
  while (check.first - 1 < pos.first + range)
  {
    tmp = _map->getCase(check.first, check.second);
    if (tmp && tmp->getType() == BLOCKD)
    {
      _map->deleteCube(check.first, check.second);
      newBomb(check);
    }
    else if (!tmp)
      newBomb(check);
    check.first++;
  }
}

void	Bombs::setObjects(Map *map, Sound *sound)
{
	_map = map;
	_sound = sound;
}