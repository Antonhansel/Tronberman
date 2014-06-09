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
  void    setSeeRange(int);
  void    setRec(int);
  void    setAction(int);
  void    setFreqBombs(int);
  PlayerType getType() const;

private:
  bool    lineSafe(int, int, int, int) const;
  bool    isSafe(int, int) const;
  bool    setObjDef(int, int, int, enum dir);
  int     setObjDef(int, int);
  int     setObjOff(int, int);
  void    moveTo(int, int, int, int);
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
