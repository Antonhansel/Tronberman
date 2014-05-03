/*
** Camera.cpp for Camera in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 19:25:38 2014 Antonin Ribeaud
** Last update Fri May  02 19:25:38 2014 Antonin Ribeaud
*/

#include "Camera.hpp"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void 	Camera::setPlayer(int players)
{
	_players = players;
}

bool	Camera::initScene()
{
	if (!_context.start(1800, 1000, "Best Bomberman!"))
	 	return (false);
	glEnable(GL_DEPTH_TEST);
	if (!_shader.load("./ressources/shaders/basic.fp", GL_FRAGMENT_SHADER) || 
	!_shader.load("./ressources/shaders/basic.vp", GL_VERTEX_SHADER) || 
	!_shader.build())
		return (false);
	if (_players == 1)
		_projection = glm::perspective(60.0f, 1800.0f / 1000.0f, 0.1f, 100.0f);
	else
		_projection = glm::perspective(60.0f, 900.0f / 500.0f, 0.5f, 100.0f);
	_transformation = glm::lookAt(glm::vec3(0, 10, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_shader.bind();
	_shader.setUniform("view", _transformation);
	_shader.setUniform("projection", _projection);
	return (true);	
}

bool 	Camera::flushContext()
{
	_context.flush();
}

bool 	Camera::moveCameraP1(glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3)
{
	if (_players == 1)
	{
		glViewport(0,0,1800,1000);
		_transformation = glm::lookAt(vec1, vec2, vec3);
		_shader.setUniform("view", _transformation);
	}
	else
	{
		glViewport(1800/2, 0, 1800/2,1000);
		_transformation = glm::lookAt(vec1, vec2, vec3);
		_shader.setUniform("view", _transformation);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader.bind();
}

bool 	Camera::moveCameraP2(glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3)
{
	glViewport(0,0,1800/2,1000);
	_shader.setUniform("view", glm::lookAt(vec1, vec2, vec3));
	_shader.setUniform("view", _transformation);
}

gdl::BasicShader &Camera::getShader()
{
	return (_shader);
}

gdl::Clock &Camera::getClock()
{
	_context.updateClock(_clock);
	return (_clock);
}

gdl::Input &Camera::getInput()
{
	_context.updateInputs(_input);
	return (_input);
}

void 	Camera::stopContext()
{
	_context.stop();
}
