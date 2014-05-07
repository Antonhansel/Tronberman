#ifndef BOMBS_HPP_
# define BOMBS_HPP_

# include "AObject.hpp"

class Bombs : public AObject
{
private:
	gdl::Texture	_texture;
  	gdl::Geometry	_geometry;
  	float		_speed;
  	type		_type;	
public:
	Bombs();
	~Bombs();

	/* data */
	bool	initialize();
	void	draw(gdl::AShader &shader, gdl::Clock const &clock);
	void	update(gdl::Clock const &clock, gdl::Input &input);
};

#endif