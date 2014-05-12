/*
** Core.cpp for core in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 16:31:08 2014 Antonin Ribeaud
// Last update Sun May 11 00:12:10 2014 Mehdi Chouag
*/

#include "Core.hpp"
#include <unistd.h>

Core::Core(Camera *cam, Loader *loader)
{
  std::vector<std::pair<int, int> >    obj;

  _width = 1000;
  _height = 1000;
  _loader = loader;
  _cam = cam;
  _players = 1;
  _map = new Map(_width, _height);
  _sound = new Sound();
  obj = _map->setSpawn(1);
  _posx = obj.begin()->first;
  _posy = obj.begin()->second;
  _posx2 = POSX1;
  _posy2 = POSY1;
  _percent = 15;
  _time = 0;
}

Core::~Core()
{
  std::map< std::pair<float, float>, AObject *>::iterator it;

  delete _map;
  delete _sound;
}

bool	Core::initialize()
{
  _shader = _cam->getShader();
  _clock = _cam->getClock();
  if (drawFloor() == false)
    return (false);
  if (drawChar() == false)
    return (false);
  if (drawBackground() == false)
    return (false);
  if (_players == 2 && _width <= 10 && _height <= 10)
  {
    _screen = 1;
    _cam->setPlayer(1);
  }
  else
  {
    _screen = 0;
    _cam->setPlayer(_players);
  }

  std::cout << "Load done!" << std::endl;
  for (size_t i = 0; i < _loading.size(); ++i)
    delete _loading[i];
  return (true);
}

bool 	Core::drawBackground()
{
  AObject	*background = new Background(_width * 4, _height * 4, 10.0f);

  _other.push_back(background);
  return (background->initialize());
}

bool	Core::drawFloor()
{
  AObject	*floor = new Floor(_width, _height, 10.0f);

  _other.push_back(floor);
  return (floor->initialize());
}

bool   Core::makeChar(int posx, int posy, int screen)
{
  Player *chara = create<Char>();
  std::pair<float, float> pos;

  if (chara->initialize() == false)
    return (false);
  pos = std::make_pair(posx, posy);
  chara->setPos(pos);
  chara->setPlayer(screen);
  chara->setMap(_map);
  chara->setId(screen);
  _player[screen] = chara;
  return (true);
}

bool		Core::drawChar()
{
  if (makeChar(_posx, _posy, 1) == false)
    return (false);
  if (_players == 2)
  {
    if (makeChar(_posx2, _posy2, 2) == false)
      return (false);
  }
  return (true);
}

bool  Core::makeBomb(Player *player)
{
  std::pair<float, float> pos;

  pos = player->getPos();
  pos.first = floor(pos.first);
  pos.second = floor(pos.second);
  if (_map->getCase(pos.first, pos.second) == NULL)
  {
    if (player->getStock() >= 1)
    {
      AObject *bomb = create<Bombs>();
      bomb->setType(BOMB);
      bomb->initialize();
      _map->addCube(pos.first, pos.second, bomb);
      _bombs[_time] = std::make_pair(player->getId(), bomb);
      player->setStock(player->getStock() - 1);
    }
  }
  return (true);
}

void  Core::removeExplosion()
{
  std::vector< std::pair<double, AObject*> >::iterator it2;
  std::pair<float, float>     pos;

  for (it2 = _explosion.begin(); it2 != _explosion.end();)
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

void  Core::bombExplode()
{
  std::map< double, std::pair< int, AObject*> >::iterator it2;
  std::pair<int, int> pos;
  int                     playerId;

  for (it2 = _bombs.begin(); it2 != _bombs.end(); )
  {
    if (_time - (*it2).first > 2.0)
    {
      pos = (*it2).second.second->getPos();
      playerId = (*it2).second.first;
      _player[(*it2).second.first]->setStock(_player[(*it2).second.first]->getStock() + 1);
      pos = (*it2).second.second->getPos();
      _map->deleteCube(pos.first, pos.second);
      _bombs.erase(it2++);
      explosion(pos, playerId);
      _sound->playSound(BOMB_S, 100);
    }
    else
      ++it2;
  }
}

void		Core::newBomb(std::pair<float, float> &check)
{
  AObject	*bomb;

  bomb = create<Bombs>();
  bomb->setType(LASER);
  bomb->initialize();
  _map->addCube(check.first, check.second, bomb);
  _explosion.push_back(std::make_pair(_time, bomb));
}

void	Core::explosion(std::pair<float, float> pos, int playerId)
{
  AObject *tmp;
  std::map< std::pair<float, float>, AObject * >::iterator it;
  std::pair<float, float>	check;

  check.first = pos.first;
  check.second = pos.second - 1;
  while (check.second - 1 < pos.second + 1)
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
  check.first = pos.first - 1;
  check.second = pos.second;
  while (check.first - 1 < pos.first + 1)
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

bool	Core::update()
{
  std::map< int, Player *>::iterator it;
  std::map< double, AObject*>::iterator it2;
  std::vector<AObject*>::iterator it1;

  _clock = _cam->getClock();
  _input = _cam->getInput();
  _time += _clock.getElapsed();
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  if (_input.getKey(SDLK_SPACE))
    makeBomb(_player[1]);
  if (_input.getKey(SDLK_KP_0) && _players == 2)
    makeBomb(_player[2]);
  for (it = _player.begin(); it != _player.end(); ++it)
    (*it).second->update(_clock, _input);
  for (it1 = _other.begin(); it1 != _other.end(); ++it1)
    (*it1)->update(_clock, _input);
  bombExplode();
  removeExplosion();
  return (true);
}

void  Core::drawAll(AObject *cur_char)
{
  std::pair<int, int> pos;
  type LastType = static_cast<type>(-1);
  AObject     *tmp;

  pos = cur_char->getPos();
  for (int x = pos.first - 30; x < pos.first + 30; ++x)
  {
    for (int y = pos.second - 30; y < pos.second + 30; ++y)
    {
      tmp = _map->getCase(x, y);
      if (!tmp)
        continue;
      if (tmp->getType() != LastType)
      {
        LastType = tmp->getType();
        _loader->bindTexture(LastType);
      }
      _loader->drawGeometry(_shader, tmp->getTransformation());
    }
  }
  for (std::vector<AObject*>::iterator i = _other.begin(); i != _other.end(); ++i)
    (*i)->draw(_shader, _clock);
  for (size_t i = 1; i <= _player.size(); i++)
    _player[i]->draw(_shader, _clock);
}

void  Core::changeFocus(AObject *cur_char, int screen)
{
  std::pair<float, float> pos;
  pos = cur_char->getPos();
  _cam->moveCamera(glm::vec3(pos.first, 13, -10 + pos.second),
    glm::vec3(pos.first, 0, pos.second), glm::vec3(0, 1, 0), screen);
}

std::pair<float, float>  Core::genPos()
{
  std::pair<float, float> pos;

  pos.first = (_player[1]->getPos().first + _player[2]->getPos().first)/4;
  pos.second = (_player[1]->getPos().second + _player[2]->getPos().second)/4;
  //pos.first -= 2;
  pos.second -= 2;
  return (pos);
}

void	Core::draw()
{
  std::pair<float, float> pos;
  if (_screen == 0)
    changeFocus(_player[1], 1);
  else
  {
    pos = genPos();
    _cam->moveCamera(glm::vec3(pos.first, 15, -10 + pos.second),
     glm::vec3(pos.first, _dist, pos.second), glm::vec3(0, 1, 0), 1);
  }
  drawAll(_player[1]);
  if (_players == 2)
  {
    if (_screen == 0)
      changeFocus(_player[2], 2);
    drawAll(_player[2]);
  }
  _cam->flushContext();
}
