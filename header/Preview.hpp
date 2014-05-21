/*
** Preview.hpp for Preview in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue May  20 11:00:42 2014 Antonin Ribeaud
** Last update Tue May  20 11:00:42 2014 Antonin Ribeaud
*/

#ifndef _PREVIEW_HPP_
# define _PREVIEW_HPP_

# include "Saving.hpp"

#define PI 3.14159
#define PATH "./ressources/maps/"

class Preview
{
public:
	Preview(Camera *, Loader *);
	~Preview();
	bool		initialize();
	bool		update(gdl::Clock const &clock, gdl::Input &input);
	void		draw(gdl::AShader &shader, gdl::Clock const &clock);
	void 		setCameraAngle();
	void 	getPaths();
	bool 	checkName(const char *);
	std::string	makePath(const char *);
private:
	Map 			*_map;
	std::vector<std::string> _paths;
	Camera 	*_camera;
	Loader 	*_loader;
	std::vector<Map*> 	_maps;
	Saving 	*_saving;
	float			_angle;
  	float			_posy;
  	float			_posz;
  	float			_posx;
  	float			_xend;
};

#endif /*!_PREVIEW_HPP_*/