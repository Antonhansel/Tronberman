/*
** Sound.cpp for Sound in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 16:48:25 2014 Antonin Ribeaud
// Last update Mon Jun 23 17:39:22 2014 Mehdi Chouag
*/

#include "Sound.hpp"

Sound::Sound()
{
  _fx = true;
  FMOD_System_Create(&system);
  FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
  FMOD_System_CreateSound(system, "./ressources/sounds/bomb.wav", FMOD_CREATESAMPLE, 0, &_effect[BOMB_S]);
  FMOD_System_CreateSound(system, "./ressources/sounds/bonus.wav", FMOD_CREATESAMPLE, 0, &_effect[BONUS_S]);
  FMOD_System_CreateSound(system, "./ressources/sounds/pbomb.wav", FMOD_CREATESAMPLE, 0, &_effect[PBOMB_S]);
  FMOD_System_CreateSound(system, "./ressources/sounds/death.wav", FMOD_CREATESAMPLE, 0, &_effect[DEATH_S]);
  FMOD_System_CreateSound(system, "./ressources/sounds/hit.wav", FMOD_CREATESAMPLE, 0, &_effect[HIT_S]);
}

Sound::~Sound()
{
  FMOD_Sound_Release(_effect[BOMB_S]);
  FMOD_Sound_Release(_effect[BONUS_S]);
  FMOD_Sound_Release(_effect[PBOMB_S]);
  FMOD_Sound_Release(_effect[DEATH_S]);
  FMOD_Sound_Release(_effect[HIT_S]);
  FMOD_System_Close(system);
  FMOD_System_Release(system);
}

void	Sound::playSound(const TypeSound type, const int volume)
{
  if (_fx)
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, _effect[type], 0, NULL);
}

void	Sound::setEffect(const bool effect)
{
  _fx = effect;
}
