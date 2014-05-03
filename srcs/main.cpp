/*
** main.cpp for core in /home/apollo/rendu/bestbomberman
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Mon Apr  28 13:44:17 2014 Antonin Ribeaud
// Last update Thu May  1 16:51:09 2014 ribeaud antonin
*/

# include "AObject.hpp"
# include "Core.hpp"
# include "Cube.hpp"
# include "Intro.hpp"
# include "Camera.hpp"

bool	makeIntro()
{
	Intro	*intro;

	intro = new Intro();
	if (intro->initialize() == false)
		{
			std::cout << "Error on initializing" << std::endl;
			return (false);
		}
	while (intro->update() == true)
		intro->draw();
	delete intro;
	return (true);	
}

bool	startGame(Camera &cam)
{
	Core 	core(cam);

	if (core.initialize() == false)
		{
			std::cout << "Error on initializing" << std::endl;
			return false;
		}
	core.intro();
	while (core.update() == true)
		core.draw();
	return (true);
}

int		main(int argc, char **argv)
{
	Camera camera;
	// if (makeIntro() == false)
	// 	return (EXIT_FAILURE);
	if (startGame(camera) == false)
		return (EXIT_FAILURE);
	return EXIT_SUCCESS;
}
