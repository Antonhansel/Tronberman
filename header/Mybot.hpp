/*
** Mybot.hpp for Mybot in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  23 15:42:07 2014 Antonin Ribeaud
** Last update Fri May  23 15:42:07 2014 Antonin Ribeaud
*/

#ifndef _MYBOT_HPP_
# define _MYBOT_HPP_

# include "Bombs.hpp"
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
