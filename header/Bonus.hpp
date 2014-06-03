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

enum typeBonus
  {
    BONUS1,
    BONUS2,
    BONUS3
  };

class Bonus: public AObject
{
private:
	type					_type;
	typeBonus				_bonus;
	std::pair<float, float>	_pos;
	Map						*_map;
	float					_time;
    std::map<typeBonus, void (Bonus::*)(Player *)>  _ptrFunct;

public:
	Bonus();
	~Bonus();
	bool	initialize();
	void	draw(gdl::AShader &, gdl::Clock const &);
	void	update(gdl::Clock const &, gdl::Input &);
	void	setObject(std::pair<float, float> &, Map *);
	void	addToPlayer(Player *);
	void	giveBonus1(Player *);
	void	giveBonus2(Player *);
	void	giveBonus3(Player *);
    void	throwBonus();
};

#endif /* BONUS_HPP_ */
