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

enum MenuText
  {
    TITLE = 0,
    SUBTITLE = 1,
    LOCAL = 2,
    ONLINE = 3
  };

class Text : public AObject
{
private:
  gdl::Texture	_texture;
  int		_firstChar;
  Camera        *_camera;
  bool		_isDraw;
  gdl::BasicShader	_shader;
  std::map<MenuText, std::vector<gdl::Geometry *> >  _word;
  std::map<MenuText, void (Text::*)(std::vector<gdl::Geometry *>&)> _funct;
  bool		_menu;
  
private:
  int	getColumn(char c);
  void  title(std::vector<gdl::Geometry *> &);
  void  subTitle(std::vector<gdl::Geometry *> &);
  void  local(std::vector<gdl::Geometry *> &);
  void  online(std::vector<gdl::Geometry *> &);

public:
  Text(Camera *);
  ~Text();
  void putchar(char, int, std::vector<gdl::Geometry *> &);
  void putstr(const char *, int, MenuText);
  void update(gdl::Clock const &clock, gdl::Input &input);
  bool initialize();
  void draw(gdl::AShader &shader, gdl::Clock const &clock);
  void setShow(bool);
};

#endif /*!TEXT_HPP*/
