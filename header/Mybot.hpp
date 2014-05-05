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
	void update(gdl::Clock const &clock, gdl::Input &input);
	bool initialize();
	void draw(gdl::AShader &shader, gdl::Clock const &clock);
	void	setMap(std::map< std::pair<float, float>, AObject * > &);
};

#endif /* !MYBOT_HPP */
