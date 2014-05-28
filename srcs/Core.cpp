/*
** Core.cpp for core in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 16:31:08 2014 Antonin Ribeaud
// Last update Sun May 11 00:12:10 2014 Mehdi Chouag
*/

#include  <unistd.h>
#include  "Menu.hpp"
#include  "Core.hpp"

Core::Core(Camera *cam, Loader *loader, Menu *menu)
{
  _loader = loader;
  _cam = cam;
  _menu = menu;
  _sound = new Sound();
  _hud = new Hud(cam, loader);
  _displayFPS = false;
  _ainput = NULL;
}

void  Core::reset()
{
  std::map<int, Player *>::const_iterator it;
  std::map<std::pair<float, float>, Bombs *>::const_iterator it2;

  _bombs.clear();
  for (it = _player.begin(); it != _player.end(); ++it)
    delete (*it).second;
  _player.clear();
  for (size_t i(0); i != _other.size(); i++)
    delete _other[i];
  _other.clear();
  _hud->resetClock();
  _displayFPS = false;
  delete _particles;
}

void  Core::setValues(Map *map)
{
  std::vector<std::pair<int, int> >    obj;
  
  _players = _menu->getNbPlayer();
  _map = map;
  _width = _menu->getMapSize();
  _height = _width;
  obj = _map->setSpawn(_players);
  std::cout << obj.size() << std::endl;
  _posx = obj.begin()->first;
  _posy = obj.begin()->second;
  _nb_bot = _menu->getNbBots();
  if (_players == 2)
  {
    obj.erase(obj.begin());
    _posx2 = obj.begin()->first;
    _posy2 = obj.begin()->second;
  }
  _time = 0;
  _frames = 0;
  _endgame = false;

}

Core::~Core()
{
  delete _sound;
  delete _hud;
}

bool	Core::initialize()
{
  _shader = _cam->getShader();
  _clock = _cam->getClock();
  if (!drawFloor() || !drawChar() || !drawBot(_nb_bot))
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
  _particles = new Particles(_loader);
  std::cout << "Load done!" << std::endl;
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
  Player *chara = create<Player>();
  std::pair<float, float> pos;

  if (chara->initialize() == false)
    return (false);
  pos = std::make_pair(posx, posy);
  chara->setPos(pos);
  chara->setPlayer(screen);
  chara->setMap(_map);
  chara->setId(screen);
  chara->setBombs(&_bombs);
  chara->setSound(_sound);
  chara->setPlayerTab(&_player);
  _player[screen] = chara;
  return (true);
}

bool   Core::makeBot(int posx, int posy, int id)
{
  Player *chara = create<Mybot>();
  std::pair<float, float> pos;

  if (chara->initialize() == false)
    return (false);
  pos = std::make_pair(posx, posy);
  chara->setPos(pos);
  chara->setMap(_map);
  chara->setId(id);
  chara->setBombs(&_bombs);
  chara->setPlayerTab(&_player);
  chara->setSound(_sound),
  _player[id] = chara;
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

bool    Core::drawBot(int nb)
{
  std::vector<std::pair<int, int> >    spawn;
  int   x;
  int   y;
  int   i;

  i = 0;
  if (nb > 0)
    spawn = _map->setSpawn(nb);
  while (++i <= nb && nb > 0)
    {
      x = spawn.begin()->first;
      y = spawn.begin()->second;
      if (makeBot(x, y, i + 2) == false)
        return (false);
      if (i < nb)
        spawn.erase(spawn.begin());
    }
  return true;
}

void  Core::FPS()
{
  _lasttime += _clock.getElapsed();
  if (_lasttime > 1)
  {
    if (_displayFPS == true)
      _hud->updateFPS(_frames);
    _lasttime = 0;
    _frames = 1;
  }
  else
    _frames++;
}

bool	Core::update()
{
  checkAlive();
  if (_endgame == true)
    return (false);
  std::map< int, Player *>::iterator it;
  std::map< double, AObject*>::iterator it2;
  std::vector<AObject*>::iterator it1;;

  _clock = _cam->getClock();
  _input = _cam->getInput();
  if (_ainput == NULL)
  {
    _ainput = new AInput(_input, GAME);
  }
  _ainput->setInput(_input);
  switch (_ainput->getInput())
  {
    case FPSON:
      _displayFPS = true;
      break;
    case FPSOFF:
      _displayFPS = false;
      break;
    case ESCAPE:
      return (false);
    case PSAVE:
      Saving(_map->getName(), this);
      break;
    default:
      break;
  }
  FPS();
  _time += _clock.getElapsed();
  for (it = _player.begin(); it != _player.end(); ++it)
  {
    if ((*it).second->isAlive() == true)
    (*it).second->update(_clock, _input);
  }
  for (it1 = _other.begin(); it1 != _other.end(); ++it1)
    (*it1)->update(_clock, _input);
  for (std::map<std::pair<float, float>, Bombs *>::iterator it6 = _bombs.begin(); it6 != _bombs.end(); )
  {
    (*it6).second->update(_clock, _input);
    if ((*it6).second->isExplosed() == true)
    {
      _bombs.erase(it6);
      it6 = _bombs.begin();
    }
    else
      ++it6;
  }
  _hud->setClock(_clock);
  if (_players == 2)
  {
    _hud->update(_player[2]);
    _hud->setScreen(_screen + 1);
  }
  else
    _hud->setScreen(2);
  _hud->update(_player[1]);
  for (int i = 3; i <= _nb_bot + 2; i++)
    _player[i]->setObj(_clock);
  _particles->update(_clock, _input);
  return (true);
}

void  Core::drawAll(AObject *cur_char)
{
  std::pair<int, int> pos;
  type LastType = static_cast<type>(-1);
  AObject     *tmp;
  int         nb_p;

  nb_p = 0;
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
  {
    nb_p = (i == 2 && _players == 1) ? 1 : 0;
    _player[i + nb_p]->draw(_shader, _clock);
  }
  _particles->draw(_shader, _clock);
}

void  Core::checkAlive()
{
  std::map< int, Player *>::iterator it;
  int num;

  num = 0;
  if (_players == 2)
  {
    if (!_player[1]->isAlive() && !_player[2]->isAlive())
      _endgame = true;
  }
  else if (!_player[1]->isAlive())
    _endgame = true;
 
  for (it = _player.begin(); it != _player.end(); ++it)
  {
    if ((*it).second->isAlive() == true)
      num++;
  }
  if (num == 1)
    _endgame = true;
}

void	Core::draw()
{
  std::pair<float, float> pos;
  if (_players == 2)
    _screen = _cam->genSplit(_player[1], _player[2]);
  if (_screen == 0)
  {
    if (_player[1]->isAlive() == false && _players == 2)
      _cam->changeFocus(_player[2], 1);
    else
      _cam->changeFocus(_player[1], 1);
  }
  else
  {
    pos = _cam->genPos(_player[1], _player[2]);
    _cam->moveCamera(glm::vec3(pos.first, 15, -10 + pos.second),
     glm::vec3(pos.first, 0, pos.second), glm::vec3(0, 1, 0), 1);
  }
  if (_player[1]->isAlive() == true)
  {
    drawAll(_player[1]);
    _hud->draw(_player[1]);
  }
  if (_players == 2 && _player[2]->isAlive() == true)
  {
    if (_screen == 0)
      _cam->changeFocus(_player[2], 2);
    drawAll(_player[2]);
    _hud->draw(_player[2]);
  }
  if (_displayFPS)
    _hud->drawFPS();
  _cam->flushContext();
}

Map       *Core::getMap()
{
  return (_map);
}

std::map<int, Player*>  Core::getPlayer()
{
  return (_player);
}

int       Core::getNbrPlayer() const
{
  return _players;
}
