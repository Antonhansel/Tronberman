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

Text::Text(Camera *camera, Loader *load) : _firstChar(0)
{
  glAlphaFunc(GL_GREATER, 0.1f);
  glEnable(GL_ALPHA_TEST);
  _camera = camera;
  _loader = load;
  _lastType = UNSELECTED;
}

Text::~Text()
{}

int	Text::getColumn(char c)
{
  int ret;

  ret = 0;
  (c == '.') ? (_firstChar = ' ', ret = 16) : 0;
  (c >= '0' && c <= '9') ? (_firstChar = '0', ret = 15) : 0;
  (c >= '@' && c <= 'O') ? (_firstChar = '@', ret = 14) : 0;
  (c >= 'P' && c <= '\\') ? (_firstChar = 'P', ret = 13) : 0;
  return (ret);
}

int Text::getOtherColumn(char c)
{
  int ret;

  ret = 0;
  (c == '.') ? (_firstChar = ' ', ret = 8) : 0;
  (c >= '0' && c <= '9') ? (_firstChar = '0', ret = 7) : 0;
  (c >= '@' && c <= 'O') ? (_firstChar = '@', ret = 6) : 0;
  (c >= 'P' && c <= '\\') ? (_firstChar = 'P', ret = 5) : 0;
  return (ret);
}

void	Text::putchar(char c, int size, std::vector<gdl::Geometry *> &_text, bool other)
{
  gdl::Geometry *geometry = new gdl::Geometry();  
  int	div;

  glDisable(GL_DEPTH_TEST);
  c -= (c >= 'a' && c <= 'z') ? 32 : 0;
  div = other ? getColumn(c) : getOtherColumn(c);
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

std::vector<gdl::Geometry *> Text::putstr(const char *str, int size, bool other)
{
  std::vector<gdl::Geometry *> text;

  _camera->setMode();
  for (size_t i(0); str[i]; i++)
    this->putchar(str[i], size, text, other);
  _camera->setMode();
  return (text);
}

void	Text::draw(const std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &map, int isSelect)
{
  int col;
  int row;
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> >::const_iterator it;

  row = 0;
  col = 0;
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

void  Text::modifyWord(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > *old, const std::vector<std::pair<bool, std::string> > &words)
{
  size_t  cptr;

  cptr = 0;
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> >::iterator   it; 
  for (it = old->begin(); it != old->end(); ++it)
  {
    if (cptr < words.size())
      (*it).second = putstr(words[cptr].second.c_str(), 64, words[cptr].first);      
    else
      (*it).second = putstr("", 64, true);
    cptr++;
  }
}

void  Text::addNb(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > *old, int index, const std::string &input)
{
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> >::iterator   it;
  it = old->begin();
  for (int i = 0; i < index; i++)
    ++it;
  (*it).second = putstr(input.c_str(), 64, false);
}

void  Text::addText(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &t, int id, const std::pair<int, int> &p, const std::string& s, bool type)
{
  t[std::make_pair(id, p)] = putstr(s.c_str(), 64, type);
}

void  Text::deleteText(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &t, const std::pair<int, std::pair<int, int> > &p)
{
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> >::iterator   it;

  it = t.find(p);
  t.erase(it);
}

void  Text::deleteAllText(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &t)
{
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> >::iterator   it;

  for (it = t.begin(); it != t.end(); ++it)
    deleteText(t, (*it).first);
}