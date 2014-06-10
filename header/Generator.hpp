/*
** Generator.hpp for Generator in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Sat May  17 06:24:37 2014 Antonin Ribeaud
** Last update Sat May  17 06:24:37 2014 Antonin Ribeaud
*/

#ifndef _GENERATOR_HPP_
# define _GENERATOR_HPP_

# include "Camera.hpp"
# include "AObject.hpp"
# include "Loader.hpp"
# include "Factory.hpp"
# include "Floor.hpp"
# include "AInput.hpp"

class Generator
{
public:
	Generator(Camera *, Loader *, const int);
	~Generator();
	bool 	initialize();
	bool 	initCursor(const int, const int);
	bool 	drawBackground();
	bool 	cleanObjects(const int);
	bool 	update();
	void 	draw();
	bool 	changeSize(const key &);
	void 	changeType(const key &);
	void 	placeCube(const key &);
	void 	moveCursor(const key &);

private:
	AObject			*_cube;
	Camera 			*_camera;
	Loader 			*_loader;
	int 			_size;
	Map				*_map;
	Clock			_clock;
  	Input			_input;
  	BasicShader		_shader;
  	AObject			*_floor;
  	double 			_time;
  	AInput			*_ainput;
  	std::vector<key>				_k;
};

#endif /*_GENERATOR_HPP_*/