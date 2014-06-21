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

# include "AObject.hpp"
# include "Model.hh"
# include "AInput.hpp"
# include "Sound.hpp"

#define MARGE 0.4
# define SIGN(x)  (((x) < 0) ? (-1) : (1))

enum dirr
  {
    NORTH,
    SOUTH,
    EAST,
    WEST
  };

enum PlayerType {
  HUMAN,
  IA,
  NETWORK
};

class Bonus;
class AInput;
class Bombs;
class Core;

class Player : public AObject
{
protected:
  gdl::Texture  _texture;
  gdl::Geometry _geometry;
  gdl::Model    _model;
  int           _anim;
  int           _stock;
  int           _id;
  int           _range;
  float         _speed;
  Map           *_map;
  int           _player;
  AObject       *_checkMove(float y, float x);
  bool          _checkMove2(float y, float x);
  bool          _onBomb(float y, float x);
  float         _x;
  int           _life;
  bool          _begin;
  AInput        *_input;
  std::map<key, std::pair<float, float> (Player::*)(float &)>   _key;
  float         _shield;
  double        _timer;
  bool          _isAlive;
  int           _score;
  dirr          _dir;
  std::vector<Player*>  *_playermap;
  std::string   _modelpath;
  Sound         *_sound;
  Core          *_core;
  virtual void          _consumeBonus(AObject *);
public:
  void    setPlayer(int);
  void    setSpeed(float);
  void    setMap(Map *);
  bool    isAlive() const;
  void    setIsAlive();
  void    setScore(int);
  int     getScore() const;
  float   getSpeed() const;
  virtual PlayerType getType() const;
  void    setCore(Core *);
public:
  Player();
  ~Player();
  void    update(const gdl::Clock &, gdl::Input &);
  bool    initialize();
  void    draw(gdl::AShader &, const gdl::Clock &);
  int     getStock() const;
  virtual void    setStock(int);
  int     getId() const;
  void    setId(int);
  int     getRange() const;
  virtual void    setRange(int);
  virtual void    setLife(int);
  int     getLife() const;
  void    setBegin(bool);
  bool    getBegin() const;
  virtual void    spawnBomb();
  void    setSound(Sound *);
  std::pair<float, float>   realPos(std::pair<float, float>);
  float   getShield() const;
  void    setBombs(std::map<std::pair<float, float>, Bombs *> *);
  void    setPlayerTab(std::vector<Player*> *);
  void    setShield(float);
  void    dir(dirr);
  dirr    dir() const;
private:
  std::pair<float, float> up(float &);
  std::pair<float, float> right(float &);
  std::pair<float, float> left(float &);
  std::pair<float, float> down(float &);
  std::map<std::pair<float, float>, Bombs *>  *_bombs;
  float                                        _speedActiv;
};

#endif /* !_PLAYER_HPP_ */
