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
# include "AObject.hpp"
# include "Floor.hpp"
# include "Cube.hpp"
# include "Char.hpp"

class Core : public gdl::Game
{
public:
	Core();
	~Core();
	bool	initialize();
	bool	update();
	void	draw();
	bool	makeCube(int, int, int);
	bool 	drawWall();
	bool	drawFloor();
	bool	drawLimits();
	bool	drawChar();
	void	changeFocus();
private:
	Char				*_mychar;
	float 				_posx;
	float				_posy;
	glm::mat4			_transformation;
	float				_width;
	float				_height;
	gdl::SdlContext		_context;
	gdl::Clock			_clock;
	gdl::Input			_input;
	gdl::BasicShader	_shader;
	std::vector<AObject*> _objects;
};

#endif /*!_CORE_HPP_*/