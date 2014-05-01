/*
** Intro.cpp for Intro in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 12:48:21 2014 Antonin Ribeaud
** Last update Thu May  01 12:48:21 2014 Antonin Ribeaud
*/

# include "Intro.hpp"
# include "AObject.hpp"

Intro::Intro()
{
		_width = 6;
		_height = 6;
}

Intro::~Intro()
{
	for (size_t i = 0; i < _objects.size(); ++i)
		delete _objects[i];
}

bool	Intro::initialize()
{
	if (!_context.start(1800, 1000, "Best Bomberman!"))
		return (false);
	glEnable(GL_DEPTH_TEST);
	if (!_shader.load("./ressources/shaders/basic.fp", GL_FRAGMENT_SHADER) || 
	!_shader.load("./ressources/shaders/basic.vp", GL_VERTEX_SHADER) || 
	!_shader.build())
		return (false);
	_projection = glm::perspective(60.0f, 1800.0f / 1000.0f, 0.1f, 100.0f);
	_transformation = glm::lookAt(glm::vec3(0, 10, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_shader.bind();
	_shader.setUniform("view", _transformation);
	_shader.setUniform("projection", _projection);
	if (drawLimits() == false)
		return (false);
	std::cout << "Load done!" << std::endl;
	return (true);
}

bool	Intro::drawLimits()
{
	int 		z;
	int 		x;

	x = -_width;
	z = -_height;
	while (x < _width)
	{
		z = -_height;
			while (z < _height)
			{
			if (makeCube(x, (x+z)/2, z) == false)
				return (false);
			z++;
			}
		x++;
	}
	return (true);
}

bool	Intro::makeCube(int x, int y, int z)
{
	AObject	*cube = new	Cube;
	if (cube->initialize() == false)
		return (false);
	cube->translate(glm::vec3(x, y, z));
	cube->setPos(x, z);
	_objects.push_back(cube);
	return (true);
}

bool	Intro::update()
{
	if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
		return false;
	_context.updateClock(_clock);
	_context.updateInputs(_input);
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->update(_clock, _input);
	return true;
}

void	Intro::draw()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader.setUniform("view", glm::lookAt(glm::vec3(0, 13, -10),
		glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	_shader.setUniform("projection", _projection);
	_shader.bind();
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->draw(_shader, _clock);
	_context.flush();
}
