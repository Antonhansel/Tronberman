/*
** core.hpp for Core in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:35:37 2014 Antonin Ribeaud
// Last update Sat May 10 22:38:13 2014 Mehdi Chouag
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
# include <math.h>
# include "Camera.hpp"
# include "Loading.hpp"
# include "Background.hpp"
# include "AObject.hpp"
# include "Floor.hpp"
# include "Cube.hpp"
# include "Char.hpp"
# include "Map.hpp"
# include "Factory.hpp"
# include "Loader.hpp"
# include "Bombs.hpp"
# include "Sound.hpp"

#define POSX 0
#define POSY 0

#define POSX1 1
#define POSY1 0

enum cinput
{
  NONE = 0,
  P1UP,
  P1DOWN,
  P1RIGHT,
  P1LEFT,
  P1BOMB,
  P2UP,
  P2DOWN,
  P2RIGHT,
  P2LEFT,
  P2BOMB 
};

class Core : public gdl::Game
{
public:
  Core(Camera *cam, Loader *loader);
  ~Core();
  bool			initialize();
  void			draw();
  bool			drawFloor();
  bool			drawMap();
  bool			drawChar();
  bool      drawBot();
  bool			drawBackground();
  void			changeFocus(AObject *, int);
  bool 			update();
  void      drawAll(AObject *);
  bool      makeChar(int, int, int);
  bool      makeBomb(Player *);
  void			bombExplode();
  void			removeExplosion();
  void			explosion(std::pair<float, float>, int);
  void			newBomb(std::pair<float, float>&);
  std::pair<float, float> genPos();
private:
  int       _screen;
  float     _dist;
  int 			_percent;
  Camera 		*_cam;
  Loader    *_loader;
  int 			_players;
  float 		_posx;
  float			_posy;
  float			_posx2;
  float			_posy2;
  int			_width;
  int			_height;
  Map		        *_map;
  Sound			*_sound;
  gdl::Clock		_clock;
  gdl::Input		_input;
  double        _time;
  gdl::BasicShader	_shader;
  std::map< std::pair<float, float>, AObject* > _objects;
  std::map< double, std::pair< int, AObject* > > _bombs;
  std::vector< std::pair<double, AObject*> > _explosion;
  std::map<type, gdl::Texture*> _textures;
  std::map<int, Player*>	_player;
  std::vector<AObject*> _loading;
  std::vector<AObject*>	_other;
};

#endif /*!_CORE_HPP_*/
