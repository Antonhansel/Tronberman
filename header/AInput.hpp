/*
** Input.hpp for Input in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue May  06 11:22:59 2014 Antonin Ribeaud
** Last update Tue May  06 11:22:59 2014 Antonin Ribeaud
*/

#ifndef _AINPUT_HPP_  
# define _AINPUT_HPP_

# include <linux/joystick.h>
# include <fstream>
# include <map>
# include "Input.hh"
# include "AObject.hpp"

enum inputType
{
	KEY1,
	KEY2
};

/*enum key
{
        NONE = 0,
        P1UP = SDLK_UP,
        P1DOWN = SDLK_DOWN,
        P1RIGHT = SDLK_RIGHT,
        P1LEFT = SDLK_LEFT ,
        P1BOMB = SDLK_KP_0 ,
        P2UP = SDLK_z,
        P2DOWN = SDLK_s,
        P2RIGHT = SDLK_q,
        P2LEFT = SDLK_d,
        P2BOMB = SDLK_SPACE
};*/

class AInput
{
private:
	/*cinput _input;
	std::ifstream joy1;
	std::ifstream joy2;*/
	gdl::Input 								_input;
    std::map<inputType, void (AInput::*)()>	_ptrFunct;
    std::map<int, key>						_key;

public:
	AInput(gdl::Input &, inputType);
	~AInput();
	key 	getInput();

private:
	void	createPlayer1Key();
	void 	createPlayer2Key();
};

#endif /*!AINPUT_HPP_*/