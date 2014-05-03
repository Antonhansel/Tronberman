/*
** Core.cpp for core in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 16:31:08 2014 Antonin Ribeaud
// Last update Thu May  1 16:24:53 2014 ribeaud antonin
*/

#include "Core.hpp"
#include <unistd.h>

Core::Core(Camera cam)
{
	_width = 20;
	_height = 20;
	_cam = cam;
	_map = new Map(_width, _height);
	_players = 1;
	_posx = 1;
	_posy = 1;
	_posx2 = 1;
	_posy2 = 2;
	_percent = 15;
}

Core::~Core()
{
	for (size_t i = 0; i < _objects.size(); ++i)
		delete _objects[i];
	_cam.stopContext();
}

bool 	Core::makeLoading(int percent)
{
	AObject	*cube = new	Cube;
	if (cube->initialize() == false)
		return (false);
	cube->translate(glm::vec3(_percent, 0, 0));
	_loading.push_back(cube);
	return (true);
}

bool 	Core::updateLoading(int perc)
{
	while (perc != 0)
	{
		if (makeLoading(_percent) == false)
			return (false);
		_percent--;
		perc--;
	}
	_cam.moveCameraP1(glm::vec3(0, 10, -15), 
			glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	for (size_t j = 0; j < _loading.size(); ++j)
		_loading[j]->draw(_shader, _clock);
	_cam.flushContext();
	return (true);
}

bool 	Core::drawLoading()
{
	AObject	*loading = new	Loading(_width * 2, _height * 2, 10.0f);

	_loading.push_back(loading);
	loading->translate(glm::vec3(-_percent, 0, 0));
	return (loading->initialize());
}

bool	Core::initialize()
{
	if (_cam.initScene() == false)
		return (false);
	_cam.setPlayer(1);
	_shader = _cam.getShader();
	_clock = _cam.getClock();
	if (drawLoading() == false)
		return (false);
	updateLoading(6);
	if (drawFloor() == false)
	 	return (false);
	updateLoading(6);
	if (drawMap() == false)
		return (false);
	updateLoading(6);
	if (drawChar() == false)
		return (false);
	updateLoading(6);
	if (drawBackground() == false)
		return (false);
	updateLoading(6);
	sleep(1);
	_cam.setPlayer(_players);
	std::cout << "Load done!" << std::endl;
	for (size_t i = 0; i < _loading.size(); ++i)
		delete _loading[i];
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
	while (i > 0)
	{
		_cam.moveCameraP1(glm::vec3(_posy - i, 10 + i, -10 + _posx +i), 
			glm::vec3(_posy, 0, _posx + i), glm::vec3(0, 1, 0));
		for (size_t j = 0; j < _objects.size(); ++j)
			_objects[j]->draw(_shader, _clock);
		i--;
		_cam.flushContext();
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
	if (_input.getKey(SDLK_z))
		_posx2 += cur_char->getTrans();
	if (_input.getKey(SDLK_s))
		_posx2 -= cur_char->getTrans();
	if (_input.getKey(SDLK_q))
		_posy2 += cur_char->getTrans();
	if (_input.getKey(SDLK_d))
		_posy2 -= cur_char->getTrans();
	_cam.moveCameraP1(glm::vec3(_posy2, 13, -10 + _posx2), 
		glm::vec3(_posy2, 0, _posx2), glm::vec3(0, 1, 0));
}

void	Core::changeFocus(Char *cur_char)
{
	cur_char->update(_clock, _input);
	if (_input.getKey(SDLK_UP))
		_posx += cur_char->getTrans();
	if (_input.getKey(SDLK_DOWN))
		_posx -= cur_char->getTrans();
	if (_input.getKey(SDLK_LEFT))
		_posy += cur_char->getTrans();
	if (_input.getKey(SDLK_RIGHT))
		_posy -= cur_char->getTrans();
	_cam.moveCameraP1(glm::vec3(_posy, 13, -10 + _posx), 
		glm::vec3(_posy, 0, _posx), glm::vec3(0, 1, 0));
}

bool	Core::update()
{
	if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
		return false;
	_clock = _cam.getClock();
	_input = _cam.getInput();
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->update(_clock, _input);
	return true;
}

void	Core::draw()
{	
	changeFocus(_mychar1);
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->draw(_shader, _clock);
	_mychar1->draw(_shader, _clock);
	if (_players == 2)
		{
		_mychar2->draw(_shader, _clock);
		changeFocus2(_mychar2);
		for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->draw(_shader, _clock);		
		_mychar1->draw(_shader, _clock);
		_mychar2->draw(_shader, _clock);
		}
	_cam.flushContext();
}
