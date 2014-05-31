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
	bool 		loadTextures();
	void 		bindTexture(type);
	void 		drawGeometry(gdl::AShader &, glm::mat4);
	void 		pushTexture(gdl::Geometry *);
	void 		loadParticules();
	void 		drawParticules(gdl::AShader &, glm::mat4);
private:
	int 			_modelCount;
	std::vector<gdl::Texture*> _textures;
	std::vector<gdl::Model *> _models;
	gdl::Geometry 		_geometry;
	gdl::Geometry 		_trigeo;
};

#endif	/*!_LOADER_HPP_*/
