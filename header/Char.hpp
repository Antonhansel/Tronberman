#ifndef _CHAR_HPP_
# define _CHAR_HPP_

# include <map>
# include <utility>
# include "AObject.hpp"
# include "Model.hh"
# include "Case.hpp"

class Char : public AObject
{
private:
	float 			_posx;
	float			_posy;
	int 			_players;
	int 			_screen;
	gdl::Texture	_texture;
	gdl::Geometry	_geometry;
	float			_speed;
	std::map< std::pair<int, int>, Case *>	_map;
public:
	gdl::Model		*_model;
	Char(int, int, std::map< std::pair<int, int>, Case *>);
	~Char();
	void 		update(gdl::Clock const &clock, gdl::Input &input);
	bool 		initialize();
	void 		draw(gdl::AShader &shader, gdl::Clock const &clock);	
	float		getTrans();
	int 		convertToInt(float);
};

#endif /*!_CHAR_HPP_*/