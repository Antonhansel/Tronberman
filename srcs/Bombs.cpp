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
  _ptrFunct[BONUS] = &Bombs::checkBonus;
  _ptrFunct[BOMB] = &Bombs::checkBomb;
  _ptrFunct[BORDER] = &Bombs::checkBlockS;
  _ptrFunct[LASER] = &Bombs::checkLaser;
}

Bombs::~Bombs()
{
}

void Bombs::update(gdl::Clock const &clock, gdl::Input &input)
{
  _time += clock.getElapsed();
  this->bombExplode();
  this->removeExplosion();
}

void  Bombs::draw(gdl::AShader &shader, gdl::Clock const &clock)
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
  /*pos.first = roundf(pos.first - 0.2);
  pos.second = roundf(pos.second - 0.2);*/
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

  for (it2 = _explosion.begin(); it2 != _explosion.end(); )
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

void    Bombs::newBomb(std::pair<float, float> &check)
{
  AObject *bomb;
  std::pair<float, float> pos;

  bomb = create<Bombs>();
  bomb->setType(LASER);
  bomb->initialize();
  _map->addCube(check.first, check.second, bomb);
  for (std::map<int, Player *>::iterator it = _playerTab->begin(); it != _playerTab->end(); ++it)
    {
      if ((*it).second->getShield() > 1.0)
      {
        pos = (*it).second->getPos();
        pos.first = ((int)(pos.first));
        pos.second = ((int)(pos.second));
        if (pos.first == check.first && pos.second == check.second)
        {
          if ((*it).second->getLife() == 0 && (*it).second->isAlive() == true)
          {
            std::cout << "DEAD\n";
            _sound->playSound(DEATH_S, 80);
            if ((*it).second->getId() != _player->getId())
              _player->setScore(_player->getScore() + 1000);
            (*it).second->setScore((*it).second->getScore() - 100);
            std::cout << "Score: " << (*it).second->getScore() << std::endl;
            (*it).second->setIsAlive();
          }
          else if ((*it).second->isAlive() == true)
          {
            _sound->playSound(HIT_S, 10);
            (*it).second->setLife((*it).second->getLife() - 1);
            (*it).second->setScore((*it).second->getScore() - 50);
            _player->setScore(_player->getScore() + 100);
          }
        }
      }
    }
  _explosion.push_back(std::make_pair(_time, bomb));
}

void  Bombs::explosion(std::pair<float, float> pos, int playerId)
{
  std::pair<float, float> check;
  int             range;

  range = _player->getRange();
  check.first = pos.first;
  check.second = pos.second;
  exploseNegY(pos.second - range, check);
  exploseNegX(pos.first - range, check);
  explosePosY(pos.second + range, check);
  explosePosX(pos.first + range, check);
}

void  Bombs::explosePosY(float y, std::pair<float, float> check)
{
  AObject *tmp;
  bool  resume;
  std::pair<float, float> pos;

  resume = true;
  while (check.second - 1 < y && resume == true)
  {
    tmp = _map->getCase(check.first, check.second);
    resume = checkBlock(tmp, check, resume);
    check.second++;
  }
}

void  Bombs::exploseNegY(float y, std::pair<float, float> check)
{
  AObject *tmp;
  bool  resume;
  std::pair<float, float> pos;

  resume = true;
  while (check.second + 1 > y && resume == true)
  {
    tmp = _map->getCase(check.first, check.second);
    resume = checkBlock(tmp, check, resume);
    check.second--;
  }
}

void  Bombs::explosePosX(float y, std::pair<float, float> check)
{
  AObject *tmp;
  bool  resume;
  std::pair<float, float> pos;

  resume = true;
  while (check.first - 1 < y && resume == true)
  {
    tmp = _map->getCase(check.first, check.second);
    resume = checkBlock(tmp, check, resume);
    check.first++;
  }
}

void  Bombs::exploseNegX(float y, std::pair<float, float> check)
{
  AObject *tmp;
  bool  resume;

  resume = true;
  while (check.first + 1 > y && resume == true)
  {
    tmp = _map->getCase(check.first, check.second);
    resume = checkBlock(tmp, check, resume);
    check.first--;
  }
}

int  Bombs::checkBlock(AObject *tmp, std::pair<float, float> check, int resume)
{
  if (tmp)
  {
    resume = (this->*_ptrFunct[tmp->getType()])(resume, check);
  }
  else if (!tmp)
    newBomb(check);
  return (resume);
}

void  Bombs::setObjects(Map *map, Sound *sound, std::map<std::pair<float, float>, Bombs *> *bombsM)
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

void  Bombs::setPlayerTab(std::map<int, Player*> *playerTab)
{
  _playerTab = playerTab;
}

int   Bombs::checkBlockD(int resume, std::pair<float, float> &check)
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
        b->setObject(BONUS, check, _map);
        _bonusM[check] = b;
    }
  }
  resume = false;
  return (resume);
}

int   Bombs::checkBlockS(int resume, std::pair<float, float> &check)
{
  resume = false;
  return (resume);
}

int   Bombs::checkBonus(int resume, std::pair<float, float> &check)
{
  _map->deleteCube(check.first, check.second);
  newBomb(check);
  return (resume);
}

int   Bombs::checkBomb(int resume, std::pair<float, float> &check)
{
  std::map<std::pair<float, float>, Bombs *>::iterator it;

  if ((it = _bombsM->find(check)) != _bombsM->end())
  {
    (*it).second->setExplose();
    resume = false;
  }
  return (resume);
}

int   Bombs::checkLaser(int resume, std::pair<float, float> &check)
{
  /*for (std::map<int, Player *>::iterator it = _playerTab->begin(); it != _playerTab->end(); )
    {
      pos = (*it).second->getPos();
      pos.first = ((int)(pos.first));
      pos.second = ((int)(pos.second));
      std::cout << "pos.first = " << pos.first << " && check.first = " << check.first << std::endl;
      std::cout << "pos.second = " << pos.second << " && check.second = " << check.second << std::endl;
      if (pos.first == check.first && pos.second == check.second)
      {
        std::cout << "TOUCHER\n";
        if ((*it).second->getLife() == 0)
        {
          std::cout << "DEAD\n";
          //_playerTab->erase(it++);
          //it = _playerTab->begin();
          ++it;
        }
        else
        {
         (*it).second->setLife((*it).second->getLife() - 1);
        }
      }
      else
        ++it;
    }*/
    return (resume);
}
