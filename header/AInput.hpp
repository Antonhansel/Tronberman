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
	KEY2,
	GAME,
	MENU,
	GENERATOR
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
    bool 									_mode2;
    inputType								_type;

public:
	AInput(gdl::Input &, inputType);
	~AInput();
	std::vector<key> 	getInput();
	void	setInput(gdl::Input &);
	void	createMenuKey();
	void	setMode(bool);
	static bool	getKey(std::vector<key> &, key);

private:
	void	createPlayer1Key();
	void 	createPlayer2Key();
	void	createGameKey();
	void	createGeneratorKey();
};

#endif /*!AINPUT_HPP_*/