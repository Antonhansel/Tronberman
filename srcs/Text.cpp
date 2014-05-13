/*
** Text.cpp for Text in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 10:46:08 2014 Antonin Ribeaud
// Last update Wed May 14 01:47:41 2014 Mehdi Chouag
*/

#include "Text.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Text::Text(Camera *camera) : _firstChar(0), _menu(false)
{
  _camera = camera;
  _shader = _camera->getShader();
  _texture.load("./ressources/fonts/24BitTron.tga");
  putstr("Bombertron", 64, TITLE);
  putstr("Welcome to the grid", 32, SUBTITLE);
  putstr("LOCAL", 64, LOCAL);
  putstr("ONLINE", 64, ONLINE);
  _funct[TITLE] = &Text::title;
  _funct[SUBTITLE] = &Text::subTitle;
  _funct[LOCAL] = &Text::local;
  _funct[ONLINE] = &Text::online;
}

Text::~Text()
{
  std::map<MenuText, std::vector<gdl::Geometry *> >::iterator it;
  size_t i(0);
  
  for (it = _word.begin(); it != _word.end(); ++it)
    for (i = 0; i != (*it).second.size(); i++)
      delete (*it).second[i];
}

void	Text::update(gdl::Clock const &clock, gdl::Input &input)
{}

int	Text::getColumn(char c)
{
  if (c == '.')
    {
      _firstChar = ' ';
      return (16);
    }
  if (c >= '0' && c <= '9')
    {
      _firstChar = '0';
      return (15);
    }
  if (c >= '@' && c <= 'O')
    {
      _firstChar = '@';
      return (14);
    }
  if (c >= 'P' && c <= '\\')
    {
      _firstChar = 'P';
      return (13);
    }
  return (0);
}

void	Text::putchar(char c, int size,   std::vector<gdl::Geometry *> &_text)
{
  gdl::Geometry *geometry = new gdl::Geometry();
  
  int	div;

  c -= (c >= 'a' && c <= 'z') ? 32 : 0;
  div = getColumn(c);
  _texture.bind();
  geometry->setColor(glm::vec4(0, 1, 1, 0));
  geometry->pushVertex(glm::vec3(0, 0, 0));
  geometry->pushVertex(glm::vec3(size, 0, 0));
  geometry->pushVertex(glm::vec3(size, size, 0));
  geometry->pushVertex(glm::vec3(0, size, 0));
  geometry->pushUv(glm::vec2((c - _firstChar) / 16.0f, (div) / 16.0f));
  geometry->pushUv(glm::vec2((c - _firstChar + 1) / 16.0f, (div) / 16.0f));  
  geometry->pushUv(glm::vec2((c - _firstChar + 1) / 16.0f, (div - 1) / 16.0f));
  geometry->pushUv(glm::vec2((c - _firstChar) / 16.0f, (div - 1) / 16.0f));
  geometry->build();
  _text.push_back(geometry);
}

bool	Text::initialize()
{
  return (true);
}

void	Text::putstr(const char *str, int size, MenuText type)
{
  std::vector<gdl::Geometry *> _text;

  _camera->setMode();
  for (size_t i(0); str[i]; i++)
    this->putchar(str[i], size, _text);
  _word[type] = _text;
  _camera->setMode();
}

void	Text::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  std::map<MenuText, std::vector<gdl::Geometry *> >::iterator it;

  (void)clock;
  _camera->setMode();
  _texture.bind();
  for (it = _word.begin(); it != _word.end(); ++it)
    (this->*_funct[(*it).first])((*it).second);
  _camera->setMode();
}

void	Text::title(std::vector<gdl::Geometry *> &text)
{
  int	        col;
  glm::mat4	transformation;
  
  col = WIDTH_T / 2;
  for (size_t i(0); i != text.size(); i++)
    {
      transformation = glm::translate(glm::mat4(1), glm::vec3(col, 15, 0));
      text[i]->draw(_shader, transformation, GL_QUADS);
      col += 50;
    }
}

void	Text::subTitle(std::vector<gdl::Geometry *> &text)
{
  int	        col;
  glm::mat4	transformation;
  
  col = WIDTH_T / 2 + 17;
  for (size_t i(0); i != text.size(); i++)
    {
      transformation = glm::translate(glm::mat4(1), glm::vec3(col, 80, 0));
      text[i]->draw(_shader, transformation, GL_QUADS);
      col += 25;
    }
}

void	Text::local(std::vector<gdl::Geometry *> &text)
{
  int	        col;
  glm::mat4	transformation;
  
  if (_menu)
    {
      col = 15;
      for (size_t i(0); i != text.size(); i++)
	{
	  transformation = glm::translate(glm::mat4(1), glm::vec3(col, 300, 0));
	  text[i]->draw(_shader, transformation, GL_QUADS);
	  col += 50;
	}
    }
}

void	Text::online(std::vector<gdl::Geometry *> &text)
{
  int	        col;
  glm::mat4	transformation;

  if (_menu)
    {
      col = 15;
      for (size_t i(0); i != text.size(); i++)
	{
	  transformation = glm::translate(glm::mat4(1), glm::vec3(col, 380, 0));
	  text[i]->draw(_shader, transformation, GL_QUADS);
	  col += 50;
	}
    }
}

void	Text::setShow(bool menu)
{
  _menu = menu;
}
