/*
** Loader.hpp for Loader in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  09 10:46:36 2014 Antonin Ribeaud
** Last update Fri May  09 10:46:36 2014 Antonin Ribeaud
*/

#ifndef _LOADER_HPP_
# define _LOADER_HPP_

#include "AObject.hpp"

class Loader
{
public:
	Loader();
	~Loader();
	gdl::Texture *getTexture(type);
	bool 		loadTextures();
private:
	std::map<type, gdl::Texture*> _textures;
};

#endif	/*!_LOADER_HPP_*/