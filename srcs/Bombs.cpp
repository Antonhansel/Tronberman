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
  _isExplosed = false;
  _explosed = false;
  _doBonus = false;
  initialize();
  _ptrFunct[BLOCKD] = &Bombs::checkBlockD;
  _ptrFunct[BLOCK] = &Bombs::checkBlockS;
  _ptrFunct[BONUSV] = &Bombs::checkBonus;
  _ptrFunct[BONUSB] = &Bombs::checkBonus;
  _ptrFunct[BONUSR] = &Bombs::checkBonus;
  _ptrFunct[BONUSS] = &Bombs::checkBonus;
  _ptrFunct[BOMB] = &Bombs::checkBomb;
  _ptrFunct[BORDER] = &Bombs::checkBlockS;
  _ptrFunct[LASER] = &Bombs::checkLaser;
}

Bombs::~Bombs()
{
}

void Bombs::update(const gdl::Clock &clock, gdl::Input &input)
{
  _time += clock.getElapsed();
  this->bombExplode();
  this->removeExplosion();
}

void  Bombs::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  (void)clock;
}

bool  Bombs::initialize()
{
  scale(glm::vec3(0.9, 0.9, 0.9));
  _speed = 10.0f;
  return (true);
}

bool  Bombs::makeBomb(Player *player)
{
  std::pair<float, float> pos;

  pos = player->realPos(player->getPos());
  if (_map->getCase(pos.first, pos.second) == NULL)
  {
    if (player != NULL && player->getStock() >= 1)
    {
      AObject *bomb = create<Bombs>();
      bomb->setType(BOMB);
      bomb->initialize();
      _map->addCube(pos.first, pos.second, bomb);
      _bombs.push_back(bomb);
      _player = player;
      _create = _time;
      _player->setStock(_player->getStock() - 1);
    }
  }
  return (true);
}

void  Bombs::removeExplosion()
{
  std::vector< std::pair<double, AObject*> >::iterator it2;
  std::pair<float, float>     pos;

  for (it2 = _explosion.begin(); it2 != _explosion.end();)
  {
    if (_time - (*it2).first > 0.2)
    {
      _isExplosed = true;
      pos = (*it2).second->getPos();
      _map->deleteCube(pos.first, pos.second);
      it2 = _explosion.erase((it2));
    }
    else
      ++it2;
  }
  if (_doBonus == false && _isExplosed == true)
    {
      for (std::map<std::pair<float, float>, Bonus *>::iterator it = _bonusM.begin(); it != _bonusM.end(); ++it)
      {
        (*it).second->throwBonus();
      }
      _doBonus = true;
    }
}

void  Bombs::bombExplode()
{
  std::vector<AObject *>::iterator it2;
  std::pair<int, int> pos;

  for (it2 = _bombs.begin(); it2 != _bombs.end(); )
  {
    if (_time - _create > 2.0 || _explosed == true)
    {
      _player->setStock(_player->getStock() + 1);
      pos = (*it2)->getPos();
      _map->deleteCube(pos.first, pos.second);
      it2 = _bombs.erase(it2);
      explosion(pos);
      _sound->playSound(BOMB_S, 100);
    }
    else
      ++it2;
  }
}

void    Bombs::newBomb(const std::pair<float, float> &check)
{
  AObject *bomb;
  std::pair<float, float> pos;

  bomb = create<Bombs>();
  bomb->setType(LASER);
  bomb->initialize();
  _map->addCube(check.first, check.second, bomb);
  for (std::vector<Player *>::iterator it = _playerTab->begin(); it != _playerTab->end(); ++it)
    {
      if ((*it) && (*it)->getShield() > 1)
      {
        pos = (*it)->getPos();
        pos.first = ((int)(pos.first + 0.5));
        pos.second = ((int)(pos.second + 0.5));
        if (pos.first == check.first && pos.second == check.second)
        {
          if ((*it)->getLife() == 0 && (*it)->isAlive() == true)
          {
            std::cout << "DEAD\n";
            _sound->playSound(DEATH_S, 80);
            if ((*it)->getId() != _player->getId())
              _player->setScore(_player->getScore() + 1000);
            (*it)->setScore((*it)->getScore() - 100);
            std::cout << "Score: " << (*it)->getScore() << std::endl;
            (*it)->setIsAlive();
          }
          else if ((*it)->isAlive() == true)
          {
            _sound->playSound(HIT_S, 10);
            (*it)->setLife((*it)->getLife() - 1);
            (*it)->setScore((*it)->getScore() - 50);
            _player->setScore(_player->getScore() + 100);
          }
        }
      }
    }
  _explosion.push_back(std::make_pair(_time, bomb));
}

void  Bombs::explosion(const std::pair<float, float> &pos)
{
  int             range;

  range = _player->getRange();
  exploseAll(range, pos, 1, 0);
  exploseAll(range, pos, -1, 0);
  exploseAll(range, pos, 0, 1);
  exploseAll(range, pos, 0, -1);
}

void  Bombs::exploseAll(const int range, const std::pair<float, float> &check, const int x, const int y)
{
  AObject *tmp;
  bool  resume;

  resume = true;
  for (int r = 0; r <= range && resume; r++)
  {
    tmp = _map->getCase(check.first + (x * r), check.second + (y * r));
    resume = checkBlock(tmp, std::make_pair(check.first + (x * r), check.second + (y * r)), resume);
  }
}

int  Bombs::checkBlock(AObject *tmp, const std::pair<float, float> &check, int resume)
{
  if (tmp)
  {
    resume = (this->*_ptrFunct[tmp->getType()])(resume, check);
  }
  else if (!tmp)
    newBomb(check);
  return (resume);
}

void  Bombs::setObjects(Map *map, Sound *sound, std::map<std::pair<float, float> , Bombs *> *bombsM)
{
  _map = map;
  _sound = sound;
  _bombsM = bombsM;
}

bool  Bombs::isExplosed() const
{
  return (_isExplosed);
}

void  Bombs::setExplose()
{
  if (isExplosed() == false)
    _explosed = true;
}

void  Bombs::setPlayerTab(std::vector<Player*> *playerTab)
{
  _playerTab = playerTab;
}

int   Bombs::checkBlockD(int resume, const std::pair<float, float> &check)
{
  int   res;
  _map->deleteCube(check.first, check.second);
  newBomb(check);
  res = rand() % 1000;
  if (_player->getBegin() == false || res % 2 == 0)
  {
    if (_player->getBegin() == false)
      _player->setBegin(true);
    if (_bonusM.find(check) == _bonusM.end())
    {
        Bonus *b = create<Bonus>();
        b->setObject(check, _map);
        _bonusM[check] = b;
    }
  }
  resume = false;
  return (resume);
}

int   Bombs::checkBlockS(int resume, const std::pair<float, float> &check)
{
  resume = false;
  return (resume);
}

int   Bombs::checkBonus(int resume, const std::pair<float, float> &check)
{
  _map->deleteCube(check.first, check.second);
  newBomb(check);
  return (resume);
}

int   Bombs::checkBomb(int resume, const std::pair<float, float> &check)
{
  std::map<std::pair<float, float>, Bombs *>::const_iterator it;

  if ((it = _bombsM->find(check)) != _bombsM->end())
  {
    (*it).second->setExplose();
    resume = false;
  }
  return (resume);
}

int   Bombs::checkLaser(int resume, const std::pair<float, float> &check)
{
    (void)check;
    return (resume);
}
