/*
** Intro.hpp for intro in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 12:53:12 2014 Antonin Ribeaud
** Last update Thu May  01 12:53:12 2014 Antonin Ribeaud
*/

/*
** core.hpp for Core in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:35:37 2014 Antonin Ribeaud
** Last update Mon Apr  28 13:35:37 2014 Antonin Ribeaud
*/

#ifndef _INTRO_HPP_
# define _INTRO_HPP_

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
# include "Background.hpp"
# include "AObject.hpp"
# include "Floor.hpp"
# include "Cube.hpp"
# include "Char.hpp"

class Intro : public gdl::Game
{
public:
	Intro();
	~Intro();
	bool			initialize();
	bool			update();
	void			draw();
	bool			makeCube(int, int, int);
	bool			drawLimits();
private:
	glm::mat4			_transformation;
	glm::mat4			_projection;
	float				_width;
	float				_height;
	gdl::SdlContext		_context;
	gdl::Clock			_clock;
	gdl::Input			_input;
	gdl::BasicShader	_shader;
	std::vector<AObject*> _objects;
};

#endif /*!_INTRO_HPP_*/