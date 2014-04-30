/*
** Char.cpp for char in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 21:11:55 2014 Antonin Ribeaud
** Last update Tue Apr  29 21:11:55 2014 Antonin Ribeaud
*/

#include "Char.hpp"

Char::Char(int players, int screen)
{
	_players = players;
	_screen = screen;
}

Char::~Char()
{

}

float	Char::getTrans()
{
	return (_trans);
}

void Char::update(gdl::Clock const &clock, gdl::Input &input)
{
	_trans = static_cast<float>(clock.getElapsed()) * _speed;
	if (input.getKey(SDLK_UP))
		translate(glm::vec3(0, 0, 1) * _trans);
	if (input.getKey(SDLK_DOWN))
		translate(glm::vec3(0, 0, -1) * _trans);
	if (input.getKey(SDLK_LEFT))
		translate(glm::vec3(1, 0, 0) * _trans);
	if (input.getKey(SDLK_RIGHT))
		translate(glm::vec3(-1, 0, 0) * _trans);
	// if (_players == 1)
	// projection = glm::perspective(60.0f, 1800.0f / 1000.0f, 0.1f, 100.0f);
	// _transformation = glm::lookAt(glm::vec3(0, 10, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	// _shader.bind();
	// _shader.setUniform("view", _transformation);
	// _shader.setUniform("projection", projection);

}

void Char::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	(void)clock;
	_texture.bind();
	_geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool	Char::initialize()
{
	_speed = 10.0f;
	if (_texture.load("./ressources/assets/face.tga") == false)
		{
			std::cerr << "Cannot load the cube texture" << std::endl;
			return (false);
		}
	_geometry.setColor(glm::vec4(1, 0, 0, 1));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));

	_geometry.setColor(glm::vec4(1, 1, 0, 1));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));

	_geometry.setColor(glm::vec4(0, 1, 1, 1));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));

	_geometry.setColor(glm::vec4(1, 0, 1, 1));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));

	_geometry.setColor(glm::vec4(0, 1, 0, 1));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));

	_geometry.setColor(glm::vec4(0, 0, 1, 1));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.build();
	return (true);
}