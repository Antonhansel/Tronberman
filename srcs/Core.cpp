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
  _posx = 1;
  _posy = 1;
  _posx2 = 1;
  _posy2 = 2;
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
  _cam->setPlayer(1);
  _shader = _cam->getShader();
  _clock = _cam->getClock();
  if (drawMap() == false)
    return (false);
  if (drawFloor() == false)
    return (false);
  if (drawChar() == false)
    return (false);
  if (drawBackground() == false)
    return (false);
  _cam->setPlayer(_players);
  std::cout << "Load done!" << std::endl;
  for (size_t i = 0; i < _loading.size(); ++i)
    delete _loading[i];
  return (true);
}

void		Core::intro()
{
  std::map< std::pair<float, float>, AObject * >::iterator	it;
  float i;

  i = 100;
  while (i > 0)
    {
      _cam->moveCameraP1(glm::vec3(_posy - i, 10 + i, -10 + _posx +i), 
			 glm::vec3(_posy, 0, _posx + i), glm::vec3(0, 1, 0));
      for (it = _objects.begin(); it != _objects.end(); ++it)
        (*it).second->draw(_shader, _clock);
      i--;
      _cam->flushContext();
      usleep(5000);
    }
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

bool		Core::drawChar()
{  
  AObject	*chara = create<Char>();
  std::pair<float, float>	pos;

  if (chara->initialize() == false)
    return (false);
  pos = std::make_pair((float)POSX, (float)POSY);
  chara->setPos(pos);
  chara->setScreen(1);
  chara->setPlayer(1);
  chara->translate(glm::vec3(POSX, 0, POSY));
  _player[1] = chara;
  if (_players == 2)
    {
      AObject	*chara1 = create<Char>();
      if (chara1->initialize() == false)
	return (false);
      pos = std::make_pair((float)POSX1, (float)POSY1);
      chara1->setPos(pos);
      chara1->translate(glm::vec3(POSX1, 0, POSY1));
      _player[2] = chara1;
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
  _cam->moveCameraP1(glm::vec3(_posy2, 13, -10 + _posx2), 
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

  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  _clock = _cam->getClock();
  _input = _cam->getInput();
  for (it = _objects.begin(); it != _objects.end(); ++it)
    (*it).second->update(_clock, _input);
  for (it1 = _other.begin(); it1 != _other.end(); ++it1)
    (*it1)->update(_clock, _input);
  return (true);
}

void	Core::draw()
{	
  std::map< std::pair<float, float>, AObject * >::iterator	it;
  std::map< std::pair<float, float>, AObject * >::iterator	it1;
  std::vector<AObject*>::iterator it2;

  changeFocus(_player[1]);
  for (it = _objects.begin(); it != _objects.end(); ++it)
    (*it).second->draw(_shader, _clock);
  for (it2 = _other.begin(); it2 != _other.end(); ++it2)
    (*it2)->draw(_shader, _clock);
  _player[1]->draw(_shader, _clock);
  if (_players == 2)
    {
      _player[2]->draw(_shader, _clock);
      changeFocus2(_player[2]);
      for (it = _objects.begin(); it != _objects.end(); ++it)
        (*it).second->draw(_shader, _clock);		
      _player[1]->draw(_shader, _clock);
      _player[2]->draw(_shader, _clock);
      for (it2 = _other.begin(); it2 != _other.end(); ++it2)
	(*it2)->draw(_shader, _clock);
    }
  _cam->flushContext();
}
