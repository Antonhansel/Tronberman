/*
** Sound.hpp for Sound in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:35:37 2014 Antonin Ribeaud
// Last update Mon Jun 23 17:31:03 2014 Mehdi Chouag
*/

#ifndef SOUND_HPP_
# define SOUND_HPP_

# include <iostream>
# include <map>
# include <fmod.h>


enum TypeSound 
  {  
    BOMB_S = 0,
    BONUS_S = 1,
    WALK_S = 2,
    PBOMB_S = 3,
    DEATH_S = 4,
    HIT_S = 5
  };

class Sound
{
public:
  Sound();
  ~Sound();
  void	playSound(const TypeSound, const int);
  void  setEffect(const bool);

private:
  bool                                      _fx;
  FMOD_SYSTEM				    *system;
  FMOD_SOUND				    *_effect[6];

};

#endif
