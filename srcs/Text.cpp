/*
** Text.cpp for Text in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Fri May  02 10:46:08 2014 Antonin Ribeaud
// Last update Fri May  9 15:36:43 2014 Mehdi Chouag
*/

#include "Text.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Text::Text() : _firstChar(0), _isDraw(false)
{
  _texture.load("./ressources/fonts/24BitTron.tga");
}

Text::~Text()
{}

void	Text::update(gdl::Clock const &clock, gdl::Input &input)
{
  for (size_t i(0); i != _text.size(); i++)
    delete _text[i];
}

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

void	Text::putchar(char c)
{
  gdl::Geometry *geometry = new gdl::Geometry();

  int	div;

  c -= (c >= 'a' && c <= 'z') ? 32 : 0;
  div = getColumn(c);
  glPushMatrix();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  _texture.bind();
  geometry->setColor(glm::vec4(0, 1, 1, 0));
  geometry->pushVertex(glm::vec3(0, 0, 0));
  geometry->pushVertex(glm::vec3(0.1, 0, 0));
  geometry->pushVertex(glm::vec3(0.1, 0.1, 0));
  geometry->pushVertex(glm::vec3(0, 0.1, 0));
  geometry->pushUv(glm::vec2((c - _firstChar) / 16.0f, (div - 1) / 16.0f));
  geometry->pushUv(glm::vec2((c - _firstChar + 1) / 16.0f, (div - 1) / 16.0f));  
  geometry->pushUv(glm::vec2((c - _firstChar + 1) / 16.0f, div / 16.0f));
  geometry->pushUv(glm::vec2((c - _firstChar) / 16.0f, div / 16.0f));
  _text.push_back(geometry);
  std::cout <<  _text.size() << std::endl;
  glDisable(GL_BLEND);
  glPopMatrix();
}

bool	Text::initialize()
{
  return (true);
}

void	Text::putstr(const char *str)
{
  for (size_t i(0); str[i]; i++)
    this->putchar(str[i]);
}

void	Text::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  std::vector<gdl::Geometry>::iterator it;
  glm::mat4 projection;
  glm::mat4 transformation(1);

  projection = glm::ortho(0, 1800, 1000, 0, -1, 1);
  transformation = lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
  shader.bind();
  shader.setUniform("view", transformation);
  // shader.bind();
  // shader.setUniform("projection", projection);
  _texture.bind();
  translate(glm::vec3(-1, 0, 0));
  for (size_t i(0); i != _text.size(); i++)
    {
      _text[i]->build();
      _text[i]->draw(shader, getTransformation(), GL_QUADS);
      translate(glm::vec3(0.1, 0, 0));
    }
  _isDraw = true;
}
