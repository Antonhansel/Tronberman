/*
** Generator.cpp for Generator in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Sat May  17 06:22:46 2014 Antonin Ribeaud
** Last update Sat May  17 06:22:46 2014 Antonin Ribeaud
*/

#include "Generator.hpp"
#include "Saving.hpp"

Generator::Generator(Camera *camera, Loader *loader, const int size)
{
	_size = size;
	_camera = camera;
	_loader = loader;
	_time = 0;
  _map = new Map(_size, true);
  _ainput = new AInput(_camera->getInput(), GENERATOR);
}

Generator::~Generator()
{
  std::string name = "./ressources/maps/";

  for (int i = 0 ; i < 10 ; i++)
    name += (rand()%26)+97;
  name += ".xml";
  Saving *s = new Saving(name);
  s->saveGame(_map);
  delete s;
}

bool 	Generator::drawBackground()
{
  _floor = new Floor(_size, _size, 10.0f);
  return (_floor->initialize());
}

void 	Generator::draw()
{
	type LastType = BLOCKD;
	_shader = _camera->getShader();
	_camera->moveCamera(vec3(_cube->getPos().first, 10, _cube->getPos().second + -10), vec3(_cube->getPos().first, 0, _cube->getPos().second), vec3(0,1,0), 1);
	_loader->bindTexture(LastType);
  std::pair<int, int> pos;
  AObject     *tmp;

  for (int x = 0 ; x <= _size; ++x)
  {
    for (int y = 0; y <= _size; ++y)
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
  _loader->bindTexture(_cube->getType());
  _loader->drawGeometry(_shader, _cube->getTransformation());
  _floor->draw(_shader, _clock);
  _camera->flushContext();
}

bool Generator::cleanObjects(const int i)
{
	if (_size + i != 40 && _size + i != 10)
	{
		std::cout << _size + i << std::endl; 
		_size += i;
	}
  for (int i = 0; i < _size * _size; ++i)
  {
      if (_map->getCase(i / _size, i % _size))
         _map->deleteCube(i / _size, i % _size);
  }
	if (initialize() == false)
		return (false);
	return (true);
}

bool Generator::initCursor(const int x, const int z)
{
  _cube = create<Cube>();
	std::pair<float, float> pos;
  _cube->setType(BLOCK);
  if (_cube->initialize() == false)
    return (false);
  pos = std::make_pair(x, z);
  _cube->setPos(pos);
  _cube->translate(glm::vec3(0, 1, 0));
  return (true);
}

bool Generator::changeSize(const key &k)
{
  	if (k == GPLUS)
  	{
  		if (cleanObjects(1) == false)
  			return (false);
  	}
  	if (k == GMINUS)
  	{
  		if (cleanObjects(-1) == false)
  			return (false);
  	}
  	return (true);
}

void 	Generator::placeCube(const key &k)
{
  std::pair<float, float> pos;

  if (k == SPACE)
    {
    pos = _cube->getPos();
  	if ((pos.first > 0 && pos.first < _size) && 
  		pos.second > 0 && pos.second < _size)
  	{
  		  	_map->addCube(_cube->getPos().first, _cube->getPos().second, _cube->getType());
  		  	_camera->tiltMode();
  	}
  }
}

void 	Generator::changeType(const key &k)
{
	if (k == KP1)
	  	_cube->setType(BLOCKD);
	if (k == KP2)
	    _cube->setType(BLOCK);
}

void 	Generator::moveCursor(const key &k)
{
	if (k == PUP && _cube->getPos().second + 1 < _size - 1)
		_cube->translate(glm::vec3(0, 0, 1));
	if (k == PDOWN && _cube->getPos().second - 1 > 0)
		_cube->translate(glm::vec3(0, 0, -1));
	if (k == PLEFT && _cube->getPos().first + 1 < _size - 1)
		_cube->translate(glm::vec3(1, 0, 0));
	if (k == PRIGHT && _cube->getPos().first - 1 > 0)
		_cube->translate(glm::vec3(-1, 0, 0));
}

bool Generator::update()
{
	   _clock = _camera->getClock();
  	_input = _camera->getInput();
    _ainput->setInput(_input);
  	_time += _clock.getElapsed();
    _k = _ainput->getInput();
  	if (_time > 0.03)
  	{
      for (std::vector<key>::iterator it = _k.begin(); it != _k.end(); ++it)
      {
        if (changeSize((*it)) == false)
         return (false);
        if ((*it) == ESCAPE)
          return (false);
        if ((*it) == MBACKSPACE)
          _map->deleteCube(_cube->getPos().first, _cube->getPos().second);
        moveCursor((*it));
        changeType((*it));
        placeCube((*it));
      }
	    _time = 0;
	}
    return (true);
}

bool 	Generator::initialize()
{
  _map = new Map(_size, true);
	if (initCursor(round(_size/2), round(_size/2)) == false)
		return (false);
	if (drawBackground() == false)
		return (false);
  return (true);
}
