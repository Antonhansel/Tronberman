/*
** Bonus.cpp for Bonus in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Wed May  14 12:37:53 2014 Antonin Ribeaud
** Last update Wed May  14 12:37:53 2014 Antonin Ribeaud
*/

#include "Bonus.hpp"

Bonus::Bonus() :
	_time(0)
{
	_ptrFunct[BONUS1] = &Bonus::giveBonus1;
	_ptrFunct[BONUS2] = &Bonus::giveBonus2;
	_ptrFunct[BONUS3] = &Bonus::giveBonus3;
	_ptrFunct[BONUS4] = &Bonus::giveBonus4;
	initialize();
}

Bonus::~Bonus()
{}

bool	Bonus::initialize()
{
	int res;

	res = rand() % 4;
	switch (res)
	{
		case 0:
			_bonus = BONUS1;
			break;
		case 1:
			_bonus = BONUS2;
			break;
		case 2:
			_bonus = BONUS3;
			break;
		case 3:
			_bonus = BONUS4;
			break;
		default:
			break;
	}
  scale(glm::vec3(0.7, 0.7, 0.7));
  return (true);
}

void	Bonus::update(gdl::Clock const &clock, gdl::Input &input)
{
	_time += clock.getElapsed();
}

void	Bonus::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
}

void	Bonus::setObject(const std::pair<float, float> &pos, Map *map)
{
	(_bonus == BONUS1) ? _type = BONUSV : (_bonus == BONUS2) ? _type = BONUSB : (_bonus == BONUS3) ? _type = BONUSR : _type = BONUSS;
	_pos = pos;
	_map = map;
	setType(_type);
}

void	Bonus::throwBonus()
{
	_map->addCube(_pos.first, _pos.second, this);
}

void	Bonus::addToPlayer(Player *player)
{
	(this->*_ptrFunct[_bonus])(player);
}

void	Bonus::giveBonus1(Player *player)
{
	player->setLife(player->getLife() + 1);
}

void	Bonus::giveBonus2(Player *player)
{
	player->setStock(player->getStock() + 1);
}

void	Bonus::giveBonus3(Player *player)
{
	player->setRange(player->getRange() + 1);
}

void	Bonus::giveBonus4(Player *player)
{
	player->setSpeed(8);
}
