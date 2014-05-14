/*
** Bonus.hpp for Bonus in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Wed May  14 12:38:02 2014 Antonin Ribeaud
** Last update Wed May  14 12:38:02 2014 Antonin Ribeaud
*/

#ifndef BONUS_HPP_
# define BONUS_HPP_

# include "AObject.hpp"
# include "Map.hpp"
//# include "Player.hpp"

class Player;

class Bonus: public AObject
{
private:
	type					_type;
	std::pair<float, float>	_pos;
	Map						*_map;
	bool					_isTaken;
	float					_time;

public:
	Bonus();
	~Bonus();
	bool	initialize();
	void	draw(gdl::AShader &, gdl::Clock const &);
	void	update(gdl::Clock const &, gdl::Input &);
	void	setObject(type, std::pair<float, float> &, Map *);
	void	addToPlayer(Player *);
	/* data */
};

#endif /* BONUS_HPP_ */