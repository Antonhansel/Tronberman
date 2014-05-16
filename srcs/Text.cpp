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

Text::Text(Camera *camera) : _firstChar(0)
{
  _camera = camera;
  _texture.load("./ressources/fonts/24BitTron.tga");
}

Text::~Text()
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

void	Text::putchar(char c, int size, std::vector<gdl::Geometry *> &_text)
{
  gdl::Geometry *geometry = new gdl::Geometry();  
  int	div;

  c -= (c >= 'a' && c <= 'z') ? 32 : 0;
  div = getColumn(c);
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

std::vector<gdl::Geometry *> Text::putstr(const char *str, int size)
{
  std::vector<gdl::Geometry *> text;

  _camera->setMode();
  for (size_t i(0); str[i]; i++)
    this->putchar(str[i], size, text);
  _camera->setMode();
  return (text);
}

void	Text::draw(const std::map<std::pair<int, int>, std::vector<gdl::Geometry *> > &map)
{
  int __attribute__((unused))col(0);
  int __attribute__((unused))row(0);
  std::map<std::pair<int, int>, std::vector<gdl::Geometry *> >::const_iterator it;
  glm::mat4 transformation;

  _texture.bind(); 
  _camera->setMode();
  for (it = map.begin(); it != map.end(); ++it)
    {
      col = (*it).first.first;
      row = (*it).first.second;
      for (size_t i(0); i != (*it).second.size(); i++)
      {
        transformation = glm::translate(glm::mat4(1), glm::vec3(col, row, 0));
        (*it).second[i]->draw(_camera->getShader(), transformation, GL_QUADS);
        col += 50; 
      }
    }
  _camera->setMode();
}
