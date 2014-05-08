/*
** Core.cpp for core in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 16:31:08 2014 Antonin Ribeaud
// Last update Sun May  4 03:42:30 2014 Mehdi Chouag
*/

#include "Core.hpp"
#include <unistd.h>

Core::Core(Camera *cam)
{
  _width = 30;
  _height = 30;
  _cam = cam;
  _map = new Map(_width, _height, _objects);
  _players = 2;
  _cam->setPlayer(_players);
  _posx = POSX;
  _posy = POSY;
  _posx2 = POSX1;
  _posy2 = POSY1;
  _percent = 15;
}

Core::~Core()
{
  std::map< std::pair<float, float>, AObject *>::iterator it;

  for (it = _objects.begin(); it !=  _objects.end(); ++it)
    delete (*it).second;
  delete _map;
}

bool Core::drawTextures()
{
  if (_textures[BORDER].load("./ressources/assets/block.tga") == false)
    return (false);
  return (true);
}

bool	Core::initialize()
{
  _shader = _cam->getShader();
  _clock = _cam->getClock();
  if (drawTextures() == false)
    return (false);
  if (drawMap() == false)
    return (false);
  if (drawFloor() == false)
    return (false);
  if (drawChar() == false)
    return (false);
  if (drawBot() == false)
    return (false);
  if (drawBackground() == false)
    return (false);
  _cam->setPlayer(_players);
  std::cout << "Load done!" << std::endl;
  for (size_t i = 0; i < _loading.size(); ++i)
    delete _loading[i];
  return (true);
}

bool    Core::drawBot()
{
  std::pair<float, float> pos;
  AObject                 *obj;

  for (int y = (-_height + 16); y < _height; y += 15)
    {
      for (int x = (-_width + 16); x < _width; x += 15)
      {
        obj = create<Mybot>();
        if (obj->initialize() == false)
          return (false);
        pos = std::make_pair((float)x, (float)y);
        obj->initialize();
        obj->setType(BOT);
        obj->setPos(pos);
        obj->setMap(&_objects);
        _player[_player.size() + 1] = obj;
      }
    }
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
  AObject *chara = create<Char>();
  std::pair<float, float> pos;

  if (chara->initialize() == false)
    return (false);
  pos = std::make_pair((float)posx, (float)posy);
  chara->setPos(pos);
  chara->setPlayer(screen);
  chara->setMap(&_objects);
  chara->setBombs(_bombs);
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

bool	Core::update()
{
  std::map<int, AObject *>::iterator it;
  std::vector<AObject*>::iterator it1;

  _clock = _cam->getClock();
  _input = _cam->getInput();
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  for (it = _player.begin(); it != _player.end(); ++it)
    (*it).second->update(_clock, _input);
  for (it1 = _other.begin(); it1 != _other.end(); ++it1)
    (*it1)->update(_clock, _input);
  for (unsigned int i = (_players + 1); i <= _player.size(); i++)
    _player[i]->update(_clock, _input);
  return (true);
}

void  Core::drawAll(AObject *cur_char)
{
  std::map< std::pair<float, float>, AObject * >::iterator it;
  std::vector<AObject*>::iterator it2;
  std::pair<float, float> pos;

  pos = cur_char->getPos();
  for (it = _objects.begin(); it != _objects.end(); ++it)
    {
      if (((*it).first.first - pos.first < 30) && ((*it).first.first - pos.first > -30)
        && ((*it).first.second - pos.second < 25) && ((*it).first.second - pos.second > -15))
        (*it).second->draw(_shader, _clock);
    }
  for (it2 = _other.begin(); it2 != _other.end(); ++it2)
    (*it2)->draw(_shader, _clock);
  for (unsigned int i = 1; i <= _player.size(); i++)
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
