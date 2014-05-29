//
// Engine.cpp for engine  in /home/chouag_m/rendu/old
//
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
//
// Started on  Sat May  3 17:15:50 2014 Mehdi Chouag
// Last update Sun May  4 03:13:24 2014 Mehdi Chouag
//

#include "Engine.hpp"

Engine::Engine()
{
}

Engine::~Engine()
{
  delete _camera;
  delete _menu;
  delete _core;
  delete _loader;
  delete _engine;
}

bool 		Engine::init()
{
  glm::vec3 vec;

  _camera = new Camera(HEIGHT, WIDTH);
  _camera->initScene();
  _loader = new Loader();
  _engine = new ParticleEngine(_loader);
  vec = glm::vec3(1, 1, 1);
  _engine->spawnParticles(vec);
  if (_loader->loadTextures() == false)
  	return (false);
  _menu = new Menu(_camera, _loader, _engine);
  _core = new Core(_camera, _loader, _menu, _engine);
  return (true);
}

bool		Engine::start()
{
    bool		quit(false);

    if (_menu->initialize())
    {
        while (!quit)
        {
            while (_menu->update() == true)
                _menu->draw();
            if (_menu->launch() == true)
            {
              if (_menu->isSave())
                _core->setSave(_menu->getMap(), _menu->getPlayer());
              else
                _core->setValues(_menu->getMap());
              if (_core->initialize())
              {
                  while (_core->update())
                    _core->draw();
                _menu->reset(_core->getPlayer());
                _core->reset();
              }
            }
            else
              quit = true;
        }
    }
    return (false);
}
