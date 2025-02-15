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
	_text = new Text(_camera, _loader);
	_text->addText(_big, 0, std::make_pair(100, 300), "Map is too big for the preview", true);
	_text->addText(_big, 0, std::make_pair(100, 380), "SIZE   :", true);
	_text->addText(_big, 0, std::make_pair(100, 460), "PLAYER :", true);
	_angle = 0;
	_posy = 20;
	_posx = 0;
	_posz = -30;
	_time = 1;
	_state = true;
}

void		Preview::resetText()
{
	_text->deleteAllText(_nb);
	_text->addText(_nb, 0, std::make_pair(550, 380), _nbSize.c_str(), true);
	_text->addText(_nb, 0, std::make_pair(550, 460), _nbPlayer.c_str(), true);	
}

Preview::~Preview()
{
	_text->deleteAllText(_big);
	_text->deleteAllText(_nb);
	if (_text != NULL)
		delete _text;
}

bool		Preview::clearMap()
{
	if (_save.size() > 0)
	{
		for (std::vector<Saving *>::iterator it = _save.begin(); it != _save.end(); )
		{
			delete (*it);
			it = _save.erase(it);
		}
		_save.clear();
	}
	return (true);
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

void 		Preview::changeMap(const int i)
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

void 		Preview::changeMapSave(const int i)
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
			_itPlayer = _players->end();
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

bool		Preview::update(gdl::Clock const &clock, gdl::Input &input, const bool isSave)
{
	std::stringstream ss;

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
	if (isSave && (*_it)->getSize() > 50)
	{
		ss << _map->getSize();
	    _nbSize = ss.str();
	    ss.str("");
	    ss.clear();
		ss << _itPlayer->size();
		_nbPlayer = ss.str();
		resetText();
	}
	return (true);
}

void 		Preview::setCameraAngle()
{
  _angle = _angle + 0.2;
  if (_angle > 360)
    _angle = 0;
  _posx = cos((_angle/180) * PI) * 30 + _xend;
  _posz = sin((_angle/180) * PI) * 30 + _xend;
  _camera->moveCamera(vec3(_posx + _xend, _posy, _posz - _xend/8), vec3(_xend, 0,_xend), vec3(0,1,0), 3);
}

void		Preview::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  	type LastType = static_cast<type>(-1);
  	AObject     *tmp;

  	if (_map->getSize() <= 50)
  	{
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
	else
	{
		_text->draw(_big, 1);
		_text->draw(_nb, 1);
	}
}

Map 	*Preview::getMap() const
{
	return ((_maps->size() == 0) ? NULL : _map);
}

Saving	*Preview::getInstance() const
{
	if (_save.size() > 0)
	{
		for (std::vector<Saving *>::const_iterator it = _save.begin(); it != _save.end(); ++it)
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

void 	Preview::setState(const bool b)
{
	_state = b;
}

bool	Preview::getResult() const
{
	return (_result);
}