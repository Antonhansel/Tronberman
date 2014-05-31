#ifndef _MYBOT_HPP_
# define _MYBOT_HPP_

# include "Player.hpp"
# include "Map.hpp"

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
  PlayerType getType() const;

private:
  bool    lineSafe(int, int, int, int) const;
  bool    isSafe(int, int) const;
  bool    setObjDef(int, int, int, dir);
  void    setObjDef(int, int);
  void    setObjOff(int, int);
  void    moveTo(int, int, int, int);
  int     my_rand();

  int     _x_obj;
  int     _y_obj;
  int     _rec;
  int     _seerange;
};

#endif /* MYBOT_HPP */
