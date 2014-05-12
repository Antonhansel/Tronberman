//
// Player.hpp for Player.hpp in /home/chouag_m/rendu/bitbucker
//
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
//
// Started on  Sat May 10 00:36:43 2014 Mehdi Chouag
// Last update Sat May 10 01:03:44 2014 Mehdi Chouag
//

#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include <map>
# include <utility>
# include "AObject.hpp"
# include "Model.hh"

# define SIGN(x)  (((x) < 0) ? (-1) : (1))

class Player : public AObject
{
protected:
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  gdl::Model		_model;
  int			      _anim;
  int           _stock;
  int           _id;
  int           _range;
  float         _speed;
  Map           *_map;
  int           _player;
  bool          checkMove(float y, float x);
  float         _x;
public:
  void    setPlayer(int);
  void    setSpeed(float);
  void    setMap(Map *);
public:
  Player();
  ~Player();
  void    update(gdl::Clock const &clock, gdl::Input &input);
  bool    initialize();
  void    draw(gdl::AShader &shader, gdl::Clock const &clock);
  int     getStock() const;
  void    setStock(int);
  int     getId() const;
  void    setId(int);
  int     getRange() const;
  void    setRange(int);
};

#endif /* !_PLAYER_HPP_ */
