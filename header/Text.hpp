/*
** Text.hpp for Text in /home/apollo/rendu/cpp_bomberman/header
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 10:46:24 2014 Antonin Ribeaud
// Last update Wed May 14 01:48:25 2014 Mehdi Chouag
*/

#ifndef _TEXT_HPP_
# define _TEXT_HPP_

#include "AObject.hpp"
#include "Camera.hpp"
#include <vector>
#include <unistd.h>
#include <map>

#define WIDTH_T 1300

class Text
{
private:
  gdl::Texture	_texture;
  int		_firstChar;
  Camera        *_camera;
  
private:
  int	getColumn(char c);

public:
  Text(Camera *);
  ~Text();
  void putchar(char, int, std::vector<gdl::Geometry *> &);
  std::vector<gdl::Geometry *> putstr(const char *, int);
  // void update(gdl::Clock const &clock, gdl::Input &input);
  void draw(const std::map<std::pair<int, int>, std::vector<gdl::Geometry *> > &);
};

#endif /* !TEXT_HPP */
