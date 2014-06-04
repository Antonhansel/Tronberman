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
  AObject          *_checkMove(float y, float x);
  bool          _checkMove2(float y, float x);
  bool          _onBomb();
  virtual void          _consumeBonus(AObject *);
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
  Core          *_core;
  Sound         *_sound;

public:
  void    setPlayer(int);
  void    setCore(Core *);
  void    setSpeed(float);
  void    setMap(Map *);
  bool    isAlive() const;
  void    setIsAlive();
  void    setScore(int);
  int     getScore() const;
  float   getSpeed() const;
  PlayerType getType() const;
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
  void    setLife(int);
  int     getLife() const;
  void    setBegin(bool);
  bool    getBegin() const;
  virtual void    spawnBomb();
  void    setSound(Sound *sound);
  std::pair<float, float>   realPos(std::pair<float, float>);
  float   getShield() const;
  void    setBombs(std::map<std::pair<float, float>, Bombs *> *);
  void    setPlayerTab(std::vector<Player*> *playermap);
  void    setShield(float);
  void    dir(dirr);
  dirr    dir();
private:
  std::pair<float, float> up(float &);
  std::pair<float, float> right(float &);
  std::pair<float, float> left(float &);
  std::pair<float, float> down(float &);
  std::map<std::pair<float, float>, Bombs *>  *_bombs;
};

#endif /* !_PLAYER_HPP_ */
