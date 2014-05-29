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

Generator::Generator(Camera *camera, Loader *loader, int size)
{
	_size = size;
	_camera = camera;
	_loader = loader;
	_time = 0;
  _map = new AObject *[_size * _size];
  _ainput = new AInput(_camera->getInput(), GENERATOR);
  memset(_map, 0, (_size * _size) * sizeof(AObject *));
}

Generator::~Generator()
{
  std::string name = "./ressources/maps/";

  for (int i = 0 ; i < 10 ; i++)
    name += (rand()%26)+97;
  name += ".xml";
  Saving(name, _map, _size); 
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
      tmp = getCase(x, y);
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

bool Generator::cleanObjects(int i)
{
	if (_size + i != 40 && _size + i != 10)
	{
		std::cout << _size + i << std::endl; 
		_size += i;
	}
  for (int j = 0; j < _size - i * _size - i ; ++j)
  {
      if (_map[j])
         delete _map[j];
  }
	if (initialize() == false)
		return (false);
	return (true);
}

AObject     *Generator::getCase(int x, int y) const
{
    if (x < 0 || x >= _size || y < 0 || y >= _size)
        return NULL;
    return _map[x * _size + y];
}

bool Generator::initCursor(int x, int z)
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

bool Generator::changeSize(key &k)
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

void 	Generator::placeCube(key &k)
{
  std::pair<float, float> pos;

  if (k == SPACE)
    {
    pos = _cube->getPos();
  	if ((pos.first > 0 && pos.first < _size) && 
  		pos.second > 0 && pos.second < _size)
  	{
  		  	addCube(_cube->getPos().first, _cube->getPos().second, _cube->getType());
  		  	_camera->tiltMode();
  	}
  }
}

void 	Generator::changeType(key &k)
{
	if (k == KP1)
	  	_cube->setType(BLOCKD);
	if (k == KP2)
	    _cube->setType(BLOCK);
}

void 	Generator::moveCursor(key &k)
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
          deleteCube(_cube->getPos().first, _cube->getPos().second);
        moveCursor((*it));
        changeType((*it));
        placeCube((*it));
      }
	    _time = 0;
	}
    return (true);
}

void Generator::deleteCube(int x, int y)
{
    if (x < 0 || x >= _size || y < 0 || y >= _size)
        return;
    delete _map[x * _size + y];
    _map[x * _size + y] = NULL;
}

void Generator::addCube(int x, int y, type blockType)
{
    std::pair<float, float>     pos;
    AObject     *tmp;

    if (x < 0 || x >= _size || y < 0 || y >= _size)
        return;
    if (_map[x * _size + y])
        deleteCube(x, y);
    tmp = create<Cube>();
    pos = std::make_pair(x, y);
    tmp->setType(blockType);
    tmp->setPos(pos);
    tmp->initialize();
    _map[x * _size + y] = tmp;
}

bool 	Generator::initialize()
{
  _map = new AObject *[_size * _size];
   memset(_map, 0, (_size * _size) * sizeof(AObject *));
	if (initCursor(round(_size/2), round(_size/2)) == false)
		return (false);
	if (drawBackground() == false)
		return (false);
	for (int y = 0; y < _size; y++)
    {
        addCube(0, y, BORDER);
        addCube(_size - 1, y, BORDER);
    }
    for (int x = 0; x < _size; x++)
    {
        addCube(x, 0, BORDER);
        addCube(x, _size - 1, BORDER);
    }
    return (true);
}
