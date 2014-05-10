/*
** Core.cpp for core in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 16:31:08 2014 Antonin Ribeaud
// Last update Sat May 10 01:23:37 2014 Mehdi Chouag
*/

#include "Core.hpp"
#include <unistd.h>

Core::Core(Camera *cam, Loader *loader)
{
  _width = 10;
  _height = 10;
  _loader = loader;
  _cam = cam;
  _map = new Map(_width, _height, _objects);
  _players = 1;
  _cam->setPlayer(_players);
  _posx = POSX;
  _posy = POSY;
  _posx2 = POSX1;
  _posy2 = POSY1;
  _percent = 15;
  _time = 0;
}

Core::~Core()
{
  std::map< std::pair<float, float>, AObject *>::iterator it;

  for (it = _objects.begin(); it !=  _objects.end(); ++it)
    delete (*it).second;
  delete _map;
}

bool	Core::initialize()
{
  _shader = _cam->getShader();
  _clock = _cam->getClock();
  if (drawMap() == false)
    return (false);
  if (drawFloor() == false)
    return (false);
  if (drawChar() == false)
    return (false);
  // if (drawBot() == false)
  //   return (false);
  if (drawBackground() == false)
    return (false);
  _cam->setPlayer(_players);
  std::cout << "Load done!" << std::endl;
  for (size_t i = 0; i < _loading.size(); ++i)
    delete _loading[i];
  return (true);
}

bool  Core::drawMap()
{
  _objects = _map->getMap();
  std::cout << _objects.size() << std::endl;
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
  pos = std::make_pair((float)posx, (float)posy);
  chara->setPos(pos);
  chara->setPlayer(screen);
  chara->setMap(&_objects);;
  chara->setId(screen);
  chara->translate(glm::vec3(posx, 0, posy));
  _player[screen] = chara;
  return (true);
}

bool		Core::drawChar()
{
  if (makeChar(POSX, POSY, 1) == false)
    return (false);
  if (_players == 2)
  {
    if (makeChar(POSX1, POSY1, 2) == false)
      return (false);
  }
  return (true);
}

bool  Core::makeBomb(Player *player)
{
  float temp1;
  float temp2;
  std::pair<float, float> pos;

  pos = player->getPos();
  temp1 = floor(pos.first);
  temp2 = ceil(pos.first);
  if (temp1 - pos.first > pos.first - temp2)
  {
    pos.first = temp1;
  }
  else
    pos.first = temp2;
  temp1 = floor(pos.second);
  temp2 = ceil(pos.second);
  if (temp1 - pos.second > pos.second - temp2)
  {
    pos.second = temp1;
  }
  else
    pos.second = temp2;
  if (_objects.find(pos) == _objects.end())
  {
    if (player->getStock() >= 1)
    {
      AObject *bomb = create<Bombs>();
      bomb->setType(BOMB);
      bomb->setPos(pos);
      bomb->initialize();
      _objects[pos] = bomb;
      _bombs[_time] = std::make_pair(player->getId(), bomb);
      player->setStock(player->getStock() - 1);
    }
  }
  return (true);
}

void  Core::removeExplosion()
{
  std::map< double, AObject*>::iterator it2;
 
  for (it2 = _explosion.begin(); it2 != _explosion.end(); ++it2)
  {
      if (_time - (*it2).first > 0.5)
      {
        _objects.erase(_objects.find((*it2).second->getPos()));
      }
   }
  for (it2 = _explosion.begin(); it2 != _explosion.end(); ++it2)
  {
      if (_time - (*it2).first > 0.5)
      {
        _explosion.erase((it2));
      }
   }
}

void  Core::bombExplode()
{
  std::map< double, std::pair< int, AObject*> >::iterator it2;

  std::pair<float, float> pos;
  int                     playerId;

  for (it2 = _bombs.begin(); it2 != _bombs.end(); ++it2)
  {
      if (_time - (*it2).first > 2.0)
      {
        _objects.erase(_objects.find((*it2).second.second->getPos()));
     }
   }
  for (it2 = _bombs.begin(); it2 != _bombs.end(); )
  {
      if (_time - (*it2).first > 2.0)
      {
        pos = (*it2).second.second->getPos();
        playerId = (*it2).second.first;
        _player[(*it2).second.first]->setStock(_player[(*it2).second.first]->getStock() + 1);
        _bombs.erase(it2++);
        explosion(pos, playerId);
      }
      else
        ++it2;
   }
}

void  Core::explosion(std::pair<float, float> pos, int playerId)
{
    AObject *bomb = create<Bombs>();
    bomb->setType(LASER);
    bomb->setPos(pos);
    bomb->initialize();
    _objects[pos] = bomb;
    _explosion[_time] = bomb;
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
  std::map< std::pair<float, float>, AObject * >::iterator it;
  std::vector<AObject*>::iterator it2;
  std::pair<float, float> pos;
  std::pair<float, float> check;
  type LastType = BLOCKD;

  _loader->bindTexture(LastType);
  pos = cur_char->getPos();
  pos.first = (float)(int)pos.first;
  pos.second = (float)(int)pos.second;
  check.second = pos.second - 15;
  while (check.second < pos.second + 25)
  {
    check.first = pos.first - 30;
    while (check.first < pos.first + 30)
    {
        if ((it = _objects.find(check)) != _objects.end())
        {
          if ((*it).second->getType() != LastType)
          {
            LastType = (*it).second->getType();
            _loader->bindTexture(LastType);
          }
          _loader->drawGeometry(_shader, (*it).second->getTransformation());
        }
      check.first++;
    }
    check.second++;
  }
  for (it2 = _other.begin(); it2 != _other.end(); ++it2)
    (*it2)->draw(_shader, _clock);
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

void	Core::draw()
{	
  changeFocus(_player[1], 1);
  drawAll(_player[1]);
  if (_players == 2)
    {
      changeFocus(_player[2], 2);
      drawAll(_player[2]);
    }
  _cam->flushContext();
}
