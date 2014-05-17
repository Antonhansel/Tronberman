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

Text::Text(Camera *camera, Loader *load) : _firstChar(0)
{
  _camera = camera;
  _loader = load;
  _lastType = UNSELECTED;
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

  glDisable(GL_DEPTH_TEST);
  glAlphaFunc(GL_GREATER, 0.1f);
  glEnable(GL_ALPHA_TEST);
  c -= (c >= 'a' && c <= 'z') ? 32 : 0;
  div = getColumn(c);
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
  glEnable(GL_DEPTH_TEST);
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

void	Text::draw(const std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &map, int isSelect)
{
  int __attribute__((unused))col(0);
  int __attribute__((unused))row(0);
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> >::const_iterator it;

  _loader->bindTexture(_lastType);
  _camera->setMode();
  for (it = map.begin(); it != map.end(); ++it)
    {
      col = (*it).first.second.first;
      row = (*it).first.second.second;
      textureBind((*it).first.first, isSelect);
      for (size_t i(0); i != (*it).second.size(); i++)
      {
        _transformation = glm::translate(glm::mat4(1), glm::vec3(col, row, 0));
        (*it).second[i]->draw(_camera->getShader(), _transformation, GL_QUADS);
        col += 50; 
      }
    }
  _camera->setMode();
}

void  Text::textureBind(int count, int isSelect)
{
  if (count == isSelect && _lastType != SELECTED)
   {
    _lastType = SELECTED;
    _loader->bindTexture(_lastType);
   }
  else if (_lastType == SELECTED)
    {
      _lastType = UNSELECTED;
      _loader->bindTexture(_lastType);        
    }
}

void  Text::modifyWord(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > *old, const std::vector<std::string> &words)
{
  size_t  cptr;

  cptr = 0;
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> >::iterator   it; 
  for (it = old->begin(); it != old->end(); ++it)
  {
    // AVERIFIER !!!!!! MERKI CHOUAGI
    for (std::vector<gdl::Geometry *>::iterator v = (*it).second.begin(); v != (*it).second.end();)
    {
      v = (*it).second.erase(v);
    }
    if (cptr < words.size())
    {
      (*it).second = putstr(words[cptr].c_str(), 64);      
    }
    else
      (*it).second = putstr("", 64);
    cptr++;
  }
}

void  Text::addNb(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > *old, int index, const std::string &input)
{
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> >::iterator   it; 
  it = old->begin();
  for (int i = 0; i < index; i++)
    ++it;
  for (std::vector<gdl::Geometry *>::iterator v = (*it).second.begin(); v != (*it).second.end(); ++v)
    v = (*it).second.erase(v);
  (*it).second = putstr(input.c_str(), 64);
}
