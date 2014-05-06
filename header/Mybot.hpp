#ifndef _MYBOT_HPP_
# define _MYBOT_HPP_

# include "AObject.hpp"

class Mybot : public AObject
{
private:
  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  float		_speed;
  type		_type;
public:
	Mybot();
	~Mybot();
	void	update(gdl::Clock const &clock, gdl::Input &input);
	bool	initialize();
	void	draw(gdl::AShader &shader, gdl::Clock const &clock);
	bool	checkMove(float, float);
};

#endif /* !MYBOT_HPP */
