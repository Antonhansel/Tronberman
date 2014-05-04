//
// Char.hpp for char in /home/chouag_m/rendu/old
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sun May  4 02:54:34 2014 Mehdi Chouag
// Last update Sun May  4 02:54:59 2014 Mehdi Chouag
//

#ifndef _CHAR_HPP_
# define _CHAR_HPP_

# include <map>
# include <utility>
# include "AObject.hpp"
# include "Model.hh"

class Char : public AObject
{
private:
  float			_posx;
  float			_posy;
  gdl::Texture		_texture;
  gdl::Geometry		_geometry;
  gdl::Model		*_model;

public:
  void		setPlayer(int);
  void		setScreen(int);
  void		setSpeed(float);
  void		setMap(std::map< std::pair<float, float>, AObject *>&);
  
public:
  Char();
  ~Char();
  void 		update(gdl::Clock const &clock, gdl::Input &input);
  bool 		initialize();
  void 		draw(gdl::AShader &shader, gdl::Clock const &clock);	
  float		getTrans();  
  int 		convertToInt(float);
};

#endif /*!_CHAR_HPP_*/
