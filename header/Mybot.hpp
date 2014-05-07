#ifndef _MYBOT_HPP_
# define _MYBOT_HPP_

# include "AObject.hpp"

enum direction
  {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
  };

class Mybot : public AObject
{
private:
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  float		_speed;
  type		_type;
  direction	_direction;
  int 		_up;
  int 		_down;
  int 		_left;
  int 		_right;
public:
	Mybot();
	~Mybot();
	void	update(gdl::Clock const &clock, gdl::Input &input);
	bool	initialize();
	void	draw(gdl::AShader &shader, gdl::Clock const &clock);
	bool	checkMove(float, float);
	void 	randomNbr();
};

#endif /* !MYBOT_HPP */
