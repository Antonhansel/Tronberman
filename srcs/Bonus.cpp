#include "Bonus.hpp"

Bonus::Bonus() :
	_isTaken(false), _time(0)
{
	initialize();
}

Bonus::~Bonus()
{}

bool	Bonus::initialize()
{
  scale(glm::vec3(0.9, 0.9, 0.9));
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

void	Bonus::setObject(type type, std::pair<float, float> &pos, Map *map)
{
	_type = type;
	_pos = pos;
	_map = map;
	setType(_type);
	_map->addCube(_pos.first, _pos.second, this);
}

void	Bonus::addToPlayer(Player *Player)
{

}