/*
** Sound.cpp for Sound in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 16:48:25 2014 Antonin Ribeaud
// Last update Sat May 10 22:42:06 2014 Mehdi Chouag
*/

#include "Sound.hpp"

Sound::Sound()
{
  _music = new sf::Music;
  _soundEffect[BOMB_S] = &Sound::bomb;
  _soundEffect[BONUS_S] = &Sound::bonus;
  _soundEffect[PBOMB_S] = &Sound::bonus;
  _soundEffect[DEATH_S] = &Sound::bonus;
  _soundEffect[HIT_S] = &Sound::hit;
  // _soundEffect[WALK_S] = &Sound::walk; 
  // _soundEffect[DEAD_S] = &Sound::dead;
  _effect[BOMB_S] = new sf::Music;
  _effect[BONUS_S] = new sf::Music;
  _effect[PBOMB_S] = new sf::Music;
  _effect[DEATH_S] = new sf::Music;
  _effect[HIT_S] = new sf::Music;
  
  // _effect[WALK_S] = new sf::Music;
  // _effect[DEAD_S] = new sf::Music;
  _effect[BOMB_S]->openFromFile("./ressources/sounds/bomb.wav");
  // _effect[WALK_S]->openFromFile("./ressources/sounds/walk.wav");
  _effect[BONUS_S]->openFromFile("./ressources/sounds/bonus.wav");
  // _effect[DEAD_S]->openFromFile("./ressources/sounds/dead.wav");
  _effect[PBOMB_S]->openFromFile("./ressources/sounds/pbombs.wav");
  _effect[DEATH_S]->openFromFile("./ressources/sounds/death.wav");
  _effect[HIT_S]->openFromFile("./ressources/sounds/hit.wav");
}

Sound::~Sound()
{
  delete _effect[BOMB_S];
  delete _effect[BONUS_S];
  delete _effect[PBOMB_S];
  delete _effect[DEATH_S];
  delete _effect[HIT_S];
  delete _music;
}

void	Sound::playSound(TypeSound type, int volume)
{
  (this->*_soundEffect[type])(volume);
}

void	Sound::bomb(int volume)
{
  _effect[BOMB_S]->setVolume(volume);
  _effect[BOMB_S]->play();
}

void	Sound::bonus(int volume)
{
  _effect[BONUS_S]->setVolume(volume);
  _effect[BONUS_S]->play();
}

void  Sound::putBombs(int volume)
{
  _effect[PBOMB_S]->setVolume(volume);
  _effect[PBOMB_S]->play();
}

void  Sound::death(int volume)
{
  _effect[DEATH_S]->setVolume(volume);
  _effect[DEATH_S]->play();
}

void  Sound::hit(int volume)
{
  _effect[HIT_S]->setVolume(volume);
  _effect[HIT_S]->play();
}
// void	Sound::walk(int volume)
// {
//   _effect[WALK_S]->setVolume(volume);
//   _effect[WALK_S]->play();
// }

// void	Sound::dead(int volume)
// {
//   _effect[DEAD_S]->setVolume(volume);
//   _effect[DEAD_S]->play();
// }
