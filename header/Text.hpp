/*
** Text.hpp for Text in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 10:46:24 2014 Antonin Ribeaud
// Last update Thu May  8 00:58:57 2014 Mehdi Chouag
*/

#ifndef _TEXT_HPP_
# define _TEXT_HPP_

#include "AObject.hpp"
#include <vector>
#include <unistd.h>

class Text : public AObject
{
private:
  gdl::Texture	_texture;
  int		_firstChar;
  //gdl::Geometry	geometry;
  std::vector<gdl::Geometry *> _text;
  bool		_isDraw;

private:
  int	getColumn(char c);

public:
  Text();
  ~Text();
  void putchar(char c);
  void putstr(const char *);
  void update(gdl::Clock const &clock, gdl::Input &input);
  bool initialize();
  void draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif /*!TEXT_HPP*/
