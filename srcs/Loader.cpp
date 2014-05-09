/*
** Loader.cpp for Loader in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  09 10:46:17 2014 Antonin Ribeaud
** Last update Fri May  09 10:46:17 2014 Antonin Ribeaud
*/

#include "Loader.hpp"

Loader::Loader()
{
}

Loader::~Loader()
{
}

bool 	Loader::loadTextures()
{
	_textures[BLOCKD] = new gdl::Texture();
	if (_textures[BLOCKD]->load("./ressources/assets/block.tga") == false)
		return (false);
	return (true);
}

gdl::Texture *Loader::getTexture(type texttype)
{
	return (_textures[texttype]);
}