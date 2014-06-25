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

#include <vector>
#include <unistd.h>
#include <map>
#include "Loader.hpp"
#include "Camera.hpp"
#include "AInput.hpp"

class Text
{
protected:
  int		        _firstChar;
  Camera        *_camera;
  Loader        *_loader;
  type          _lastType;
  glm::mat4     _transformation;

protected:
  int   getColumn(const char);
  int   getOtherColumn(const char);
  void  textureBind(const int, const int);

public:
  Text(Camera *, Loader *);
  ~Text();
  void  putchar(char, const int, std::vector<gdl::Geometry *> &, const bool);
  std::vector<gdl::Geometry *> putstr(const char *, const int, const bool);
  void  draw(const std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &, const int);
  void  modifyWord(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > *, const std::vector<std::pair<bool, std::string> > &);
  void  addNb(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > *, const int, const std::string &);
  void  addText(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &, const int, const std::pair<int, int> &, const std::string&, const bool);
  void  deleteText(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &, const std::pair<int, std::pair<int, int> > &);
  void  deleteAllText(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &) ;
};

#endif /* !TEXT_HPP */
