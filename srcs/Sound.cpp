/*
** Sound.cpp for Sound in /home/apollo/rendu/bestbomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue Apr  29 16:48:25 2014 Antonin Ribeaud
// Last update Thu May  1 13:43:43 2014 ribeaud antonin
*/

#include "Sound.hpp"

Sound::Sound()
{
	_music = new sf::Music;
	_soundEffect[BOMB] = &Sound::bomb; 
	_soundEffect[BONUS] = &Sound::bonus; 
	_soundEffect[WALK] = &Sound::walk; 
	_soundEffect[DEAD] = &Sound::dead;
	_effect[BOMB] = new sf::Music;
	_effect[BONUS] = new sf::Music;
	_effect[WALK] = new sf::Music;
	_effect[DEAD] = new sf::Music;
	_effect[BOMB]->openFromFile("sound/bomb.wav");
	_effect[WALK]->openFromFile("sound/walk.wav");
	_effect[BONUS]->openFromFile("sound/bonus.wav");
	_effect[DEAD]->openFromFile("sound/dead.wav");
}

Sound::~Sound()
{
	for (int i = 0; i < 4; ++i)
	 	delete _effect[i];
	delete _music;
}

void	Sound::playMusic()
{
	if (_music->openFromFile("sound/theme.ogg"))
		{
			_music->setVolume(50);
			_music->play();
		}
	else
		std::cout << "Can't load " << std::endl;
}

void	Sound::playSound(TypeSound type, int volume)
{
	(this->*_soundEffect[type])(volume);
}

void	Sound::bomb(int volume)
{
	_effect[BOMB]->setVolume(volume);
	_effect[BOMB]->play();
}

void	Sound::bonus(int volume)
{
	_effect[BONUS]->setVolume(volume);
	_effect[BONUS]->play();
}

void	Sound::walk(int volume)
{
	_effect[WALK]->setVolume(volume);
	_effect[WALK]->play();
}

void	Sound::dead(int volume)
{
	_effect[DEAD]->setVolume(volume);
	_effect[DEAD]->play();
}
