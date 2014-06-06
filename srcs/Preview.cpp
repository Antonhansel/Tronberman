/*
** Preview.cpp for Preview in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue May  20 11:00:02 2014 Antonin Ribeaud
** Last update Tue May  20 11:00:02 2014 Antonin Ribeaud
*/

#include <sys/types.h>
#include <dirent.h>
#include "Preview.hpp"

Preview::Preview(Camera *camera, Loader *loader)
{
	_camera = camera;
	_loader = loader;
	//_text = new Text(_camera, _loader);
	_angle = 0;
	_posy = 20;
	_posx = 0;
	_posz = -30;
	_time = 1;
	_state = true;
}

Preview::~Preview()
{}

bool 		Preview::checkName(const char *str1)
{
	std::string pp = "..";
	std::string p = ".";
	std::string tocheck = str1;

	if (pp == str1 || p == str1)
		return (false);
	return (true);
}

std::string 	Preview::makePath(const char *str1, const char *p)
{
	std::string path = p;

	path += str1;
	return (path);
}

void 		Preview::getPaths(const char * path)
{
	DIR 			*mydir;
	struct dirent 	*currentdir;
	mydir = opendir(path);
	_paths.clear();
	if (mydir != NULL)
		while ((currentdir = readdir(mydir)) != NULL)
		{
			if (checkName(currentdir->d_name) &&
				checkName(currentdir->d_name))
			_paths.push_back(makePath(currentdir->d_name, path));
		}
}

bool		Preview::initialize()
{
	_save.clear();
	getPaths(PATH);
	for (std::vector<std::string>::const_iterator it = _paths.begin(); it != _paths.end(); ++it)
	{
		Saving *s = new Saving((*it));
		if (s->getSavedGame())
			_save.push_back(s);
	}
	_maps = Saving::getMapList(_save);
	if (_maps->size() == 0)
	{
		_state = false;
		_result = false;
		return (false);		
	}
	_it = _maps->begin();
	_map = (*_it);
    _xend = _map->getSize() / 2;
    _state = false;
    _result = true;
	return (true);
}

bool		Preview::initializeSave()
{
	_save.clear();
	getPaths(SAVE);
	for (std::vector<std::string>::const_iterator it = _paths.begin(); it != _paths.end(); ++it)
	{
		Saving *s = new Saving((*it));
		if (s->getSavedGame())
			_save.push_back(s);
	}
	_maps = Saving::getMapList(_save);
	_players = Saving::getPlayerList(_save);
	if (_maps->size() == 0)
	{
		_state = false;
		_result = false;
		return (false);
	}
	_it = _maps->begin();
	_map = (*_it);
	_itPlayer = _players->begin();
    _xend = _map->getSize() / 2;
    _result = true;
    _state = false;
	return (true);
}

void 		Preview::changeMap(int i)
{
	if (i == 1)
	{
		_it++;
		if (_it == _maps->end())
			_it = _maps->begin();
	}
	else if (i == -1)
	{
		if (_it == _maps->begin())
		{
			_it = _maps->end();
			_it--;
		}
		else
			_it--;
	}
    _map = (*_it);
    _xend = _map->getSize()/2;
}

void 		Preview::changeMapSave(int i)
{
	if (i == 1)
	{
		_it++;
		_itPlayer++;
		if (_it == _maps->end())
		{
			_it = _maps->begin();
			_itPlayer = _players->begin();
		}
	}
	else if (i == -1)
	{
		if (_it == _maps->begin())
		{
			_it = _maps->end();
			_it--;
			_itPlayer = _players->begin();
			_itPlayer--;
		}
		else
		{
			_itPlayer--;
			_it--;
		}
	}
    _map = (*_it);
    _xend = _map->getSize()/2;
}

bool		Preview::update(gdl::Clock const &clock, gdl::Input &input, bool isSave)
{

	_time += clock.getElapsed();
	if (_time > 0.1)
	{
		_time = 0;
		if (input.getInput(SDLK_LEFT))
		{
			if (!isSave)
				changeMap(-1);
			else
				changeMapSave(-1);
		}
		else if (input.getInput(SDLK_RIGHT))
		{
			if (!isSave)
				changeMap(1);
			else
				changeMapSave(1);
		}
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
	return ((_maps->size() == 0) ? NULL : _map);
}

Saving	*Preview::getInstance()
{
	if (_save.size() > 0)
	{
		for (std::vector<Saving *>::iterator it = _save.begin(); it != _save.end(); ++it)
		{
			if ((*it)->getMap()->getName().compare(_map->getName()) == 0)
				return (*it);
		}
	}
	return (NULL);
}

bool	Preview::getState() const
{
	return (_state);
}

void 	Preview::setState(bool b)
{
	_state = b;
}

bool	Preview::getResult() const
{
	return (_result);
}