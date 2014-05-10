/*
** Sound.hpp for Sound in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:35:37 2014 Antonin Ribeaud
// Last update Sat May 10 22:11:27 2014 Mehdi Chouag
*/

# include <iostream>
# include <map>
# include <SFML/Audio/Music.hpp>
# include <SFML/Audio.hpp>

enum TypeSound 
  {  
    BOMB_S = 0,
    BONUS_S = 1,
    WALK_S = 2,
    DEAD_S = 3
  };

class Sound
{
public:
  Sound();
  ~Sound();
  void	playSound(TypeSound, int);
  void	playMusic();
  void	bomb(int);
  void	bonus(int);
  void	walk(int);
  void	dead(int);
private:
  sf::Music			*_music;
  sf::Music			*_effect[4];
  std::map<TypeSound, void(Sound::*)(int)> _soundEffect;
};
