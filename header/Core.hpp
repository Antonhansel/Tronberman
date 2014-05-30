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
# include "AInput.hpp"
# include "Saving.hpp"

class Menu;
class Player;

class Core : public gdl::Game
{
public:
  Core(Camera *cam, Loader *loader, Menu *menu, ParticleEngine *);
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
  int       getNbrPlayer() const;
  Map       *getMap();
  std::map<int, Player*>  getPlayer();
  void      setValues(Map *);
  void      reset();
  void      setSave(Map *, std::map<int, Player*> &, Saving *);
  gdl::Clock *getClock();
  bool      playerDraw(std::pair<float, float>, std::pair<float, float>);
private:
  std::vector<std::pair<int, int> >    _obj;
  bool      _isSave;
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
  AInput      *_ainput;
  ParticleEngine   *_particles;
};

#endif /*!_CORE_HPP_*/
