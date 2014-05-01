/*
** main.cpp for core in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:44:17 2014 Antonin Ribeaud
** Last update Mon Apr  28 13:44:17 2014 Antonin Ribeaud
*/

# include "AObject.hpp"
# include "Core.hpp"
# include "Cube.hpp"
# include "Intro.hpp"

//Not needed yet
//# include "Window.hpp"

int		main(int argc, char **argv)
{
	Core 	core;

	// Intro	intro;
	// if (intro.initialize() == false)
	// 	{
	// 		std::cout << "Error on initializing" << std::endl;
	// 		return EXIT_FAILURE;
	// 	}
	// while (intro.update() == true)
	// 		intro.draw();
	if (core.initialize() == false)
		{
			std::cout << "Error on initializing" << std::endl;
			return EXIT_FAILURE;
		}
	while (core.update() == true)
		core.draw();
	return EXIT_SUCCESS;
}