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
}

bool 		Engine::init()
{
  _camera = new Camera(HEIGHT, WIDTH);
  _loader = new Loader();
  if (_loader->loadTextures() == false)
  	return (false);
  _menu = new Menu(_camera);
  _core = new Core(_camera);
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
	      // getter depuis le menu
	      // setter vers core
	      std::cout << "LAUNCHING THE MENU" << std::endl;
	        if (_core->initialize())
	    	{
	    	  while (_core->update())
	    	    _core->draw();		  
	    	}
		_menu->reset();
		//	      _core->reset();
	    }
	  else
	    quit = true;
	}
    }
  return (false);
}
