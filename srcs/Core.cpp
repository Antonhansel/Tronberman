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
  _width = 50;
  _height = 50;
  _cam = cam;
  _map = new Map(_width, _height, _objects);
  _players = 1;
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
  _cam->stopContext();
}

bool	Core::drawMap()
{
  _objects = _map->getMap();
  std::cout << _objects.size() << std::endl;
  return (true);
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
        _player[_player.size() + 1] = obj;
      }
    }
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
  chara->setScreen(screen);
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

void	Core::changeFocus2(AObject *cur_char)
{
  cur_char->update(_clock, _input);
  if (_input.getKey(SDLK_z))
    _posx2 += cur_char->getTrans();
  if (_input.getKey(SDLK_s))
    _posx2 -= cur_char->getTrans();
  if (_input.getKey(SDLK_q))
    _posy2 += cur_char->getTrans();
  if (_input.getKey(SDLK_d))
    _posy2 -= cur_char->getTrans();
  _cam->moveCameraP2(glm::vec3(_posy2, 13, -10 + _posx2), 
		     glm::vec3(_posy2, 0, _posx2), glm::vec3(0, 1, 0));
}

void	Core::changeFocus(AObject *cur_char)
{
  cur_char->update(_clock, _input);
  if (_input.getKey(SDLK_UP))
    _posx += cur_char->getTrans();
  if (_input.getKey(SDLK_DOWN))
    _posx -= cur_char->getTrans();
  if (_input.getKey(SDLK_LEFT))
    _posy += cur_char->getTrans();
  if (_input.getKey(SDLK_RIGHT))
    _posy -= cur_char->getTrans();
  _cam->moveCameraP1(glm::vec3(_posy, 13, -10 + _posx), 
		     glm::vec3(_posy, 0, _posx), glm::vec3(0, 1, 0));
}

bool	Core::update()
{
  std::map< std::pair<float, float>, AObject * >::iterator	it;
  std::vector<AObject*>::iterator it1;

  _clock = _cam->getClock();
  _input = _cam->getInput();
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  // for (it = _objects.begin(); it != _objects.end(); ++it)
  //   (*it).second->update(_clock, _input);
  for (it1 = _other.begin(); it1 != _other.end(); ++it1)
    (*it1)->update(_clock, _input);
  return (true);
}

void  Core::drawAll()
{
  std::map< std::pair<float, float>, AObject * >::iterator it;
  std::map< std::pair<float, float>, AObject * >::iterator  it3;
  std::vector<AObject*>::iterator it2;

  for (it = _objects.begin(); it != _objects.end(); ++it)
    {
      if (((*it).first.first - _posy < 30) && ((*it).first.first - _posy > -30)
        && ((*it).first.second - _posx < 25) && ((*it).first.second - _posx > -15))
        (*it).second->draw(_shader, _clock);
    }
  for (it2 = _other.begin(); it2 != _other.end(); ++it2)
    (*it2)->draw(_shader, _clock);
  for (int i = 1; i <= _player.size(); i++)
    _player[i]->draw(_shader, _clock);
}

void	Core::draw()
{	
  changeFocus(_player[1]);
  drawAll();
  if (_players == 2)
    {
      changeFocus2(_player[2]);
      drawAll();
    }
  _cam->flushContext();
}
