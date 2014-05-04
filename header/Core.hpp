/*
** core.hpp for Core in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:35:37 2014 Antonin Ribeaud
// Last update Sun May  4 02:22:46 2014 Mehdi Chouag
*/

#ifndef _CORE_HPP_
# define _CORE_HPP_

# include <Game.hh> 
# include <Clock.hh> 
# include <Input.hh> 
# include <SdlContext.hh> 
# include <Geometry.hh> 
# include <Texture.hh> 
# include <Model.hh> 
# include <glm/glm.hpp>
# include <BasicShader.hh>
# include <glm/gtc/matrix_transform.hpp>
# include <OpenGL.hh>
# include <vector>
# include <iostream>
# include <map>
# include "Camera.hpp"
# include "Loading.hpp"
# include "Background.hpp"
# include "AObject.hpp"
# include "Floor.hpp"
# include "Cube.hpp"
# include "Char.hpp"
# include "Map.hpp"
# include "Factory.hpp"

#define POSX 0
#define POSY 0

#define POSX1 1
#define POSY1 1


class Core : public gdl::Game
{
public:
  Core(Camera *cam);
  ~Core();
  bool			initialize();
  void			draw();
  bool			drawFloor();
  bool			drawMap();
  bool			drawChar();
  bool			drawBackground();
  void			changeFocus(AObject *);
  void			changeFocus2(AObject *);
  void			intro();
  bool 			update();

private:
  int 			_percent;
  Camera 		*_cam;
  int 			_players;
  float 		_posx;
  float			_posy;
  float			_posx2;
  float			_posy2;
  int			_width;
  int			_height;
  Map		        *_map;
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::BasicShader	_shader;
  std::map< std::pair<float, float>, AObject* > _objects;
  std::map<int, AObject*>	_player;
  std::vector<AObject*> _loading;
  std::vector<AObject*>	_other;
};

#endif /*!_CORE_HPP_*/
