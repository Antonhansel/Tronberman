/*
** Preview.cpp for Preview in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue May  20 11:00:02 2014 Antonin Ribeaud
** Last update Tue May  20 11:00:02 2014 Antonin Ribeaud
*/

#include "Preview.hpp"

Preview::Preview(Camera *camera, Loader *loader)
{
	_camera = camera;
	_loader = loader;
}

Preview::~Preview()
{

}