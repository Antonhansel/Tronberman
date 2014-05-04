/*
** main.cpp for core in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:44:17 2014 Antonin Ribeaud
// Last update Sat May  3 21:37:33 2014 Mehdi Chouag
*/

# include "Engine.hpp"

int		main(int ac, char **argv)
{
  Engine	game;
  
  if (!game.start())
    return (EXIT_FAILURE);
  else
    {
      
    }
  return (EXIT_SUCCESS);
}
