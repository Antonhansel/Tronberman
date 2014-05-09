//
// Engine.hpp for Engine in /home/chouag_m/rendu/old
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sat May  3 17:16:52 2014 Mehdi Chouag
// Last update Sat May  3 21:40:49 2014 Mehdi Chouag
//

#ifndef ENGINE_HPP_
# define ENGINE_HPP_

#include "Camera.hpp"
#include "Menu.hpp"
#include "Core.hpp"
#include "Loader.hpp"

#define WIDTH	1000
#define HEIGHT	1800

class Engine
{
public:
  Engine();
  ~Engine();
  bool		start();
  bool 		init();
private:
  Engine(const Engine&);
  Engine &operator=(const Engine &);
  
private:
  Camera	*_camera;
  Core		*_core;
  Menu		*_menu;
  Loader 	*_loader;
};

#endif /* !ENGINE_HPP_ */
