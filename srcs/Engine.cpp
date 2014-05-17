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
  std::string str = "save_file.xml";
  _camera = new Camera(HEIGHT, WIDTH);
  _camera->initScene();
  _loader = new Loader();
  if (_loader->loadTextures() == false)
  	return (false);
  _menu = new Menu(_camera, _loader);
  _core = new Core(_camera, _loader, _menu);
  return (true);
}

void    Engine::save_player()
{
  std::map<int, Player*>  player = _core->getPlayer();
  for (int i = 1; i <= _menu->getNbPlayer(); i++)
  {
    _file << "<player>" << std::endl;
    _file << "\t<id>" << player[i]->getId() << "</id>" << std::endl;
    _file << "\t<life>" << player[i]->getId() << "</life>" << std::endl;
    _file << "\t<range>" << player[i]->getId() << "</range>" << std::endl;
    _file << "\t<stock>" << player[i]->getId() << "</stock>" << std::endl;
    _file << "</player>" << std::endl;

  }
}

void    Engine::save_map()
{
  Map     *map = _core->getMap();
  int     size_x = _core->getMap()->getSize();

  _file << "<map>" << std::endl;
  _file << "\t<size>" << size_x << "</size>" << std::endl;
  for (int y = 0; y < size_x; y++)
    {
      for (int x = 0; x < size_x; x++)
      {
        if (map->getCase(x, y) != NULL)
        {
          type t = map->getCase(x, y)->getType();
          if (t != BOMB && t != BONUS && t != LASER)
          {
            _file << "\t<case>" << y << " " << x << " " << 
            map->getCase(x, y)->getType() << "</case>"<< std::endl;
        }
      }
    }
  }
  save_spawn();
  _file << "</map>" << std::endl;
}

void    Engine::save_spawn()
{
  std::vector<std::pair<int, int> >    obj;

  std::map<int, Player*>  player = _core->getPlayer();
  for (int i = 1; i <= _menu->getNbPlayer(); i++)
  {
    std::pair<int, int> pos = player[i]->getPos();
    _file << "\t<spawn>" << pos.second << " " << pos.first << "</spawn>" << std::endl;
  }
}

void    Engine::saving()
{
  _file.open("save_file.xml");
  _file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
  save_map();
  save_player();
  _file.close();
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
                _core->setValues(_menu->getMap());
                if (_core->initialize())
                {
                    while (_core->update())
                        _core->draw();
                    //saving();
                }
                _menu->reset();
                //_core->reset();
            }
            else
                quit = true;
        }
    }
    return (false);
}
