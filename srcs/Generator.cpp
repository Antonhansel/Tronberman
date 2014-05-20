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

Generator::Generator(Camera *camera, Loader *loader, int size)
{
	_size = size;
	_camera = camera;
	_loader = loader;
	_time = 0;
}

Generator::~Generator()
{
  	for (unsigned int it1 = 1; it1 < _objects.size(); it1++)
  		delete _objects[it1];
}

bool 	Generator::drawBackground()
{
  _floor = new Floor(100, 100, 10.0f);
  return (_floor->initialize());
}

void 	Generator::draw()
{
	type LastType = BLOCKD;
	_shader = _camera->getShader();
	_camera->moveCamera(vec3(_cube->getPos().first, 10, _cube->getPos().second + -10), vec3(_cube->getPos().first, 0, _cube->getPos().second), vec3(0,1,0), 1);
	_loader->bindTexture(LastType);
	for (size_t i = 0; i < _objects.size(); ++i)
    {
      if (_objects[i]->getType() != LastType)
      {
        LastType = _objects[i]->getType();
        _loader->bindTexture(LastType);
      }
      _loader->drawGeometry(_shader, _objects[i]->getTransformation());
    }
    _floor->draw(_shader, _clock);
    _camera->flushContext();
}

bool Generator::cleanObjects(int i)
{
	if (_size + i != 100 && _size + i != 10)
	{
		std::cout << _size + i << std::endl; 
		_size += i;
	}
  	for (unsigned int it1 = 1; it1 < _objects.size(); it1++)
  		delete _objects[it1];
    _objects.clear();
	if (initialize() == false)
		return (false);
	return (true);
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
  _objects.push_back(_cube);
  return (true);
}

bool Generator::changeSize()
{
  	if (_input.getKey(SDLK_KP_PLUS))
  	{
  		if (cleanObjects(1) == false)
  			return (false);
  	}
  	if (_input.getKey(SDLK_KP_MINUS))
  	{
  		if (cleanObjects(-1) == false)
  			return (false);
  	}
  	return (true);
}

void 	Generator::placeCube()
{
  std::pair<float, float> pos;
  int  exist = 0;

  if (_input.getKey(SDLK_SPACE))
    {
    pos = _cube->getPos();
  	if ((pos.first > 0 && pos.first < _size) && 
  		pos.second > 0 && pos.second < _size)
  	{
      std::vector<AObject *>::iterator it;
      for (it = _objects.begin(); it != _objects.end(); ++it)
      {
        if ((*it)->getPos() == pos)
          exist++;
      }
      if (exist == 1)
  		{
  		  	addCube(_cube->getPos().first, _cube->getPos().second, _cube->getType());
  		  	_camera->tiltMode();
  		}
  	}
  }
}

void 	Generator::changeType()
{
	if (_input.getKey(SDLK_KP_1))
	  	_cube->setType(BLOCKD);
	if (_input.getKey(SDLK_KP_2))
	    _cube->setType(BLOCK);	
}

void 	Generator::moveCursor()
{
	if (_input.getKey(SDLK_UP) && _cube->getPos().second + 1 < _size - 1)
		_cube->translate(glm::vec3(0, 0, 1));
	if (_input.getKey(SDLK_DOWN) && _cube->getPos().second - 1 > 0)
		_cube->translate(glm::vec3(0, 0, -1));
	if (_input.getKey(SDLK_LEFT) && _cube->getPos().first + 1 < _size - 1)
		_cube->translate(glm::vec3(1, 0, 0));
	if (_input.getKey(SDLK_RIGHT) && _cube->getPos().first - 1 > 0)
		_cube->translate(glm::vec3(-1, 0, 0));
}

bool Generator::update()
{
	   _clock = _camera->getClock();
  	_input = _camera->getInput();
  	_time += _clock.getElapsed();
  	if (_time > 0.03)
  	{
  		if (changeSize() == false)
  			return (false);
		if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
	    	return (false);
	    moveCursor();
	    changeType();
	    placeCube();
	    _time = 0;
	}
    return (true);
}

bool		Generator::addCube(int x, int z, type thetype)
{
  AObject	*cube = create<Cube>();
  std::pair<float, float> pos;

  cube->setType(thetype);
  if (cube->initialize() == false)
    return (false);
  pos = std::make_pair(x, z);
  cube->setPos(pos);
  _objects.push_back(cube);
  return (true);
}

bool 	Generator::initialize()
{
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
