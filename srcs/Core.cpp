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
  _width = 30;
  _height = 30;
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

void  Core::spawnBomb(Player *player)
{
  std::pair<float, float> pos;

  pos = player->getPos();
  pos.first = floor(pos.first);
  pos.second = floor(pos.second);
  if (_bombs.find(pos) == _bombs.end())
  {
     Bombs *b = new Bombs();
     b->setObjects(_map, _sound, &_bombs);
     b->setPlayerTab(&_player);
     b->makeBomb(player);
     _bombs[pos] = b;
   }
}

bool	Core::update()
{
  std::map< int, Player *>::iterator it;
  std::map< double, AObject*>::iterator it2;
  std::vector<AObject*>::iterator it1;;

  _clock = _cam->getClock();
  _input = _cam->getInput();
  FPS();
  _time += _clock.getElapsed();
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  if (_input.getKey(SDLK_l))
    glEnable(GL_LIGHT1);
  if (_input.getKey(SDLK_m))
    glDisable(GL_LIGHT1);
  if (_input.getKey(SDLK_KP_0))
    spawnBomb(_player[1]);
  if (_input.getKey(SDLK_SPACE) && _players == 2)
    spawnBomb(_player[2]);
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

void	Core::draw()
{
  std::pair<float, float> pos;
  if (_players == 2)
    _screen = _cam->genSplit(_player[1], _player[2]);
  if (_screen == 0)
    _cam->changeFocus(_player[1], 1);
  else
  {
    pos = _cam->genPos(_player[1], _player[2]);
    _cam->moveCamera(glm::vec3(pos.first, 15, -10 + pos.second),
     glm::vec3(pos.first, _dist, pos.second), glm::vec3(0, 1, 0), 1);
  }
  drawAll(_player[1]);
  if (_players == 2)
  {
    if (_screen == 0)
      _cam->changeFocus(_player[2], 2);
    drawAll(_player[2]);
  }
  _cam->flushContext();
}
