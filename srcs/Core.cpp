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
  _width = 50;
  _height = 50;
  _loader = loader;
  _cam = cam;
  _players = 2;
  _map = new Map(_width, _height);
  _sound = new Sound();
  obj = _map->setSpawn(_players);
  _posx = obj.begin()->first;
  _posy = obj.begin()->second;
  if (_players == 2)
  {
    obj.erase(obj.begin());
    _posx2 = obj.begin()->first;
    _posy2 = obj.begin()->second;
  }
  _percent = 15;
  _time = 0;
  _frames = 0;
  _lasttime = 0;
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
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   float LightPos[4]={0,0,0,1};
   glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
   glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,40);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
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

void  Core::FPS()
{
  _lasttime += _clock.getElapsed();
  if (_lasttime > 1)
  {
    std::cout << _frames << std::endl;
    _lasttime = 0;
    _frames = 1;
  }
  else
  {
    _frames++;
  }
}

bool	Core::update()
{
  std::map< int, Player *>::iterator it;
  std::map< double, AObject*>::iterator it2;
  std::vector<AObject*>::iterator it1;
  std::pair<float, float> pos;

  _clock = _cam->getClock();
  _input = _cam->getInput();
  FPS();
  _time += _clock.getElapsed();
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  if (_input.getKey(SDLK_KP_0))
  {
    pos = _player[1]->getPos();
    pos.first = floor(pos.first);
    pos.second = floor(pos.second);
    if (_bombs.find(pos) == _bombs.end())
    {
      Bombs *b = new Bombs();
      b->setObjects(_map, _sound, &_bombs);
      b->makeBomb(_player[1]);
      _bombs[pos] = b;
    }
  }
  if (_input.getKey(SDLK_SPACE) && _players == 2)
  {
    pos = _player[2]->getPos();
    pos.first = floor(pos.first);
    pos.second = floor(pos.second);
    if (_bombs.find(pos) == _bombs.end())
    {
      Bombs *b = new Bombs();
      b->setObjects(_map, _sound, &_bombs);
      b->makeBomb(_player[2]);
      _bombs[pos] = b;
    }
  }
  for (it = _player.begin(); it != _player.end(); ++it)
    (*it).second->update(_clock, _input);
  for (it1 = _other.begin(); it1 != _other.end(); ++it1)
    (*it1)->update(_clock, _input);
  for (std::map<std::pair<float, float>, Bombs *>::iterator it = _bombs.begin(); it != _bombs.end(); )
  {
    (*it).second->update(_clock, _input);
    (*it).second->bombExplode();
    (*it).second->removeExplosion();
    if ((*it).second->isExplosed() == true)
    {
      _bombs.erase(it);
      it = _bombs.begin();
    }
    else
      ++it;
  }
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

  pos.first = (_player[1]->getPos().first + _player[2]->getPos().first)/2;
  pos.second = (_player[1]->getPos().second + _player[2]->getPos().second)/2;
  pos.second -= 2;
  return (pos);
}

void  Core::genSplit()
{
  float   pos1;
  float   pos2;

  if (_player[1]->getPos().first > _player[2]->getPos().first)
    pos1 = _player[1]->getPos().first - _player[2]->getPos().first;
  else
    pos1 = _player[2]->getPos().first - _player[1]->getPos().first;
  if (_player[1]->getPos().second > _player[2]->getPos().second)
    pos2 = _player[1]->getPos().second - _player[2]->getPos().second;
  else
    pos2 = _player[2]->getPos().second - _player[1]->getPos().second;
  if (pos1 > 20 || pos2 > 20)
  {
    _cam->setPlayer(2);
    _screen = 0;
  }
  else
  {
    _cam->setPlayer(1);
    _screen = 1;
  }
}

void	Core::draw()
{
  std::pair<float, float> pos;
  if (_players == 2)
    genSplit();
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
