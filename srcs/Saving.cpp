/*
** Saving.cpp for Saving in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Tue May  20 10:56:43 2014 Antonin Ribeaud
** Last update Tue May  20 10:56:43 2014 Antonin Ribeaud
*/

#include "Saving.hpp"

Saving::Saving(std::string &file_name) : _name(file_name)
{
  if (loadMap(file_name) == false)
  {
    _isGood = false;
    std::cout << "Failed to Load" << std::endl;
  }
  else
    _isGood = true;
}

Saving::~Saving()
{
	delete _map;
	while (_spawn.size() > 0)
		_spawn.pop_back();
}

bool    Saving::loadSize(std::list<std::string> &file)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<size>";
  std::string       out = "</size>";


  str = file.front();
  if (myBalise(in, out, str, file.front()) == false)
    return false;
  myParseur(tab, str);
  if (tab.size() != 1)
  {
    std::cout << "Error line " << _nbrLine << ":" << std::endl;
    std::cout << "Bad value '" << str << "'" << std::endl;
    return (false);
  }
  _sizeMap = tab.back();
  _map = new AObject *[_sizeMap * _sizeMap];
  memset(_map, 0, (_sizeMap * _sizeMap) * sizeof(AObject *));
  return true;
}

bool    Saving::loadCase(std::list<std::string> &file)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<case>";
  std::string       out = "</case>";
  AObject           *tmp;
  std::pair<float, float> pos;
  type _type;
  int x;
  int y;
  int t;

  str = file.front();
  if (myBalise(in, out, str, file.front()) == false)
    return false;
  myParseur(tab, str);
  if (tab.size() != 3)
  {
    std::cout << "Error line " << _nbrLine << ":" << std::endl;
    std::cout << "Bad value '" << str << "'" << std::endl;
    return (false);
  }
  t = tab.back();
  tab.pop_back();
  x = tab.back();
  tab.pop_back();
  y = tab.back();
  _type = (type)t;
  tmp = create<Cube>();
  pos = std::make_pair(x, y);
  tmp->setType(_type);
  tmp->setPos(pos);
  tmp->initialize();
  _map[x * _sizeMap + y] = tmp;
  return true;
}

bool    Saving::loadSpawn(std::list<std::string> &file)
{
  std::vector<int> tab;
  std::string       str;
  std::string       in = "<spawn>";
  std::string       out = "</spawn>";
  int x;
  int y;

  str = file.front();
  if (myBalise(in, out, str, file.front()) == false)
    return false;
  myParseur(tab, str);
  if (tab.size() != 2)
  {
    std::cout << "Error line " << _nbrLine << ":" << std::endl;
    std::cout << "Bad value '" << str << "'" << std::endl;
    return (false);
  }
  x = tab.back();
  tab.pop_back();
  y = tab.back();
  tab.pop_back();
  _spawn.push_back(std::make_pair(x, y));
  return true;
}

bool    Saving::loadMap(std::string &file_name)
{
  std::list<std::string>  file;
  std::string             str;
  std::ifstream           infile(file_name.c_str());
  std::size_t             pos;
  bool                    error;

  while (std::getline(infile, str))
    file.push_back(str);
  _nbrLine = 1;
  if (file.size() > 0)
  {
    while ((pos = file.front().find("<map>")) == std::string::npos
          && file.size() > 0)
    {
      file.pop_front();
      _nbrLine++;
    }
    _nbrLine++;
    file.pop_front();
    std::string front;
    while ((pos = file.front().find("</map")) == std::string::npos
          && file.size() > 0)
    {
      error = true;
      front = file.front();
      if ((pos = front.find("<size>")) != std::string::npos)
        error = loadSize(file);
      if ((pos = front.find("<case>")) != std::string::npos)
        error = loadCase(file);
      if ((pos = front.find("<spawn>")) != std::string::npos)
        error = loadSpawn(file);
      if (error == false)
        return false;
      std::cout << file.front() << std::endl;
      if (file.front() == "")
      {
        file.pop_front();
        _nbrLine++;
      }
    }
  }
  else
  {
    std::cout << "The map is not found." << std::endl;    
    return false;
  }
  return true;
}

void        Saving::myParseur(std::vector<int> &tab, std::string &str)
{
  std::size_t   x;
  std::size_t   y;
  int v;
  tab.clear();

  x = 0;
  y = 0;
  while (str[y])
  {
    if (str[y] == ' ')
    {
      std::istringstream buffer(str.substr(x, y - x + 1));
      buffer >> v;
      tab.push_back(v);
      x = y + 1;
    }
    ++y;
  }
  std::istringstream buffer(str.substr(x, y - x + 1));
  buffer >> v;
  tab.push_back(v);
}

bool        Saving::myBalise(std::string &in, std::string &out, 
                              std::string &str, std::string &front)
{
  std::size_t pos = str.find(in) + in.length();
  std::size_t pos2 = str.find(out);

  if (pos2 != std::string::npos)
    str = str.substr(pos, pos2 - pos);
  else
  {
    std::cout << "Error line " << _nbrLine <<
    " in the file \"" << _name << "\"" << std::endl;
    return (false);
  }
  front = front.substr(pos2 + out.length());
  return (true);
}

Map                 *Saving::returnMap()
{
  if (_isGood == false)
    return NULL;
  Map *myMap = new Map(_sizeMap);
  myMap->setMap(_map);
  myMap->setSpawn(_spawn);
  myMap->setSize(_sizeMap);
  return myMap;
}