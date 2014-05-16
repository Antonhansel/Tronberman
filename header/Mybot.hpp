#ifndef _MYBOT_HPP_
# define _MYBOT_HPP_

# include "Player.hpp"
# include "Map.hpp"

class Mybot : public Player
{
public:
  Mybot();
  ~Mybot();
  bool			isSafe(int, int);
private:
  bool			lineSave(int, int, int, int);
};

#endif /* MYBOT_HPP */
