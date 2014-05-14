/*
** Camera.cpp for Camera in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 19:25:38 2014 Antonin Ribeaud
// Last update Tue May 13 20:05:19 2014 Mehdi Chouag
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

void  Camera::setMode()
{
  if (_mode == 1)
    {
      _projection = glm::ortho(0.0f, (float)_width, (float)_height, 0.0f, -1.0f, 1.0f);
      _shader.bind();
      _shader.setUniform("view", glm::mat4(1));
      _shader.setUniform("projection", _projection);
      _mode = 0;  
    }
  else
    {
      _projection = perspective(60.0f, ((float)_width/2) / (float)_height, 0.1f, 100.0f);
      _shader.bind();
      _shader.setUniform("view", _transformation);
      _shader.setUniform("projection", _projection);
      _mode = 1;
    }
}

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
    GLfloat LightAmbient[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat LightPosition[] = { 0.0f, 0.0f, 1000.0f, 1.0f };
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
  glEnable(GL_LIGHT1);
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
  _mode = 1;
  _shader.bind();
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);
  // float LightPos[4]={0,0,0,1};
  // glLightfv(GL_LIGHT0,GL_SPECULAR,LightPos);
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

std::pair<float, float>  Camera::genPos(Player *player1, Player *player2)
{
  std::pair<float, float> pos;

  pos.first = (player1->getPos().first + player2->getPos().first)/2;
  pos.second = (player1->getPos().second + player2->getPos().second)/2;
  pos.second -= 2;
  return (pos);
}

void  Camera::changeFocus(AObject *cur_char, int screen)
{
  moveCamera(glm::vec3(cur_char->getPos().first, 13, -10 + cur_char->getPos().second),
    glm::vec3(cur_char->getPos().first, 0, cur_char->getPos().second), glm::vec3(0, 1, 0), screen);
}

int  Camera::genSplit(Player *player1, Player *player2)
{
  float   pos1;
  float   pos2;

  if (player1->getPos().first > player2->getPos().first)
    pos1 = player1->getPos().first - player2->getPos().first;
  else
    pos1 = player2->getPos().first - player1->getPos().first;
  if (player1->getPos().second > player2->getPos().second)
    pos2 = player1->getPos().second - player2->getPos().second;
  else
    pos2 = player2->getPos().second - player1->getPos().second;
  if (pos1 > 20 || pos2 > 20)
  {
    setPlayer(2);
    return (0);
  }
  else
  {
    setPlayer(1);
    return (1);
  }
}
