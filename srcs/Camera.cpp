/*
** Camera.cpp for Camera in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 19:25:38 2014 Antonin Ribeaud
// Last update Mon May  5 15:01:09 2014 charly roche
*/

#include "Camera.hpp"

Camera::Camera(const int width, const int height)
{
  _players = 1;
  _width = width;
  _height = height;
}

Camera::~Camera()
{}

void 	Camera::setPlayer(int players)
{
  _players = players;
  if (_players == 1)
    _projection = perspective(60.0f, (float)_width / (float)_height, 0.1f, 100.0f);
  else
    _projection = perspective(60.0f, ((float)_width/2) / (float)_height, 0.1f, 100.0f);
  _shader.bind();
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);
}

bool	Camera::initScene()
{
  if (!_context.start(_width, _height, "Best Bomberman!"))
    return (false);
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./ressources/shaders/basic.fp", GL_FRAGMENT_SHADER) || 
      !_shader.load("./ressources/shaders/basic.vp", GL_VERTEX_SHADER) || 
      !_shader.build())
    return (false);
  if (_players == 1)
    _projection = perspective(60.0f, (float)_width / (float)_height, 0.1f, 100.0f);
  else
    _projection = perspective(60.0f, ((float)_width / 2.0f) / ((float)_height / 2.0f), 0.5f, 100.0f);
  _transformation = lookAt(vec3(0, 10, -10), vec3(0, 0, 0), vec3(0, 1, 0));
  _shader.bind();
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);
  return (true);
}

void 	Camera::flushContext()
{
  _context.flush();
}

void 	Camera::moveCamera(vec3 vec1, vec3 vec2, vec3 vec3, int screen)
{
  if (_players == 1)
  {
    glViewport(0, 0, _width, _height);
  }
  else
  {
    if (screen == 1)
      glViewport(_width/2, 0, _width/2, _height);
    else
      glViewport(0,0,_width/2, _height);
  }
  if (_players == 1 || (_players == 2 && screen == 1))
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _transformation = lookAt(vec1, vec2, vec3);
  _shader.setUniform("view", _transformation);
  _shader.bind();
}
  
BasicShader &Camera::getShader()
{
  return (_shader);
}

Clock &Camera::getClock()
{
  _context.updateClock(_clock);
  return (_clock);
}

Input &Camera::getInput()
{
  _context.updateInputs(_input);
  return (_input);
}

void 	Camera::stopContext()
{
  _context.stop();
}
