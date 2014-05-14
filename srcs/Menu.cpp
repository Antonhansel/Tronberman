/*
** Intro.cpp for Intro in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 12:48:21 2014 Antonin Ribeaud
// Last update Wed May 14 01:50:17 2014 Mehdi Chouag
*/

#include "Menu.hpp"
#include "CubeAnim.hpp"

Menu::Menu(Camera *camera, Loader *loader) : _camera(camera)
{
  _camera->setPlayer(1);
  _loader = loader;
  _shader = _camera->getShader();
  _clock = _camera->getClock();
  _text = new Text(_camera);
  _players = 1;
  _isLaunch = false;
  _cubeanim = new CubeAnim(camera, loader);
}

Menu::~Menu()
{
  delete _text;
  delete _background;
}

bool  Menu::drawBackground()
{
  _background = new Background(130, 130, 10.0f);
  if (_background->initialize() == false)
    return (false);
  _background->translate(glm::vec3(0, 0, 20));
  _background->rotate(glm::vec3(30, 0, 100));
  return (true);
}

bool	Menu::initialize()
{ 
  if (_cubeanim->initIntro() == false)
    return (false);
  if (drawBackground() == false)
    return (false);
  std::cout << "Menu init ended" << std::endl;
  return (true);
}

bool    Menu::update()
{
  _camera->setPlayer(1);
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return (false);
  if (_isLaunch == true)
    return (false);
  _clock = _camera->getClock();
  _input = _camera->getInput();
  _cubeanim->update();
  return (true);
}

void    Menu::draw()
{
  type LastType = BLOCKD;

  if (_input.getKey(SDLK_p))
    {
      _isLaunch = true;
      _cubeanim->changeVolum(0.4f);
    }
  if (_input.getKey(SDLK_SPACE))
    {
      _cubeanim->stopIntro(true);
      _text->setShow(true);
    }
  _cubeanim->rotate();
  _loader->bindTexture(LastType);
  _cubeanim->draw(_shader, LastType);
  if (_cubeanim->getStatus())
    _background->draw(_shader, _clock);
  _text->draw(_shader, _clock);
  _camera->flushContext();
}

void    Menu::reset()
{
  _isLaunch = false;
}

bool    Menu::launch() const
{
  return (_isLaunch);
}