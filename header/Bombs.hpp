/*
** Bombs.hpp for Bombs in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Sat May  10 02:45:01 2014 Antonin Ribeaud
** Last update Sat May  10 02:45:01 2014 Antonin Ribeaud
*/

#ifndef BOMBS_HPP_
# define BOMBS_HPP_

# include "AObject.hpp"
# include "Player.hpp"
# include "Map.hpp"
# include "Sound.hpp"

class Bombs : public AObject
{
private:
  	float		_speed;
  	gdl::Model 	_model;
  	type		_type;
  	int			_anim;
  	std::vector<AObject *> _bombs;
  	Map 		*_map;
  	double		_time;
  	double		_create;
  	std::vector< std::pair<double, AObject*> > _explosion;
  	Player 		*_player;
  	Sound			*_sound;
    std::map<std::pair<float, float>, Bombs *>  *_bombsM;
    bool      _isExplosed;
    bool      _explosed;

public:
	Bombs();
	~Bombs();

	/* data */
	bool 	exploded(gdl::Clock const &clock, gdl::Input &input);
	bool	initialize();
	void	draw(gdl::AShader &shader, gdl::Clock const &clock);
	void	update(gdl::Clock const &clock, gdl::Input &input);
	bool    makeBomb(Player *);
  void	bombExplode();
  void	removeExplosion();
  void	explosion(std::pair<float, float>, int);
  void	newBomb(std::pair<float, float>&);
  void	setObjects(Map *, Sound *, std::map<std::pair<float, float>, Bombs *>  *);
  void  explosePosY(float, std::pair<float, float>);
  void  exploseNegY(float, std::pair<float, float>);
  void  explosePosX(float, std::pair<float, float>);
  void  exploseNegX(float, std::pair<float, float>);
  bool  isExplosed() const;
  void  setExplose();
};

#endif