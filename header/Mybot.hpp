#ifndef _MYBOT_HPP_
# define _MYBOT_HPP_

# include "Player.hpp"
# include "Map.hpp"
# include "Bonus.hpp"

enum dir
{
  LEFT,
  UP,
  RIGHT,
  DOWN
};

class Mybot : public Player
{
public:
  Mybot();
  ~Mybot();
  void    update(gdl::Clock const &clock, gdl::Input &input);
  void    setSeeRange(const int);
  void    setRec(const int);
  void    setAction(const int);
  void    setFreqBombs(const int);
  PlayerType getType() const;

private:
  bool    lineSafe(const int, const int, const int, const int) const;
  bool    isSafe(const int, const int) const;
  bool    setObjDef(const int, const int, const int, enum dir);
  int     setObjDef(const int, const int);
  int     setObjOff(const int, const int);
  void    moveTo(const int, const int, const int, const int);
  int     my_rand();

  int     _x_obj;
  int     _y_obj;
  float   _dep;
  int     _move;

  int     _rec;
  int     _action;
  int     _seerange;
  int     _freq_bombs;
};

#endif /* MYBOT_HPP */
