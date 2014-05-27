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

# include "Camera.hpp"
# include "Background.hpp"
# include "AObject.hpp"
# include "Floor.hpp"
# include "Map.hpp"
# include "Factory.hpp"
# include "Loader.hpp"
# include "Bombs.hpp"
# include "Sound.hpp"
# include "Hud.hpp"
<<<<<<< HEAD
# include  "AInput.hpp"
=======
# include "Particles.hpp"
>>>>>>> 0afb239c368754c93b52578c67c19aae8b850c2a

# define PATH "./ressources/maps/"

class Menu;
class Player;

class Core : public gdl::Game
{
public:
  Core(Camera *cam, Loader *loader, Menu *menu);
  ~Core();
  bool			initialize();
  void			draw();
  bool			drawFloor();
  bool			drawChar();
  bool      drawBot(int);
  bool			drawBackground();
  bool 			update();
  void      drawAll(AObject *);
  bool      makeChar(int, int, int);
  bool      makeBot(int, int, int);
  void      FPS();
  void      checkAlive();
  void      spawnBomb(Player *);
  Map       *getMap();
  std::map<int, Player*>  getPlayer();
  void      setValues(Map *map);
  void      reset();
private:
  bool      _displayFPS;
  int       _screen;
  Hud       *_hud;
  Menu      *_menu;
  Camera 		*_cam;
  Loader    *_loader;
  int 			_players;
  float 		_posx;
  float			_posy;
  float			_posx2;
  float			_posy2;
  int       _nb_bot;
  int			_width;
  int			_height;
  Map		        *_map;
  Sound			    *_sound;
  gdl::Clock		_clock;
  gdl::Input		_input;
  double        _time;
  double        _frames;
  double        _lasttime;
  gdl::BasicShader	_shader;
  std::map<int, Player*>	_player;
  std::vector<AObject*>	_other;
  std::map<std::pair<float, float>, Bombs *>  _bombs;
  bool        _endgame;
<<<<<<< HEAD
  AInput      *_ainput;
=======
  Particles   *_particles;
>>>>>>> 0afb239c368754c93b52578c67c19aae8b850c2a
};

#endif /*!_CORE_HPP_*/
