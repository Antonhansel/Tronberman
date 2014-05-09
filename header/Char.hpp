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
# include "Bombs.hpp"

class Char : public AObject
{
private:
  gdl::Texture		_texture;
  gdl::Geometry		_geometry;
  gdl::Model		  _model;
  int             _anim;

public:
  void		setPlayer(int);
  void		setScreen(int);
  void		setSpeed(float);
  void		setMap(std::map< std::pair<float, float>, AObject *> *);
  void    setBombs(std::map< std::pair<float, float>, AObject* >&);
  const std::map< std::pair<float, float>, AObject* >&  getBombs();

public:
  Char();
  ~Char();
  void 		update(gdl::Clock const &clock, gdl::Input &input);
  bool 		initialize();
  void 		draw(gdl::AShader &shader, gdl::Clock const &clock);	
  bool    checkMove(float y, float x);  
  float		getTrans();  
  int 		convertToInt(float);

private:
  void  checkBombs();
};

#endif /*!_CHAR_HPP_*/
