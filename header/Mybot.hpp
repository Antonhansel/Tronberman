#ifndef _MYBOT_HPP_
# define _MYBOT_HPP_

# include "Player.hpp"

enum direction
  {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
  };

class Mybot : public Player
{
public:
  Mybot();
  ~Mybot();
};

#endif /* !MYBOT_HPP */
