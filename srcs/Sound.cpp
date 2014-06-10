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
  _fx = true;
  _music = new sf::Music;
  _soundEffect[BOMB_S] = &Sound::bomb;
  _soundEffect[BONUS_S] = &Sound::bonus;
  _soundEffect[PBOMB_S] = &Sound::putBombs;
  _soundEffect[DEATH_S] = &Sound::death;
  _soundEffect[HIT_S] = &Sound::hit;
  _effect[BOMB_S] = new sf::Music;
  _effect[BONUS_S] = new sf::Music;
  _effect[PBOMB_S] = new sf::Music;
  _effect[DEATH_S] = new sf::Music;
  _effect[HIT_S] = new sf::Music;
  _effect[BOMB_S]->openFromFile("./ressources/sounds/bomb.wav");
  _effect[BONUS_S]->openFromFile("./ressources/sounds/bonus.wav");
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

void	Sound::playSound(const TypeSound type, const int volume)
{
  if (_fx)
    (this->*_soundEffect[type])(volume);
}

void	Sound::bomb(const int volume)
{
  _effect[BOMB_S]->setVolume(volume);
  _effect[BOMB_S]->play();
}

void	Sound::bonus(const int volume)
{
  _effect[BONUS_S]->setVolume(volume);
  _effect[BONUS_S]->play();
}

void  Sound::putBombs(const int volume)
{
  _effect[PBOMB_S]->setVolume(volume);
  _effect[PBOMB_S]->play();
}

void  Sound::death(const int volume)
{
  _effect[DEATH_S]->setVolume(volume);
  _effect[DEATH_S]->play();
}

void  Sound::hit(const int volume)
{
  _effect[HIT_S]->setVolume(volume);
  _effect[HIT_S]->play();
}

void  Sound::setEffect(const bool effect)
{
  _fx = effect;
}