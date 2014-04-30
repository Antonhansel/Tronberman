/*
** Core.cpp for core in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 16:31:08 2014 Antonin Ribeaud
** Last update Mon Apr  28 16:31:08 2014 Antonin Ribeaud
*/

# include "AObject.hpp"
# include "Core.hpp"
# include "Floor.hpp"
# include "Char.hpp"

Core::Core()
{
	_width = 40.5f;
	_height = 40.5f;
	_players = 1;
}

Core::~Core()
{
	for (size_t i = 0; i < _objects.size(); ++i)
		delete _objects[i];
}

bool	Core::initialize()
{
	glm::mat4	projection;

	_posx = 0;
	_posy = 0;
	if (!_context.start(1800, 1000, "Best Bomberman!"))
		return (false);
	glEnable(GL_DEPTH_TEST);
	if (!_shader.load("./ressources/shaders/basic.fp", GL_FRAGMENT_SHADER) || 
	!_shader.load("./ressources/shaders/basic.vp", GL_VERTEX_SHADER) || 
	!_shader.build())
		return (false);
	projection = glm::perspective(60.0f, 1800.0f / 1000.0f, 0.1f, 100.0f);
	_transformation = glm::lookAt(glm::vec3(0, 10, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_shader.bind();
	_shader.setUniform("view", _transformation);
	_shader.setUniform("projection", projection);
	if (drawFloor() == false)
		return (false);
	if (drawWall() == false)
		return (false);
	if (drawLimits() == false)
		return (false);
	if (drawChar() == false)
		return (false);
	return (true);
}

bool	Core::drawLimits()
{
	int 		z;
	int 		x;

	x = _width;
	z = _height;
	while (x > -_width)
	{
		if (makeCube(x, 0, z) == false)
			return (false);
		x--;
	}
	while (z > -_height)
	{
		if (makeCube(x, 0, z) == false)
			return (false);
		z--;
	}
	while (x < _width)
	{
		if (makeCube(x, 0, z) == false)
			return (false);
		x++;
	}
	while (z < _height)
	{
		if (makeCube(x, 0, z) == false)
			return (false);
		z++;
	}
	return (true);
}

bool	Core::drawChar()
{
	Char	*Chara = new	Char(_players, 0);
	_mychar = Chara;
	if (Chara->initialize() == false)
		return (false);
	_objects.push_back(Chara);
	return (true);
}

bool	Core::drawFloor()
{
	AObject	*floor = new	Floor(_width, _height, 10.0f);

	_objects.push_back(floor);
	return (floor->initialize());
}

bool	Core::drawWall()
{
	int 		z;
	int 		x;

	x = _height;
	while (x >= -_height)
	{
		z = _width;
		while (z >= -_width)
		{
			if (makeCube(x, 0, z) == false)
				return (false);
			z -= 2;
		}
		x -= 2;
	}
	return (true);
}

bool	Core::makeCube(int x, int y, int z)
{
	AObject	*cube = new	Cube;
	if (cube->initialize() == false)
		return (false);
	cube->translate(glm::vec3(x, y, z));
	_objects.push_back(cube);
	return (true);
}

void	Core::changeFocus()
{
	_shader.bind();
	if (_input.getKey(SDLK_UP))
		_posx += _mychar->getTrans();
	if (_input.getKey(SDLK_DOWN))
		_posx -= _mychar->getTrans();
	if (_input.getKey(SDLK_LEFT))
		_posy += _mychar->getTrans();
	if (_input.getKey(SDLK_RIGHT))
		_posy -= _mychar->getTrans();
	//_transformation glm::lookAt(glm::vec3(_posy, 10, -20 + _posx),
	//glm::vec3(_posy, 0, _posx), glm::vec3(0, 1, 0));
	_shader.setUniform("view", glm::lookAt(glm::vec3(_posy, 10, -20 + _posx),
	glm::vec3(_posy, 0, _posx), glm::vec3(0, 1, 0)));
}

bool	Core::update()
{
	if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
		return false;
	_context.updateClock(_clock);
	_context.updateInputs(_input);
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->update(_clock, _input);
	changeFocus();
	return true;
}

void	Core::draw()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader.bind();
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->draw(_shader, _clock);
	_context.flush();
}
