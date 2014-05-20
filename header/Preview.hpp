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
# include "Camera.hpp"
# include "Loader.hpp"

class Preview
{
public:
	Preview(Camera *, Loader *);
	~Preview();
private:
	Camera *_camera;
	Loader *_loader;
};

#endif /*!_PREVIEW_HPP_*/