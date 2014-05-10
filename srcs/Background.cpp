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
}

void Background::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void Background::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	(void)clock;
	_texture.bind();
	_geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool	Background::initialize()
{
	if (_texture.load("./ressources/assets/bg.tga") == false)
	{
		std::cerr << "Cannot load the floor texture" << std::endl;
		return (false);
	}
	_geometry.setColor(glm::vec4(1, 1, 1, 1));
	_geometry.pushVertex(glm::vec3(_width, -0.5, -_height));
	_geometry.pushVertex(glm::vec3(_width, -0.5, _height));
	_geometry.pushVertex(glm::vec3(-_width, -0.5, _height));
	_geometry.pushVertex(glm::vec3(-_width, -0.5, -_height));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.build();
	translate(glm::vec3(0, -10, 0));
	return (true);
}

Background::~Background()
{

}