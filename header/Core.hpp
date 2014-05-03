/*
** core.hpp for Core in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:35:37 2014 Antonin Ribeaud
** Last update Mon Apr  28 13:35:37 2014 Antonin Ribeaud
*/

#ifndef _CORE_HPP_
# define _CORE_HPP_

# include <Game.hh> 
# include <Clock.hh> 
# include <Input.hh> 
# include <SdlContext.hh> 
# include <Geometry.hh> 
# include <Texture.hh> 
# include <Model.hh> 
# include <glm/glm.hpp>
# include <BasicShader.hh>
# include <glm/gtc/matrix_transform.hpp>
# include <OpenGL.hh>
# include <vector>
# include <iostream>
# include "Camera.hpp"
# include "Loading.hpp"
# include "Background.hpp"
# include "AObject.hpp"
# include "Floor.hpp"
# include "Cube.hpp"
# include "Char.hpp"
# include "Map.hpp"

class Core : public gdl::Game
{
public:
	Core(Camera cam);
	~Core();
	bool			initialize();
	void			draw();
	bool			makeCube(int, int, int);
	bool			drawFloor();
	bool			drawMap();
	bool			drawChar();
	bool			drawBackground();
	void			changeFocus(Char *cur_char);
	void			changeFocus2(Char *cur_char);
	void			intro();
	bool 			update();
	bool 			drawLoading();
	bool 			updateLoading(int);
	bool 			makeLoading(int);
private:
	int 			_percent;
	Camera 			_cam;
	int 			_players;
	Char			*_mychar1;
	Char 			*_mychar2;
	float 			_posx;
	float			_posy;
	float			_posx2;
	float			_posy2;
	int				_width;
	int				_height;
	Map				*_map;
	gdl::Clock		_clock;
	gdl::Input		_input;
	gdl::BasicShader	_shader;
	std::vector<AObject*> _objects;
	std::vector<AObject*> _loading;
};

#endif /*!_CORE_HPP_*/