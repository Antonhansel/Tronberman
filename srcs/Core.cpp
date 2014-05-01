/*
** Core.cpp for core in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 16:31:08 2014 Antonin Ribeaud
// Last update Thu May  1 16:24:53 2014 ribeaud antonin
*/

#include "AObject.hpp"
#include "Core.hpp"
#include "Floor.hpp"
#include "Char.hpp"
#include "Map.hpp"
#include <unistd.h>

Core::Core()
{
	_width = 20;
	_height = 20;
	_map = new Map(_width, _height);
	_players = 1;
	_posx = 1;
	_posy = 1;
	_posx2 = 1;
	_posy2 = 2;
}

Core::~Core()
{
	for (size_t i = 0; i < _objects.size(); ++i)
		delete _objects[i];
	_context.stop();
}

bool	Core::initialize()
{
	if (!_context.start(1800, 1000, "Best Bomberman!"))
		return (false);
	glEnable(GL_DEPTH_TEST);
	if (!_shader.load("./ressources/shaders/basic.fp", GL_FRAGMENT_SHADER) || 
	!_shader.load("./ressources/shaders/basic.vp", GL_VERTEX_SHADER) || 
	!_shader.build())
		return (false);
	if (_players == 1)
		_projection = glm::perspective(60.0f, 1800.0f / 1000.0f, 0.1f, 100.0f);
	else
		_projection = glm::perspective(60.0f, 900.0f / 500.0f, 0.5f, 100.0f);
	_transformation = glm::lookAt(glm::vec3(0, 10, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_shader.bind();
	_shader.setUniform("view", _transformation);
	_shader.setUniform("projection", _projection);
	 if (drawFloor() == false)
	 	return (false);
	if (drawMap() == false)
		return (false);
	if (drawChar() == false)
		return (false);
	if (drawBackground() == false)
		return (false);
	std::cout << "Load done!" << std::endl;
	return (true);
}

bool	Core::drawMap()
{
	std::map< std::pair<int, int>, Case *> map = _map->getCases();
	std::pair<int, int>	pos;

	for (int y(-_height); y <= _height; y++) {
		for (int x(-_width); x <= _width; x++) {
			pos = std::make_pair(x, y);
			if (map[pos] != NULL)
			{
				if (map[pos]->getTypeCase() == 0)
				{
					if (makeCube(x, 0, y) == false)
					return (false);
				}
				else if (map[pos]->getTypeCase() == 1)
				{
					if (makeCube(x, 0, y) == false)
					return (false);
				}
			}
		}
	}
	return (true);
}
void Core::intro()
{
	float i;

	i = 100;
	_shader.bind();
	while (i > 0)
	{
		_transformation = glm::lookAt(glm::vec3(_posy - i, 10 + i, -10 + _posx + i),
		glm::vec3(_posy, 0, _posx + i), glm::vec3(0, 1, 0));
		_shader.setUniform("view", _transformation);
		glViewport(0,0,1800,1000);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_shader.bind();
		for (size_t j = 0; j < _objects.size(); ++j)
		_objects[j]->draw(_shader, _clock);
		_context.flush();
		i--;
		usleep(5000);
	}
}

bool 	Core::drawBackground()
{
	AObject	*background = new	Background(_width * 4, _height * 4, 10.0f);

	_objects.push_back(background);
	return (background->initialize());
}

bool	Core::drawFloor()
{
	AObject	*floor = new	Floor(_width, _height, 10.0f);

	_objects.push_back(floor);
	return (floor->initialize());
}

bool	Core::makeCube(int x, int y, int z)
{
	AObject	*cube = new	Cube;
	if (cube->initialize() == false)
		return (false);
	cube->translate(glm::vec3(x, y, z));
	cube->setPos(x, z);
	_objects.push_back(cube);
	return (true);
}

bool	Core::drawChar()
{
	Char	*Chara = new	Char(_players, 1, _map->getCases());
	_mychar1 = Chara;
	if (_mychar1->initialize() == false)
		return (false);
	_mychar1->setPos(_posx, _posy);
	_mychar1->translate(glm::vec3(_posx, 0, _posy));
	if (_players == 2)
	{
		Char	*Chara = new	Char(_players, 2, _map->getCases());
		_mychar2 = Chara;
		if (_mychar2->initialize() == false)
			return (false);
		_mychar2->setPos(_posx2, _posy2);
		_mychar2->translate(glm::vec3(_posx2, 0, _posy2));
	}
	return (true);
}

void	Core::changeFocus2(Char *cur_char)
{
	cur_char->update(_clock, _input);
	_shader.bind();
	if (_input.getKey(SDLK_z))
		_posx2 += cur_char->getTrans();
	if (_input.getKey(SDLK_s))
		_posx2 -= cur_char->getTrans();
	if (_input.getKey(SDLK_q))
		_posy2 += cur_char->getTrans();
	if (_input.getKey(SDLK_d))
		_posy2 -= cur_char->getTrans();
	glViewport(0,0,1800/2,1000);
	_shader.setUniform("view", glm::lookAt(glm::vec3(_posy2, 13, -10 + _posx2),
	glm::vec3(_posy2, 0, _posx2), glm::vec3(0, 1, 0)));
}

void	Core::changeFocus(Char *cur_char)
{
	cur_char->update(_clock, _input);
	_shader.bind();
	if (_input.getKey(SDLK_UP))
		_posx += cur_char->getTrans();
	if (_input.getKey(SDLK_DOWN))
		_posx -= cur_char->getTrans();
	if (_input.getKey(SDLK_LEFT))
		_posy += cur_char->getTrans();
	if (_input.getKey(SDLK_RIGHT))
		_posy -= cur_char->getTrans();
	if (_players == 1)
	{
		_shader.setUniform("view", glm::lookAt(glm::vec3(_posy, 13, -10 + _posx),
		glm::vec3(_posy, 0, _posx), glm::vec3(0, 1, 0)));
		_shader.setUniform("projection", _projection);
	}
	else
	{
		glViewport(1800/2, 0, 1800/2,1000);
		_shader.setUniform("view", glm::lookAt(glm::vec3(_posy, 13, -10 + _posx),
		glm::vec3(_posy, 0, _posx), glm::vec3(0, 1, 0)));
	}
}

bool	Core::update()
{
	if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
		return false;
	_context.updateClock(_clock);
	_context.updateInputs(_input);
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->update(_clock, _input);
	return true;
}

void	Core::draw()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader.bind();
	changeFocus(_mychar1);
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->draw(_shader, _clock);
	_mychar1->draw(_shader, _clock);
	if (_players == 2)
		{
		_mychar2->draw(_shader, _clock);
		//_context.flush();	
		changeFocus2(_mychar2);
		for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->draw(_shader, _clock);		
		_mychar1->draw(_shader, _clock);
		_mychar2->draw(_shader, _clock);
		}
	_context.flush();
}
