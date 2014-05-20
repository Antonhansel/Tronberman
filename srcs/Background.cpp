/*
** Floor.cpp for Floor in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 18:52:58 2014 Antonin Ribeaud
** Last update Tue Apr  29 18:52:58 2014 Antonin Ribeaud
*/

#include "Background.hpp"

Background::Background(float width, float height, float speed)
{
	_width = width;
	_height = height;
	_speed = speed;
	_dir = true;
	_spin = 0;
	_x = 30;
	_z = 100;
}

void Background::update(gdl::Clock const &clock, gdl::Input &input)
{
	if (_dir)
		_spin++;
	else
		_spin--;
	if (_spin == 100)
		_dir = false;
	else if (_spin == -100)
		_dir = true;
	rotate(glm::vec3(_x + _spin/100, _spin/100, _z + _spin/100));
}

void Background::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	(void)clock;
	_texture.bind();
	_geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool	Background::initialize()
{
	if (_texture.load("./ressources/assets/test.tga") == false)
	{
		std::cerr << "Cannot load the floor texture" << std::endl;
		return (false);
	}
  _geometry.setColor(glm::vec4(1, 1, 0, 1));
    _geometry.pushVertex(glm::vec3(-_height, _width, -0.5));
  _geometry.pushVertex(glm::vec3(-_height, -_width, -0.5));
  _geometry.pushVertex(glm::vec3(_height, -_width, -0.5));
  _geometry.pushVertex(glm::vec3(_height, _width, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
	return (true);
}

Background::~Background()
{

}