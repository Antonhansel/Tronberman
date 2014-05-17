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

#include "Loader.hpp"
#include "Camera.hpp"
#include "AInput.hpp"
#include <vector>
#include <unistd.h>
#include <map>

class Text
{
private:
  int		         _firstChar;
  Camera        *_camera;
  Loader        *_loader;
  type          _lastType;
  glm::mat4     _transformation;

private:
  int	getColumn(char c);
  void textureBind(int, int);

public:
  Text(Camera *, Loader *);
  ~Text();
  void putchar(char, int, std::vector<gdl::Geometry *> &);
  std::vector<gdl::Geometry *> putstr(const char *, int);
  // void update(gdl::Clock const &clock, gdl::Input &input);
  void draw(const std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &, int);
  void  modifyWord(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > *, const std::vector<std::string> &);
  void  addNb(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > *, int, const std::string &);
};

#endif /* !TEXT_HPP */
