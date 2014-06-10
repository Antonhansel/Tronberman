/*
** Core.cpp for core in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 16:31:08 2014 Antonin Ribeaud
// Last update Thu May 29 15:46:20 2014 ribeaud antonin
*/

#include  <unistd.h>
#include  "Menu.hpp"
#include  "Core.hpp"

Core::Core(Camera *cam, Loader *loader, Menu *menu, ParticleEngine *particles)
{
  _loader = loader;
  _cam = cam;
  _menu = menu;
  _sound = new Sound();
  _hud = new Hud(cam, loader);
  _displayFPS = false;
  _ainput = NULL;
  _particles = particles;
  _isSave = false;
  _mapFiller = NULL;
  _pause = false;
}

void  Core::reset()
{
  std::map<int, Player *>::const_iterator it;
  std::map<std::pair<float, float>, Bombs *>::const_iterator it2;

  _bombs.clear();
  for (std::vector<Player *>::iterator it = _player.begin(); it != _player.end(); ++it)
    delete (*it);
  _player.clear();
  for (size_t i(0); i != _other.size(); i++)
    delete _other[i];
  _other.clear();
  _hud->resetClock();
  _displayFPS = false;
  _ainput = NULL;
  _isSave = false;
  _mapFiller = NULL;
}

void  Core::setValues(Map *map)
{
  _sound->setEffect(_menu->getFx());
  _players = _menu->getNbPlayer();
  _map = map;
  _width = _menu->getMapSize();
  _height = _width;
  _nb_bot = _menu->getNbBots();
  if (_networking == NULL)
    _map->setSpawn(_players + _nb_bot);
  else
    _map->setSpawn(_players + _nb_bot + 10);
  _time = 0;
  _frames = 0;
  _endgame = false;
}

void  Core::setSave(Saving *saving)
{
  std::vector<std::pair<int, int> >    obj;

  _sound->setEffect(_menu->getFx());
  _player = saving->getPlayer();
  _players = saving->getPlayerNb();
  _nb_bot = _player.size() - _players;
  for (std::vector<Player *>::iterator it = _player.begin(); it != _player.end(); ++it)
  {
    (*it)->setBombs(&_bombs);
    (*it)->setSound(_sound);
  }
  _hud->setTimer(saving->getTimer());
  _map = saving->getMap();
  _width = _menu->getMapSize();
  _height = _width;
  _time = 0;
  _frames = 0;
  _isSave = _menu->isSave();
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
  std::cout << "Load done!" << std::endl;
  _networking = _menu->getNetwork();
  if (_networking)
  {
    _players = 1;
    _screen = 0;
    _cam->setPlayer(_players);
    _networking->startGame(this);
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

bool   Core::makeChar(const std::pair<float, float> &pos, const int screen)
{
  Player *chara = create<Player>();

  chara->setId(screen);
  if (chara->initialize() == false)
    return (false);
  chara->setPos(pos);
  chara->setPlayer(screen);
  chara->setMap(_map);
  chara->setBombs(&_bombs);
  chara->setSound(_sound);
  chara->setPlayerTab(&_player);
  _player.push_back(chara);
  return (true);
}

bool   Core::makeBot(const std::pair<float, float>& pos, const int id)
{
  Player *chara = create<Mybot>();

  chara->setId(id);
  if (chara->initialize() == false)
    return (false);
  chara->setPos(pos);
  chara->setMap(_map);
  chara->setBombs(&_bombs);
  chara->setPlayerTab(&_player);
  chara->setSound(_sound);
  _player.push_back(chara);
  return (true);
}

bool		Core::drawChar()
{
  if (!_isSave)
  {
    if (makeChar(_map->getSpawn(), 1) == false)
      return (false);
    if (_players == 2)
    {
      if (makeChar(_map->getSpawn(), 2) == false)
        return (false);
    }
  }
  return (true);
}

bool    Core::drawBot(const int nb)
{
  int   i;

  i = 0;
  if (!_isSave)
  {
    while (++i <= nb && nb > 0)
      if (makeBot(_map->getSpawn(), i + 2) == false)
        return (false);
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
  std::vector<key>  k;

  if (!_pause)
  {
    checkAlive();
    if (_endgame == true)
      return (false);
    _clock = _cam->getClock();
    _input = _cam->getInput();
    if (_networking)
      _networking->refreshGame();
    if (_ainput == NULL)
      _ainput = new AInput(_input, GAME);
    _ainput->setInput(_input);
    k = _ainput->getInput();
    if (!checkKey(k))
      return (false);
    FPS();
    _time += _clock.getElapsed();
    for (std::vector<Player *>::iterator it = _player.begin(); it != _player.end(); ++it)
    {
      if (*it && (*it)->isAlive() == true)
        (*it)->update(_clock, _input);
    }
    for (std::vector<AObject*>::iterator it1 = _other.begin(); it1 != _other.end(); ++it1)
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
      _hud->update(_player[1]);
      _hud->setScreen(_screen + 1);
    }
    else
      _hud->setScreen(2);
    _hud->update(_player[0]);
    _particles->update();
    if (_hud->getTimer() <= 0 && _networking == NULL)
    {
      if (_mapFiller == NULL)
        _mapFiller = new MapFiller(_map, _loader, &_player);
      _mapFiller->fillMap(_clock);
    }
  }
  else
  {
    if (!checkKey(k))
      return (false);
  }
  return (true);
}

bool  Core::checkKey(const std::vector<key> &k)
{
  for (std::vector<key>::const_iterator it = k.begin(); it != k.end(); ++it)
  {
    switch ((*it))
    {
      if (!_pause)
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
      {
        if (!_networking && _map->getSize() <= 500)
        {
          std::string name("");
          if ((name = _map->getName()).size() == 0)
          {
            name.assign("./ressources/save/");
            for (int i = 0 ; i < 10 ; i++)
            name += (rand()%26)+97;
            name += ".xml";
            _map->setName(name);
          }
          std::string t(name);
          Saving  *s = new Saving(t);
          _hud->displaySaving(true);
          draw();
          s->saveGame(_map, _player, _hud->getTimer());
          _clock = _cam->getClock();
          _time = _clock.getElapsed();
          _hud->displaySaving(false);
          delete s;
        }
      break;
      }
      }
      case PPSAVE:
      {
        _pause = !_pause;
        return (true);
      }
      default:
        continue;
    }
  }
  return (true);
}

bool  Core::playerDraw(const std::pair<float, float> &playerpos, const std::pair<float, float> &botpos) const
{
  std::pair<float, float> pos;
  if (playerpos.first > botpos.first)
  {
    if (playerpos.second > botpos.second)
    {
      if ((playerpos.first - botpos.first > 30) && (playerpos.second - botpos.second > 30))
        return (false);
    }
    else
    {
      if ((playerpos.first - botpos.first > 30) && (botpos.second - playerpos.second > 30))
        return (false);
    }
  }
  else
  {
    if (playerpos.second > botpos.second)
    {
      if ((botpos.first - playerpos.first > 30 ) && (playerpos.second - botpos.second > 30))
        return (false);
    }
    else
    {
      if ((botpos.first - playerpos.first > 30) && (botpos.second - playerpos.second > 30))
        return (false);
    }
  }
  return (true);
}

void  Core::drawAll(AObject *cur_char)
{
  std::pair<int, int> pos;
  AObject     *tmp;

  pos = cur_char->getPos();
  for (int x = pos.first - (30); x < pos.first + (30); ++x)
  {
    for (int y = pos.second - (30); y < pos.second + (30); ++y)
    {
      tmp = _map->getCase(x, y);
      if (!tmp)
        continue;
      _loader->bindTexture(tmp->getType());
      _loader->drawGeometry(_shader, tmp->getTransformation());
      }
  }
  for (std::vector<AObject*>::iterator i = _other.begin(); i != _other.end(); ++i)
    (*i)->draw(_shader, _clock);
  for (std::vector<Player *>::iterator player = _player.begin(); player != _player.end(); ++player)
  {
    if (*player && playerDraw((*player)->getPos(), cur_char->getPos()) && (*player)->isAlive())
      (*player)->draw(_shader, _clock);
  }
  _particles->draw(_shader, _clock, cur_char);
}

void  Core::checkAlive()
{
  int num;

  num = 0;
  if (_networking)
    return;
  if (_players == 2)
  {
    if (!_player[0]->isAlive() && !_player[1]->isAlive())
      _endgame = true;
  }
  else if (_player[0] && !_player[0]->isAlive())
    _endgame = true;
  for (std::vector<Player *>::iterator it = _player.begin(); it != _player.end(); ++it)
  {
    if ((*it)->isAlive() == true)
      num++;
  }
  if (num == 1)
  {
    for (std::vector<Player *>::iterator it = _player.begin(); it != _player.end(); ++it)
    {
      if ((*it)->isAlive() == true)
      {
        if ((*it)->getId() == 1 || (*it)->getId() == 2)
         endingGame(VICTORY);
        else
          endingGame(FATALITY);
      }
    }
    _endgame = true;
  }
}

void  Core::endingGame(const Death type)
{
  double time;

  time = 0;
  _hud->drawDeath(type);
  while (time < 3)
  {
    _cam->flushContext();
    _clock = _cam->getClock();
    time += _clock.getElapsed();
  }
}

void	Core::draw()
{
  std::pair<float, float> pos;
  if (_players == 2)
    _screen = _cam->genSplit(_player[0], _player[1]);
  if (_screen == 0)
  {
    if (_player[0]->isAlive() == false && _players == 2)
      _cam->changeFocus(_player[1], 1);
    else
      _cam->changeFocus(_player[0], 1);
  }
  else
  {
    pos = _cam->genPos(_player[0], _player[1]);
    _cam->moveCamera(glm::vec3(pos.first, 15, -10 + pos.second),
     glm::vec3(pos.first, 0, pos.second), glm::vec3(0, 1, 0), 1);
  }
  if (_player[0]->isAlive() == true)
  {
    drawAll(_player[0]);
    _hud->draw(_player[0]);
  }
  if (_players == 2 && _player[1]->isAlive() == true)
  {
    if (_screen == 0)
      _cam->changeFocus(_player[1], 2);
    drawAll(_player[1]);
    _hud->draw(_player[1]);
  }
  if (_displayFPS)
    _hud->drawFPS();
  if (_mapFiller != NULL)
    _mapFiller->draw(_shader);
  _cam->flushContext();
}

Map       *Core::getMap() const
{
  return (_map);
}

std::vector<Player*>  &Core::getPlayer()
{
  return (_player);
}

int       Core::getNbrPlayer() const
{
  return (_players);
}

const gdl::Clock *Core::getClock() const
{
  return (&_clock);
}

std::map<std::pair<float, float>, Bombs *> *Core::getBombs()
{
  return (&_bombs);
}

Sound   *Core::getSound() const
{
  return (_sound);
}

