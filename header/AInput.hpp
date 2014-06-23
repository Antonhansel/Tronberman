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

class AInput
{
private:
	std::ifstream joy1;
	gdl::Input 								_input;
    std::map<inputType, void (AInput::*)()>	_ptrFunct;
    std::map<int, key>						_key;
    bool 									_mode2;
    inputType								_type;
    std::vector<key>						in;

public:
	AInput(gdl::Input &, inputType);
	~AInput();
	const std::vector<key> 	&getInput();
	void	setInput(gdl::Input const &);
	void	createMenuKey();
	void	setMode(const bool);
	static bool	getKey(const std::vector<key> &, const key);

private:
	void	createPlayer1Key();
	void 	createPlayer2Key();
	void	createGameKey();
	void	createGeneratorKey();
};

#endif /*!AINPUT_HPP_*/