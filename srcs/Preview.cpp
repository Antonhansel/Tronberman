/*
** Preview.cpp for Preview in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue May  20 11:00:02 2014 Antonin Ribeaud
** Last update Tue May  20 11:00:02 2014 Antonin Ribeaud
*/

#include "Preview.hpp"
#include "Saving.hpp"
#include <sys/types.h>
#include <dirent.h>

Preview::Preview(Camera *camera, Loader *loader)
{
	_camera = camera;
	_loader = loader;
	_angle = 0;
	_posy = 20;
	_posx = 0;
	_posz = -30;
	_time = 1;
}

Preview::~Preview()
{
}

bool 		Preview::checkName(const char *str1)
{
	std::string pp = "..";
	std::string p = ".";
	std::string tocheck = str1;

	if (pp == str1 || p == str1)
		return (false);
	return (true);
}

std::string 	Preview::makePath(const char *str1)
{
	std::string path = PATH;

	path += str1;
	return (path);
}

void 		Preview::getPaths()
{
	DIR 			*mydir;
	struct dirent 	*currentdir;
	mydir = opendir(PATH);
	while ((currentdir = readdir(mydir)) != NULL)
	{
		if (checkName(currentdir->d_name) && 
			checkName(currentdir->d_name))
		_paths.push_back(makePath(currentdir->d_name));
	}
}

bool		Preview::initialize()
{
	getPaths();
	Saving _saving(_paths);
	_maps = _saving.getListMap();
	std::cout << "PREVIEW STARTED" << std::endl;
	if (_maps.size() == 0)
		return (false);
	_it = _maps.begin();
	_map = (*_it);
    _xend = _map->getSize()/2;
	return (true);
}

void 		Preview::changeMap(int i)
{
	if (i == 1)
	{
		_it++;
		if (_it == _maps.end())
			_it = _maps.begin();
	}
	else if (i == -1)
	{
		if (_it == _maps.begin())
		{
			_it = _maps.end();
			_it--;
		}
		else
			_it--;
	}
    _map = (*_it);
    _xend = _map->getSize()/2;
}

bool		Preview::update(gdl::Clock const &clock, gdl::Input &input)
{

	_time += clock.getElapsed();
	if (_time > 0.1)
	{
		_time = 0;
		if (input.getInput(SDLK_LEFT))
			changeMap(-1);
		else if (input.getInput(SDLK_RIGHT))
			changeMap(1);
	}
	return (true);
}

void 		Preview::setCameraAngle()
{
  _angle = _angle + 0.2;
  if (_angle > 360)
    _angle = 0;
 	//_angle = 75;
  _posx = cos((_angle/180) * PI) * 30 + _xend;
  _posz = sin((_angle/180) * PI) * 30 + _xend;
  _camera->moveCamera(vec3(_posx + _xend, _posy, _posz - _xend/8), vec3(_xend, 0,_xend), vec3(0,1,0), 3);
}

void		Preview::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  	type LastType = static_cast<type>(-1);
  	AObject     *tmp;

  	_camera->previewMode(true);
	setCameraAngle();
	for (int x = 0; x < _map->getSize(); ++x)
  	{
	    for (int y = 0; y < _map->getSize(); ++y)
	    {
		  tmp = _map->getCase(x, y);
		 	if (tmp)
		 	{
		  	if (tmp->getType() != LastType)
		      {
		        LastType = tmp->getType();
		        _loader->bindTexture(LastType);
		      }
		   	_loader->drawGeometry(shader, tmp->getTransformation());
			}
		}
	}
  _camera->previewMode(false);
}

Map 	*Preview::getMap() const
{
	return (_map);
}